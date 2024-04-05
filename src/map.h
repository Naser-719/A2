//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
#ifndef MAP_H
#define MAP_H

#include <ncurses.h>

// Initializes the start screen of the game
void startScreen();

// Displays the game instructions in the specified window
void displayInstructions(WINDOW *win, char power_up);

// The main loop of the game, handling game logic and user input
void game_loop(WINDOW *game_win, WINDOW *message_win);

// 
void display_window(WINDOW *win);



// In map.h or a suitable header file



#endif // MAP_H

