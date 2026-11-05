FervorField_PlayersHouse_2F_ARHU_MapScripts::
	.byte 0

PalletTown_PlayersHouse_2F_EventScript_NES::
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES, MSGBOX_SIGN
	end

PalletTown_PlayersHouse_2F_EventScript_Sign::
	msgbox PalletTown_PlayersHouse_2F_Text_PressLRForHelp, MSGBOX_SIGN
	end

PalletTown_PlayersHouse_2F_Text_PlayedWithNES::
	.string "{PLAYER} played with the NES.\p"
	.string "…Okay!\nIt's time to go!$"

PalletTown_PlayersHouse_2F_Text_PressLRForHelp::
	.string "It's a posted notice…\p"
	.string "If you're confused, ask for HELP!\nPress the L or R Button!$"


@ Things to poke at, so a first-time player who clicks around gets something back.
FervorField_PlayersHouse_2F_ARHU_EventScript_Desk::
	msgbox FervorField_PlayersHouse_2F_ARHU_Text_Desk, MSGBOX_SIGN
	end

FervorField_PlayersHouse_2F_ARHU_EventScript_Drawers::
	msgbox FervorField_PlayersHouse_2F_ARHU_Text_Drawers, MSGBOX_SIGN
	end

FervorField_PlayersHouse_2F_ARHU_EventScript_Bookshelf::
	msgbox FervorField_PlayersHouse_2F_ARHU_Text_Bookshelf, MSGBOX_SIGN
	end

FervorField_PlayersHouse_2F_ARHU_EventScript_TV::
	msgbox FervorField_PlayersHouse_2F_ARHU_Text_TV, MSGBOX_SIGN
	end

FervorField_PlayersHouse_2F_ARHU_EventScript_Bed::
	msgbox FervorField_PlayersHouse_2F_ARHU_Text_Bed, MSGBOX_SIGN
	end

FervorField_PlayersHouse_2F_ARHU_Text_Desk::
	.string "Your desk. Old school notes are\n"
	.string "still scribbled all over it.$"

FervorField_PlayersHouse_2F_ARHU_Text_Drawers::
	.string "A chest of drawers.\p"
	.string "You've already packed everything\n"
	.string "you need.$"

FervorField_PlayersHouse_2F_ARHU_Text_Bookshelf::
	.string "A shelf of Pokémon books and\n"
	.string "magazines.\p"
	.string "You've read every one of them\n"
	.string "at least twice.$"

FervorField_PlayersHouse_2F_ARHU_Text_TV::
	.string "A small TV, hooked up to the NES.$"

FervorField_PlayersHouse_2F_ARHU_Text_Bed::
	.string "Your bed, neatly made.\p"
	.string "You're too excited to sleep now!$"
