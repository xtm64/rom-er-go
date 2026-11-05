@ Ported from PalletTown_Frlg. The FRLG Oak, sign lady and house/lab content was dropped
@ (their buildings aren't built for Fervor yet); only the town sign, trainer tips sign and a bystander remain.

Willowsville_ARHU_MapScripts::
	.byte 0

Willowsville_ARHU_EventScript_FatMan::
	msgbox Willowsville_ARHU_Text_CanStoreItemsAndMonsInPC, MSGBOX_NPC
	end

Willowsville_ARHU_EventScript_WestinsHouseSign::
	msgbox Willowsville_ARHU_Text_WestinsHouse, MSGBOX_SIGN
	end

Willowsville_ARHU_EventScript_CottageSign::
	msgbox Willowsville_ARHU_Text_Cottage, MSGBOX_SIGN
	end

Willowsville_ARHU_EventScript_LabSign::
	msgbox Willowsville_ARHU_Text_Lab, MSGBOX_SIGN
	end

Willowsville_ARHU_EventScript_TownSign::
	msgbox Willowsville_ARHU_Text_TownSign, MSGBOX_SIGN
	end

Willowsville_ARHU_EventScript_TrainerTips::
	msgbox Willowsville_ARHU_Text_PressStartToOpenMenu, MSGBOX_SIGN
	end

Willowsville_ARHU_Text_CanStoreItemsAndMonsInPC::
	.string "Technology is incredible!\p"
	.string "You can now store and recall items\n"
	.string "and POKéMON as data via PC.$"

Willowsville_ARHU_Text_WestinsHouse::
	.string "WESTIN's house$"

Willowsville_ARHU_Text_Cottage::
	.string "WILLOWSVILLE COTTAGE\n"
	.string "“Kettle's always on.”$"

Willowsville_ARHU_Text_Lab::
	.string "WILLOWSVILLE FIELD LAB\n"
	.string "Northern POKéMON Research$"

Willowsville_ARHU_Text_TownSign::
	.string "WILLOWSVILLE\n"
	.string "Where the willows whisper!$"

Willowsville_ARHU_Text_PressStartToOpenMenu::
	.string "TRAINER TIPS\p"
	.string "Press START to open the MENU!$"

Willowsville_ARHU_EventScript_DirectionsSign::
	msgbox Willowsville_ARHU_Text_Directions, MSGBOX_SIGN
	end

Willowsville_ARHU_Text_Directions::
	.string "SOUTH: ROUTE 2 NORTH\n"
	.string "WEST: WILLOW WOODS$"
