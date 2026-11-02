CeruleanCave_2F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCave_2F_OnTransition
	.byte 0

CeruleanCave_2F_OnTransition::
	call CeruleanCave_2F_MosaicOnTransition
	end

CeruleanCave_2F_MosaicOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, CeruleanCave_2F_MosaicRandomOnTransition
	getcaughtmon SPECIES_NECROZMA
	call_if_eq VAR_RESULT, TRUE, CeruleanCave_2F_MosaicHideNecrozma
	call_if_ne VAR_RESULT, TRUE, CeruleanCave_2F_MosaicShowNecrozma
	return

// Post-Kanto-Champion Cerulean Cave 2F legendary encounter.

CeruleanCave_2F_MosaicRandomOnTransition::
	call_if_set FLAG_CAUGHT_RANDOM_CERULEANCAVE_2F_NECROZMA, CeruleanCave_2F_MosaicHideNecrozma
	call_if_unset FLAG_CAUGHT_RANDOM_CERULEANCAVE_2F_NECROZMA, CeruleanCave_2F_MosaicShowNecrozma
	return

CeruleanCave_2F_MosaicHideNecrozma::
	setflag FLAG_HIDE_MOSAIC_NECROZMA
	return

CeruleanCave_2F_MosaicShowNecrozma::
	clearflag FLAG_HIDE_MOSAIC_NECROZMA
	return

CeruleanCave_2F_EventScript_Necrozma::
	lock
	faceplayer
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_NECROZMA, 65
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, CeruleanCave_2F_MosaicNecrozmaRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, CeruleanCave_2F_MosaicNecrozmaRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, CeruleanCave_2F_MosaicNecrozmaResolvedRandomCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, CeruleanCave_2F_MosaicNecrozmaResolved
	release
	end

CeruleanCave_2F_MosaicNecrozmaResolvedRandomCaught::
	setflag FLAG_CAUGHT_RANDOM_CERULEANCAVE_2F_NECROZMA
	goto CeruleanCave_2F_MosaicNecrozmaResolved

CeruleanCave_2F_MosaicNecrozmaResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_NECROZMA
	setflag FLAG_HIDE_MOSAIC_NECROZMA
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

CeruleanCave_2F_MosaicNecrozmaRetreated::
	release
	end
