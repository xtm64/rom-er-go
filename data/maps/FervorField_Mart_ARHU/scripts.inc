FervorField_Mart_ARHU_MapScripts::
	.byte 0

FervorField_Mart_ARHU_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FervorField_Mart_ARHU_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FervorField_Mart_ARHU_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	pokemartlistend

FervorField_Mart_ARHU_EventScript_Woman::
	msgbox FervorField_Mart_ARHU_Text_ImGoingToBuyPokeBalls, MSGBOX_NPC
	end

FervorField_Mart_ARHU_EventScript_Boy::
	msgbox FervorField_Mart_ARHU_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

FervorField_Mart_ARHU_Text_ImGoingToBuyPokeBalls:
	.string "I'm going to buy a bunch of POKé BALLS\n"
	.string "and catch a bunch of POKéMON!$"

FervorField_Mart_ARHU_Text_RestoreHPWithPotion:
	.string "If a POKéMON gets hurt and loses its HP\n"
	.string "and faints, it won't be able to battle.\p"
	.string "To prevent your POKéMON from fainting,\n"
	.string "restore its HP with a POTION.$"
