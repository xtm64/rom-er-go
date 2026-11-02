@ Ported from SafariZone_North_RestHouse_Frlg by arhu_maps.pl; labels renamed SafariZone_North_RestHouse_Frlg/SafariZone_North_RestHouse_* -> FervorFieldCity_SafariZone_North_RestHouse_ARHU_*
FervorFieldCity_SafariZone_North_RestHouse_ARHU_MapScripts::
	.byte 0

FervorFieldCity_SafariZone_North_RestHouse_ARHU_EventScript_Fisher::
	msgbox FervorFieldCity_SafariZone_North_RestHouse_ARHU_SafariZone_East_Text_PrizeInDeepestPartOfSafariZone, MSGBOX_NPC
	end

FervorFieldCity_SafariZone_North_RestHouse_ARHU_EventScript_Scientist::
	msgbox FervorFieldCity_SafariZone_North_RestHouse_ARHU_SafariZone_East_Text_KeepAnyItemFoundOnSafari, MSGBOX_NPC
	end

FervorFieldCity_SafariZone_North_RestHouse_ARHU_EventScript_Gentleman::
	msgbox FervorFieldCity_SafariZone_North_RestHouse_ARHU_SafariZone_East_Text_MyEeveeEvolvedIntoFlareon, MSGBOX_NPC
	end

FervorFieldCity_SafariZone_North_RestHouse_ARHU_SafariZone_East_Text_KeepAnyItemFoundOnSafari::
	.string "You can keep any item you find in\n"
	.string "the SAFARI ZONE.\p"
	.string "But, you'll run out of time if you\n"
	.string "try for all of them at once.$"

FervorFieldCity_SafariZone_North_RestHouse_ARHU_SafariZone_East_Text_PrizeInDeepestPartOfSafariZone::
	.string "Go to the deepest part of the\n"
	.string "SAFARI ZONE. You will win a prize!$"

FervorFieldCity_SafariZone_North_RestHouse_ARHU_SafariZone_East_Text_MyEeveeEvolvedIntoFlareon::
	.string "My EEVEE evolved into FLAREON.\p"
	.string "But, a friend's EEVEE turned into a\n"
	.string "VAPOREON. I wonder why?$"

@ Copied from data/scripts/fame_checker_frlg.inc (FRLG-only there)
FervorFieldCity_SafariZone_North_RestHouse_ARHU_EventScript_BaldingMan::
	lock
	faceplayer
	famechecker FAMECHECKER_KOGA, 5
	msgbox FervorFieldCity_SafariZone_West_RestHouse_ARHU_SafariZone_West_Text_KogaPatrolsSafariEverySoOften
	release
	end

