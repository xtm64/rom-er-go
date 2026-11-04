Earnest_PokemonCenter_1F_ARHU_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Earnest_PokemonCenter_1F_ARHU_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

Earnest_PokemonCenter_1F_ARHU_OnTransition:
	setrespawn HEAL_LOCATION_EARNEST_TOWNSHIP
	end

Earnest_PokemonCenter_1F_ARHU_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_EARNEST_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

Earnest_PokemonCenter_1F_ARHU_EventScript_Sailor::
	msgbox Earnest_PokemonCenter_1F_ARHU_Text_RaiseDifferentTypesOfPokemon, MSGBOX_NPC
	end

Earnest_PokemonCenter_1F_ARHU_EventScript_Woman::
	msgbox Earnest_PokemonCenter_1F_ARHU_Text_TradedMonWithFriend, MSGBOX_NPC
	end

Earnest_PokemonCenter_1F_ARHU_Text_RaiseDifferentTypesOfPokemon:
	.string "Want a tip for battling?\p"
	.string "I'd say it's raising different kinds\n"
	.string "of POKéMON in a balanced manner.\p"
	.string "It's no good to make just one\n"
	.string "POKéMON strong.\p"
	.string "If it has a type disadvantage,\n"
	.string "it might not stand a chance.$"

Earnest_PokemonCenter_1F_ARHU_Text_TradedMonWithFriend:
	.string "I trade POKéMON with my friends.\p"
	.string "If a traded POKéMON is holding an\n"
	.string "item, it makes me twice as happy!$"

