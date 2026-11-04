EarnestStateCampus_LectureHall_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_LectureHall_ARHU_EventScript_Professor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EARNEST_STATE_WISE_GLASSES, EarnestStateCampus_LectureHall_ARHU_EventScript_ProfessorAfter
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_ProfessorOfferQuiz, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_LectureHall_ARHU_EventScript_ProfessorDeclined
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuizQuestion1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_LectureHall_ARHU_EventScript_QuizWrong
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuizQuestion2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EarnestStateCampus_LectureHall_ARHU_EventScript_QuizWrong
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuizQuestion3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_LectureHall_ARHU_EventScript_QuizWrong
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuizPassed, MSGBOX_DEFAULT
	giveitem ITEM_WISE_GLASSES
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EARNEST_STATE_WISE_GLASSES
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_ExplainWiseGlasses, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_ProfessorDeclined::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_ProfessorDeclined, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_QuizWrong::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuizWrong, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_ProfessorAfter::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_ProfessorAfter, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_Quinn::
	lock
	faceplayer
	goto_if_defeated TRAINER_EARNEST_STATE_QUINN, EarnestStateCampus_LectureHall_ARHU_EventScript_QuinnAfter
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuinnChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_LectureHall_ARHU_EventScript_QuinnDeclined
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuinnIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_EARNEST_STATE_QUINN, EarnestStateCampus_LectureHall_ARHU_Text_QuinnDefeat
	goto EarnestStateCampus_LectureHall_ARHU_EventScript_QuinnAfter
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_QuinnDeclined::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuinnDeclined, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_QuinnAfter::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_QuinnAfter, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_LinkCableStudent::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_LinkCableStudent, MSGBOX_NPC
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_AbilityStudent::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_AbilityStudent, MSGBOX_NPC
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_StabStudent::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_StabStudent, MSGBOX_NPC
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_Blackboard::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_Blackboard, MSGBOX_SIGN
	end

EarnestStateCampus_LectureHall_ARHU_EventScript_Notebook::
	msgbox EarnestStateCampus_LectureHall_ARHU_Text_Notebook, MSGBOX_SIGN
	end

EarnestStateCampus_LectureHall_ARHU_Text_ProfessorOfferQuiz:
	.string "Ah, a visitor! Welcome to BATTLE\n"
	.string "THEORY 201. I'm PROFESSOR ROWE.\p"
	.string "Today's lesson: types and status\n"
	.string "conditions.\p"
	.string "Care to take my pop quiz?\n"
	.string "Three questions, true or false.$"

EarnestStateCampus_LectureHall_ARHU_Text_ProfessorDeclined:
	.string "No? The quiz will be here when\n"
	.string "you're ready. Knowledge never\l"
	.string "expires!$"

EarnestStateCampus_LectureHall_ARHU_Text_QuizQuestion1:
	.string "Question one! Answer YES for true.\p"
	.string "GROUND-type POKéMON are completely\n"
	.string "immune to ELECTRIC-type moves.\p"
	.string "True?$"

EarnestStateCampus_LectureHall_ARHU_Text_QuizQuestion2:
	.string "Correct! Question two!\p"
	.string "A burned POKéMON's SPECIAL moves\n"
	.string "deal only half damage.\p"
	.string "True?$"

EarnestStateCampus_LectureHall_ARHU_Text_QuizQuestion3:
	.string "Correct! A burn halves PHYSICAL\n"
	.string "damage, not special. Final one!\p"
	.string "STEEL-type POKéMON can't be\n"
	.string "poisoned by TOXIC.\p"
	.string "True?$"

EarnestStateCampus_LectureHall_ARHU_Text_QuizWrong:
	.string "Hmm, not quite!\p"
	.string "Review the blackboard, then come\n"
	.string "take the quiz again.$"

EarnestStateCampus_LectureHall_ARHU_Text_QuizPassed:
	.string "Correct! A perfect score!\p"
	.string "Every great scholar needs a good\n"
	.string "pair of glasses. Here!$"

EarnestStateCampus_LectureHall_ARHU_Text_ExplainWiseGlasses:
	.string "WISE GLASSES boost the power of a\n"
	.string "POKéMON's special moves.\p"
	.string "Think sharp, battle sharp!$"

EarnestStateCampus_LectureHall_ARHU_Text_ProfessorAfter:
	.string "Keep studying! A Trainer who knows\n"
	.string "their types can topple a stronger\l"
	.string "opponent.$"

EarnestStateCampus_LectureHall_ARHU_Text_QuinnChallenge:
	.string "I'm QUINN, the teaching assistant.\n"
	.string "I grade the professor's quizzes.\p"
	.string "But theory only goes so far, right?\p"
	.string "Want a dual-type lesson in action?\n"
	.string "Let's battle!$"

EarnestStateCampus_LectureHall_ARHU_Text_QuinnIntro:
	.string "Class is in session!$"

EarnestStateCampus_LectureHall_ARHU_Text_QuinnDeclined:
	.string "Skipping class, huh?\n"
	.string "Come back when you're ready.$"

EarnestStateCampus_LectureHall_ARHU_Text_QuinnDefeat:
	.string "Ouch… I need to re-read\n"
	.string "my own notes!$"

EarnestStateCampus_LectureHall_ARHU_Text_QuinnAfter:
	.string "Dual types can cancel weaknesses\n"
	.string "out… or stack them!\p"
	.string "LOTAD is WATER and GRASS, so FIRE\n"
	.string "moves only hit it normally.\p"
	.string "NUMEL is FIRE and GROUND, so WATER\n"
	.string "moves hit it four times as hard!$"

EarnestStateCampus_LectureHall_ARHU_Text_LinkCableStudent:
	.string "My thesis is on trade evolution.\p"
	.string "KADABRA, MACHOKE, GRAVELER and\n"
	.string "HAUNTER all evolve when traded.\p"
	.string "My roommate won't trade with me,\n"
	.string "though. He thinks I'll keep his\l"
	.string "MACHAMP!$"

EarnestStateCampus_LectureHall_ARHU_Text_AbilityStudent:
	.string "Some abilities work outside of\n"
	.string "battle, too.\p"
	.string "If the first POKéMON in your party\n"
	.string "has INTIMIDATE, weaker wild\l"
	.string "POKéMON will avoid you!$"

EarnestStateCampus_LectureHall_ARHU_Text_StabStudent:
	.string "When a POKéMON uses a move that\n"
	.string "matches its own type, it gets a\l"
	.string "power boost.\p"
	.string "It's called STAB: Same-Type Attack\n"
	.string "Bonus. That's 1.5 times the damage!$"

EarnestStateCampus_LectureHall_ARHU_Text_Blackboard:
	.string "Today's lecture: STATUS CONDITIONS\p"
	.string "BURN: Halves physical damage.\n"
	.string "FIRE types can't be burned.\p"
	.string "PARALYSIS: Lowers SPEED. ELECTRIC\n"
	.string "types can't be paralyzed.\p"
	.string "POISON: Damage every turn. POISON\n"
	.string "and STEEL types are immune.\p"
	.string "FREEZE: Can't move.\n"
	.string "ICE types can't be frozen.$"

EarnestStateCampus_LectureHall_ARHU_Text_Notebook:
	.string "A student's notebook…\p"
	.string "“NATURES raise one stat by 10% and\n"
	.string "lower another by 10%.\p"
	.string "ADAMANT: more ATTACK, less SP. ATK.\n"
	.string "TIMID: more SPEED, less ATTACK.”\p"
	.string "SKITTY doodles fill the margins.$"
