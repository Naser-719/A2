#include <ncurses.h>
#include <stdlib.h> // for srand, rand
#include <time.h>   // for time, nanosleep
#include "blocks.h" // for block and leaderboard definitions
#include "leaderboard.h"
#include "player.h"  // for player definitions and functions
#include "map.h"     // for map definitions and functions

#define EASY_MODE_DELAY_MS 120
#define HARD_MODE_DELAY_MS 60
#define HARD_MODE_START 60 // Time in seconds to switch to hard mode

// Function prototypes
struct timespec get_mode_delay(int mode);

int main() {
    // Initialize ncurses
    initscr();
    start_color(); // Initialize color support
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    cbreak();
    noecho();
    curs_set(0); // Hide cursor

    // Set up game and message windows
    WINDOW *game_win = newwin(30, 80, 0, 0); // Game window
    WINDOW *message_win = newwin(5, 80, 30, 0); // Message window below game window
    keypad(game_win, TRUE); // Enable keypad for the game window to capture input

    // Seed the random number generator
    srand(time(NULL));

    // Initialize game state
    initialize_blocks();
    Player player;
    initPlayer(&player); // Initialize the player

    // Display the start screen and instructions
    startScreen();
    displayInstructions(message_win);

    // Draw initial game level
    display_level(game_win, 1); // Start at level 1

    int mode = 0; // Start in easy mode
    time_t start_time = time(NULL);

    // Main game loop
    while (true) {
        // Check and update the game mode based on elapsed time
        if (difftime(time(NULL), start_time) >= HARD_MODE_START && mode == 0) {
            mode = 1; // Switch to hard mode
            display_level(game_win, 2); // Update the display to indicate a new level (hard mode)
        }

        // Spawn new blocks and update their positions
        spawn_new_block();
        update_blocks_position();

        // Draw updated game state
        werase(game_win); // Clear game window for the new frame
        display_level(game_win, mode + 1); // Redraw level with borders
        drawPlayer(game_win, &player); // Draw the player
        render_blocks(game_win); // Draw the blocks
        wrefresh(game_win); // Refresh the game window to display the new frame

        // Optionally, update and refresh the message window
        mvwprintw(message_win, 1, 1, "Current Mode: %s", mode == 0 ? "Easy" : "Hard");
        wrefresh(message_win);

        // Delay based on the current mode
        struct timespec ts = get_mode_delay(mode);
        nanosleep(&ts, NULL);

        // Handle user input for movement and game control
        int ch = wgetch(game_win);
        int deltaX = 0, deltaY = 0;
        switch(ch) {
            case KEY_LEFT:
                deltaX = -1;
                break;
            case KEY_RIGHT:
                deltaX = 1;
                break;
            case KEY_UP:
                deltaY = -1;
                break;
            case KEY_DOWN:
                deltaY = 1;
                break;
            case 'q':
            case 'Q':
                goto cleanup_and_exit; // Use goto for exiting from nested loops or conditionals
        }
        if (deltaX != 0 || deltaY != 0) {
            movePlayer(&player, deltaX, deltaY);
        }

        // The rest of the game loop code...
    }

cleanup_and_exit:
    // Cleanup and exit
    delwin(game_win);
    delwin(message_win);
    endwin();
    return 0;
}

struct timespec get_mode_delay(int mode) {
    int delay_ms = mode == 0 ? EASY_MODE_DELAY_MS : HARD_MODE_DELAY_MS;
    struct timespec ts;
    ts.tv_sec = delay_ms / 1000;
    ts.tv_nsec = (delay_ms % 1000) * 1000000L; // Convert to nanoseconds
    return ts;
}
