// main.c
// Use the ncurses library for input handling and screen refreshing.
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
