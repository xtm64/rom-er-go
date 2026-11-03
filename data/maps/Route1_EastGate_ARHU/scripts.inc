@ Gate on Route 1, ported from Route18_EastEntrance_1F_Frlg. The FRLG "need a bicycle" triggers across the
@ walkway (x=6) now stop the player until the Safari challenge is complete.
Route1_EastGate_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route1_EastGate_ARHU_OnTransition
	.byte 0

Route1_EastGate_ARHU_OnTransition::
	call_if_set FLAG_FERVOR_FIELD_SAFARI_CHALLENGE_COMPLETE, Route1_EastGate_ARHU_EventScript_OpenGate
	end

Route1_EastGate_ARHU_EventScript_OpenGate::
	setvar VAR_TEMP_1, 1
	return

Route1_EastGate_ARHU_EventScript_Guard::
	goto_if_set FLAG_FERVOR_FIELD_SAFARI_CHALLENGE_COMPLETE, Route1_EastGate_ARHU_EventScript_GuardOpen
	msgbox Route1_EastGate_ARHU_Text_RouteClosed, MSGBOX_NPC
	end

Route1_EastGate_ARHU_EventScript_GuardOpen::
	msgbox Route1_EastGate_ARHU_Text_RouteOpen, MSGBOX_NPC
	end

@ Player is walking west toward Route 1: send them back east, toward the city
Route1_EastGate_ARHU_EventScript_BlockTrigger::
	lockall
	msgbox Route1_EastGate_ARHU_Text_ExcuseMe
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Route1_EastGate_ARHU_Text_FinishChallengeFirst
	closemessage
	applymovement LOCALID_PLAYER, Route1_EastGate_ARHU_Movement_WalkRight
	waitmovement 0
	releaseall
	end

Route1_EastGate_ARHU_Movement_WalkRight::
	walk_right
	step_end

Route1_EastGate_ARHU_Text_ExcuseMe::
	.string "Excuse me!$"

Route1_EastGate_ARHU_Text_FinishChallengeFirst::
	.string "ROUTE 1 is closed to Trainers\n"
	.string "until the SAFARI challenge is over.\p"
	.string "Go find your partner first!$"

Route1_EastGate_ARHU_Text_RouteClosed::
	.string "Sorry, ROUTE 1 is closed while the\n"
	.string "SAFARI challenge is going on.\p"
	.string "Come back once you've finished!$"

Route1_EastGate_ARHU_Text_RouteOpen::
	.string "ROUTE 1 is just through here.\p"
	.string "Wild POKéMON hide in the tall grass,\n"
	.string "so keep your partner healthy!$"
