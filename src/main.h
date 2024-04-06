#ifndef MAIN_H
#define MAIN_H

#include <time.h> // Include necessary for struct timespec

/*
Constants for the game delay mechanics in different modes and game mode switch timing
*/
#define EASY_MODE_DELAY_MS 120
#define HARD_MODE_DELAY_MS 60
#define HARD_MODE_START 60

/*
 Function prototype for getting the delay time based on the current game mode
*/

struct timespec get_mode_delay(int mode);

#endif
