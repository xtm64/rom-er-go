Willowsville_WestinsHouse_2F_ARHU_MapScripts::
	.byte 0

Willowsville_WestinsHouse_2F_ARHU_EventScript_NES::
	msgbox Willowsville_WestinsHouse_2F_ARHU_Text_PlayedWithNES, MSGBOX_SIGN
	end

Willowsville_WestinsHouse_2F_ARHU_EventScript_Sign::
	msgbox Willowsville_WestinsHouse_2F_ARHU_Text_PressLRForHelp, MSGBOX_SIGN
	end

Willowsville_WestinsHouse_2F_ARHU_Text_PlayedWithNES::
	.string "{PLAYER} played with the NES.\p"
	.string "…Okay!\n"
	.string "It's time to go!$"

Willowsville_WestinsHouse_2F_ARHU_Text_PressLRForHelp::
	.string "It's a posted notice…\p"
	.string "If you're confused, ask for HELP!\n"
	.string "Press the L or R Button!$"
