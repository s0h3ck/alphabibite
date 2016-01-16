/**
 * K3P16 © Copyright 2015
 * Date : 25/11/2015
 *
 * File's name: alphabetic.cpp
 */

#include "alphabetic.h"

/**
 * Description: Initialize an array of 26 letter. Guess what? It's the array of the alphabet from A to Z
 * Return: nothing (KISS)
 */
static void initialize_alpha(char *alpha)
{
    int i = 0;

    for(i = 0; i < 26; i++)
    {
        alpha[i] = (char)(i + 65);
    }
}

/**
 * Description: Return a random letter between A and Z (inclusive)
 * Return: Character (char) from A to Z
 */
char ask_alpha(void)
{
    char alpha[26] = { 0 };

    // Add alphabet from A to Z
    initialize_alpha(alpha);

    // Return a random alpha
    return alpha[rand() % 26];
}

/**
 * Description: Spin alpha means print the letter you wants and three random letters.
 * Parameters:
 * 	character_wanted: The character you want you trust
 * 	number: the number of alphabet you want to print
 * 			(value between 1 and 26 included)
 * Return: 1 on successful operation
 * 		  -1 on error
 */
int spin_alpha(char character_wanted, int number)
{
    int position_alpha = 0;
    int i = 0;
	int j = 0;
    int index = 0;
    int new_alpha = 1;
    int array_length = 0;
    char array_of_alpha[26] = { 0 };

    if (number < 1 || number > 4)
    {
        printf("Error: Number should be between 1 and 4.\n");
        return -1;
    }

	position_alpha = rand() % number; // genere la position de la vrai lettre
	array_of_alpha[0] = character_wanted;
	array_length += 1;

	// less than 4
    for(i = 0; i < number; i++)
    {
    	switch(i)
    	{
    	case 0:
    		LCD_Printf("%15c", ' ');
    		break;
    	case 1:
    		LCD_Printf("\n ");
    		break;
    	case 2:
    		LCD_Printf("%28c", ' ');
    		break;
    	case 3:
    		LCD_Printf("\n%15c", ' ');
    		break;
    	}

    	if( i == position_alpha )
        {
			LCD_Printf("%c", character_wanted);
        }
        else
        {
        	while(new_alpha)
        	{
                new_alpha = 1;
                index = rand() % ALPHABET_COUNT;
        		for(j = 0; j < array_length ; j++)
        		{
        			if(array_of_alpha[j] == (char)(index+65))
        			{
        				new_alpha = 0;
        			}
        		}
        		if(new_alpha)
        		{
        			array_of_alpha[array_length] = (char)(index+65);
        			LCD_Printf("%c", array_of_alpha[array_length]);
        			array_length += 1;
        			break;
        		}
        		new_alpha = 1;
        	}
        }
    }
    LCD_Printf("\n\n");
    return position_alpha;
}


/**
 * Description: Play a word
 * Return: 1 on successful operation
 * 		  -1 on error
 */
int play_mode_two(void)
{
    char word[100];
    char action[100];
	char letter = 0;
	char temp = ' ';

	int i = 0, j = 0;
	int position_alpha = 0;

	// The list
	FILE *file = NULL;
	file = fopen("/media/sd0/list.txt", "r");

	letter = ask_alpha();

	if (file == NULL)
	{
		LCD_Printf("Error: The file is corrupted.");
		return 0;
	}
	else
	{
		// Read the word and the action
		while(2 == fscanf(file, "%80s%*[ \n\t]%80s", word, action))
		{
			if (letter == word[0])
			{
				//LCD_Printf("The word is %s.", word);
				//THREAD_MSleep(3000);
				break;
			}
		}
	}

	i = 0;
	while(1)
	{
		//LCD_ClearAndPrint(" ----Trouver la lettre [%c]----\n\n", word[i]);
		LCD_ClearAndPrint("  ---- Trouver la lettre ----  \n\n");

		// Print
		position_alpha = spin_alpha(word[i], 4);
		// Find the good alpha
		LCD_Printf("Appuyer sur le bon pare-choc!\n");

		if( i != 0)
		{
			LCD_Printf("Assemblage du mot : ");
			for(j = 0; j < i; j++)
			{
				temp = *(word+j);
				LCD_Printf("%c", temp);
				// play_sound(&temp); // bug unsolved

			}
		}
		play_sound(word);

		while(1)
		{
			if(DIGITALIO_Read(BMP_FRONT) == 1)
			{
				if(0 == position_alpha)
				{
					break;
				}
				return -1;
			}

			if(DIGITALIO_Read(BMP_REAR) == 1)
			{
				if(3 == position_alpha)
				{
					break;
				}
				return -1;
			}

			if(DIGITALIO_Read(BMP_LEFT) == 1)
			{
				if(1 == position_alpha)
				{
					break;
				}
				return -1;
			}

			if(DIGITALIO_Read(BMP_RIGHT) == 1)
			{
				if(2 == position_alpha)
				{
					break;
				}
				return -1;
			}
		}

		i++;

		letter = toupper(word[i]);
		if (!((word[i] > 64 && word[i] < 91) || (word[i] > 96 && word[i] < 123)))
		{
			break;
		}
	}

	// The user find the word
	LCD_ClearAndPrint("Felicitation!\n");
	LCD_Printf("Le mot etait ");
	play_sound((char*)"felicitation");
	LCD_Printf("%s!\n", word);
	play_sound(word);
	//debug//LCD_Printf("\n\n\n%s!", action);
	play_sound(action);

	if (strcmp(action, "JOIE") == 0)
	{
		happy();
	}
	if (strcmp(action, "PEUR") == 0)
	{
		fear();
	}
	if (strcmp(action, "COLERE") == 0)
	{
		angry();
	}
	if (strcmp(action, "TRISTE") == 0)
	{
		sad();
	}
	if (strcmp(action, "MIAM") == 0)
	{
		miam();
	}
	MOTOR_SetSpeed(7,0);
	MOTOR_SetSpeed(8 ,0);
	THREAD_MSleep(3000);
	return 1;
}
