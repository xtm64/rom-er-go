@ Ported from Route1_Frlg by arhu_maps.pl; labels renamed Route1_Frlg/Route1_* -> Route2_North_ARHU_*
Route2_North_ARHU_MapScripts::
	.byte 0

Route2_North_ARHU_EventScript_Boy::
	msgbox Route2_North_ARHU_Text_CanJumpFromLedges, MSGBOX_NPC
	end

Route2_North_ARHU_EventScript_RouteSign::
	msgbox Route2_North_ARHU_Text_RouteSign, MSGBOX_SIGN
	end

Route2_North_ARHU_Text_CanJumpFromLedges::
	.string "See those ledges along the road?\p"
	.string "It's a bit scary, but you can jump\n"
	.string "from them.\p"
	.string "You can get back to FERVOR FIELD\n"
	.string "quicker that way.$"

Route2_North_ARHU_Text_RouteSign::
	.string "ROUTE 2\n"
	.string "FERVOR FIELD - WILLOWSVILLE$"

