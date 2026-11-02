FervorFieldCity_SafariZone_Entrance_ARHU_1_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FervorFieldCity_SafariZone_Entrance_OnFrame
	.byte 0

@ Safari attendant flow copied from FuchsiaCity_SafariZone_Entrance_Frlg, with the
@ FRLG scene var swapped for VAR_FERVOR_FIELD_SAFARI_STATE and FRLG text colors dropped.
FervorFieldCity_SafariZone_Entrance_OnFrame::
	map_script_2 VAR_FERVOR_FIELD_SAFARI_STATE, 1, FervorFieldCity_SafariZone_Entrance_EventScript_ExitWarpIn
	map_script_2 VAR_FERVOR_FIELD_SAFARI_STATE, 2, FervorFieldCity_SafariZone_Entrance_EventScript_ExitEarly
	map_script_2 VAR_FERVOR_FIELD_SAFARI_STATE, 3, FervorFieldCity_SafariZone_Entrance_EventScript_ExitWalkIn
	.2byte 0

@ When player runs out of balls mid-battle
FervorFieldCity_SafariZone_Entrance_EventScript_ExitWalkIn::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_ApproachCounter
	waitmovement 0
	msgbox FervorFieldCity_SafariZone_Entrance_Text_CatchFairShareComeAgain
	closemessage
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_Exit2
	waitmovement 0
	special ExitSafariMode
	setvar VAR_FERVOR_FIELD_SAFARI_STATE, 0
	releaseall
	end

@ When player runs of out balls after catching a pokemon, or runs out of steps
FervorFieldCity_SafariZone_Entrance_EventScript_ExitWarpIn::
	lockall
	msgbox FervorFieldCity_SafariZone_Entrance_Text_CatchFairShareComeAgain
	closemessage
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_Exit
	waitmovement 0
	special ExitSafariMode
	setvar VAR_FERVOR_FIELD_SAFARI_STATE, 0
	releaseall
	end

@ When player re-enters the entrance building with balls/steps remaining
FervorFieldCity_SafariZone_Entrance_EventScript_ExitEarly::
	lockall
	msgbox FervorFieldCity_SafariZone_Entrance_Text_GoingToLeaveSafariZoneEarly, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FervorFieldCity_SafariZone_Entrance_EventScript_ReturnToSafariZone
	msgbox FervorFieldCity_SafariZone_Entrance_Text_PleaseReturnSafariBalls
	closemessage
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_Exit
	waitmovement 0
	special ExitSafariMode
	setvar VAR_FERVOR_FIELD_SAFARI_STATE, 0
	releaseall
	end

FervorFieldCity_SafariZone_Entrance_EventScript_ReturnToSafariZone::
	msgbox FervorFieldCity_SafariZone_Entrance_Text_GoodLuck
	closemessage
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_ReEnter
	waitmovement 0
	warp MAP_FERVOR_FIELD_CITY_SAFARI_ZONE_CENTER_ARHU, 26, 30
	waitstate
	end

FervorFieldCity_SafariZone_Entrance_Movement_Exit:
	walk_down
	walk_down
	step_end

FervorFieldCity_SafariZone_Entrance_Movement_ReEnter:
	walk_up
	step_end

FervorFieldCity_SafariZone_Entrance_Movement_Exit2:
	walk_down
	walk_down
	step_end

FervorFieldCity_SafariZone_Entrance_Movement_ApproachCounter:
	walk_down
	delay_8
	step_end

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

FervorFieldCity_SafariZone_Entrance_EventScript_AskEnterSafariZone::
	msgbox FervorFieldCity_SafariZone_Entrance_Text_WelcomeToSafariZone
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmoneybox 0, 0
	msgbox FervorFieldCity_SafariZone_Entrance_Text_PlaySafariGameFor500, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FervorFieldCity_SafariZone_Entrance_EventScript_TryEnterSafariZone
	msgbox FervorFieldCity_SafariZone_Entrance_Text_OkayPleaseComeAgain
	goto FervorFieldCity_SafariZone_Entrance_EventScript_ForcePlayerBack
	end

FervorFieldCity_SafariZone_Entrance_EventScript_TryEnterSafariZone::
	call FervorFieldCity_SafariZone_Entrance_EventScript_CheckSpaceForMons
	checkmoney 500
	goto_if_eq VAR_RESULT, FALSE, FervorFieldCity_SafariZone_Entrance_EventScript_NotEnoughMoney
	removemoney 500
	updatemoneybox
	msgbox FervorFieldCity_SafariZone_Entrance_Text_ThatllBe500WeOnlyUseSpecialBalls
	playfanfare MUS_LEVEL_UP
	message FervorFieldCity_SafariZone_Entrance_Text_PlayerReceived30SafariBalls
	waitfanfare
	msgbox FervorFieldCity_SafariZone_Entrance_Text_CallYouOnPAWhenYouRunOut
	closemessage
	hidemoneybox
	call_if_eq VAR_TEMP_2, 0, FervorFieldCity_SafariZone_Entrance_EventScript_EnterSafariZoneMid
	call_if_eq VAR_TEMP_2, 1, FervorFieldCity_SafariZone_Entrance_EventScript_EnterSafariZoneRight
	call_if_eq VAR_TEMP_2, 2, FervorFieldCity_SafariZone_Entrance_EventScript_EnterSafariZoneLeft
	special EnterSafariMode
	setvar VAR_FERVOR_FIELD_SAFARI_STATE, 2
	warp MAP_FERVOR_FIELD_CITY_SAFARI_ZONE_CENTER_ARHU, 26, 30
	waitstate
	end

FervorFieldCity_SafariZone_Entrance_EventScript_EnterSafariZoneRight::
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_EnterSafariZoneRight
	waitmovement 0
	return

FervorFieldCity_SafariZone_Entrance_EventScript_EnterSafariZoneMid::
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_EnterSafariZoneMid
	waitmovement 0
	return

FervorFieldCity_SafariZone_Entrance_EventScript_EnterSafariZoneLeft::
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_EnterSafariZoneLeft
	waitmovement 0
	return

FervorFieldCity_SafariZone_Entrance_EventScript_CheckSpaceForMons::
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, Common_EventScript_NopReturn
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NopReturn
	msgbox Route121_SafariZoneEntrance_Text_PCIsFull
	goto FervorFieldCity_SafariZone_Entrance_EventScript_ForcePlayerBack
	end

FervorFieldCity_SafariZone_Entrance_EventScript_NotEnoughMoney::
	msgbox FervorFieldCity_SafariZone_Entrance_Text_OopsNotEnoughMoney
	goto FervorFieldCity_SafariZone_Entrance_EventScript_ForcePlayerBack
	end

FervorFieldCity_SafariZone_Entrance_EventScript_ForcePlayerBack::
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, FervorFieldCity_SafariZone_Entrance_Movement_ForceBack
	waitmovement 0
	releaseall
	end

FervorFieldCity_SafariZone_Entrance_Movement_ForceBack:
	walk_down
	step_end

FervorFieldCity_SafariZone_Entrance_Movement_EnterSafariZoneMid:
	walk_up
	walk_up
	step_end

FervorFieldCity_SafariZone_Entrance_Movement_EnterSafariZoneRight:
	walk_up
	walk_left
	walk_up
	step_end

FervorFieldCity_SafariZone_Entrance_Movement_EnterSafariZoneLeft:
	walk_up
	walk_right
	walk_up
	step_end

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

FervorFieldCity_SafariZone_Entrance_Text_WelcomeToSafariZone::
	.string "Welcome to the SAFARI ZONE!$"

FervorFieldCity_SafariZone_Entrance_Text_PlaySafariGameFor500::
	.string "For just ¥500, you can play the\n"
	.string "SAFARI GAME.\p"
	.string "You can roam the wide-open safari\n"
	.string "and catch what you like.\p"
	.string "Would you like to play?$"

FervorFieldCity_SafariZone_Entrance_Text_ThatllBe500WeOnlyUseSpecialBalls::
	.string "That'll be ¥500, please!\p"
	.string "We only use a special kind of \n"
	.string "POKé BALLS here.$"

FervorFieldCity_SafariZone_Entrance_Text_PlayerReceived30SafariBalls::
	.string "{PLAYER} received 30 SAFARI BALLS\n"
	.string "from the attendant.$"

FervorFieldCity_SafariZone_Entrance_Text_CallYouOnPAWhenYouRunOut::
	.string "We'll call you on the PA when you\n"
	.string "run out of time or SAFARI BALLS.\p"
	.string "Well, I'll wish you the best of\n"
	.string "luck!$"

FervorFieldCity_SafariZone_Entrance_Text_OkayPleaseComeAgain::
	.string "Okay.\n"
	.string "Please come again!$"

FervorFieldCity_SafariZone_Entrance_Text_OopsNotEnoughMoney::
	.string "Oops!\n"
	.string "Not enough money!$"

FervorFieldCity_SafariZone_Entrance_Text_GoingToLeaveSafariZoneEarly::
	.string "Are you going to leave the\n"
	.string "SAFARI ZONE early?$"

FervorFieldCity_SafariZone_Entrance_Text_PleaseReturnSafariBalls::
	.string "Please return any SAFARI BALLS\n"
	.string "you may have left.$"

FervorFieldCity_SafariZone_Entrance_Text_GoodLuck::
	.string "Good luck!$"

FervorFieldCity_SafariZone_Entrance_Text_CatchFairShareComeAgain::
	.string "Did you catch your fair share?\n"
	.string "Come again!$"

FervorFieldCity_SafariZone_Entrance_Text_FirstTimeAtSafariZone::
	.string "Hi! Is it your first time here at\n"
	.string "the SAFARI ZONE?$"

FervorFieldCity_SafariZone_Entrance_Text_ExplainSafariZone::
	.string "The SAFARI ZONE actually has\n"
	.string "four zones in it.\p"
	.string "Each zone has different kinds of\n"
	.string "POKéMON, even some rare ones.\p"
	.string "Use the supplied SAFARI BALLS to\n"
	.string "catch them.\p"
	.string "You can also throw BAIT or ROCKS\n"
	.string "besides the SAFARI BALLS.\p"
	.string "If you throw BAIT, the POKéMON\n"
	.string "becomes less likely to flee, but\l"
	.string "harder to catch.\p"
	.string "If you throw ROCKS, the POKéMON\n"
	.string "becomes more likely to flee, but\l"
	.string "easier to catch.\p"
	.string "When you run out of time or SAFARI\n"
	.string "BALLS, it's game over for you!$"

FervorFieldCity_SafariZone_Entrance_Text_SorryYoureARegularHere::
	.string "Sorry, you're a regular here!$"
