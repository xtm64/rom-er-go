@ Ported from SafariZone_North_Frlg by arhu_maps.pl; labels renamed SafariZone_North_Frlg/SafariZone_North_* -> FervorFieldCity_SafariZone_North_ARHU_*
FervorFieldCity_SafariZone_North_ARHU_MapScripts::
	.byte 0

FervorFieldCity_SafariZone_North_ARHU_EventScript_RestHouseSign::
	msgbox FervorFieldCity_SafariZone_North_ARHU_Text_RestHouse, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_North_ARHU_EventScript_TrainerTips1::
	msgbox FervorFieldCity_SafariZone_North_ARHU_Text_SecretHouseStillAhead, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_North_ARHU_EventScript_AreaSign::
	msgbox FervorFieldCity_SafariZone_North_ARHU_Text_Area2, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_North_ARHU_EventScript_TrainerTips2::
	msgbox FervorFieldCity_SafariZone_North_ARHU_Text_ZigzagThroughTallGrass, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_North_ARHU_EventScript_TrainerTips3::
	msgbox FervorFieldCity_SafariZone_North_ARHU_Text_WinFreeHMFindSecretHouse, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_North_ARHU_Text_RestHouse::
	.string "REST HOUSE$"

FervorFieldCity_SafariZone_North_ARHU_Text_SecretHouseStillAhead::
	.string "TRAINER TIPS\p"
	.string "The SECRET HOUSE is still ahead.$"

FervorFieldCity_SafariZone_North_ARHU_Text_Area2::
	.string "AREA 2$"

FervorFieldCity_SafariZone_North_ARHU_Text_ZigzagThroughTallGrass::
	.string "TRAINER TIPS\p"
	.string "POKéMON hide in tall grass.\p"
	.string "Zigzag through grassy areas to\n"
	.string "flush them out.$"

FervorFieldCity_SafariZone_North_ARHU_Text_WinFreeHMFindSecretHouse::
	.string "TRAINER TIPS\p"
	.string "Win a free HM for finding the\n"
	.string "SECRET HOUSE.$"

FervorFieldCity_SafariZone_North_ARHU_EventScript_DirectionsSign::
	msgbox FervorFieldCity_SafariZone_North_ARHU_Text_Directions, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_North_ARHU_Text_Directions::
	.string "WEST: AREA 3\n"
	.string "EAST: AREA 1\p"
	.string "SOUTH: CENTER AREA$"

