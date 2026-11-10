Earnest_Gym_ARHU_MapScripts::
	.byte 0

Earnest_Gym_ARHU_EventScript_Thresh::
	trainerbattle_single TRAINER_EARNEST_GYM_THRESH, Earnest_Gym_ARHU_Text_ThreshIntro, Earnest_Gym_ARHU_Text_ThreshDefeat, Earnest_Gym_ARHU_EventScript_ThreshDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_HM_ROCK_SMASH, Earnest_Gym_ARHU_EventScript_GiveRockSmash
	msgbox Earnest_Gym_ARHU_Text_ThreshPostBattle, MSGBOX_DEFAULT
	release
	end

Earnest_Gym_ARHU_EventScript_ThreshDefeated::
	goto_if_set FLAG_BADGE01_GET, Earnest_Gym_ARHU_EventScript_ThreshDefeatedHasBadge
	message Earnest_Gym_ARHU_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox Earnest_Gym_ARHU_Text_BadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_BADGE01_GET
	setvar VAR_EARNEST_GYM_RIVAL_STATE, 1
	goto Earnest_Gym_ARHU_EventScript_GiveRockSmash
	end

@ The DOJO BADGE was already won on stage under the Fervor Accord (Earnest_ContestHall_ARHU).
Earnest_Gym_ARHU_EventScript_ThreshDefeatedHasBadge::
	msgbox Earnest_Gym_ARHU_Text_ThreshBothRoads, MSGBOX_DEFAULT
	setvar VAR_EARNEST_GYM_RIVAL_STATE, 1
	goto_if_unset FLAG_RECEIVED_HM_ROCK_SMASH, Earnest_Gym_ARHU_EventScript_GiveRockSmash
	release
	end

Earnest_Gym_ARHU_EventScript_GiveRockSmash::
	giveitem ITEM_HM06
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	msgbox Earnest_Gym_ARHU_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

Earnest_Gym_ARHU_EventScript_Harlan::
	trainerbattle_single TRAINER_EARNEST_GYM_HARLAN, Earnest_Gym_ARHU_Text_HarlanIntro, Earnest_Gym_ARHU_Text_HarlanDefeat
	msgbox Earnest_Gym_ARHU_Text_HarlanPostBattle, MSGBOX_AUTOCLOSE
	end

Earnest_Gym_ARHU_EventScript_Kaia::
	trainerbattle_single TRAINER_EARNEST_GYM_KAIA, Earnest_Gym_ARHU_Text_KaiaIntro, Earnest_Gym_ARHU_Text_KaiaDefeat
	msgbox Earnest_Gym_ARHU_Text_KaiaPostBattle, MSGBOX_AUTOCLOSE
	end

Earnest_Gym_ARHU_EventScript_Isamu::
	trainerbattle_single TRAINER_EARNEST_GYM_ISAMU, Earnest_Gym_ARHU_Text_IsamuIntro, Earnest_Gym_ARHU_Text_IsamuDefeat
	msgbox Earnest_Gym_ARHU_Text_IsamuPostBattle, MSGBOX_AUTOCLOSE
	end

Earnest_Gym_ARHU_EventScript_Guide::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, Earnest_Gym_ARHU_EventScript_GuidePostVictory
	msgbox Earnest_Gym_ARHU_Text_GuideAdvice, MSGBOX_DEFAULT
	release
	end

Earnest_Gym_ARHU_EventScript_GuidePostVictory::
	msgbox Earnest_Gym_ARHU_Text_GuidePostVictory, MSGBOX_DEFAULT
	release
	end

Earnest_Gym_ARHU_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, Earnest_Gym_ARHU_EventScript_GymStatueCertified
	msgbox Earnest_Gym_ARHU_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

Earnest_Gym_ARHU_EventScript_GymStatueCertified::
	msgbox Earnest_Gym_ARHU_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

Earnest_Gym_ARHU_Text_ThreshIntro:
	.string "I competed for many years before\n"
	.string "I hung up my belt.\p"
	.string "The loudest fighters I faced were\n"
	.string "rarely the ones left standing.\p"
	.string "Strength is not the question.\n"
	.string "Are you calm enough to use it?\p"
	.string "I am THRESH. Show me your clarity.$"

Earnest_Gym_ARHU_Text_ThreshDefeat:
	.string "Hm. You stayed composed even when\n"
	.string "the fight turned against you.\p"
	.string "That is worth more than power.$"

Earnest_Gym_ARHU_Text_ReceivedBadge:
	.string "{PLAYER} received the DOJO BADGE\n"
	.string "from THRESH.$"

Earnest_Gym_ARHU_Text_ThreshBothRoads:
	.string "You already carry my BADGE.\n"
	.string "I signed it for the CONTEST HALL.\p"
	.string "You won over a crowd, and now\n"
	.string "you have stood against me as well.\p"
	.string "Two roads, one destination.\n"
	.string "Few walk both. Be proud of it.$"

Earnest_Gym_ARHU_Text_BadgeInfoTakeThis:
	.string "The DOJO BADGE lets your POKéMON\n"
	.string "use ROCK SMASH outside of battle.\p"
	.string "Take this as well.$"

Earnest_Gym_ARHU_Text_ExplainRockSmash:
	.string "That is HM06, ROCK SMASH.\p"
	.string "Cracked rocks can hide paths that\n"
	.string "the hurried never notice.\p"
	.string "Use it patiently. The rocky country\n"
	.string "ahead will not forgive carelessness.$"

Earnest_Gym_ARHU_Text_ThreshPostBattle:
	.string "Discipline over recklessness.\n"
	.string "Clarity over arrogance.\p"
	.string "Carry both with you and you will go\n"
	.string "farther than raw strength allows.$"

Earnest_Gym_ARHU_Text_HarlanIntro:
	.string "ENDURANCE is the first lesson.\p"
	.string "I can take any hit you throw!$"

Earnest_Gym_ARHU_Text_HarlanDefeat:
	.string "I couldn't outlast you...$"

Earnest_Gym_ARHU_Text_HarlanPostBattle:
	.string "Standing back up is the hardest\n"
	.string "technique to master.$"

Earnest_Gym_ARHU_Text_KaiaIntro:
	.string "INITIATIVE is the second lesson.\p"
	.string "The one who moves first sets the\n"
	.string "rhythm of the fight!$"

Earnest_Gym_ARHU_Text_KaiaDefeat:
	.string "You read me before I even moved!$"

Earnest_Gym_ARHU_Text_KaiaPostBattle:
	.string "Being fast isn't enough.\n"
	.string "You have to move with a purpose.$"

Earnest_Gym_ARHU_Text_IsamuIntro:
	.string "PRECISION is the third lesson.\p"
	.string "One clean strike beats a hundred\n"
	.string "wild ones.$"

Earnest_Gym_ARHU_Text_IsamuDefeat:
	.string "My aim was off...$"

Earnest_Gym_ARHU_Text_IsamuPostBattle:
	.string "Master THRESH is just beyond this\n"
	.string "point. Stay calm and watch him.$"

Earnest_Gym_ARHU_Text_GuideAdvice:
	.string "Welcome to the dojo, challenger.\p"
	.string "THRESH, the GYM LEADER, is a\n"
	.string "retired martial artist who uses\l"
	.string "FIGHTING-type POKéMON.\p"
	.string "FIGHTING types hit hard, but they\n"
	.string "are weak against FLYING-type and\l"
	.string "PSYCHIC-type moves.\p"
	.string "Three students guard the way, each\n"
	.string "teaching a lesson: endurance,\l"
	.string "initiative and precision.\p"
	.string "Don't rush the fights. THRESH\n"
	.string "punishes recklessness.$"

Earnest_Gym_ARHU_Text_GuidePostVictory:
	.string "You beat THRESH?\n"
	.string "That was a calm, clear victory!$"

Earnest_Gym_ARHU_Text_GymStatue:
	.string "EARNEST TOWNSHIP POKéMON GYM\n"
	.string "LEADER: THRESH$"

Earnest_Gym_ARHU_Text_GymStatueCertified:
	.string "EARNEST TOWNSHIP POKéMON GYM\n"
	.string "LEADER: THRESH\p"
	.string "CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"
