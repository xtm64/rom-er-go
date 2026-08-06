FervorFieldCity_SafariZone_Entrance_ARHU_1_MapScripts::
	.byte 0

FervorFieldCity_SafariZone_Entrance_EventScript_InfoAttendant::
	lock
	faceplayer
	msgbox FervorFieldCity_SafariZone_Entrance_Text_FirstTimeAtSafariZone, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FervorFieldCity_SafariZone_Entrance_EventScript_ExplainSafariZone
	msgbox FervorFieldCity_SafariZone_Entrance_Text_SorryYoureARegularHere
	release
	end

FervorFieldCity_SafariZone_Entrance_EventScript_ExplainSafariZone::
	msgbox FervorFieldCity_SafariZone_Entrance_Text_ExplainSafariZone
	release
	end

FervorFieldCity_SafariZone_Entrance_EventScript_EntryTriggerMid::
	lockall
	setvar VAR_TEMP_2, 0
	goto FervorFieldCity_SafariZone_Entrance_EventScript_AskEnterSafariZone
	end

FervorFieldCity_SafariZone_Entrance_EventScript_EntryTriggerRight::
	lockall
	setvar VAR_TEMP_2, 1
	goto FervorFieldCity_SafariZone_Entrance_EventScript_AskEnterSafariZone
	end

FervorFieldCity_SafariZone_Entrance_EventScript_EntryTriggerLeft::
	lockall
	setvar VAR_TEMP_2, 2
	goto FervorFieldCity_SafariZone_Entrance_EventScript_AskEnterSafariZone
	end

@ TODO: Implement safari zone entry logic (¥500 fee, 30 balls, warp to safari zone center)
FervorFieldCity_SafariZone_Entrance_EventScript_AskEnterSafariZone::
	releaseall
	end

FervorFieldCity_SafariZone_Entrance_Text_FirstTimeAtSafariZone::
	.string "Hi! Is it your first time here at\nthe SAFARI ZONE?$"

FervorFieldCity_SafariZone_Entrance_Text_ExplainSafariZone::
	.string "Welcome to the SAFARI ZONE!\p"
	.string "You can catch rare POKéMON here.$"

FervorFieldCity_SafariZone_Entrance_Text_SorryYoureARegularHere::
	.string "Sorry, you're a regular here!$"
