//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
#ifndef MAP_H
#define MAP_H

extern int best_time;

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>
#include "player.h"
#include "map.h"
#include "blocks.h"

#define EASY_MODE_DELAY_MS 120
#define HARD_MODE_DELAY_MS 60
#define HARD_MODE_START 60 
#define POWERUP_TIME 20

// Initializes the start screen of the game
void startScreen();

int load_best_time();

// Displays the game instructions in the specified window
void displayInstructions(WINDOW *win, char power_up);

// The main loop of the game, handling game logic and user input
void game_loop(WINDOW *game_win, WINDOW *message_win);

// 
void display_window(WINDOW *win);

bool quit_game(int ch, WINDOW *message_win);

void pause_game(int ch, WINDOW *message_win);

// In map.h or a suitable header file



#endif // MAP_H

