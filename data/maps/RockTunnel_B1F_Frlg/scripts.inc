RockTunnel_B1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RockTunnel_B1F_OnTransition
	.byte 0

RockTunnel_B1F_OnTransition::
	call RockTunnel_B1F_BigBatchOnTransition
	call RockTunnel_B1F_MosaicOnTransition
	end

RockTunnel_B1F_EventScript_Sofia::
	trainerbattle_single TRAINER_PICNICKER_SOFIA, RockTunnel_B1F_Text_SofiaIntro, RockTunnel_B1F_Text_SofiaDefeat
	msgbox RockTunnel_B1F_Text_SofiaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Martha::
	trainerbattle_single TRAINER_PICNICKER_MARTHA, RockTunnel_B1F_Text_MarthaIntro, RockTunnel_B1F_Text_MarthaDefeat
	msgbox RockTunnel_B1F_Text_MarthaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Dudley::
	trainerbattle_single TRAINER_HIKER_DUDLEY, RockTunnel_B1F_Text_DudleyIntro, RockTunnel_B1F_Text_DudleyDefeat
	msgbox RockTunnel_B1F_Text_DudleyPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Allen::
	trainerbattle_single TRAINER_HIKER_ALLEN, RockTunnel_B1F_Text_AllenIntro, RockTunnel_B1F_Text_AllenDefeat
	msgbox RockTunnel_B1F_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Eric::
	trainerbattle_single TRAINER_HIKER_ERIC, RockTunnel_B1F_Text_EricIntro, RockTunnel_B1F_Text_EricDefeat
	msgbox RockTunnel_B1F_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Cooper::
	trainerbattle_single TRAINER_POKEMANIAC_COOPER, RockTunnel_B1F_Text_CooperIntro, RockTunnel_B1F_Text_CooperDefeat
	msgbox RockTunnel_B1F_Text_CooperPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Steve::
	trainerbattle_single TRAINER_POKEMANIAC_STEVE, RockTunnel_B1F_Text_SteveIntro, RockTunnel_B1F_Text_SteveDefeat
	msgbox RockTunnel_B1F_Text_StevePostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Winston::
	trainerbattle_single TRAINER_POKEMANIAC_WINSTON, RockTunnel_B1F_Text_WinstonIntro, RockTunnel_B1F_Text_WinstonDefeat
	msgbox RockTunnel_B1F_Text_WinstonPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_Text_SofiaIntro::
	.string "Do you know how you can avoid\n"
	.string "getting lost in the mountains?\p"
	.string "You can bend twigs as trail\n"
	.string "markers.$"

RockTunnel_B1F_Text_SofiaDefeat::
	.string "Ohhh!\n"
	.string "I did my best!$"

RockTunnel_B1F_Text_SofiaPostBattle::
	.string "I want to go home!$"

RockTunnel_B1F_Text_DudleyIntro::
	.string "Hahaha!\n"
	.string "Can you beat my power?$"

RockTunnel_B1F_Text_DudleyDefeat::
	.string "Oops!\n"
	.string "Outmuscled!$"

RockTunnel_B1F_Text_DudleyPostBattle::
	.string "I go for power because I hate\n"
	.string "thinking.$"

RockTunnel_B1F_Text_CooperIntro::
	.string "You have a POKéDEX?\n"
	.string "I want one, too.$"

RockTunnel_B1F_Text_CooperDefeat::
	.string "Shoot!\n"
	.string "I am so jealous!$"

RockTunnel_B1F_Text_CooperPostBattle::
	.string "When you finish your POKéDEX,\n"
	.string "can I have it?$"

RockTunnel_B1F_Text_SteveIntro::
	.string "Um… Do you know about POKéMON\n"
	.string "cosplay?$"

RockTunnel_B1F_Text_SteveDefeat::
	.string "Well, that's that.$"

RockTunnel_B1F_Text_StevePostBattle::
	.string "POKéMON cosplay is dressing up as\n"
	.string "POKéMON for fun.\p"
	.string "CLEFAIRY is a favorite.$"

RockTunnel_B1F_Text_AllenIntro::
	.string "My POKéMON techniques will leave\n"
	.string "you crying!$"

RockTunnel_B1F_Text_AllenDefeat::
	.string "I give!\n"
	.string "You're a better technician!$"

RockTunnel_B1F_Text_AllenPostBattle::
	.string "In mountains, you'll often find\n"
	.string "ROCK-type POKéMON.$"

RockTunnel_B1F_Text_MarthaIntro::
	.string "I don't often come here, but I will\n"
	.string "battle you.$"

RockTunnel_B1F_Text_MarthaDefeat::
	.string "Oh!\n"
	.string "I lost!$"

RockTunnel_B1F_Text_MarthaPostBattle::
	.string "I like tiny POKéMON.\n"
	.string "Big ones are too scary!$"

RockTunnel_B1F_Text_EricIntro::
	.string "Hit me with your best shot!$"

RockTunnel_B1F_Text_EricDefeat::
	.string "Fired away!$"

RockTunnel_B1F_Text_EricPostBattle::
	.string "I'll raise my POKéMON to beat\n"
	.string "yours, kid.$"

RockTunnel_B1F_Text_WinstonIntro::
	.string "I draw illustrations of POKéMON\n"
	.string "when I'm home.$"

RockTunnel_B1F_Text_WinstonDefeat::
	.string "Whew…\n"
	.string "I'm exhausted…$"

RockTunnel_B1F_Text_WinstonPostBattle::
	.string "I'm an artist, not a fighter.\n"
	.string "I'll go home to draw.$"

// Regigigas requires all three Hoenn Regis registered caught, not in party.
RockTunnel_B1F_MosaicOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, RockTunnel_B1F_MosaicRandomOnTransition
	getcaughtmon SPECIES_REGIROCK
	goto_if_ne VAR_RESULT, TRUE, RockTunnel_B1F_MosaicRegigigasLocked
	getcaughtmon SPECIES_REGICE
	goto_if_ne VAR_RESULT, TRUE, RockTunnel_B1F_MosaicRegigigasLocked
	getcaughtmon SPECIES_REGISTEEL
	goto_if_ne VAR_RESULT, TRUE, RockTunnel_B1F_MosaicRegigigasLocked
	getcaughtmon SPECIES_REGIGIGAS
	call_if_eq VAR_RESULT, TRUE, RockTunnel_B1F_MosaicHideRegigigas
	call_if_ne VAR_RESULT, TRUE, RockTunnel_B1F_MosaicShowRegigigas
	goto RockTunnel_B1F_MosaicOtherStatics

RockTunnel_B1F_MosaicRegigigasLocked::
	setflag FLAG_HIDE_MOSAIC_REGIGIGAS
RockTunnel_B1F_MosaicOtherStatics::
	getcaughtmon SPECIES_UXIE
	call_if_eq VAR_RESULT, TRUE, RockTunnel_B1F_MosaicHideUxie
	call_if_ne VAR_RESULT, TRUE, RockTunnel_B1F_MosaicShowUxie
	getcaughtmon SPECIES_MESPRIT
	call_if_eq VAR_RESULT, TRUE, RockTunnel_B1F_MosaicHideMesprit
	call_if_ne VAR_RESULT, TRUE, RockTunnel_B1F_MosaicShowMesprit
	getcaughtmon SPECIES_AZELF
	call_if_eq VAR_RESULT, TRUE, RockTunnel_B1F_MosaicHideAzelf
	call_if_ne VAR_RESULT, TRUE, RockTunnel_B1F_MosaicShowAzelf
	return

RockTunnel_B1F_MosaicRandomOnTransition::
	goto_if_unset FLAG_CAUGHT_RANDOM_DESERTRUINS_REGIROCK, RockTunnel_B1F_MosaicRegigigasRandomLocked
	goto_if_unset FLAG_CAUGHT_RANDOM_ISLANDCAVE_REGICE, RockTunnel_B1F_MosaicRegigigasRandomLocked
	goto_if_unset FLAG_CAUGHT_RANDOM_ANCIENTTOMB_REGISTEEL, RockTunnel_B1F_MosaicRegigigasRandomLocked
	call_if_set FLAG_CAUGHT_RANDOM_ROCKTUNNEL_REGIGIGAS, RockTunnel_B1F_MosaicHideRegigigas
	call_if_unset FLAG_CAUGHT_RANDOM_ROCKTUNNEL_REGIGIGAS, RockTunnel_B1F_MosaicShowRegigigas
	goto RockTunnel_B1F_MosaicOtherRandomStatics

RockTunnel_B1F_MosaicRegigigasRandomLocked::
	setflag FLAG_HIDE_MOSAIC_REGIGIGAS
RockTunnel_B1F_MosaicOtherRandomStatics::
	call_if_set FLAG_CAUGHT_RANDOM_ROCKTUNNEL_UXIE, RockTunnel_B1F_MosaicHideUxie
	call_if_unset FLAG_CAUGHT_RANDOM_ROCKTUNNEL_UXIE, RockTunnel_B1F_MosaicShowUxie
	call_if_set FLAG_CAUGHT_RANDOM_ROCKTUNNEL_MESPRIT, RockTunnel_B1F_MosaicHideMesprit
	call_if_unset FLAG_CAUGHT_RANDOM_ROCKTUNNEL_MESPRIT, RockTunnel_B1F_MosaicShowMesprit
	call_if_set FLAG_CAUGHT_RANDOM_ROCKTUNNEL_AZELF, RockTunnel_B1F_MosaicHideAzelf
	call_if_unset FLAG_CAUGHT_RANDOM_ROCKTUNNEL_AZELF, RockTunnel_B1F_MosaicShowAzelf
	return

RockTunnel_B1F_MosaicHideRegigigas::
	setflag FLAG_HIDE_MOSAIC_REGIGIGAS
	return

RockTunnel_B1F_MosaicShowRegigigas::
	clearflag FLAG_HIDE_MOSAIC_REGIGIGAS
	return

RockTunnel_B1F_EventScript_Regigigas::
	lock
	faceplayer
	playmoncry SPECIES_REGIGIGAS, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_REGIGIGAS, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, RockTunnel_B1F_MosaicRegigigasRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, RockTunnel_B1F_MosaicRegigigasRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, RockTunnel_B1F_MosaicRegigigasCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, RockTunnel_B1F_MosaicRegigigasResolved
	release
	end

RockTunnel_B1F_MosaicRegigigasCaught::
	setflag FLAG_CAUGHT_RANDOM_ROCKTUNNEL_REGIGIGAS
	goto RockTunnel_B1F_MosaicRegigigasResolved

RockTunnel_B1F_MosaicRegigigasResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_REGIGIGAS
	setflag FLAG_HIDE_MOSAIC_REGIGIGAS
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

RockTunnel_B1F_MosaicRegigigasRetreated::
	release
	end

RockTunnel_B1F_MosaicHideUxie::
	setflag FLAG_HIDE_MOSAIC_UXIE
	return

RockTunnel_B1F_MosaicShowUxie::
	clearflag FLAG_HIDE_MOSAIC_UXIE
	return

RockTunnel_B1F_EventScript_Uxie::
	lock
	faceplayer
	playmoncry SPECIES_UXIE, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_UXIE, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, RockTunnel_B1F_MosaicUxieRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, RockTunnel_B1F_MosaicUxieRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, RockTunnel_B1F_MosaicUxieCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, RockTunnel_B1F_MosaicUxieResolved
	release
	end

RockTunnel_B1F_MosaicUxieCaught::
	setflag FLAG_CAUGHT_RANDOM_ROCKTUNNEL_UXIE
	goto RockTunnel_B1F_MosaicUxieResolved

RockTunnel_B1F_MosaicUxieResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_UXIE
	setflag FLAG_HIDE_MOSAIC_UXIE
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

RockTunnel_B1F_MosaicUxieRetreated::
	release
	end

RockTunnel_B1F_MosaicHideMesprit::
	setflag FLAG_HIDE_MOSAIC_MESPRIT
	return

RockTunnel_B1F_MosaicShowMesprit::
	clearflag FLAG_HIDE_MOSAIC_MESPRIT
	return

RockTunnel_B1F_EventScript_Mesprit::
	lock
	faceplayer
	playmoncry SPECIES_MESPRIT, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_MESPRIT, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, RockTunnel_B1F_MosaicMespritRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, RockTunnel_B1F_MosaicMespritRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, RockTunnel_B1F_MosaicMespritCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, RockTunnel_B1F_MosaicMespritResolved
	release
	end

RockTunnel_B1F_MosaicMespritCaught::
	setflag FLAG_CAUGHT_RANDOM_ROCKTUNNEL_MESPRIT
	goto RockTunnel_B1F_MosaicMespritResolved

RockTunnel_B1F_MosaicMespritResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_MESPRIT
	setflag FLAG_HIDE_MOSAIC_MESPRIT
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

RockTunnel_B1F_MosaicMespritRetreated::
	release
	end

RockTunnel_B1F_MosaicHideAzelf::
	setflag FLAG_HIDE_MOSAIC_AZELF
	return

RockTunnel_B1F_MosaicShowAzelf::
	clearflag FLAG_HIDE_MOSAIC_AZELF
	return

RockTunnel_B1F_EventScript_Azelf::
	lock
	faceplayer
	playmoncry SPECIES_AZELF, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_AZELF, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, RockTunnel_B1F_MosaicAzelfRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, RockTunnel_B1F_MosaicAzelfRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, RockTunnel_B1F_MosaicAzelfCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, RockTunnel_B1F_MosaicAzelfResolved
	release
	end

RockTunnel_B1F_MosaicAzelfCaught::
	setflag FLAG_CAUGHT_RANDOM_ROCKTUNNEL_AZELF
	goto RockTunnel_B1F_MosaicAzelfResolved

RockTunnel_B1F_MosaicAzelfResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_AZELF
	setflag FLAG_HIDE_MOSAIC_AZELF
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

RockTunnel_B1F_MosaicAzelfRetreated::
	release
	end

// Multi-location acquisition batch: preserve canonical map scripts.
RockTunnel_B1F_BigBatchOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, RockTunnel_B1F_BigBatchRandomOnTransition
	getcaughtmon SPECIES_HEATRAN
	call_if_eq VAR_RESULT, TRUE, RockTunnel_B1F_BigBatchHideHeatran
	call_if_ne VAR_RESULT, TRUE, RockTunnel_B1F_BigBatchShowHeatran
	return

RockTunnel_B1F_BigBatchRandomOnTransition::
	call_if_set FLAG_CAUGHT_RANDOM_ROCKTUNNEL_HEATRAN, RockTunnel_B1F_BigBatchHideHeatran
	call_if_unset FLAG_CAUGHT_RANDOM_ROCKTUNNEL_HEATRAN, RockTunnel_B1F_BigBatchShowHeatran
	return

RockTunnel_B1F_BigBatchHideHeatran::
	setflag FLAG_HIDE_MOSAIC_HEATRAN
	return

RockTunnel_B1F_BigBatchShowHeatran::
	clearflag FLAG_HIDE_MOSAIC_HEATRAN
	return

RockTunnel_B1F_EventScript_Heatran::
	lock
	faceplayer
	playmoncry SPECIES_HEATRAN, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_HEATRAN, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, RockTunnel_B1F_BigBatchHeatranRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, RockTunnel_B1F_BigBatchHeatranRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, RockTunnel_B1F_BigBatchHeatranCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, RockTunnel_B1F_BigBatchHeatranResolved
	release
	end

RockTunnel_B1F_BigBatchHeatranCaught::
	setflag FLAG_CAUGHT_RANDOM_ROCKTUNNEL_HEATRAN
	goto RockTunnel_B1F_BigBatchHeatranResolved

RockTunnel_B1F_BigBatchHeatranResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_HEATRAN
	setflag FLAG_HIDE_MOSAIC_HEATRAN
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

RockTunnel_B1F_BigBatchHeatranRetreated::
	release
	end

Mosaic_MegaStone_HEATRANITE::
    callnative MosaicStaticRandomizerIsOn
    goto_if_eq VAR_RESULT, TRUE, RockTunnel_B1F_MegaStoneHeatranRandom
    getcaughtmon SPECIES_HEATRAN
    goto_if_ne VAR_RESULT, TRUE, Mosaic_MegaStone_HEATRANITE_Locked
    finditem ITEM_HEATRANITE
    end
RockTunnel_B1F_MegaStoneHeatranRandom::
    goto_if_unset FLAG_CAUGHT_RANDOM_ROCKTUNNEL_HEATRAN, Mosaic_MegaStone_HEATRANITE_Locked
    finditem ITEM_HEATRANITE
    end
Mosaic_MegaStone_HEATRANITE_Locked::
    msgbox Mosaic_MegaStone_HEATRANITE_LockedText, MSGBOX_DEFAULT
    end
Mosaic_MegaStone_HEATRANITE_LockedText::
    .string "A special MEGA STONE resonates here.\p"
    .string "Return when its guardian is yours.$"
