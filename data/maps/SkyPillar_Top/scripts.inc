SkyPillar_Top_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SkyPillar_Top_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_Top_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SkyPillar_Top_OnWarp
	.byte 0

SkyPillar_Top_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, SkyPillar_Top_EventScript_TryRemoveRayquaza
	end

SkyPillar_Top_EventScript_TryRemoveRayquaza::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

SkyPillar_Top_OnTransition:
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_Top_EventScript_SetCleanLayout
	call_if_ge VAR_SKY_PILLAR_STATE, 2, SkyPillar_Top_EventScript_TryShowRayquaza
	end

SkyPillar_Top_EventScript_SetCleanLayout::
	setmaplayoutindex LAYOUT_SKY_PILLAR_TOP_CLEAN
	setobjectmovementtype LOCALID_RAYQUAZA_SLEEPING, MOVEMENT_TYPE_FACE_DOWN
	return

SkyPillar_Top_EventScript_TryShowRayquaza::
	call_if_unset FLAG_DEFEATED_RAYQUAZA, SkyPillar_Top_EventScript_ShowRayquaza
	return

SkyPillar_Top_EventScript_ShowRayquaza::
	clearflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA_STILL
	return

SkyPillar_Top_OnWarp:
	map_script_2 VAR_SKY_PILLAR_STATE, 0, SkyPillar_Top_EventScript_RayquazaFaceDown
	.2byte 0

SkyPillar_Top_EventScript_RayquazaFaceDown::
	turnobject LOCALID_RAYQUAZA_SLEEPING, DIR_SOUTH
	end

SkyPillar_Top_EventScript_Rayquaza::
	lockall
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RAYQUAZA, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_ERIVALRAYQUAZA, 1
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SkyPillar_Top_EventScript_DefeatedRayquaza
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SkyPillar_Top_EventScript_RanFromRayquaza
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SkyPillar_Top_EventScript_RanFromRayquaza
	setflag FLAG_DEFEATED_RAYQUAZA
	releaseall
	end

SkyPillar_Top_EventScript_DefeatedRayquaza::
	setflag FLAG_DEFEATED_RAYQUAZA
	goto SkyPillar_Top_EventScript_DefeatedRayquaza2
	end

SkyPillar_Top_EventScript_RanFromRayquaza::
	setvar VAR_0x8004, SPECIES_RAYQUAZA
	goto SkyPillar_Top_EventScript_RanFromRayquaza2
	end

SkyPillar_Top_EventScript_DefeatedRayquaza2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

SkyPillar_Top_EventScript_RanFromRayquaza2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	releaseall
	end

SkyPillar_Top_EventScript_AwakenRayquaza::
	lockall
	fadeoutbgm 1
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_RayquazaStir
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	waitmoncry
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_RayquazaFlyOff
	waitmovement 0
	removeobject LOCALID_RAYQUAZA_SLEEPING
	msgbox SkyPillar_Top_Text_RayquazaFlewOff, MSGBOX_DEFAULT
	closemessage
	delay 20
	fadeinbgm 1
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_SOOTOPOLIS_CITY_STATE, 5
	setvar VAR_SKY_PILLAR_STATE, 1
	setvar VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE, 1
	releaseall
	end

SkyPillar_Top_EventScript_IntroFinal::
	lock
	setvar VAR_ERIVALRAYQUAZA, 2
	fadeoutbgm 1
	delay 80
	setvar VAR_0x8000, MUGSHOT_INTROMIN1
	setvar VAR_0x8001, 1
	setvar VAR_0x8002, 2
	callnative DrawMugshotAtPos
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO0
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTROMIN1
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO0
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTROMIN1
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO0
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO1
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO2
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO1
	callnative DrawMugshot
	delay 20
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	delay 20
	setvar VAR_0x8000, MUGSHOT_INTRO2
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO1
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO2
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO3
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO4
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO3
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO4
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO3
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO4
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO5
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO6
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO5
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO6
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO5
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_INTRO6
	callnative DrawMugshot
	delay 40
	callnative ClearMugshot
	delay 40
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanRight
	waitmovement 0
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	addobject LOCALID_WINGULL1
	waitmovement 0
	setobjectxy LOCALID_WINGULL1, 15, 23
	waitmovement 0
	addobject LOCALID_WINGULL2
	waitmovement 0
	setobjectxy LOCALID_WINGULL2, 17, 23
	waitmovement 0
	applymovement LOCALID_WINGULL1, SkyPillar_Top_Movement_WingullArrive
	applymovement LOCALID_WINGULL2, SkyPillar_Top_Movement_WingullArrive
	waitmovement 0
	delay 20
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	delay 120
	applymovement LOCALID_WINGULL1, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	applymovement LOCALID_WINGULL1, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_WINGULL2, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 120
	addobject LOCALID_CHOSEN_ONE
	playbgm MUS_RG_ENCOUNTER_DEOXYS, FALSE
	setobjectxy LOCALID_CHOSEN_ONE, 16, 14
	waitmovement 0
	playse SE_DOOR
	applymovement LOCALID_CHOSEN_ONE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 20
	applymovement LOCALID_WINGULL1, Common_Movement_FaceUp
	applymovement LOCALID_WINGULL2, Common_Movement_FaceUp
	waitmovement 0
	delay 10
	playse SE_PIN
	applymovement LOCALID_WINGULL1, Common_Movement_ExclamationMark
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WINGULL2, Common_Movement_ExclamationMark
	waitmovement 
	playmoncry SPECIES_WINGULL, CRY_MODE_DOUBLES
	applymovement LOCALID_CHOSEN_ONE, SkyPillar_Top_Movement_SlowDown
	waitmovement 0
	applymovement LOCALID_WINGULL1, SkyPillar_Top_Movement_WingullFlee
	applymovement LOCALID_WINGULL2, SkyPillar_Top_Movement_WingullFlee
	waitmovement 0
	removeobject LOCALID_WINGULL1
	removeobject LOCALID_WINGULL2
	waitmovement 0
	delay 40
	applymovement LOCALID_CHOSEN_ONE, SkyPillar_Top_Movement_SlowLeft
	delay 120
	applymovement LOCALID_CHOSEN_ONE, SkyPillar_Top_Movement_SlowLeft
	delay 120
	applymovement LOCALID_CHOSEN_ONE, SkyPillar_Top_Movement_SlowLeft
	delay 120
	applymovement LOCALID_CHOSEN_ONE, SkyPillar_Top_Movement_SlowLeft
	delay 120
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanBack
	waitmovement 0
	special RemoveCameraObject
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR1
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR2
	callnative DrawMugshot
	applymovement LOCALID_CHOSEN_ONE, SkyPillar_Top_Movement_SlowUp
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR3
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR4
	callnative DrawMugshot
	applymovement LOCALID_CHOSEN_ONE, SkyPillar_Top_Movement_SlowUp
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR5
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR6
	callnative DrawMugshot
	applymovement LOCALID_CHOSEN_ONE, SkyPillar_Top_Movement_SlowUp
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7B
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7B
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7B
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7B
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_APPEAR7
	callnative DrawMugshot
	delay 40
	setobjectxy LOCALID_CHOSEN_ONE, 11, 12
	setvar VAR_0x8000, MUGSHOT_APPEAR7B
	callnative DrawMugshot
	delay 40
	callnative ClearMugshot
	release
	end

SkyPillar_Top_EventScript_TalkToChosenOne::
	faceplayer
	waitmovement 0
	end

SkyPillar_Top_EventScript_WalkToChosenOne::
	playbgm MUS_RG_ENCOUNTER_DEOXYS, FALSE
	lock
	delay 20
	applymovement LOCALID_PLAYER, SkyPillar_Top_Movement_TriggerWalk
	waitmovement 0
	call SkyPillar_Top_EventScript_FinalEncounter
	end

SkyPillar_Top_EventScript_FinalEncounter::
	delay 20
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER1
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER2
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER1
	callnative DrawMugshot
	delay 40
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER2
	callnative DrawMugshot
	delay 40
	playse SE_M_LOCK_ON
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER3
	callnative DrawMugshot
	delay 5
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER4
	callnative DrawMugshot
	delay 5
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER5
	callnative DrawMugshot
	delay 5
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER6
	callnative DrawMugshot
	delay 5
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER7
	callnative DrawMugshot
	delay 5
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER6
	callnative DrawMugshot
	delay 5
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER7
	callnative DrawMugshot
	delay 5
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER6
	callnative DrawMugshot
	delay 5
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER7
	callnative DrawMugshot
	delay 10
	playse SE_M_COSMIC_POWER
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8
	callnative DrawMugshot
	delay 2
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A1
	callnative DrawMugshot
	delay 2
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A2
	callnative DrawMugshot
	delay 2
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A1
	callnative DrawMugshot
	delay 2
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A2
	callnative DrawMugshot
	delay 1
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A1
	callnative DrawMugshot
	delay 1
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A2
	callnative DrawMugshot
	delay 1
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A1
	callnative DrawMugshot
	delay 1
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A2
	callnative DrawMugshot
	delay 2
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A1
	callnative DrawMugshot
	delay 2
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A2
	callnative DrawMugshot
	delay 2
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A1
	callnative DrawMugshot
	delay 2
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER8A2
	callnative DrawMugshot
	delay 2
	fadescreen FADE_TO_WHITE
	delay 30
	playse SE_M_CONFUSE_RAY
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER9
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER10
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER11
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER12
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER13
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER14
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER15
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER16
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER17
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER18
	callnative DrawMugshot
	playse SE_RG_DEOXYS_MOVE
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER19
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER20
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER21
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER22
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER23
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER24
	callnative DrawMugshot
	delay 7
	setvar VAR_0x8000, MUGSHOT_ENCOUNTER25
	callnative DrawMugshot
	delay 7
	trainerbattle_no_intro TRAINER_ERIVALFINAL, SkyPillar_Top_Text_ErivalLost
	removeobject LOCALID_CHOSEN_ONE
	addobject LOCALID_SKYPILLAR_EXTRARIVAL
	setobjectxy LOCALID_SKYPILLAR_EXTRARIVAL, 11, 12
	setvar VAR_ERIVALRAYQUAZA, 3
	callnative ClearMugshot
	release
	end 


SkyPillar_Top_EventScript_Erival::
	lock
	playbgm MUS_B_PIKE, FALSE
	msgbox SkyPillar_Top_Text_Postbattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SKYPILLAR_EXTRARIVAL, SkyPillar_Top_Movement_RivalExit
	waitmovement 0 
	playse SE_PIN
	applymovement LOCALID_SKYPILLAR_EXTRARIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	playse SE_FALL
	removeobject LOCALID_SKYPILLAR_EXTRARIVAL
	delay 40
	playse SE_M_BUBBLE
	waitse
	delay 10
	playse SE_M_BUBBLE2
	waitse
	delay 180
	msgbox SkyPillar_Top_Text_PostbattleFinal, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	release
	end

@ Rayquaza has unusual movement frames
@ See comments, or sAnimTable_Rayquaza
SkyPillar_Top_Movement_RayquazaStir:
	delay_16
	walk_in_place_fast_left  @ Coiled, awake
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left  @ Coiled, mouth open
	delay_16
	walk_in_place_right  @ Normal, awake
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

SkyPillar_Top_Movement_RayquazaFlyOff:
	delay_16
	walk_in_place_down  @ Coiled, asleep
	delay_8
	walk_in_place_right  @ Normal, awake
	delay_8
	walk_faster_up  @ Fly up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

SkyPillar_Top_Movement_CameraPanUp:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

SkyPillar_Top_Movement_CameraPanDown:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

SkyPillar_Top_Movement_CameraPanBack:
	walk_faster_up
	walk_faster_up
	walk_fast_left
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_fast_left
	step_end

SkyPillar_Top_Movement_CameraPanRight:
	walk_slow_right
	walk_slow_right
	step_end

SkyPillar_Top_Movement_TalkWalk:
	walk_right
	walk_right
	walk_right
	face_down
	step_end

SkyPillar_Top_Movement_TriggerWalk:
	walk_up
	walk_right
	walk_right
	face_down
	step_end


SkyPillar_Top_Movement_WingullArrive:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_slow_up
	step_end

SkyPillar_Top_Movement_SlowDown:
	walk_slow_down
	step_end

SkyPillar_Top_Movement_SlowLeft:
	walk_slow_left
	step_end

SkyPillar_Top_Movement_SlowUp:
	walk_slow_up
	step_end

SkyPillar_Top_Movement_WingullFlee:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SkyPillar_Top_Movement_RivalExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

SkyPillar_Top_Text_RayquazaFlewOff:
	.string "The awakened RAYQUAZA flew off…$"

SkyPillar_Top_Text_ErivalLost:
	.string "...$"	

SkyPillar_Top_Text_Postbattle:
	.string "oh noes i loset!\p"
	.string "...\p"
	.string "By the way,\n"
	.string "where the fuck was Emerald?\p"
	.string "...\p"
	.string "...???\n"
	.string "That green thing?\p"
	.string "...\p"
	.string "Are you fucking kidding me?\n"
	.string "Ree kweyzar?\p"
	.string "Major weak-sauce dude.\p"
	.string "What do you mean I got it wrong?\n"
	.string "Is Emerald not going to get us all?\p"
	.string "...\p"
	.string "Our saviour???????????\p"
	.string "I went to space for that?\n"
	.string "Awwwwww maaaaannnnnnnnnnn\p"
	.string "Well...\n"
	.string "At least I got that cool cloak!\p"
	.string "...\n"
	.string "Where is that thing anyway?\p"
	.string "Ohhh right! I threw it off for dramatic\n"
	.string "effect.\p"
	.string "Ok, I'm gonna retrieve it.\p"
	.string "It was a sweet cloak.\p"
	.string "Byeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee.$"
	
SkyPillar_Top_Text_PostbattleFinal:
	.string "FOUND IT!$"