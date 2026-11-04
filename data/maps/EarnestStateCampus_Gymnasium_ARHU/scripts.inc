EarnestStateCampus_Gymnasium_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_Gymnasium_ARHU_EventScript_Tasha::
	trainerbattle_single TRAINER_EARNEST_STATE_TASHA, EarnestStateCampus_Gymnasium_ARHU_Text_TashaIntro, EarnestStateCampus_Gymnasium_ARHU_Text_TashaDefeat
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

EarnestStateCampus_Gymnasium_ARHU_EventScript_Darius::
	trainerbattle_single TRAINER_EARNEST_STATE_DARIUS, EarnestStateCampus_Gymnasium_ARHU_Text_DariusIntro, EarnestStateCampus_Gymnasium_ARHU_Text_DariusDefeat
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

EarnestStateCampus_Gymnasium_ARHU_EventScript_Malik::
	lock
	faceplayer
	goto_if_defeated TRAINER_EARNEST_STATE_MALIK, EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikAfterBattle
	goto_if_not_defeated TRAINER_EARNEST_STATE_TASHA, EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikNotYet
	goto_if_not_defeated TRAINER_EARNEST_STATE_DARIUS, EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikNotYet
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_MalikChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikDeclined
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_MalikIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_EARNEST_STATE_MALIK, EarnestStateCampus_Gymnasium_ARHU_Text_MalikDefeat
	goto EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikGiveMuscleBand
	end

EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikNotYet::
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_MalikNotYet, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikDeclined::
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_MalikDeclined, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikAfterBattle::
	goto_if_unset FLAG_RECEIVED_EARNEST_STATE_MUSCLE_BAND, EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikGiveMuscleBand
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_MalikAfter, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Gymnasium_ARHU_EventScript_MalikGiveMuscleBand::
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_MalikReward, MSGBOX_DEFAULT
	giveitem ITEM_MUSCLE_BAND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EARNEST_STATE_MUSCLE_BAND
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_ExplainMuscleBand, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Gymnasium_ARHU_EventScript_Coach::
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_Coach, MSGBOX_NPC
	end

EarnestStateCampus_Gymnasium_ARHU_EventScript_TrophyStatue::
	msgbox EarnestStateCampus_Gymnasium_ARHU_Text_TrophyStatue, MSGBOX_SIGN
	end

EarnestStateCampus_Gymnasium_ARHU_Text_TashaIntro:
	.string "Varsity tryouts are CLOSED!\n"
	.string "…Unless you can beat me!$"

EarnestStateCampus_Gymnasium_ARHU_Text_TashaDefeat:
	.string "Okay, okay!\n"
	.string "You've got the moves!$"

EarnestStateCampus_Gymnasium_ARHU_Text_TashaPostBattle:
	.string "MEDITITE trains its mind through\n"
	.string "meditation.\p"
	.string "It eats just one BERRY a day.\n"
	.string "Eating less is part of its training!$"

EarnestStateCampus_Gymnasium_ARHU_Text_DariusIntro:
	.string "Hoo-ah! Captain's orders: nobody\n"
	.string "passes without a sparring match!$"

EarnestStateCampus_Gymnasium_ARHU_Text_DariusDefeat:
	.string "Ugh! My form was sloppy!$"

EarnestStateCampus_Gymnasium_ARHU_Text_DariusPostBattle:
	.string "MACHOP works out by hefting a\n"
	.string "GRAVELER like a barbell.\p"
	.string "I tried it once. Only once.$"

EarnestStateCampus_Gymnasium_ARHU_Text_MalikNotYet:
	.string "You want to battle the captain?\p"
	.string "Get past TASHA and DARIUS first.\n"
	.string "That's how it works on this team.$"

EarnestStateCampus_Gymnasium_ARHU_Text_MalikChallenge:
	.string "So you got through TASHA and\n"
	.string "DARIUS. Not bad.\p"
	.string "I'm MALIK, captain of the EARNEST\n"
	.string "STATE Varsity Battle Team.\p"
	.string "We've won the Collegiate Cup three\n"
	.string "years running.\p"
	.string "Think you can break our streak?$"

EarnestStateCampus_Gymnasium_ARHU_Text_MalikDeclined:
	.string "Smart. Come back once you've\n"
	.string "trained a little more.$"

EarnestStateCampus_Gymnasium_ARHU_Text_MalikIntro:
	.string "Then show me what you've got!\n"
	.string "Full power!$"

EarnestStateCampus_Gymnasium_ARHU_Text_MalikDefeat:
	.string "…Hah! First loss in this gym all\n"
	.string "season.$"

EarnestStateCampus_Gymnasium_ARHU_Text_MalikReward:
	.string "You'd make one heck of a walk-on.\p"
	.string "Every member of the team earns one\n"
	.string "of these. You've earned it too.$"

EarnestStateCampus_Gymnasium_ARHU_Text_ExplainMuscleBand:
	.string "A MUSCLE BAND powers up physical\n"
	.string "moves.\p"
	.string "Put it on a POKéMON that hits hard,\n"
	.string "and watch it hit harder!$"

EarnestStateCampus_Gymnasium_ARHU_Text_MalikAfter:
	.string "RIOLU can see emotions like joy\n"
	.string "and anger as waves.\p"
	.string "It knew you'd win before I did.$"

EarnestStateCampus_Gymnasium_ARHU_Text_Coach:
	.string "I'm COACH BRIGGS. Welcome to\n"
	.string "WALKER GYMNASIUM!\p"
	.string "Beat my two starters, and the\n"
	.string "captain will take you on.\p"
	.string "And stay hydrated! FRESH WATER from\n"
	.string "the CAMPUS STORE works wonders.$"

EarnestStateCampus_Gymnasium_ARHU_Text_TrophyStatue:
	.string "EARNEST STATE VARSITY BATTLE TEAM\n"
	.string "Collegiate Cup Champions\p"
	.string "Captain: MALIK$"
