@ Earnest Township CONTEST HALL lobby: the first stop on the contest road (NORMAL RANK only).
@ Uses the Lilycove lobby layout. The stage itself is Emerald's shared ContestHall* maps;
@ ContestHall_EventScript_SetExitWarp sends the player back here while VAR_EARNEST_CONTEST_STATE is
@ EARNEST_CONTEST_STATE_ENTERED(_REMATCH). Mira is seated in every contest here (SetContestants, contestant
@ slot 0) until the player wins, which grants the DOJO BADGE under the "Fervor Accord", the same reward as
@ beating THRESH, so either road opens the same doors.
Earnest_ContestHall_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Earnest_ContestHall_ARHU_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Earnest_ContestHall_ARHU_OnFrame
	.byte 0

Earnest_ContestHall_ARHU_OnTransition:
	setflag FLAG_HIDE_EARNEST_CONTEST_HALL_MIRA
	call_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_MIRA_INTRO, Earnest_ContestHall_ARHU_EventScript_SetMiraAtCounter
	call_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_PLAYER_WON, Earnest_ContestHall_ARHU_EventScript_SetMiraForResults
	call_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_MIRA_WON, Earnest_ContestHall_ARHU_EventScript_SetMiraForResults
	call_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_OTHER_WON, Earnest_ContestHall_ARHU_EventScript_SetMiraForResults
	end

Earnest_ContestHall_ARHU_EventScript_SetMiraAtCounter::
	clearflag FLAG_HIDE_EARNEST_CONTEST_HALL_MIRA
	setobjectxyperm LOCALID_EARNEST_CONTEST_MIRA, 14, 4
	setobjectmovementtype LOCALID_EARNEST_CONTEST_MIRA, MOVEMENT_TYPE_FACE_UP
	return

@ The player is warped back to (14,4); Mira waits two tiles below.
Earnest_ContestHall_ARHU_EventScript_SetMiraForResults::
	clearflag FLAG_HIDE_EARNEST_CONTEST_HALL_MIRA
	setobjectxyperm LOCALID_EARNEST_CONTEST_MIRA, 14, 6
	setobjectmovementtype LOCALID_EARNEST_CONTEST_MIRA, MOVEMENT_TYPE_FACE_UP
	return

Earnest_ContestHall_ARHU_OnFrame:
	map_script_2 VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_MIRA_INTRO, Earnest_ContestHall_ARHU_EventScript_MiraIntro
	map_script_2 VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_PLAYER_WON, Earnest_ContestHall_ARHU_EventScript_PlayerWon
	map_script_2 VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_MIRA_WON, Earnest_ContestHall_ARHU_EventScript_MiraWon
	map_script_2 VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_OTHER_WON, Earnest_ContestHall_ARHU_EventScript_OtherWon
	.2byte 0

@ ---------------------------------------------------------------------------
@ First visit: the player walks in at (14,11) while Mira is signing up at the counter (14,4).
@ She spots the player, comes down to (14,10), then heads backstage through the dressing room door (21,1).
Earnest_ContestHall_ARHU_EventScript_MiraIntro::
	lockall
	msgbox Earnest_ContestHall_ARHU_Text_Intro_ReceptionistBusy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EARNEST_CONTEST_MIRA, Common_Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_EARNEST_CONTEST_MIRA, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Earnest_ContestHall_ARHU_Text_Intro_MiraSpotsPlayer, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EARNEST_CONTEST_MIRA, Earnest_ContestHall_ARHU_Movement_MiraIntroApproach
	waitmovement 0
	msgbox Earnest_ContestHall_ARHU_Text_Intro_MiraCrowd, MSGBOX_DEFAULT
	msgbox Earnest_ContestHall_ARHU_Text_Intro_MiraAccord, MSGBOX_DEFAULT
	call_if_unset FLAG_RECEIVED_POKEBLOCK_CASE, Earnest_ContestHall_ARHU_EventScript_MiraGivePokeblockCase
	msgbox Earnest_ContestHall_ARHU_Text_Intro_MiraChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EARNEST_CONTEST_MIRA, Earnest_ContestHall_ARHU_Movement_MiraIntroToDressingRoom
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_EARNEST_CONTEST_MIRA
	setflag FLAG_HIDE_EARNEST_CONTEST_HALL_MIRA
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_READY
	releaseall
	end

Earnest_ContestHall_ARHU_EventScript_MiraGivePokeblockCase::
	msgbox Earnest_ContestHall_ARHU_Text_Intro_MiraPokeblockCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	goto_if_eq VAR_RESULT, FALSE, Earnest_ContestHall_ARHU_EventScript_MiraPokeblockCaseNoRoom
	setflag FLAG_RECEIVED_POKEBLOCK_CASE
	msgbox Earnest_ContestHall_ARHU_Text_Intro_MiraExplainPokeblocks, MSGBOX_DEFAULT
	return

@ The receptionist hands one out instead (LilycoveCity_ContestLobby_EventScript_GivePokeblockCase)
Earnest_ContestHall_ARHU_EventScript_MiraPokeblockCaseNoRoom::
	msgbox Earnest_ContestHall_ARHU_Text_Intro_MiraCaseNoRoom, MSGBOX_DEFAULT
	return

Earnest_ContestHall_ARHU_Movement_MiraIntroApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Earnest_ContestHall_ARHU_Movement_MiraIntroToDressingRoom:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

@ ---------------------------------------------------------------------------
@ Called from ContestHall_EventScript_SetExitWarp (on the stage map) when the contest was entered here.
@ In NPC contests the player is contestant 3; Mira is seated in slot 0 by SetContestants.
Earnest_ContestHall_ARHU_EventScript_ReturnFromStage::
	special GetContestWinnerId
	goto_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_ENTERED_REMATCH, Earnest_ContestHall_ARHU_EventScript_ReturnFromRematch
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_OTHER_WON
	call_if_eq VAR_0x8005, 0, Earnest_ContestHall_ARHU_EventScript_SetMiraWon
	call_if_eq VAR_0x8005, 3, Earnest_ContestHall_ARHU_EventScript_SetPlayerWon
	goto Earnest_ContestHall_ARHU_EventScript_WarpBackToLobby
	end

Earnest_ContestHall_ARHU_EventScript_ReturnFromRematch::
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_CLEARED
	goto Earnest_ContestHall_ARHU_EventScript_WarpBackToLobby
	end

Earnest_ContestHall_ARHU_EventScript_SetMiraWon::
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_MIRA_WON
	return

Earnest_ContestHall_ARHU_EventScript_SetPlayerWon::
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_PLAYER_WON
	return

Earnest_ContestHall_ARHU_EventScript_WarpBackToLobby::
	warp MAP_EARNEST_CONTEST_HALL_ARHU, 14, 4
	waitstate
	end

@ ---------------------------------------------------------------------------
@ Results scenes. The player stands at (14,4) facing the counter; Mira steps up from (14,6) to (14,5).
Earnest_ContestHall_ARHU_EventScript_MiraStepsUp::
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	applymovement LOCALID_EARNEST_CONTEST_MIRA, Common_Movement_WalkUp
	waitmovement 0
	return

Earnest_ContestHall_ARHU_EventScript_PlayerWon::
	lockall
	call Earnest_ContestHall_ARHU_EventScript_MiraStepsUp
	msgbox Earnest_ContestHall_ARHU_Text_PlayerWon_Mira, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox Earnest_ContestHall_ARHU_Text_PlayerWon_Accord, MSGBOX_DEFAULT
	goto_if_set FLAG_BADGE01_GET, Earnest_ContestHall_ARHU_EventScript_PlayerWon_AlreadyHasBadge
	message Earnest_ContestHall_ARHU_Text_PlayerWon_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE01_GET
	msgbox Earnest_ContestHall_ARHU_Text_PlayerWon_BadgeInfo, MSGBOX_DEFAULT
	call_if_unset FLAG_RECEIVED_HM_ROCK_SMASH, Earnest_ContestHall_ARHU_EventScript_GiveRockSmash
	goto Earnest_ContestHall_ARHU_EventScript_PlayerWon_HallPrize
	end

Earnest_ContestHall_ARHU_EventScript_PlayerWon_AlreadyHasBadge::
	msgbox Earnest_ContestHall_ARHU_Text_PlayerWon_BothRoads, MSGBOX_DEFAULT
	goto Earnest_ContestHall_ARHU_EventScript_PlayerWon_HallPrize
	end

Earnest_ContestHall_ARHU_EventScript_PlayerWon_HallPrize::
	msgbox Earnest_ContestHall_ARHU_Text_PlayerWon_HallPrize, MSGBOX_DEFAULT
	call Earnest_ContestHall_ARHU_EventScript_GiveSilkScarf
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	msgbox Earnest_ContestHall_ARHU_Text_PlayerWon_MiraFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EARNEST_CONTEST_MIRA, Earnest_ContestHall_ARHU_Movement_MiraLeaveLobby
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_EARNEST_CONTEST_MIRA
	setflag FLAG_HIDE_EARNEST_CONTEST_HALL_MIRA
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_CLEARED
	releaseall
	end

@ A full bag never loses a reward: the receptionist hands over anything still owed (TryGiveOwedPrizes).
Earnest_ContestHall_ARHU_EventScript_GiveRockSmash::
	giveitem ITEM_HM06
	goto_if_eq VAR_RESULT, FALSE, Earnest_ContestHall_ARHU_EventScript_PrizeBagFull
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	msgbox Earnest_ContestHall_ARHU_Text_ExplainRockSmash, MSGBOX_DEFAULT
	return

Earnest_ContestHall_ARHU_EventScript_GiveSilkScarf::
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, Earnest_ContestHall_ARHU_EventScript_PrizeBagFull
	setflag FLAG_RECEIVED_EARNEST_CONTEST_SILK_SCARF
	msgbox Earnest_ContestHall_ARHU_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	return

Earnest_ContestHall_ARHU_EventScript_PrizeBagFull::
	call Common_EventScript_BagIsFull
	msgbox Earnest_ContestHall_ARHU_Text_PickUpPrizeLater, MSGBOX_DEFAULT
	return

Earnest_ContestHall_ARHU_EventScript_MiraWon::
	lockall
	call Earnest_ContestHall_ARHU_EventScript_MiraStepsUp
	msgbox Earnest_ContestHall_ARHU_Text_MiraWon, MSGBOX_DEFAULT
	goto Earnest_ContestHall_ARHU_EventScript_MiraBackToDressingRoom
	end

Earnest_ContestHall_ARHU_EventScript_OtherWon::
	lockall
	special BufferContestWinnerTrainerName
	call Earnest_ContestHall_ARHU_EventScript_MiraStepsUp
	msgbox Earnest_ContestHall_ARHU_Text_OtherWon, MSGBOX_DEFAULT
	goto Earnest_ContestHall_ARHU_EventScript_MiraBackToDressingRoom
	end

Earnest_ContestHall_ARHU_EventScript_MiraBackToDressingRoom::
	closemessage
	applymovement LOCALID_EARNEST_CONTEST_MIRA, Earnest_ContestHall_ARHU_Movement_MiraResultsToDressingRoom
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_EARNEST_CONTEST_MIRA
	setflag FLAG_HIDE_EARNEST_CONTEST_HALL_MIRA
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_READY
	releaseall
	end

@ (14,5) -> (19,5) -> (19,2) -> (21,2) -> dressing room door (21,1)
Earnest_ContestHall_ARHU_Movement_MiraResultsToDressingRoom:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

@ (14,5) -> lobby exit (14,11)
Earnest_ContestHall_ARHU_Movement_MiraLeaveLobby:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ ---------------------------------------------------------------------------
@ Receptionist: NORMAL RANK only. The shared Lilycove entry scripts (data/scripts/contest_hall.inc) only
@ return here once a Pokémon is entered; every cancel path ends the script.
Earnest_ContestHall_ARHU_EventScript_Receptionist::
	special ClearLinkContestFlags
	lock
	faceplayer
	call_if_unset FLAG_RECEIVED_POKEBLOCK_CASE, LilycoveCity_ContestLobby_EventScript_GivePokeblockCase
	call_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_CLEARED, Earnest_ContestHall_ARHU_EventScript_TryGiveOwedPrizes
	call Earnest_ContestHall_ARHU_EventScript_AskEnterContest
	goto_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_CLEARED, Earnest_ContestHall_ARHU_EventScript_EnteredRematch
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_ENTERED
	goto Earnest_ContestHall_ARHU_EventScript_GoToStage
	end

Earnest_ContestHall_ARHU_EventScript_EnteredRematch::
	setvar VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_ENTERED_REMATCH
	goto Earnest_ContestHall_ARHU_EventScript_GoToStage
	end

Earnest_ContestHall_ARHU_EventScript_GoToStage::
	call Earnest_ContestHall_ARHU_EventScript_LeadToStage
	special SetContestTrainerGfxIds
	call LilycoveCity_ContestLobby_EventScript_SetPlayerGfx
	setvar VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_NORMAL
	call LilycoveCity_ContestLobby_EventScript_WarpToContestHall
	waitstate
	end

Earnest_ContestHall_ARHU_EventScript_TryGiveOwedPrizes::
	call_if_unset FLAG_RECEIVED_EARNEST_CONTEST_SILK_SCARF, Earnest_ContestHall_ARHU_EventScript_GiveOwedSilkScarf
	goto_if_unset FLAG_BADGE01_GET, Earnest_ContestHall_ARHU_EventScript_Return
	call_if_unset FLAG_RECEIVED_HM_ROCK_SMASH, Earnest_ContestHall_ARHU_EventScript_GiveOwedRockSmash
	return

Earnest_ContestHall_ARHU_EventScript_GiveOwedSilkScarf::
	msgbox Earnest_ContestHall_ARHU_Text_HereIsYourPrize, MSGBOX_DEFAULT
	call Earnest_ContestHall_ARHU_EventScript_GiveSilkScarf
	return

Earnest_ContestHall_ARHU_EventScript_GiveOwedRockSmash::
	msgbox Earnest_ContestHall_ARHU_Text_HereIsYourPrize, MSGBOX_DEFAULT
	call Earnest_ContestHall_ARHU_EventScript_GiveRockSmash
	return

Earnest_ContestHall_ARHU_EventScript_Return::
	return

Earnest_ContestHall_ARHU_EventScript_AskEnterContest::
	message Earnest_ContestHall_ARHU_Text_EnterNormalRank
	waitmessage
	multichoice 0, 0, MULTI_ENTERINFO, FALSE
	switch VAR_RESULT
	case 0, Earnest_ContestHall_ARHU_EventScript_EnterNormalRank
	case 1, Earnest_ContestHall_ARHU_EventScript_ContestInfo
	case 2, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	end

Earnest_ContestHall_ARHU_EventScript_EnterNormalRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_NORMAL
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

Earnest_ContestHall_ARHU_EventScript_ContestInfo::
	message LilycoveCity_ContestLobby_Text_WhichTopic1
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_INFO, FALSE
	switch VAR_RESULT
	case 0, Earnest_ContestHall_ARHU_EventScript_ExplainContests
	case 1, Earnest_ContestHall_ARHU_EventScript_ExplainContestTypes
	case 2, Earnest_ContestHall_ARHU_EventScript_ExplainContestRanks
	case 3, Earnest_ContestHall_ARHU_EventScript_AskEnterContest
	case MULTI_B_PRESSED, Earnest_ContestHall_ARHU_EventScript_AskEnterContest
	end

Earnest_ContestHall_ARHU_EventScript_ExplainContests::
	msgbox LilycoveCity_ContestLobby_Text_ExplainContests, MSGBOX_DEFAULT
	goto Earnest_ContestHall_ARHU_EventScript_ContestInfo
	end

Earnest_ContestHall_ARHU_EventScript_ExplainContestTypes::
	msgbox LilycoveCity_ContestLobby_Text_ExplainContestTypes, MSGBOX_DEFAULT
	goto Earnest_ContestHall_ARHU_EventScript_ContestInfo
	end

Earnest_ContestHall_ARHU_EventScript_ExplainContestRanks::
	msgbox Earnest_ContestHall_ARHU_Text_ExplainRanks, MSGBOX_DEFAULT
	goto Earnest_ContestHall_ARHU_EventScript_ContestInfo
	end

@ Same choreography as LilycoveCity_ContestLobby_EventScript_LeadToContestHall (same layout), with this
@ map's receptionist. Ends with both of them through the stage door at (9,1).
Earnest_ContestHall_ARHU_EventScript_LeadToStage::
	lockall
	applymovement LOCALID_EARNEST_CONTEST_RECEPTIONIST, LilycoveCity_ContestLobby_Movement_ReceptionistApproachCounter
	waitmovement 0
	playse SE_BRIDGE_WALK
	setmetatile 12, 2, METATILE_Contest_WallShadow, TRUE
	setmetatile 12, 3, METATILE_Contest_FloorShadow, TRUE
	special DrawWholeMapView
	applymovement LOCALID_EARNEST_CONTEST_RECEPTIONIST, LilycoveCity_ContestLobby_Movement_ReceptionistExitCounter
	waitmovement 0
	playse SE_BRIDGE_WALK
	setmetatile 12, 2, METATILE_Contest_CounterFlap_Top, TRUE
	setmetatile 12, 3, METATILE_Contest_CounterFlap_Bottom, TRUE
	special DrawWholeMapView
	delay 20
	applymovement LOCALID_EARNEST_CONTEST_RECEPTIONIST, LilycoveCity_ContestLobby_Movement_ReceptionistFacePlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, LilycoveCity_ContestLobby_Movement_PlayerApproachReceptionist
	waitmovement 0
	call_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_ENTERED, Earnest_ContestHall_ARHU_EventScript_ComeThroughMiraWaiting
	call_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_ENTERED_REMATCH, Earnest_ContestHall_ARHU_EventScript_ComeThrough
	closemessage
	applymovement LOCALID_EARNEST_CONTEST_RECEPTIONIST, LilycoveCity_ContestLobby_Movement_ReceptionistWalkToContestHall
	applymovement LOCALID_PLAYER, LilycoveCity_ContestLobby_Movement_PlayerWalkToContestHall
	waitmovement 0
	releaseall
	return

Earnest_ContestHall_ARHU_EventScript_ComeThroughMiraWaiting::
	msgbox Earnest_ContestHall_ARHU_Text_ComeThroughMiraWaiting, MSGBOX_DEFAULT
	return

Earnest_ContestHall_ARHU_EventScript_ComeThrough::
	msgbox LilycoveCity_ContestLobby_Text_ComeThroughHere, MSGBOX_DEFAULT
	return

Earnest_ContestHall_ARHU_EventScript_LinkReceptionist::
	msgbox Earnest_ContestHall_ARHU_Text_LinkCounterClosed, MSGBOX_NPC
	end

@ The back doors have no warp; only the receptionist can take the player through.
Earnest_ContestHall_ARHU_EventScript_StageDoor::
	lockall
	msgbox Earnest_ContestHall_ARHU_Text_StageDoor, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

Earnest_ContestHall_ARHU_EventScript_DressingRoomDoor::
	lockall
	msgbox Earnest_ContestHall_ARHU_Text_DressingRoomDoor, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

@ ---------------------------------------------------------------------------
@ BERRY BLENDERS. Each entry point stands in for BerryBlender_EventScript_BerryBlender1/2/3 (which use
@ Lilycove's object ids) and then joins the shared blending flow in data/scripts/berry_blender.inc.
@ VAR_0x8009 is NUM_OPPONENTS there.
Earnest_ContestHall_ARHU_EventScript_BerryBlender1::
	lockall
	setvar VAR_0x8009, 1
	applymovement LOCALID_EARNEST_CONTEST_BLENDER_1_HOST, BerryBlender_Movement_BlendLeaderWalkInPlace
	waitmovement 0
	msgbox Earnest_ContestHall_ARHU_Text_Blender1_Invite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, BerryBlender_EventScript_TryUseBerryBlender1
	msgbox Earnest_ContestHall_ARHU_Text_Blender1_Declined, MSGBOX_DEFAULT
	releaseall
	end

Earnest_ContestHall_ARHU_EventScript_BerryBlender2::
	lockall
	setvar VAR_0x8009, 2
	applymovement LOCALID_EARNEST_CONTEST_BLENDER_2_PARTICIPANT, Common_Movement_FaceOriginalDirection
	applymovement LOCALID_EARNEST_CONTEST_BLENDER_2_LEADER, BerryBlender_Movement_BlendLeaderWalkInPlace
	waitmovement 0
	msgbox Earnest_ContestHall_ARHU_Text_Blender2_Invite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, BerryBlender_EventScript_TryUseBerryBlender2
	msgbox BerryBlender_Text_ThatsTooBad, MSGBOX_DEFAULT
	releaseall
	end

Earnest_ContestHall_ARHU_EventScript_BerryBlender3::
	lockall
	setvar VAR_0x8009, 3
	applymovement LOCALID_EARNEST_CONTEST_BLENDER_3_PARTICIPANT_1, Common_Movement_FaceOriginalDirection
	applymovement LOCALID_EARNEST_CONTEST_BLENDER_3_PARTICIPANT_2, Common_Movement_FaceOriginalDirection
	applymovement LOCALID_EARNEST_CONTEST_BLENDER_3_LEADER, BerryBlender_Movement_BlendLeaderWalkInPlace
	waitmovement 0
	msgbox BerryBlender_Text_LookGoodAtBlendingJoinUs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, BerryBlender_EventScript_TryUseBlender3
	msgbox BerryBlender_Text_LeftUsInShock, MSGBOX_DEFAULT
	releaseall
	end

@ Talking to Nana Bramble gives a spare berry once a day (shared daily flag with the Lilycove lobby).
Earnest_ContestHall_ARHU_EventScript_Blender1Host::
	lock
	faceplayer
	msgbox Earnest_ContestHall_ARHU_Text_Blender1Host, MSGBOX_DEFAULT
	goto BerryBlender_EventScript_ExpertMCheckGiveBerry
	end

Earnest_ContestHall_ARHU_EventScript_Blender2Camper::
	msgbox Earnest_ContestHall_ARHU_Text_Blender2Camper, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_Blender2Picnicker::
	msgbox Earnest_ContestHall_ARHU_Text_Blender2Picnicker, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_Blender3PokefanF::
	msgbox BerryBlender_Text_LookGoodAtBlendingJoinUs, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_Blender3Boy::
	msgbox Earnest_ContestHall_ARHU_Text_Blender3Boy, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_Blender3Twin::
	msgbox BerryBlender_Text_WhatKindOfPokeblockWillIGet, MSGBOX_NPC
	end

@ ---------------------------------------------------------------------------
@ The crowd: Tanglewood's Safari class has flooded the hall.
Earnest_ContestHall_ARHU_EventScript_Hiker::
	msgbox Earnest_ContestHall_ARHU_Text_Hiker, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_Inspector::
	lock
	faceplayer
	goto_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_CLEARED, Earnest_ContestHall_ARHU_EventScript_InspectorCleared
	msgbox Earnest_ContestHall_ARHU_Text_Inspector, MSGBOX_DEFAULT
	release
	end

Earnest_ContestHall_ARHU_EventScript_InspectorCleared::
	msgbox Earnest_ContestHall_ARHU_Text_InspectorCleared, MSGBOX_DEFAULT
	release
	end

Earnest_ContestHall_ARHU_EventScript_PoserRookie::
	msgbox Earnest_ContestHall_ARHU_Text_PoserRookie, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_GymLineLass::
	msgbox Earnest_ContestHall_ARHU_Text_GymLineLass, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_BadgeBoy::
	msgbox Earnest_ContestHall_ARHU_Text_BadgeBoy, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_RibbonGirl::
	msgbox Earnest_ContestHall_ARHU_Text_RibbonGirl, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_SafariAssistant::
	msgbox Earnest_ContestHall_ARHU_Text_SafariAssistant, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_PokeblockKid::
	msgbox Earnest_ContestHall_ARHU_Text_PokeblockKid, MSGBOX_NPC
	end

Earnest_ContestHall_ARHU_EventScript_Veteran::
	lock
	faceplayer
	goto_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_CLEARED, Earnest_ContestHall_ARHU_EventScript_VeteranCleared
	msgbox Earnest_ContestHall_ARHU_Text_Veteran, MSGBOX_DEFAULT
	release
	end

Earnest_ContestHall_ARHU_EventScript_VeteranCleared::
	msgbox Earnest_ContestHall_ARHU_Text_VeteranCleared, MSGBOX_DEFAULT
	release
	end

Earnest_ContestHall_ARHU_EventScript_AccordNotice::
	msgbox Earnest_ContestHall_ARHU_Text_AccordNotice, MSGBOX_SIGN
	end

Earnest_ContestHall_ARHU_EventScript_RankBoard::
	msgbox Earnest_ContestHall_ARHU_Text_RankBoard, MSGBOX_SIGN
	end

Earnest_ContestHall_ARHU_EventScript_PokeblockPoster::
	msgbox Earnest_ContestHall_ARHU_Text_PokeblockPoster, MSGBOX_SIGN
	end

Earnest_ContestHall_ARHU_EventScript_WinnersFrame::
	goto_if_eq VAR_EARNEST_CONTEST_STATE, EARNEST_CONTEST_STATE_CLEARED, Earnest_ContestHall_ARHU_EventScript_WinnersFrameCleared
	msgbox Earnest_ContestHall_ARHU_Text_WinnersFrame, MSGBOX_SIGN
	end

Earnest_ContestHall_ARHU_EventScript_WinnersFrameCleared::
	msgbox Earnest_ContestHall_ARHU_Text_WinnersFrameCleared, MSGBOX_SIGN
	end

@ ===========================================================================
@ Text
@ ===========================================================================

Earnest_ContestHall_ARHU_Text_Intro_ReceptionistBusy:
	.string "RECEPTIONIST: …and that's entry\n"
	.string "number forty-eight today!\p"
	.string "Professor Tanglewood's Safari\n"
	.string "class certainly keeps us busy!$"

Earnest_ContestHall_ARHU_Text_Intro_MiraSpotsPlayer:
	.string "Mira: Huh? {PLAYER}!\n"
	.string "Hey! Over here!$"

Earnest_ContestHall_ARHU_Text_Intro_MiraCrowd:
	.string "Mira: I knew you'd turn up sooner\n"
	.string "or later. Look at this place!\p"
	.string "Tanglewood gave out partners to\n"
	.string "half the kids in the region, and\l"
	.string "they ALL heard the hall just\l"
	.string "opened.\p"
	.string "Some of them caught the cutest\n"
	.string "thing they saw and only realized\l"
	.string "afterward that it hates fighting.\p"
	.string "Some of them got a good look at\n"
	.string "THRESH and walked straight back\l"
	.string "out of the GYM line.\p"
	.string "And some of them…\n"
	.string "are just like me.$"

Earnest_ContestHall_ARHU_Text_Intro_MiraAccord:
	.string "Mira: Have you heard of the\n"
	.string "FERVOR ACCORD?\p"
	.string "The POKéMON LEAGUE signed it\n"
	.string "with the CONTEST COMMITTEE.\p"
	.string "Win a town's CONTEST HALL, and\n"
	.string "the LEAGUE counts it the same as\l"
	.string "beating that town's GYM.\p"
	.string "Same BADGE. Same HMs. Same\n"
	.string "respect from your POKéMON.\p"
	.string "Westin calls it the easy way.\p"
	.string "Easy?! In a GYM you only have to\n"
	.string "beat one person.\p"
	.string "Up on that stage you have to win\n"
	.string "over a whole room of strangers.\p"
	.string "That's my road, {PLAYER}.\n"
	.string "Eevee and I decided in the Safari.$"

Earnest_ContestHall_ARHU_Text_Intro_MiraPokeblockCase:
	.string "Mira: Oh! Before I forget.\p"
	.string "The hall gave every Safari rookie\n"
	.string "a {POKEBLOCK} CASE, but they ran\l"
	.string "out by lunchtime.\p"
	.string "So I grabbed a spare one for you.\n"
	.string "You owe me!$"

Earnest_ContestHall_ARHU_Text_Intro_MiraExplainPokeblocks:
	.string "Mira: Put BERRIES in one of those\n"
	.string "BLENDERS over there and you get\l"
	.string "{POKEBLOCK}S.\p"
	.string "Feed them to your partner and its\n"
	.string "condition goes up. Cool, Beauty,\l"
	.string "Cute, Smart, Tough…\p"
	.string "The judges notice everything.$"

Earnest_ContestHall_ARHU_Text_Intro_MiraCaseNoRoom:
	.string "Mira: …Your bag's stuffed.\n"
	.string "Ask the counter for one later!$"

Earnest_ContestHall_ARHU_Text_Intro_MiraChallenge:
	.string "Mira: I already signed up. Any\n"
	.string "NORMAL RANK show you enter here,\l"
	.string "Eevee and I will be on that stage.\p"
	.string "You beat me at the Safari gate.\n"
	.string "That was a battle.\p"
	.string "This time it's about who makes\n"
	.string "the crowd forget to breathe.\p"
	.string "I'll be warming up backstage.\n"
	.string "Don't keep me waiting, {PLAYER}!$"

Earnest_ContestHall_ARHU_Text_PlayerWon_Mira:
	.string "Mira: …Second place.\p"
	.string "Eevee hit every beat. I was the\n"
	.string "one who rushed the last appeal.\p"
	.string "That was beautiful, {PLAYER}.\n"
	.string "Don't let it go to your head.$"

Earnest_ContestHall_ARHU_Text_PlayerWon_Accord:
	.string "RECEPTIONIST: Congratulations on\n"
	.string "your victory!\p"
	.string "Under the FERVOR ACCORD, the\n"
	.string "winner of this hall stands equal\l"
	.string "to a challenger who defeated\l"
	.string "THRESH of the EARNEST GYM.$"

Earnest_ContestHall_ARHU_Text_PlayerWon_ReceivedBadge:
	.string "{PLAYER} received the DOJO BADGE\n"
	.string "under the FERVOR ACCORD!$"

Earnest_ContestHall_ARHU_Text_PlayerWon_BadgeInfo:
	.string "RECEPTIONIST: THRESH signs every\n"
	.string "BADGE we hand out himself.\p"
	.string "He told us, “A crowd is a harder\n"
	.string "opponent than I am.”\p"
	.string "The DOJO BADGE lets your POKéMON\n"
	.string "use ROCK SMASH outside of battle.\l"
	.string "Please take this as well.$"

Earnest_ContestHall_ARHU_Text_ExplainRockSmash:
	.string "That's HM06, ROCK SMASH.\p"
	.string "Cracked boulders hide all sorts\n"
	.string "of paths around EARNEST.$"

Earnest_ContestHall_ARHU_Text_PlayerWon_BothRoads:
	.string "RECEPTIONIST: Oh my! You already\n"
	.string "carry THRESH's DOJO BADGE!\p"
	.string "You took both roads? We don't see\n"
	.string "that very often!$"

Earnest_ContestHall_ARHU_Text_PlayerWon_HallPrize:
	.string "RECEPTIONIST: And here is the\n"
	.string "hall's own prize for our winner.$"

Earnest_ContestHall_ARHU_Text_ExplainSilkScarf:
	.string "A SILK SCARF from the hall's very\n"
	.string "first costume rack.\p"
	.string "It powers up NORMAL-type moves.\n"
	.string "Something to remember us by!$"

Earnest_ContestHall_ARHU_Text_PickUpPrizeLater:
	.string "Please collect it from the counter\n"
	.string "once you've made some room.$"

Earnest_ContestHall_ARHU_Text_HereIsYourPrize:
	.string "Welcome back, champion! We've\n"
	.string "been keeping your prize safe.$"

Earnest_ContestHall_ARHU_Text_PlayerWon_MiraFarewell:
	.string "Mira: The same BADGE Westin's\n"
	.string "chasing in the GYM, and you got\l"
	.string "it without throwing a punch.\p"
	.string "He's going to HATE that.\p"
	.string "…Okay. I'm done sulking.\p"
	.string "The next town has a hall too, and\n"
	.string "the ranks only go up from here.\p"
	.string "Next time, Eevee and I take the\n"
	.string "ribbon. See you on the road!$"

Earnest_ContestHall_ARHU_Text_MiraWon:
	.string "Mira: Did you SEE that?!\n"
	.string "Eevee and I took first!\p"
	.string "…You were good, though.\n"
	.string "Really good.\p"
	.string "The judges just didn't see what\n"
	.string "you see in your partner yet.\p"
	.string "Feed it some {POKEBLOCK}S and try\n"
	.string "again. I'm not leaving EARNEST\l"
	.string "until you beat me fair and square.$"

Earnest_ContestHall_ARHU_Text_OtherWon:
	.string "Mira: Neither of us?!\p"
	.string "Beaten by {STR_VAR_3}…\n"
	.string "Tanglewood's Safari class is no\l"
	.string "joke.\p"
	.string "A week ago half these kids were\n"
	.string "chasing bugs with nets!\p"
	.string "Back to the BLENDERS. Next time,\n"
	.string "it's you and me for first place.$"

Earnest_ContestHall_ARHU_Text_EnterNormalRank:
	.string "Welcome to the EARNEST CONTEST\n"
	.string "HALL! Today is NORMAL RANK.\p"
	.string "Would you like to enter?$"

Earnest_ContestHall_ARHU_Text_ExplainRanks:
	.string "There are four ranks: NORMAL,\n"
	.string "SUPER, HYPER and MASTER.\p"
	.string "Our hall hosts NORMAL RANK, the\n"
	.string "first step for every POKéMON.\p"
	.string "Halls in other towns hold the\n"
	.string "higher ranks.\p"
	.string "Under the FERVOR ACCORD, winning\n"
	.string "here counts with the LEAGUE just\l"
	.string "like a win at the EARNEST GYM.$"

Earnest_ContestHall_ARHU_Text_ComeThroughMiraWaiting:
	.string "Please come through here.\p"
	.string "Miss Mira is already on stage.\n"
	.string "She asked us to tell you,\l"
	.string "“No holding back!”$"

Earnest_ContestHall_ARHU_Text_LinkCounterClosed:
	.string "I'm sorry, the LINK CONTEST\n"
	.string "counter is closed during opening\l"
	.string "week.\p"
	.string "We simply have too many rookies to\n"
	.string "register!$"

Earnest_ContestHall_ARHU_Text_StageDoor:
	.string "STAGE DOOR\n"
	.string "Entrants only, please register at\l"
	.string "the counter!$"

Earnest_ContestHall_ARHU_Text_DressingRoomDoor:
	.string "DRESSING ROOM\n"
	.string "Shh! Contestants are warming up.$"

Earnest_ContestHall_ARHU_Text_Blender1_Invite:
	.string "Fancy making {POKEBLOCK}S with Nana\n"
	.string "Bramble, dearie?$"

Earnest_ContestHall_ARHU_Text_Blender1_Declined:
	.string "Oh, go on, then. Nana will be right\n"
	.string "here when you change your mind.$"

Earnest_ContestHall_ARHU_Text_Blender2_Invite:
	.string "We're rookies too! Wanna blend\n"
	.string "some {POKEBLOCK}S with us?$"

Earnest_ContestHall_ARHU_Text_Blender1Host:
	.string "NANA BRAMBLE: I bake the bread in\n"
	.string "this town, you know.\p"
	.string "Blending BERRIES is just baking\n"
	.string "for POKéMON.$"

Earnest_ContestHall_ARHU_Text_Blender2Camper:
	.string "My POKéMON was too shy to battle.\p"
	.string "Then it tried a {POKEBLOCK} and\n"
	.string "danced for an hour. I'm sold!$"

Earnest_ContestHall_ARHU_Text_Blender2Picnicker:
	.string "We've made forty {POKEBLOCK}S today.\n"
	.string "My partner ate thirty-nine.$"

Earnest_ContestHall_ARHU_Text_Blender3Boy:
	.string "Mom said I could come watch\n"
	.string "the contests if I helped blend.\p"
	.string "I'm the official arrow-watcher!$"

Earnest_ContestHall_ARHU_Text_Hiker:
	.string "I GOT HERE FIRST!\p"
	.string "…Hm? This is the LINK CONTEST\n"
	.string "line? The one that's closed?\p"
	.string "Then I'm FIRST and LAST in line!\n"
	.string "That's a win either way!$"

Earnest_ContestHall_ARHU_Text_Inspector:
	.string "I'm an inspector from the CONTEST\n"
	.string "COMMITTEE.\p"
	.string "The FERVOR ACCORD pairs every\n"
	.string "hall with a GYM.\p"
	.string "Win a hall's ribbon, and the\n"
	.string "LEAGUE grants that town's BADGE.\p"
	.string "HMs, obedience, the right to walk\n"
	.string "on… all of it is the same.\p"
	.string "Battlers and performers can now\n"
	.string "travel side by side.$"

Earnest_ContestHall_ARHU_Text_InspectorCleared:
	.string "So you're the one who won the\n"
	.string "DOJO BADGE on stage!\p"
	.string "The next hall will expect more.\n"
	.string "The ranks rise as the GYMS do.$"

Earnest_ContestHall_ARHU_Text_PoserRookie:
	.string "Tanglewood said to pick the one\n"
	.string "I connect with.\p"
	.string "Mine won't battle. It just POSES.\n"
	.string "Every time. Mid-battle!\p"
	.string "So… here we are!$"

Earnest_ContestHall_ARHU_Text_GymLineLass:
	.string "The GYM's got a line out the door\n"
	.string "too.\p"
	.string "THRESH made a boy cry this\n"
	.string "morning. He didn't even say\l"
	.string "anything. He just looked at him.$"

Earnest_ContestHall_ARHU_Text_BadgeBoy:
	.string "BADGES are REAL power! You beat\n"
	.string "the LEADER, you prove you're\l"
	.string "strong!$"

Earnest_ContestHall_ARHU_Text_RibbonGirl:
	.string "It's the SAME BADGE! It's in the\n"
	.string "ACCORD! Read the notice board!\p"
	.string "…We've been arguing since the\n"
	.string "Safari gate.$"

Earnest_ContestHall_ARHU_Text_SafariAssistant:
	.string "I'm one of Professor Tanglewood's\n"
	.string "assistants.\p"
	.string "Forty-three partners handed out\n"
	.string "in a single week!\p"
	.string "The POKéMON CENTER ran out of\n"
	.string "POTIONS on the second day.\p"
	.string "The Professor sent me here to keep\n"
	.string "an eye on the rookies. I'm also\l"
	.string "taking notes for his research.$"

Earnest_ContestHall_ARHU_Text_PokeblockKid:
	.string "My partner turns its nose up at\n"
	.string "dry {POKEBLOCK}S.\p"
	.string "It only likes the sweet ones!$"

Earnest_ContestHall_ARHU_Text_Veteran:
	.string "Twenty years I've performed, and\n"
	.string "I've never seen a lobby this full.\p"
	.string "One tip, newcomer. Judges love a\n"
	.string "combo, and they love a POKéMON\l"
	.string "that trusts its Trainer more.\p"
	.string "Anyone can learn a combo. Trust\n"
	.string "takes {POKEBLOCK}S and time.$"

Earnest_ContestHall_ARHU_Text_VeteranCleared:
	.string "You moved the room, newcomer.\p"
	.string "I can't remember the last time I\n"
	.string "saw that, and I've seen it all.$"

Earnest_ContestHall_ARHU_Text_AccordNotice:
	.string "THE FERVOR ACCORD\p"
	.string "The POKéMON LEAGUE recognizes a\n"
	.string "win at a licensed CONTEST HALL\l"
	.string "as equal to a win at the GYM it\l"
	.string "is paired with.\p"
	.string "EARNEST HALL, NORMAL RANK:\n"
	.string "paired with the EARNEST GYM.\l"
	.string "Reward: DOJO BADGE$"

Earnest_ContestHall_ARHU_Text_RankBoard:
	.string "TODAY'S STAGE: NORMAL RANK\n"
	.string "COOL, BEAUTY, CUTE, SMART and\l"
	.string "TOUGH categories.\p"
	.string "Higher ranks are hosted at halls\n"
	.string "in other towns.$"

Earnest_ContestHall_ARHU_Text_PokeblockPoster:
	.string "A poster with a smiling POKéMON on\n"
	.string "it…\p"
	.string "“Dry {POKEBLOCK}S raise SMART!\n"
	.string "Spicy ones raise COOL!\l"
	.string "Know your BERRIES!”$"

Earnest_ContestHall_ARHU_Text_WinnersFrame:
	.string "An empty golden frame.\p"
	.string "“The hall's first champion's\n"
	.string "portrait goes here!”$"

Earnest_ContestHall_ARHU_Text_WinnersFrameCleared:
	.string "A hastily drawn sketch of {PLAYER}\n"
	.string "fills the golden frame.\p"
	.string "Someone has scribbled in the\n"
	.string "corner, “Next time! -M”$"
