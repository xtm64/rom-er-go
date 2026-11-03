WillowLake_ARHU_MapScripts::
	.byte 0

WillowLake_ARHU_EventScript_Fisherman::
	msgbox WillowLake_ARHU_Text_Fisherman, MSGBOX_NPC
	end

WillowLake_ARHU_EventScript_Sign::
	msgbox WillowLake_ARHU_Text_Sign, MSGBOX_SIGN
	end

WillowLake_ARHU_Text_Fisherman::
	.string "See those little islands out in\n"
	.string "the lake?\p"
	.string "Odd birds nest out there. I've seen\n"
	.string "one carrying a leek stalk!\p"
	.string "You'd need a way to cross the\n"
	.string "water to find out.$"

WillowLake_ARHU_Text_Sign::
	.string "WILLOW LAKE\n"
	.string "No swimming past the sandbars.$"
