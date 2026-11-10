Route3_ARHU_MapScripts::
	.byte 0

@ Demo edge: the guard stops anyone who steps up to him or talks to him.
Route3_ARHU_EventScript_Guard::
	lockall
	faceplayer
	msgbox Route3_ARHU_Text_NoTrainersAllowed, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

Route3_ARHU_EventScript_GuardTrigger::
	lockall
	applymovement LOCALID_ROUTE3_ARHU_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE3_ARHU_GUARD, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Route3_ARHU_Text_NoTrainersAllowed, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route3_ARHU_Movement_PushPlayerBack
	waitmovement 0
	releaseall
	end

Route3_ARHU_Movement_PushPlayerBack:
	walk_left
	step_end

Route3_ARHU_Text_NoTrainersAllowed:
	.string "Hold it right there, Trainer!\n"
	.string "We aren't allowing Trainers to pass\l"
	.string "right now.$"

Route3_ARHU_EventScript_DirectionsSign::
	msgbox Route3_ARHU_Text_Directions, MSGBOX_SIGN
	end

Route3_ARHU_Text_Directions::
	.string "WEST: EARNEST TOWNSHIP$"
