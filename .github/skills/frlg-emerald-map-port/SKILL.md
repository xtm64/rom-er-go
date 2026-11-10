---
name: frlg-emerald-map-port
description: Build, port and validate Fervor Field maps for the Emerald build of this rom hack, using FireRed/LeafGreen (FRLG) maps as raw material the way FervorFieldCity_ARHU and its houses were made. Use when creating or editing any *_ARHU map, building the next Fervor building or area (Safari, Mart, Gym, Pokemon Center, houses), copying an FRLG map into the Emerald build, or fixing warps, door animations, tiles, encounters, items, flags or scripts on ARHU maps.
---

# Building Fervor Field maps (ARHU) for the Emerald build

This repo is pokeemerald-expansion with FRLG data on board. The game ships as Emerald
(`MAP_VERSION=emerald`). FRLG maps in `data/maps/*_Frlg` are left out of that build; ARHU maps are
converted copies that are part of it. `references/rules.md` explains why every step below exists.

## The design source: start here

`data/maps/FervorFieldCity_ARHU/FervorFieldCity_ARHU/` is **the user's Fervor Field City from their
original binary hack**. It is the starting town of the game and the plan for everything still to
come. The build deliberately leaves it out (it's nested one folder too deep). Never delete or
"clean up" this folder. Its warps name every building the city should have, and the FRLG map each one
points at is the default source for the Fervor version.

```
perl $T roadmap        # each planned building, its FRLG source, and whether it's built and wired
```

## House style: Emerald first

FRLG maps supply layouts and art. **Gameplay data is Emerald's:**
- **Flags/vars:** all new, for the new storyline. FRLG flag names are meaningless here (they're 0 in
  Emerald). `port` clears them to `"0"` and lists where new ones are needed. Claim
  `FLAG_UNUSED_0x...` / `VAR_UNUSED_0x...` slots with descriptive names and a comment, like
  `FLAG_HIDE_FERVOR_FIELD_CITY_*` and `VAR_FERVOR_FIELD_*`.
- **Items:** Emerald item balls: `Common_EventScript_FindItem`, the item in
  `trainer_sight_or_berry_tree_id`, the amount in `movement_range_x`, plus a new flag. Hidden items use
  `bg_events` `hidden_item` with a new flag. `port` converts FRLG `finditem` balls automatically.
- **Doors, tile behaviors, field effects:** use Emerald's door animation, sound and field-effect
  systems wherever possible, so moving between maps feels seamless. Fervor Field City: FRLG door art
  driven by the Emerald door system. Other maps may use Emerald door art; ask the user per area. See
  "Doors" in `references/rules.md`. `validate` warns about every door that would open without animating.
- **Dead code:** NPCs and scripts that nothing references can go (the user approved this for Fervor
  maps). Keep an NPC that does a job without a script, such as one blocking a path between triggers, and say why.
- **Sprites, scripts, encounters:** Emerald sprite table, Emerald script commands, and an Emerald
  `wild_encounters.json` entry (no `FireRed`/`LeafGreen` in the label).

## Tool

Run from the repo root with Git Bash `perl` (nothing else to install):

```
T=.github/skills/frlg-emerald-map-port/scripts/arhu_maps.pl
perl $T roadmap                                  # what the design source still needs
perl $T audit    <FrlgMap>                       # what a port of this map needs
perl $T port     Src=New [...] --group gMapGroup_X [--retarget MAP_A=MAP_B] [--promote-overflow] [--write]
perl $T validate [Map ...]                       # default: every *ARHU* map
perl $T restore-behaviors <gTileset_X> [...] [--write]
```

`port` and `restore-behaviors` are **dry runs unless `--write` is given**. `port` builds every file
in memory, re-parses each JSON file, and writes nothing if any fatal problem is found.

## Safety rules (always)

1. **Commit or stash first.** Do a dry run, show the user the plan, and only then run `--write`. Afterwards
   `git diff --stat` must show only the files the dry run listed.
2. **Never edit `data/maps/*_Frlg`, FRLG layouts, or the design source.** Work on `_ARHU` maps.
3. **Shared tilesets are shared.** `gTileset_General_Frlg`, `gTileset_FuchsiaCity`, `gTileset_BuildingFrlg`,
   `gTileset_SafariZoneBuilding` and `gTileset_GenericBuilding1` were converted in place, and
   Fervor uses them. Any change to them (`restore-behaviors --write`, `--promote-overflow`, door
   entries, Porymap edits) changes Fervor too. The tool lists the affected maps. Get the user's yes first.
4. **Keep new IDs to the naming convention.** The folder is `Name_ARHU`, the id is `MAP_` + SNAKE(name), the layout is `LAYOUT_` + SNAKE(name), and
   labels start with `Name_`. Fervor buildings use a `FervorField...` prefix
   (`FervorField_PlayersHouse_1F_ARHU`, `FervorFieldCity_SafariZone_Entrance_ARHU_1`). Confirm names
   with the user when they ask for a new area.
5. **Only build what the user asked for.** The roadmap lists candidates; the user decides what comes
   next and what features it has.
6. **`validate` must show 0 errors before a build.** The user builds (`make` in their toolchain; this
   Windows shell has no `make`) and tests in mGBA/Porymap. Never claim a build passed unless you saw it.

## Workflow: a new Fervor building or area

1. `perl $T roadmap` and confirm with the user which entry, which FRLG source, the names, and the
   features they want.
2. `perl $T audit <FrlgMap>` for each source map:
   - **tilesets** must say `attribute format emerald, compiled for Emerald: yes`. Otherwise see
     "Converting a new tileset" in rules.md and stop to ask.
   - **primary metatiles 512-639**: use `--promote-overflow` or `--substitute FRLGID=EMERALDID`.
   - **behaviors that differ from the original** (grass/water/ledges/doors zeroed by the conversion): `restore-behaviors` (rule 3).
   - **repainted metatiles**: slots now showing Fervor edits. Tell the user.
3. Port every map that warps to the others **in one `port` call**. Use `--retarget` to send exits
   outside the batch to the Fervor map they belong to.
4. Dry run, show the plan, `--write`, then wire the live city's warp (roadmap shows
   `no warp on the live map yet` until you do).
5. `perl $T validate <maps>`, then do the Emerald-first follow-ups: new flags for every listed item and
   object, door animations, and scripts for the requested features.
6. The user builds and checks in game.

## Working through validate results

| Message | Fix |
|---|---|
| `map exists only in the FRLG build` / `not in map_groups.json` | Point the warp at an ARHU map (map.json `dest_map`, or `warp`/`setwarp` in scripts). |
| `destination only has N warps` | `dest_warp_id` is the index into the destination's `warp_events`. |
| `animated door ... no Emerald door animation` | Add a door entry (rules.md "Doors"). |
| `stands on MB_NORMAL` | The player can arrive on this tile but not leave through it. Expected for the outer tile of FRLG 3-wide exits; otherwise restore the behavior or paint a door/arrow tile. |
| `FRLG name (0 in Emerald)` / `has no flag, so the item respawns` | Claim a new storyline flag in `include/constants/flags.h`. |
| `comes from vars_frlg.h` | Claim a new var in `include/constants/vars.h`. |
| `FRLG-only sprite` | `port` swaps in an Emerald candidate when one exists; otherwise choose a sprite in Porymap. |
| `not defined in any file the Emerald build assembles` | Write or copy the script into this map's `scripts.inc` under a `Name_` label. |
| `not a script/movement macro in the Emerald build` | FRLG-only command; rewrite it with Emerald commands. |
| `defined more than once` | Rename the duplicate label; the assembler will reject it. |
| `past the end of their tileset` | The metatile id doesn't exist in the tileset (wrong tileset pair or a stale `map.bin`). |
| `grass/water tiles but no Emerald wild encounter entry` | Add an entry to `src/data/wild_encounters.json`. |

## References

- `references/rules.md`: how the build picks maps, layouts, tilesets, scripts, flags, sprites
  and doors for Emerald, and the tile/ID conversion math.
- `references/safari-zone-playbook.md`: the plan for Fervor's Safari behind the entrance building
  (run it when the user asks; they will supply the features).
- `references/fervor-field-example.md`: what each Fervor file was made from and the open issues.
