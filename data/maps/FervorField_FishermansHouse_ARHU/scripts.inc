FervorField_FishermansHouse_ARHU_MapScripts::
	.byte 0

FervorField_FishermansHouse_ARHU_EventScript_FishingGuru::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OLD_ROD, FervorField_FishermansHouse_ARHU_EventScript_AlreadyGotOldRod
	msgbox FervorField_FishermansHouse_ARHU_Text_DoYouLikeToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FervorField_FishermansHouse_ARHU_EventScript_GiveOldRod
	msgbox FervorField_FishermansHouse_ARHU_Text_OhThatsDisappointing
	release
	end

FervorField_FishermansHouse_ARHU_EventScript_AlreadyGotOldRod::
	msgbox FervorField_FishermansHouse_ARHU_Text_HowAreTheFishBiting
	release
	end

FervorField_FishermansHouse_ARHU_EventScript_GiveOldRod::
	checkitemspace ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, FervorField_FishermansHouse_ARHU_EventScript_NoRoomForOldRod
	msgbox FervorField_FishermansHouse_ARHU_Text_LikeYourStyleTakeThis
	giveitem_msg FervorField_FishermansHouse_ARHU_Text_ReceivedOldRod, ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox FervorField_FishermansHouse_ARHU_Text_FishingIsAWayOfLife
	release
	end

FervorField_FishermansHouse_ARHU_EventScript_NoRoomForOldRod::
	msgbox FervorField_FishermansHouse_ARHU_Text_YouHaveNoRoomForGift
	release
	end

@ Trigger on the tile in front of the back exit: blocked until the Safari challenge is complete
FervorField_FishermansHouse_ARHU_EventScript_BackExitGuard::
	lockall
	goto_if_set FLAG_FERVOR_FIELD_SAFARI_CHALLENGE_COMPLETE, FervorField_FishermansHouse_ARHU_EventScript_BackExitOpen
	msgbox FervorField_FishermansHouse_ARHU_Text_ShouldBeAtTheCompetition
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, FervorField_FishermansHouse_ARHU_Movement_WalkDown
	waitmovement 0
	releaseall
	end

FervorField_FishermansHouse_ARHU_EventScript_BackExitOpen::
	releaseall
	end

FervorField_FishermansHouse_ARHU_Movement_WalkDown:
	walk_down
	step_end

FervorField_FishermansHouse_ARHU_Text_DoYouLikeToFish:
	.string "All those kids rushin' into the\n"
	.string "SAFARI...\p"
	.string "Meanwhile, the best catch is\n"
	.string "been sittin' right here!\p"
	.string "Tell me, do you like to fish?$"

FervorField_FishermansHouse_ARHU_Text_LikeYourStyleTakeThis:
	.string "Grand! I like your style.\n"
	.string "I think we can be friends.\p"
	.string "Take this and fish, young friend!$"

FervorField_FishermansHouse_ARHU_Text_ReceivedOldRod:
	.string "{PLAYER} received an OLD ROD from\n"
	.string "the FISHING GURU.$"

FervorField_FishermansHouse_ARHU_Text_FishingIsAWayOfLife:
	.string "Fishing is a way of life!\n"
	.string "It is like the finest poetry.\p"
	.string "From the seas to the rivers, go out\n"
	.string "and land the big one, my friend.$"

FervorField_FishermansHouse_ARHU_Text_OhThatsDisappointing:
	.string "Oh...\n"
	.string "That's so disappointing...$"

FervorField_FishermansHouse_ARHU_Text_HowAreTheFishBiting:
	.string "Hello there, {PLAYER}!\p"
	.string "How are the fish biting?$"

FervorField_FishermansHouse_ARHU_Text_YouHaveNoRoomForGift:
	.string "Oh, no!\p"
	.string "I had a nice gift for you, but you\n"
	.string "have no room for it!$"

FervorField_FishermansHouse_ARHU_Text_ShouldBeAtTheCompetition:
	.string "Hey! Don't you have a\n"
	.string "competition to get to?\p"
	.string "Go on and show the other\n"
	.string "youngsters a little somethin'!$"
