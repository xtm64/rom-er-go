@ Gate on Route 2, ported from Route18_EastEntrance_1F_Frlg. The road east stays closed for now:
@ the FRLG "need a bicycle" triggers across the walkway (x=6) always turn the player back.
@ To open it later, set VAR_TEMP_1 to 1 in an ON_TRANSITION script, as Route1_EastGate_ARHU does.
Route2_WestGate_ARHU_MapScripts::
	.byte 0

Route2_WestGate_ARHU_EventScript_Guard::
	msgbox Route2_WestGate_ARHU_Text_RoadClosed, MSGBOX_NPC
	end

@ Player is walking east toward Route 2: send them back west, toward the city
Route2_WestGate_ARHU_EventScript_BlockTrigger::
	lockall
	msgbox Route2_WestGate_ARHU_Text_ExcuseMe
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Route2_WestGate_ARHU_Text_RoadClosed
	closemessage
	applymovement LOCALID_PLAYER, Route2_WestGate_ARHU_Movement_WalkLeft
	waitmovement 0
	releaseall
	end

Route2_WestGate_ARHU_Movement_WalkLeft::
	walk_left
	step_end

Route2_WestGate_ARHU_Text_ExcuseMe::
	.string "Excuse me!$"

Route2_WestGate_ARHU_Text_RoadClosed::
	.string "Sorry, the road east is closed\n"
	.string "for now.\p"
	.string "Come back another time!$"
