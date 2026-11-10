EarnestStateCampus_MediaCenter_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_MediaCenter_ARHU_EventScript_Remy::
	lock
	faceplayer
	goto_if_defeated TRAINER_EARNEST_STATE_REMY, EarnestStateCampus_MediaCenter_ARHU_EventScript_RemyAfterBattle
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_RemyChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_MediaCenter_ARHU_EventScript_RemyDeclined
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_RemyIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_EARNEST_STATE_REMY, EarnestStateCampus_MediaCenter_ARHU_Text_RemyDefeat
	goto EarnestStateCampus_MediaCenter_ARHU_EventScript_RemyGiveThroatSpray
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_RemyAfterBattle::
	goto_if_unset FLAG_RECEIVED_EARNEST_STATE_THROAT_SPRAY, EarnestStateCampus_MediaCenter_ARHU_EventScript_RemyGiveThroatSpray
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_RemyAfter, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_RemyGiveThroatSpray::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_RemyReward, MSGBOX_DEFAULT
	giveitem ITEM_THROAT_SPRAY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EARNEST_STATE_THROAT_SPRAY
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_ExplainThroatSpray, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_RemyDeclined::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_RemyDeclined, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_Reporter::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_Reporter, MSGBOX_NPC
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_Cameraman::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_Cameraman, MSGBOX_NPC
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_Producer::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_Producer, MSGBOX_NPC
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_BroadcastArchive::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_BroadcastArchive, MSGBOX_SIGN
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_RecordShelf::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_RecordShelf, MSGBOX_SIGN
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_FirstBroadcastPhoto::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_FirstBroadcastPhoto, MSGBOX_SIGN
	end

EarnestStateCampus_MediaCenter_ARHU_EventScript_GoldRecord::
	msgbox EarnestStateCampus_MediaCenter_ARHU_Text_GoldRecord, MSGBOX_SIGN
	end

EarnestStateCampus_MediaCenter_ARHU_Text_RemyChallenge:
	.string "Yo! REMY here, host of “Late Night\n"
	.string "Lo-Fi” on KEST 88.1!\p"
	.string "I'm running a sound check before\n"
	.string "tonight's show, and I need someone\l"
	.string "to test the levels.\p"
	.string "Wanna battle? Fair warning…\n"
	.string "my crew gets LOUD.$"

EarnestStateCampus_MediaCenter_ARHU_Text_RemyIntro:
	.string "Mic check, one, two…\n"
	.string "Let's GO!$"

EarnestStateCampus_MediaCenter_ARHU_Text_RemyDeclined:
	.string "No worries. Tune in at midnight!$"

EarnestStateCampus_MediaCenter_ARHU_Text_RemyDefeat:
	.string "Feedback! Total feedback!\n"
	.string "You blew out my speakers!$"

EarnestStateCampus_MediaCenter_ARHU_Text_RemyReward:
	.string "Best sound check ever. Here, this\n"
	.string "has been rattling around the booth.$"

EarnestStateCampus_MediaCenter_ARHU_Text_ExplainThroatSpray:
	.string "When a POKéMON holding THROAT SPRAY\n"
	.string "uses a sound move, its SP. ATK\l"
	.string "goes up. Then the spray is used up.\p"
	.string "Perfect for a WHISMUR with a set\n"
	.string "of pipes like mine!$"

EarnestStateCampus_MediaCenter_ARHU_Text_RemyAfter:
	.string "WHISMUR's voice is usually super\n"
	.string "quiet… until it gets startled.\p"
	.string "Then it cries loud enough to hurt\n"
	.string "your ears. That's my kind of DJ!$"

EarnestStateCampus_MediaCenter_ARHU_Text_Reporter:
	.string "I edit THE EARNEST LEDGER, the\n"
	.string "student paper.\p"
	.string "This week's headline: “CAMPUS\n"
	.string "ZIGZAGOON STEALS PROFESSOR'S\l"
	.string "LUNCH… AGAIN.”\p"
	.string "Hard-hitting journalism, I know.$"

EarnestStateCampus_MediaCenter_ARHU_Text_Cameraman:
	.string "We're filming a segment on the\n"
	.string "station's AZUMARILL.\p"
	.string "Its ears are so sharp, it hears our\n"
	.string "cue cards rustling. Every take!$"

EarnestStateCampus_MediaCenter_ARHU_Text_Producer:
	.string "Did you know CHATOT can learn human\n"
	.string "words?\p"
	.string "We tried to make one our station\n"
	.string "announcer.\p"
	.string "It just squawks “REQUESTS?\n"
	.string "REQUESTS?” all night long.$"

EarnestStateCampus_MediaCenter_ARHU_Text_Azumarill:
	.string "AZUMARILL: Rurii!\p"
	.string "Its long ears twitch. It can pick\n"
	.string "out tiny sounds, even in a fast,\l"
	.string "rough river.$"

EarnestStateCampus_MediaCenter_ARHU_Text_BroadcastArchive:
	.string "Shelves of old broadcast tapes.\p"
	.string "“Did You Know?” Episode 112:\n"
	.string "“EXPLOUD's bellowing is so loud,\l"
	.string "its tremors can trigger earthquakes!”$"

EarnestStateCampus_MediaCenter_ARHU_Text_RecordShelf:
	.string "Records of POKéMON cries, sorted\n"
	.string "alphabetically.\p"
	.string "“JIGGLYPUFF's Lullaby” has a label:\n"
	.string "“DO NOT PLAY DURING BROADCASTS.”$"

EarnestStateCampus_MediaCenter_ARHU_Text_FirstBroadcastPhoto:
	.string "A faded photo of KEST's very first\n"
	.string "broadcast.\p"
	.string "A JIGGLYPUFF is singing into the\n"
	.string "microphone… and everyone else in\l"
	.string "the picture is fast asleep.$"

EarnestStateCampus_MediaCenter_ARHU_Text_GoldRecord:
	.string "A framed gold record.\p"
	.string "“1,000,000 LISTENERS!\n"
	.string "Thank you, EARNEST!”$"
