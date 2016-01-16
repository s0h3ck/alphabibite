/**
 * K3P16 © Copyright 2015
 * Date : 25/11/2015
 *
 * File's name: alphabetic.h
 */

#ifndef ALPHABETIC_H_
#define ALPHABETIC_H_

#define ALPHABET_COUNT 26

// Inclusion of ARMus library
#include <libarmus.h>

// Inclusion of standard library
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // need it for pseudo-random number
#include <ctype.h> // toupper function needed
#include "sounds.h"
#include "messages.h"
#include "movements.h"

// Guys, we need comment here!

static void initialize_alpha(char *alpha);
char ask_alpha(void);
int spin_alpha(char character_wanted, int number);
int check_alpha(int bumper_value, int position_alpha);
int play_mode_two(void);

#endif /* ALPHABETIC_H_ */
