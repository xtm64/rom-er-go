@ Ported from SafariZone_SecretHouse_Frlg by arhu_maps.pl; labels renamed SafariZone_SecretHouse_Frlg/SafariZone_SecretHouse_* -> FervorFieldCity_SafariZone_SecretHouse_ARHU_*
FervorFieldCity_SafariZone_SecretHouse_ARHU_MapScripts::
	.byte 0

FervorFieldCity_SafariZone_SecretHouse_ARHU_EventScript_Attendant::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_FERVOR_SAFARI_HM03, FervorFieldCity_SafariZone_SecretHouse_ARHU_EventScript_ExplainSurf
	msgbox FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_CongratsYouveWon
	checkitemspace ITEM_HM03
	goto_if_eq VAR_RESULT, FALSE, FervorFieldCity_SafariZone_SecretHouse_ARHU_EventScript_NoRoomForHM03
	giveitem_msg FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_ReceivedHM03FromAttendant, ITEM_HM03
	msgbox FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_ExplainSurf
	setflag FLAG_RECEIVED_FERVOR_SAFARI_HM03
	release
	end

FervorFieldCity_SafariZone_SecretHouse_ARHU_EventScript_NoRoomForHM03::
	msgbox FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_DontHaveRoomForPrize
	release
	end

FervorFieldCity_SafariZone_SecretHouse_ARHU_EventScript_ExplainSurf::
	msgbox FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_ExplainSurf
	release
	end

FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_CongratsYouveWon::
	.string "Ah! Finally!\p"
	.string "You're the first person to reach\n"
	.string "the SECRET HOUSE!\p"
	.string "Although I made a campaign\n"
	.string "for our grand opening,\p"
	.string "I was getting worried that no one\n"
	.string "would win our campaign prize.\p"
	.string "Congratulations!\n"
	.string "You have won!$"

FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_ReceivedHM03FromAttendant::
	.string "{PLAYER} received HM03\n"
	.string "from the attendant!$"

FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_ExplainSurf::
	.string "HM03 is SURF.\p"
	.string "POKéMON will be able to ferry you\n"
	.string "across water using it.\p"
	.string "And, this HM isn't disposable, so\n"
	.string "you can use it over and over.\p"
	.string "You're super lucky for winning this\n"
	.string "fabulous prize!$"

FervorFieldCity_SafariZone_SecretHouse_ARHU_Text_DontHaveRoomForPrize::
	.string "You don't have room for this\n"
	.string "fabulous prize!$"

