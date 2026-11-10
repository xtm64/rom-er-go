FervorField_PokemonCenter_1F_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FervorField_PokemonCenter_1F_ARHU_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FervorField_PokemonCenter_1F_ARHU_OnTransition:
	setrespawn HEAL_LOCATION_FERVOR_FIELD_POKEMON_CENTER
	end

FervorField_PokemonCenter_1F_ARHU_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FERVOR_FIELD_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FervorField_PokemonCenter_1F_ARHU_EventScript_Gentleman::
	msgbox FervorField_PokemonCenter_1F_ARHU_Text_TrainersCanUsePC, MSGBOX_NPC
	end

FervorField_PokemonCenter_1F_ARHU_EventScript_Boy::
	msgbox FervorField_PokemonCenter_1F_ARHU_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

FervorField_PokemonCenter_1F_ARHU_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, FervorField_PokemonCenter_1F_ARHU_EventScript_WirelessClubAvailable
	msgbox FervorField_PokemonCenter_1F_ARHU_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

FervorField_PokemonCenter_1F_ARHU_EventScript_WirelessClubAvailable::
	msgbox FervorField_PokemonCenter_1F_ARHU_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

FervorField_PokemonCenter_1F_ARHU_Text_TrainersCanUsePC:
	.string "That PC in the corner there is\n"
	.string "for any POKéMON TRAINER to use.\p"
	.string "Naturally, that means you're welcome\n"
	.string "to use it, too.$"

FervorField_PokemonCenter_1F_ARHU_Text_PokemonCentersAreGreat:
	.string "POKéMON CENTERS are great!\p"
	.string "You can use their services as much\n"
	.string "as you like, and it's all for free.\l"
	.string "You never have to worry!$"

FervorField_PokemonCenter_1F_ARHU_Text_WirelessClubNotAvailable:
	.string "The POKéMON WIRELESS CLUB on\n"
	.string "the second floor was built recently.\p"
	.string "But they say they're still making\n"
	.string "adjustments.$"

FervorField_PokemonCenter_1F_ARHU_Text_TradedInWirelessClub:
	.string "The POKéMON WIRELESS CLUB on\n"
	.string "the second floor was built recently.\p"
	.string "I traded POKéMON right away.$"
