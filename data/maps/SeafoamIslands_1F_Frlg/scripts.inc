SeafoamIslands_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_1F_OnTransition
	.byte 0

SeafoamIslands_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SEAFOAM_ISLANDS_1F
	call SeafoamIslands_1F_MosaicOnTransition
	end


// Restore uncaught statics on entry; let the original map scripts run.
SeafoamIslands_1F_MosaicOnTransition::
	call_if_set FLAG_CAUGHT_MOSAIC_COSMOG_SEAFOAM, SeafoamIslands_1F_MosaicHideCosmogSeafoam
	call_if_unset FLAG_CAUGHT_MOSAIC_COSMOG_SEAFOAM, SeafoamIslands_1F_MosaicShowCosmogSeafoam
	return

SeafoamIslands_1F_MosaicHideCosmogSeafoam::
	setflag FLAG_HIDE_MOSAIC_COSMOG_SEAFOAM
	return

SeafoamIslands_1F_MosaicShowCosmogSeafoam::
	clearflag FLAG_HIDE_MOSAIC_COSMOG_SEAFOAM
	return

// Caught: permanently gone. Fainted: returns on re-entry. Run: stays here.
SeafoamIslands_1F_EventScript_CosmogSeafoam::
	lock
	faceplayer
	playmoncry SPECIES_COSMOG, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_COSMOG, 15
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SeafoamIslands_1F_MosaicCosmogSeafoamRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SeafoamIslands_1F_MosaicCosmogSeafoamRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SeafoamIslands_1F_MosaicCosmogSeafoamCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SeafoamIslands_1F_MosaicCosmogSeafoamResolved
	release
	end

SeafoamIslands_1F_MosaicCosmogSeafoamCaught::
	setflag FLAG_CAUGHT_MOSAIC_COSMOG_SEAFOAM
	goto SeafoamIslands_1F_MosaicCosmogSeafoamResolved

SeafoamIslands_1F_MosaicCosmogSeafoamResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_COSMOG_SEAFOAM
	setflag FLAG_HIDE_MOSAIC_COSMOG_SEAFOAM
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SeafoamIslands_1F_MosaicCosmogSeafoamRetreated::
	release
	end
