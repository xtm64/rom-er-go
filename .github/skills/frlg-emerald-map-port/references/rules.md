# How the Emerald build treats FRLG data

Every rule here was checked against the code in this repo (`tools/mapjson/mapjson.cpp`,
`map_data_rules.mk`, `src/fieldmap.c`, `src/data/tilesets/*.h`, `data/event_scripts.s`,
`include/constants/*.h`). If any of those change, re-check this file.

## Which maps get built

- `mapjson groups emerald` includes a map only if its `map.json` has **no `region`** or
  `"region": "REGION_HOENN"`. Every `_Frlg` map has `"region": "REGION_KANTO"`, so it is left out of
  `groups.inc`/`headers.inc`/`events.inc`.
- `include/constants/map_groups.h` still numbers **every** map in `map_groups.json`. Excluded maps
  also get `#define`s from `tools/mapjson/required_map_defines.json`. So `MAP_SAFARI_ZONE_CENTER`
  **compiles** in Emerald, but no map header exists for it, and warping there sends the player into garbage or a crash.
  `validate` reports these as errors.
- The build only looks one level deep, at `data/maps/*/map.json`. That is why the user's design source,
  `data/maps/FervorFieldCity_ARHU/FervorFieldCity_ARHU/` (the city from their binary hack, still
  marked `REGION_KANTO` and pointing at FRLG buildings), is safe where it is: it's reference data
  and is never built. Keep it.
- `map_event_ids.h` is generated from **all** `map.json` files, FRLG ones included. A `local_id` or
  `warp_id` name used in two maps at different positions gets redefined. `validate` warns.
- When a connection target isn't built, mapjson leaves it out of the list but still counts it
  in `.4byte <count>`, so the count is wrong. Only connect to built maps.

## Layouts

- `layouts.json` entries with `"layout_version": "frlg"` become `NULL` in the Emerald layout table.
  ARHU layouts leave `layout_version` out (so it defaults to emerald) and set `border_width`/`border_height` to 2.
- An Emerald layout has `isFrlg = FALSE`, and the engine then assumes:
  - a primary tileset of **512** metatiles / 512 tiles / 6 palettes (FRLG: 640 / 640 / 7);
  - **u16** metatile attributes: behavior in bits 0-7, layer type in bits 12-15. FRLG uses u32:
    behavior in bits 0-8, terrain in 9-13, encounter type in 24-26, layer in 29-30;
  - a **2x2 border**, always. An FRLG 3x2 border is cut to its top-left 2x2.
- Block data (`map.bin`) entries are u16: metatile id in bits 0-9, collision in 10-11, elevation in 12-15.

### Connections between maps on different tilesets

- Vanilla `LoadMapFromCameraTransition` (`src/overworld.c`) only reloaded the **secondary** tileset when
  walking across a connection. It now also reloads the primary tiles/palettes/animations when the
  primary tileset differs (added for `Route1_ARHU` (General_Frlg) <-> `Route1_CyclingRoad_ARHU` (General)).
  Before that, the Cycling Road drew with Route 1's FRLG primary art.
- The GBA holds one tileset pair in VRAM, so the strip of the **neighbouring** map that is on screen near
  the seam is always drawn with the current map's tilesets. Seams between maps that share the primary
  tileset look right (Game Freak keeps seam rows to primary tiles). Seams between an FRLG-primary map and
  an Emerald-primary map show a garbage strip. So **don't connect FRLG-primary maps to Emerald-primary
  maps; use an edge warp** (below), or repaint one side on the other's tilesets.
- **Edge warps** (`TryMapEdgeWarp`, `src/field_control_avatar.c`): a warp event on the outermost
  row/column fires with a fade when the player presses toward that edge, on any tile behavior. Bike and
  facing carry over. Pair each edge tile with the matching edge tile on the other map (each warp's
  `dest_warp_id` points at its partner). A real connection on the same side wins (no warp fires). No
  padding corridor is needed: the fade hides the tileset change.
- Edge-warped pairs (2026-11-04): Route1 <-> Route1_CyclingRoad (Route1 bottom (24-27,15) / road top
  (16-19,0)), Route1_CyclingRoad <-> EarnestStateCampus, Route1 <-> Route2_North, Route2_North <->
  Willowsville, Willowsville <-> WillowWoods, WillowWoods <-> WillowRanch, WillowRanch <-> WillowLake.
  Still real connections: Fervor <-> Route1/Route2, Route1_CyclingRoad <-> Earnest_Township,
  Earnest_Township <-> Route3/Route4.
- To convert another connection: for each tile on the shared edge that is open (collision 0) on both
  sides, add a warp on each map pointing at the partner, then delete the connection from both maps.
  For left/right edges the partner row is `y - offset`; for up/down the partner column is `x - offset`.
- Warps on `MB_NORMAL` tiles anywhere else never fire (`IsWarpMetatileBehavior`). Use a connection,
  an edge warp, or an arrow-warp/door behavior.
- Elevation must match across the seam: 3 -> 5 is blocked. Put a row of elevation-0 tiles at the seam
  when the two sides differ (done on `Earnest_Township_ARHU` row 0).

### Converting FRLG block data to Emerald (what `port` does)

| FRLG metatile id | Emerald id | Why |
|---|---|---|
| 0-511 | same | primary, unchanged |
| 512-639 | **none** | FRLG primary overflow; Emerald can't reach it. Use `--promote-overflow` or `--substitute` |
| 640-1023 | id - 128 | secondary metatile N moves from 640+N to 512+N |
| 0x3FF | same | "undefined" marker |

Collision and elevation bits are kept as they are.

## Tilesets

- `src/data/tilesets/headers.h` and `metatiles.h` put most FRLG tilesets inside `#if IS_FRLG`, so
  they aren't compiled for Emerald. The ones Fervor uses were moved **outside** that block (the end of each
  file, "Used by custom ARHU maps"): `gTileset_General_Frlg`, `gTileset_FuchsiaCity`,
  `gTileset_BuildingFrlg`, `gTileset_GenericBuilding1`, `gTileset_SafariZoneBuilding`.
- Those five were **converted in place** to Emerald format, starting in commit `2edab6211b`. The last
  untouched version is `2edab6211b^`, the tool's default `--orig-ref`. The conversion:
  1. primary `metatiles.bin` cut from 640 to 512 metatiles (10240 -> 8192 bytes);
  2. `metatile_attributes.bin` repacked from u32 to u16 (`behavior | layer << 12`);
  3. in the metatile tile references, secondary tiles 640+ became 512+ (-128), and FRLG primary
     tiles 512-639 were appended to the secondary tile sheets at index 192 (+192);
  4. palette numbers left as they were.
- **Side effects found while checking** (`audit` and `restore-behaviors` report them):
  - About 122 primary and 19 Fuchsia metatiles lost their behavior and became `MB_NORMAL`. This
    includes FRLG tall grass #10-13, most water, ledges and arrow warps. Without fixing this the
    Safari has **no grass encounters and no surfing**. `restore-behaviors` puts the original
    value back only where the graphics are unchanged and the current value is `MB_NORMAL`, so deliberate
    edits survive.
  - Some slots were repurposed for Fervor. For example, Fuchsia #126 (Emerald id 638) is now
    `MB_ANIMATED_DOOR`, and 73 primary / 4 Fuchsia metatiles were repainted. FRLG maps that use
    those slots inherit the edit. `audit` lists them.
- Behavior **numbers** are the same in both versions (one `metatile_behaviors.h` enum), so a
  restored value means the same thing in Emerald.

### Converting a new tileset (not done yet for others, e.g. `gTileset_PalletTown`)

Do this only with the user's go-ahead. Expect a Porymap session afterwards.

1. Move its `const struct Tileset` and its `INCBIN`s outside `#if IS_FRLG` (next to the five above).
   For a primary tileset, drop everything past metatile 511.
2. Repack its attributes from u32 to u16 and remap tile references as in step 3 above. For primary tiles
   512-639 to show up, the paired secondary sheet must contain them at index 192 or later.
3. Run `audit` on a map that uses it and check that the behaviors match the original.
The FRLG build would then read this tileset in the wrong format. That's acceptable here because this hack ships Emerald.

## Scripts

- `data/event_scripts.s` includes FRLG map scripts inside `.if IS_FRLG` (lines ~603-1050). ARHU
  `scripts.inc` files are included **at the very end of the file**, outside that block. `port`
  appends there.
- `data/scripts/item_ball_scripts_frlg.inc`, `fame_checker_frlg.inc` and similar files are FRLG-only.
  `port` copies the blocks a map points at into its own `scripts.inc`.
- Each map needs a `<MapName>_MapScripts::` label (the generated header points at it).
- Labels must be unique across everything the build assembles. Fervor kept the original names for
  some copies (e.g. `PalletTown_PlayersHouse_1F_EventScript_Mom`). That works only because the FRLG
  original isn't assembled. `port` renames copies to `<NewMap>_...` to be safe.
- `data/scripts/safari_zone.inc` decides where the Safari exit sends the player:
  `#if IS_FRLG` -> Fuchsia entrance, `#else` -> `MAP_ROUTE121_SAFARI_ZONE_ENTRANCE`. A new Safari has to
  change the `#else` branch (see the playbook).
- `EnterSafariMode` / `ExitSafariMode` (`src/safari_zone.c`) work on any map: 30 balls, 500 steps
  in Emerald (600 in FRLG). Safari battles happen anywhere while `FLAG_SYS_SAFARI_MODE` is set.

## Doors (Emerald animation wherever possible)

How a door animates (`src/field_door.c`):
- `GetDoorGraphics` looks for an `sDoorAnimGraphicsTable` entry whose **metatile id** matches the
  door tile, **and** whose tileset is the layout's primary or secondary tileset.
- In the Emerald build, that table holds **only Emerald tilesets** (`#if !IS_FRLG`). The FRLG entries
  (`METATILE_GeneralFrlg_Door`, `METATILE_FuchsiaCity_Door`, ...) and their art (`sDoorAnimTiles_*Frlg`,
  `graphics/door_anims/*_frlg.png`, `fuchsia.png`, ...) are in the `#else`/`#if IS_FRLG` parts. So every
  door on an ARHU map that uses FRLG tiles opens **without animating**. Fervor's gate script already
  notes this ("no Emerald door animation registered").
- The draw path depends on `mapLayout->isFrlg`, which is FALSE for ARHU layouts. The Emerald path
  draws **two metatiles** (the door at `y` and the one above at `y-1`) from 16x96 art: 3 frames × 2
  metatiles, bottom layer only, Emerald frame timing. FRLG art is 16x48: 3 frames × 1 metatile.
- Table ids must be **Emerald-layout ids**: primary unchanged, secondary FRLG id − 128.

Doors in Fervor's tilesets (FRLG label value -> Emerald-layout id):

| Door | FRLG id | Emerald-layout id | FRLG art |
|---|---|---|---|
| `METATILE_GeneralFrlg_Door` (player's house, (17,29)) | 0x03D | 0x03D | `general_frlg.png` |
| `METATILE_GeneralFrlg_SlidingSingleDoor` | 0x062 | 0x062 | `sliding_single.png` |
| `METATILE_GeneralFrlg_SlidingDoubleDoor` | 0x15B | 0x15B | `sliding_double.png` |
| `METATILE_FuchsiaCity_Door` | 0x2BF | 0x23F | `fuchsia.png` |
| `METATILE_FuchsiaCity_SafariZoneDoor` (Fervor's Safari gate, (24,5)) | 0x2D2 | 0x252 | `safari_zone_frlg.png` |

Fervor's gate tile (Fuchsia #82) was `MB_NON_ANIMATED_DOOR`; it is now `MB_ANIMATED_DOOR` with a
door entry (only that one cell uses #82). Fuchsia #126 (Emerald-layout 0x27E) was retagged
`MB_ANIMATED_DOOR` during the Fervor work but has no door art; check whether that was intended.

**Decision (2026-10-29): Fervor Field City uses A. Other maps may use B; the user decides per area.**

How A is wired (already done for the city's two doors):
- `struct DoorGraphics` has a trailing `bool8 frlgStyle`. `IsFrlgStyleDoor(gfx)` (true for FRLG layouts
  or `frlgStyle` entries) picks the one-metatile drawing and the FRLG frame offsets.
- The Emerald half of `sDoorAnimGraphicsTable` has a "Fervor Field City" block. Each entry uses
  `ARHU_METATILE(<FRLG label>)` (which converts secondary ids, −128) and ends with `TRUE`:
  `{ARHU_METATILE(METATILE_FuchsiaCity_SafariZoneDoor), &gTileset_FuchsiaCity, DOOR_SOUND_SLIDING, 1, sDoorAnimTiles_SafariZoneFrlg, sDoorAnimPalettes_SafariZoneFrlg, TRUE}`.
- For another FRLG door: move its `sDoorAnimTiles_*`/`sDoorAnimPalettes_*` out of `#if IS_FRLG` (next to
  `GeneralFrlg`/`SafariZoneFrlg`), add an entry the same way, and make sure the tile has `MB_ANIMATED_DOOR`.
  If its palette number is 6, check it first: in an Emerald layout, slot 6 comes from the secondary tileset.
- An Emerald-art door (B) is a normal entry: Emerald art, no `TRUE`, two metatiles tall.

Ways to get Emerald door behavior (this changes shared code and tilesets):
- **A. FRLG door art, Emerald door system.** Move the needed FRLG door art and palettes out of
  `#if IS_FRLG`, add entries to the Emerald half of the table using the Emerald-layout ids above,
  and make `DrawCurrentDoorAnimFrame`/`DrawClosedDoorTiles`/`CopyDoorTilesToVram` use the
  one-metatile FRLG drawing for entries whose tileset is one of the five ARHU tilesets (a small helper
  instead of checking `isFrlg` directly). Doors then open with Emerald's task, sound and timing, and the
  art still matches the FRLG building around them. Smallest change.
- **B. Emerald door art.** Import an Emerald door (e.g. `METATILE_General_Door`, both metatiles plus its
  palette) into the FRLG secondary tileset, paint it on the building, and add an entry that points at
  the Emerald art (`sDoorAnimTiles_General`). It looks like Emerald, but needs a free palette slot and
  Porymap work per building.
- **C. Emerald tilesets.** Rebuild the map on Emerald tilesets. Everything (doors, tile animations,
  behaviors) is native, but every map has to be repainted.
- In every case the door tile needs `MB_ANIMATED_DOOR`. The conversion zeroed the Fuchsia door
  (0x23F); `restore-behaviors` puts it back.

Other animations: FRLG tile animations (`InitTilesetAnim_General_Frlg`: water, flowers) are compiled
for Emerald and already run. Field effects (grass rustle, water ripples, ledge hops, sand) are Emerald's
and play automatically once the tile behaviors are right.

## Items

- Emerald item ball: `OBJ_EVENT_GFX_ITEM_BALL`, script `Common_EventScript_FindItem`, item in
  `trainer_sight_or_berry_tree_id`, amount in `movement_range_x` (0 or 1 means 1; see
  `src/item_ball.c`), and a `FLAG_ITEM_*`-style flag that hides it once taken.
- Hidden item: `bg_events` `"type": "hidden_item"` with `item`, `flag`, `quantity`, `underfoot`.
- FRLG item balls point at per-item `finditem` scripts in `item_ball_scripts_frlg.inc` (FRLG-only).
  `port` turns them into Emerald item balls and lists where new flags are needed.

## Flags, vars, sprites, encounters

- **The storyline uses new flags and vars only.** FRLG names (`FLAG_HIDE_SAFARI_ZONE_*`,
  `FLAG_HIDDEN_ITEM_*_FUCHSIA_*`, `FLAG_BEAT_RIVAL_IN_OAKS_LAB`, ...) carry no meaning here.
- `include/constants/flags.h`: under `#if IS_FRLG` it includes `flags_frlg.h`. The `#else` (Emerald)
  branch defines every FRLG flag name as **0**, so the name compiles but setting the flag does nothing.
  There are 364 `FLAG_UNUSED_0x...` slots, starting at 0x027 (Fervor uses 0x20-0x26).
- `include/constants/vars.h` includes `vars_frlg.h` **unconditionally**. FRLG var numbers overlap
  Emerald vars (e.g. `VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE` = 0x406E). There are 20
  `VAR_UNUSED_0x...` slots. `VAR_SAFARI_ZONE_STATE` (0x40A4) is the Emerald Safari state var.
- `src/data/object_events/object_event_graphics_info_pointers.h`: sprites inside `#if IS_FRLG`
  (`OBJ_EVENT_GFX_*_FRLG`, `SCIENTIST`, `MAN`, `FISHER`, `ROCKER`, `WORKER_M`, ...) are missing from
  the Emerald table, so the object gets a NULL graphics pointer. `RED`, `LEAF`, `FAT_MAN`, ... are fine.
- `src/data/wild_encounters.json`: an entry whose `base_label` contains `FireRed` or `LeafGreen` is
  wrapped in `#ifdef FIRERED`/`LEAFGREEN`. Emerald entries need a plain label such as
  `gSafariZone_Center_ARHU`, which is what `port` uses.
- Region map sections such as `MAPSEC_FUCHSIA_CITY` and `MAPSEC_KANTO_SAFARI_ZONE` exist in Emerald.
- Heal locations: `src/data/heal_locations.json` (Fervor: `HEAL_LOCATION_FERVOR_FIELD`).
