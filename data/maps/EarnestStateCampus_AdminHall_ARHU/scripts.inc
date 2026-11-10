EarnestStateCampus_AdminHall_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_AdminHall_ARHU_EventScript_Receptionist::
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_Receptionist, MSGBOX_NPC
	end

EarnestStateCampus_AdminHall_ARHU_EventScript_Bursar::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EARNEST_STATE_AMULET_COIN, EarnestStateCampus_AdminHall_ARHU_EventScript_BursarAfter
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_BursarScholarship, MSGBOX_DEFAULT
	giveitem ITEM_AMULET_COIN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EARNEST_STATE_AMULET_COIN
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_BursarExplainAmuletCoin, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_AdminHall_ARHU_EventScript_BursarAfter::
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_BursarAfter, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_AdminHall_ARHU_EventScript_Dean::
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_Dean, MSGBOX_NPC
	end

EarnestStateCampus_AdminHall_ARHU_EventScript_StairGuard::
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_StairGuard, MSGBOX_NPC
	end

EarnestStateCampus_AdminHall_ARHU_EventScript_Freshman::
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_Freshman, MSGBOX_NPC
	end

EarnestStateCampus_AdminHall_ARHU_EventScript_TrophyCase::
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_TrophyCase, MSGBOX_SIGN
	end

EarnestStateCampus_AdminHall_ARHU_EventScript_Charter::
	msgbox EarnestStateCampus_AdminHall_ARHU_Text_Charter, MSGBOX_SIGN
	end

EarnestStateCampus_AdminHall_ARHU_Text_Receptionist:
	.string "Welcome to NEWSOM HALL, EARNEST\n"
	.string "STATE's administration building.\p"
	.string "Admissions are open year-round to\n"
	.string "Trainers of all ages.\p"
	.string "For financial aid, please see the\n"
	.string "BURSAR by the west wall.$"

EarnestStateCampus_AdminHall_ARHU_Text_BursarScholarship:
	.string "BURSAR's OFFICE. Let me pull up\n"
	.string "your account…\p"
	.string "{PLAYER}… {PLAYER}… Ah, there you\n"
	.string "are!\p"
	.string "You aren't enrolled, but the Board\n"
	.string "voted to award a Field Study\l"
	.string "Scholarship to visiting Trainers!\p"
	.string "It isn't money, exactly.\n"
	.string "It's something that MAKES money.$"

EarnestStateCampus_AdminHall_ARHU_Text_BursarExplainAmuletCoin:
	.string "Have a POKéMON hold that AMULET\n"
	.string "COIN, and you'll earn double the\l"
	.string "prize money from battles.\p"
	.string "Consider it an investment in your\n"
	.string "education!$"

EarnestStateCampus_AdminHall_ARHU_Text_BursarAfter:
	.string "Tuition is due at the end of the\n"
	.string "month… for students, anyway.\p"
	.string "Lucky you!$"

EarnestStateCampus_AdminHall_ARHU_Text_Dean:
	.string "I'm the DEAN of EARNEST STATE.\p"
	.string "Our motto is “Learn by battling,\n"
	.string "battle by learning.”\p"
	.string "Professors write about POKéMON,\n"
	.string "but Trainers live beside them.\l"
	.string "Both kinds of knowledge matter.\p"
	.string "If you have time, sit in on the\n"
	.string "lecture at WESLEY HALL.\p"
	.string "The professor loves a pop quiz.$"

EarnestStateCampus_AdminHall_ARHU_Text_StairGuard:
	.string "The REGISTRAR's office upstairs is\n"
	.string "closed for transcript season.\p"
	.string "Try back next semester!$"

EarnestStateCampus_AdminHall_ARHU_Text_Freshman:
	.string "I'm in line to declare my major…\p"
	.string "POKéMON Breeding? Battle Theory?\n"
	.string "BERRY Agriculture?\p"
	.string "They all sound amazing! How is\n"
	.string "anyone supposed to choose?$"

EarnestStateCampus_AdminHall_ARHU_Text_TrophyCase:
	.string "A trophy case. The biggest cup\n"
	.string "is engraved:\p"
	.string "“EARNEST STATE VARSITY BATTLE TEAM\n"
	.string "Collegiate Cup Champions”$"

EarnestStateCampus_AdminHall_ARHU_Text_Charter:
	.string "A framed charter, yellowed with age.\p"
	.string "“EARNEST STATE UNIVERSITY is hereby\n"
	.string "founded in the year 1887…\p"
	.string "…for the study of POKéMON, and of\n"
	.string "the people who love them.”$"
