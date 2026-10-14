FervorField_PlayersHouse_1F_ARHU_MapScripts::
	.byte 0

@ Trainer Challenge intro cutscene (ported from HMA script "trainer_challenge").
@ Fires once when the player first steps off the stairs at (10,2) onto (9,2) or (10,3).
@ Both entry points converge with the player at (6,3) facing the TV.
FervorField_PlayersHouse_1F_ARHU_EventScript_TrainerChallengeIntro_LeftOfStairs::
	lockall
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, FervorField_PlayersHouse_1F_ARHU_Movement_CameraToTV_LeftOfStairs
	waitmovement 0
	applymovement LOCALID_PLAYER, FervorField_PlayersHouse_1F_ARHU_Movement_PlayerToTV_LeftOfStairs
	waitmovement 0
	goto FervorField_PlayersHouse_1F_ARHU_EventScript_TrainerChallengeIntro_Broadcast

FervorField_PlayersHouse_1F_ARHU_EventScript_TrainerChallengeIntro_BelowStairs::
	lockall
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, FervorField_PlayersHouse_1F_ARHU_Movement_CameraToTV_BelowStairs
	waitmovement 0
	applymovement LOCALID_PLAYER, FervorField_PlayersHouse_1F_ARHU_Movement_PlayerToTV_BelowStairs
	waitmovement 0
	goto FervorField_PlayersHouse_1F_ARHU_EventScript_TrainerChallengeIntro_Broadcast

FervorField_PlayersHouse_1F_ARHU_EventScript_TrainerChallengeIntro_Broadcast::
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, Common_Movement_FaceUp
	waitmovement 0
	msgbox FervorField_PlayersHouse_1F_ARHU_Text_TrainerChallengeBroadcast, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAMERA, Common_Movement_WalkDown
	waitmovement 0
	msgbox FervorField_PlayersHouse_1F_ARHU_Text_MomThatProgramAgain, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, FervorField_PlayersHouse_1F_ARHU_Movement_MomApproachPlayer
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement LOCALID_PLAYERS_HOUSE_1F_MOM
	msgbox FervorField_PlayersHouse_1F_ARHU_Text_MomSoYoureReallyGoing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, FervorField_PlayersHouse_1F_ARHU_Movement_MomReturnToSpot
	waitmovement 0
	setvar VAR_FERVOR_FIELD_TRAINER_CHALLENGE_STATE, 1
	special RemoveCameraObject
	releaseall
	end

FervorField_PlayersHouse_1F_ARHU_Movement_CameraToTV_LeftOfStairs:
	walk_left
	walk_left
	walk_left
	step_end

FervorField_PlayersHouse_1F_ARHU_Movement_PlayerToTV_LeftOfStairs:
	walk_left
	walk_left
	walk_left
	walk_down
	face_up
	step_end

FervorField_PlayersHouse_1F_ARHU_Movement_CameraToTV_BelowStairs:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

FervorField_PlayersHouse_1F_ARHU_Movement_PlayerToTV_BelowStairs:
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

FervorField_PlayersHouse_1F_ARHU_Movement_MomApproachPlayer:
	walk_up
	walk_left
	step_end

FervorField_PlayersHouse_1F_ARHU_Movement_MomReturnToSpot:
	walk_right
	walk_down
	face_left
	step_end

FervorField_PlayersHouse_1F_ARHU_Text_TrainerChallengeBroadcast::
	.string "Announcer: This just in! The annual\n"
	.string "Trainer Challenge is about to begin!\p"
	.string "The Former Pokémon Ranger Professor\n"
	.string "Tanglewood announced today that\l"
	.string "Trainers of all ages are invited to\l"
	.string "take part.\p"
	.string "Participants will begin their journey\n"
	.string "in the Safari Grounds!\l"
	.string "Pokémon from many regions have been\l"
	.string "carefully protected just for this!\p"
	.string "Professor Tanglewood says the\n"
	.string "challenge isn't about strength alone\p"
	.string "It's about trust, patience,\n"
	.string "and learning how Pokémon live\l"
	.string "alongside people.\p"
	.string "Those who complete the Trainer\n"
	.string "Challenge may uncover new paths\l"
	.string "and a new understanding of Pokémon!\p"
	.string "Registration begins today.\n"
	.string "Don't miss this chance to start your\l"
	.string "own adventure!$"

FervorField_PlayersHouse_1F_ARHU_Text_MomThatProgramAgain::
	.string "Mom: Oh! That program again!\n"
	.string "Professor Tanglewood always did\l"
	.string "do things differently.\l"
	.string "Even when he was a Ranger…\p"
	.string "He used to say Pokémon don't choose\n"
	.string "Trainers because they're strong\p"
	.string "They choose them because\n"
	.string "they feel safe.$"

FervorField_PlayersHouse_1F_ARHU_Text_MomSoYoureReallyGoing::
	.string "Mom: So you're really going to take\n"
	.string "the Trainer Challenge?\p"
	.string "I knew this day would come…\n"
	.string "I didn't think it would feel so soon.\p"
	.string "If you've got to go heading into\n"
	.string "the Safari Grounds, remember this\p"
	.string "Pokémon won't wait to be caught.\n"
	.string "They're watching you too.\p"
	.string "Phew, you worry your mother so much!\n"
	.string "Take your time.\l"
	.string "Listen to them.\l"
	.string "And don't forget to rest sometimes.\p"
	.string "No matter how far you go\n"
	.string "this will always be home.$"

PalletTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_BEAT_RIVAL_IN_OAKS_LAB, PalletTown_PlayersHouse_1F_EventScript_MomHeal
	checkplayergender
	call_if_eq VAR_RESULT, MALE, PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouMale
	call_if_eq VAR_RESULT, FEMALE, PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouFemale
	closemessage
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouMale::
	msgbox PalletTown_PlayersHouse_1F_Text_AllBoysLeaveOakLookingForYou
	return

PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouFemale::
	msgbox PalletTown_PlayersHouse_1F_Text_AllGirlsLeaveOakLookingForYou
	return

PalletTown_PlayersHouse_1F_EventScript_MomHeal::
	msgbox PalletTown_PlayersHouse_1F_Text_YouShouldTakeQuickRest
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox PalletTown_PlayersHouse_1F_Text_LookingGreatTakeCare
	release
	end

PalletTown_PlayersHouse_1F_EventScript_TV::
	lockall
	goto_if_eq VAR_FACING, DIR_NORTH, PalletTown_PlayersHouse_1F_EventScript_TVScreen
	msgbox PalletTown_PlayersHouse_1F_Text_OopsWrongSide
	releaseall
	end

PalletTown_PlayersHouse_1F_EventScript_TVScreen::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, PalletTown_PlayersHouse_1F_EventScript_TVScreenMale
	call_if_eq VAR_RESULT, FEMALE, PalletTown_PlayersHouse_1F_EventScript_TVScreenFemale
	releaseall
	end

PalletTown_PlayersHouse_1F_EventScript_TVScreenMale::
	msgbox PalletTown_PlayersHouse_1F_Text_MovieOnTVFourBoysOnRailroad
	return

PalletTown_PlayersHouse_1F_EventScript_TVScreenFemale::
	msgbox PalletTown_PlayersHouse_1F_Text_MovieOnTVGirlOnBrickRoad
	return

PalletTown_PlayersHouse_1F_Text_AllBoysLeaveOakLookingForYou::
	.string "MOM: …Right.\nAll boys leave home someday.\l"
	.string "It said so on TV.\p"
	.string "Oh, yes. PROF. OAK, next door, was\nlooking for you.$"

PalletTown_PlayersHouse_1F_Text_AllGirlsLeaveOakLookingForYou::
	.string "MOM: …Right.\nAll girls dream of traveling.\l"
	.string "It said so on TV.\p"
	.string "Oh, yes. PROF. OAK, next door, was\nlooking for you.$"

PalletTown_PlayersHouse_1F_Text_YouShouldTakeQuickRest::
	.string "MOM: {PLAYER}!\nYou should take a quick rest.$"

PalletTown_PlayersHouse_1F_Text_LookingGreatTakeCare::
	.string "MOM: Oh, good! You and your\nPOKéMON are looking great.\l"
	.string "Take care now!$"

PalletTown_PlayersHouse_1F_Text_MovieOnTVFourBoysOnRailroad::
	.string "There's a movie on TV.\nFour boys are walking on railroad\l"
	.string "tracks.\p"
	.string "…I better go, too.$"

PalletTown_PlayersHouse_1F_Text_MovieOnTVGirlOnBrickRoad::
	.string "There's a movie on TV.\nA girl with her hair in pigtails is\l"
	.string "walking up a brick road.\p"
	.string "…I better go, too.$"

PalletTown_PlayersHouse_1F_Text_OopsWrongSide::
	.string "Oops, wrong side…$"

