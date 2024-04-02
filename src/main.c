// main.c
// Use the ncurses library for input handling and screen refreshing.

#include <ncurses.h>
#include "player.h" // Make sure to include this

void startScreen();
void game_loop(WINDOW *game_win, WINDOW *message_win);


// Assume the rest of your necessary includes and function declarations are here

int main() {
    // Initialize ncurses
    initscr();
    start_color(); // Initialize color support
    
    // Define color pairs
    init_pair(1, COLOR_BLUE, COLOR_BLACK); // Pair 1: Blue foreground, Black background
    init_pair(2, COLOR_CYAN, COLOR_BLACK); // Pair 2: Cyan (light blue) foreground, Black background

    cbreak();
    noecho();
    keypad(stdscr, TRUE); // Enable keypad for the standard screen, to capture function keys, etc.

    // Create windows for the game and messages
    WINDOW *game_win = newwin(30, 80, 0, 0);
    WINDOW *message_win = newwin(5, 80, 30, 0); // Positioned below the game window
    keypad(game_win, TRUE); // Enable keypad for the game window

    // Begin the game
    startScreen();
    game_loop(game_win, message_win);

    // Cleanup
    delwin(game_win);
    delwin(message_win);
    endwin();

    return 0;
}

/*
#include "player.h"
#include <ncurses.h>
#include <stdlib.h>

int main() {
    Player player;
    int ch;

    // Initialize ncurses mode
    initscr();
    cbreak(); // Disable line buffering
    noecho(); // Do not echo input characters
    keypad(stdscr, TRUE); // Enable special keys to be captured

    // Initialize the player
    initPlayer(&player);

    // Main game loop
    while ((ch = getch()) != 'd') { // Read input from keyboard (blocking call), use 'd' to quit
        switch (ch) {
            case KEY_LEFT: // If left arrow key is pressed
                movePlayer(&player, -1, 0); // Move left without changing vertical position
                break;
            case KEY_RIGHT: // If right arrow key is pressed
                movePlayer(&player, 1, 0); // Move right without changing vertical position
                break;
            case KEY_UP: // If up arrow key is pressed
                movePlayer(&player, 0, -1); // Move up without changing horizontal position
                break;
            case KEY_DOWN: // If down arrow key is pressed
                movePlayer(&player, 0, 1); // Move down without changing horizontal position
                break;
        }
        drawPlayer(&player); // Draw the player at the new position
        refresh(); // Refresh the screen to show updates
    }

    // End ncurses mode
    endwin();

    return 0;
}
*/
