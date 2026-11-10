@ Gate at the south end of the Route 1 Cycling Road. Copied from Route110_SeasideCyclingRoadSouthEntrance.
@ The clerk's bike check stops anyone without a bike from walking in.
Route1_CyclingRoad_SouthGate_ARHU_MapScripts::
	.byte 0

Route1_CyclingRoad_SouthGate_ARHU_EventScript_Clerk::
	lock
	faceplayer
	msgbox Route1_CyclingRoad_SouthGate_ARHU_Text_GoAllOutOnCyclingRoad, MSGBOX_DEFAULT
	release
	end

Route1_CyclingRoad_SouthGate_ARHU_EventScript_BikeCheck::
	lockall
	specialvar VAR_RESULT, GetPlayerAvatarBike
	goto_if_eq VAR_RESULT, 0, Route1_CyclingRoad_SouthGate_ARHU_EventScript_NoBike
	setflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 1
	releaseall
	end

Route1_CyclingRoad_SouthGate_ARHU_EventScript_NoBike::
	msgbox Route1_CyclingRoad_SouthGate_ARHU_Text_TooDangerousToWalk, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Route1_CyclingRoad_SouthGate_ARHU_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

Route1_CyclingRoad_SouthGate_ARHU_Movement_PushPlayerBackFromCounter:
	walk_left
	step_end

Route1_CyclingRoad_SouthGate_ARHU_EventScript_ClearCyclingRoad::
	lockall
	clearflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route1_CyclingRoad_SouthGate_ARHU_Text_GoAllOutOnCyclingRoad:
	.string "On CYCLING ROAD, you can go all out\n"
	.string "and cycle as fast as you'd like.\p"
	.string "It feels great to go that fast, but try\n"
	.string "not to crash into anyone!$"

Route1_CyclingRoad_SouthGate_ARHU_Text_TooDangerousToWalk:
	.string "Sorry, you can't walk on CYCLING\n"
	.string "ROAD. It's too dangerous.\p"
	.string "Please come back with a BIKE.$"
