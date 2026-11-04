Earnest_Mart_ARHU_MapScripts::
	.byte 0

Earnest_Mart_ARHU_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Earnest_Mart_ARHU_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Earnest_Mart_ARHU_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_HARBOR_MAIL
	pokemartlistend

Earnest_Mart_ARHU_EventScript_BlackBelt::
	msgbox Earnest_Mart_ARHU_Text_SomeItemsOnlyAtMart, MSGBOX_NPC
	end

Earnest_Mart_ARHU_EventScript_Man::
	msgbox Earnest_Mart_ARHU_Text_GreatBallIsBetter, MSGBOX_NPC
	end

Earnest_Mart_ARHU_Text_SomeItemsOnlyAtMart:
	.string "The MARKET does have some interesting\n"
	.string "merchandise.\p"
	.string "But there are some items you can only\n"
	.string "get at a POKéMON MART.$"

Earnest_Mart_ARHU_Text_GreatBallIsBetter:
	.string "A GREAT BALL is better than a POKé BALL\n"
	.string "at catching POKéMON.\p"
	.string "With this, I should be able to get that\n"
	.string "elusive POKéMON…$"

