WillowRanch_ARHU_MapScripts::
	.byte 0

WillowRanch_ARHU_EventScript_Rancher::
	msgbox WillowRanch_ARHU_Text_Rancher, MSGBOX_NPC
	end

WillowRanch_ARHU_Text_Rancher::
	.string "Plant a berry in the soft soil and\n"
	.string "water it every day.\p"
	.string "Trees out here grow tall and sweet\n"
	.string "in the cold. Folks say apples too!$"

WillowRanch_ARHU_EventScript_DirectionsSign::
	msgbox WillowRanch_ARHU_Text_Directions, MSGBOX_SIGN
	end

WillowRanch_ARHU_Text_Directions::
	.string "EAST: WILLOW WOODS\n"
	.string "NORTH: WILLOW LAKE$"
