@ Seed shop, based on Route 104's Pretty Petal Flower Shop. The owner:
@  - sells 10 berries a day (4 kinds, +1 kind per badge, up to 8)
@  - trades 100 of one berry for a Tart, Sweet or Syrupy Apple
@  - sells the Pretty Petal plant decorations once the 3rd badge is earned
@ Note: FLAG_BADGE0x_GET are the Emerald badge flags; point them at Fervor's badges once those exist.
WillowRanch_SeedShop_ARHU_MapScripts::
	.byte 0

WillowRanch_SeedShop_ARHU_EventScript_ShopOwner::
	lock
	faceplayer
	dotimebasedevents
	msgbox WillowRanch_SeedShop_ARHU_Text_Welcome, MSGBOX_DEFAULT
	goto WillowRanch_SeedShop_ARHU_EventScript_Menu
	end

WillowRanch_SeedShop_ARHU_EventScript_Menu::
	dynmultipush WillowRanch_SeedShop_ARHU_Text_MenuBuyBerries, 0
	dynmultipush WillowRanch_SeedShop_ARHU_Text_MenuTradeApples, 1
	goto_if_set FLAG_BADGE03_GET, WillowRanch_SeedShop_ARHU_EventScript_MenuWithDecor
	dynmultipush WillowRanch_SeedShop_ARHU_Text_MenuCancel, 3
	goto WillowRanch_SeedShop_ARHU_EventScript_ShowMenu
	end

WillowRanch_SeedShop_ARHU_EventScript_MenuWithDecor::
	dynmultipush WillowRanch_SeedShop_ARHU_Text_MenuDecorations, 2
	dynmultipush WillowRanch_SeedShop_ARHU_Text_MenuCancel, 3
	goto WillowRanch_SeedShop_ARHU_EventScript_ShowMenu
	end

WillowRanch_SeedShop_ARHU_EventScript_ShowMenu::
	dynmultistack 0, 0, TRUE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, WillowRanch_SeedShop_ARHU_EventScript_BuyBerries
	case 1, WillowRanch_SeedShop_ARHU_EventScript_TradeApples
	case 2, WillowRanch_SeedShop_ARHU_EventScript_SellDecorations
	goto WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	end

WillowRanch_SeedShop_ARHU_EventScript_Goodbye::
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

@ ---- Buying berries: 10 a day ----
WillowRanch_SeedShop_ARHU_EventScript_BuyBerries::
	goto_if_set FLAG_DAILY_WILLOW_RANCH_BERRIES, WillowRanch_SeedShop_ARHU_EventScript_AlreadyBought
	msgbox WillowRanch_SeedShop_ARHU_Text_WhichBerries, MSGBOX_DEFAULT
	call WillowRanch_SeedShop_ARHU_EventScript_PushBuyBerries
	dynmultistack 0, 0, TRUE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	goto_if_eq VAR_RESULT, 0, WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	copyvar VAR_0x8004, VAR_RESULT
	bufferitemnameplural STR_VAR_1, VAR_0x8004, 10
	msgbox WillowRanch_SeedShop_ARHU_Text_TenForPrice, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, WillowRanch_SeedShop_ARHU_EventScript_NotEnoughMoney
	checkitemspace VAR_0x8004, 10
	goto_if_eq VAR_RESULT, FALSE, WillowRanch_SeedShop_ARHU_EventScript_BagFull
	removemoney 200
	giveitem VAR_0x8004, 10
	setflag FLAG_DAILY_WILLOW_RANCH_BERRIES
	msgbox WillowRanch_SeedShop_ARHU_Text_ThankYouComeTomorrow, MSGBOX_DEFAULT
	release
	end

WillowRanch_SeedShop_ARHU_EventScript_AlreadyBought::
	msgbox WillowRanch_SeedShop_ARHU_Text_AlreadyBought, MSGBOX_DEFAULT
	release
	end

WillowRanch_SeedShop_ARHU_EventScript_NotEnoughMoney::
	msgbox WillowRanch_SeedShop_ARHU_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

WillowRanch_SeedShop_ARHU_EventScript_BagFull::
	msgbox WillowRanch_SeedShop_ARHU_Text_BagFull, MSGBOX_DEFAULT
	release
	end

@ Berries unlocked by badge count: Oran, Cheri, Chesto, Pecha from the start,
@ then Rawst, Aspear, Leppa and Sitrus with each badge.
WillowRanch_SeedShop_ARHU_EventScript_PushBuyBerries::
	call WillowRanch_SeedShop_ARHU_EventScript_CountBadges
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Oran, ITEM_ORAN_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Cheri, ITEM_CHERI_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Chesto, ITEM_CHESTO_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Pecha, ITEM_PECHA_BERRY
	call_if_ge VAR_0x8005, 1, WillowRanch_SeedShop_ARHU_EventScript_PushRawst
	call_if_ge VAR_0x8005, 2, WillowRanch_SeedShop_ARHU_EventScript_PushAspear
	call_if_ge VAR_0x8005, 3, WillowRanch_SeedShop_ARHU_EventScript_PushLeppa
	call_if_ge VAR_0x8005, 4, WillowRanch_SeedShop_ARHU_EventScript_PushSitrus
	dynmultipush WillowRanch_SeedShop_ARHU_Text_MenuCancel, 0
	return

WillowRanch_SeedShop_ARHU_EventScript_PushRawst::
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Rawst, ITEM_RAWST_BERRY
	return

WillowRanch_SeedShop_ARHU_EventScript_PushAspear::
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Aspear, ITEM_ASPEAR_BERRY
	return

WillowRanch_SeedShop_ARHU_EventScript_PushLeppa::
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Leppa, ITEM_LEPPA_BERRY
	return

WillowRanch_SeedShop_ARHU_EventScript_PushSitrus::
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Sitrus, ITEM_SITRUS_BERRY
	return

WillowRanch_SeedShop_ARHU_EventScript_CountBadges::
	setvar VAR_0x8005, 0
	call_if_set FLAG_BADGE01_GET, WillowRanch_SeedShop_ARHU_EventScript_AddBadge
	call_if_set FLAG_BADGE02_GET, WillowRanch_SeedShop_ARHU_EventScript_AddBadge
	call_if_set FLAG_BADGE03_GET, WillowRanch_SeedShop_ARHU_EventScript_AddBadge
	call_if_set FLAG_BADGE04_GET, WillowRanch_SeedShop_ARHU_EventScript_AddBadge
	call_if_set FLAG_BADGE05_GET, WillowRanch_SeedShop_ARHU_EventScript_AddBadge
	call_if_set FLAG_BADGE06_GET, WillowRanch_SeedShop_ARHU_EventScript_AddBadge
	call_if_set FLAG_BADGE07_GET, WillowRanch_SeedShop_ARHU_EventScript_AddBadge
	call_if_set FLAG_BADGE08_GET, WillowRanch_SeedShop_ARHU_EventScript_AddBadge
	return

WillowRanch_SeedShop_ARHU_EventScript_AddBadge::
	addvar VAR_0x8005, 1
	return

@ ---- Trading 100 of one berry for an apple ----
WillowRanch_SeedShop_ARHU_EventScript_TradeApples::
	msgbox WillowRanch_SeedShop_ARHU_Text_WhichApple, MSGBOX_DEFAULT
	dynmultipush WillowRanch_SeedShop_ARHU_Text_TartApple, ITEM_TART_APPLE
	dynmultipush WillowRanch_SeedShop_ARHU_Text_SweetApple, ITEM_SWEET_APPLE
	dynmultipush WillowRanch_SeedShop_ARHU_Text_SyrupyApple, ITEM_SYRUPY_APPLE
	dynmultipush WillowRanch_SeedShop_ARHU_Text_MenuCancel, 0
	dynmultistack 0, 0, TRUE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	goto_if_eq VAR_RESULT, 0, WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	copyvar VAR_0x8006, VAR_RESULT
	msgbox WillowRanch_SeedShop_ARHU_Text_WhichBerryToTrade, MSGBOX_DEFAULT
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Oran, ITEM_ORAN_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Cheri, ITEM_CHERI_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Chesto, ITEM_CHESTO_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Pecha, ITEM_PECHA_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Rawst, ITEM_RAWST_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Aspear, ITEM_ASPEAR_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Leppa, ITEM_LEPPA_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_Sitrus, ITEM_SITRUS_BERRY
	dynmultipush WillowRanch_SeedShop_ARHU_Text_MenuCancel, 0
	dynmultistack 0, 0, TRUE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	goto_if_eq VAR_RESULT, 0, WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	copyvar VAR_0x8004, VAR_RESULT
	bufferitemnameplural STR_VAR_1, VAR_0x8004, 100
	bufferitemname STR_VAR_2, VAR_0x8006
	checkitem VAR_0x8004, 100
	goto_if_eq VAR_RESULT, FALSE, WillowRanch_SeedShop_ARHU_EventScript_NotEnoughBerries
	checkitemspace VAR_0x8006, 1
	goto_if_eq VAR_RESULT, FALSE, WillowRanch_SeedShop_ARHU_EventScript_BagFull
	msgbox WillowRanch_SeedShop_ARHU_Text_ConfirmTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, WillowRanch_SeedShop_ARHU_EventScript_Goodbye
	removeitem VAR_0x8004, 100
	giveitem VAR_0x8006, 1
	msgbox WillowRanch_SeedShop_ARHU_Text_EnjoyTheApple, MSGBOX_DEFAULT
	release
	end

WillowRanch_SeedShop_ARHU_EventScript_NotEnoughBerries::
	msgbox WillowRanch_SeedShop_ARHU_Text_NotEnoughBerries, MSGBOX_DEFAULT
	release
	end

@ ---- Plant decorations (same stock as Pretty Petal), unlocked at the 3rd badge ----
WillowRanch_SeedShop_ARHU_EventScript_SellDecorations::
	message gText_PlayerWhatCanIDoForYou
	waitmessage
	pokemartdecoration2 WillowRanch_SeedShop_ARHU_Pokemart_Plants
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
WillowRanch_SeedShop_ARHU_Pokemart_Plants:
	.2byte DECOR_RED_PLANT
	.2byte DECOR_TROPICAL_PLANT
	.2byte DECOR_PRETTY_FLOWERS
	.2byte DECOR_COLORFUL_PLANT
	.2byte DECOR_BIG_PLANT
	.2byte DECOR_GORGEOUS_PLANT
	pokemartlistend

WillowRanch_SeedShop_ARHU_EventScript_WailmerPailGirl::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_WAILMER_PAIL, WillowRanch_SeedShop_ARHU_EventScript_GiveWailmerPail
	msgbox WillowRanch_SeedShop_ARHU_Text_WailmerPailExplanation, MSGBOX_DEFAULT
	release
	end

WillowRanch_SeedShop_ARHU_EventScript_GiveWailmerPail::
	msgbox WillowRanch_SeedShop_ARHU_Text_YouCanHaveThis, MSGBOX_DEFAULT
	giveitem ITEM_WAILMER_PAIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox WillowRanch_SeedShop_ARHU_Text_WailmerPailExplanation, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_WAILMER_PAIL
	release
	end

WillowRanch_SeedShop_ARHU_EventScript_RandomBerryGirl::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY, WillowRanch_SeedShop_ARHU_EventScript_AlreadyReceivedBerry
	msgbox WillowRanch_SeedShop_ARHU_Text_ImGrowingFlowers, MSGBOX_DEFAULT
	giverandomberry BERRY_ID_CHERI, BERRY_ID_PERSIM
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY
	msgbox WillowRanch_SeedShop_ARHU_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

WillowRanch_SeedShop_ARHU_EventScript_AlreadyReceivedBerry::
	msgbox WillowRanch_SeedShop_ARHU_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

WillowRanch_SeedShop_ARHU_Text_Welcome::
	.string "Welcome to the WILLOW SEED SHOP!\p"
	.string "Everything grows well in the north\n"
	.string "if you give it time and care.$"

WillowRanch_SeedShop_ARHU_Text_MenuBuyBerries::
	.string "BUY BERRIES$"

WillowRanch_SeedShop_ARHU_Text_MenuTradeApples::
	.string "TRADE FOR APPLES$"

WillowRanch_SeedShop_ARHU_Text_MenuDecorations::
	.string "PLANTS$"

WillowRanch_SeedShop_ARHU_Text_MenuCancel::
	.string "CANCEL$"

WillowRanch_SeedShop_ARHU_Text_WhichBerries::
	.string "I can sell you up to 10 berries\n"
	.string "a day, all of one kind.\p"
	.string "Which berry will you plant?$"

WillowRanch_SeedShop_ARHU_Text_TenForPrice::
	.string "10 {STR_VAR_1} for ¥200.\n"
	.string "Is that all right?$"

WillowRanch_SeedShop_ARHU_Text_ThankYouComeTomorrow::
	.string "Thank you!\n"
	.string "Come back tomorrow for more.$"

WillowRanch_SeedShop_ARHU_Text_AlreadyBought::
	.string "That's all the berries I can spare\n"
	.string "today. Come back tomorrow!$"

WillowRanch_SeedShop_ARHU_Text_NotEnoughMoney::
	.string "You don't have enough money.$"

WillowRanch_SeedShop_ARHU_Text_BagFull::
	.string "Your BAG is full.$"

WillowRanch_SeedShop_ARHU_Text_WhichApple::
	.string "I'll trade you a prized apple for\n"
	.string "100 of any one kind of berry.\p"
	.string "Which apple would you like?$"

WillowRanch_SeedShop_ARHU_Text_WhichBerryToTrade::
	.string "And which berry will you trade?$"

WillowRanch_SeedShop_ARHU_Text_ConfirmTrade::
	.string "100 {STR_VAR_1} for one {STR_VAR_2}.\n"
	.string "Is that all right?$"

WillowRanch_SeedShop_ARHU_Text_NotEnoughBerries::
	.string "You need 100 of that berry\n"
	.string "for the trade.$"

WillowRanch_SeedShop_ARHU_Text_EnjoyTheApple::
	.string "Here you go! Enjoy the apple.$"

WillowRanch_SeedShop_ARHU_Text_Oran::
	.string "ORAN BERRY$"

WillowRanch_SeedShop_ARHU_Text_Cheri::
	.string "CHERI BERRY$"

WillowRanch_SeedShop_ARHU_Text_Chesto::
	.string "CHESTO BERRY$"

WillowRanch_SeedShop_ARHU_Text_Pecha::
	.string "PECHA BERRY$"

WillowRanch_SeedShop_ARHU_Text_Rawst::
	.string "RAWST BERRY$"

WillowRanch_SeedShop_ARHU_Text_Aspear::
	.string "ASPEAR BERRY$"

WillowRanch_SeedShop_ARHU_Text_Leppa::
	.string "LEPPA BERRY$"

WillowRanch_SeedShop_ARHU_Text_Sitrus::
	.string "SITRUS BERRY$"

WillowRanch_SeedShop_ARHU_Text_TartApple::
	.string "TART APPLE$"

WillowRanch_SeedShop_ARHU_Text_SweetApple::
	.string "SWEET APPLE$"

WillowRanch_SeedShop_ARHU_Text_SyrupyApple::
	.string "SYRUPY APPLE$"

WillowRanch_SeedShop_ARHU_Text_YouCanHaveThis::
	.string "Oh, you're a trainer?\n"
	.string "Then you can have this!$"

WillowRanch_SeedShop_ARHU_Text_WailmerPailExplanation::
	.string "That's a WAILMER PAIL.\p"
	.string "Use it to water the berries you\n"
	.string "plant so they grow strong.$"

WillowRanch_SeedShop_ARHU_Text_ImGrowingFlowers::
	.string "I'm growing flowers and berries\n"
	.string "out back.\p"
	.string "Here, have a berry from today's\n"
	.string "harvest!$"

WillowRanch_SeedShop_ARHU_Text_MachineMixesBerries::
	.string "There's a machine in the corner\n"
	.string "that mixes berries into POKéBLOCKS.$"
