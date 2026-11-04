EarnestStateCampus_HealthCenter_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_HealthCenter_ARHU_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_EARNEST_STATE_HEALTH_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EarnestStateCampus_HealthCenter_ARHU_EventScript_Pharmacist::
	msgbox EarnestStateCampus_HealthCenter_ARHU_Text_Pharmacist, MSGBOX_NPC
	end

EarnestStateCampus_HealthCenter_ARHU_EventScript_Athlete::
	msgbox EarnestStateCampus_HealthCenter_ARHU_Text_Athlete, MSGBOX_NPC
	end

EarnestStateCampus_HealthCenter_ARHU_EventScript_Researcher::
	msgbox EarnestStateCampus_HealthCenter_ARHU_Text_Researcher, MSGBOX_NPC
	end

EarnestStateCampus_HealthCenter_ARHU_EventScript_Freshman::
	msgbox EarnestStateCampus_HealthCenter_ARHU_Text_Freshman, MSGBOX_NPC
	end

EarnestStateCampus_HealthCenter_ARHU_EventScript_WellnessPoster::
	msgbox EarnestStateCampus_HealthCenter_ARHU_Text_WellnessPoster, MSGBOX_SIGN
	end

EarnestStateCampus_HealthCenter_ARHU_Text_Pharmacist:
	.string "Upstairs is the POKéMON pharmacy.\n"
	.string "Staff only, sorry!\p"
	.string "Fun fact: CHANSEY lay eggs so\n"
	.string "nutritious that even people with\l"
	.string "no appetite gobble them up!$"

EarnestStateCampus_HealthCenter_ARHU_Text_Athlete:
	.string "My MAKUHITA got knocked around at\n"
	.string "Varsity practice.\p"
	.string "It'll be fine, though. Every time\n"
	.string "MAKUHITA gets back up, it stores\l"
	.string "more energy for evolving!$"

EarnestStateCampus_HealthCenter_ARHU_Text_Researcher:
	.string "I'm researching POKéRUS, a tiny\n"
	.string "virus that infects POKéMON.\p"
	.string "Don't worry, it's harmless!\n"
	.string "Infected POKéMON actually grow\l"
	.string "stronger faster.\p"
	.string "If the NURSE ever mentions it,\n"
	.string "consider yourself lucky!$"

EarnestStateCampus_HealthCenter_ARHU_Text_Freshman:
	.string "First week of college, and I've\n"
	.string "already gotten lost three times.\p"
	.string "At least the HEALTH CENTER is easy\n"
	.string "to find. Just follow the smell of\l"
	.string "POTIONS!$"

EarnestStateCampus_HealthCenter_ARHU_Text_WellnessPoster:
	.string "CAMPUS WELLNESS TIP\p"
	.string "“Stressed about finals? Spend time\n"
	.string "with your POKéMON!\p"
	.string "Petting a SKITTY is proven to lower\n"
	.string "stress by 80%!”\p"
	.string "The source just says “trust us.”$"
