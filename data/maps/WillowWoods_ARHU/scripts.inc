WillowWoods_ARHU_MapScripts::
	.byte 0

WillowWoods_ARHU_EventScript_Boy::
	msgbox WillowWoods_ARHU_Text_Boy, MSGBOX_NPC
	end

WillowWoods_ARHU_EventScript_OrchardGirl::
	msgbox WillowWoods_ARHU_Text_OrchardGirl, MSGBOX_NPC
	end

WillowWoods_ARHU_EventScript_EntranceSign::
	msgbox WillowWoods_ARHU_Text_EntranceSign, MSGBOX_SIGN
	end

WillowWoods_ARHU_EventScript_OrchardSign::
	msgbox WillowWoods_ARHU_Text_OrchardSign, MSGBOX_SIGN
	end

WillowWoods_ARHU_Text_Boy::
	.string "I heard a huge bear lives deep in\n"
	.string "these woods.\p"
	.string "Nobody I know has ever seen it\n"
	.string "up close…$"

WillowWoods_ARHU_Text_OrchardGirl::
	.string "My family tends the apple orchard\n"
	.string "up here.\p"
	.string "The sweet smell draws POKéMON out\n"
	.string "of the trees. Watch your step!$"

WillowWoods_ARHU_Text_EntranceSign::
	.string "WILLOW WOODS\n"
	.string "Beware the bears. Stay on the path.$"

WillowWoods_ARHU_Text_OrchardSign::
	.string "WILLOW ORCHARD\n"
	.string "Please don't pick the apples!$"

WillowWoods_ARHU_EventScript_DirectionsSign::
	msgbox WillowWoods_ARHU_Text_Directions, MSGBOX_SIGN
	end

WillowWoods_ARHU_Text_Directions::
	.string "SOUTH: WILLOWSVILLE\n"
	.string "NORTH: WILLOW RANCH$"
