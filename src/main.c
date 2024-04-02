// main.c
// Use the ncurses library for input handling and screen refreshing.

#include <ncurses.h>
#include "player.h" // Make sure to include this

void startScreen();
void game_loop(WINDOW *game_win, WINDOW *message_win);


int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE); // Enable function keys

    // Create windows for the game and instructions
    WINDOW *game_win = newwin(30, 80, 0, 0);
    WINDOW *message_win = newwin(5, 80, 30, 0); // Adjusted for messages
    keypad(game_win, TRUE);

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
