/**
 * K3P16 © Copyright 2015
 * Date : 25/11/2015
 *
 * File's name: sounds.cpp
 */

#include "sounds.h"

/**
 * Description: Play a sound file
 * Parameters:
 * 	filename: The name of the file
 * Return: Nothing (void)
 */
void play_sound(char *filename)
{
    char big_array[100] = { 0 };
    int i = 0;
    int audio_value = 0;

    //debug//LCD_Printf("%s\n", filename);

    // Between A and Z (65 to 91)
    // Between a and z (97 to 122)
    // Character '_'
    while((filename[i] > 64 && filename[i] < 91) || filename[i] == '_' || (filename[i] > 96 && filename[i] < 123))
    {
    	//debug//LCD_Printf("[%c,%d]", filename[i], i);
        big_array[i] = filename[i];
        i++;
    }
    big_array[i] = '.';
    big_array[i+1] = 'w';
    big_array[i+2] = 'a';
    big_array[i+3] = 'v';

    //debug//LCD_Printf("%s\n", big_array);

	// Set the volume of sound
	AUDIO_SetVolume(100);

	audio_value = AUDIO_PlayFile(big_array);

	while(AUDIO_IsPlaybackDone(audio_value) == 0) {}

	AUDIO_StopPlayback(audio_value);
}

