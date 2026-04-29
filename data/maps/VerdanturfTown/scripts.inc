VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_Getkwondo::
	msgbox VerdanturfTown_Text_Getkwondobegin, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GETKWONDO, VerdanturfTown_Text_Getkwondolost
	closemessage
	playbgm MUS_NONE, 0
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_VERDANTURF_GETKWONDO
	setflag FLAG_GETKWONDO
	playse SE_PUDDLE
	waitse
	delay 10
	playse SE_BRIDGE_WALK
	delay 5
	playse SE_BRIDGE_WALK
	delay 5
	playse SE_BRIDGE_WALK
	waitse
	delay 20
	playse SE_TRUCK_DOOR
	waitse
	delay 30
	playse SE_FU_ZAKU
	waitse
	delay 10
	playse SE_CONTEST_PLACE
	waitse
	delay 30
	playse SE_NOTE_E
	waitse
	delay 5
	playse SE_NOTE_E
	waitse
	delay 5
	playse SE_NOTE_F
	waitse
	delay 5
	playse SE_NOTE_G
	waitse
	delay 5
	playse SE_NOTE_G
	waitse
	delay 5
	playse SE_NOTE_F
	waitse
	delay 5
	playse SE_NOTE_E
	waitse
	delay 5
	playse SE_NOTE_D
	waitse
	delay 5
	playse SE_NOTE_C
	waitse
	delay 5
	playse SE_NOTE_C
	waitse
	delay 5
	playse SE_NOTE_D
	waitse
	delay 5
	playse SE_NOTE_E
	waitse
	delay 5
	playse SE_NOTE_E
	waitse
	delay 15
	playse SE_NOTE_D
	waitse
	playse SE_NOTE_D
	waitse
	delay 50
	playse SE_DING_DONG
	waitse
	fadescreen FADE_FROM_BLACK
	msgbox VerdanturfTown_Text_Getkwondofinal, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	release
	
	
VerdanturfTown_Text_Getkwondobegin:
	.string "I have trained the ultimate Pokémon!\p"
	.string "I have developed the ultimate\n"
	.string "strategy!\p"
	.string "I am the ultimate trainer!\p"
	.string "And I am standing in your way?\n"
	.string "Well not for long!\p"
	.string "Because I'll blow you away!$"

VerdanturfTown_Text_Getkwondolost:
	.string "No...\n"
	.string "It was the ultimate strategy.\p"
	.string "How can this be?$"

VerdanturfTown_Text_Getkwondofinal:
	.string "The end.$"

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "My papa told me.\p"
	.string "He says this tunnel is full of\n"
	.string "timid POKéMON.\p"
	.string "They get all scared of loud noise and\n"
	.string "make a big uproar.\p"
	.string "So they had to stop the big tunnel\n"
	.string "project.\p"
	.string "But there's one man. He's trying to dig\n"
	.string "the tunnel by himself!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "There was a man who dug a tunnel for\n"
	.string "a lady he loved.\p"
	.string "I don't really get it, but hey!$"

VerdanturfTown_Text_AirCleanHere:
	.string "The way the winds blow, volcanic ash\n"
	.string "is never blown in this direction.\p"
	.string "The air is clean and delicious here.\n"
	.string "Living here should do wonders for even\l"
	.string "frail and sickly people.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "My POKéMON and I, we've been riding\n"
	.string "a hot winning streak.\p"
	.string "So I decided to make my BATTLE TENT\n"
	.string "debut in this town.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "Did you see the cave next to the\n"
	.string "POKéMON MART?\p"
	.string "There's a guy in there who's trying to\n"
	.string "bust up boulders so he can bust out\l"
	.string "through to the other side.\p"
	.string "It'd be great if we could go through…\n"
	.string "It'll make it easy to visit RUSTBORO.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "That cave next to the POKéMON MART\n"
	.string "is now a tunnel to the other side.\p"
	.string "It's great--it's easy to go shop for\n"
	.string "new DEVON products in RUSTBORO now.$"

VerdanturfTown_Text_TownSign:
	.string "VERDANTURF TOWN\p"
	.string "“The windswept highlands with the\n"
	.string "sweet fragrance of grass.”$"

VerdanturfTown_Text_WandasHouse:
	.string "WANDA'S HOUSE$"

VerdanturfTown_Text_BattleTentSign:
	.string "BATTLE TENT VERDANTURF SITE\n"
	.string "“Feast Your Eyes on Battles!”$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "RUSTURF TUNNEL\n"
	.string "“Linking RUSTBORO and VERDANTURF\p"
	.string "“The tunnel project has been\n"
	.string "canceled.”$"

