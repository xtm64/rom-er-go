EarnestStateCampus_Museum_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_Museum_ARHU_EventScript_Greeter::
	msgbox EarnestStateCampus_Museum_ARHU_Text_Greeter, MSGBOX_NPC
	end

EarnestStateCampus_Museum_ARHU_EventScript_Curator::
	msgbox EarnestStateCampus_Museum_ARHU_Text_Curator, MSGBOX_NPC
	end

EarnestStateCampus_Museum_ARHU_EventScript_Hollis::
	lock
	faceplayer
	goto_if_defeated TRAINER_EARNEST_STATE_HOLLIS, EarnestStateCampus_Museum_ARHU_EventScript_HollisAfter
	msgbox EarnestStateCampus_Museum_ARHU_Text_HollisChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_Museum_ARHU_EventScript_HollisDeclined
	msgbox EarnestStateCampus_Museum_ARHU_Text_HollisIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_EARNEST_STATE_HOLLIS, EarnestStateCampus_Museum_ARHU_Text_HollisDefeat
	goto EarnestStateCampus_Museum_ARHU_EventScript_HollisAfter
	end

EarnestStateCampus_Museum_ARHU_EventScript_HollisDeclined::
	msgbox EarnestStateCampus_Museum_ARHU_Text_HollisDeclined, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Museum_ARHU_EventScript_HollisAfter::
	msgbox EarnestStateCampus_Museum_ARHU_Text_HollisAfter, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Museum_ARHU_EventScript_FieldTripKid::
	msgbox EarnestStateCampus_Museum_ARHU_Text_FieldTripKid, MSGBOX_NPC
	end

EarnestStateCampus_Museum_ARHU_EventScript_Artist::
	msgbox EarnestStateCampus_Museum_ARHU_Text_Artist, MSGBOX_NPC
	end

EarnestStateCampus_Museum_ARHU_EventScript_HoOhPainting::
	msgbox EarnestStateCampus_Museum_ARHU_Text_HoOhPainting, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_BerryPainting::
	msgbox EarnestStateCampus_Museum_ARHU_Text_BerryPainting, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_FounderPortrait::
	msgbox EarnestStateCampus_Museum_ARHU_Text_FounderPortrait, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_OldMap::
	msgbox EarnestStateCampus_Museum_ARHU_Text_OldMap, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_EonPainting::
	msgbox EarnestStateCampus_Museum_ARHU_Text_EonPainting, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_LaprasPainting::
	msgbox EarnestStateCampus_Museum_ARHU_Text_LaprasPainting, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_CelebiSketch::
	msgbox EarnestStateCampus_Museum_ARHU_Text_CelebiSketch, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_XatuStatue::
	msgbox EarnestStateCampus_Museum_ARHU_Text_XatuStatue, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_StoneTablet::
	msgbox EarnestStateCampus_Museum_ARHU_Text_StoneTablet, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_EventScript_ApricornDisplay::
	msgbox EarnestStateCampus_Museum_ARHU_Text_ApricornDisplay, MSGBOX_SIGN
	end

EarnestStateCampus_Museum_ARHU_Text_Greeter:
	.string "Welcome to the ROBESON CULTURAL\n"
	.string "MUSEUM! Admission is free.\p"
	.string "Our collection celebrates the art,\n"
	.string "history and legends shared by\l"
	.string "POKéMON and people.$"

EarnestStateCampus_Museum_ARHU_Text_Curator:
	.string "Upstairs is closed while we install\n"
	.string "a new exhibit:\p"
	.string "“CROWNS OF THE DEEP:\n"
	.string "Relics of the Ancient Sea.”\p"
	.string "It opens next semester.\n"
	.string "Do come back!$"

EarnestStateCampus_Museum_ARHU_Text_HollisChallenge:
	.string "Look at this tablet! I'm HOLLIS,\n"
	.string "from the archaeology department.\p"
	.string "I've spent six years translating it.\n"
	.string "It tells of GROUDON and KYOGRE…\p"
	.string "…and a third figure in the sky.\p"
	.string "You've got an ancient sort of\n"
	.string "energy, Trainer. Shall we test it?$"

EarnestStateCampus_Museum_ARHU_Text_HollisIntro:
	.string "My partners are older than this\n"
	.string "whole museum! Let's dig in!$"

EarnestStateCampus_Museum_ARHU_Text_HollisDeclined:
	.string "This tablet waited a thousand years.\n"
	.string "I can wait a few more minutes.$"

EarnestStateCampus_Museum_ARHU_Text_HollisDefeat:
	.string "Crumbled like an old clay pot…$"

EarnestStateCampus_Museum_ARHU_Text_HollisAfter:
	.string "BALTOY appear in ancient wall\n"
	.string "paintings, living beside people.\p"
	.string "Oh! I dropped a RARE BONE somewhere\n"
	.string "near the back corner when we moved\l"
	.string "exhibits last week.\p"
	.string "If you find it, it's yours.\n"
	.string "Collectors pay a fortune for them.$"

EarnestStateCampus_Museum_ARHU_Text_FieldTripKid:
	.string "We're on a field trip! Teacher says\n"
	.string "paintings can't come to life.\p"
	.string "But SMEARGLE paints with its tail!\n"
	.string "What if one painted THESE?$"

EarnestStateCampus_Museum_ARHU_Text_Artist:
	.string "I'm an art major. I sketch here\n"
	.string "every day.\p"
	.string "Over 5,000 different marks left by\n"
	.string "SMEARGLE have been found. Fans pay\l"
	.string "big money for the rare ones!$"

EarnestStateCampus_Museum_ARHU_Text_HoOhPainting:
	.string "“THE RAINBOW WING”\p"
	.string "HO-OH soars through a rainbow on\n"
	.string "seven-colored wings.\p"
	.string "Legend says whoever sees it is\n"
	.string "blessed with eternal happiness.$"

EarnestStateCampus_Museum_ARHU_Text_BerryPainting:
	.string "“STILL LIFE WITH BERRIES”\p"
	.string "ORAN, PECHA and CHERI BERRIES,\n"
	.string "painted so well your stomach growls.$"

EarnestStateCampus_Museum_ARHU_Text_FounderPortrait:
	.string "A portrait of the university's\n"
	.string "founders, 1887.\p"
	.string "A PIDGEY sits on one founder's hat.\n"
	.string "It refused to leave the sitting.$"

EarnestStateCampus_Museum_ARHU_Text_OldMap:
	.string "A hand-drawn map of the region\n"
	.string "from the 1800s.\p"
	.string "Where WILLOWSVILLE stands today,\n"
	.string "there's only a forest labeled\l"
	.string "“HERE BE BEEDRILL.”$"

EarnestStateCampus_Museum_ARHU_Text_EonPainting:
	.string "“TWIN DRAGONS OF THE SOUTHERN ISLE”\p"
	.string "LATIAS and LATIOS fly side by side.\p"
	.string "They're said to understand human\n"
	.string "speech and talk using telepathy.$"

EarnestStateCampus_Museum_ARHU_Text_LaprasPainting:
	.string "“THE FERRY”\p"
	.string "A gentle LAPRAS carries children on\n"
	.string "its back across a misty sea.$"

EarnestStateCampus_Museum_ARHU_Text_CelebiSketch:
	.string "A charcoal sketch of CELEBI.\p"
	.string "“It wanders across time. Grass and\n"
	.string "trees flourish in forests where it\l"
	.string "has appeared.”$"

EarnestStateCampus_Museum_ARHU_Text_XatuStatue:
	.string "A stone statue of XATU, staring\n"
	.string "at the sun.\p"
	.string "“XATU stand still all day. Some say\n"
	.string "it's out of fear of the terrible\l"
	.string "things they've foreseen.”$"

EarnestStateCampus_Museum_ARHU_Text_StoneTablet:
	.string "An ancient stone tablet.\n"
	.string "The placard reads:\p"
	.string "“When land and sea did battle, the\n"
	.string "sky dragon came down from the\l"
	.string "heavens, and the world was calmed.”\p"
	.string "Translation by H. HOLLIS$"

EarnestStateCampus_Museum_ARHU_Text_ApricornDisplay:
	.string "An antique APRICORN BALL, carved\n"
	.string "by hand.\p"
	.string "“Before modern POKé BALLS, craftsmen\n"
	.string "made them from APRICORN fruit.”$"
