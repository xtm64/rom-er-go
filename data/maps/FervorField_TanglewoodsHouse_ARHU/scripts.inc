FervorField_TanglewoodsHouse_ARHU_MapScripts::
	.byte 0

FervorField_TanglewoodsHouse_ARHU_EventScript_Books::
	msgbox FervorField_TanglewoodsHouse_ARHU_Text_Books, MSGBOX_SIGN
	end

FervorField_TanglewoodsHouse_ARHU_EventScript_LakeJournal::
	msgbox FervorField_TanglewoodsHouse_ARHU_Text_LakeJournal, MSGBOX_DEFAULT
	release
	end

FervorField_TanglewoodsHouse_ARHU_EventScript_Notes::
	msgbox FervorField_TanglewoodsHouse_ARHU_Text_Notes, MSGBOX_SIGN
	end

FervorField_TanglewoodsHouse_ARHU_EventScript_Curios::
	msgbox FervorField_TanglewoodsHouse_ARHU_Text_Curios, MSGBOX_SIGN
	end

FervorField_TanglewoodsHouse_ARHU_Text_Books::
	.string "Worn books on trails, weather and\n"
	.string "POKéMON habits.$"

FervorField_TanglewoodsHouse_ARHU_Text_LakeJournal::
	.string "The water on the lake's surface\n"
	.string "never stayed still.\p"
	.string "No wind.\n"
	.string "No current.\p"
	.string "POKéMON gathered at the edge\n"
	.string "but wouldn't drink.\p"
	.string "The next two nights were\n"
	.string "eerily quiet…\p"
	.string "On the third,\n"
	.string "everything left at once.\p"
	.string "I packed up right behind them.$"

FervorField_TanglewoodsHouse_ARHU_Text_Notes::
	.string "Pages of field notes and rough\n"
	.string "sketches, held down with pebbles.$"

FervorField_TanglewoodsHouse_ARHU_Text_Curios::
	.string "Odd stones and feathers collected\n"
	.string "from the woods.$"
