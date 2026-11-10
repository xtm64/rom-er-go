EarnestStateCampus_ScienceTower_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_ScienceTower_ARHU_EventScript_DrMarsh::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EARNEST_STATE_MYSTIC_WATER, EarnestStateCampus_ScienceTower_ARHU_EventScript_DrMarshAfter
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_DrMarshOfferQuiz, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_ScienceTower_ARHU_EventScript_DrMarshDeclined
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuestion1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_ScienceTower_ARHU_EventScript_FieldQuizWrong
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuestion2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EarnestStateCampus_ScienceTower_ARHU_EventScript_FieldQuizWrong
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuestion3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_ScienceTower_ARHU_EventScript_FieldQuizWrong
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuizPassed, MSGBOX_DEFAULT
	giveitem ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EARNEST_STATE_MYSTIC_WATER
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_ExplainMysticWater, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_DrMarshDeclined::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_DrMarshDeclined, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_FieldQuizWrong::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuizWrong, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_DrMarshAfter::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_DrMarshAfter, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_WeatherScientist::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_WeatherScientist, MSGBOX_NPC
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_HydrologyScientist::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_HydrologyScientist, MSGBOX_NPC
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_GeneticsScientist::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_GeneticsScientist, MSGBOX_NPC
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_StairGuard::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_StairGuard, MSGBOX_NPC
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_GradStudent::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_GradStudent, MSGBOX_NPC
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_WeatherComputer::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_WeatherComputer, MSGBOX_SIGN
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_Server::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_Server, MSGBOX_SIGN
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_Blueprint::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_Blueprint, MSGBOX_SIGN
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_WaterSamples::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_WaterSamples, MSGBOX_SIGN
	end

EarnestStateCampus_ScienceTower_ARHU_EventScript_Monitors::
	msgbox EarnestStateCampus_ScienceTower_ARHU_Text_Monitors, MSGBOX_SIGN
	end

EarnestStateCampus_ScienceTower_ARHU_Text_DrMarshOfferQuiz:
	.string "I'm DR. MARSH, director of the\n"
	.string "McLIN Water Resources Program.\p"
	.string "We study how POKéMON shape our\n"
	.string "rivers, lakes and seas.\p"
	.string "My grad students keep failing my\n"
	.string "field quiz. Care to give it a try?$"

EarnestStateCampus_ScienceTower_ARHU_Text_DrMarshDeclined:
	.string "Hmph. Come back once you've done\n"
	.string "your reading.$"

EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuestion1:
	.string "Question one! Answer YES for true.\p"
	.string "LOTAD once lived on land, but its\n"
	.string "leaf grew so big and heavy that it\l"
	.string "returned to the water.\p"
	.string "True?$"

EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuestion2:
	.string "Correct! Question two!\p"
	.string "WAILORD is the smallest of all\n"
	.string "known POKéMON.\p"
	.string "True?$"

EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuestion3:
	.string "Correct! It's the LARGEST ever\n"
	.string "identified. Final question!\p"
	.string "CORPHISH were originally imported\n"
	.string "from abroad as pets, and later\l"
	.string "turned up in the wild.\p"
	.string "True?$"

EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuizWrong:
	.string "Wrong! Go read the WATER SAMPLE\n"
	.string "labels, and visit the LIBRARY.\p"
	.string "Then come back and try again.$"

EarnestStateCampus_ScienceTower_ARHU_Text_FieldQuizPassed:
	.string "Correct! Finally, someone who's done\n"
	.string "the reading!\p"
	.string "Here. We pulled this from the bottom\n"
	.string "of a local lake.$"

EarnestStateCampus_ScienceTower_ARHU_Text_ExplainMysticWater:
	.string "MYSTIC WATER is a teardrop-shaped\n"
	.string "gem. It boosts WATER-type moves.\p"
	.string "Water is the source of all life…\n"
	.string "and of a lot of POKéMON, too.$"

EarnestStateCampus_ScienceTower_ARHU_Text_DrMarshAfter:
	.string "Fieldwork is the heart of science.\p"
	.string "Every river you cross on your\n"
	.string "journey is a living laboratory.$"

EarnestStateCampus_ScienceTower_ARHU_Text_WeatherScientist:
	.string "I study CASTFORM. Its form changes\n"
	.string "with the weather: sun, rain or snow.\p"
	.string "It borrows the power of nature to\n"
	.string "protect its tiny body.$"

EarnestStateCampus_ScienceTower_ARHU_Text_HydrologyScientist:
	.string "I'm tracking QWILFISH populations.\p"
	.string "To fire its poison spikes, it has\n"
	.string "to gulp down over 2.6 gallons of\l"
	.string "water and puff itself up!$"

EarnestStateCampus_ScienceTower_ARHU_Text_GeneticsScientist:
	.string "My lab studies DITTO. It can\n"
	.string "rearrange its cells to transform.\p"
	.string "But when it transforms from memory,\n"
	.string "it always gets some details wrong.$"

EarnestStateCampus_ScienceTower_ARHU_Text_StairGuard:
	.string "The upper labs are restricted.\n"
	.string "Faculty with clearance only.\p"
	.string "There's… something up there they\n"
	.string "still haven't finished classifying.$"

EarnestStateCampus_ScienceTower_ARHU_Text_GradStudent:
	.string "My research is on WHISCASH.\p"
	.string "It's very territorial… and it can\n"
	.string "sense real earthquakes before they\l"
	.string "happen!$"

EarnestStateCampus_ScienceTower_ARHU_Text_WeatherComputer:
	.string "WEATHER MONITOR\p"
	.string "Today: SUNNY.\n"
	.string "CASTFORM sunny form chance: 100%.$"

EarnestStateCampus_ScienceTower_ARHU_Text_Server:
	.string "A humming server rack.\p"
	.string "A sticky note reads: “DO NOT let\n"
	.string "the PORYGON into the mainframe\l"
	.string "AGAIN.”$"

EarnestStateCampus_ScienceTower_ARHU_Text_Blueprint:
	.string "Blueprints for a riverbank\n"
	.string "restoration project.\p"
	.string "Someone doodled little LOTAD\n"
	.string "floating in the margins.$"

EarnestStateCampus_ScienceTower_ARHU_Text_WaterSamples:
	.string "Jars of water samples, labeled:\n"
	.string "“WILLOW LAKE,” “ROUTE 2 CREEK”…\p"
	.string "One jar just says “GYARADOS???\n"
	.string "DO NOT OPEN.”$"

EarnestStateCampus_ScienceTower_ARHU_Text_Monitors:
	.string "A screen tracks river currents in\n"
	.string "real time.\p"
	.string "A tiny dot labeled “FEEBAS?” blinks\n"
	.string "once… then vanishes.$"
