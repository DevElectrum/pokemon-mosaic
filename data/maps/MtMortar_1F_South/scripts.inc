MtMortar_1F_South_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMortar_1F_South_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MtMortar_1F_South_OnTransition: 
	call MtMortar_1F_South_MosaicOnTransition
	end



MtMortar_1F_South_EventScript_Item_Revive::
    finditem ITEM_REVIVE
    end

MtMortar_1F_South_EventScript_Item_Elixir::
    finditem ITEM_ELIXIR
    end

// Independent early/mid-Johto Sword of Justice static. No sibling capture gate.
MtMortar_1F_South_MosaicOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, MtMortar_1F_South_MosaicRandomOnTransition
	getcaughtmon SPECIES_COBALION
	call_if_eq VAR_RESULT, TRUE, MtMortar_1F_South_MosaicHideCobalion
	call_if_ne VAR_RESULT, TRUE, MtMortar_1F_South_MosaicShowCobalion
	return

MtMortar_1F_South_MosaicRandomOnTransition::
	call_if_set FLAG_CAUGHT_RANDOM_MTMORTAR_COBALION, MtMortar_1F_South_MosaicHideCobalion
	call_if_unset FLAG_CAUGHT_RANDOM_MTMORTAR_COBALION, MtMortar_1F_South_MosaicShowCobalion
	return

MtMortar_1F_South_MosaicHideCobalion::
	setflag FLAG_HIDE_MOSAIC_COBALION
	return

MtMortar_1F_South_MosaicShowCobalion::
	clearflag FLAG_HIDE_MOSAIC_COBALION
	return

MtMortar_1F_South_EventScript_Cobalion::
	lock
	faceplayer
	playmoncry SPECIES_COBALION, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_COBALION, 28
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MtMortar_1F_South_MosaicCobalionRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MtMortar_1F_South_MosaicCobalionRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtMortar_1F_South_MosaicCobalionResolvedRandomCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MtMortar_1F_South_MosaicCobalionResolved
	release
	end

MtMortar_1F_South_MosaicCobalionResolvedRandomCaught::
	setflag FLAG_CAUGHT_RANDOM_MTMORTAR_COBALION
	goto MtMortar_1F_South_MosaicCobalionResolved

MtMortar_1F_South_MosaicCobalionResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_COBALION
	setflag FLAG_HIDE_MOSAIC_COBALION
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

MtMortar_1F_South_MosaicCobalionRetreated::
	release
	end
