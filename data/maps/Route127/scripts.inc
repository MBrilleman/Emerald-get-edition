Route127_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route127_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route127_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route127_OnFrame
	.byte 0

Route127_OnTransition:
	//call testywesty
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_127_NORTH, AbnormalWeather_StartKyogreWeather
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_127_SOUTH, AbnormalWeather_StartKyogreWeather
	end

testywesty::
	setvar VAR_ROUTE127_STATE, 0
	return

Route127_OnLoad:
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_127_NORTH, AbnormalWeather_EventScript_PlaceTilesRoute127North
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_127_SOUTH, AbnormalWeather_EventScript_PlaceTilesRoute127South
	end

Route127_OnFrame:
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route127_EventScript_Camden::
	trainerbattle_single TRAINER_CAMDEN, Route127_Text_CamdenIntro, Route127_Text_CamdenDefeat
	msgbox Route127_Text_CamdenPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Donny::
	trainerbattle_single TRAINER_DONNY, Route127_Text_DonnyIntro, Route127_Text_DonnyDefeat
	msgbox Route127_Text_DonnyPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Jonah::
	trainerbattle_single TRAINER_JONAH, Route127_Text_JonahIntro, Route127_Text_JonahDefeat
	msgbox Route127_Text_JonahPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Henry::
	trainerbattle_single TRAINER_HENRY, Route127_Text_HenryIntro, Route127_Text_HenryDefeat
	msgbox Route127_Text_HenryPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Roger::
	trainerbattle_single TRAINER_ROGER, Route127_Text_RogerIntro, Route127_Text_RogerDefeat
	msgbox Route127_Text_RogerPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Aidan::
	trainerbattle_single TRAINER_AIDAN, Route127_Text_AidanIntro, Route127_Text_AidanDefeat
	msgbox Route127_Text_AidanPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Athena::
	trainerbattle_single TRAINER_ATHENA, Route127_Text_AthenaIntro, Route127_Text_AthenaDefeat
	msgbox Route127_Text_AthenaPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Koji::
	trainerbattle_single TRAINER_KOJI_1, Route127_Text_KojiIntro, Route127_Text_KojiDefeat, Route127_EventScript_RegisterKoji
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route127_EventScript_RematchKoji
	msgbox Route127_Text_KojiPostBattle, MSGBOX_DEFAULT
	release
	end

Route127_EventScript_RegisterKoji::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route127_Text_KojiRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KOJI_1
	release
	end

Route127_EventScript_RematchKoji::
	trainerbattle_rematch TRAINER_KOJI_1, Route127_Text_KojiRematchIntro, Route127_Text_KojiRematchDefeat
	msgbox Route127_Text_KojiPostRematch, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_TalkJoke::
	msgbox Route127_TalkJoke_Text, MSGBOX_DEFAULT
	closemessage
	goto Route127_EventScript_JokeExit
	end

Route127_EventScript_Joke_Encounter0::
	lock
	playbgm MUS_RG_MYSTERY_GIFT , FALSE
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 35, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter1::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 36, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter2::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 37, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter3::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 38, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter4::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 39, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter5::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 40, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter6::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 41, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter7::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 42, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter8::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 43, 0
    goto Route127_EventScript_Joke_walkup
	end

Route127_EventScript_Joke_Encounter9::
	lock
	addobject LOCALID_ROUTE127_JOKE
	setobjectxy LOCALID_ROUTE127_JOKE, 44, 0
	goto Route127_EventScript_Joke_walkup	
	end

Route127_EventScript_Joke_walkup::
	playbgm MUS_RG_MYSTERY_GIFT , FALSE
	playse SE_PIN
	applymovement LOCALID_ROUTE127_JOKE, Common_Movement_ExclamationMark
	applymovement LOCALID_ROUTE127_JOKE, Common_Movement_FaceLeft
	delay 30
	waitmovement 0
	applymovement LOCALID_ROUTE127_JOKE, Route127_Movement_joke
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	goto Route127_EventScript_JokeFight
	end

Route127_EventScript_JokeFight::
	msgbox Route127_FightJoke_Text, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_JOKE, Route127_Joke_Text_defeat
	playbgm MUS_RG_MYSTERY_GIFT , FALSE
	closemessage
	msgbox Route127_Joke_Text_postbattle, MSGBOX_DEFAULT
	closemessage
	call Route127_EventScript_JokeExit
	setvar VAR_ROUTE127_STATE, 1
	msgbox Route127_Joke_Text_Item, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_CHOICE_BAND
	playse SE_APPLAUSE
	msgbox Route127_Joke_text_F, MSGBOX_GETPOINTS
	delay 30
	closemessage
	waitse
	fadedefaultbgm
	release
	releaseall
	end

Route127_EventScript_JokeExit::
	playse SE_M_WATERFALL
	applymovement LOCALID_ROUTE127_JOKE, Route127_Movment_jokeExit
	waitmovement 0
	removeobject LOCALID_ROUTE127_JOKE
	return

Route127_Movement_joke:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route127_Movment_jokeExit:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route127_FightJoke_Text:
	.string "Hi!\n"
	.string "I forgot the name of a Pokémon...\l"
	.string "Can you help me?\p"
	.string "I want to know the name of the Pokémon\n"
	.string "that evolves into Magcargo.\p"
	.string "...\p"
	.string "Oh it's called 'Slugma'?\p"
	.string "SLUGMA DICK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\p"
	.string "HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA\n"
	.string "HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA$"

Route127_Joke_Text_defeat:
	.string "AHAhaha.. ha..\n"
	.string "... ha...  ha?$"

Route127_Joke_Text_postbattle:
	.string "Shit... Fuck! Uhmmm what Pokémon\n"
	.string "evolves from Rhydon?\l"
	.string "Wait. No, that's not right...\p"
	.string "What was that? Rhydon your dick?\p"
	.string "AI NOOOOOOOOOOO MAAT$"

Route127_TalkJoke_Text:
	.string "What Pokémon evolves from Gulpin?\n"
	.string "SWALOT THESE NU-...\p"
	.string "WHAT DID YOU SAY!?!?!\n"
	.string "GULPIN YOUR SPERRIE!?!?!\p"
	.string "AI NOOOOOOOOOOO MAAT$"

Route127_Joke_Text_Item:
	.string "Wow!!!\p"
	.string "His mother will probably have some\n"
	.string "CHOICE words for him!$"

Route127_Joke_text_F:
	.string "That was the joke everyone!\n"
	.string "GOODBYEEEEEEEEEEEEE!$"