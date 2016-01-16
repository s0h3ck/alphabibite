/**
 * K3P16 © Copyright 2015
 * Date : 25/11/2015
 *
 * File's name: messages.cpp
 */

#include "messages.h"

void state_win(void)
{
	int i = 0;

	LCD_ClearAndPrint("Bravo!");
	play_sound((char*)"bravo");

	for(i = 0; i < 5; i++)
	{
		DIGITALIO_Write(14, 0);
		THREAD_MSleep(250);
		DIGITALIO_Write(14, 1);
		THREAD_MSleep(250);
	}
}

void state_lose(void)
{
	int i = 0;

	LCD_ClearAndPrint("Ha non!");
	play_sound((char*)"ahnon");
	for(i = 0; i < 5; i++)
	{
		DIGITALIO_Write(15, 0);
		THREAD_MSleep(250);
		DIGITALIO_Write(15, 1);
		THREAD_MSleep(250);
	}
	DIGITALIO_Write(15, 0);
}

