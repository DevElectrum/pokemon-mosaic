PokemonMansion_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PokemonMansion_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonMansion_1F_OnTransition
	.byte 0

PokemonMansion_1F_OnLoad::
	call_if_set FLAG_POKEMON_MANSION_SWITCH_STATE, PokemonMansion_EventScript_PressSwitch_1F
	end

PokemonMansion_1F_OnTransition::
	call PokemonMansion_1F_MosaicOnTransition
	setworldmapflag FLAG_WORLD_MAP_POKEMON_MANSION_1F
	end

PokemonMansion_1F_EventScript_Statue::
	lockall
	setvar VAR_0x8004, 0
	call PokemonMansion_EventScript_SecretSwitch
	playse SE_UNLOCK
	special DrawWholeMapView
	waitse
	releaseall
	end

PokemonMansion_1F_EventScript_Ted::
	trainerbattle_single TRAINER_SCIENTIST_TED, PokemonMansion_1F_Text_TedIntro, PokemonMansion_1F_Text_TedDefeat
	msgbox PokemonMansion_1F_Text_TedPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonMansion_1F_EventScript_Johnson::
	trainerbattle_single TRAINER_YOUNGSTER_JOHNSON, PokemonMansion_1F_Text_JohnsonIntro, PokemonMansion_1F_Text_JohnsonDefeat
	msgbox PokemonMansion_1F_Text_JohnsonPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonMansion_1F_Text_TedIntro::
	.string "Who are you?\n"
	.string "There shouldn't be anyone here.$"

PokemonMansion_1F_Text_TedDefeat::
	.string "Ouch!$"

PokemonMansion_1F_Text_TedPostBattle::
	.string "A key? I don't know what you're\n"
	.string "talking about.$"

PokemonMansion_1F_Text_JohnsonIntro::
	.string "W-w-waah! You startled me!\n"
	.string "I thought you were a ghost.$"

PokemonMansion_1F_Text_JohnsonDefeat::
	.string "Tch!\n"
	.string "I can't get any wins.$"

PokemonMansion_1F_Text_JohnsonPostBattle::
	.string "I was exploring here by myself,\n"
	.string "but I feel spooked.\p"
	.string "I ought to go soon.$"

// Independent pre-League encounters; preserve original local puzzle/story.
PokemonMansion_1F_MosaicOnTransition::
	callnative MosaicStaticRandomizerIsOn
	goto_if_eq VAR_RESULT, TRUE, PokemonMansion_1F_MosaicSeededTransition
	getcaughtmon SPECIES_TYPE_NULL
	call_if_eq VAR_RESULT, TRUE, PokemonMansion_1F_MosaicHideTypeNull
	call_if_ne VAR_RESULT, TRUE, PokemonMansion_1F_MosaicShowTypeNull
	return

PokemonMansion_1F_MosaicSeededTransition::
	call_if_set FLAG_CAUGHT_RANDOM_MANSION_MEW, PokemonMansion_1F_MosaicHideMew
	call_if_unset FLAG_CAUGHT_RANDOM_MANSION_MEW, PokemonMansion_1F_MosaicShowMew
	call_if_set FLAG_CAUGHT_RANDOM_MANSION_TYPE_NULL, PokemonMansion_1F_MosaicHideTypeNull
	call_if_unset FLAG_CAUGHT_RANDOM_MANSION_TYPE_NULL, PokemonMansion_1F_MosaicShowTypeNull
	return

PokemonMansion_1F_MosaicHideMew::
	setflag FLAG_HIDE_MOSAIC_MEW
	return

PokemonMansion_1F_MosaicShowMew::
	clearflag FLAG_HIDE_MOSAIC_MEW
	return

PokemonMansion_1F_EventScript_Mew::
	lock
	faceplayer
	special MewGauntletShouldRun
	goto_if_eq VAR_RESULT, FALSE, PokemonMansion_1F_RandomizedMewStatic
	playmoncry SPECIES_MEW, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox PokemonMansion_1F_Text_MewChallenge, MSGBOX_DEFAULT
	special MewGauntletRollDisguises
	setvar VAR_0x8004, 0
	special MewGauntletPrepareBattle
	msgbox PokemonMansion_1F_Text_MewDisguise, MSGBOX_DEFAULT
	playmoncry VAR_0x8005, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartMewGauntletBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, PokemonMansion_1F_MosaicMewRetreated

	setvar VAR_0x8004, 1
	special MewGauntletPrepareBattle
	msgbox PokemonMansion_1F_Text_MewDisguiseAgain, MSGBOX_DEFAULT
	playmoncry VAR_0x8005, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartMewGauntletBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, PokemonMansion_1F_MosaicMewRetreated

	setvar VAR_0x8004, 2
	special MewGauntletPrepareBattle
	msgbox PokemonMansion_1F_Text_MewDisguiseAgain, MSGBOX_DEFAULT
	playmoncry VAR_0x8005, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartMewGauntletBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, PokemonMansion_1F_MosaicMewRetreated

	setvar VAR_0x8004, 3
	special MewGauntletPrepareBattle
	msgbox PokemonMansion_1F_Text_MewRevealed, MSGBOX_DEFAULT
	playmoncry SPECIES_MEW, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartMewGauntletBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, PokemonMansion_1F_MosaicMewResolved
	goto PokemonMansion_1F_MosaicMewRetreated

PokemonMansion_1F_RandomizedMewStatic::
    @ No illusion battle unless the resident species really is Mew.
    seteventmon SPECIES_MEW, 45
    special BattleSetup_StartLegendaryBattle
    waitstate
    specialvar VAR_RESULT, GetBattleOutcome
    goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, PokemonMansion_1F_MosaicMewResolved
    @ Fainting/fleeing does not consume the static location.
    goto PokemonMansion_1F_MosaicMewRetreated

PokemonMansion_1F_Text_MewChallenge::
	.string "MEW looks at you curiously...\p"
	.string "It begins to change shape!$"

PokemonMansion_1F_Text_MewDisguise::
	.string "MEW transformed into\n"
	.string "{STR_VAR_1}!$"

PokemonMansion_1F_Text_MewDisguiseAgain::
	.string "The illusion fades...\p"
	.string "MEW transformed into\n"
	.string "{STR_VAR_1}!$"

PokemonMansion_1F_Text_MewRevealed::
	.string "All three illusions are gone!\p"
	.string "The real MEW appeared!$"

PokemonMansion_1F_MosaicMewResolved::
	callnative MosaicStaticRandomizerIsOn
	call_if_eq VAR_RESULT, TRUE, PokemonMansion_1F_MosaicMarkSeededMew
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_MEW
	setflag FLAG_HIDE_MOSAIC_MEW
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

PokemonMansion_1F_MosaicMarkSeededMew::
	setflag FLAG_CAUGHT_RANDOM_MANSION_MEW
	return

PokemonMansion_1F_MosaicMewRetreated::
	release
	end

PokemonMansion_1F_MosaicHideTypeNull::
	setflag FLAG_HIDE_MOSAIC_TYPE_NULL
	return

PokemonMansion_1F_MosaicShowTypeNull::
	clearflag FLAG_HIDE_MOSAIC_TYPE_NULL
	return

PokemonMansion_1F_EventScript_TypeNull::
	lock
	faceplayer
	playmoncry SPECIES_TYPE_NULL, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_TYPE_NULL, 35
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, PokemonMansion_1F_MosaicTypeNullRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, PokemonMansion_1F_MosaicTypeNullRetreated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, PokemonMansion_1F_MosaicTypeNullCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, PokemonMansion_1F_MosaicTypeNullResolved
	release
	end

PokemonMansion_1F_MosaicTypeNullCaught::
	callnative MosaicStaticRandomizerIsOn
	call_if_eq VAR_RESULT, TRUE, PokemonMansion_1F_MosaicMarkSeededTypeNull
	goto PokemonMansion_1F_MosaicTypeNullResolved

PokemonMansion_1F_MosaicMarkSeededTypeNull::
	setflag FLAG_CAUGHT_RANDOM_MANSION_TYPE_NULL
	return

PokemonMansion_1F_MosaicTypeNullResolved::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MOSAIC_TYPE_NULL
	setflag FLAG_HIDE_MOSAIC_TYPE_NULL
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

PokemonMansion_1F_MosaicTypeNullRetreated::
	release
	end

