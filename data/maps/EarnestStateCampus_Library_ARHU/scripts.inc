EarnestStateCampus_Library_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_Library_ARHU_EventScript_Librarian::
	msgbox EarnestStateCampus_Library_ARHU_Text_Librarian, MSGBOX_NPC
	end

EarnestStateCampus_Library_ARHU_EventScript_Elliot::
	lock
	faceplayer
	goto_if_defeated TRAINER_EARNEST_STATE_ELLIOT, EarnestStateCampus_Library_ARHU_EventScript_ElliotAfterBattle
	msgbox EarnestStateCampus_Library_ARHU_Text_ElliotChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EarnestStateCampus_Library_ARHU_EventScript_ElliotDeclined
	msgbox EarnestStateCampus_Library_ARHU_Text_ElliotIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_EARNEST_STATE_ELLIOT, EarnestStateCampus_Library_ARHU_Text_ElliotDefeat
	goto EarnestStateCampus_Library_ARHU_EventScript_ElliotGiveTwistedSpoon
	end

EarnestStateCampus_Library_ARHU_EventScript_ElliotAfterBattle::
	goto_if_unset FLAG_RECEIVED_EARNEST_STATE_TWISTED_SPOON, EarnestStateCampus_Library_ARHU_EventScript_ElliotGiveTwistedSpoon
	msgbox EarnestStateCampus_Library_ARHU_Text_ElliotAfter, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Library_ARHU_EventScript_ElliotGiveTwistedSpoon::
	msgbox EarnestStateCampus_Library_ARHU_Text_ElliotReward, MSGBOX_DEFAULT
	giveitem ITEM_TWISTED_SPOON
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EARNEST_STATE_TWISTED_SPOON
	msgbox EarnestStateCampus_Library_ARHU_Text_ExplainTwistedSpoon, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Library_ARHU_EventScript_ElliotDeclined::
	msgbox EarnestStateCampus_Library_ARHU_Text_ElliotDeclined, MSGBOX_DEFAULT
	release
	end

EarnestStateCampus_Library_ARHU_EventScript_ThesisStudent::
	msgbox EarnestStateCampus_Library_ARHU_Text_ThesisStudent, MSGBOX_NPC
	end

EarnestStateCampus_Library_ARHU_EventScript_CrammingStudent::
	msgbox EarnestStateCampus_Library_ARHU_Text_CrammingStudent, MSGBOX_NPC
	end

EarnestStateCampus_Library_ARHU_EventScript_ShelfHoenn::
	msgbox EarnestStateCampus_Library_ARHU_Text_ShelfHoenn, MSGBOX_SIGN
	end

EarnestStateCampus_Library_ARHU_EventScript_ShelfKanto::
	msgbox EarnestStateCampus_Library_ARHU_Text_ShelfKanto, MSGBOX_SIGN
	end

EarnestStateCampus_Library_ARHU_EventScript_ShelfEvolution::
	msgbox EarnestStateCampus_Library_ARHU_Text_ShelfEvolution, MSGBOX_SIGN
	end

EarnestStateCampus_Library_ARHU_EventScript_ShelfLegends::
	msgbox EarnestStateCampus_Library_ARHU_Text_ShelfLegends, MSGBOX_SIGN
	end

EarnestStateCampus_Library_ARHU_EventScript_ShelfReference::
	msgbox EarnestStateCampus_Library_ARHU_Text_ShelfReference, MSGBOX_SIGN
	end

EarnestStateCampus_Library_ARHU_EventScript_ReturnCart::
	msgbox EarnestStateCampus_Library_ARHU_Text_ReturnCart, MSGBOX_SIGN
	end

EarnestStateCampus_Library_ARHU_EventScript_CardCatalog::
	msgbox EarnestStateCampus_Library_ARHU_Text_CardCatalog, MSGBOX_SIGN
	end

EarnestStateCampus_Library_ARHU_EventScript_Microfiche::
	msgbox EarnestStateCampus_Library_ARHU_Text_Microfiche, MSGBOX_SIGN
	end

EarnestStateCampus_Library_ARHU_Text_Librarian:
	.string "Welcome to the HALLIE Q. BROWN\n"
	.string "MEMORIAL LIBRARY.\p"
	.string "Our shelves are sorted by region,\n"
	.string "and the CARD CATALOG terminals can\l"
	.string "find anything else.\p"
	.string "And please, no battles in the\n"
	.string "stacks. That means you, ELLIOT.$"

EarnestStateCampus_Library_ARHU_Text_ElliotChallenge:
	.string "…Shh. I'm ELLIOT, a graduate\n"
	.string "student in Ancient Linguistics.\p"
	.string "I study UNOWN. Their shapes look\n"
	.string "just like ancient writing.\p"
	.string "No one knows which came first:\n"
	.string "the letters, or the UNOWN.\p"
	.string "You look curious. Would you like\n"
	.string "to see my research up close?$"

EarnestStateCampus_Library_ARHU_Text_ElliotIntro:
	.string "Then let the letters speak!$"

EarnestStateCampus_Library_ARHU_Text_ElliotDeclined:
	.string "Mm. The UNOWN will wait.\n"
	.string "They always do.$"

EarnestStateCampus_Library_ARHU_Text_ElliotDefeat:
	.string "The letters spelled… L-O-S-E.\n"
	.string "How fitting.$"

EarnestStateCampus_Library_ARHU_Text_ElliotReward:
	.string "Your mind is sharper than I\n"
	.string "expected.\p"
	.string "This bent spoon helped me focus\n"
	.string "through my thesis defense. Take it.$"

EarnestStateCampus_Library_ARHU_Text_ExplainTwistedSpoon:
	.string "A TWISTED SPOON powers up\n"
	.string "PSYCHIC-type moves.\p"
	.string "There's a reason KADABRA always\n"
	.string "carry spoons, you know.$"

EarnestStateCampus_Library_ARHU_Text_ElliotAfter:
	.string "There are 28 known forms of UNOWN.\n"
	.string "Twenty-six letters, plus ! and ?.\p"
	.string "They've been found carved into ruins\n"
	.string "all over the world…\p"
	.string "I wonder what's written on the\n"
	.string "walls of the ruins in this region.$"

EarnestStateCampus_Library_ARHU_Text_ThesisStudent:
	.string "My thesis: “Why do BIBAREL build\n"
	.string "dams across rivers?”\p"
	.string "It's 400 pages long.\n"
	.string "Most of them are BIDOOF photos.$"

EarnestStateCampus_Library_ARHU_Text_CrammingStudent:
	.string "I've read the same page eight\n"
	.string "times…\p"
	.string "“GROWLITHE is loyal and faithful.\n"
	.string "GROWLITHE is loyal and faithful…”\p"
	.string "I think I need a nap.$"

EarnestStateCampus_Library_ARHU_Text_ShelfHoenn:
	.string "HOENN FIELD STUDIES\p"
	.string "“SEEDOT dangle from branches looking\n"
	.string "just like acorns, then startle\l"
	.string "other POKéMON by suddenly moving.”\p"
	.string "“WINGULL glide on ocean winds and\n"
	.string "hide food around their nests.”$"

EarnestStateCampus_Library_ARHU_Text_ShelfKanto:
	.string "KANTO: A NATURAL HISTORY\p"
	.string "“It is said MOON STONES fell onto\n"
	.string "MT. MOON from space long ago.\p"
	.string "CLEFAIRY gather there to dance on\n"
	.string "nights when the moon is full.”$"

EarnestStateCampus_Library_ARHU_Text_ShelfEvolution:
	.string "EVOLUTION: A PRIMER\p"
	.string "“EEVEE's genetic code is unstable.\n"
	.string "It can evolve into many different\l"
	.string "forms depending on its environment.\p"
	.string "Eight evolutions are known so far.”$"

EarnestStateCampus_Library_ARHU_Text_ShelfLegends:
	.string "MYTHS OF HOENN\p"
	.string "“GROUDON raised the land. KYOGRE\n"
	.string "expanded the seas.\p"
	.string "Their clash shook the world, until\n"
	.string "RAYQUAZA descended from the sky\l"
	.string "and calmed them both.”$"

EarnestStateCampus_Library_ARHU_Text_ShelfReference:
	.string "REFERENCE: THE POKéDEX, 1ST EDITION\p"
	.string "Every page is drawn by hand.\n"
	.string "Several entries just say “???”$"

EarnestStateCampus_Library_ARHU_Text_ReturnCart:
	.string "A cart of returned books.\p"
	.string "“So You Want to Be a GYM LEADER”\n"
	.string "“BERRY Blending for Beginners”\p"
	.string "“101 Recipes for SLOWPOKETAIL”…\n"
	.string "Wait, what?$"

EarnestStateCampus_Library_ARHU_Text_CardCatalog:
	.string "CARD CATALOG TERMINAL\p"
	.string "Search: “Rare POKéMON”\n"
	.string "Results: 4,096 entries.\p"
	.string "That's way too many to read!$"

EarnestStateCampus_Library_ARHU_Text_Microfiche:
	.string "MICROFICHE READER\p"
	.string "An old newspaper from 1912:\p"
	.string "“SEA SERPENT SIGHTED OFF THE COAST!\n"
	.string "EXPERTS SAY: PROBABLY A GYARADOS.”$"
