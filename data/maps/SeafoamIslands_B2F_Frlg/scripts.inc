SeafoamIslands_B2F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_B2F_OnTransition
	.byte 0

SeafoamIslands_B2F_OnTransition::
	call SeafoamIslands_B2F_MosaicOnTransition
	end

// The original cave event set was empty. These statics coexist with the native
// wild habitat and normal stairs, items, Strength puzzles, and Articuno events.
SeafoamIslands_B2F_MosaicOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, SeafoamIslands_B2F_MosaicRandomOnTransition
	getcaughtmon SPECIES_MANAPHY
	call_if_eq VAR_RESULT, TRUE, SeafoamIslands_B2F_MosaicHideManaphy
	call_if_ne VAR_RESULT, TRUE, SeafoamIslands_B2F_MosaicShowManaphy
	getcaughtmon SPECIES_TAPU_FINI
	call_if_eq VAR_RESULT, TRUE, SeafoamIslands_B2F_MosaicHideTapuFini
	call_if_ne VAR_RESULT, TRUE, SeafoamIslands_B2F_MosaicShowTapuFini
	return

SeafoamIslands_B2F_MosaicRandomOnTransition::
	call_if_set FLAG_CAUGHT_RANDOM_SEAFOAMISLANDS_B2F_MANAPHY, SeafoamIslands_B2F_MosaicHideManaphy
	call_if_unset FLAG_CAUGHT_RANDOM_SEAFOAMISLANDS_B2F_MANAPHY, SeafoamIslands_B2F_MosaicShowManaphy
	call_if_set FLAG_CAUGHT_RANDOM_SEAFOAMISLANDS_B2F_TAPU_FINI, SeafoamIslands_B2F_MosaicHideTapuFini
	call_if_unset FLAG_CAUGHT_RANDOM_SEAFOAMISLANDS_B2F_TAPU_FINI, SeafoamIslands_B2F_MosaicShowTapuFini
	return

SeafoamIslands_B2F_MosaicHideManaphy::
	setflag FLAG_HIDE_MOSAIC_MANAPHY
	return

SeafoamIslands_B2F_MosaicShowManaphy::
	clearflag FLAG_HIDE_MOSAIC_MANAPHY
	return

// Caught: permanently hidden. Won without catch: reappears on re-entry.
// Run/teleport: remains available at the current site.
SeafoamIslands_B2F_EventScript_Manaphy::
	lock
	faceplayer
	playmoncry SPECIES_MANAPHY, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_MANAPHY, 35
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SeafoamIslands_B2F_MosaicManaphyRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SeafoamIslands_B2F_MosaicManaphyRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SeafoamIslands_B2F_MosaicManaphyResolvedRandomCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SeafoamIslands_B2F_MosaicManaphyResolved
	release
	end

SeafoamIslands_B2F_MosaicManaphyResolvedRandomCaught::
	setflag FLAG_CAUGHT_RANDOM_SEAFOAMISLANDS_B2F_MANAPHY
	goto SeafoamIslands_B2F_MosaicManaphyResolved

SeafoamIslands_B2F_MosaicManaphyResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_MANAPHY
	setflag FLAG_HIDE_MOSAIC_MANAPHY
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SeafoamIslands_B2F_MosaicManaphyRetreated::
	release
	end

SeafoamIslands_B2F_MosaicHideTapuFini::
	setflag FLAG_HIDE_MOSAIC_TAPU_FINI
	return

SeafoamIslands_B2F_MosaicShowTapuFini::
	clearflag FLAG_HIDE_MOSAIC_TAPU_FINI
	return

// Caught: permanently hidden. Won without catch: reappears on re-entry.
// Run/teleport: remains available at the current site.
SeafoamIslands_B2F_EventScript_TapuFini::
	lock
	faceplayer
	playmoncry SPECIES_TAPU_FINI, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_TAPU_FINI, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SeafoamIslands_B2F_MosaicTapuFiniRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SeafoamIslands_B2F_MosaicTapuFiniRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SeafoamIslands_B2F_MosaicTapuFiniResolvedRandomCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SeafoamIslands_B2F_MosaicTapuFiniResolved
	release
	end

SeafoamIslands_B2F_MosaicTapuFiniResolvedRandomCaught::
	setflag FLAG_CAUGHT_RANDOM_SEAFOAMISLANDS_B2F_TAPU_FINI
	goto SeafoamIslands_B2F_MosaicTapuFiniResolved

SeafoamIslands_B2F_MosaicTapuFiniResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_TAPU_FINI
	setflag FLAG_HIDE_MOSAIC_TAPU_FINI
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SeafoamIslands_B2F_MosaicTapuFiniRetreated::
	release
	end
