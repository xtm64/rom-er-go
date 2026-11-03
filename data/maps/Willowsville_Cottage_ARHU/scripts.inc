Willowsville_Cottage_ARHU_MapScripts::
	.byte 0

Willowsville_Cottage_ARHU_EventScript_Neighbor::
	msgbox Willowsville_Cottage_ARHU_Text_Neighbor, MSGBOX_NPC
	end

Willowsville_Cottage_ARHU_EventScript_Bookshelf::
	msgbox Willowsville_Cottage_ARHU_Text_ShelvesCrammedFullOfBooks, MSGBOX_SIGN
	end

Willowsville_Cottage_ARHU_EventScript_Picture::
	msgbox Willowsville_Cottage_ARHU_Text_Picture, MSGBOX_SIGN
	end

Willowsville_Cottage_ARHU_Text_Neighbor::
	.string "Winters up here are long, so we\n"
	.string "keep the cottage warm and the\l"
	.string "kettle on.\p"
	.string "Westin's mom lives next door.\n"
	.string "She's always happy to see travelers.$"

Willowsville_Cottage_ARHU_Text_ShelvesCrammedFullOfBooks::
	.string "The shelves are crammed full of\n"
	.string "books on the north woods.$"

Willowsville_Cottage_ARHU_Text_Picture::
	.string "It's a framed photo of a frozen\n"
	.string "lake at sunrise.$"
