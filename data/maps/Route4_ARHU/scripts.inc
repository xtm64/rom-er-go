Route4_ARHU_MapScripts::
	.byte 0

@ Demo edge: the guard stops anyone who steps up to him or talks to him.
Route4_ARHU_EventScript_Guard::
	lockall
	faceplayer
	msgbox Route4_ARHU_Text_NoTrainersAllowed, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

Route4_ARHU_EventScript_GuardTrigger::
	lockall
	applymovement LOCALID_ROUTE4_ARHU_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE4_ARHU_GUARD, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox Route4_ARHU_Text_NoTrainersAllowed, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route4_ARHU_Movement_PushPlayerBack
	waitmovement 0
	releaseall
	end

Route4_ARHU_Movement_PushPlayerBack:
	walk_right
	step_end

Route4_ARHU_Text_NoTrainersAllowed:
	.string "Hold it right there, Trainer!\n"
	.string "We aren't allowing Trainers to pass\l"
	.string "right now.$"
