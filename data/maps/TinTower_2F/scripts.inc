TinTower_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_2F_OnTransition
	.byte 0

TinTower_2F_OnTransition::
	setescapewarp MAP_BELLCHIME_TRAIL, 35, 42
	call TinTower_2F_MosaicOnTransition
	end

TinTower_2F_MosaicOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, TinTower_2F_MosaicRandomOnTransition
	getcaughtmon SPECIES_RESHIRAM
	goto_if_eq VAR_RESULT, TRUE, TinTower_2F_MosaicHideReshiram
	clearflag FLAG_HIDE_MOSAIC_RESHIRAM
	return

TinTower_2F_MosaicRandomOnTransition::
	goto_if_set FLAG_CAUGHT_RANDOM_TINTOWER_RESHIRAM, TinTower_2F_MosaicHideReshiram
	clearflag FLAG_HIDE_MOSAIC_RESHIRAM
	return

TinTower_2F_MosaicHideReshiram::
	setflag FLAG_HIDE_MOSAIC_RESHIRAM
	return

TinTower_2F_EventScript_Reshiram::
	lock
	faceplayer
	playmoncry SPECIES_RESHIRAM, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_RESHIRAM, 44
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, TinTower_2F_MosaicReshiramRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, TinTower_2F_MosaicReshiramRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TinTower_2F_MosaicReshiramResolvedRandomCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TinTower_2F_MosaicReshiramResolved
	release
	end

TinTower_2F_MosaicReshiramResolvedRandomCaught::
	setflag FLAG_CAUGHT_RANDOM_TINTOWER_RESHIRAM
	goto TinTower_2F_MosaicReshiramResolved

TinTower_2F_MosaicReshiramResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_RESHIRAM
	setflag FLAG_HIDE_MOSAIC_RESHIRAM
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

TinTower_2F_MosaicReshiramRetreated::
	release
	end
