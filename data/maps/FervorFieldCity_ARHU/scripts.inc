FervorFieldCity_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FervorFieldCity_ARHU_OnTransition
	.byte 0

FervorFieldCity_ARHU_OnTransition::
	call_if_eq VAR_FERVOR_FIELD_STARTER_SPEECH_STATE, 1, FervorFieldCity_ARHU_EventScript_PlaceExitSpeechCast
	goto_if_ne VAR_FERVOR_FIELD_RIVAL_INTRO_STATE, 0, FervorFieldCity_ARHU_OnTransition_End
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_RIVAL_FRIEND
FervorFieldCity_ARHU_OnTransition_End::
	end

@ The player is about to walk out of the Safari gate: Tanglewood waits at (25,7) and Mira, who finished
@ first, is already beside him at (25,8).
FervorFieldCity_ARHU_EventScript_PlaceExitSpeechCast::
	clearflag FLAG_HIDE_FERVOR_FIELD_CITY_GATE_MIRA
	setobjectxyperm LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, 25, 7
	setobjectxyperm LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, 25, 8
	return

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
	msgbox FervorFieldCity_ARHU_Text_Rival_TheyMakeAllKinds, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_FERVOR_FIELD_CITY_RIVAL, FervorFieldCity_ARHU_Movement_RivalFaceDownExclaim
	waitmovement 0
	delay 20
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
	msgbox FervorFieldCity_ARHU_Text_Rival_PokeblockCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	special GiveFervorFieldStarterPokeblocks
	playfanfare MUS_OBTAIN_ITEM
	message FervorFieldCity_ARHU_Text_ReceivedPokeblocks
	waitmessage
	waitfanfare
	closemessage
	msgbox FervorFieldCity_ARHU_Text_Rival_UseThose, MSGBOX_DEFAULT
	closemessage
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

FervorFieldCity_ARHU_Text_Rival_PokeblockCase::
	.string "Westin: Oh yeah, I remembered to get\n"
	.string "you a case as well!\p"
	.string "I grinded up all my berries for you!\p"
	.string "I only made 10 blocks, so I'm\n"
	.string "giving you half of mine.$"

FervorFieldCity_ARHU_Text_ReceivedPokeblocks::
	.string "{PLAYER} received 5 POKéBLOCKs!$"

FervorFieldCity_ARHU_Text_Rival_UseThose::
	.string "Westin: Use those to make it easier\n"
	.string "to catch Pokémon when we get in!\p"
	.string "Any left over can make your Pokémon\n"
	.string "more beautiful, cool, cute, smart\l"
	.string "or tough outside the Safari, too!$"

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
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, Common_Movement_FaceLeft
	waitmovement 0
	delay 25
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, Common_Movement_FaceRight
	waitmovement 0
	delay 25
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
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN, Common_Movement_FaceRight
	waitmovement 0
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
	setflag FLAG_SYS_POKEMON_GET
	releaseall
	end

@ Tanglewood's exit speech. Fires once at (24,7) after the Safari challenge is finished (the player has
@ their starter in VAR_FERVOR_FIELD_PLAYER_STARTER). While that is pending, OnTransition places Tanglewood
@ at (25,7) and Mira at (25,8): Mira left the Safari first and already has her (secret) partner.
@ Tanglewood talks to the player and hands over the POKéDEX, then Westin walks out of the Safari gate
@ door last and receives his own.
@ Westin's starter counters the player's type. Then the player battles Westin, is healed, and battles Mira.
@ Mira runs off first, then Westin, win or lose.
FervorFieldCity_ARHU_EventScript_StarterSpeech::
	lockall
	setvar VAR_FERVOR_FIELD_STARTER_SPEECH_STATE, 2
	bufferspeciesname STR_VAR_1, VAR_FERVOR_FIELD_PLAYER_STARTER
	special FervorFieldGetRivalStarterGroup
	call_if_eq VAR_RESULT, 0, FervorFieldCity_ARHU_EventScript_StarterSpeech_WestinSquirtle
	call_if_eq VAR_RESULT, 1, FervorFieldCity_ARHU_EventScript_StarterSpeech_WestinChimchar
	call_if_eq VAR_RESULT, 2, FervorFieldCity_ARHU_EventScript_StarterSpeech_WestinSprigatito
	bufferspeciesname STR_VAR_2, VAR_FERVOR_FIELD_WESTIN_STARTER
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, Common_Movement_FaceLeft
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	bufferspeciesname STR_VAR_1, VAR_FERVOR_FIELD_PLAYER_STARTER
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_WellWhatDoWeHaveHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, Common_Movement_FaceLeft
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Mira_GotMineToo, MSGBOX_DEFAULT
	closemessage
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_Pokedex, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message FervorFieldCity_ARHU_Text_ExitSpeech_ReceivedPokedex
	waitmessage
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_CatchingTools, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_HowToUseBalls, MSGBOX_DEFAULT
	closemessage
	setobjectxyperm LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN, 24, 5
	clearflag FLAG_HIDE_FERVOR_FIELD_CITY_GATE_WESTIN
	call FervorFieldCity_ARHU_EventScript_SafariGate_OpenDoor
	addobject LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN, FervorFieldCity_ARHU_Movement_WestinComesOut
	waitmovement LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN
	call FervorFieldCity_ARHU_EventScript_SafariGate_CloseDoor
	setobjectxyperm LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN, 23, 7
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Westin_MadeIt, MSGBOX_DEFAULT
	closemessage
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_WhatDidYouGet, MSGBOX_DEFAULT
	closemessage
	bufferspeciesname STR_VAR_1, VAR_FERVOR_FIELD_PLAYER_STARTER
	bufferspeciesname STR_VAR_2, VAR_FERVOR_FIELD_WESTIN_STARTER
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Westin_GotMine, MSGBOX_DEFAULT
	closemessage
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_WestinPokedex, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message FervorFieldCity_ARHU_Text_ExitSpeech_WestinReceivedPokedex
	waitmessage
	waitfanfare
	closemessage
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Westin_LetsBattle, MSGBOX_DEFAULT
	closemessage
	@ Mira steps in under the player so she faces them for the rest of the scene
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, Common_Movement_ExclamationMark
	waitmovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, FervorFieldCity_ARHU_Movement_MiraStepUp
	waitmovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA
	setobjectxyperm LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, 24, 8
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Mira_WantIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_GoOnThen, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	setflag FLAG_FERVOR_FIELD_RIVAL_NO_WHITEOUT
	call_if_eq VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_SQUIRTLE, FervorFieldCity_ARHU_EventScript_StarterSpeech_BattleSquirtle
	call_if_eq VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_CHIMCHAR, FervorFieldCity_ARHU_EventScript_StarterSpeech_BattleChimchar
	call_if_eq VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_SPRIGATITO, FervorFieldCity_ARHU_EventScript_StarterSpeech_BattleSprigatito
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_0x8009, VAR_RESULT
	call FervorFieldCity_ARHU_EventScript_StarterSpeech_FaceWestin
	call_if_ne VAR_0x8009, B_OUTCOME_WON, FervorFieldCity_ARHU_EventScript_StarterSpeech_WestinWon
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_HealThem, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call FervorFieldCity_ARHU_EventScript_StarterSpeech_FaceMira
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Mira_MyTurn, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_FERVOR_MIRA_EEVEE, FervorFieldCity_ARHU_Text_ExitSpeech_Mira_Defeat
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_0x8009, VAR_RESULT
	clearflag FLAG_FERVOR_FIELD_RIVAL_NO_WHITEOUT
	special HealPlayerParty
	call FervorFieldCity_ARHU_EventScript_StarterSpeech_FaceMira
	call_if_eq VAR_0x8009, B_OUTCOME_WON, FervorFieldCity_ARHU_EventScript_StarterSpeech_MiraLost
	call_if_ne VAR_0x8009, B_OUTCOME_WON, FervorFieldCity_ARHU_EventScript_StarterSpeech_MiraWon
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, FervorFieldCity_ARHU_Movement_MiraRunsOff
	waitmovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA
	removeobject LOCALID_FERVOR_FIELD_CITY_GATE_MIRA
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_GATE_MIRA
	call FervorFieldCity_ARHU_EventScript_StarterSpeech_FaceWestin
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Westin_GoodLuck, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN, FervorFieldCity_ARHU_Movement_WestinRunsOff
	waitmovement LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN
	removeobject LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_GATE_WESTIN
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, Common_Movement_FaceLeft
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_StartYourJourney, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, FervorFieldCity_ARHU_Movement_TanglewoodToDoor
	waitmovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD
	call FervorFieldCity_ARHU_EventScript_SafariGate_OpenDoor
	applymovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD, FervorFieldCity_ARHU_Movement_EnterDoor
	waitmovement LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD
	call FervorFieldCity_ARHU_EventScript_SafariGate_CloseDoor
	removeobject LOCALID_FERVOR_FIELD_CITY_TANGLEWOOD
	setflag FLAG_HIDE_FERVOR_FIELD_CITY_TANGLEWOOD
	setflag FLAG_FERVOR_FIELD_SAFARI_CHALLENGE_COMPLETE
	removeobject LOCALID_FERVOR_FIELD_CITY_MART_BLOCKER
	removeobject LOCALID_FERVOR_FIELD_CITY_POKEMON_CENTER_BLOCKER
	removeobject LOCALID_FERVOR_FIELD_CITY_MOVE_DELETER_BLOCKER
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_PlayerPastGate
	waitmovement 0
	releaseall
	end

@ The speech trigger is only on (24,7). Triggers on the row above (y=6) pull the player onto it
@ so they can't sidestep around Tanglewood and Mira.
FervorFieldCity_ARHU_EventScript_StarterSpeechPull_X21::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_StarterSpeechPull_X21
	waitmovement 0
	goto FervorFieldCity_ARHU_EventScript_StarterSpeech

FervorFieldCity_ARHU_EventScript_StarterSpeechPull_X22::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_StarterSpeechPull_X22
	waitmovement 0
	goto FervorFieldCity_ARHU_EventScript_StarterSpeech

FervorFieldCity_ARHU_EventScript_StarterSpeechPull_X23::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_StarterSpeechPull_X23
	waitmovement 0
	goto FervorFieldCity_ARHU_EventScript_StarterSpeech

FervorFieldCity_ARHU_EventScript_StarterSpeechPull_X25::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_StarterSpeechPull_X25
	waitmovement 0
	goto FervorFieldCity_ARHU_EventScript_StarterSpeech

FervorFieldCity_ARHU_EventScript_StarterSpeechPull_X26::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_StarterSpeechPull_X26
	waitmovement 0
	goto FervorFieldCity_ARHU_EventScript_StarterSpeech

FervorFieldCity_ARHU_EventScript_StarterSpeechPull_X27::
	lockall
	applymovement LOCALID_PLAYER, FervorFieldCity_ARHU_Movement_StarterSpeechPull_X27
	waitmovement 0
	goto FervorFieldCity_ARHU_EventScript_StarterSpeech

FervorFieldCity_ARHU_Movement_StarterSpeechPull_X21:
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

FervorFieldCity_ARHU_Movement_StarterSpeechPull_X22:
	walk_right
	walk_right
	walk_down
	step_end

FervorFieldCity_ARHU_Movement_StarterSpeechPull_X23:
	walk_right
	walk_down
	step_end

FervorFieldCity_ARHU_Movement_StarterSpeechPull_X25:
	walk_left
	walk_down
	step_end

FervorFieldCity_ARHU_Movement_StarterSpeechPull_X26:
	walk_left
	walk_left
	walk_down
	step_end

FervorFieldCity_ARHU_Movement_StarterSpeechPull_X27:
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

@ Battles can reload the scene, so faces are set again after each one, whatever the outcome
FervorFieldCity_ARHU_EventScript_StarterSpeech_FaceWestin::
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_WESTIN, Common_Movement_FaceRight
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_FaceMira::
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_MIRA, Common_Movement_FaceUp
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_WestinSquirtle::
	setvar VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_SQUIRTLE
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_WestinChimchar::
	setvar VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_CHIMCHAR
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_WestinSprigatito::
	setvar VAR_FERVOR_FIELD_WESTIN_STARTER, SPECIES_SPRIGATITO
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_BattleSquirtle::
	trainerbattle_no_intro TRAINER_FERVOR_WESTIN_SQUIRTLE, FervorFieldCity_ARHU_Text_ExitSpeech_Westin_Defeat
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_BattleChimchar::
	trainerbattle_no_intro TRAINER_FERVOR_WESTIN_CHIMCHAR, FervorFieldCity_ARHU_Text_ExitSpeech_Westin_Defeat
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_BattleSprigatito::
	trainerbattle_no_intro TRAINER_FERVOR_WESTIN_SPRIGATITO, FervorFieldCity_ARHU_Text_ExitSpeech_Westin_Defeat
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_WestinWon::
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Westin_Victory, MSGBOX_DEFAULT
	closemessage
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_MiraWon::
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Mira_Victory, MSGBOX_DEFAULT
	closemessage
	return

FervorFieldCity_ARHU_EventScript_StarterSpeech_MiraLost::
	msgbox FervorFieldCity_ARHU_Text_ExitSpeech_Mira_AfterLoss, MSGBOX_DEFAULT
	closemessage
	return

@ Out of the Safari gate door at (24,5), then around the player to stand beside them at (23,7)
FervorFieldCity_ARHU_Movement_WestinComesOut:
	walk_fast_down
	walk_fast_left
	walk_fast_down
	face_right
	step_end

@ (25,8) -> (24,8), directly below the player
FervorFieldCity_ARHU_Movement_MiraStepUp:
	walk_left
	face_up
	step_end

@ (25,7) -> (24,6), in front of the Safari gate door
FervorFieldCity_ARHU_Movement_TanglewoodToDoor:
	walk_up
	walk_left
	step_end

@ (24,7) -> (23,13): down the plaza and out through the south gate, past the camper
FervorFieldCity_ARHU_Movement_PlayerPastGate:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

@ (23,7) -> (23,12), just off screen
FervorFieldCity_ARHU_Movement_WestinRunsOff:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ (24,8) -> (25,12), just off screen
FervorFieldCity_ARHU_Movement_MiraRunsOff:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	step_end

@ The camper guards (23,12)/(25,12). VAR_FERVOR_FIELD_TANGLEWOOD_STATE:
@   1 = speech seen, challenge not done: nobody gets past him, player is pushed back north.
@   2 = challenge done: player is pushed one tile south, so heading out is allowed and
@       heading back in is always refused.
FervorFieldCity_ARHU_EventScript_SafariGate_ChallengeNotDone::
	lockall
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_CAMPER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_SafariGate_ChallengeNotDone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	releaseall
	end

FervorFieldCity_ARHU_EventScript_SafariGate_AlreadyPassed::
	lockall
	applymovement LOCALID_FERVOR_FIELD_CITY_GATE_CAMPER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FervorFieldCity_ARHU_Text_SafariGate_AlreadyPassed, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

@ The gate (METATILE_FuchsiaCity_SafariZoneDoor) animates with the FRLG Safari door art through the
@ Emerald door system (src/field_door.c, "Fervor Field City" entries).
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
	.string "to be your partner.\p"
	.string "There are 27 Pokémon in total to\n"
	.string "be found, of three types:\l"
	.string "Water, Fire and Grass.\p"
	.string "Only one can be your starter,\n"
	.string "so choose wisely!\p"
	.string "If you don't find what you are\n"
	.string "looking for, there are 4 zones to\l"
	.string "explore, and the Pokémon vary\l"
	.string "within each zone.\p"
	.string "So don't be shy to walk a bit.\n"
	.string "Keep hunting until you find\l"
	.string "the one!\p"
	.string "I and the rest of my staff will be\n"
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
	.string "Congratulations on completing the\n"
	.string "challenge!\p"
	.string "Good luck on your journey!$"

FervorFieldCity_ARHU_Text_SafariGate_ChallengeNotDone::
	.string "Hold it! Nobody gets past me until\n"
	.string "they've completed the challenge.$"

@ Camper guarding the gate. VAR_FERVOR_FIELD_TANGLEWOOD_STATE: 0 = not been through yet, 1 = challenge in progress, 2 = finished.
FervorFieldCity_ARHU_EventScript_GateCamper::
	lock
	faceplayer
	goto_if_eq VAR_FERVOR_FIELD_TANGLEWOOD_STATE, 2, FervorFieldCity_ARHU_EventScript_GateCamper_Passed
	goto_if_eq VAR_FERVOR_FIELD_TANGLEWOOD_STATE, 1, FervorFieldCity_ARHU_EventScript_GateCamper_InProgress
	msgbox FervorFieldCity_ARHU_Text_GateCamper_Welcome, MSGBOX_DEFAULT
	release
	end

FervorFieldCity_ARHU_EventScript_GateCamper_InProgress::
	msgbox FervorFieldCity_ARHU_Text_GateCamper_NotYet, MSGBOX_DEFAULT
	release
	end

FervorFieldCity_ARHU_EventScript_GateCamper_Passed::
	msgbox FervorFieldCity_ARHU_Text_GateCamper_Passed, MSGBOX_DEFAULT
	release
	end

FervorFieldCity_ARHU_Text_GateCamper_Welcome::
	.string "Hey there! Are you here for the\n"
	.string "Safari challenge?\p"
	.string "The Safari Grounds are just north\n"
	.string "of here, past this gate.\p"
	.string "Professor Tanglewood will explain\n"
	.string "everything.\p"
	.string "Nobody gets through the Safari\n"
	.string "challenge without completing it,\l"
	.string "so take your time and do your best!$"

FervorFieldCity_ARHU_Text_GateCamper_Passed::
	.string "You're back from the Safari\n"
	.string "challenge, right?\p"
	.string "Congratulations! You may move along.$"

FervorFieldCity_ARHU_Text_GateCamper_NotYet::
	.string "Hey there! Are you here for the\n"
	.string "Safari challenge?\p"
	.string "The challenge has to be completed\n"
	.string "before anyone can move along.\p"
	.string "Good luck out there!$"

@ Local copies of FuchsiaCity_Frlg sign scripts (FRLG originals are IS_FRLG-only)

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

@ Door blockers. The Mart, Pokémon Center and Move Deleter blockers are hidden by
@ FLAG_FERVOR_FIELD_SAFARI_CHALLENGE_COMPLETE (set at the end of Tanglewood's exit speech).
@ The Gym blocker has no flag yet: the Gym stays shut until its leader is designed.
FervorFieldCity_ARHU_EventScript_GymBlocker::
	msgbox FervorFieldCity_ARHU_Text_GymBlocker, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_MartBlocker::
	msgbox FervorFieldCity_ARHU_Text_MartBlocker, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_PokemonCenterBlocker::
	msgbox FervorFieldCity_ARHU_Text_PokemonCenterBlocker, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_MoveDeleterBlocker::
	msgbox FervorFieldCity_ARHU_Text_MoveDeleterBlocker, MSGBOX_NPC
	end

@ Only reachable while the challenge is running (VAR_FERVOR_FIELD_TANGLEWOOD_STATE 1): he waits by the gate.
FervorFieldCity_ARHU_EventScript_Tanglewood::
	msgbox FervorFieldCity_ARHU_Text_Tanglewood_GoOnIn, MSGBOX_NPC
	end

FervorFieldCity_ARHU_Text_GymBlocker::
	.string "The GYM is closed until further\n"
	.string "notice.\p"
	.string "Our LEADER only takes on Trainers\n"
	.string "who've already earned a few BADGES.$"

FervorFieldCity_ARHU_Text_MartBlocker::
	.string "Sorry, we're closed today!\p"
	.string "Everyone in town is over at the\n"
	.string "SAFARI challenge.\p"
	.string "Come back once you have a partner\n"
	.string "of your own!$"

FervorFieldCity_ARHU_Text_PokemonCenterBlocker::
	.string "The POKéMON CENTER is closed for\n"
	.string "the SAFARI challenge.\p"
	.string "We're getting everything ready for\n"
	.string "the challengers' new partners.\p"
	.string "Please come back when you've\n"
	.string "finished!$"

FervorFieldCity_ARHU_Text_MoveDeleterBlocker::
	.string "Grandpa's taking a nap inside.\p"
	.string "He said no visitors until the\n"
	.string "SAFARI challenge is over.$"

@ General tips for first-time players. Two kids outside the player's house, always present.
FervorFieldCity_ARHU_EventScript_TipKid_FastText::
	msgbox FervorFieldCity_ARHU_Text_TipKid_FastText, MSGBOX_NPC
	end

FervorFieldCity_ARHU_EventScript_TipKid_Saving::
	msgbox FervorFieldCity_ARHU_Text_TipKid_Saving, MSGBOX_NPC
	end

FervorFieldCity_ARHU_Text_TipKid_FastText::
	.string "Sometimes when I play these games\n"
	.string "I feel like people talk forever!\p"
	.string "That's why I hold the A Button to\n"
	.string "speed up conversations!\p"
	.string "Sometimes I get confused on where\n"
	.string "I am though…$"

FervorFieldCity_ARHU_Text_TipKid_Saving::
	.string "You never know what could happen\n"
	.string "next in these games!\p"
	.string "That's why I SAVE a lot.\n"
	.string "Open the START menu and pick SAVE!\p"
	.string "I save before big moments, like\n"
	.string "a tough battle or a new area.\p"
	.string "Better safe than sorry!$"

FervorFieldCity_ARHU_Text_Tanglewood_GoOnIn::
	.string "Tanglewood: What are you waiting\n"
	.string "for? Your partner is somewhere in\l"
	.string "the Safari Zone!\p"
	.string "Head through the gate behind me.\n"
	.string "Remember, you only get to keep one,\l"
	.string "so choose the one you connect with.$"

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
	.string "FERVOR FIELD CITY POKéMON GYM\n"
	.string "LEADER: RIN\l"
	.string "Flow Like Water$"

FervorFieldCity_ARHU_Text_ExitSpeech_WellWhatDoWeHaveHere::
	.string "Tanglewood: Well, what do we have\n"
	.string "here?\p"
	.string "A {STR_VAR_1}!\n"
	.string "Now look at that, you have a partner.\p"
	.string "If a wild Pokémon appears,\n"
	.string "you don't have to be alone!\l"
	.string "Your Pokémon can battle it.\p"
	.string "With it at your side, you should be\n"
	.string "able to start your journey.\p"
	.string "Tanglewood: {PLAYER}, Pokémon gain\n"
	.string "valuable experience by battle.\l"
	.string "Don't be too hard on it.\l"
	.string "It has to battle for it to grow.\p"
	.string "Now it's your job to rely on your\n"
	.string "Pokémon!\l"
	.string "And with friends you can go far!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Mira_GotMineToo::
	.string "Mira: Heh, I beat you out by a bit.\n"
	.string "I've got my partner too!\p"
	.string "No, I won't tell you what it is.\n"
	.string "You'll see it soon enough!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Westin_MadeIt::
	.string "Westin: Phew! Finally made it out!\p"
	.string "Looks like you two beat me again.\n"
	.string "Mira, you're fast!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_WhatDidYouGet::
	.string "Tanglewood: Ah, Westin! Right on\n"
	.string "time.\p"
	.string "Now then, out loud for everyone.\n"
	.string "What did the Safari give you?$"

FervorFieldCity_ARHU_Text_ExitSpeech_Westin_GotMine::
	.string "Westin: A {STR_VAR_2}!\p"
	.string "And you got a {STR_VAR_1}, {PLAYER}?\n"
	.string "Nice pick!\p"
	.string "I think mine has a slight edge on\n"
	.string "yours, though. Just saying!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_WestinPokedex::
	.string "Tanglewood: Hah! That's the spirit.\p"
	.string "Here, Westin. The same POKéDEX I\n"
	.string "gave the other two.$"

FervorFieldCity_ARHU_Text_ExitSpeech_WestinReceivedPokedex::
	.string "Westin received the POKéDEX\n"
	.string "from PROF. TANGLEWOOD!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_Pokedex::
	.string "Tanglewood: Now, in my hands, I have\n"
	.string "an invention called the POKéDEX.\p"
	.string "It automatically records data on\n"
	.string "Pokémon you've seen or caught.\p"
	.string "This tool can help you to bridge\n"
	.string "the gap when understanding Pokémon!\p"
	.string "Mira already has hers, so this one\n"
	.string "is yours. Take it with you.$"

FervorFieldCity_ARHU_Text_ExitSpeech_ReceivedPokedex::
	.string "{PLAYER} received the POKéDEX\n"
	.string "from PROF. TANGLEWOOD!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_CatchingTools::
	.string "Tanglewood: Sadly, you can't get\n"
	.string "detailed data on Pokémon\l"
	.string "just by seeing them.\p"
	.string "You must catch them to obtain\n"
	.string "complete data.\p"
	.string "So, here are some tools for\n"
	.string "catching wild Pokémon.$"

FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_HowToUseBalls::
	.string "Tanglewood: It's not normally the\n"
	.string "ranger way, but that's just how I\l"
	.string "chose my life.\p"
	.string "They aren't hard to use.\n"
	.string "When a wild Pokémon appears,\l"
	.string "catch it!\p"
	.string "This won't always work, however.\n"
	.string "A healthy Pokémon can escape.\l"
	.string "You have to be lucky!\p"
	.string "I've traveled the world and\n"
	.string "seen a lot!\p"
	.string "I get a sense of wonder from you!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Westin_LetsBattle::
	.string "Westin: Alright, we've all got a\n"
	.string "partner now!\p"
	.string "{PLAYER}, how about a battle?\n"
	.string "Let's see what we can do together!\p"
	.string "I'll go first, and no holding back!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Mira_WantIn::
	.string "Mira: Hey! Don't leave me out!\n"
	.string "I wanna get in on this too!\p"
	.string "{PLAYER}, once you're done with\n"
	.string "Westin, you're battling me next!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_GoOnThen::
	.string "Tanglewood: Hah! Go on, then.\n"
	.string "Battle is the best teacher.$"

FervorFieldCity_ARHU_Text_ExitSpeech_Westin_Defeat::
	.string "Westin: Whoa! You're good!\p"
	.string "Alright, you got me this time.\n"
	.string "I'll get you next time!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Westin_Victory::
	.string "Westin: Yes! That was close!\p"
	.string "Great battle, {PLAYER}.\n"
	.string "You'll get me next time!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_HealThem::
	.string "Tanglewood: Nicely fought, both of\n"
	.string "you!\p"
	.string "Remember, every Pokémon has a type.\n"
	.string "Water beats Fire, Fire beats Grass,\l"
	.string "and Grass beats Water.\p"
	.string "But out in the world you will meet\n"
	.string "Pokémon of many other types.\p"
	.string "Each one changes the balance, so\n"
	.string "watch what works and learn!\p"
	.string "Let me restore your Pokémon\n"
	.string "before the next battle.$"

FervorFieldCity_ARHU_Text_ExitSpeech_Mira_MyTurn::
	.string "Mira: Alright, my turn!\p"
	.string "You've been waiting to see what\n"
	.string "I picked. Here it is!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Mira_Defeat::
	.string "Mira: Wow, you're good…\p"
	.string "Eevee and I still have a lot\n"
	.string "to learn!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Mira_Victory::
	.string "Mira: Yes! We did it, Eevee!\p"
	.string "Don't look so down, {PLAYER}.\n"
	.string "You and your partner only just met.\p"
	.string "Get stronger together, and I'll be\n"
	.string "waiting for a rematch.\p"
	.string "I'm off to win my first RIBBON at\n"
	.string "a Pokémon Contest!\p"
	.string "See you on the road!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Mira_AfterLoss::
	.string "Mira: Okay, you win this round,\n"
	.string "{PLAYER}.\p"
	.string "Next time, Eevee and I will be\n"
	.string "ready for you.\p"
	.string "I'm off to win my first RIBBON at\n"
	.string "a Pokémon Contest!\p"
	.string "See you on the road!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Westin_GoodLuck::
	.string "Westin: Mira's already gone?\n"
	.string "Then I'd better hurry too!\p"
	.string "That was a great battle, {PLAYER}.\n"
	.string "I'm glad we're starting out\l"
	.string "together.\p"
	.string "I'm off to get my first BADGE from\n"
	.string "a Pokémon Gym!\p"
	.string "Good luck out there.\n"
	.string "May the best Trainer win!$"

FervorFieldCity_ARHU_Text_ExitSpeech_Tanglewood_StartYourJourney::
	.string "Tanglewood: Well, {PLAYER}, you're\n"
	.string "off to a fine start!\p"
	.string "I have a few more Trainers to look\n"
	.string "after in the Safari, so I'll leave\l"
	.string "you here.\p"
	.string "Oh, and the Safari's west exit\n"
	.string "was being monitored for the\l"
	.string "challenge. It should be open by\l"
	.string "now.\p"
	.string "Ahead of you lie two challenges.\n"
	.string "The Gym Challenge: defeat the Gym\l"
	.string "Leaders and earn their BADGES.\p"
	.string "The Contest Challenge: show how\n"
	.string "beautiful, cool, cute, smart and\l"
	.string "tough your Pokémon can be to earn\l"
	.string "RIBBONS.\p"
	.string "Choose one path, or walk both.\p"
	.string "Your first stop is the trek to the\n"
	.string "next town, Earnest.\p"
	.string "Head south down Route 1 and along\n"
	.string "the Cycling Road. You don't have a\l"
	.string "bike yet, so you'll have to walk.\p"
	.string "Stock up on supplies at the Mart\n"
	.string "before you go. It's a long way!\p"
	.string "Good luck out there, and don't give\n"
	.string "up! Every Pokémon has more to\l"
	.string "teach you.$"
