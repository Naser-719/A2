// main.c
// Use the ncurses library for input handling and screen refreshing.

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
    while ((ch = getch()) != 'd') { // Read input from keyboard (blocking call)
        switch (ch) {
            case KEY_LEFT: // If left arrow key is pressed
                movePlayer(&player, -1);
                break;
            case KEY_RIGHT: // If right arrow key is pressed
                movePlayer(&player, 1);
                break;
        }
        drawPlayer(&player); // Draw the player at the new position
        refresh(); // Refresh the screen to show updates
    }

    // End ncurses mode
    endwin();

    return 0;
}
