@ Ported from SafariZone_West_Frlg by arhu_maps.pl; labels renamed SafariZone_West_Frlg/SafariZone_West_* -> FervorFieldCity_SafariZone_West_ARHU_*
FervorFieldCity_SafariZone_West_ARHU_MapScripts::
	.byte 0

FervorFieldCity_SafariZone_West_ARHU_EventScript_RestHouseSign::
	msgbox FervorFieldCity_SafariZone_West_ARHU_Text_RestHouse, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_West_ARHU_EventScript_LostTeethNotice::
	msgbox FervorFieldCity_SafariZone_West_ARHU_Text_PleaseFindWardensLostTeeth, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_West_ARHU_EventScript_TrainerTips::
	msgbox FervorFieldCity_SafariZone_West_ARHU_Text_SearchForSecretHouse, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_West_ARHU_EventScript_AreaSign::
	msgbox FervorFieldCity_SafariZone_West_ARHU_Text_AreaSign, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_West_ARHU_Text_RestHouse::
	.string "REST HOUSE$"

FervorFieldCity_SafariZone_West_ARHU_Text_PleaseFindWardensLostTeeth::
	.string "REQUEST NOTICE\p"
	.string "Please find the SAFARI WARDEN's\n"
	.string "lost GOLD TEETH.\l"
	.string "They're around here somewhere.\p"
	.string "Reward offered!\n"
	.string "Contact: WARDEN$"

FervorFieldCity_SafariZone_West_ARHU_Text_SearchForSecretHouse::
	.string "TRAINER TIPS\p"
	.string "Zone Exploration Campaign!\n"
	.string "The Search for the SECRET HOUSE!$"

FervorFieldCity_SafariZone_West_ARHU_Text_AreaSign::
	.string "AREA 3\n"
	.string "EAST: CENTER AREA$"

