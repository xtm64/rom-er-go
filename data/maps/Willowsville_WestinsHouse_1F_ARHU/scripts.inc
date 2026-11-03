@ Westin's family home. His mom lives here and acts as a heal point for the far north.
Willowsville_WestinsHouse_1F_ARHU_MapScripts::
	.byte 0

Willowsville_WestinsHouse_1F_ARHU_EventScript_Mom::
	lock
	faceplayer
	goto Willowsville_WestinsHouse_1F_ARHU_EventScript_MomHeal
	end

Willowsville_WestinsHouse_1F_ARHU_EventScript_MomHeal::
	msgbox Willowsville_WestinsHouse_1F_ARHU_Text_YouShouldTakeQuickRest
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	setrespawn HEAL_LOCATION_WILLOWSVILLE
	msgbox Willowsville_WestinsHouse_1F_ARHU_Text_LookingGreatTakeCare
	closemessage
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

@ Displays special text if interacted with from side or back (which are normally inaccessible)
Willowsville_WestinsHouse_1F_ARHU_EventScript_TV::
	lockall
	goto_if_eq VAR_FACING, DIR_NORTH, Willowsville_WestinsHouse_1F_ARHU_EventScript_TVScreen
	msgbox Willowsville_WestinsHouse_1F_ARHU_Text_OopsWrongSide
	releaseall
	end

Willowsville_WestinsHouse_1F_ARHU_EventScript_TVScreen::
	msgbox Willowsville_WestinsHouse_1F_ARHU_Text_WeatherReport
	releaseall
	end

Willowsville_WestinsHouse_1F_ARHU_Text_YouShouldTakeQuickRest::
	.string "Oh, {PLAYER}! Westin's told me all\n"
	.string "about you.\p"
	.string "You should take a quick rest.\n"
	.string "Come sit by the stove.$"

Willowsville_WestinsHouse_1F_ARHU_Text_LookingGreatTakeCare::
	.string "Oh, good! You and your\n"
	.string "POKéMON are looking great.\p"
	.string "You're always welcome here.\n"
	.string "Take care now!$"

Willowsville_WestinsHouse_1F_ARHU_Text_WeatherReport::
	.string "The weather report is on TV.\p"
	.string "“A cold front is moving in from\n"
	.string "the north. Bundle up!”$"

Willowsville_WestinsHouse_1F_ARHU_Text_OopsWrongSide::
	.string "Oops, wrong side…$"
