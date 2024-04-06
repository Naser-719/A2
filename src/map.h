#ifndef MAP_H
#define MAP_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>
#include "player.h"
#include "blocks.h"

#define EASY_MODE_DELAY_MS 120 ///< Delay in milliseconds for easy mode.
#define HARD_MODE_DELAY_MS 60 ///< Delay in milliseconds for hard mode.
#define HARD_MODE_START 60 ///< Time in seconds when the game switches to hard mode.
#define POWERUP_TIME 20 ///< Duration in seconds for power-ups.

extern int best_time; ///< Stores the best time achieved across game sessions.

/**
 * Initializes and displays the start screen of the game.
 * The start screen includes the game title and a prompt to start the game.
 */
void startScreen();

/**
 * Loads the best time from a file.
 * @return The best time loaded from the file or -1 if the file doesn't exist or can't be opened.
 */
int load_best_time();

/**
 * Displays the game instructions in the specified window.
 * Instructions vary depending on the current power-up status.
 * 
 * @param win The window where the instructions will be displayed.
 * @param power_up The current power-up character indicating the state ('i' for immunity, 's' for slow mode, etc.).
 */
void displayInstructions(WINDOW *win, char power_up);

/**
 * The main loop of the game, handling game logic, user input, and rendering.
 * This function is the core of the game's execution, managing game states and interactions.
 * 
 * @param game_win The main game window where the gameplay is displayed.
 * @param message_win The window for displaying messages and instructions to the player.
 */
void game_loop(WINDOW *game_win, WINDOW *message_win);

/**
 * Displays the game window, including the borders and any necessary UI components.
 * This function refreshes the game window, updating any changes to the display.
 * 
 * @param win The game window to be displayed and refreshed.
 */
void display_window(WINDOW *win);

/**
 * Handles the logic for quitting the game based on user input.
 * If the user chooses to quit, this function updates the game state accordingly.
 * 
 * @param ch The character input by the user, used to determine if quitting was requested.
 * @param message_win The window where the quit confirmation message is displayed.
 * @return Returns true if the user confirms to quit the game, otherwise false.
 */
bool quit_game(int ch, WINDOW *message_win);

/**
 * Pauses the game until the user decides to continue.
 * This function displays a pause message and waits for user input to resume the game.
 * 
 * @param ch The character input by the user, used to pause or resume the game.
 * @param message_win The window where the pause message is displayed.
 */
void pause_game(int ch, WINDOW *message_win);

#endif // MAP_H
