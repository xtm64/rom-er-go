FervorFieldCity_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FervorFieldCity_ARHU_OnTransition
	.byte 0

FervorFieldCity_ARHU_OnTransition::
	goto_if_ne VAR_FERVOR_FIELD_RIVAL_INTRO_STATE, 0, FervorFieldCity_ARHU_OnTransition_End
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_RIVAL_FRIEND
FervorFieldCity_ARHU_OnTransition_End::
	end

@ Meet the Rival cutscene (ported from HMA script "meet_the_rival").
@ Fires once when the player steps on (12,28), (13,28) or (14,28) on the main road.
@ All three entry points converge with the player at (13,24) facing the rival at (13,23).
FervorFieldCity_ARHU_EventScript_MeetTheRival_Left::
	lockall
	setvar VAR_0x8008, 0
	goto FervorFieldCity_ARHU_EventScript_MeetTheRival_Main

FervorFieldCity_ARHU_EventScript_MeetTheRival_Center::
	lockall
	setvar VAR_0x8008, 1
	goto FervorFieldCity_ARHU_EventScript_MeetTheRival_Main

FervorFieldCity_ARHU_EventScript_MeetTheRival_Right::
	lockall
	setvar VAR_0x8008, 2
	goto FervorFieldCity_ARHU_EventScript_MeetTheRival_Main

FervorFieldCity_ARHU_EventScript_MeetTheRival_Main::
	delay 30
	playbgm MUS_RG_OAK, TRUE
	msgbox FervorFieldCity_ARHU_Text_Rival_GetLost, MSGBOX_DEFAULT
	closemessage
	special SpawnCameraObject
	call_if_eq VAR_0x8008, 0, FervorFieldCity_ARHU_EventScript_MeetTheRival_CameraLeft
	call_if_eq VAR_0x8008, 1, FervorFieldCity_ARHU_EventScript_MeetTheRival_CameraCenter
	call_if_eq VAR_0x8008, 2, FervorFieldCity_ARHU_EventScript_MeetTheRival_CameraRight
	msgbox FervorFieldCity_ARHU_Text_RudeTrainer_DontGetInMyWay, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_FERVOR_FIELD_CITY_RUDE_TRAINER, FervorFieldCity_ARHU_Movement_RudeTrainerLeaves
	waitmovement 0
	delay 90
	call_if_eq VAR_0x8008, 0, FervorFieldCity_ARHU_EventScript_MeetTheRival_PlayerLeft
	call_if_eq VAR_0x8008, 1, FervorFieldCity_ARHU_EventScript_MeetTheRival_PlayerCenter
	call_if_eq VAR_0x8008, 2, FervorFieldCity_ARHU_EventScript_MeetTheRival_PlayerRight
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Rival_TheyMakeAllKinds, MSGBOX_DEFAULT
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL, Common_Movement_FaceDown
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Rival_YouHadMeWaiting, MSGBOX_DEFAULT
	closemessage
	msgbox FervorFieldCity_ARHU_Text_Friend_EvenAfterHePushedYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_ExclaimFaceLeft
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL, FervorFieldCity_ARHU_Movement_ExclaimFaceLeft
	waitmovement 0
	clearflag FLAG_HIDE_FERVOR_FIELD_CITY_RIVAL_FRIEND
	addobject LOCALID_FERVOR_FIELD_CITY_RIVAL_FRIEND
	delay 30
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL_FRIEND, FervorFieldCity_ARHU_Movement_FriendApproach
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Friend_PureExpectation, MSGBOX_DEFAULT
	msgbox FervorFieldCity_ARHU_Text_Rival_StillSoundsFiredUp, MSGBOX_DEFAULT
	msgbox FervorFieldCity_ARHU_Text_Friend_SoClueless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL_FRIEND, FervorFieldCity_ARHU_Movement_FriendFacePlayer
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Friend_WhatAboutYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL_FRIEND, FervorFieldCity_ARHU_Movement_FriendLeaves
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL, Common_Movement_FaceRight
	waitmovement LOCALID_FERVOR_FIELD_CITY_RIVAL_FRIEND
	msgbox FervorFieldCity_ARHU_Text_Rival_AllKinds, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL, FervorFieldCity_ARHU_Movement_RivalFaceDownExclaim
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Rival_HeadingToSafariGate, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL, FervorFieldCity_ARHU_Movement_RivalLeaves
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement LOCALID_FERVOR_FIELD_CITY_RIVAL
	special RemoveCameraObject
	removeobject LOCALID_FERVOR_FIELD_CITY_RIVAL
	removeobject LOCALID_FERVOR_FIELD_CITY_RUDE_TRAINER
	removeobject LOCALID_FERVOR_FIELD_CITY_RIVAL_FRIEND
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_RIVAL
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_RUDE_TRAINER
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_RIVAL_FRIEND
	setvar VAR_FERVOR_FIELD_RIVAL_INTRO_STATE, 1
	fadedefaultbgm
	releaseall
	end

FervorFieldCity_ARHU_EventScript_MeetTheRival_CameraLeft::
	applymovement LOCALID_CAMERA, FervorFieldCity_ARHU_Movement_ToRival_Left
	waitmovement 0
	return

FervorFieldCity_ARHU_EventScript_MeetTheRival_CameraCenter::
	applymovement LOCALID_CAMERA, FervorFieldCity_ARHU_Movement_ToRival_Center
	waitmovement 0
	return

FervorFieldCity_ARHU_EventScript_MeetTheRival_CameraRight::
	applymovement LOCALID_CAMERA, FervorFieldCity_ARHU_Movement_ToRival_Right
	waitmovement 0
	return

FervorFieldCity_ARHU_EventScript_MeetTheRival_PlayerLeft::
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_ToRival_Left
	waitmovement 0
	return

FervorFieldCity_ARHU_EventScript_MeetTheRival_PlayerCenter::
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_ToRival_Center
	waitmovement 0
	return

FervorFieldCity_ARHU_EventScript_MeetTheRival_PlayerRight::
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_ToRival_Right
	waitmovement 0
	return

@ Shared by camera and player: (12,28) -> (13,24)
FervorFieldCity_ARHU_Movement_ToRival_Left:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ (13,28) -> (13,24)
FervorFieldCity_ARHU_Movement_ToRival_Center:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ (14,28) -> (13,24)
FervorFieldCity_ARHU_Movement_ToRival_Right:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

FervorFieldCity_ARHU_Movement_RudeTrainerLeaves:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	set_invisible
	step_end

FervorFieldCity_ARHU_Movement_ExclaimFaceLeft:
	emote_exclamation_mark
	face_left
	step_end

FervorFieldCity_ARHU_Movement_FriendApproach:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

FervorFieldCity_ARHU_Movement_FriendFacePlayer:
	walk_down
	face_right
	step_end

FervorFieldCity_ARHU_Movement_FriendLeaves:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	set_invisible
	step_end

FervorFieldCity_ARHU_Movement_RivalFaceDownExclaim:
	face_down
	emote_exclamation_mark
	step_end

FervorFieldCity_ARHU_Movement_RivalLeaves:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	set_invisible
	step_end

FervorFieldCity_ARHU_Text_Rival_GetLost::
	.string "Westin: You sure love to chit chat,\n"
	.string "get lost!\l"
	.string "I'm waiting on a friend.$"

FervorFieldCity_ARHU_Text_RudeTrainer_DontGetInMyWay::
	.string "???: Standing around on a busy road,\n"
	.string "on a day like this!\l"
	.string "Don't get in my way again!$"

FervorFieldCity_ARHU_Text_Rival_TheyMakeAllKinds::
	.string "Westin: They really make\n"
	.string "all kinds…$"

FervorFieldCity_ARHU_Text_Rival_YouHadMeWaiting::
	.string "Oh, hey!\n"
	.string "You sure had me waiting!\l"
	.string "Thought you might've got cold feet!\p"
	.string "Oh, him? Some guy I know.\n"
	.string "I'm not taking him seriously…\p"
	.string "I guess everyone is just fired up!$"

FervorFieldCity_ARHU_Text_Friend_EvenAfterHePushedYou::
	.string "???: Even after he pushed\n"
	.string "you like that?$"

FervorFieldCity_ARHU_Text_Friend_PureExpectation::
	.string "???: To me that didn't look like\n"
	.string "excitement at all,\l"
	.string "It's pure expectation.\l"
	.string "I've seen people like that.\l"
	.string "They come to prove something…$"

FervorFieldCity_ARHU_Text_Rival_StillSoundsFiredUp::
	.string "Westin: Hmm… You got a point…\n"
	.string "But wait,\l"
	.string "that still sounds like fired up to me!$"

FervorFieldCity_ARHU_Text_Friend_SoClueless::
	.string "???: Ugh geez,\n"
	.string "can you be so clueless?$"

FervorFieldCity_ARHU_Text_Friend_WhatAboutYou::
	.string "???: What about you?\n"
	.string "Hmm…\l"
	.string "…!\l"
	.string "Oh shoot!\l"
	.string "Curiosity got the best of me!\l"
	.string "I'm gonna be late!$"

FervorFieldCity_ARHU_Text_Rival_AllKinds::
	.string "Westin: All kinds…\n"
	.string "…\l"
	.string "…!$"

FervorFieldCity_ARHU_Text_Rival_HeadingToSafariGate::
	.string "Wait! If she's late, we're late!\n"
	.string "I'm heading to the Safari Gate!\l"
	.string "Just follow the path north!\l"
	.string "Don't fall behind!$"

@ Tanglewood's speech at the Safari gate (ported from HMA script "tanglewood_speech").
@ Fires once when the player steps on (23,12) or (25,12). Both entries converge with the
@ player at (26,9) facing up, beside Holt (25,9). Tanglewood ends at (25,7) facing left.
@ Holt, the Hiker, Mira and Westin each enter the gate door at (24,5) and are removed.
FervorFieldCity_ARHU_EventScript_TanglewoodSpeech_Left::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_PlayerToGate_Left
	waitmovement 0
	goto FervorFieldCity_ARHU_EventScript_TanglewoodSpeech_Main

FervorFieldCity_ARHU_EventScript_TanglewoodSpeech_Right::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_PlayerToGate_Right
	waitmovement 0
	goto FervorFieldCity_ARHU_EventScript_TanglewoodSpeech_Main

FervorFieldCity_ARHU_EventScript_TanglewoodSpeech_Main::
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, FervorFieldCity_ARHU_Movement_CameraToGate
	waitmovement 0
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, FervorFieldCity_ARHU_Movement_TanglewoodStepUp
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Tanglewood_Introduction, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, Common_Movement_FaceUp
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Tanglewood_EveryPokemonHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, Common_Movement_FaceDown
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Tanglewood_Rules, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, FervorFieldCity_ARHU_Movement_TanglewoodStepAside
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_Holt_OutOfTheWay, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_HOLT, FervorFieldCity_ARHU_Movement_HoltToDoor
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, Common_Movement_ExclamationMark
	waitmovement LOCALID_FERVOR_FIELD_CITY_GATE_HOLT
	call FervorFieldCity_ARHU_EventScript_SafariGate_OpenDoor
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_HOLT, FervorFieldCity_ARHU_Movement_EnterDoor
	waitmovement LOCALID_FERVOR_FIELD_CITY_GATE_HOLT
	call FervorFieldCity_ARHU_EventScript_SafariGate_CloseDoor
	removeobject LOCALID_FERVOR_FIELD_CITY_GATE_HOLT
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_GATE_HOLT
	msgbox FervorFieldCity_ARHU_Text_Hiker_IGotHereFirst, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_HIKER, FervorFieldCity_ARHU_Movement_HikerToDoor
	waitmovement 0
	call FervorFieldCity_ARHU_EventScript_SafariGate_OpenDoor
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_HIKER, FervorFieldCity_ARHU_Movement_EnterDoor
	waitmovement 0
	call FervorFieldCity_ARHU_EventScript_SafariGate_CloseDoor
	removeobject LOCALID_FERVOR_FIELD_CITY_GATE_HIKER
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_GATE_HIKER
	msgbox FervorFieldCity_ARHU_Text_Mira_SoItStartsLikeThat, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, FervorFieldCity_ARHU_Movement_MiraToDoor
	waitmovement 0
	call FervorFieldCity_ARHU_EventScript_SafariGate_OpenDoor
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, FervorFieldCity_ARHU_Movement_EnterDoor
	waitmovement 0
	call FervorFieldCity_ARHU_EventScript_SafariGate_CloseDoor
	removeobject LOCALID_FERVOR_FIELD_CITY_GATE_MIRA
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_GATE_MIRA
	msgbox FervorFieldCity_ARHU_Text_Westin_ThatsOurCue, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN, FervorFieldCity_ARHU_Movement_WestinToDoor
	waitmovement 0
	call FervorFieldCity_ARHU_EventScript_SafariGate_OpenDoor
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN, FervorFieldCity_ARHU_Movement_EnterDoor
	waitmovement 0
	call FervorFieldCity_ARHU_EventScript_SafariGate_CloseDoor
	removeobject LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_GATE_WESTIN
	applymovement LOCALID_CAMERA, FervorFieldCity_ARHU_Movement_CameraBackToPlayer
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_FERVOR_FIELD_TANGLEWOOD_STATE, 1
	releaseall
	end

@ Gate refuses re-entry once VAR_FERVOR_FIELD_TANGLEWOOD_STATE == 2 (player already passed the challenge).
FervorFieldCity_ARHU_EventScript_SafariGate_AlreadyPassed::
	lockall
	msgbox FervorFieldCity_ARHU_Text_SafariGate_AlreadyPassed, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

@ The FRLG gate door has no Emerald door animation registered, so these are no-ops visually
@ but keep the timing of the original script.
FervorFieldCity_ARHU_EventScript_SafariGate_OpenDoor::
	opendoor 24, 5
	waitdooranim
	return

FervorFieldCity_ARHU_EventScript_SafariGate_CloseDoor::
	closedoor 24, 5
	waitdooranim
	return

@ (25,12) -> (26,9)
FervorFieldCity_ARHU_Movement_PlayerToGate_Right:
	walk_up
	walk_up
	walk_right
	walk_up
	step_end

@ (23,12) -> (26,9)
FervorFieldCity_ARHU_Movement_PlayerToGate_Left:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

FervorFieldCity_ARHU_Movement_CameraToGate:
	walk_left
	walk_left
	step_end

FervorFieldCity_ARHU_Movement_CameraBackToPlayer:
	walk_right
	walk_right
	step_end

@ (24,8) -> (24,7)
FervorFieldCity_ARHU_Movement_TanglewoodStepUp:
	walk_up
	face_down
	step_end

@ (24,7) -> (25,7), clearing the path to the door
FervorFieldCity_ARHU_Movement_TanglewoodStepAside:
	walk_right
	face_left
	step_end

@ (25,9) -> (24,6)
FervorFieldCity_ARHU_Movement_HoltToDoor:
	walk_up
	walk_left
	walk_up
	walk_up
	step_end

@ (24,9) -> (24,6)
FervorFieldCity_ARHU_Movement_HikerToDoor:
	walk_up
	walk_up
	walk_up
	step_end

@ (23,9) -> (24,6)
FervorFieldCity_ARHU_Movement_MiraToDoor:
	walk_up
	walk_right
	walk_up
	walk_up
	step_end

@ (22,9) -> (24,6)
FervorFieldCity_ARHU_Movement_WestinToDoor:
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

@ (24,6) -> through the door at (24,5)
FervorFieldCity_ARHU_Movement_EnterDoor:
	walk_up
	set_invisible
	step_end

FervorFieldCity_ARHU_Text_Tanglewood_Introduction::
	.string "???: Attention!\n"
	.string "You all look competitive enough!\l"
	.string "Ease up,\l"
	.string "You won't lose to each other today.\l"
	.string "Allow me to introduce myself!\p"
	.string "Tanglewood: I am the Professor,\n"
	.string "Tanglewood.\l"
	.string "Long ago,\l"
	.string "I used to be a Pokémon Ranger.\l"
	.string "Now, I look after this place and\l"
	.string "watch young hopefuls learn to\l"
	.string "care for these creatures as\l"
	.string "they do for themselves.$"

FervorFieldCity_ARHU_Text_Tanglewood_EveryPokemonHere::
	.string "Tanglewood: Every Pokémon here\n"
	.string "comes from a different land.\l"
	.string "Some are strong.\l"
	.string "Some are cautious.\l"
	.string "All of them are protected.\p"
	.string "Tanglewood: Now… I know, I know…\n"
	.string "You've come to be the best!\l"
	.string "But make one thing clear,\l"
	.string "You don't enter the Safari Grounds\l"
	.string "to conquer Pokémon.\p"
	.string "You must enter to understand them.\n"
	.string "That is why you are here.$"

FervorFieldCity_ARHU_Text_Tanglewood_Rules::
	.string "Tanglewood: You may encounter those\n"
	.string "who have also started inside.\l"
	.string "Be helpful to one another but know\l"
	.string "that you have your own time limit!\l"
	.string "You will be given 30 Poké Balls\l"
	.string "to aid you.\l"
	.string "Use them wisely.\p"
	.string "Once either runs out, you will be\n"
	.string "exited with any Pokémon you have.\l"
	.string "You will choose only one\l"
	.string "to be your partner.\l"
	.string "I and the rest of my staff will be\l"
	.string "waiting in case of emergency.\p"
	.string "If you'll accept it,\n"
	.string "your journey starts here!\l"
	.string "Inside the Safari Zone!\p"
	.string "Now go on!\n"
	.string "Let's see what kind of Trainer\l"
	.string "you really are.$"

FervorFieldCity_ARHU_Text_Holt_OutOfTheWay::
	.string "???: Out of the way.\n"
	.string "Holt waits for no one.$"

FervorFieldCity_ARHU_Text_Hiker_IGotHereFirst::
	.string "???: Hey wait!\n"
	.string "I got here first!$"

FervorFieldCity_ARHU_Text_Mira_SoItStartsLikeThat::
	.string "???: So… it starts like that?\n"
	.string "Some people decide fast…\p"
	.string "Welp,\n"
	.string "good luck you two.\p"
	.string "Mira: The name is Mira by the way.\n"
	.string "See you inside!$"

FervorFieldCity_ARHU_Text_Westin_ThatsOurCue::
	.string "Westin: Guess that's our cue.\n"
	.string "Tagging in!$"

FervorFieldCity_ARHU_Text_SafariGate_AlreadyPassed::
	.string "Hey! You've already passed!$"

@ Local copies of FuchsiaCity_Frlg scripts (FRLG originals are IS_FRLG-only)

FervorFieldCity_ARHU_EventScript_LittleBoy::
	msgbox FervorFieldCity_ARHU_Text_DidYouTrySafariGame, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_OldMan::
	msgbox FervorFieldCity_ARHU_Text_SafariZoneZooInFront, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_Erik::
	msgbox FervorFieldCity_ARHU_Text_WheresSara, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_Youngster::
	msgbox FervorFieldCity_ARHU_Text_ItemBallInThere, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_SubstituteTutor::
	msgbox FervorFieldCity_ARHU_Text_SubstituteTutor, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_CitySign::
	msgbox FervorFieldCity_ARHU_Text_CitySign, MSGBOX_SIGN
	end

FervorFieldCity_ARHU_EventScript_SafariZoneSign::
	msgbox FervorFieldCity_ARHU_Text_SafariZoneSign, MSGBOX_SIGN
	end

FervorFieldCity_ARHU_EventScript_SafariGameSign::
	msgbox FervorFieldCity_ARHU_Text_SafariGameSign, MSGBOX_SIGN
	end

FervorFieldCity_ARHU_EventScript_WardensHomeSign::
	msgbox FervorFieldCity_ARHU_Text_WardensHomeSign, MSGBOX_SIGN
	end

FervorFieldCity_ARHU_EventScript_GymSign::
	msgbox FervorFieldCity_ARHU_Text_GymSign, MSGBOX_SIGN
	end

FervorFieldCity_ARHU_Text_DidYouTrySafariGame::
	.string "Did you try the SAFARI GAME?\p"
	.string "There are some rare POKéMON that\n"
	.string "can only be caught there.$"

FervorFieldCity_ARHU_Text_SafariZoneZooInFront::
	.string "The SAFARI ZONE has a zoo in front\n"
	.string "of the entrance.\p"
	.string "Out back is the SAFARI GAME for\n"
	.string "catching POKéMON.$"

FervorFieldCity_ARHU_Text_WheresSara::
	.string "ERIK: Where's SARA?\n"
	.string "I said I'd meet her here.$"

FervorFieldCity_ARHU_Text_ItemBallInThere::
	.string "That item ball in there…\n"
	.string "Were you wanting that?\p"
	.string "Me, too!\n"
	.string "…Huh? That's a POKéMON?$"

FervorFieldCity_ARHU_Text_SubstituteTutor::
	.string "I can teach a POKéMON how to use\n"
	.string "SUBSTITUTE…\p"
	.string "But I'm taking a break right now.$"

FervorFieldCity_ARHU_Text_CitySign::
	.string "FUCHSIA CITY\n"
	.string "Behold! It's Passion Pink!$"

FervorFieldCity_ARHU_Text_SafariZoneSign::
	.string "POKéMON PARADISE\n"
	.string "SAFARI ZONE$"

FervorFieldCity_ARHU_Text_SafariGameSign::
	.string "SAFARI GAME\n"
	.string "POKéMON-U-CATCH!$"

FervorFieldCity_ARHU_Text_WardensHomeSign::
	.string "SAFARI ZONE\n"
	.string "WARDEN'S HOME$"

FervorFieldCity_ARHU_Text_GymSign::
	.string "FUCHSIA CITY POKéMON GYM\n"
	.string "LEADER: KOGA\l"
	.string "The Poisonous Ninja Master$"
