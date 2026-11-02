@ Ported from SafariZone_East_Frlg by arhu_maps.pl; labels renamed SafariZone_East_Frlg/SafariZone_East_* -> FervorFieldCity_SafariZone_East_ARHU_*
FervorFieldCity_SafariZone_East_ARHU_MapScripts::
	.byte 0

FervorFieldCity_SafariZone_East_ARHU_EventScript_RestHouseSign::
	msgbox FervorFieldCity_SafariZone_East_ARHU_Text_RestHouse, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_East_ARHU_EventScript_TrainerTips::
	msgbox FervorFieldCity_SafariZone_East_ARHU_Text_TimeDeclinesOnlyWhileYouWalk, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_East_ARHU_EventScript_AreaSign::
	msgbox FervorFieldCity_SafariZone_East_ARHU_Text_AreaSign, MSGBOX_SIGN
	end

FervorFieldCity_SafariZone_East_ARHU_Text_RestHouse::
	.string "REST HOUSE$"

FervorFieldCity_SafariZone_East_ARHU_Text_TimeDeclinesOnlyWhileYouWalk::
	.string "TRAINER TIPS\p"
	.string "The remaining time declines only\n"
	.string "while you walk.$"

FervorFieldCity_SafariZone_East_ARHU_Text_AreaSign::
	.string "AREA 1\n"
	.string "WEST: CENTER AREA$"

