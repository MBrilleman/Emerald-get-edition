Route122_MapScripts::
	.byte 0

Route122_EventScript_Lefto::
	lock
	msgbox Route122_Text_Lefto_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LEFTO, Route122_Lefto_Text_Defeat
	msgbox Route122_Text_Lefto_Give, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	delay 10
	giveitem ITEM_LEFTOVERS
	//Check met Marcus voor de to pc if bag full 
	closemessage
	removeobject LOCALID_ROUTE122_LEFTO
	setflag FLAG_RANDO_LEFTO
	fadescreen FADE_FROM_BLACK
	delay 20
	msgbox Route122_Text_Lefto_Outro, MSGBOX_GETPOINTS
	delay 40
	closemessage
	
	Route122_Text_Lefto_Intro:
	.string "Hi!\p"
	.string "I'm Vers.\p"
	.string "But you can call me Lefto!\p"
	.string "I was tossed in this water a long\n"
	.string "time ago...\l"
	.string "And have been floating here ever since.\p"
	.string "Are you on an adventure?\p"
	.string "Please.\n"
	.string "Take me with you!\p"
	.string "I'll turn into an item if you defeat me.\n"
	.string "You'll be able to pick me up!\p"
	.string "You can let your POKéMON chew on me,\n"
	.string "I don't care. Just get me out of here!!!$"

	Route122_Lefto_Text_Defeat:
	.string "A LEFTOVERS a day keeps the\n"
	.string "POKéMON center away!$"

	Route122_Text_Lefto_Give:
	.string "Lefto Vers floats before you in\n"
	.string "the water. You decide to pick it up.$"

	Route122_Text_Lefto_Outro:
	.string "Lefto has joined you on your\n"
	.string "ADVENTURE!$"
