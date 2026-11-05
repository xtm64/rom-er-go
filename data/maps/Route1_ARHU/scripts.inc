Route1_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route1_ARHU_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route1_ARHU_OnFrame
	.byte 0

@ The Holt ambush is waiting from the moment the Safari challenge is complete until the player has
@ the Running Shoes (FLAG_RECEIVED_RUNNING_SHOES is set at the end of the scene). Tanglewood and Mom
@ are always hidden on arrival; the scene adds them.
Route1_ARHU_OnTransition::
	setflag FLAG_HIDE_ROUTE1_HOLT_AMBUSH_RESCUERS
	setflag FLAG_HIDE_ROUTE1_HOLT_AMBUSH
	goto_if_unset FLAG_FERVOR_FIELD_SAFARI_CHALLENGE_COMPLETE, Route1_ARHU_OnTransition_End
	goto_if_set FLAG_RECEIVED_RUNNING_SHOES, Route1_ARHU_OnTransition_End
	clearflag FLAG_HIDE_ROUTE1_HOLT_AMBUSH
	setvar VAR_TEMP_1, 1
Route1_ARHU_OnTransition_End::
	end

Route1_ARHU_OnFrame::
	map_script_2 VAR_TEMP_1, 1, Route1_ARHU_EventScript_HoltAmbush
	.2byte 0

@ Holt ambush: a tag battle (player + partner vs two of Holt's crew).
@ The only way onto Route 1 before this scene is the east gate, so the player arrives on the gate
@ warp (44,16) and steps out to (43,16), facing left.
@ Cast: Westin (39,15) and Mira (39,17) are cornered by Holt (40,16), Rook (41,15) and Dash (41,17).
@ The player picks a partner (VAR_TEMP_2: 0 = Westin, 1 = Mira). Holt only fights Westin:
@   Westin: player + Westin vs Holt + Rook. Mira squares off with Dash on the side.
@   Mira:   player + Mira vs Rook + Dash. Westin squares off with Holt on the side.
@ The partner jumps over the goon in their way and lands beside the player.
@ Tag battles (DoSpecialTrainerBattle) always return to the script, so there is no whiteout.
@ Win or lose, Tanglewood and Mom come out of the gate and break it up, and Mom hands over the
@ Running Shoes. VAR_0x8009 = battle outcome.
Route1_ARHU_EventScript_HoltAmbush::
	lockall
	setvar VAR_TEMP_1, 0
	call Route1_ARHU_EventScript_HoltAmbush_BufferNames
	playbgm MUS_ENCOUNTER_SUSPICIOUS, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_ROUTE1_HOLT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Route1_ARHU_Text_Holt_GimmeYourPokemon, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Westin_CatchTheRealThing, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Holt_ThirtyBalls, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Mira_ItsForTheBerry, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_ROOK, Common_Movement_FaceDown
	waitmovement 0
	msgbox Route1_ARHU_Text_Rook_SheHasAPoint, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_HOLT, Route1_ARHU_Movement_HoltSnapAtRook
	waitmovement 0
	msgbox Route1_ARHU_Text_Holt_WhoseSide, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Rook_YoursBoss, MSGBOX_DEFAULT
	closemessage
	@ Dash spots the player
	playse SE_PIN
	applymovement LOCALID_ROUTE1_DASH, Route1_ARHU_Movement_FaceRightExclaim
	waitmovement 0
	msgbox Route1_ARHU_Text_Dash_AnotherOne, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_HOLT, Common_Movement_FaceRight
	applymovement LOCALID_ROUTE1_ROOK, Common_Movement_FaceRight
	applymovement LOCALID_ROUTE1_WESTIN, Common_Movement_ExclamationMark
	applymovement LOCALID_ROUTE1_MIRA, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Route1_ARHU_Text_Holt_MathWorksOut, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Westin_TeamUp, MSGBOX_DEFAULT
	closemessage
	@ Pick a partner
	message Route1_ARHU_Text_Mira_WhoIsItGonnaBe
	waitmessage
	dynmultipush Route1_ARHU_Text_ChoiceWestin, 0
	dynmultipush Route1_ARHU_Text_ChoiceMira, 1
	dynmultistack 0, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, 1, Route1_ARHU_EventScript_HoltAmbush_PickMira
	goto Route1_ARHU_EventScript_HoltAmbush_PickWestin

@ Westin jumps over Rook to (43,15); Mira takes Dash. Holt (42,16) and Rook (42,15) line up.
Route1_ARHU_EventScript_HoltAmbush_PickWestin::
	msgbox Route1_ARHU_Text_Westin_ImIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_WESTIN, Route1_ARHU_Movement_WestinJoinPlayer
	waitmovement 0
	msgbox Route1_ARHU_Text_Mira_DashIsMine, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_DASH, Route1_ARHU_Movement_DashToMira
	applymovement LOCALID_ROUTE1_MIRA, Common_Movement_FaceRight
	waitmovement 0
	msgbox Route1_ARHU_Text_Holt_FinallyWestin, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_HOLT, Route1_ARHU_Movement_HoltToPlayer
	applymovement LOCALID_ROUTE1_ROOK, Route1_ARHU_Movement_RookToWestin
	waitmovement 0
	msgbox Route1_ARHU_Text_Rook_HereWeGo, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_SQUIRTLE, Route1_ARHU_EventScript_HoltAmbush_BattleWithWestinSquirtle
	call_if_eq VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_CHIMCHAR, Route1_ARHU_EventScript_HoltAmbush_BattleWithWestinChimchar
	call_if_eq VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_SPRIGATITO, Route1_ARHU_EventScript_HoltAmbush_BattleWithWestinSprigatito
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_0x8009, VAR_RESULT
	call Route1_ARHU_EventScript_HoltAmbush_AfterBattle
	call_if_eq VAR_0x8009, B_OUTCOME_WON, Route1_ARHU_EventScript_HoltAmbush_WestinTeamWon
	call_if_ne VAR_0x8009, B_OUTCOME_WON, Route1_ARHU_EventScript_HoltAmbush_TeamLost
	goto Route1_ARHU_EventScript_HoltAmbush_Rescue

@ Mira jumps over Dash to (43,17); Westin takes Holt. Rook (42,16) and Dash (42,17) line up.
Route1_ARHU_EventScript_HoltAmbush_PickMira::
	msgbox Route1_ARHU_Text_Mira_ImIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_MIRA, Route1_ARHU_Movement_MiraJoinPlayer
	waitmovement 0
	msgbox Route1_ARHU_Text_Westin_HoltIsMine, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_HOLT, Route1_ARHU_Movement_HoltToWestin
	applymovement LOCALID_ROUTE1_WESTIN, Common_Movement_FaceRight
	waitmovement 0
	msgbox Route1_ARHU_Text_Holt_Gladly, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_ROOK, Route1_ARHU_Movement_RookToPlayer
	applymovement LOCALID_ROUTE1_DASH, Route1_ARHU_Movement_DashToMiraSide
	waitmovement 0
	msgbox Route1_ARHU_Text_Rook_JustUs, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Dash_Hustle, MSGBOX_DEFAULT
	closemessage
	setmultitrainerbattle TRAINER_ROUTE1_GOON_ROOK, Route1_ARHU_Text_Rook_Defeat, TRAINER_ROUTE1_GOON_DASH, Route1_ARHU_Text_Dash_Defeat, PARTNER_FERVOR_MIRA
	call Route1_ARHU_EventScript_HoltAmbush_DoTagBattle
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_0x8009, VAR_RESULT
	call Route1_ARHU_EventScript_HoltAmbush_AfterBattle
	call_if_eq VAR_0x8009, B_OUTCOME_WON, Route1_ARHU_EventScript_HoltAmbush_MiraTeamWon
	call_if_ne VAR_0x8009, B_OUTCOME_WON, Route1_ARHU_EventScript_HoltAmbush_TeamLost
	goto Route1_ARHU_EventScript_HoltAmbush_Rescue

Route1_ARHU_EventScript_HoltAmbush_BattleWithWestinSquirtle::
	setmultitrainerbattle TRAINER_ROUTE1_HOLT, Route1_ARHU_Text_Holt_Defeat, TRAINER_ROUTE1_GOON_ROOK, Route1_ARHU_Text_Rook_Defeat, PARTNER_FERVOR_WESTIN_SQUIRTLE
	call Route1_ARHU_EventScript_HoltAmbush_DoTagBattle
	return

Route1_ARHU_EventScript_HoltAmbush_BattleWithWestinChimchar::
	setmultitrainerbattle TRAINER_ROUTE1_HOLT, Route1_ARHU_Text_Holt_Defeat, TRAINER_ROUTE1_GOON_ROOK, Route1_ARHU_Text_Rook_Defeat, PARTNER_FERVOR_WESTIN_CHIMCHAR
	call Route1_ARHU_EventScript_HoltAmbush_DoTagBattle
	return

Route1_ARHU_EventScript_HoltAmbush_BattleWithWestinSprigatito::
	setmultitrainerbattle TRAINER_ROUTE1_HOLT, Route1_ARHU_Text_Holt_Defeat, TRAINER_ROUTE1_GOON_ROOK, Route1_ARHU_Text_Rook_Defeat, PARTNER_FERVOR_WESTIN_SPRIGATITO
	call Route1_ARHU_EventScript_HoltAmbush_DoTagBattle
	return

@ Runs the battle set up by setmultitrainerbattle. This skips the multi_2_vs_2 macro on purpose: that
@ macro saves and reloads the player's party around the battle (for Frontier-style mon picking),
@ which would undo the EXP and damage from this fight. The player keeps their whole party here.
Route1_ARHU_EventScript_HoltAmbush_DoTagBattle::
	setvar VAR_0x8004, SPECIAL_BATTLE_MULTI
	setvar VAR_0x8005, MULTI_BATTLE_2_VS_2
	special DoSpecialTrainerBattle
	return

Route1_ARHU_EventScript_HoltAmbush_BufferNames::
	bufferspeciesname STR_VAR_1, VAR_FERVOR_FIELD_WESTIN_STARTER
	bufferspeciesname STR_VAR_2, VAR_FERVOR_FIELD_PLAYER_STARTER
	return

@ Battles can reload the scene and reuse the string buffers, so names, faces and music are set again
Route1_ARHU_EventScript_HoltAmbush_AfterBattle::
	call Route1_ARHU_EventScript_HoltAmbush_BufferNames
	playbgm MUS_ENCOUNTER_SUSPICIOUS, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	applymovement LOCALID_ROUTE1_ROOK, Common_Movement_FaceRight
	goto_if_eq VAR_TEMP_2, 1, Route1_ARHU_EventScript_HoltAmbush_AfterBattle_Mira
	applymovement LOCALID_ROUTE1_WESTIN, Common_Movement_FaceLeft
	applymovement LOCALID_ROUTE1_HOLT, Common_Movement_FaceRight
	applymovement LOCALID_ROUTE1_MIRA, Common_Movement_FaceRight
	applymovement LOCALID_ROUTE1_DASH, Common_Movement_FaceLeft
	waitmovement 0
	return

Route1_ARHU_EventScript_HoltAmbush_AfterBattle_Mira::
	applymovement LOCALID_ROUTE1_MIRA, Common_Movement_FaceLeft
	applymovement LOCALID_ROUTE1_DASH, Common_Movement_FaceRight
	applymovement LOCALID_ROUTE1_WESTIN, Common_Movement_FaceRight
	applymovement LOCALID_ROUTE1_HOLT, Common_Movement_FaceLeft
	waitmovement 0
	return

Route1_ARHU_EventScript_HoltAmbush_WestinTeamWon::
	msgbox Route1_ARHU_Text_Holt_DoesntCount, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Westin_ItsTwoOnTwo, MSGBOX_DEFAULT
	closemessage
	return

Route1_ARHU_EventScript_HoltAmbush_MiraTeamWon::
	msgbox Route1_ARHU_Text_Dash_NeedBackup, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_HOLT, Common_Movement_FaceRight
	waitmovement 0
	msgbox Route1_ARHU_Text_Holt_CantYouHandleAnything, MSGBOX_DEFAULT
	closemessage
	return

Route1_ARHU_EventScript_HoltAmbush_TeamLost::
	msgbox Route1_ARHU_Text_Holt_HandThemOver, MSGBOX_DEFAULT
	closemessage
	return

@ Tanglewood comes out of the gate (44,16) and steps up to (44,15); Mom follows and stays on (44,16),
@ right beside the player.
Route1_ARHU_EventScript_HoltAmbush_Rescue::
	msgbox Route1_ARHU_Text_Tanglewood_ThatIsEnough, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_OAK, TRUE
	applymovement LOCALID_PLAYER, Route1_ARHU_Movement_FaceRightExclaim
	applymovement LOCALID_ROUTE1_HOLT, Common_Movement_ExclamationMark
	applymovement LOCALID_ROUTE1_ROOK, Common_Movement_ExclamationMark
	applymovement LOCALID_ROUTE1_DASH, Common_Movement_ExclamationMark
	waitmovement 0
	clearflag FLAG_HIDE_ROUTE1_HOLT_AMBUSH_RESCUERS
	playse SE_EXIT
	addobject LOCALID_ROUTE1_TANGLEWOOD
	applymovement LOCALID_ROUTE1_TANGLEWOOD, Route1_ARHU_Movement_TanglewoodArrive
	waitmovement 0
	playse SE_EXIT
	addobject LOCALID_ROUTE1_MOM
	delay 16
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox Route1_ARHU_Text_Tanglewood_ItChoseYou, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Holt_WhateverOldMan, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE1_ROOK, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_ROUTE1_DASH, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Route1_ARHU_Text_Goons_Hey, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_TEMP_2, 0, Route1_ARHU_EventScript_HoltAmbush_CrewFlees_Westin
	call_if_eq VAR_TEMP_2, 1, Route1_ARHU_EventScript_HoltAmbush_CrewFlees_Mira
	removeobject LOCALID_ROUTE1_HOLT
	removeobject LOCALID_ROUTE1_ROOK
	removeobject LOCALID_ROUTE1_DASH
	@ Tanglewood patches everyone up (again), then Mom, right beside the player, hands over the shoes
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox Route1_ARHU_Text_Tanglewood_BoundByDestiny, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route1_ARHU_Text_Mom_YouForgotThese, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message Route1_ARHU_Text_SwitchShoesWithRunningShoes
	waitmessage
	waitfanfare
	setflag FLAG_SYS_B_DASH
	setflag FLAG_RECEIVED_RUNNING_SHOES
	msgbox Route1_ARHU_Text_Mom_ExplainRunningShoes, MSGBOX_DEFAULT
	closemessage
	@ The friend who fought on the side comes over
	call_if_eq VAR_TEMP_2, 0, Route1_ARHU_EventScript_HoltAmbush_FriendsGather_Westin
	call_if_eq VAR_TEMP_2, 1, Route1_ARHU_EventScript_HoltAmbush_FriendsGather_Mira
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox Route1_ARHU_Text_Westin_ThatWasAwesome, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Mira_ItKeptLookingBack, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Westin_DontMakeMeFeelBad, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_TEMP_2, 0, Route1_ARHU_EventScript_HoltAmbush_FriendsLeave_Westin
	call_if_eq VAR_TEMP_2, 1, Route1_ARHU_EventScript_HoltAmbush_FriendsLeave_Mira
	removeobject LOCALID_ROUTE1_WESTIN
	removeobject LOCALID_ROUTE1_MIRA
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox Route1_ARHU_Text_Tanglewood_OffYouGo, MSGBOX_DEFAULT
	closemessage
	msgbox Route1_ARHU_Text_Mom_BeSafe, MSGBOX_DEFAULT
	closemessage
	@ Both head back into the gate at (44,16)
	applymovement LOCALID_ROUTE1_MOM, Route1_ARHU_Movement_EnterGate
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_ROUTE1_MOM
	applymovement LOCALID_ROUTE1_TANGLEWOOD, Route1_ARHU_Movement_TanglewoodLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_ROUTE1_TANGLEWOOD
	setflag FLAG_HIDE_ROUTE1_HOLT_AMBUSH
	setflag FLAG_HIDE_ROUTE1_HOLT_AMBUSH_RESCUERS
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	fadedefaultbgm
	releaseall
	end

@ Westin pick: Holt (42,16), Rook (42,15), Dash (40,17). Everyone leaves west along row 16
@ (row 15 has the Youngster at (38,15), row 17 has Mira at (39,17)).
Route1_ARHU_EventScript_HoltAmbush_CrewFlees_Westin::
	applymovement LOCALID_ROUTE1_HOLT, Route1_ARHU_Movement_FleeWest
	applymovement LOCALID_ROUTE1_ROOK, Route1_ARHU_Movement_RookFlee_Westin
	applymovement LOCALID_ROUTE1_DASH, Route1_ARHU_Movement_DashFlee_Westin
	waitmovement 0
	return

@ Mira pick: Holt (40,15), Rook (42,16), Dash (42,17). Rook leaves along row 16, Dash along row 17,
@ Holt drops to row 16 behind Rook (Westin is at (39,15)).
Route1_ARHU_EventScript_HoltAmbush_CrewFlees_Mira::
	applymovement LOCALID_ROUTE1_ROOK, Route1_ARHU_Movement_FleeWest
	applymovement LOCALID_ROUTE1_DASH, Route1_ARHU_Movement_FleeWest
	applymovement LOCALID_ROUTE1_HOLT, Route1_ARHU_Movement_HoltFlee_Mira
	waitmovement 0
	return

@ Westin pick: Westin is at (43,15); Mira comes over from (39,17) to (42,17)
Route1_ARHU_EventScript_HoltAmbush_FriendsGather_Westin::
	applymovement LOCALID_ROUTE1_MIRA, Route1_ARHU_Movement_MiraComeOver
	waitmovement 0
	applymovement LOCALID_ROUTE1_WESTIN, Common_Movement_FaceDown
	waitmovement 0
	return

@ Mira pick: Mira is at (43,17); Westin comes over from (39,15) to (42,15)
Route1_ARHU_EventScript_HoltAmbush_FriendsGather_Mira::
	applymovement LOCALID_ROUTE1_WESTIN, Route1_ARHU_Movement_WestinComeOver
	waitmovement 0
	applymovement LOCALID_ROUTE1_MIRA, Common_Movement_FaceUp
	waitmovement 0
	return

Route1_ARHU_EventScript_HoltAmbush_FriendsLeave_Westin::
	applymovement LOCALID_ROUTE1_WESTIN, Route1_ARHU_Movement_WestinLeave_FromPlayer
	applymovement LOCALID_ROUTE1_MIRA, Route1_ARHU_Movement_MiraLeave_FromSide
	waitmovement 0
	return

Route1_ARHU_EventScript_HoltAmbush_FriendsLeave_Mira::
	applymovement LOCALID_ROUTE1_WESTIN, Route1_ARHU_Movement_WestinLeave_FromSide
	applymovement LOCALID_ROUTE1_MIRA, Route1_ARHU_Movement_MiraLeave_FromPlayer
	waitmovement 0
	return

Route1_ARHU_Movement_HoltSnapAtRook:
	face_up
	emote_exclamation_mark
	step_end

Route1_ARHU_Movement_FaceRightExclaim:
	face_right
	emote_exclamation_mark
	step_end

@ (39,15) -> jump over Rook (41,15) -> (43,15), just above the player
Route1_ARHU_Movement_WestinJoinPlayer:
	walk_fast_right
	jump_2_right
	walk_fast_right
	face_left
	step_end

@ (39,17) -> jump over Dash (41,17) -> (43,17), just below the player
Route1_ARHU_Movement_MiraJoinPlayer:
	walk_fast_right
	jump_2_right
	walk_fast_right
	face_left
	step_end

@ Westin pick: Dash (41,17) -> (40,17), facing Mira (39,17)
Route1_ARHU_Movement_DashToMira:
	walk_left
	face_left
	step_end

@ Westin pick: Holt (40,16) -> (42,16), facing the player
Route1_ARHU_Movement_HoltToPlayer:
	walk_right
	walk_right
	face_right
	step_end

@ Westin pick: Rook (41,15) -> (42,15), facing Westin
Route1_ARHU_Movement_RookToWestin:
	walk_right
	face_right
	step_end

@ Mira pick: Holt (40,16) -> (40,15), facing Westin (39,15)
Route1_ARHU_Movement_HoltToWestin:
	walk_up
	face_left
	step_end

@ Mira pick: Rook (41,15) -> (42,16), facing the player
Route1_ARHU_Movement_RookToPlayer:
	walk_down
	walk_right
	face_right
	step_end

@ Mira pick: Dash (41,17) -> (42,17), facing Mira
Route1_ARHU_Movement_DashToMiraSide:
	walk_right
	face_right
	step_end

@ (44,16) -> (44,15)
Route1_ARHU_Movement_TanglewoodArrive:
	walk_up
	face_left
	step_end

@ Ten tiles west along the current row, off screen
Route1_ARHU_Movement_FleeWest:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

@ Westin pick: Rook (42,15) drops to row 16 once Holt is clear, then west
Route1_ARHU_Movement_RookFlee_Westin:
	delay_16
	delay_16
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

@ Westin pick: Dash (40,17) steps up to row 16 once Rook is past, then west
Route1_ARHU_Movement_DashFlee_Westin:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

@ Mira pick: Holt (40,15) drops to row 16 once Rook is past, then west
Route1_ARHU_Movement_HoltFlee_Mira:
	delay_16
	delay_16
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

@ (39,17) -> (42,17)
Route1_ARHU_Movement_MiraComeOver:
	walk_right
	walk_right
	walk_right
	face_up
	step_end

@ (39,15) -> (42,15)
Route1_ARHU_Movement_WestinComeOver:
	walk_right
	walk_right
	walk_right
	face_down
	step_end

@ Westin pick: Westin (43,15) -> (42,15) -> down to row 16 -> west
Route1_ARHU_Movement_WestinLeave_FromPlayer:
	walk_fast_left
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

@ Westin pick: Mira (42,17) west along row 17
Route1_ARHU_Movement_MiraLeave_FromSide:
	delay_16
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

@ Mira pick: Westin (42,15) down to row 16 -> west
Route1_ARHU_Movement_WestinLeave_FromSide:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

@ Mira pick: Mira (43,17) west along row 17
Route1_ARHU_Movement_MiraLeave_FromPlayer:
	delay_16
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

@ Mom is already on the gate warp (44,16)
Route1_ARHU_Movement_EnterGate:
	face_right
	delay_8
	set_invisible
	step_end

@ (44,15) -> back through the gate at (44,16)
Route1_ARHU_Movement_TanglewoodLeave:
	walk_down
	face_right
	delay_8
	set_invisible
	step_end

Route1_ARHU_EventScript_HurtMonsYoungster::
	msgbox Route1_ARHU_Text_HurtMonsYoungster, MSGBOX_NPC
	end

Route1_ARHU_EventScript_CoolMonsLass::
	msgbox Route1_ARHU_Text_CoolMonsLass, MSGBOX_NPC
	end

Route1_ARHU_Text_HurtMonsYoungster:
	.string "I'm looking for Pokémon, but my\n"
	.string "partner keeps getting hurt.\p"
	.string "I have to run back to the Pokémon\n"
	.string "Center every time!$"

Route1_ARHU_Text_CoolMonsLass:
	.string "Where are the cool Pokémon?\n"
	.string "I bet they're further in.\p"
	.string "I bet I'll be able to take on more\n"
	.string "Trainers with more Pokémon!$"

@ Holt ambush text. STR_VAR_1 = Westin's starter, STR_VAR_2 = the player's starter.

Route1_ARHU_Text_Holt_GimmeYourPokemon::
	.string "Holt: Gimme your Pokémon!\n"
	.string "Why should I only have one…\p"
	.string "Heh.\n"
	.string "That {STR_VAR_1} would look\l"
	.string "better on my belt anyway.$"

Route1_ARHU_Text_Westin_CatchTheRealThing::
	.string "Westin: Try catching the real thing\n"
	.string "from the challenge next time!$"

Route1_ARHU_Text_Holt_ThirtyBalls::
	.string "Holt: Thirty Poké Balls!\n"
	.string "Twenty-seven starters!\p"
	.string "And the only thing that would sit\n"
	.string "still for me was this walking\l"
	.string "trash can!$"

Route1_ARHU_Text_Mira_ItsForTheBerry::
	.string "Mira: Maybe because you yelled at\n"
	.string "every bush in the Safari.\p"
	.string "And that Zigzagoon isn't following\n"
	.string "you, Holt.\l"
	.string "It's following your Oran Berry.$"

Route1_ARHU_Text_Rook_SheHasAPoint::
	.string "Rook: …She kinda has a point,\n"
	.string "boss.$"

Route1_ARHU_Text_Holt_WhoseSide::
	.string "Holt: Whose side are you on?!$"

Route1_ARHU_Text_Rook_YoursBoss::
	.string "Rook: Yours! Always yours!\n"
	.string "My Meowth's just nervous, that's all!$"

Route1_ARHU_Text_Dash_AnotherOne::
	.string "Dash: Boss! Another one just walked\n"
	.string "outta the gate!\p"
	.string "And they got a {STR_VAR_2}!$"

Route1_ARHU_Text_Holt_MathWorksOut::
	.string "Holt: Well, well.\n"
	.string "Fresh out of the challenge, huh?\p"
	.string "Three of you, three of us.\n"
	.string "Three new partners.\p"
	.string "I'm no professor,\n"
	.string "but the math works out!$"

Route1_ARHU_Text_Westin_TeamUp::
	.string "Westin: {PLAYER}! You showed up at\n"
	.string "the perfect time!\p"
	.string "Tanglewood said to help each other\n"
	.string "out, right?\l"
	.string "Then let's team up!$"

Route1_ARHU_Text_Mira_WhoIsItGonnaBe::
	.string "Mira: Who's it gonna be, {PLAYER}?$"

Route1_ARHU_Text_ChoiceWestin::
	.string "Westin$"

Route1_ARHU_Text_ChoiceMira::
	.string "Mira$"

Route1_ARHU_Text_Westin_ImIn::
	.string "Westin: Yes! Just like old times!\n"
	.string "Coming through!$"

Route1_ARHU_Text_Mira_DashIsMine::
	.string "Mira: Then I'll keep this one busy.\n"
	.string "Eevee, let's go!$"

Route1_ARHU_Text_Holt_FinallyWestin::
	.string "Holt: Westin. Perfect.\p"
	.string "I've wanted to wipe that grin off\n"
	.string "your face since the gate.\l"
	.string "Rook! You're with me!$"

Route1_ARHU_Text_Rook_HereWeGo::
	.string "Rook: R-right behind you, boss!$"

Route1_ARHU_Text_Mira_ImIn::
	.string "Mira: Good call.\n"
	.string "Eevee, hop to it!$"

Route1_ARHU_Text_Westin_HoltIsMine::
	.string "Westin: Then Holt's mine!\p"
	.string "You want my {STR_VAR_1}, Holt?\n"
	.string "Come and get it!$"

Route1_ARHU_Text_Holt_Gladly::
	.string "Holt: Gladly.\n"
	.string "Rook! Dash! Deal with those two!$"

Route1_ARHU_Text_Rook_JustUs::
	.string "Rook: Uh… boss?\n"
	.string "It's just us two?$"

Route1_ARHU_Text_Dash_Hustle::
	.string "Dash: Quit whining and hustle, Rook!\n"
	.string "HUSTLE!$"

Route1_ARHU_Text_Holt_Defeat::
	.string "Holt: It ate the berry and STILL\n"
	.string "lost?!$"

Route1_ARHU_Text_Rook_Defeat::
	.string "Rook: My Meowth got scared…\n"
	.string "And, uh… so did I.$"

Route1_ARHU_Text_Dash_Defeat::
	.string "Dash: Hustlin' means I miss a lot,\n"
	.string "doesn't it…$"

Route1_ARHU_Text_Holt_DoesntCount::
	.string "Holt: That doesn't count!\n"
	.string "You ganged up on us!$"

Route1_ARHU_Text_Westin_ItsTwoOnTwo::
	.string "Westin: It was two on two!\n"
	.string "That's literally fair!$"

Route1_ARHU_Text_Dash_NeedBackup::
	.string "Dash: Boss! Boss!\n"
	.string "We need backup over here!$"

Route1_ARHU_Text_Holt_CantYouHandleAnything::
	.string "Holt: Can't you two handle\n"
	.string "ANYTHING?!$"

Route1_ARHU_Text_Holt_HandThemOver::
	.string "Holt: Ha! Told you the math\n"
	.string "works out.\p"
	.string "Now hand them over.\n"
	.string "All of them!$"

Route1_ARHU_Text_Tanglewood_ThatIsEnough::
	.string "???: That is ENOUGH!$"

Route1_ARHU_Text_Tanglewood_ItChoseYou::
	.string "Tanglewood: Holt.\n"
	.string "I watched you in my Safari.\p"
	.string "You chased every Pokémon in there\n"
	.string "with your fists balled up.\l"
	.string "Not one would go near you.\p"
	.string "Yet that Zigzagoon followed you\n"
	.string "out anyway.\p"
	.string "It chose you, Holt.\n"
	.string "And this is how you thank it?\l"
	.string "By taking someone else's partner?$"

Route1_ARHU_Text_Holt_WhateverOldMan::
	.string "Holt: …Tch.\n"
	.string "Whatever, old man.\p"
	.string "Westin! {PLAYER}!\n"
	.string "This isn't over.\p"
	.string "And next time,\n"
	.string "I won't need these two.$"

Route1_ARHU_Text_Goons_Hey::
	.string "Rook and Dash: Hey!!$"

Route1_ARHU_Text_Mom_YouForgotThese::
	.string "Mom: {PLAYER}!\n"
	.string "Are you hurt? Let me look at you!\p"
	.string "I came to see you off the second\n"
	.string "the challenge ended, and I ran into\l"
	.string "the Professor at the gate.\p"
	.string "Then we hear all that shouting!\n"
	.string "Phew, you worry your mother so much!\p"
	.string "Oh! And you ran out this morning\n"
	.string "so fast, you forgot these!\l"
	.string "Your new RUNNING SHOES!$"

Route1_ARHU_Text_SwitchShoesWithRunningShoes::
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

Route1_ARHU_Text_Mom_ExplainRunningShoes::
	.string "Mom: Hold the B Button while you\n"
	.string "walk to run extra fast!\p"
	.string "Just promise me you'll use them to\n"
	.string "run AWAY from trouble sometimes,\l"
	.string "too.$"

Route1_ARHU_Text_Tanglewood_BoundByDestiny::
	.string "Tanglewood: Hmm… Another round of\n"
	.string "healing for all of you, is it?\p"
	.string "Wow, you three sure get hurt a lot\n"
	.string "whenever you're together!\p"
	.string "You must be bound by destiny…\n"
	.string "Hahaha!\p"
	.string "Now hold still, all of you.$"

Route1_ARHU_Text_Westin_ThatWasAwesome::
	.string "Westin: {PLAYER}! That was awesome!\n"
	.string "We stood up to all three of them!\p"
	.string "Tanglewood's speech was right.\n"
	.string "We really did help each other out!$"

Route1_ARHU_Text_Mira_ItKeptLookingBack::
	.string "Mira: Holt's all bark.\p"
	.string "But his Zigzagoon…\n"
	.string "Did you see it?\l"
	.string "It kept looking back at him.\p"
	.string "Maybe the Professor's right.\n"
	.string "Maybe it picked him for a reason.$"

Route1_ARHU_Text_Westin_DontMakeMeFeelBad::
	.string "Westin: Ugh, don't make me feel bad\n"
	.string "for the guy!\p"
	.string "Come on, Mira, the road won't wait!\n"
	.string "See ya, {PLAYER}!$"

Route1_ARHU_Text_Tanglewood_OffYouGo::
	.string "Tanglewood: Hmhm. Those two will\n"
	.string "keep each other honest.\p"
	.string "As for Holt… some partnerships take\n"
	.string "longer to grow than others.\p"
	.string "Now then, {PLAYER}.\n"
	.string "Route 1 leads to the rest of the\l"
	.string "region. Off you go!$"

Route1_ARHU_Text_Mom_BeSafe::
	.string "Mom: Be safe, sweetie!\n"
	.string "And come home if anything happens!$"
