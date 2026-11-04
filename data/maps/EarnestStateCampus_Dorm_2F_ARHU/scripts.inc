EarnestStateCampus_Dorm_2F_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_Dorm_2F_ARHU_EventScript_Roommate::
	msgbox EarnestStateCampus_Dorm_2F_ARHU_Text_Roommate, MSGBOX_NPC
	end

EarnestStateCampus_Dorm_2F_ARHU_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox EarnestStateCampus_Dorm_2F_ARHU_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EarnestStateCampus_Dorm_2F_ARHU_EventScript_Neighbor::
	msgbox EarnestStateCampus_Dorm_2F_ARHU_Text_Neighbor, MSGBOX_NPC
	end

EarnestStateCampus_Dorm_2F_ARHU_EventScript_Bed::
	lockall
	msgbox EarnestStateCampus_Dorm_2F_ARHU_Text_TakeANap, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_Dorm_2F_ARHU_EventScript_NoNap
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox EarnestStateCampus_Dorm_2F_ARHU_Text_FeelRefreshed, MSGBOX_DEFAULT
	releaseall
	end

EarnestStateCampus_Dorm_2F_ARHU_EventScript_NoNap::
	releaseall
	end

EarnestStateCampus_Dorm_2F_ARHU_Text_Roommate:
	.string "Oh, hey! That's my roommate's\n"
	.string "SKITTY.\p"
	.string "It chases its own tail in circles\n"
	.string "until it gets dizzy.\p"
	.string "Honestly? Kinda relatable during\n"
	.string "finals week.$"

EarnestStateCampus_Dorm_2F_ARHU_Text_Skitty:
	.string "SKITTY: Mew!\p"
	.string "It's chasing its tail around and\n"
	.string "around… It looks dizzy.$"

EarnestStateCampus_Dorm_2F_ARHU_Text_Neighbor:
	.string "My roommate snores like a SNORLAX,\n"
	.string "so I've been sleeping in the\l"
	.string "LIBRARY.\p"
	.string "If you're worn out, you can nap on\n"
	.string "the spare bed. We won't tell the RA.$"

EarnestStateCampus_Dorm_2F_ARHU_Text_TakeANap:
	.string "A neatly made spare bed.\n"
	.string "Take a quick nap?$"

EarnestStateCampus_Dorm_2F_ARHU_Text_FeelRefreshed:
	.string "{PLAYER} and the POKéMON feel\n"
	.string "refreshed!$"
