EarnestStateCampus_ARHU_MapScripts::
	.byte 0

EarnestStateCampus_ARHU_EventScript_TourGuide::
	msgbox EarnestStateCampus_ARHU_Text_TourGuide, MSGBOX_NPC
	end

EarnestStateCampus_ARHU_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox EarnestStateCampus_ARHU_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EarnestStateCampus_ARHU_EventScript_FountainStudent::
	msgbox EarnestStateCampus_ARHU_Text_FountainStudent, MSGBOX_NPC
	end

EarnestStateCampus_ARHU_EventScript_Jogger::
	msgbox EarnestStateCampus_ARHU_Text_Jogger, MSGBOX_NPC
	end

EarnestStateCampus_ARHU_EventScript_StudyingStudent::
	msgbox EarnestStateCampus_ARHU_Text_StudyingStudent, MSGBOX_NPC
	end

EarnestStateCampus_ARHU_EventScript_Botanist::
	msgbox EarnestStateCampus_ARHU_Text_Botanist, MSGBOX_NPC
	end

EarnestStateCampus_ARHU_EventScript_ProfessorEmeritus::
	msgbox EarnestStateCampus_ARHU_Text_ProfessorEmeritus, MSGBOX_NPC
	end

EarnestStateCampus_ARHU_EventScript_HexManiac::
	msgbox EarnestStateCampus_ARHU_Text_HexManiac, MSGBOX_NPC
	end

EarnestStateCampus_ARHU_EventScript_AdminHallSign::
	msgbox EarnestStateCampus_ARHU_Text_AdminHallSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_LectureHallSign::
	msgbox EarnestStateCampus_ARHU_Text_LectureHallSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_MediaCenterSign::
	msgbox EarnestStateCampus_ARHU_Text_MediaCenterSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_CampusStoreSign::
	msgbox EarnestStateCampus_ARHU_Text_CampusStoreSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_LibrarySign::
	msgbox EarnestStateCampus_ARHU_Text_LibrarySign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_HealthCenterSign::
	msgbox EarnestStateCampus_ARHU_Text_HealthCenterSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_ScienceTowerSign::
	msgbox EarnestStateCampus_ARHU_Text_ScienceTowerSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_DormSign::
	msgbox EarnestStateCampus_ARHU_Text_DormSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_MuseumSign::
	msgbox EarnestStateCampus_ARHU_Text_MuseumSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_GymnasiumSign::
	msgbox EarnestStateCampus_ARHU_Text_GymnasiumSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_FountainPlaque::
	msgbox EarnestStateCampus_ARHU_Text_FountainPlaque, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_SteamPlantSign::
	msgbox EarnestStateCampus_ARHU_Text_SteamPlantSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_EventScript_GardenSign::
	msgbox EarnestStateCampus_ARHU_Text_GardenSign, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_Text_TourGuide:
	.string "Welcome to EARNEST STATE UNIVERSITY!\p"
	.string "Founded in 1887, we're the oldest\n"
	.string "POKéMON college in the region.\p"
	.string "WESLEY HALL teaches battle theory,\n"
	.string "the LIBRARY keeps a century of\l"
	.string "field notes, and WALKER GYMNASIUM\l"
	.string "is home to our Varsity Battle Team.\p"
	.string "Worn out? The HEALTH CENTER treats\n"
	.string "POKéMON free of charge.\p"
	.string "Go on, explore! Every building on\n"
	.string "campus has something to teach.$"

EarnestStateCampus_ARHU_Text_Zigzagoon:
	.string "ZIGZAGOON: Guguu!\p"
	.string "It's the unofficial campus mascot.\n"
	.string "It zigzags across the quad sniffing\l"
	.string "out anything the students dropped.$"

EarnestStateCampus_ARHU_Text_FountainStudent:
	.string "They say if you toss a coin in the\n"
	.string "fountain before finals, JIRACHI\l"
	.string "wakes up and grants you an A.\p"
	.string "Then again, JIRACHI only wakes for\n"
	.string "one week every thousand years…\p"
	.string "My odds aren't great.$"

EarnestStateCampus_ARHU_Text_Jogger:
	.string "Hup, hup! Laps around the quad keep\n"
	.string "me and my POKéMON in shape!\p"
	.string "The Varsity captain says stamina\n"
	.string "wins long battles. I believe him!$"

EarnestStateCampus_ARHU_Text_StudyingStudent:
	.string "Shh… Cramming for my Type Theory\n"
	.string "midterm.\p"
	.string "FIRE beats GRASS, GRASS beats\n"
	.string "WATER, WATER beats FIRE…\p"
	.string "And DRAGON beats… DRAGON?\p"
	.string "Wait, that's right! DRAGON moves\n"
	.string "are super effective on DRAGONS!$"

EarnestStateCampus_ARHU_Text_Botanist:
	.string "Welcome to the SEED TO BLOOM\n"
	.string "BOTANICAL GARDEN.\p"
	.string "Our horticulture students grow\n"
	.string "BERRIES and rare herbs here.\p"
	.string "Did you know ODDISH bury their\n"
	.string "faces in the soil during the day?\p"
	.string "At night they wander around,\n"
	.string "scattering seeds everywhere.\p"
	.string "Look closely between the flower\n"
	.string "beds. You never know what's grown.$"

EarnestStateCampus_ARHU_Text_ProfessorEmeritus:
	.string "I taught at EARNEST STATE for\n"
	.string "forty years.\p"
	.string "Back then, there were no POKéDEXES.\n"
	.string "We sketched every POKéMON by hand\l"
	.string "in our field journals.\p"
	.string "The LIBRARY still has my old notes.\n"
	.string "Give them a read, young one.$"

EarnestStateCampus_ARHU_Text_HexManiac:
	.string "That brick building is the old\n"
	.string "STEAM PLANT…\p"
	.string "Students say a DUSKULL drifts\n"
	.string "through its walls at night.\p"
	.string "DUSKULL can pass through any wall,\n"
	.string "no matter how thick…\p"
	.string "And once it picks a target, it\n"
	.string "follows them until dawn.\p"
	.string "Hehehe… Sweet dreams.$"

EarnestStateCampus_ARHU_Text_AdminHallSign:
	.string "NEWSOM ADMINISTRATION HALL\n"
	.string "Admissions - Bursar - Dean's Office$"

EarnestStateCampus_ARHU_Text_LectureHallSign:
	.string "WESLEY ARTS & SCIENCE HALL\n"
	.string "Now in session: BATTLE THEORY 201$"

EarnestStateCampus_ARHU_Text_MediaCenterSign:
	.string "MASS COMMUNICATIONS CENTER\n"
	.string "Home of KEST 88.1 Campus Radio$"

EarnestStateCampus_ARHU_Text_CampusStoreSign:
	.string "SMITH COLLEGE OF BUSINESS\n"
	.string "Student-run CAMPUS STORE$"

EarnestStateCampus_ARHU_Text_LibrarySign:
	.string "HALLIE Q. BROWN MEMORIAL LIBRARY\n"
	.string "Quiet, please!$"

EarnestStateCampus_ARHU_Text_HealthCenterSign:
	.string "LACKEY-LEE HEALTH CENTER\n"
	.string "POKéMON and Trainers welcome$"

EarnestStateCampus_ARHU_Text_ScienceTowerSign:
	.string "McLIN SCIENCE TOWER\n"
	.string "Water Resources & Natural Sciences$"

EarnestStateCampus_ARHU_Text_DormSign:
	.string "JOHNS LIVING-LEARNING CENTER\n"
	.string "Residents and guests only$"

EarnestStateCampus_ARHU_Text_MuseumSign:
	.string "ROBESON CULTURAL MUSEUM\n"
	.string "Art, history and POKéMON legends$"

EarnestStateCampus_ARHU_Text_GymnasiumSign:
	.string "WALKER GYMNASIUM\n"
	.string "Home of the Varsity Battle Team$"

EarnestStateCampus_ARHU_Text_FountainPlaque:
	.string "FOUNDERS' FOUNTAIN\n"
	.string "EARNEST STATE UNIVERSITY, est. 1887\p"
	.string "“Learn by battling.\n"
	.string "Battle by learning.”$"

EarnestStateCampus_ARHU_Text_SteamPlantSign:
	.string "CAMPUS STEAM PLANT\n"
	.string "Authorized personnel only.$"

EarnestStateCampus_ARHU_Text_GardenSign:
	.string "SEED TO BLOOM BOTANICAL GARDEN\n"
	.string "Please don't pick the flowers!$"

EarnestStateCampus_ARHU_EventScript_DirectionsSign::
	msgbox EarnestStateCampus_ARHU_Text_Directions, MSGBOX_SIGN
	end

EarnestStateCampus_ARHU_Text_Directions::
	.string "EAST: ROUTE 1 CYCLING ROAD$"
