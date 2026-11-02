MtMoon_B1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMoon_B1F_OnTransition
	.byte 0

MtMoon_B1F_OnTransition::
	call MtMoon_B1F_MosaicOnTransition
	end

// The original cave event set was empty. These statics coexist with the native
// wild habitat and normal stairs, items, Strength puzzles, and Articuno events.
MtMoon_B1F_MosaicOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, MtMoon_B1F_MosaicRandomOnTransition
	getcaughtmon SPECIES_CRESSELIA
	call_if_eq VAR_RESULT, TRUE, MtMoon_B1F_MosaicHideCresselia
	call_if_ne VAR_RESULT, TRUE, MtMoon_B1F_MosaicShowCresselia
	getcaughtmon SPECIES_DIALGA
	call_if_eq VAR_RESULT, TRUE, MtMoon_B1F_MosaicHideDialga
	call_if_ne VAR_RESULT, TRUE, MtMoon_B1F_MosaicShowDialga
	getcaughtmon SPECIES_PALKIA
	call_if_eq VAR_RESULT, TRUE, MtMoon_B1F_MosaicHidePalkia
	call_if_ne VAR_RESULT, TRUE, MtMoon_B1F_MosaicShowPalkia
	return

// In randomized games each encounter's own completion bit, not the species
// caught anywhere else, controls visibility and Giratina's prerequisites.
MtMoon_B1F_MosaicRandomOnTransition::
	call_if_set FLAG_CAUGHT_RANDOM_MTMOON_CRESSELIA, MtMoon_B1F_MosaicHideCresselia
	call_if_unset FLAG_CAUGHT_RANDOM_MTMOON_CRESSELIA, MtMoon_B1F_MosaicShowCresselia
	call_if_set FLAG_CAUGHT_RANDOM_MTMOON_DIALGA, MtMoon_B1F_MosaicHideDialga
	call_if_unset FLAG_CAUGHT_RANDOM_MTMOON_DIALGA, MtMoon_B1F_MosaicShowDialga
	call_if_set FLAG_CAUGHT_RANDOM_MTMOON_PALKIA, MtMoon_B1F_MosaicHidePalkia
	call_if_unset FLAG_CAUGHT_RANDOM_MTMOON_PALKIA, MtMoon_B1F_MosaicShowPalkia
	return

MtMoon_B1F_MosaicHideCresselia::
	setflag FLAG_HIDE_MOSAIC_CRESSELIA
	return

MtMoon_B1F_MosaicShowCresselia::
	clearflag FLAG_HIDE_MOSAIC_CRESSELIA
	return

// Caught: permanently hidden. Won without catch: reappears on re-entry.
// Run/teleport: remains available at the current site.
MtMoon_B1F_EventScript_Cresselia::
	lock
	faceplayer
	playmoncry SPECIES_CRESSELIA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_CRESSELIA, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MtMoon_B1F_MosaicCresseliaRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MtMoon_B1F_MosaicCresseliaRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtMoon_B1F_MosaicCresseliaCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MtMoon_B1F_MosaicCresseliaResolved
	release
	end

MtMoon_B1F_MosaicCresseliaCaught::
	setflag FLAG_CAUGHT_RANDOM_MTMOON_CRESSELIA
	goto MtMoon_B1F_MosaicCresseliaResolved

MtMoon_B1F_MosaicCresseliaResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_CRESSELIA
	setflag FLAG_HIDE_MOSAIC_CRESSELIA
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

MtMoon_B1F_MosaicCresseliaRetreated::
	release
	end

MtMoon_B1F_MosaicHideDialga::
	setflag FLAG_HIDE_MOSAIC_DIALGA
	return

MtMoon_B1F_MosaicShowDialga::
	clearflag FLAG_HIDE_MOSAIC_DIALGA
	return

// Caught: permanently hidden. Won without catch: reappears on re-entry.
// Run/teleport: remains available at the current site.
MtMoon_B1F_EventScript_Dialga::
	lock
	faceplayer
	playmoncry SPECIES_DIALGA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_DIALGA, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MtMoon_B1F_MosaicDialgaRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MtMoon_B1F_MosaicDialgaRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtMoon_B1F_MosaicDialgaCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MtMoon_B1F_MosaicDialgaResolved
	release
	end

MtMoon_B1F_MosaicDialgaCaught::
	setflag FLAG_CAUGHT_RANDOM_MTMOON_DIALGA
	goto MtMoon_B1F_MosaicDialgaResolved

MtMoon_B1F_MosaicDialgaResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_DIALGA
	setflag FLAG_HIDE_MOSAIC_DIALGA
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

MtMoon_B1F_MosaicDialgaRetreated::
	release
	end

MtMoon_B1F_MosaicHidePalkia::
	setflag FLAG_HIDE_MOSAIC_PALKIA
	return

MtMoon_B1F_MosaicShowPalkia::
	clearflag FLAG_HIDE_MOSAIC_PALKIA
	return

// Caught: permanently hidden. Won without catch: reappears on re-entry.
// Run/teleport: remains available at the current site.
MtMoon_B1F_EventScript_Palkia::
	lock
	faceplayer
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_PALKIA, 45
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MtMoon_B1F_MosaicPalkiaRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MtMoon_B1F_MosaicPalkiaRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtMoon_B1F_MosaicPalkiaCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MtMoon_B1F_MosaicPalkiaResolved
	release
	end

MtMoon_B1F_MosaicPalkiaCaught::
	setflag FLAG_CAUGHT_RANDOM_MTMOON_PALKIA
	goto MtMoon_B1F_MosaicPalkiaResolved

MtMoon_B1F_MosaicPalkiaResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_PALKIA
	setflag FLAG_HIDE_MOSAIC_PALKIA
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

MtMoon_B1F_MosaicPalkiaRetreated::
	release
	end

