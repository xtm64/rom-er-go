@ Ported from SafariZone_Center_Frlg by arhu_maps.pl; labels renamed SafariZone_Center_Frlg/SafariZone_Center_* -> FervorFieldCity_SafariZone_Center_ARHU_*
FervorFieldCity_SafariZone_Center_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FervorFieldCity_SafariZone_Center_ARHU_OnTransition
	.byte 0

FervorFieldCity_SafariZone_Center_ARHU_OnTransition::
	end

FervorFieldCity_SafariZone_Center_ARHU_EventScript_RestHouseSign::
	msgbox FervorFieldCity_SafariZone_Center_ARHU_Text_RestHouse, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_Center_ARHU_EventScript_TrainerTips::
	msgbox FervorFieldCity_SafariZone_Center_ARHU_Text_PressStartToCheckTime, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_Center_ARHU_EventScript_AreaSign::
	msgbox FervorFieldCity_SafariZone_Center_ARHU_Text_CenterArea, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_Center_ARHU_Text_RestHouse::
	.string "REST HOUSE$"

FervorFieldCity_SafariZone_Center_ARHU_Text_PressStartToCheckTime::
	.string "TRAINER TIPS\p"
	.string "Press START to check\n"
	.string "remaining time.$"

FervorFieldCity_SafariZone_Center_ARHU_Text_CenterArea::
	.string "CENTER AREA$"

FervorFieldCity_SafariZone_Center_ARHU_EventScript_DirectionsSign::
	msgbox FervorFieldCity_SafariZone_Center_ARHU_Text_Directions, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_Center_ARHU_Text_Directions::
	.string "NORTH: AREA 2\n"
	.string "EAST: AREA 1\p"
	.string "WEST: AREA 3$"

