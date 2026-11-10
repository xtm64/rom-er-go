# Worked example: how Fervor Field was built

Use this as the house style for new ARHU maps.

**Design source:** `data/maps/FervorFieldCity_ARHU/FervorFieldCity_ARHU/map.json` is the city as the
user first laid it out in their binary hack. It's the starting town and the blueprint: its 12 warps
list the planned buildings (player's house and Safari entrance are built; Warden's house, Mart, Safari
office, Gym, Pokémon Center and three houses are still to come). Its NPCs are the ones placed in
the binary hack.
The cutscenes in the live city were ported from the user's Hex Maniac Advance (HMA) scripts.
`perl $T roadmap` shows the current state.

| ARHU map | Made from | Layout tilesets | Notes |
|---|---|---|---|
| `FervorFieldCity_ARHU` (48x40) | `FuchsiaCity_Frlg` | General_Frlg + FuchsiaCity | Block data repainted; secondary ids -128. Group `gMapGroup_TownsAndRoutes_ARHU`. Heal location `HEAL_LOCATION_FERVOR_FIELD`. |
| `FervorField_PlayersHouse_1F_ARHU` (13x10) | `PalletTown_PlayersHouse_1F_Frlg` | BuildingFrlg + GenericBuilding1 | Block data identical to the source (primary only). Mom keeps `LOCALID_PLAYERS_HOUSE_1F_MOM` (index 1, the same in every map that uses it). |
| `FervorField_PlayersHouse_2F_ARHU` (12x9) | `PalletTown_PlayersHouse_2F_Frlg` | BuildingFrlg + GenericBuilding1 | 15 secondary cells -128. |
| `FervorFieldCity_SafariZone_Entrance_ARHU_1` (9x9) | `FuchsiaCity_SafariZone_Entrance_Frlg` | BuildingFrlg + SafariZoneBuilding | Entry trigger stubs; `AskEnterSafariZone` is a TODO (see the playbook). |
| `FervorFieldCity_SafariZone_Entrance_SideRoom_ARHU` (9x9) | new | BuildingFrlg + SafariZoneBuilding | Joined to the entrance with left/right *connections*, not warps. |

What was registered by hand (the tool now does the first four):
- `data/layouts/layouts.json`: entries at the end, no `layout_version`, 2x2 border.
- `data/maps/map_groups.json`: groups `gMapGroup_TownsAndRoutes_ARHU`, `gMapGroup_IndoorFervorField_ARHU`
  appended to `group_order`.
- `data/event_scripts.s`: `.include`s appended after the last line.
- Map JSON: no `region`; `connections: null`.
- `src/data/tilesets/headers.h` / `metatiles.h` / `graphics.h`: the five FRLG tilesets moved outside
  `#if IS_FRLG` and converted in place (see rules.md).
- Flags 0x20-0x26 (`FLAG_HIDE_FERVOR_FIELD_CITY_*`) and vars 0x40F7-0x40F9 (`VAR_FERVOR_FIELD_*`),
  each claimed from an unused slot with a comment saying what its values mean.
- Scripts: cutscenes written fresh with a `<MapName>_EventScript_*` prefix. FRLG NPC scripts copied
  into the map ("Local copies of FuchsiaCity_Frlg scripts (FRLG originals are IS_FRLG-only)").
  Cutscene patterns worth reusing: `special SpawnCameraObject` + `applymovement LOCALID_CAMERA`; one
  coord trigger per entry tile that sets `VAR_0x8008` and jumps to a shared `_Main`; objects hidden with
  `setflag FLAG_HIDE_*` + `removeobject` once their scene is over.

Open issues `validate` reports on Fervor today (2026-10-29), so you know what's already there:
- Fixed 2026-11-02: playbook steps 1-4 were run. The Safari is `FervorFieldCity_SafariZone_{Center,East,North,West}_ARHU`
  plus rest houses and the secret house (group `gMapGroup_SafariZone_ARHU`). The entrance runs the FRLG attendant flow
  on `VAR_FERVOR_FIELD_SAFARI_STATE` (0x40FA), and Mom gives ¥500 at the end of the TV cutscene (new games start
  with ¥0). The East rest house Rocker is now `OBJ_EVENT_GFX_MAN_2`. Steps 5 and 5b were then done too:
  - Item balls use flags 0x27-0x32 (`FLAG_ITEM_FERVOR_SAFARI_*`).
  - Hidden items use `FLAG_HIDDEN_ITEMS_START + 0x71/0x72` (they must stay in the hidden-item range).
  - The secret-house HM03 uses 0x33 (`FLAG_RECEIVED_FERVOR_SAFARI_HM03`).
  - Rest-house doors (`METATILE_FuchsiaCity_Door`) animate with FRLG Fuchsia door art through the Emerald door system. Emerald door art is two
    metatiles tall and uses Emerald palettes, so it can't sit on these FRLG tilesets.

  Still open: step 6 (Porymap cleanup).
- Entrance warps (3,7) and (5,7) and house 1F (3,9) are arrival-only (`MB_NORMAL`). Only the entrance's
  middle exit (4,7) can be walked through.
- `FervorField_PlayersHouse_1F_ARHU` Mom script still uses the copied FRLG logic
  (`FLAG_BEAT_RIVAL_IN_OAKS_LAB`, always 0); rewrite it against a new storyline flag.
- Doors: the player's house (17,29) and the Safari gate (24,5) animate with FRLG door art through the
  Emerald door system (rules.md "Doors", option A). Not yet checked in game.

Cleanup done 2026-10-29: NPCs that no script referenced were removed (the Old Man, Link Receptionist and
Picnicker beside the gate; the side-room receptionist), along with the unused copied Fuchsia NPC scripts
(LittleBoy, OldMan, Erik, Youngster, SubstituteTutor). Two unreferenced NPCs were kept on purpose: the
camper at (24,12), who physically blocks the gap between the Tanglewood triggers at (23,12)/(25,12),
and the Safari counter clerk at (7,3) in the entrance, whom the Safari entry flow faces.
- Fervor City has grass but no wild encounter entry.
