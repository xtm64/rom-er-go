# Playbook: Fervor Field's Safari behind the entrance building

**Run this only when the user asks.** They will list the new Safari features in that request, and
those features decide the scripts in steps 3-5. Everything below is the base the features build on.

Goal: a Fervor version of the FRLG Safari Zone, built from Center, East, North, West, four rest houses
and the secret house, running in the Emerald build with Emerald items, flags and doors. The player
reaches it through `FervorFieldCity_SafariZone_Entrance_ARHU_1`. Today that warp points at the
FRLG-only `MAP_SAFARI_ZONE_CENTER`, and `AskEnterSafariZone` is still a TODO.

The map names below (`SafariZone_*_ARHU`) are placeholders. Agree real Fervor names with the user
first (for example a `FervorField...` prefix, like the entrance) and substitute them throughout.

This whole plan was dry-run, then run with `--write` and validated in a throwaway worktree on
2026-10-28/29 (commit `4c4a6d976a`). Expected results are written next to each step. If a step's
output differs, stop and find out why before going on.

```
T=.github/skills/frlg-emerald-map-port/scripts/arhu_maps.pl
```

## 0. Preparation

- Commit or stash. `git status` should show nothing staged.
- Confirm with the user: map names (`SafariZone_*_ARHU` below), map group
  (`gMapGroup_SafariZone_ARHU`, new), and whether the ¥500 fee stays (the Tanglewood story may want
  the first visit free).

## 1. Put the tile behaviors back (shared tilesets; ask first)

```
perl $T restore-behaviors gTileset_General_Frlg gTileset_FuchsiaCity gTileset_BuildingFrlg gTileset_SafariZoneBuilding
```
Expect 122 + 19 + 11 + 0 metatiles, mostly tall grass, water, ledges and arrow warps. Each line shows which
Fervor maps use that metatile. For example, Fervor City's water #291/#292/#299 becomes surfable again, and its
#98/#347 become doors again. Show the user this list; Fervor City changes too. With their yes:
```
perl $T restore-behaviors gTileset_General_Frlg gTileset_FuchsiaCity gTileset_BuildingFrlg --write
```
Without this step the Safari has **no grass encounters** (FRLG grass #13 is `MB_NORMAL` today).

## 2. Port all nine maps in one batch

Dry run first, then the same command with `--write`:
```
perl $T port \
  SafariZone_Center_Frlg=SafariZone_Center_ARHU  SafariZone_East_Frlg=SafariZone_East_ARHU \
  SafariZone_North_Frlg=SafariZone_North_ARHU    SafariZone_West_Frlg=SafariZone_West_ARHU \
  SafariZone_Center_RestHouse_Frlg=SafariZone_Center_RestHouse_ARHU \
  SafariZone_East_RestHouse_Frlg=SafariZone_East_RestHouse_ARHU \
  SafariZone_North_RestHouse_Frlg=SafariZone_North_RestHouse_ARHU \
  SafariZone_West_RestHouse_Frlg=SafariZone_West_RestHouse_ARHU \
  SafariZone_SecretHouse_Frlg=SafariZone_SecretHouse_ARHU \
  --group gMapGroup_SafariZone_ARHU \
  --retarget MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE=MAP_FERVOR_FIELD_CITY_SAFARI_ZONE_ENTRANCE_ARHU_1 \
  --promote-overflow
```
Expected:
- `FRLG primary metatile 519 -> gTileset_FuchsiaCity #192 (Emerald id 704, ..., appended)`. This is the
  only overflow metatile (73 cells across East/North/West). It's appended, so no existing id changes.
- 4 wild encounter tables copied from the FireRed versions as `gSafariZone_{Center,East,North,West}_ARHU`
  (exact copies; 388 -> 392 entries, none lost). Use `--encounters LeafGreen` for the LeafGreen lists.
- FRLG item balls converted to Emerald item balls (`Common_EventScript_FindItem` + item id), and
  FRLG flags cleared to `"0"` with a list of the spots that need new storyline flags (step 5).
  All other script labels renamed to `SafariZone_*_ARHU_*`.
- Sprites swapped automatically: SCIENTIST -> SCIENTIST_1, MAN -> MAN_1, FISHER -> FISHERMAN,
  GENTLEMAN_FRLG -> GENTLEMAN, WOMAN_1_FRLG -> WOMAN_1, BALDING_MAN -> OLD_MAN,
  COOLTRAINER_F -> WOMAN_5, WORKER_M -> MAN_4. **ROCKER** (East rest house) has no candidate, so the user picks one.
- The three Center exits now lead to the Fervor entrance (warp 0 = the door at 4,1).
- Files: 9 map folders, 9 layout folders, `layouts.json`, `map_groups.json`, `event_scripts.s`,
  `wild_encounters.json`, and Fuchsia `metatiles.bin`/`metatile_attributes.bin` (+1 metatile).

## 3. Connect the Fervor entrance to the new Center

In `data/maps/FervorFieldCity_SafariZone_Entrance_ARHU_1/map.json`, set warp 0 (4,1)
`dest_map` to `MAP_SAFARI_ZONE_CENTER_ARHU` and keep `dest_warp_id` `"1"`, the middle of the Center's
bottom exit. This clears the one `validate` error Fervor has today.

Claim a var for the entrance flow. Don't reuse `VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE`,
because it shares 0x406E with an Emerald var. In `include/constants/vars.h`:
```
#define VAR_FERVOR_FIELD_SAFARI_STATE   0x40FA // 0 = outside, 1 = exited (warp in), 2 = inside, 3 = out of balls mid-battle (walk in)
```
(replacing `VAR_UNUSED_0x40FA`).

Write the entrance script in `FervorFieldCity_SafariZone_Entrance_ARHU_1/scripts.inc`, using
`data/maps/FuchsiaCity_SafariZone_Entrance_Frlg/scripts.inc` as the model. Swap the FRLG var for the
one above, drop `textcolor`/`EventScript_RestorePrevTextColor` (FRLG text colors), and use
`warp MAP_SAFARI_ZONE_CENTER_ARHU, 26, 30`. Outline:
```
FervorFieldCity_SafariZone_Entrance_ARHU_1_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FervorFieldCity_SafariZone_Entrance_OnFrame
	.byte 0

FervorFieldCity_SafariZone_Entrance_OnFrame:
	map_script_2 VAR_FERVOR_FIELD_SAFARI_STATE, 1, FervorFieldCity_SafariZone_Entrance_EventScript_ExitWarpIn
	map_script_2 VAR_FERVOR_FIELD_SAFARI_STATE, 2, FervorFieldCity_SafariZone_Entrance_EventScript_ExitEarly
	map_script_2 VAR_FERVOR_FIELD_SAFARI_STATE, 3, FervorFieldCity_SafariZone_Entrance_EventScript_ExitWalkIn
	.2byte 0
```
`AskEnterSafariZone` = the FRLG version: money box, `checkmoney 500`, `removemoney 500`, the
30-ball fanfare, the walk-up movement chosen by `VAR_TEMP_2`, `special EnterSafariMode`,
`setvar VAR_FERVOR_FIELD_SAFARI_STATE, 2`, then the warp. Each exit script ends with
`special ExitSafariMode` and `setvar VAR_FERVOR_FIELD_SAFARI_STATE, 0`. For the "already passed"
story beat, also set `VAR_FERVOR_FIELD_TANGLEWOOD_STATE` to 2 there.

## 4. Send the Safari exit to Fervor (shared Safari script)

`data/scripts/safari_zone.inc` sends Emerald players to Route 121. Add a Fervor branch at the top of
the `#else` paths so the Hoenn Safari keeps working:
```
SafariZone_EventScript_Exit::
#if IS_FRLG
	...unchanged...
#else
	goto_if_eq VAR_FERVOR_FIELD_SAFARI_STATE, 2, SafariZone_EventScript_ExitToFervorField
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	...

SafariZone_EventScript_ExitToFervorField::
	setvar VAR_FERVOR_FIELD_SAFARI_STATE, 1
	special ExitSafariMode
	warp MAP_FERVOR_FIELD_CITY_SAFARI_ZONE_ENTRANCE_ARHU_1, 4, 1
	waitstate
	end
```
Do the same in `SafariZone_EventScript_OutOfBallsMidBattle`: set the var to 3, then
`setwarp MAP_FERVOR_FIELD_CITY_SAFARI_ZONE_ENTRANCE_ARHU_1, 4, 1`. The step limit is 500 in Emerald
(`src/safari_zone.c`); change it there if the story's time limit differs.

## 5. New storyline flags for items (Emerald configuration)

Which items exist and where is up to the user's feature list. The FRLG ones are only a starting
point. For every item ball and hidden item that stays, claim a `FLAG_UNUSED_0x...` in `flags.h` with a
Fervor name (e.g. `FLAG_ITEM_FERVOR_SAFARI_CENTER_NUGGET`) and put it in the map.json `flag`.
`port` prints the list and `validate` warns about every item still on flag `"0"`. Delete the
`setworldmapflag FLAG_WORLD_MAP_...` line in the Center's `OnTransition` (FRLG world map, no effect in
Emerald).

## 5b. Doors

Rest-house and secret-house doors are FRLG door tiles; `validate` reports each one that won't animate.
Use the approach the user chose in rules.md "Doors" (A: FRLG art with Emerald's door system; B: Emerald
door art; C: Emerald tilesets). Fervor's own doors take the same fix: the player's house at (17,29),
and the gate at (24,5), which also needs `MB_ANIMATED_DOOR` instead of `MB_NON_ANIMATED_DOOR`.

## 6. Clean up in Porymap

- Borders: FRLG used a 3x2 tree border; the port keeps `0x275 0x276 / 0x27D 0x27E`. Check the edges.
- Repainted slots: `audit` lists primary metatiles 1, 8, 9, 16, 17, 230 and 307 as repainted for Fervor. Check that
  they still look right in the Safari, or move Fervor's art to a new slot.
- Fuchsia #126 (Emerald 638) is `MB_ANIMATED_DOOR` for Fervor's gate, and the Center uses it in 91 cells.
  That's harmless where there's no warp, but check it visually.
- North rest house: the Balding Man uses `famechecker` (an FRLG feature). Replace it with a plain `msgbox`.
- East rest house: choose a sprite for the Rocker.
- The "stands on MB_NORMAL" warnings left after step 1 are the outer tile of each 3-wide exit, which is arrival-only
  in FRLG too. No fix needed.

## 7. Check and build

```
perl $T validate
```
Goal: 0 errors. Then the user builds in their toolchain and checks in game:
- Enter through the gate: money is taken, you get 30 balls, you land at (26,30) in Center.
- Walk every area exit (Center <-> East/North/West) and every rest-house door.
- Grass gives Safari battles (bait/rock), water surfs and fishes, ledges hop.
- Running out of balls or steps returns you to the Fervor entrance; walking back in asks about leaving early.
- Item balls disappear once picked up and stay gone after a save and reload.
