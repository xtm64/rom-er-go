#!/usr/bin/env perl
# arhu_maps.pl - audit, port and validate FRLG-derived maps for the Emerald build
# (MAP_VERSION=emerald) of this pokeemerald-expansion hack.
#
#   perl arhu_maps.pl audit    <FrlgMapName> [--orig-ref REF]
#   perl arhu_maps.pl port     <Src=New> [<Src=New> ...] --group <gMapGroup_X> [--write]
#                              [--no-scripts] [--encounters auto|FireRed|LeafGreen|none]
#                              [--retarget MAP_OLD=MAP_NEW ...] [--promote-overflow]
#                              [--substitute FRLGID=EMERALDID ...]
#   perl arhu_maps.pl validate [MapName ...]            (default: every map whose name contains ARHU)
#   perl arhu_maps.pl restore-behaviors <gTileset_X> [...] [--classes ...] [--write]
#
# Nothing is written unless `port --write` is given. Every registry edit is made in
# memory, re-parsed as JSON, and only then written to disk.

use strict;
use warnings;
use JSON::PP ();
use File::Path qw(make_path);
use File::Basename qw(dirname);
use Getopt::Long qw(GetOptionsFromArray);

# Last commit whose FRLG tileset binaries are still the untouched upstream versions.
# Used only to report how the in-place Emerald conversion changed metatile behaviors.
my $ORIG_REF_DEFAULT = '2edab6211b^';

my $NUM_PRIMARY_EM   = 512;   # NUM_METATILES_IN_PRIMARY
my $NUM_PRIMARY_FRLG = 640;   # NUM_METATILES_IN_PRIMARY_FRLG
my $NUM_TOTAL        = 1024;  # NUM_METATILES_TOTAL

my $JSON = JSON::PP->new->allow_nonref->canonical;

sub usage {
    return <<'EOF';
usage:
  perl arhu_maps.pl audit    <FrlgMapName> [--orig-ref REF]
  perl arhu_maps.pl port     <Src=New> [<Src=New> ...] --group <gMapGroup_X> [--write]
                             [--no-scripts] [--encounters auto|FireRed|LeafGreen|none]
                             [--retarget MAP_OLD=MAP_NEW ...] [--promote-overflow]
                             [--substitute FRLGID=EMERALDID ...] [--orig-ref REF] [--keep-sprites]
  perl arhu_maps.pl validate [MapName ...]
  perl arhu_maps.pl restore-behaviors <gTileset_X> [...] [--classes grass,water,ledge,warp|all]
                             [--orig-ref REF] [--write]
  perl arhu_maps.pl roadmap  [design-map.json]   (default: the Fervor Field design source)
EOF
}

# ---------------------------------------------------------------- utilities

sub chdir_to_repo {
    my $top = `git rev-parse --show-toplevel 2>/dev/null`;
    chomp $top;
    chdir $top if $top ne '' && -d $top;
    die "run from inside the rom repo (data/maps/map_groups.json not found)\n"
        unless -f 'data/maps/map_groups.json';
}

sub read_text {
    my ($path) = @_;
    open my $fh, '<:raw', $path or die "cannot read $path: $!\n";
    local $/;
    my $t = <$fh>;
    return $t // '';
}

sub write_text {
    my ($path, $text) = @_;
    make_path(dirname($path));
    open my $fh, '>:raw', $path or die "cannot write $path: $!\n";
    print $fh $text;
    close $fh or die "cannot write $path: $!\n";
}

sub read_json {
    my ($path) = @_;
    my $data = eval { $JSON->decode(read_text($path)) };
    die "invalid JSON in $path: $@" if $@;
    return $data;
}

sub git_show_raw {
    my ($ref, $path) = @_;
    open my $fh, '-|:raw', 'git', 'show', "$ref:$path" or return undef;
    local $/;
    my $data = <$fh>;
    close $fh;
    return ($? == 0 && defined $data) ? $data : undef;
}

sub snake {
    my ($name) = @_;
    my @parts = split /_/, $name;
    for (@parts) {
        next if /^[A-Z0-9]+$/;
        s/(?<=[a-z0-9])(?=[A-Z])/_/g;
        s/(?<=[A-Z])(?=[A-Z][a-z])/_/g;
    }
    return uc join '_', @parts;
}

sub frlg_prefix {
    my ($name) = @_;
    (my $p = $name) =~ s/_Frlg$//;
    return $p;
}

# Evaluate a #if / .if condition for an Emerald build: 1, 0, or undef (unknown).
sub eval_cond {
    my ($c) = @_;
    $c =~ s{//.*$}{};
    $c =~ s/^\s+|\s+$//g;
    return 0 if $c =~ /^\(?\s*IS_FRLG\s*\)?$/;
    return 1 if $c =~ /^!\s*\(?\s*IS_FRLG\s*\)?$/;
    return 0 if $c =~ /^(?:defined\s*\(?\s*)?(?:FIRERED|LEAFGREEN)\b/;
    return 1 if $c =~ /^(?:defined\s*\(?\s*)?EMERALD\b/;
    return undef;
}

# Returns the text with lines that are compiled out of the Emerald build blanked.
# Unknown conditions keep both branches (conservative for "is it defined" checks).
sub emerald_active_text {
    my ($text) = @_;
    my @stack;
    my @out;
    for my $line (split /\n/, $text, -1) {
        my $active = !grep { !$_->{active} } @stack;
        if ($line =~ /^\s*#\s*if\s+(.*)$/ || $line =~ /^\s*\.if\s+(.*)$/) {
            push @stack, { val => eval_cond($1), else => 0 };
            update_frame($stack[-1]);
        } elsif ($line =~ /^\s*#\s*ifdef\s+(\w+)/) {
            push @stack, { val => eval_cond("defined($1)"), else => 0 };
            update_frame($stack[-1]);
        } elsif ($line =~ /^\s*#\s*ifndef\s+(\w+)/) {
            my $v = eval_cond("defined($1)");
            push @stack, { val => defined $v ? !$v : undef, else => 0 };
            update_frame($stack[-1]);
        } elsif ($line =~ /^\s*(?:#\s*|\.)else\b/ && @stack) {
            $stack[-1]{else} = 1;
            update_frame($stack[-1]);
        } elsif ($line =~ /^\s*#\s*elif\b/ && @stack) {
            $stack[-1]{val} = undef;
            $stack[-1]{else} = 0;
            update_frame($stack[-1]);
        } elsif ($line =~ /^\s*(?:#\s*endif|\.endif)\b/ && @stack) {
            pop @stack;
        } else {
            push @out, $active ? $line : '';
            next;
        }
        push @out, '';
    }
    return join "\n", @out;
}

sub update_frame {
    my ($f) = @_;
    if (!defined $f->{val}) { $f->{active} = 1; return; }
    $f->{active} = $f->{else} ? !$f->{val} : $f->{val};
}

# ---------------------------------------------------------------- build model

my %M;    # lazily-built model of what the Emerald build contains

sub model {
    return \%M if %M;
    for my $step (\&load_behaviors, \&load_tilesets, \&load_layouts, \&load_maps, \&load_labels,
                  \&load_constants, \&load_gfx, \&load_macros, \&load_doors, \&load_specials, \&load_encounters) {
        my $t = time;
        $step->();
        printf STDERR "[profile] step took %ds\n", time - $t if $ENV{ARHU_PROFILE};
    }
    return \%M;
}

sub load_behaviors {
    my $t = read_text('include/constants/metatile_behaviors.h');
    my $i = 0;
    my %name;
    while ($t =~ /^\s*(MB_\w+)\s*(?:=\s*(\w+))?\s*,/mg) {
        $i = $2 =~ /^0x/i ? hex($2) : $2 if defined $2;
        $name{$i++} = $1;
    }
    $M{mb} = \%name;
}

sub mb_name {
    my ($v) = @_;
    return 'none' unless defined $v;
    return $M{mb}{$v} // sprintf('MB_0x%02X', $v);
}

sub mb_class {
    my ($n) = @_;
    return 'grass'   if $n =~ /GRASS/;
    return 'water'   if $n =~ /WATER|WATERFALL|PUDDLE|CURRENT/;
    return 'ledge'   if $n =~ /^MB_JUMP_/;
    return 'warp'    if $n =~ /DOOR|WARP|LADDER|ESCALATOR|STAIR|HOLE/;
    return 'counter' if $n eq 'MB_COUNTER';
    return 'sand'    if $n =~ /SAND/;
    return 'normal'  if $n eq 'MB_NORMAL';
    return 'other';
}

sub load_tilesets {
    my $hdr_all = read_text('src/data/tilesets/headers.h');
    my $hdr_em  = emerald_active_text($hdr_all);
    my $mt_all  = read_text('src/data/tilesets/metatiles.h');
    my $mt_em   = emerald_active_text($mt_all);

    my (%path_all, %path_em);
    while ($mt_all =~ /const\s+u16\s+(\w+)\[\]\s*=\s*INCBIN_U16\("([^"]+)"\)/g) { $path_all{$1} = $2 }
    while ($mt_em  =~ /const\s+u16\s+(\w+)\[\]\s*=\s*INCBIN_U16\("([^"]+)"\)/g) { $path_em{$1}  = $2 }

    my %ts;
    for my $pass ([$hdr_all, 0], [$hdr_em, 1]) {
        my ($text, $em) = @$pass;
        while ($text =~ /const\s+struct\s+Tileset\s+(\w+)\s*=\s*\{(.*?)\};/sg) {
            my ($sym, $body) = ($1, $2);
            my %f;
            $f{$1} = $2 while $body =~ /\.(\w+)\s*=\s*([^,\n]+)/g;
            s/^\s+|\s+$//g for values %f;
            my $e = $ts{$sym} //= { sym => $sym };
            $e->{secondary} = ($f{isSecondary} // '') eq 'TRUE' ? 1 : 0;
            $e->{mt_sym}    = $f{metatiles};
            $e->{attr_sym}  = $f{metatileAttributes};
            if ($em) {
                $e->{emerald} = defined $path_em{ $e->{mt_sym} // '' }
                             && defined $path_em{ $e->{attr_sym} // '' } ? 1 : 0;
            }
        }
    }
    for my $e (values %ts) {
        $e->{emerald} //= 0;
        $e->{mt_path}   = $path_all{ $e->{mt_sym}   // '' };
        $e->{attr_path} = $path_all{ $e->{attr_sym} // '' };
        next unless $e->{mt_path} && -f $e->{mt_path} && $e->{attr_path} && -f $e->{attr_path};
        my $mts = -s $e->{mt_path};
        my $ats = -s $e->{attr_path};
        $e->{count}  = int($mts / 16);
        $e->{format} = $ats * 8 == $mts ? 'emerald' : $ats * 4 == $mts ? 'frlg' : 'unknown';
    }
    $M{ts} = \%ts;
}

sub tileset_attrs {
    my ($sym, $raw_override, $as_frlg) = @_;
    my $e = $M{ts}{$sym} or return [];
    my $raw = $raw_override // ($M{ts_override} || {})->{$sym}
           // ($e->{attr_path} && -f $e->{attr_path} ? read_text($e->{attr_path}) : '');
    my $fmt = $as_frlg ? 'frlg' : ($e->{format} // 'emerald');
    if ($fmt eq 'frlg') {
        return [ map { $_ & 0x1FF } unpack 'V*', $raw ];
    }
    return [ map { $_ & 0xFF } unpack 'v*', $raw ];
}

# FRLG tile numbers as they appear after the in-place Emerald conversion: secondary tiles
# moved from 640+ to 512+, and FRLG primary tiles 512-639 were appended to the secondary
# sheets at index 192 (tile 704+).
sub norm_frlg_tile {
    my ($t) = @_;
    my $id = $t & 0x3FF;
    my $hi = $t & 0xFC00;
    $id = $id >= 640 ? $id - 128 : $id >= 512 ? $id + 192 : $id;
    return $hi | $id;
}

# Per-metatile comparison of a converted tileset with its original at $ref.
# Each entry: { i, gfx (graphics changed), ob/ol (original behavior/layer), cb/cl (current) }.
sub orig_tileset_diff {
    my ($sym, $ref) = @_;
    my $ts = $M{ts}{$sym} or return undef;
    return $ts->{_diff}{$ref} if $ts->{_diff}{$ref};
    return undef unless ($ts->{format} // '') eq 'emerald';
    my $oa = git_show_raw($ref, $ts->{attr_path});
    my $om = git_show_raw($ref, $ts->{mt_path});
    return undef unless defined $oa && defined $om && length $om;
    my $ofmt = length($oa) * 4 == length($om) ? 'frlg' : length($oa) * 8 == length($om) ? 'emerald' : return undef;
    my @OA = unpack($ofmt eq 'frlg' ? 'V*' : 'v*', $oa);
    my @OM = unpack 'v*', $om;
    my @CA = unpack 'v*', read_text($ts->{attr_path});
    my @CM = unpack 'v*', read_text($ts->{mt_path});
    my @d;
    for my $i (0 .. $#CA) {
        last if $i > $#OA;
        my $g = 0;
        for my $k (0 .. 7) {
            my $o = $OM[ $i * 8 + $k ];
            my $c = $CM[ $i * 8 + $k ];
            next unless defined $o && defined $c;
            $g = 1 if ($ofmt eq 'frlg' ? norm_frlg_tile($o) : $o) != $c;
        }
        my ($ob, $ol) = $ofmt eq 'frlg' ? ($OA[$i] & 0x1FF, ($OA[$i] >> 29) & 3) : ($OA[$i] & 0xFF, ($OA[$i] >> 12) & 0xF);
        push @d, { i => $i, gfx => $g, ob => $ob, ol => $ol, cb => $CA[$i] & 0xFF, cl => ($CA[$i] >> 12) & 0xF };
    }
    return $ts->{_diff}{$ref} = \@d;
}

sub load_layouts {
    my $data = read_json('data/layouts/layouts.json');
    my %by_id;
    for my $l (@{ $data->{layouts} }) {
        next unless ref $l eq 'HASH' && $l->{id};
        my $ver = $l->{layout_version} // '';
        $l->{_emerald} = ($ver eq '' || $ver eq 'emerald') && -f ($l->{border_filepath} // '') ? 1 : 0;
        $by_id{ $l->{id} } = $l;
    }
    $M{layouts} = \%by_id;
}

sub load_maps {
    my $groups = read_json('data/maps/map_groups.json');
    my (%by_id, %by_name);
    my $gnum = 0;
    for my $g (@{ $groups->{group_order} }) {
        my $num = 0;
        for my $name (@{ $groups->{$g} // [] }) {
            my $path = "data/maps/$name/map.json";
            next unless -f $path;
            my $j = read_json($path);
            my $region = $j->{region} // 'REGION_HOENN';
            my $info = { name => $name, id => $j->{id}, json => $j, group => $g,
                         path => $path, emerald => $region eq 'REGION_HOENN' ? 1 : 0 };
            $by_id{ $j->{id} } = $info if $j->{id};
            $by_name{$name} = $info;
            $num++;
        }
        $gnum++;
    }
    $M{groups} = $groups;
    $M{maps_by_id} = \%by_id;
    $M{maps_by_name} = \%by_name;

    # mapjson event_constants runs over every data/maps/*/map.json, grouped or not.
    my %localid;
    for my $path (glob 'data/maps/*/map.json') {
        my $j = eval { read_json($path) } or next;
        my $objs = $j->{object_events} || [];
        for my $i (0 .. $#$objs) {
            my $lid = $objs->[$i]{local_id} or next;
            push @{ $localid{$lid} }, { idx => $i + 1, map => $j->{name} // $path };
        }
        my $warps = $j->{warp_events} || [];
        for my $i (0 .. $#$warps) {
            my $wid = $warps->[$i]{warp_id} or next;
            push @{ $localid{$wid} }, { idx => $i, map => $j->{name} // $path };
        }
    }
    $M{event_ids} = \%localid;
}

sub load_labels {
    my (%labels, %seen);
    my @queue = glob 'data/*.s';
    while (my $file = shift @queue) {
        next if $seen{$file}++;
        next unless -f $file;
        my $text = emerald_active_text(read_text($file));
        for my $line (split /\n/, $text) {
            if ($line =~ /^\s*\.include\s+"([^"]+\.inc)"/) {
                push @queue, $1;
            } elsif ($line =~ /^\s*([A-Za-z_]\w*)::?(?!\S)/) {
                push @{ $labels{$1} }, $file;
            }
        }
    }
    $M{labels} = \%labels;
    $M{included} = \%seen;
}

sub load_constants {
    my %flags;
    my $ft = emerald_active_text(read_text('include/constants/flags.h'));
    $flags{$1} = $2 while $ft =~ /^\s*#\s*define\s+(FLAG_\w+)\s+(.+?)\s*(?:\/\/.*)?$/mg;
    $M{flags} = \%flags;

    my (%vars, %frlg_var);
    for my $f ('include/constants/vars.h', 'include/constants/vars_frlg.h') {
        next unless -f $f;
        my $t = emerald_active_text(read_text($f));
        my $is_frlg = $f =~ /_frlg/;
        while ($t =~ /^\s*#\s*define\s+(VAR_\w+)\s+(.+?)\s*(?:\/\/.*)?$/mg) {
            my ($name, $val) = ($1, $2);
            $vars{$name} = $val;
            $frlg_var{$name} = 1 if $is_frlg;
        }
    }
    $M{vars} = \%vars;
    $M{frlg_var} = \%frlg_var;

    my %generic;
    for my $f (glob 'include/constants/*.h') {
        next if $f =~ /map_event_ids\.h$/;
        my $t = read_text($f);
        $generic{$1} = 1 while $t =~ /^\s*#\s*define\s+(LOCALID_\w+)/mg;
    }
    $M{generic_localids} = \%generic;
}

sub const_value {
    my ($table, $name, $depth) = @_;
    $depth //= 0;
    my $v = $table->{$name};
    return undef if !defined $v || $depth > 8;
    $v =~ s/\b([A-Z_][A-Z0-9_]*)\b/my $x = const_value($table, $1, $depth + 1); defined $x ? $x : 'X'/ge;
    return undef if $v =~ /X/ || $v !~ /^[\s0-9a-fA-Fx()+\-*]+$/;
    my $r = eval $v;
    return $@ ? undef : $r;
}

sub load_gfx {
    my $t = emerald_active_text(read_text('src/data/object_events/object_event_graphics_info_pointers.h'));
    my %gfx;
    $gfx{$1} = 1 while $t =~ /\[\s*(OBJ_EVENT_GFX_\w+)\s*\]/g;
    $M{gfx} = \%gfx;
}

sub load_macros {
    my %mac;
    for my $f (glob('asm/macros/*.inc'), glob('asm/*.inc')) {
        my $t = emerald_active_text(read_text($f));
        $mac{$1} = 1 while $t =~ /^\s*\.macro\s+(\w+)/mg;
        # movement.inc generates one macro per action through a helper macro.
        $mac{$1} = 1 while $t =~ /^\s*create_\w+\s+(\w+)\s*,/mg;
    }
    $M{macros} = \%mac;
}

# Door animations the Emerald build knows: sDoorAnimGraphicsTable entries outside #if IS_FRLG.
# GetDoorGraphics matches the metatile id at the door AND one of the layout's two tilesets.
sub load_doors {
    my %lab;
    for my $f (glob 'include/constants/metatile_labels*.h') {
        my $t = read_text($f);
        $lab{$1} = hex $2 while $t =~ /^\s*#\s*define\s+(METATILE_\w+)\s+0x([0-9A-Fa-f]+)/mg;
    }
    my @doors;
    my $t = -f 'src/field_door.c' ? emerald_active_text(read_text('src/field_door.c')) : '';
    while ($t =~ /\{\s*(ARHU_METATILE\(\s*)?(\w+)\s*\)?\s*,\s*&(gTileset_\w+)\s*,\s*(DOOR_SOUND_\w+)\s*,\s*(\d+)\s*,([^}]*)\}/g) {
        my ($arhu, $m, $ts, $rest) = ($1, $2, $3, $6);
        my $id = $m =~ /^0x/i ? hex $m : $m =~ /^\d+$/ ? $m : $lab{$m};
        next unless defined $id;
        # ARHU_METATILE(): FRLG label -> Emerald-layout id (secondary ids drop by 128)
        $id -= $NUM_PRIMARY_FRLG - $NUM_PRIMARY_EM if $arhu && $id >= $NUM_PRIMARY_FRLG;
        push @doors, { id => $id, tileset => $ts, label => $m, frlg_style => $rest =~ /\bTRUE\b/ ? 1 : 0 };
    }
    $M{doors} = \@doors;
}

sub door_anim_for {
    my ($mid, $l) = @_;
    for my $d (@{ $M{doors} || [] }) {
        return $d if $d->{id} == $mid && ($d->{tileset} eq $l->{primary_tileset} || $d->{tileset} eq $l->{secondary_tileset});
    }
    return undef;
}

sub load_specials {
    my %sp;
    if (-f 'data/specials.inc') {
        my $t = read_text('data/specials.inc');
        $sp{$1} = 1 while $t =~ /^\s*def_special\s+(\w+)/mg;
    }
    $M{specials} = \%sp;
}

sub load_encounters {
    my %enc;
    my $data = eval { read_json('src/data/wild_encounters.json') } or return;
    for my $grp (@{ $data->{wild_encounter_groups} || [] }) {
        next unless $grp->{for_maps};
        for my $e (@{ $grp->{encounters} || [] }) {
            next unless $e->{map};
            my @kinds = grep { /_mons$/ } sort keys %$e;
            push @{ $enc{ $e->{map} } }, { label => $e->{base_label}, kinds => \@kinds,
                emerald => ($e->{base_label} // '') =~ /FireRed|LeafGreen/ ? 0 : 1 };
        }
    }
    $M{encounters} = \%enc;
}

# ---------------------------------------------------------------- reporting

my @REPORT;
my $ERRORS = 0;
my $WARNINGS = 0;

sub say_ { print @_, "\n" }
sub err  { $ERRORS++;   say_("  ERROR: ", @_) }
sub warn_{ $WARNINGS++; say_("  WARN:  ", @_) }
sub info { say_("  ", @_) }
sub ok   { say_("  ok:    ", @_) }

# ---------------------------------------------------------------- block data

sub read_blocks {
    my ($path) = @_;
    return [ unpack 'v*', read_text($path) ];
}

sub behaviors_for_layout {
    my ($l, $as_frlg) = @_;
    return (tileset_attrs($l->{primary_tileset}, undef, $as_frlg),
            tileset_attrs($l->{secondary_tileset}, undef, $as_frlg));
}

sub behavior_of {
    my ($id, $prim, $sec, $nprim) = @_;
    return $id < $nprim ? $prim->[$id] : $sec->[ $id - $nprim ];
}

# Converts one FRLG block entry to the Emerald layout of the same (converted) tilesets.
# Returns (new_entry, problem) where problem is undef, 'primary_overflow'.
sub remap_block {
    my ($v) = @_;
    my $id = $v & 0x3FF;
    my $hi = $v & ~0x3FF & 0xFFFF;
    return ($v, undef) if $id == 0x3FF;
    return ($hi | ($id - ($NUM_PRIMARY_FRLG - $NUM_PRIMARY_EM)), undef) if $id >= $NUM_PRIMARY_FRLG;
    return ($v, 'primary_overflow') if $id >= $NUM_PRIMARY_EM;
    return ($v, undef);
}

# ---------------------------------------------------------------- audit

sub cmd_audit {
    my @args = @_;
    my $orig_ref = $ORIG_REF_DEFAULT;
    GetOptionsFromArray(\@args, 'orig-ref=s' => \$orig_ref) or return 2;
    my $name = shift @args or do { print usage(); return 2 };
    model();
    my $info = $M{maps_by_name}{$name} // (-f "data/maps/$name/map.json"
        ? { name => $name, json => read_json("data/maps/$name/map.json"), group => '(not in map_groups.json)' }
        : undef);
    die "no map named $name\n" unless $info;
    my $j = $info->{json};
    say_("== audit $name ($j->{id})");
    info("group: $info->{group}; region: ", $j->{region} // '(none = Hoenn, Emerald build)');
    info("music $j->{music}, mapsec $j->{region_map_section}, type $j->{map_type}, weather $j->{weather}");

    my $l = $M{layouts}{ $j->{layout} } or do { err("layout $j->{layout} not in layouts.json"); return 1 };
    my $is_frlg_layout = ($l->{layout_version} // '') eq 'frlg';
    info("layout $l->{id}: $l->{width}x$l->{height}, border ",
         ($l->{border_width} // 2), 'x', ($l->{border_height} // 2),
         ", version ", ($l->{layout_version} // 'emerald (default)'));
    for my $k (qw(primary_tileset secondary_tileset)) {
        my $ts = $M{ts}{ $l->{$k} };
        if (!$ts) { err("$k $l->{$k} not found in src/data/tilesets/headers.h"); next }
        my $msg = sprintf('%s %s: %d metatiles, attribute format %s, compiled for Emerald: %s',
            $k, $ts->{sym}, $ts->{count} // 0, $ts->{format} // '?', $ts->{emerald} ? 'yes' : 'NO');
        ($ts->{emerald} && ($ts->{format} // '') eq 'emerald') ? info($msg) : err($msg . ' -> tileset must be converted/exposed first (see references/rules.md)');
        if ($k eq 'primary_tileset' && ($ts->{count} // 0) > $NUM_PRIMARY_EM) {
            err("primary tileset has $ts->{count} metatiles; Emerald layouts can only address $NUM_PRIMARY_EM");
        }
    }

    my $blocks = read_blocks($l->{blockdata_filepath});
    my ($prim, $sec) = behaviors_for_layout($l);
    my (%hist, @overflow, %orig_changed, %gfx_changed);
    my ($dprim, $dsec);
    if ($is_frlg_layout && $orig_ref) {
        $dprim = orig_tileset_diff($l->{primary_tileset}, $orig_ref);
        $dsec  = orig_tileset_diff($l->{secondary_tileset}, $orig_ref);
        warn_("could not read original tileset data at $orig_ref; skipping conversion comparison") unless $dprim && $dsec;
    }
    for my $i (0 .. $#$blocks) {
        my $v = $blocks->[$i];
        my $id = $v & 0x3FF;
        my ($nv, $problem) = $is_frlg_layout ? remap_block($v) : ($v, undef);
        if ($problem) { push @overflow, [$i % $l->{width}, int($i / $l->{width}), $id]; next }
        my $nid = $nv & 0x3FF;
        my $b = behavior_of($nid, $prim, $sec, $NUM_PRIMARY_EM);
        $hist{ mb_class(mb_name($b)) }++;
        next unless $dprim && $dsec && $nid != 0x3FF;
        # The same index addresses the metatile in the original and the converted tileset.
        my $d = $nid < $NUM_PRIMARY_EM ? $dprim->[$nid] : $dsec->[ $nid - $NUM_PRIMARY_EM ];
        next unless $d;
        if ($d->{gfx}) { $gfx_changed{$id}{n}++; $gfx_changed{$id}{nid} = $nid }
        if ($d->{ob} != $d->{cb}) {
            my $c = $orig_changed{$id} //= { nid => $nid, from => mb_name($d->{ob}), to => mb_name($d->{cb}), gfx => $d->{gfx} };
            $c->{n}++;
        }
    }
    info('behavior classes after conversion: ', join(', ', map { "$_=$hist{$_}" } sort keys %hist));
    if (@overflow) {
        err(scalar(@overflow) . " cells use FRLG primary metatiles 512-639, which do not exist in the Emerald layout. First: "
            . join(' ', map { "($_->[0],$_->[1])#$_->[2]" } @overflow[0 .. ($#overflow < 9 ? $#overflow : 9)]));
    } elsif ($is_frlg_layout) {
        ok('no FRLG-only primary metatiles (512-639) used');
    }
    if (%orig_changed) {
        warn_("metatile behaviors that differ from the original FRLG data at $orig_ref (FRLG id -> Emerald id: original -> now, cells):");
        for my $id (sort { $orig_changed{$b}{n} <=> $orig_changed{$a}{n} } keys %orig_changed) {
            my $c = $orig_changed{$id};
            my $mark = mb_class($c->{from}) =~ /grass|water|ledge|warp/ ? '  <-- gameplay' : '';
            $mark .= '  (graphics repainted too)' if $c->{gfx};
            info(sprintf('    %4d -> %4d: %s -> %s (%d)%s', $id, $c->{nid}, $c->{from}, $c->{to}, $c->{n}, $mark));
        }
        info('    fix zeroed behaviors with: perl ' . __FILE__ . ' restore-behaviors ' . join(' ', $l->{primary_tileset}, $l->{secondary_tileset}));
    } elsif ($dprim && $dsec) {
        ok("tile behaviors identical to $orig_ref");
    }
    if (%gfx_changed) {
        warn_('metatiles whose graphics were repainted in the shared tileset since the FRLG import (they will look like the Fervor edit, not the original):');
        info('    ' . join(' ', map { "$_->$gfx_changed{$_}{nid}(x$gfx_changed{$_}{n})" } sort { $a <=> $b } keys %gfx_changed));
    }
    my $bw = $l->{border_width} // 2;
    my $bh = $l->{border_height} // 2;
    warn_("border is ${bw}x$bh; Emerald layouts always draw a 2x2 border, port keeps the top-left 2x2")
        if $bw != 2 || $bh != 2;

    audit_events($j, $l, 1);
    my $enc = $M{encounters}{ $j->{id} } || [];
    info('wild encounters: ', @$enc ? join(', ', map { "$_->{label} [" . join('/', @{ $_->{kinds} }) . ']' . ($_->{emerald} ? '' : ' (FRLG-only label)') } @$enc) : 'none');
    if (-f "data/maps/$name/scripts.inc") {
        my $active = grep { $_ eq "data/maps/$name/scripts.inc" } keys %{ $M{included} };
        info("scripts.inc compiled in Emerald build: ", $active ? 'yes' : 'no (inside .if IS_FRLG) -> port copies and renames it');
    }
    say_("summary: $ERRORS error(s), $WARNINGS warning(s)");
    return 0;
}

# Shared event checks. $src = 1 when auditing an FRLG source map (dest maps are informational).
sub audit_events {
    my ($j, $l, $src, $batch_ids, $blocks) = @_;
    $batch_ids //= {};
    my ($w, $h) = ($l->{width}, $l->{height});
    $blocks //= -f ($l->{blockdata_filepath} // '') ? read_blocks($l->{blockdata_filepath}) : [];
    my ($prim, $sec) = behaviors_for_layout($l);
    my $is_frlg_layout = ($l->{layout_version} // '') eq 'frlg';

    my $objs = $j->{object_events} || [];
    my %own_lids;
    for my $i (0 .. $#$objs) {
        my $o = $objs->[$i];
        my $tag = "object #" . ($i + 1) . ($o->{local_id} ? " $o->{local_id}" : '');
        $own_lids{ $o->{local_id} } = 1 if $o->{local_id};
        check_bounds($tag, $o, $w, $h);
        my $g = $o->{graphics_id} // '';
        if (!($M{gfx}{$g} || $g =~ /^OBJ_EVENT_GFX_VAR_/ || $g =~ /^\d+$/)) {
            my @alt = suggest_gfx($g);
            err("$tag uses $g, which is not in the Emerald object graphics table (FRLG-only sprite)"
                . (@alt ? '; Emerald candidates (check the sprite in Porymap): ' . join(' or ', @alt) : ''));
        }
        check_flag("$tag flag", $o->{flag});
        check_item_flag("$tag item ball", $o->{flag}) if !$src && $g eq 'OBJ_EVENT_GFX_ITEM_BALL';
        check_script("$tag script", $o->{script}, $src);
        if (($o->{trainer_type} // 'TRAINER_TYPE_NONE') ne 'TRAINER_TYPE_NONE') {
            warn_("$tag is a trainer; check its TRAINER_* party exists in the Emerald trainer data");
        }
    }
    my $warps = $j->{warp_events} || [];
    for my $i (0 .. $#$warps) {
        my $wp = $warps->[$i];
        my $tag = "warp $i ($wp->{x},$wp->{y})";
        check_bounds($tag, $wp, $w, $h);
        my $dest = $wp->{dest_map} // '';
        my $dm = $M{maps_by_id}{$dest};
        if ($batch_ids->{$dest}) {
            # resolved by the same port batch
        } elsif (!$dm) {
            ($src ? \&warn_ : \&err)->("$tag -> $dest: map is not in map_groups.json (warping there crashes or lands in garbage)");
        } elsif (!$dm->{emerald}) {
            ($src ? \&warn_ : \&err)->("$tag -> $dest: map exists only in the FRLG build");
        } else {
            my $dw = $dm->{json}{warp_events} || [];
            my $id = $wp->{dest_warp_id} // '';
            if ($id =~ /^\d+$/ ? $id >= @$dw : !grep { ($_->{warp_id} // '') eq $id } @$dw) {
                err("$tag -> $dest warp $id: destination only has " . scalar(@$dw) . " warps");
            }
        }
        if (@$blocks && $wp->{x} < $w && $wp->{y} < $h) {
            my $v = $blocks->[ $wp->{y} * $w + $wp->{x} ];
            ($v) = remap_block($v) if $is_frlg_layout;
            my $mid = $v & 0x3FF;
            my $b = mb_name(behavior_of($mid, $prim, $sec, $NUM_PRIMARY_EM));
            # TryMapEdgeWarp (src/field_control_avatar.c) fires any warp on the outermost row/column
            # when the player presses toward that edge, so edge warps need no special behavior.
            my $on_edge = $wp->{x} == 0 || $wp->{y} == 0 || $wp->{x} == $w - 1 || $wp->{y} == $h - 1;
            warn_("$tag stands on $b: the player can arrive here but cannot walk into it (needs a door/arrow/stair behavior, or put it on the map's outer edge for an edge warp)")
                unless mb_class($b) eq 'warp' || $on_edge;
            if ($b eq 'MB_NON_ANIMATED_DOOR' && ($j->{map_type} // '') !~ /INDOOR/) {
                warn_(sprintf('%s is an outdoor door on MB_NON_ANIMATED_DOOR (metatile 0x%03X): it warps without opening; use MB_ANIMATED_DOOR plus a door entry for an Emerald door animation',
                    $tag, $mid));
            }
            if ($b eq 'MB_ANIMATED_DOOR' && !door_anim_for($mid, $l)) {
                warn_(sprintf('%s is an animated door (metatile 0x%03X) with no Emerald door animation for %s/%s; it opens without animating (references/rules.md "Doors")',
                    $tag, $mid, $l->{primary_tileset}, $l->{secondary_tileset}));
            }
        }
    }
    for my $c (@{ $j->{coord_events} || [] }) {
        my $tag = "coord event ($c->{x},$c->{y})";
        check_bounds($tag, $c, $w, $h);
        check_var("$tag var", $c->{var}) if ($c->{type} // '') eq 'trigger';
        check_script("$tag script", $c->{script}, $src) if ($c->{type} // '') eq 'trigger';
    }
    for my $b (@{ $j->{bg_events} || [] }) {
        my $tag = "bg $b->{type} ($b->{x},$b->{y})";
        check_bounds($tag, $b, $w, $h);
        check_script("$tag script", $b->{script}, $src) if $b->{type} eq 'sign';
        if ($b->{type} eq 'hidden_item') {
            check_flag("$tag flag", $b->{flag});
            check_item_flag($tag, $b->{flag}) unless $src;
        }
    }
    for my $c (@{ ref $j->{connections} eq 'ARRAY' ? $j->{connections} : [] }) {
        my $dm = $M{maps_by_id}{ $c->{map} };
        next if $batch_ids->{ $c->{map} };
        if (!$dm || !$dm->{emerald}) {
            ($src ? \&warn_ : \&err)->("connection $c->{direction} -> $c->{map} is not an Emerald map; mapjson drops it from the list but still counts it");
            next;
        }
        my %opp = (up => 'down', down => 'up', left => 'right', right => 'left', dive => 'emerge', emerge => 'dive');
        my $back = grep { ($_->{map} // '') eq $j->{id} && $_->{direction} eq $opp{ $c->{direction} } }
            @{ ref $dm->{json}{connections} eq 'ARRAY' ? $dm->{json}{connections} : [] };
        warn_("connection $c->{direction} -> $c->{map} has no matching $opp{$c->{direction}} connection back") unless $back;
    }
    return \%own_lids;
}

sub suggest_gfx {
    my ($g) = @_;
    (my $base = $g) =~ s/_FRLG$//;
    my %alias = (FISHER => 'FISHERMAN', WORKER_M => 'MAN_4', COOLTRAINER_F => 'WOMAN_5', COOLTRAINER_M => 'MAN_5',
                 BALDING_MAN => 'OLD_MAN', ROCKER => 'GUITARIST', SCIENTIST => 'SCIENTIST_1', MAN => 'MAN_1',
                 WOMAN_1 => 'WOMAN_1', BEAUTY => 'BEAUTY', OLD_MAN_1 => 'OLD_MAN');
    my ($short) = $base =~ /^OBJ_EVENT_GFX_(\w+)$/;
    my @c = ($base, "${base}_1", $short && $alias{$short} ? "OBJ_EVENT_GFX_$alias{$short}" : ());
    my %seen;
    return grep { $_ ne $g && $M{gfx}{$_} && !$seen{$_}++ } @c;
}

sub map_script_refs {
    my ($j) = @_;
    my @r;
    for my $list (qw(object_events coord_events bg_events)) {
        for my $e (@{ $j->{$list} || [] }) {
            push @r, $e->{script} if defined $e->{script} && $e->{script} !~ /^(NULL|0x0|0)$/;
        }
    }
    my %seen;
    return grep { !$seen{$_}++ } @r;
}

# Locate a label in the shared script/text files regardless of build version.
# Returns [file, text from the label to the next global label].
sub find_label_block {
    my ($label) = @_;
    $M{label_files} //= [ glob('data/scripts/*.inc'), glob('data/text/*.inc') ];
    for my $f (@{ $M{label_files} }) {
        my $t = $M{file_cache}{$f} //= read_text($f);
        next unless $t =~ /^\Q$label\E::?[ \t]*$/m;
        my $start = $-[0];
        my $rest = substr($t, $start);
        my $end = $rest =~ /\n(?=[A-Za-z_]\w*::?[ \t]*$)/mg ? pos($rest) : length $rest;
        return [$f, substr($rest, 0, $end)];
    }
    return undef;
}

sub check_bounds {
    my ($tag, $e, $w, $h) = @_;
    return unless defined $e->{x} && defined $e->{y};
    err("$tag at ($e->{x},$e->{y}) is outside the ${w}x$h layout")
        if $e->{x} < 0 || $e->{y} < 0 || $e->{x} >= $w || $e->{y} >= $h;
}

sub check_flag {
    my ($tag, $flag) = @_;
    return if !defined $flag || $flag eq '0' || $flag eq '';
    my $v = $M{flags}{$flag};
    if (!defined $v) { err("$tag $flag is not defined for Emerald"); return }
    warn_("$tag $flag is an FRLG name (0 in Emerald, does nothing); give it a new storyline flag in include/constants/flags.h")
        if $v =~ /^\s*0\s*$/;
}

# Item balls and hidden items need a real flag or they come back every time.
sub check_item_flag {
    my ($tag, $flag) = @_;
    warn_("$tag has no flag, so the item respawns; give it a new FLAG_ITEM_* / FLAG_HIDDEN_ITEM_* flag")
        if !defined $flag || $flag eq '0' || $flag eq '';
}

sub check_var {
    my ($tag, $var) = @_;
    return if !defined $var || $var eq '0';
    if (!defined $M{vars}{$var}) { err("$tag $var is not defined"); return }
    if ($M{frlg_var}{$var}) {
        my $val = const_value($M{vars}, $var);
        my @clash = defined $val ? grep { !$M{frlg_var}{$_} && (const_value($M{vars}, $_) // -1) == $val } keys %{ $M{vars} } : ();
        warn_("$tag $var comes from vars_frlg.h" . (@clash ? sprintf(' and shares 0x%X with Emerald %s', $val, join('/', sort @clash)) : '')
              . '; use a dedicated Emerald var');
    }
}

sub check_script {
    my ($tag, $s, $src) = @_;
    return if !defined $s || $s =~ /^(NULL|0x0|0)$/;
    return if $M{labels}{$s} || ($M{batch_labels} || {})->{$s};
    ($src ? \&warn_ : \&err)->("$tag $s is not defined in any file the Emerald build assembles"
        . ($src ? ' (FRLG-only; port copies it if it lives in this map\'s scripts.inc)' : ''));
}

# ---------------------------------------------------------------- restore-behaviors

# Puts back metatile behaviors that the in-place FRLG->Emerald tileset conversion zeroed
# (tall grass, water, ledges, arrow warps...). Only touches metatiles whose graphics are
# unchanged and whose current behavior is MB_NORMAL, so deliberate edits survive.
sub cmd_restore_behaviors {
    my @args = @_;
    my ($orig_ref, $write, $classes) = ($ORIG_REF_DEFAULT, 0, 'grass,water,ledge,warp');
    GetOptionsFromArray(\@args, 'orig-ref=s' => \$orig_ref, 'write' => \$write, 'classes=s' => \$classes) or return 2;
    die "restore-behaviors needs one or more tileset symbols (e.g. gTileset_General_Frlg)\n" unless @args;
    model();
    my %want = map { $_ => 1 } split /,/, $classes;

    # Cells per (tileset, index) across the Emerald ARHU maps, so the impact is visible.
    my %usage;
    for my $mi (values %{ $M{maps_by_name} }) {
        next unless $mi->{name} =~ /ARHU/ && $mi->{emerald};
        my $l = $M{layouts}{ $mi->{json}{layout} } or next;
        next unless -f ($l->{blockdata_filepath} // '');
        for my $v (@{ read_blocks($l->{blockdata_filepath}) }) {
            my $id = $v & 0x3FF;
            next if $id == 0x3FF;
            my ($sym, $idx) = $id < $NUM_PRIMARY_EM ? ($l->{primary_tileset}, $id) : ($l->{secondary_tileset}, $id - $NUM_PRIMARY_EM);
            $usage{$sym}{$idx}{ $mi->{name} }++;
        }
    }

    my $total = 0;
    for my $sym (@args) {
        my $ts = $M{ts}{$sym} or do { err("unknown tileset $sym"); next };
        my $diff = orig_tileset_diff($sym, $orig_ref) or do { err("$sym: no Emerald-format data or no original at $orig_ref"); next };
        my @fix;
        for my $d (@$diff) {
            next if $d->{gfx} || $d->{cb} != 0 || $d->{ob} == 0;
            next if $d->{ob} > 0xFF;
            my $cls = mb_class(mb_name($d->{ob}));
            next unless $want{all} || $want{$cls};
            push @fix, $d;
        }
        say_("== $sym ($ts->{attr_path}): " . scalar(@fix) . ' metatile(s) to restore');
        for my $d (@fix) {
            my $u = $usage{$sym}{ $d->{i} } || {};
            my $where = %$u ? join(', ', map { "$_ x$u->{$_}" } sort keys %$u) : 'not used by ARHU maps yet';
            info(sprintf('#%-4d %s -> %s  (%s)', $d->{i}, mb_name($d->{cb}), mb_name($d->{ob}), $where));
        }
        next unless @fix && $write;
        my @attrs = unpack 'v*', read_text($ts->{attr_path});
        $attrs[ $_->{i} ] = ($attrs[ $_->{i} ] & ~0xFF & 0xFFFF) | $_->{ob} for @fix;
        write_text($ts->{attr_path}, pack 'v*', @attrs);
        $total += @fix;
    }
    say_($write ? "\nrestored $total behavior(s). Rebuild and walk the affected maps in the emulator."
                : "\ndry run: add --write to apply. These tilesets are shared, so every map listed above changes too.");
    return $ERRORS ? 1 : 0;
}

# ---------------------------------------------------------------- roadmap

# The design source is the city as it was laid out in the original binary hack
# (data/maps/FervorFieldCity_ARHU/FervorFieldCity_ARHU/map.json). It is not built; its
# warps name every building the city should get. This lists each one, the FRLG map it
# points at today (the default port source) and whether a built ARHU map already exists.
sub cmd_roadmap {
    my @args = @_;
    model();
    my $design = shift(@args) // 'data/maps/FervorFieldCity_ARHU/FervorFieldCity_ARHU/map.json';
    die "no design source at $design\n" unless -f $design;
    my $dj = read_json($design);
    my $live = $M{maps_by_id}{ $dj->{id} };
    my @lw = $live ? @{ $live->{json}{warp_events} || [] } : ();
    say_("== roadmap for $dj->{id} from $design");
    say_("   live map: " . ($live ? $live->{name} : '(none)'));
    for my $w (@{ $dj->{warp_events} || [] }) {
        my ($lv) = grep { $_->{x} == $w->{x} && $_->{y} == $w->{y} } @lw;
        my $dest = $w->{dest_map};
        my $dm = $M{maps_by_id}{$dest};
        my $state;
        if ($dm && $dm->{emerald} && $dm->{name} =~ /ARHU/) {
            $state = "built: $dm->{name}";
        } else {
            $state = 'to build from ' . ($dm ? $dm->{name} : "$dest (no such map)");
        }
        my $wired = !$lv ? 'no warp on the live map yet'
                  : $lv->{dest_map} eq $dest ? 'live warp matches'
                  : "live warp -> $lv->{dest_map}";
        say_(sprintf('  (%2d,%2d) %-46s %s; %s', $w->{x}, $w->{y}, $dest, $state, $wired));
    }
    my %dn = map { $_->{graphics_id} => 1 } @{ $dj->{object_events} || [] };
    my %ln = map { $_->{graphics_id} => 1 } @{ $live ? $live->{json}{object_events} || [] : [] };
    my @missing = grep { !$ln{$_} } sort keys %dn;
    say_('  design NPC sprites not on the live map: ' . (@missing ? join(', ', @missing) : 'none'));
    return 0;
}

# ---------------------------------------------------------------- validate

sub cmd_validate {
    my @names = @_;
    model();
    @names = sort grep { /ARHU/ } keys %{ $M{maps_by_name} } unless @names;
    my @all_arhu = grep { /ARHU/ } glob 'data/maps/*/map.json';
    for my $p (@all_arhu) {
        (my $n = $p) =~ s{^data/maps/|/map\.json$}{}g;
        warn_("$n has a map.json but is not listed in map_groups.json (not built)") unless $M{maps_by_name}{$n};
    }
    for my $p (glob 'data/maps/*/*/map.json') {
        info("design source (not built, by design): $p; see `roadmap`") if $p =~ /ARHU/;
    }
    validate_map($_) for @names;
    say_("\nvalidate: $ERRORS error(s), $WARNINGS warning(s)");
    return $ERRORS ? 1 : 0;
}

sub validate_map {
    my ($name, $batch_ids) = @_;
    my $info = $M{maps_by_name}{$name};
    say_("\n== $name");
    if (!$info) { err("$name is not listed in data/maps/map_groups.json"); return }
    my $j = $info->{json};
    err("map has \"region\": $j->{region}; only REGION_HOENN (or no region) maps are built for Emerald") unless $info->{emerald};
    err("name field \"$j->{name}\" does not match folder $name") if ($j->{name} // '') ne $name;
    warn_("id $j->{id} differs from naming convention MAP_" . snake($name)) if $j->{id} ne 'MAP_' . snake($name);
    warn_("layout $j->{layout} differs from naming convention LAYOUT_" . snake($name)) if $j->{layout} ne 'LAYOUT_' . snake($name);

    my $l = $M{layouts}{ $j->{layout} };
    if (!$l) { err("layout $j->{layout} is not in data/layouts/layouts.json"); return }
    if (!$l->{_emerald}) { err("layout $l->{id} is not built for Emerald (layout_version frlg or missing border.bin)"); return }
    for my $k (qw(primary_tileset secondary_tileset)) {
        my $ts = $M{ts}{ $l->{$k} };
        if (!$ts)                      { err("$k $l->{$k} not found"); next }
        if (!$ts->{emerald})           { err("$k $l->{$k} is only compiled for FRLG (inside #if IS_FRLG in headers.h/metatiles.h)") }
        if (($ts->{format} // '') ne 'emerald') { err("$k $l->{$k} still has FRLG 32-bit metatile attributes") }
        if ($ts->{secondary} != ($k eq 'secondary_tileset' ? 1 : 0)) { err("$k $l->{$k} has isSecondary=" . ($ts->{secondary} ? 'TRUE' : 'FALSE')) }
    }
    my $bpath = $l->{blockdata_filepath};
    my $size = -s $bpath // 0;
    err("$bpath is $size bytes, expected " . ($l->{width} * $l->{height} * 2)) if $size != $l->{width} * $l->{height} * 2;
    my $bs = -s $l->{border_filepath} // 0;
    err("$l->{border_filepath} is $bs bytes; Emerald borders are 2x2 (8 bytes)") if $bs != 8;
    my $pc = $M{ts}{ $l->{primary_tileset} }{count} // 0;
    my $sc = $M{ts}{ $l->{secondary_tileset} }{count} // 0;
    my (%bad, %hist);
    my ($prim, $sec) = behaviors_for_layout($l);
    my $blocks = read_blocks($bpath);
    for my $i (0 .. $#$blocks) {
        my $id = $blocks->[$i] & 0x3FF;
        next if $id == 0x3FF;
        my $okid = $id < $NUM_PRIMARY_EM ? $id < $pc : $id - $NUM_PRIMARY_EM < $sc;
        if (!$okid) { $bad{$id}++; next }
        $hist{ mb_class(mb_name(behavior_of($id, $prim, $sec, $NUM_PRIMARY_EM))) }++;
    }
    err("metatile ids past the end of their tileset (render as garbage): "
        . join(' ', map { "${_}x$bad{$_}" } sort { $a <=> $b } keys %bad)) if %bad;
    info('behavior classes: ', join(', ', map { "$_=$hist{$_}" } sort keys %hist));

    my $own = audit_events($j, $l, 0, $batch_ids);
    my $objs = $j->{object_events} || [];
    for my $o (@$objs) {
        my $lid = $o->{local_id} or next;
        my %idx = map { $_->{idx} => 1 } @{ $M{event_ids}{$lid} || [] };
        warn_("$lid is generated with different values across maps (" . join(', ', map { "$_->{map}=$_->{idx}" } @{ $M{event_ids}{$lid} })
              . '); map_event_ids.h will redefine it') if keys %idx > 1;
    }

    my $enc = $M{encounters}{ $j->{id} } || [];
    my @em_enc = grep { $_->{emerald} } @$enc;
    if (!@em_enc && (($hist{grass} // 0) || ($hist{water} // 0)) && $j->{map_type} !~ /INDOOR/) {
        warn_("map has grass/water tiles but no Emerald wild encounter entry in src/data/wild_encounters.json");
    }
    info('wild encounters: ' . (@em_enc ? join(', ', map { $_->{label} } @em_enc) : 'none'));

    my $sfile = "data/maps/$name/scripts.inc";
    if (!-f $sfile) { err("$sfile is missing"); return }
    err("$sfile is not included by data/event_scripts.s outside .if IS_FRLG") unless $M{included}{$sfile};
    err("${name}_MapScripts label missing from $sfile") unless $M{labels}{"${name}_MapScripts"};
    validate_script_file($sfile, $own);
}

sub validate_script_file {
    my ($sfile, $own_lids) = @_;
    my $text = read_text($sfile);
    my (%defined_here);
    for my $line (split /\n/, $text) {
        $defined_here{$1} = 1 if $line =~ /^\s*([A-Za-z_]\w*)::?(?!\S)/;
    }
    for my $lab (sort keys %defined_here) {
        my @files = @{ $M{labels}{$lab} || [] };
        err("label $lab is defined more than once: " . join(', ', @files)) if @files > 1;
    }
    my (%seen);
    my $ln = 0;
    for my $line (split /\n/, $text) {
        $ln++;
        next if $line =~ /^\s*(\.string|@|$)/;
        $line =~ s/@.*$//;
        $line =~ s/^\s*[A-Za-z_]\w*::?//;
        my ($op) = $line =~ /^\s*(\w+)/;
        next unless defined $op;
        if (%{ $M{macros} || {} } && !$M{macros}{$op} && !$seen{"op:$op"}++) {
            err("$sfile:$ln '$op' is not a script/movement macro in the Emerald build (FRLG-only command?)");
        }
        for my $tok ($line =~ /\b([A-Za-z_]\w*)\b/g) {
            next if $seen{"$tok"}++;
            if ($tok =~ /^(?:FLAG_\w+)$/)      { check_flag("$sfile:$ln", $tok) }
            elsif ($tok =~ /^VAR_(?!TEMP_|0x|RESULT|FACING|LAST_TALKED|SPECIAL_)\w+$/) { check_var("$sfile:$ln", $tok) }
            elsif ($tok =~ /^LOCALID_\w+$/)    {
                err("$sfile:$ln $tok is not a local_id of this map") unless $own_lids->{$tok} || $M{generic_localids}{$tok};
            }
            elsif ($tok =~ /^OBJ_EVENT_GFX_\w+$/) {
                err("$sfile:$ln $tok is FRLG-only") unless $M{gfx}{$tok} || $tok =~ /^OBJ_EVENT_GFX_VAR_/;
            }
            elsif ($tok =~ /^MAP_(?!SCRIPT_|TYPE_|BATTLE_SCENE_|OFFSET|GROUP|NUM|UNDEFINED|DYNAMIC)\w+$/ && $op =~ /warp|setwarp|setdynamicwarp|setescapewarp|setholewarp|setrespawn/) {
                my $dm = $M{maps_by_id}{$tok};
                err("$sfile:$ln $op target $tok is not an Emerald map") unless $dm && $dm->{emerald};
            }
            elsif ($tok =~ /^[A-Z]\w*_(?:EventScript|Text|Movement)_\w+$|^(?:Common_(?:EventScript|Movement)|EventScript)_\w+$/) {
                err("$sfile:$ln $tok is not defined in any file the Emerald build assembles") unless $M{labels}{$tok};
            }
        }
        if ($op eq 'special' || $op eq 'specialvar') {
            my ($sp) = $line =~ /special(?:var)?\s+(?:\w+\s*,\s*)?(\w+)\s*$/;
            err("$sfile:$ln special $sp is not in data/specials.inc") if $sp && !$M{specials}{$sp};
        }
    }
}

# ---------------------------------------------------------------- port

sub cmd_port {
    my @args = @_;
    my ($group, $write, $no_scripts, $enc_mode, $promote, $orig_ref, $keep_sprites, @retarget, @substitute)
        = (undef, 0, 0, 'auto', 0, $ORIG_REF_DEFAULT, 0);
    GetOptionsFromArray(\@args, 'group=s' => \$group, 'write' => \$write, 'keep-sprites' => \$keep_sprites,
        'no-scripts' => \$no_scripts, 'encounters=s' => \$enc_mode, 'retarget=s' => \@retarget,
        'substitute=s' => \@substitute, 'promote-overflow' => \$promote, 'orig-ref=s' => \$orig_ref) or return 2;
    die "port needs --group <gMapGroup_Name>\n" unless $group;
    die "port needs at least one Src=New pair\n" unless @args;
    die "--group must look like gMapGroup_Something\n" unless $group =~ /^gMapGroup_\w+$/;
    model();

    my (@pairs, %batch_ids, %id_map);
    for my $a (@args) {
        my ($src, $new) = $a =~ /^(\w+)=(\w+)$/ or die "bad pair '$a' (expected Src=New)\n";
        my $si = $M{maps_by_name}{$src} or die "source map $src not found in map_groups.json\n";
        my $new_id = 'MAP_' . snake($new);
        die "$new already exists (data/maps/$new)\n" if -e "data/maps/$new";
        die "$new_id already exists\n" if $M{maps_by_id}{$new_id};
        die "data/layouts/$new already exists\n" if -e "data/layouts/$new";
        die "LAYOUT_" . snake($new) . " already exists\n" if $M{layouts}{ 'LAYOUT_' . snake($new) };
        push @pairs, { src => $src, si => $si, new => $new, new_id => $new_id, new_layout => 'LAYOUT_' . snake($new) };
        $id_map{ $si->{id} } = $new_id;
        $batch_ids{$new_id} = 1;
    }
    # --retarget MAP_OLD=MAP_NEW: references to a map outside the batch (e.g. the FRLG
    # Fuchsia entrance) are pointed at an existing Emerald map instead.
    for my $r (@retarget) {
        my ($old, $new) = $r =~ /^(MAP_\w+)=(MAP_\w+)$/ or die "bad --retarget '$r' (expected MAP_OLD=MAP_NEW)\n";
        my $dm = $M{maps_by_id}{$new};
        die "--retarget target $new is not an Emerald map\n" unless ($dm && $dm->{emerald}) || $batch_ids{$new};
        $id_map{$old} = $new;
    }

    # Script label renames across the whole batch, so cross-references stay consistent.
    my %label_map;
    unless ($no_scripts) {
        for my $p (@pairs) {
            my $sfile = "data/maps/$p->{src}/scripts.inc";
            next unless -f $sfile;
            my $old_prefix = frlg_prefix($p->{src});
            for my $line (split /\n/, read_text($sfile)) {
                next unless $line =~ /^\s*([A-Za-z_]\w*)::?(?!\S)/;
                my $lab = $1;
                my $new_lab = $lab eq "$p->{src}_MapScripts" ? "$p->{new}_MapScripts"
                            : $lab =~ /^\Q$old_prefix\E_(.+)$/ ? "$p->{new}_$1"
                            : "$p->{new}_$lab";
                $label_map{$lab} = $new_lab;
            }
        }
    }
    # Scripts the map points at that live in FRLG-only shared files (item balls in
    # item_ball_scripts_frlg.inc, ...) are copied into the new map's scripts.inc.
    # FRLG item balls (`finditem ITEM_X` scripts) become Emerald item balls instead:
    # Common_EventScript_FindItem, item in trainer_sight_or_berry_tree_id, amount in movement_range_x.
    my %item_ball;
    for my $p (@pairs) {
        for my $o (@{ $p->{si}{json}{object_events} || [] }) {
            my $s = $o->{script} // '';
            next if $s =~ /^(NULL|0x0|0|)$/ || $item_ball{$s};
            my $blk = find_label_block($s);
            if (!$blk && -f "data/maps/$p->{src}/scripts.inc") {
                my $t = read_text("data/maps/$p->{src}/scripts.inc");
                $blk = ['', $1] if $t =~ /^(\Q$s\E::?[ \t]*\n(?:(?![A-Za-z_]\w*::?[ \t]*$).*\n?)*)/m;
            }
            next unless $blk && $blk->[1] =~ /^\Q$s\E::?\s*\n\s*finditem\s+(ITEM_\w+)(?:\s*,\s*(\d+))?\s*\n\s*end\b/;
            $item_ball{$s} = [$1, $2 // 1];
        }
    }
    my %extra_blocks;
    unless ($no_scripts) {
        for my $p (@pairs) {
            my $old_prefix = frlg_prefix($p->{src});
            for my $ref (map_script_refs($p->{si}{json})) {
                next if $label_map{$ref} || $M{labels}{$ref} || $item_ball{$ref};
                my $blk = find_label_block($ref) or next;
                $label_map{$ref} = $ref =~ /^\Q$old_prefix\E_(.+)$/ ? "$p->{new}_$1" : "$p->{new}_$ref";
                push @{ $extra_blocks{ $p->{new} } }, $blk;
            }
        }
    }
    $M{batch_labels} = { map { $_ => 1 } values %label_map };

    my $rename = sub {
        my ($text) = @_;
        my %all = (%label_map, %id_map);
        return $text unless %all;
        my $re = join '|', map { quotemeta } sort { length $b <=> length $a } keys %all;
        $text =~ s/\b($re)\b/$all{$1}/g;
        return $text;
    };

    my %files;   # path => new content (registry files and new files)
    my $layouts_text = read_text('data/layouts/layouts.json');
    my $groups_text  = read_text('data/maps/map_groups.json');
    my $es_text      = read_text('data/event_scripts.s');
    my $enc_text     = read_text('src/data/wild_encounters.json');
    my $enc_changed  = 0;
    my $fatal = 0;

    # FRLG primary metatiles 512-639 have no Emerald id. --substitute FRLG=EM picks a
    # replacement by hand; --promote-overflow appends an exact copy (graphics + original
    # behavior) to the end of the secondary tileset, leaving every existing id unchanged.
    my %subst;
    for my $s (@substitute) {
        my ($from, $to) = $s =~ /^(\d+)=(\d+)$/ or die "bad --substitute '$s' (expected FRLGID=EMERALDID)\n";
        die "--substitute $s: source must be an FRLG primary id 512-639\n" unless $from >= 512 && $from < 640;
        $subst{$from} = $to;
    }
    my %promoted;   # secondary tileset => { frlg id => emerald id }
    if ($promote) {
        my %need;
        for my $p (@pairs) {
            my $l = $M{layouts}{ $p->{si}{json}{layout} } or next;
            next unless ($l->{layout_version} // '') eq 'frlg';
            for my $v (@{ read_blocks($l->{blockdata_filepath}) }, unpack('v*', read_text($l->{border_filepath}))) {
                my $id = $v & 0x3FF;
                $need{ $l->{secondary_tileset} }{$id} = $l->{primary_tileset} if $id >= 512 && $id < 640 && !exists $subst{$id};
            }
        }
        for my $sec (sort keys %need) {
            my $ts = $M{ts}{$sec};
            my @mt = unpack 'v*', read_text($ts->{mt_path});
            my @at = unpack 'v*', read_text($ts->{attr_path});
            my $appended = 0;
            for my $id (sort { $a <=> $b } keys %{ $need{$sec} }) {
                my $pts = $M{ts}{ $need{$sec}{$id} };
                my $om = git_show_raw($orig_ref, $pts->{mt_path});
                my $oa = git_show_raw($orig_ref, $pts->{attr_path});
                if (!defined $om || !defined $oa || length($oa) * 4 != length($om)) {
                    err("cannot promote FRLG metatile $id: no FRLG-format original of $pts->{sym} at $orig_ref"); $fatal++; next;
                }
                my @raw = (unpack 'v*', $om)[ $id * 8 .. $id * 8 + 7 ];
                warn_("promoted metatile $id uses FRLG primary tiles 512-639; they resolve to the relocated copies in the secondary sheet, check it in Porymap")
                    if grep { ($_ & 0x3FF) >= 512 && ($_ & 0x3FF) < 640 } @raw;
                my @t = map { norm_frlg_tile($_) } @raw;
                my $a32 = (unpack 'V*', $oa)[$id];
                my $a16 = ($a32 & 0xFF) | ((($a32 >> 29) & 3) << 12);
                my $found;
                for my $i (0 .. int(@mt / 8) - 1) {
                    if (join(',', @mt[ $i * 8 .. $i * 8 + 7 ]) eq join(',', @t) && ($at[$i] // -1) == $a16) { $found = $i; last }
                }
                if (!defined $found) {
                    $found = int(@mt / 8);
                    if ($found >= $NUM_TOTAL - $NUM_PRIMARY_EM) { err("$sec is full; cannot promote metatile $id"); $fatal++; next }
                    push @mt, @t;
                    push @at, $a16;
                    $appended++;
                }
                $promoted{$sec}{$id} = $NUM_PRIMARY_EM + $found;
                info("FRLG primary metatile $id -> $sec #$found (Emerald id " . ($NUM_PRIMARY_EM + $found) . ', '
                     . mb_name($a16 & 0xFF) . ($appended && $found == int(@mt / 8) - 1 ? ', appended' : ', existing copy') . ')');
            }
            if ($appended) {
                $files{ $ts->{mt_path} }   = pack 'v*', @mt;
                $files{ $ts->{attr_path} } = pack 'v*', @at;
            }
        }
    }

    for my $p (@pairs) {
        my $j = $p->{si}{json};
        say_("\n== port $p->{src} ($j->{id}) -> $p->{new} ($p->{new_id})");
        my $l = $M{layouts}{ $j->{layout} } or die "layout $j->{layout} missing\n";
        my $is_frlg = ($l->{layout_version} // '') eq 'frlg';
        for my $k (qw(primary_tileset secondary_tileset)) {
            my $ts = $M{ts}{ $l->{$k} };
            if (!$ts || !$ts->{emerald} || ($ts->{format} // '') ne 'emerald') {
                err("$k $l->{$k} is not an Emerald-format tileset compiled for Emerald; convert it first (references/rules.md)");
                $fatal++;
            }
        }

        # block data
        my $prom = $promoted{ $l->{secondary_tileset} } || {};
        my $conv_block = sub {
            my ($v) = @_;
            return ($v, undef) unless $is_frlg;
            my $id = $v & 0x3FF;
            my $to = $subst{$id} // $prom->{$id};
            return (($v & 0xFC00) | $to, undef) if defined $to && $id >= 512 && $id < 640;
            return remap_block($v);
        };
        my @out;
        my %overflow;
        my $blocks = read_blocks($l->{blockdata_filepath});
        for my $i (0 .. $#$blocks) {
            my ($nv, $problem) = $conv_block->($blocks->[$i]);
            push @{ $overflow{ $blocks->[$i] & 0x3FF } }, [$i % $l->{width}, int($i / $l->{width})] if $problem;
            push @out, $nv;
        }
        for my $id (sort { $a <=> $b } keys %overflow) {
            my $cells = $overflow{$id};
            err(scalar(@$cells) . " cells use FRLG primary metatile $id (not addressable in Emerald), first at ($cells->[0][0],$cells->[0][1])");
            $fatal++;
        }
        info('fix with --promote-overflow (copies them into the secondary tileset) or --substitute ID=EMERALD_ID') if %overflow;
        my @border = unpack 'v*', read_text($l->{border_filepath});
        my $bw = $l->{border_width} // 2;
        my @b2 = map { ($conv_block->($_))[0] } @border[0, 1, $bw, $bw + 1];
        if ($bw != 2 || ($l->{border_height} // 2) != 2) {
            warn_("FRLG border was ${bw}x" . ($l->{border_height} // 2) . '; kept the top-left 2x2, check it in Porymap');
        }
        $files{"data/layouts/$p->{new}/map.bin"}    = pack 'v*', @out;
        $files{"data/layouts/$p->{new}/border.bin"} = pack 'v*', @b2;
        info(sprintf('layout %s %dx%d, %s + %s, block data %s', $p->{new_layout}, $l->{width}, $l->{height},
            $l->{primary_tileset}, $l->{secondary_tileset}, $is_frlg ? 'remapped (secondary ids -128)' : 'copied as-is'));

        my $entry = join "\n",
            '    {',
            qq(      "id": "$p->{new_layout}",),
            qq(      "name": "$p->{new}_Layout",),
            qq(      "width": $l->{width},),
            qq(      "height": $l->{height},),
            qq(      "primary_tileset": "$l->{primary_tileset}",),
            qq(      "secondary_tileset": "$l->{secondary_tileset}",),
            qq(      "border_filepath": "data/layouts/$p->{new}/border.bin",),
            qq(      "blockdata_filepath": "data/layouts/$p->{new}/map.bin",),
            qq(      "border_height": 2,),
            qq(      "border_width": 2),
            '    }';
        $layouts_text =~ s/(\})(\s*\]\s*\}\s*)\z/$1,\n$entry$2/ or die "could not find the end of the layouts array\n";

        # map.json
        my $nj = $JSON->decode($JSON->encode($j));
        $nj->{id} = $p->{new_id};
        $nj->{name} = $p->{new};
        $nj->{layout} = $p->{new_layout};
        delete $nj->{region};
        $nj->{connections} = undef if !ref $nj->{connections} || !@{ $nj->{connections} };
        my @needs_flag;
        my $is_stub = sub { my $f = shift; defined $f && $f ne '0' && ($M{flags}{$f} // '') =~ /^\s*0\s*$/ };
        for my $b (@{ $nj->{bg_events} || [] }) {
            next unless $b->{type} eq 'hidden_item' && $is_stub->($b->{flag});
            push @needs_flag, "hidden $b->{item} at ($b->{x},$b->{y}) (was $b->{flag})";
            $b->{flag} = '0';
        }
        for my $o (@{ $nj->{object_events} || [] }) {
            delete $o->{type} if ($o->{type} // '') eq 'object';
            if (my $ib = $item_ball{ $o->{script} // '' }) {
                $o->{script} = 'Common_EventScript_FindItem';
                $o->{trainer_sight_or_berry_tree_id} = $ib->[0];
                $o->{movement_range_x} = $ib->[1] + 0;
            }
            if ($is_stub->($o->{flag})) {
                push @needs_flag, ($o->{graphics_id} eq 'OBJ_EVENT_GFX_ITEM_BALL' ? "item ball $o->{trainer_sight_or_berry_tree_id}" : "object $o->{graphics_id}")
                                  . " at ($o->{x},$o->{y}) (was $o->{flag})";
                $o->{flag} = '0';
            }
            # An FRLG-only sprite compiles but has a NULL graphics pointer in Emerald (crash
            # when the object loads), so swap in the closest Emerald sprite unless told not to.
            my $g = $o->{graphics_id} // '';
            next if $keep_sprites || $M{gfx}{$g} || $g =~ /^OBJ_EVENT_GFX_VAR_|^\d+$/;
            my ($alt) = suggest_gfx($g) or next;
            info("sprite $g -> $alt" . ($o->{local_id} ? " ($o->{local_id})" : '') . '; restyle in Porymap if needed');
            $o->{graphics_id} = $alt;
        }
        my $nib = grep { $_->{script} eq 'Common_EventScript_FindItem' } @{ $nj->{object_events} || [] };
        info("$nib FRLG item ball(s) converted to Emerald item balls (Common_EventScript_FindItem)") if $nib;
        if (@needs_flag) {
            info('FRLG flags cleared to "0"; these need new storyline flags:');
            info("    $_") for @needs_flag;
        }
        my $json_text = $rename->(emit_map_json($nj));
        $files{"data/maps/$p->{new}/map.json"} = $json_text;

        # scripts.inc
        my $sfile = "data/maps/$p->{src}/scripts.inc";
        if (!$no_scripts && -f $sfile) {
            my $s = $rename->(read_text($sfile));
            $s = "\@ Ported from $p->{src} by arhu_maps.pl; labels renamed $p->{src}/" . frlg_prefix($p->{src}) . "_* -> $p->{new}_*\n" . $s;
            for my $blk (@{ $extra_blocks{ $p->{new} } || [] }) {
                $s =~ s/\s*\z/\n/;
                $s .= "\n\@ Copied from $blk->[0] (FRLG-only there)\n" . $rename->($blk->[1]);
            }
            $files{"data/maps/$p->{new}/scripts.inc"} = $s;
            info('scripts.inc copied with ' . scalar(grep { index($label_map{$_}, "$p->{new}_") == 0 } keys %label_map) . ' labels renamed'
                 . (@{ $extra_blocks{ $p->{new} } || [] } ? ', plus ' . scalar(@{ $extra_blocks{ $p->{new} } }) . ' block(s) from FRLG-only shared files' : ''));
        } else {
            $files{"data/maps/$p->{new}/scripts.inc"} = "$p->{new}_MapScripts::\n\t.byte 0\n";
            my $nn = 0;
            my $jj = $JSON->decode($json_text);
            for my $list (qw(object_events coord_events bg_events)) {
                for my $e (@{ $jj->{$list} || [] }) {
                    next unless defined $e->{script} && $e->{script} !~ /^(NULL|0x0|0)$/ && !$M{labels}{ $e->{script} };
                    $e->{script} = 'NULL';
                    $nn++;
                }
            }
            $files{"data/maps/$p->{new}/map.json"} = emit_map_json($jj);
            info("empty scripts.inc created; $nn unresolved script references set to NULL");
        }

        # map_groups.json
        if ($groups_text =~ /"\Q$group\E"\s*:\s*\[/) {
            $groups_text =~ s/("\Q$group\E"\s*:\s*\[)(.*?)(\n\s*\])/
                my ($h, $body, $t) = ($1, $2, $3);
                $body =~ m{\S} ? "$h$body,\n    \"$p->{new}\"$t" : "$h\n    \"$p->{new}\"$t"/se
                or die "could not extend $group\n";
        } else {
            $groups_text =~ s/("group_order"\s*:\s*\[)(.*?)(\n\s*\])/$1$2,\n    "$group"$3/s
                or die "could not extend group_order\n";
            $groups_text =~ s/(\])(\s*\}\s*)\z/$1,\n  "$group": [\n    "$p->{new}"\n  ]$2/
                or die "could not append group $group\n";
            info("new map group $group appended to group_order");
        }

        # event_scripts.s (appended after the last line, which is outside .if IS_FRLG)
        $es_text =~ s/\s*\z//;
        $es_text .= "\n\n        .include \"data/maps/$p->{new}/scripts.inc\"\n";

        # wild encounters
        my $want = $enc_mode;
        my @src_enc = @{ $M{encounters}{ $j->{id} } || [] };
        if ($want eq 'auto') {
            $want = (grep { ($_->{label} // '') =~ /FireRed/ } @src_enc) ? 'FireRed'
                  : (grep { ($_->{label} // '') =~ /LeafGreen/ } @src_enc) ? 'LeafGreen'
                  : (grep { $_->{emerald} } @src_enc) ? 'emerald' : 'none';
        }
        if ($want ne 'none') {
            my ($e) = grep { $want eq 'emerald' ? $_->{emerald} : ($_->{label} // '') =~ /\Q$want\E/ } @src_enc;
            if (!$e) {
                warn_("no $want encounter table for $j->{id}");
            } else {
                my $new_label = 'g' . $p->{new};
                my $copy = extract_json_object($enc_text, $e->{label});
                if (!$copy) { warn_("could not locate encounter block $e->{label}") }
                else {
                    my ($start, $end, $obj) = @$copy;
                    $obj =~ s/"map"\s*:\s*"\Q$j->{id}\E"/"map": "$p->{new_id}"/;
                    $obj =~ s/"base_label"\s*:\s*"\Q$e->{label}\E"/"base_label": "$new_label"/;
                    my ($indent) = substr($enc_text, 0, $start) =~ /([ \t]*)\z/;
                    substr($enc_text, $end, 0) = ",\n$indent$obj";
                    $enc_changed = 1;
                    info("wild encounters copied from $e->{label} as $new_label");
                }
            }
        }

        say_('  checks on the converted map:');
        my $conv = { %$l, id => $p->{new_layout}, layout_version => undef, border_width => 2, border_height => 2 };
        local $M{ts_override} = { map { $_ => $files{ $M{ts}{$_}{attr_path} } } grep { $files{ $M{ts}{$_}{attr_path} // '' } } keys %promoted };
        audit_events($JSON->decode($files{"data/maps/$p->{new}/map.json"}), $conv, 0, \%batch_ids, \@out);
        my $sc = $files{"data/maps/$p->{new}/scripts.inc"};
        if ($sc =~ /\b(famechecker|setflyflag|textcolor|questlog|setquestlogflag)\b/) {
            warn_("scripts.inc uses '$1'; check that every macro the copy uses exists for Emerald (validate reports any that don't)");
        }
    }

    # Validate all edited JSON before touching disk.
    for my $pair (['data/layouts/layouts.json', $layouts_text], ['data/maps/map_groups.json', $groups_text],
                  ($enc_changed ? (['src/data/wild_encounters.json', $enc_text]) : ())) {
        eval { $JSON->decode($pair->[1]) };
        die "internal error: edited $pair->[0] is not valid JSON ($@); nothing written\n" if $@;
        $files{ $pair->[0] } = $pair->[1];
    }
    for my $p (grep { /map\.json$/ } keys %files) {
        eval { $JSON->decode($files{$p}) };
        die "internal error: generated $p is not valid JSON ($@); nothing written\n" if $@;
    }
    $files{'data/event_scripts.s'} = $es_text;

    say_("\nfiles " . ($write ? 'written' : 'that --write would create/modify') . ':');
    say_("  $_") for sort keys %files;
    if ($fatal) {
        say_("\nport blocked by $fatal fatal problem(s); nothing written.");
        return 1;
    }
    if (!$write) {
        say_("\ndry run: re-run with --write to apply. Commit or stash first so `git diff` shows exactly what changed.");
        return 0;
    }
    write_text($_, $files{$_}) for sort keys %files;
    say_("\nwritten. Next: perl " . __FILE__ . " validate " . join(' ', map { $_->{new} } @pairs));
    return 0;
}

# Find the JSON object that contains "base_label": "<label>"; returns [start, end, text].
sub extract_json_object {
    my ($text, $label) = @_;
    my $pos = index($text, qq("base_label": "$label"));
    return undef if $pos < 0;
    my $depth = 0;
    my $start;
    for (my $i = $pos; $i >= 0; $i--) {
        my $c = substr($text, $i, 1);
        if ($c eq '}') { $depth++ }
        elsif ($c eq '{') { if ($depth == 0) { $start = $i; last } $depth-- }
    }
    return undef unless defined $start;
    $depth = 0;
    for (my $i = $start; $i < length $text; $i++) {
        my $c = substr($text, $i, 1);
        $depth++ if $c eq '{';
        if ($c eq '}' && --$depth == 0) {
            return [$start, $i + 1, substr($text, $start, $i + 1 - $start)];
        }
    }
    return undef;
}

# ---------------------------------------------------------------- map.json writer

my @MAP_KEYS = qw(id name layout music region region_map_section requires_flash weather map_type
                  allow_cycling allow_escaping allow_running show_map_name battle_scene connections
                  object_events warp_events coord_events bg_events floor_number);
my %EVENT_KEYS = (
    object_events => [qw(type local_id graphics_id x y elevation movement_type movement_range_x movement_range_y
                         trainer_type trainer_sight_or_berry_tree_id script flag target_local_id target_map)],
    warp_events   => [qw(warp_id x y elevation dest_map dest_warp_id)],
    coord_events  => [qw(type x y elevation var var_value script weather)],
    bg_events     => [qw(type x y elevation player_facing_dir script item flag quantity underfoot secret_base_id)],
    connections   => [qw(map offset direction)],
);

sub emit_map_json {
    my ($j) = @_;
    my @keys = ((grep { exists $j->{$_} } @MAP_KEYS), (sort grep { my $k = $_; !grep { $_ eq $k } @MAP_KEYS } keys %$j));
    my @lines;
    for my $k (@keys) {
        push @lines, '  ' . $JSON->encode($k) . ': ' . emit_value($j->{$k}, 1, $EVENT_KEYS{$k});
    }
    return "{\n" . join(",\n", @lines) . "\n}\n";
}

sub emit_value {
    my ($v, $depth, $order) = @_;
    my $pad = '  ' x $depth;
    if (ref $v eq 'ARRAY') {
        return '[]' unless @$v;
        return "[\n" . join(",\n", map { "$pad  " . emit_value($_, $depth + 1, $order) } @$v) . "\n$pad]";
    }
    if (ref $v eq 'HASH') {
        my @o = $order ? @$order : ();
        my @keys = ((grep { exists $v->{$_} } @o), (sort grep { my $k = $_; !grep { $_ eq $k } @o } keys %$v));
        return "{\n" . join(",\n", map { "$pad  " . $JSON->encode($_) . ': ' . emit_value($v->{$_}, $depth + 1) } @keys) . "\n$pad}";
    }
    return $JSON->encode($v);
}

# ---------------------------------------------------------------- main

chdir_to_repo();
my $cmd = shift @ARGV // 'help';
my %dispatch = (audit => \&cmd_audit, port => \&cmd_port, validate => \&cmd_validate,
                'restore-behaviors' => \&cmd_restore_behaviors, roadmap => \&cmd_roadmap);
if (!$dispatch{$cmd}) {
    print usage();
    exit($cmd eq 'help' ? 0 : 2);
}
exit($dispatch{$cmd}->(@ARGV) // 0);
