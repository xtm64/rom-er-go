EarnestStateCampus_CampusStore_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_CampusStore_ARHU_EventScript_Clerk::
	lock
	faceplayer
	msgbox EarnestStateCampus_CampusStore_ARHU_Text_ClerkWelcome, MSGBOX_DEFAULT
	message gText_HowMayIServeYou
	waitmessage
	pokemart EarnestStateCampus_CampusStore_ARHU_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
EarnestStateCampus_CampusStore_ARHU_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_SPEED
	.2byte ITEM_FRESH_WATER
	.2byte ITEM_SODA_POP
	.2byte ITEM_LEMONADE
	pokemartlistend

EarnestStateCampus_CampusStore_ARHU_EventScript_BusinessMajor::
	msgbox EarnestStateCampus_CampusStore_ARHU_Text_BusinessMajor, MSGBOX_NPC
	end

EarnestStateCampus_CampusStore_ARHU_EventScript_Student::
	msgbox EarnestStateCampus_CampusStore_ARHU_Text_Student, MSGBOX_NPC
	end

EarnestStateCampus_CampusStore_ARHU_EventScript_SnackShopper::
	msgbox EarnestStateCampus_CampusStore_ARHU_Text_SnackShopper, MSGBOX_NPC
	end

EarnestStateCampus_CampusStore_ARHU_Text_ClerkWelcome:
	.string "Welcome to the CAMPUS STORE!\p"
	.string "We're run entirely by students of\n"
	.string "the SMITH COLLEGE OF BUSINESS.$"

EarnestStateCampus_CampusStore_ARHU_Text_BusinessMajor:
	.string "My business plan: buy NUGGETS low,\n"
	.string "sell NUGGETS high.\p"
	.string "One problem… every shop buys them\n"
	.string "at exactly the same price!$"

EarnestStateCampus_CampusStore_ARHU_Text_Student:
	.string "Finals week survival kit:\p"
	.string "SODA POP, LEMONADE, and a POKéMON\n"
	.string "that knows REST.$"

EarnestStateCampus_CampusStore_ARHU_Text_SnackShopper:
	.string "SNORLAX would love this place.\p"
	.string "It isn't satisfied unless it eats\n"
	.string "over 880 pounds of food a day!$"
