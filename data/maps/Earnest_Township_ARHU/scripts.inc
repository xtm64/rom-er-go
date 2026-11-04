Earnest_Township_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Earnest_Township_ARHU_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Earnest_Township_ARHU_OnFrame
	.byte 0

Earnest_Township_ARHU_OnTransition:
	setflag FLAG_HIDE_EARNEST_TOWNSHIP_RIVAL
	setflag FLAG_HIDE_EARNEST_TOWNSHIP_THRESH
	setvar VAR_CONTEST_HALL_STATE, 0
	end

Earnest_Township_ARHU_OnFrame:
	map_script_2 VAR_EARNEST_GYM_RIVAL_STATE, 1, Earnest_Township_ARHU_EventScript_GymRival
	.2byte 0

@ Fires on the first frame after the player leaves the gym with the badge. Westin waits at (38,27), the player
@ stands at (38,25) and Thresh watches from the open gym door at (38,24).
Earnest_Township_ARHU_EventScript_GymRival::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8005, 24, Earnest_Township_ARHU_EventScript_GymRival_PlayerStepDown
	clearflag FLAG_HIDE_EARNEST_TOWNSHIP_RIVAL
	addobject LOCALID_EARNEST_TOWNSHIP_RIVAL
	applymovement LOCALID_EARNEST_TOWNSHIP_RIVAL, Common_Movement_ExclamationMark
	waitmovement LOCALID_EARNEST_TOWNSHIP_RIVAL
	applymovement LOCALID_EARNEST_TOWNSHIP_RIVAL, Earnest_Township_ARHU_Movement_RivalApproach
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	msgbox Earnest_Township_ARHU_Text_Westin_Challenge, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_FERVOR_FIELD_RIVAL_NO_WHITEOUT
	goto_if_eq VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_SQUIRTLE, Earnest_Township_ARHU_EventScript_GymRival_BattleSquirtle
	goto_if_eq VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_SPRIGATITO, Earnest_Township_ARHU_EventScript_GymRival_BattleSprigatito
	trainerbattle_no_intro TRAINER_EARNEST_GYM_WESTIN_CHIMCHAR, Earnest_Township_ARHU_Text_Westin_Defeat
	goto Earnest_Township_ARHU_EventScript_GymRival_AfterBattle
	end

Earnest_Township_ARHU_EventScript_GymRival_PlayerStepDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	waitmovement LOCALID_PLAYER
	return

Earnest_Township_ARHU_EventScript_GymRival_BattleSquirtle::
	trainerbattle_no_intro TRAINER_EARNEST_GYM_WESTIN_SQUIRTLE, Earnest_Township_ARHU_Text_Westin_Defeat
	goto Earnest_Township_ARHU_EventScript_GymRival_AfterBattle
	end

Earnest_Township_ARHU_EventScript_GymRival_BattleSprigatito::
	trainerbattle_no_intro TRAINER_EARNEST_GYM_WESTIN_SPRIGATITO, Earnest_Township_ARHU_Text_Westin_Defeat
	goto Earnest_Township_ARHU_EventScript_GymRival_AfterBattle
	end

Earnest_Township_ARHU_EventScript_GymRival_AfterBattle::
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_0x8009, VAR_RESULT
	clearflag FLAG_FERVOR_FIELD_RIVAL_NO_WHITEOUT
	special HealPlayerParty
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	call_if_eq VAR_0x8009, B_OUTCOME_WON, Earnest_Township_ARHU_EventScript_GymRival_PlayerWon
	call_if_ne VAR_0x8009, B_OUTCOME_WON, Earnest_Township_ARHU_EventScript_GymRival_PlayerLost
	opendoor 38, 24
	waitdooranim
	clearflag FLAG_HIDE_EARNEST_TOWNSHIP_THRESH
	addobject LOCALID_EARNEST_TOWNSHIP_THRESH
	playse SE_PIN
	applymovement LOCALID_EARNEST_TOWNSHIP_THRESH, Common_Movement_ExclamationMark
	waitmovement LOCALID_EARNEST_TOWNSHIP_THRESH
	msgbox Earnest_Township_ARHU_Text_Thresh_Observes, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EARNEST_TOWNSHIP_RIVAL, Common_Movement_FaceUp
	waitmovement LOCALID_EARNEST_TOWNSHIP_RIVAL
	msgbox Earnest_Township_ARHU_Text_Westin_Parting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EARNEST_TOWNSHIP_RIVAL, Earnest_Township_ARHU_Movement_RivalRunsOff
	waitmovement LOCALID_EARNEST_TOWNSHIP_RIVAL
	removeobject LOCALID_EARNEST_TOWNSHIP_RIVAL
	setflag FLAG_HIDE_EARNEST_TOWNSHIP_RIVAL
	msgbox Earnest_Township_ARHU_Text_Thresh_ToPlayer, MSGBOX_DEFAULT
	closemessage
	removeobject LOCALID_EARNEST_TOWNSHIP_THRESH
	setflag FLAG_HIDE_EARNEST_TOWNSHIP_THRESH
	closedoor 38, 24
	waitdooranim
	setvar VAR_EARNEST_GYM_RIVAL_STATE, 2
	releaseall
	end

Earnest_Township_ARHU_EventScript_GymRival_PlayerWon::
	msgbox Earnest_Township_ARHU_Text_Westin_Lost, MSGBOX_DEFAULT
	closemessage
	return

Earnest_Township_ARHU_EventScript_GymRival_PlayerLost::
	msgbox Earnest_Township_ARHU_Text_Westin_Won, MSGBOX_DEFAULT
	closemessage
	return

Earnest_Township_ARHU_Movement_RivalApproach:
	walk_up
	step_end

Earnest_Township_ARHU_Movement_RivalRunsOff:
	walk_fast_down
	walk_fast_down
	step_end

Earnest_Township_ARHU_Text_Westin_Challenge:
	.string "Westin: Hey! {PLAYER}!\p"
	.string "So you actually beat the GYM LEADER.\n"
	.string "I saw the BADGE from over here.\p"
	.string "I've been training nonstop, and I\n"
	.string "want to see how far I've come.\p"
	.string "Let's battle!$"

Earnest_Township_ARHU_Text_Westin_Defeat:
	.string "Westin: What?! Again?!$"

Earnest_Township_ARHU_Text_Westin_Lost:
	.string "Westin: Tch… I lost.\p"
	.string "Fine. That just means I haven't\n"
	.string "trained hard enough yet.\p"
	.string "More battles, more hours, no days\n"
	.string "off. That's all it takes!$"

Earnest_Township_ARHU_Text_Westin_Won:
	.string "Westin: Yes! I won!\p"
	.string "That was too close, though.\p"
	.string "If I'd just pushed a little harder,\n"
	.string "it wouldn't have been close at all.\p"
	.string "I'll keep working harder. That's\n"
	.string "the answer to everything!$"

Earnest_Township_ARHU_Text_Thresh_Observes:
	.string "Thresh: That boy has plenty of drive.\p"
	.string "He simply hasn't learned where to\n"
	.string "direct it.$"

Earnest_Township_ARHU_Text_Westin_Parting:
	.string "Westin: Huh? Direct it?\p"
	.string "…Whatever. I'll just train harder\n"
	.string "than anyone. See you around!$"

Earnest_Township_ARHU_Text_Thresh_ToPlayer:
	.string "Thresh: Effort is a fine thing.\n"
	.string "Aimed well, it becomes strength.\p"
	.string "Walk carefully, {PLAYER}. Your\n"
	.string "ROCK SMASH may open new paths.$"

Earnest_Township_ARHU_EventScript_FatMan::
	msgbox Earnest_Township_ARHU_Text_ForestAllAround, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_Man1::
	msgbox Earnest_Township_ARHU_Text_GymLeaderTough, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_RichBoy::
	msgbox Earnest_Township_ARHU_Text_ContestHallOpening, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_Woman1::
	msgbox Earnest_Township_ARHU_Text_GymBadges, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_Cook::
	msgbox Earnest_Township_ARHU_Text_GoodFood, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_OldWoman::
	msgbox Earnest_Township_ARHU_Text_TownHistory, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_Girl::
	msgbox Earnest_Township_ARHU_Text_QuietTown, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_PokefanF::
	msgbox Earnest_Township_ARHU_Text_ShopsAreGood, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_Man2::
	msgbox Earnest_Township_ARHU_Text_GatesClosed, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_Maniac::
	msgbox Earnest_Township_ARHU_Text_GetNameRaterToHelpYou, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_Woman2::
	msgbox Earnest_Township_ARHU_Text_CantChangeTradeMonName, MSGBOX_NPC
	end

Earnest_Township_ARHU_EventScript_NameRatersHouseSign::
	msgbox Earnest_Township_ARHU_Text_NameRatersHouseSign, MSGBOX_SIGN
	end

Earnest_Township_ARHU_EventScript_GymSign::
	msgbox Earnest_Township_ARHU_Text_GymSign, MSGBOX_SIGN
	end

Earnest_Township_ARHU_EventScript_CitySign::
	msgbox Earnest_Township_ARHU_Text_CitySign, MSGBOX_SIGN
	end

Earnest_Township_ARHU_EventScript_WestGateSign::
	msgbox Earnest_Township_ARHU_Text_WestGateSign, MSGBOX_SIGN
	end

Earnest_Township_ARHU_EventScript_EastGateSign::
	msgbox Earnest_Township_ARHU_Text_EastGateSign, MSGBOX_SIGN
	end

Earnest_Township_ARHU_EventScript_ContestHallSign::
	msgbox Earnest_Township_ARHU_Text_ContestHallSign, MSGBOX_SIGN
	end

Earnest_Township_ARHU_Text_ForestAllAround:
	.string "Nothing but forest all around\n"
	.string "EARNEST TOWNSHIP.\p"
	.string "It's peaceful, and I like it that\n"
	.string "way.$"

Earnest_Township_ARHU_Text_GymLeaderTough:
	.string "The GYM LEADER here is no pushover.\n"
	.string "Train up before you challenge.$"

Earnest_Township_ARHU_Text_ContestHallOpening:
	.string "The CONTEST HALL finally opened!\p"
	.string "Half of Professor Tanglewood's\n"
	.string "Safari class is lined up inside.\p"
	.string "They say a ribbon there counts\n"
	.string "the same as the GYM's BADGE now!$"

Earnest_Township_ARHU_Text_GymBadges:
	.string "You'll need a few BADGES under\n"
	.string "your belt before the GYM here\l"
	.string "starts to feel fair.$"

Earnest_Township_ARHU_Text_GoodFood:
	.string "Fresh berries, fresh bread, and\n"
	.string "not a fish in sight!$"

Earnest_Township_ARHU_Text_TownHistory:
	.string "This town was built in a clearing\n"
	.string "in the woods, long before the\l"
	.string "CYCLING ROAD was paved.$"

Earnest_Township_ARHU_Text_QuietTown:
	.string "It's quiet here, but the trees\n"
	.string "make great hiding spots!$"

Earnest_Township_ARHU_Text_ShopsAreGood:
	.string "The shops here are small, but\n"
	.string "they stock everything you need.$"

Earnest_Township_ARHU_Text_GatesClosed:
	.string "Both gates are shut for now.\p"
	.string "I hear they'll open when the\n"
	.string "time is right.$"

Earnest_Township_ARHU_Text_GetNameRaterToHelpYou:
	.string "If you don't like your POKéMON's\n"
	.string "nickname, get the NAME RATER to\l"
	.string "help you.$"

Earnest_Township_ARHU_Text_CantChangeTradeMonName:
	.string "The NAME RATER can't change the\n"
	.string "nickname of a POKéMON you got in\l"
	.string "a trade.$"

Earnest_Township_ARHU_Text_NameRatersHouseSign:
	.string "NAME RATER'S HOUSE\n"
	.string "“POKéMON nicknames rated.”$"

Earnest_Township_ARHU_Text_GymSign:
	.string "EARNEST TOWNSHIP POKéMON GYM$"

Earnest_Township_ARHU_Text_CitySign:
	.string "EARNEST TOWNSHIP\p"
	.string "“A quiet town hidden in the woods.”$"

Earnest_Township_ARHU_Text_WestGateSign:
	.string "WEST GATE\n"
	.string "“Closed for now.”$"

Earnest_Township_ARHU_Text_EastGateSign:
	.string "EAST GATE\n"
	.string "“Closed for now.”$"

Earnest_Township_ARHU_Text_ContestHallSign:
	.string "EARNEST CONTEST HALL\n"
	.string "“NORMAL RANK: Now open!”$"
