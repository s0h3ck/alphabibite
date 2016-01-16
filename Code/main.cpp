/**
 * K3P16 © Copyright 2015
 * Date : 25/11/2015
 *
 * File's name: main.cpp
 */

#include "alphabetic.h"
#include "movements.h"
#include "sounds.h"

// Constants for the button
#define GREEN_BUTTON 6
#define GREEN_LIGHT 11

#define BLUE_BUTTON 7
#define BLUE_LIGHT 10

#define RED_BUTTON 8
#define RED_LIGHT 12

#define ANTENNA_1 14
#define ANTENNA_2 15

#define ON 1
#define OFF 0

#define DELAY_SONG 30

int main()
{
	// Declarations of variables
    int mode = 1;
    int i = 0;
    int t = 0;
    int position_alpha = 0;
    int bumper_value = 0;
    int mode1 = 0;
    int mode2 = 0;
    int k = 0;

    char letter = 0;
    char emergency_letter[1];

    const char *bumper_names[4] = {"Avant", "Gauche", "Droite", "Arriere"};

    // Seed for random number
    srand((unsigned)time(NULL));

    LCD_SetMonitorMode(MONITOR_OFF);

    //LCD_PrintBmp(smallfontdata);

    //LCD_PrintBmp("coccinelle.bmp");
    //THREAD_MSleep(2000);


    for (k = 15; k > 0; k--)
    {
    	LCD_Printf("%d\n", k);
    	THREAD_MSleep(1000);
    }
    // Voice at the beginning (presentation of himself)
    SYSTEM_ResetTimer();
    LCD_ClearAndPrint("Bonjour les amis!\n");
    LCD_Printf("Je m'appel ALPHABIBITE!\n");

    play_sound((char *)"bonjour");

	// Game structure
	while(1)
	{
		DIGITALIO_Write(ANTENNA_1, ON);


		if ((int)(SYSTEM_ReadTimerMSeconds() / 1000) > ((int)(DELAY_SONG/2) * t))
		{
			t += 1;
			LCD_ClearAndPrint("Appuyer sur le bouton vert!\n");
			play_sound((char *)"boutonvert");
		}


		if ((int)(SYSTEM_ReadTimerMSeconds() / 1000) > DELAY_SONG)
		{
			THREAD_MSleep(1000);
			play_sound((char*)"chanteavecmoi");
			LCD_ClearAndPrint("Chante avec moi!\n\n");
			LCD_Printf("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
			play_sound((char *)"alphabet");
			SYSTEM_ResetTimer();
			t = 0;
		}
		else
		{
			//LCD_Printf("%d - %d\n", (int)(SYSTEM_ReadTimerMSeconds() / 1000), DELAY_SONG);
			THREAD_MSleep(500);
		}

		// Mode 0 - Enter in the game
		while (ANALOG_Read(GREEN_BUTTON) > 1000)
		{
			t = 0;
			SYSTEM_ResetTimer();
			DIGITALIO_Write(ANTENNA_1, ON);
			DIGITALIO_Write(GREEN_LIGHT, ON);

			while (ANALOG_Read (BLUE_BUTTON) > 1000 && ANALOG_Read (RED_BUTTON) > 1000)
			{
				LCD_ClearAndPrint("Bouton bleu ou bouton rouge!");
				DIGITALIO_Write(BLUE_LIGHT, ON);
				DIGITALIO_Write(RED_LIGHT, ON);
				play_sound((char *)"collision");
				THREAD_MSleep(1000);
			}
			DIGITALIO_Write(BLUE_LIGHT, OFF);
			DIGITALIO_Write(RED_LIGHT, OFF);

			if (ANALOG_Read (BLUE_BUTTON) < 1000 && ANALOG_Read (RED_BUTTON) < 1000)
			{
			LCD_ClearAndPrint("Veuillez choisir un mode!\n");
				if (ANALOG_Read (BLUE_BUTTON) < 1000 && ANALOG_Read (RED_BUTTON) < 1000)
				{
				LCD_Printf("Mode 1: Jouez avec les lettres :)\n");
				play_sound((char *)"boutonbleu");
				THREAD_MSleep(1000);
					if(ANALOG_Read (BLUE_BUTTON) < 1000 && ANALOG_Read (RED_BUTTON) < 1000)
					{
						LCD_Printf("Mode 2: Jouez avec les mots :)\n");
						play_sound((char *)"boutonrouge");

						if (ANALOG_Read (BLUE_BUTTON) < 1000 && ANALOG_Read (RED_BUTTON) < 1000)
						{
							LCD_Printf("Fermer: Bouton vert et merci :D\n");
							play_sound((char*)"quittervert");
							THREAD_MSleep(2000);
						}
					}
				}
			}

			mode1 = 1;
			// -=-=-=-=-=-=-=-=-=- Mode 1 -=-=-=-=-=-=-=-=-=-=-
			while (ANALOG_Read (BLUE_BUTTON) > 1000)
			{
				DIGITALIO_Write(ANTENNA_1, OFF);
				DIGITALIO_Write(BLUE_LIGHT, ON);

				SYSTEM_ResetTimer();

				THREAD_MSleep(250);
				if (ANALOG_Read (BLUE_BUTTON) > 1000 && ANALOG_Read (RED_BUTTON) > 1000)
				{
					LCD_ClearAndPrint("Bouton bleu ou bouton rouge!");
					DIGITALIO_Write(BLUE_LIGHT, ON);
					DIGITALIO_Write(RED_LIGHT, ON);
					play_sound((char *)"collision");
					break;
				}


				if (mode1)
				{
					mode1 = 0;
					LCD_ClearAndPrint("Bienvenue dans le mode 1\n");
					play_sound((char *)"bienvenuemodeun");
					THREAD_MSleep(500);
					play_sound((char*)"quitterbleu");
					THREAD_MSleep(1000);
					if (ANALOG_Read (BLUE_BUTTON) < 1000)
					{
						break;
					}
					play_sound((char *)"drescriptionmodeun");
					THREAD_MSleep(500);
				}

				// Ask an alpha
				letter = ask_alpha();
				//LCD_ClearAndPrint(" ----Trouver la lettre [%c]----\n\n", letter);
				LCD_ClearAndPrint("  ---- Trouver la lettre ----  \n\n");
				play_sound(&letter);
				puts("\n");

				// Print one alpha and three fake number
				position_alpha = spin_alpha(letter, 4);
				// Find the good alpha
				LCD_Printf("Appuyer sur le bon pare-choc!\n");
				play_sound((char *)"appuyerparechoc");
				//debug//LCD_Printf("Le bon pare-choc est %s.\n", bumper_names[position_alpha]);

				while(1)
				{
					if(DIGITALIO_Read(BMP_FRONT) == 1)
					{
						if(0 == position_alpha)
						{
							state_win();
							break;
						}
						else
						{
							state_lose();
							break;
						}
					}

					if(DIGITALIO_Read(BMP_REAR) == 1)
					{
						if(3 == position_alpha)
						{
							state_win();
							break;
						}
						else
						{
							state_lose();
							break;
						}
					}

					if(DIGITALIO_Read(BMP_LEFT) == 1)
					{
						if(1 == position_alpha)
						{
							state_win();
							break;
						}
						else
						{
							state_lose();
							break;
						}
					}

					if(DIGITALIO_Read(BMP_RIGHT) == 1)
					{
						if(2 == position_alpha)
						{
							state_win();
							break;
						}
						else
						{
							state_lose();
							break;
						}
					}
				}
			}

			// Red button turn off
			DIGITALIO_Write(BLUE_LIGHT, OFF);

			mode2 = 1;
			// -=-=-=-=-=-=-=-=-=- Mode 2 -=-=-=-=-=-=-=-=-=-=-
			while (ANALOG_Read (RED_BUTTON) > 1000)
			{
				DIGITALIO_Write(ANTENNA_1, OFF);
				DIGITALIO_Write(RED_LIGHT, ON);

				SYSTEM_ResetTimer();
				THREAD_MSleep(250);
				if (ANALOG_Read (BLUE_BUTTON) > 1000 && ANALOG_Read (RED_BUTTON) > 1000)
				{
					LCD_ClearAndPrint("Bouton bleu ou bouton rouge!");
					DIGITALIO_Write(BLUE_LIGHT, ON);
					DIGITALIO_Write(RED_LIGHT, ON);
					play_sound((char *)"collision");
					break;
				}

				if(mode2)
				{
					mode2 = 0;
					LCD_ClearAndPrint("Bienvenue dans le mode 2\n");
					play_sound((char *)"bienvenuemodedeux");
					THREAD_MSleep(500);
					play_sound((char*)"quitterrouge");
					THREAD_MSleep(500);
					if (ANALOG_Read (RED_BUTTON) < 1000)
					{
						break;
					}
					play_sound((char *)"drescriptionmodedeux");
					THREAD_MSleep(500);
				}

				if(play_mode_two() == -1)
				{
					LCD_ClearAndPrint("Tu as perdu!\n");
					THREAD_MSleep(250);
					LCD_Printf("Aller on ressaie!\n");
					play_sound((char*)"reessaie");
					THREAD_MSleep(1500);
				}

			}
			// Red button turn off
			DIGITALIO_Write(RED_LIGHT, OFF);
		}

		if(DIGITALIO_Read(GREEN_LIGHT))
		{
			play_sound((char *)"merci");
		}

		// Green button turn off
		DIGITALIO_Write(GREEN_LIGHT, OFF);
		THREAD_MSleep(1000);
	}
}

