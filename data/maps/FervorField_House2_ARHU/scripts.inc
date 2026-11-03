@ Ported from FuchsiaCity_House3_Frlg by arhu_maps.pl; labels renamed FuchsiaCity_House3_Frlg/FuchsiaCity_House3_* -> FervorField_House2_ARHU_*
FervorField_House2_ARHU_MapScripts::
	.byte 0

FervorField_House2_ARHU_EventScript_MoveDeleter::
	lock
	faceplayer
	msgbox FervorField_House2_ARHU_Text_WouldYouLikeToForgetMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FervorField_House2_ARHU_EventScript_ChooseMonForMoveDeleter
	goto FervorField_House2_ARHU_EventScript_CancelForgetMove
	end

FervorField_House2_ARHU_EventScript_ChooseMonForMoveDeleter::
	msgbox FervorField_House2_ARHU_Text_WhichMonShouldForgetMove
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, FervorField_House2_ARHU_EventScript_CancelForgetMove
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FervorField_House2_ARHU_EventScript_CantForgetMoveEgg
	special GetNumMovesSelectedMonHas
	goto_if_eq VAR_RESULT, 1, FervorField_House2_ARHU_EventScript_CantForgetOnlyMove
	msgbox FervorField_House2_ARHU_Text_WhichMoveShouldBeForgotten
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_0x8005, MAX_MON_MOVES, FervorField_House2_ARHU_EventScript_ChooseMonForMoveDeleter
	special BufferMoveDeleterNicknameAndMove
	msgbox FervorField_House2_ARHU_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FervorField_House2_ARHU_EventScript_ForgetMove
	goto FervorField_House2_ARHU_EventScript_CancelForgetMove
	end

FervorField_House2_ARHU_EventScript_ForgetMove::
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox FervorField_House2_ARHU_Text_MonHasForgottenMoveCompletely
	release
	end

FervorField_House2_ARHU_EventScript_CantForgetOnlyMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox FervorField_House2_ARHU_Text_MonOnlyKnowsOneMove
	release
	end

FervorField_House2_ARHU_EventScript_CantForgetMoveEgg::
	msgbox FervorField_House2_ARHU_Text_NoEggShouldKnowMoves
	release
	end

FervorField_House2_ARHU_EventScript_CancelForgetMove::
	msgbox FervorField_House2_ARHU_Text_ComeAgainToForgetOtherMoves
	release
	end

FervorField_House2_ARHU_Text_WouldYouLikeToForgetMove::
	.string "Uh…\n"
	.string "Oh, yes, I'm the MOVE DELETER.\p"
	.string "I can make POKéMON forget their\n"
	.string "moves.\p"
	.string "Would you like me to do that?$"

FervorField_House2_ARHU_Text_WhichMonShouldForgetMove::
	.string "Which POKéMON should forget a\n"
	.string "move?$"

FervorField_House2_ARHU_Text_WhichMoveShouldBeForgotten::
	.string "Which move should be forgotten?$"

FervorField_House2_ARHU_Text_MonOnlyKnowsOneMove::
	.string "{STR_VAR_1} seems to know only one\n"
	.string "move…$"

FervorField_House2_ARHU_Text_MonsMoveShouldBeForgotten::
	.string "Hm! {STR_VAR_1}'s {STR_VAR_2}?\n"
	.string "That move should be forgotten?$"

FervorField_House2_ARHU_Text_MonHasForgottenMoveCompletely::
	.string "It worked to perfection!\p"
	.string "{STR_VAR_1} has forgotten\n"
	.string "{STR_VAR_2} completely.$"

FervorField_House2_ARHU_Text_ComeAgainToForgetOtherMoves::
	.string "Come again if there are other\n"
	.string "moves to be forgotten.$"

FervorField_House2_ARHU_Text_NoEggShouldKnowMoves::
	.string "What?\n"
	.string "No EGG should know any moves.$"

