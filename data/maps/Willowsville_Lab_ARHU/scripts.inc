Willowsville_Lab_ARHU_MapScripts::
	.byte 0

@ The researcher rewards trainers who made the long trip north: a Rare Candy and TM Rock Tomb, once each
Willowsville_Lab_ARHU_EventScript_Researcher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WILLOWSVILLE_RARE_CANDY, Willowsville_Lab_ARHU_EventScript_CheckTM
	msgbox Willowsville_Lab_ARHU_Text_NotManyVisitors, MSGBOX_DEFAULT
	checkitemspace ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, Willowsville_Lab_ARHU_EventScript_BagFull
	giveitem ITEM_RARE_CANDY
	setflag FLAG_RECEIVED_WILLOWSVILLE_RARE_CANDY
	goto Willowsville_Lab_ARHU_EventScript_CheckTM
	end

Willowsville_Lab_ARHU_EventScript_CheckTM::
	goto_if_set FLAG_RECEIVED_WILLOWSVILLE_TM_ROCK_TOMB, Willowsville_Lab_ARHU_EventScript_AlreadyGaveAll
	msgbox Willowsville_Lab_ARHU_Text_TakeThisTooRockTomb, MSGBOX_DEFAULT
	checkitemspace ITEM_TM_ROCK_TOMB
	goto_if_eq VAR_RESULT, FALSE, Willowsville_Lab_ARHU_EventScript_BagFull
	giveitem ITEM_TM_ROCK_TOMB
	setflag FLAG_RECEIVED_WILLOWSVILLE_TM_ROCK_TOMB
	msgbox Willowsville_Lab_ARHU_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

Willowsville_Lab_ARHU_EventScript_AlreadyGaveAll::
	msgbox Willowsville_Lab_ARHU_Text_StayWarm, MSGBOX_DEFAULT
	release
	end

Willowsville_Lab_ARHU_EventScript_BagFull::
	msgbox Willowsville_Lab_ARHU_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Willowsville_Lab_ARHU_EventScript_Aide1::
	msgbox Willowsville_Lab_ARHU_Text_Aide1, MSGBOX_NPC
	end

Willowsville_Lab_ARHU_EventScript_Aide2::
	msgbox Willowsville_Lab_ARHU_Text_Aide2, MSGBOX_NPC
	end

Willowsville_Lab_ARHU_EventScript_Aide3::
	msgbox Willowsville_Lab_ARHU_Text_Aide3, MSGBOX_NPC
	end

Willowsville_Lab_ARHU_EventScript_Computer::
	msgbox Willowsville_Lab_ARHU_Text_Computer, MSGBOX_SIGN
	end

Willowsville_Lab_ARHU_EventScript_Bookshelf::
	msgbox Willowsville_Lab_ARHU_Text_Bookshelf, MSGBOX_SIGN
	end

Willowsville_Lab_ARHU_Text_NotManyVisitors::
	.string "Well, well! A visitor!\p"
	.string "We don't see many Trainers this far\n"
	.string "north. It's a long road.\p"
	.string "Anyone who makes the trip deserves\n"
	.string "a little something.\p"
	.string "Here, take this.$"

Willowsville_Lab_ARHU_Text_TakeThisTooRockTomb::
	.string "And one more thing.\p"
	.string "I found this TM while surveying the\n"
	.string "rocky ground around the lakes.$"

Willowsville_Lab_ARHU_Text_ExplainRockTomb::
	.string "That's ROCK TOMB.\p"
	.string "It hurls rocks at the foe and\n"
	.string "slows it down. Handy against\l"
	.string "flying POKéMON!$"

Willowsville_Lab_ARHU_Text_StayWarm::
	.string "Stay warm out there, and keep\n"
	.string "exploring!$"

Willowsville_Lab_ARHU_Text_BagFull::
	.string "Your BAG is full.\n"
	.string "Make some room and come back.$"

Willowsville_Lab_ARHU_Text_Aide1::
	.string "The professor studies POKéMON that\n"
	.string "live in the cold north woods.$"

Willowsville_Lab_ARHU_Text_Aide2::
	.string "I'm cataloguing the berries and\n"
	.string "apples that grow around here.$"

Willowsville_Lab_ARHU_Text_Aide3::
	.string "It's cold outside, but the lab is\n"
	.string "always warm.$"

Willowsville_Lab_ARHU_Text_Computer::
	.string "It's logging field data from the\n"
	.string "northern forests.$"

Willowsville_Lab_ARHU_Text_Bookshelf::
	.string "The shelves hold research notes on\n"
	.string "northern POKéMON.$"
