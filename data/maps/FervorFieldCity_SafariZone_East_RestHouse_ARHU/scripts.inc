@ Ported from SafariZone_East_RestHouse_Frlg by arhu_maps.pl; labels renamed SafariZone_East_RestHouse_Frlg/SafariZone_East_RestHouse_* -> FervorFieldCity_SafariZone_East_RestHouse_ARHU_*
FervorFieldCity_SafariZone_East_RestHouse_ARHU_MapScripts::
	.byte 0

FervorFieldCity_SafariZone_East_RestHouse_ARHU_EventScript_Rocker::
	msgbox FervorFieldCity_SafariZone_East_RestHouse_ARHU_SafariZone_East_Text_CaughtChanseyAllWorthwhile, MSGBOX_NPC
	end

FervorFieldCity_SafariZone_East_RestHouse_ARHU_EventScript_Scientist::
	msgbox FervorFieldCity_SafariZone_East_RestHouse_ARHU_SafariZone_East_Text_HowManyDidYouCatch, MSGBOX_NPC
	end

FervorFieldCity_SafariZone_East_RestHouse_ARHU_EventScript_BaldingMan::
	msgbox FervorFieldCity_SafariZone_East_RestHouse_ARHU_SafariZone_East_Text_TiredFromAllTheFun, MSGBOX_NPC
	end

FervorFieldCity_SafariZone_East_RestHouse_ARHU_SafariZone_East_Text_HowManyDidYouCatch::
	.string "How many did you catch?\n"
	.string "I'm bushed from the effort!$"

FervorFieldCity_SafariZone_East_RestHouse_ARHU_SafariZone_East_Text_CaughtChanseyAllWorthwhile::
	.string "I caught a CHANSEY!\p"
	.string "That makes this all worthwhile.$"

FervorFieldCity_SafariZone_East_RestHouse_ARHU_SafariZone_East_Text_TiredFromAllTheFun::
	.string "Whew!\n"
	.string "I'm tired from all the fun!$"

