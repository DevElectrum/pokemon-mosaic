MtPyre_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Exterior_OnTransition
	.byte 0

MtPyre_Exterior_OnTransition:
	call MtPyre_Exterior_EventScript_CheckEnterFromSummit
	call MtPyre_Exterior_MosaicOnTransition
	end

MtPyre_Exterior_EventScript_CheckEnterFromSummit::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_lt VAR_TEMP_1, 12, MtPyre_Exterior_EventScript_EnterFromSummit
	return

MtPyre_Exterior_EventScript_EnterFromSummit::
	setweather WEATHER_FOG_HORIZONTAL
	return

MtPyre_Exterior_EventScript_FogTrigger::
	setweather WEATHER_FOG_HORIZONTAL
	doweather
	end

MtPyre_Exterior_EventScript_SunTrigger::
	setweather WEATHER_SUNNY
	doweather
	end

// All four statics are on one stable exterior layout. Fog/sun boundaries and
// canonical summit script continue to run without changing their logic.
MtPyre_Exterior_MosaicOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, MtPyre_Exterior_MosaicRandomOnTransition
	getcaughtmon SPECIES_YVELTAL
	call_if_eq VAR_RESULT, TRUE, MtPyre_Exterior_MosaicHideYveltal
	call_if_ne VAR_RESULT, TRUE, MtPyre_Exterior_MosaicShowYveltal
	return

MtPyre_Exterior_MosaicRandomOnTransition::
	call_if_set FLAG_CAUGHT_RANDOM_MTPYRE_EXTERIOR_YVELTAL, MtPyre_Exterior_MosaicHideYveltal
	call_if_unset FLAG_CAUGHT_RANDOM_MTPYRE_EXTERIOR_YVELTAL, MtPyre_Exterior_MosaicShowYveltal
	return

MtPyre_Exterior_MosaicHideYveltal::
	setflag FLAG_HIDE_MOSAIC_YVELTAL
	return

MtPyre_Exterior_MosaicShowYveltal::
	clearflag FLAG_HIDE_MOSAIC_YVELTAL
	return

MtPyre_Exterior_EventScript_Yveltal::
	lock
	faceplayer
	playmoncry SPECIES_YVELTAL, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_YVELTAL, 39
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MtPyre_Exterior_MosaicYveltalRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MtPyre_Exterior_MosaicYveltalRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtPyre_Exterior_MosaicYveltalResolvedRandomCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MtPyre_Exterior_MosaicYveltalResolved
	release
	end

MtPyre_Exterior_MosaicYveltalResolvedRandomCaught::
	setflag FLAG_CAUGHT_RANDOM_MTPYRE_EXTERIOR_YVELTAL
	goto MtPyre_Exterior_MosaicYveltalResolved

MtPyre_Exterior_MosaicYveltalResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_YVELTAL
	setflag FLAG_HIDE_MOSAIC_YVELTAL
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

MtPyre_Exterior_MosaicYveltalRetreated::
	release
	end

