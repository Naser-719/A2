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

#define PLAYER_WIDTH 2.5
#define PLAYER_HEIGHT 2.5

// Function prototypes
struct timespec get_mode_delay(int mode);

int main() {
    initscr(); start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK); init_pair(2, COLOR_CYAN, COLOR_BLACK);
    cbreak(); noecho(); curs_set(0); // Setup ncurses
    WINDOW *game_win = newwin(30, 80, 0, 0); WINDOW *message_win = newwin(5, 80, 30, 0);
    keypad(game_win, TRUE); nodelay(game_win, TRUE); // Non-blocking input

    srand(time(NULL)); // Seed RNG
    initialize_blocks(); // Setup blocks
    Player player; initPlayer(&player); // Initialize player

    startScreen(); displayInstructions(message_win); // Show start screen and instructions
    int mode = 0; time_t start_time = time(NULL); // Game mode setup

    int frame_delay = 50; // Milliseconds to delay each frame for game responsiveness
    timeout(frame_delay); // Set how long getch waits for input

    bool game_running = true;
    while (game_running) {
        if (difftime(time(NULL), start_time) >= HARD_MODE_START && mode == 0) {
            mode = 1; display_level(game_win, 2); // Switch to hard mode
        }
        spawn_new_block(); update_blocks_position(); // Update blocks

        if (check_collision_with_player(player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT)) {
            break; // End game on collision
        }

        werase(game_win); display_level(game_win, mode + 1);
        drawPlayer(game_win, &player); render_blocks(game_win); wrefresh(game_win); // Draw state

        mvwprintw(message_win, 1, 1, "Current Mode: %s", mode == 0 ? "Easy" : "Hard");
        wrefresh(message_win);

        struct timespec ts = get_mode_delay(mode); nanosleep(&ts, NULL); // Delay based on mode

        int ch = wgetch(game_win); // Non-blocking input read
        if (ch == 'q' || ch == 'Q'){
            // Ask if the user really wants to quit
                werase(message_win);
                mvwprintw(message_win, 1, 1, "Do you want to quit? (y/n) ");
                wrefresh(message_win);
                do {
                    ch = wgetch(message_win); // Wait for 'y' or 'n'
                } while (ch != 'y' && ch != 'n');

                if (ch == 'y') {
                    return; // Exit the loop and end the game
                } else {
                    werase(message_win); // Clear the quit message
                    displayInstructions(message_win); // Redisplay instructions
                }

        }

        else if (ch != ERR) { // If input was received
            int deltaX = 0, deltaY = 0;
            switch(ch) {
                case KEY_LEFT: deltaX = -1; break;
                case KEY_RIGHT: deltaX = 1; break;
                case KEY_UP: deltaY = -1; break;
                case KEY_DOWN: deltaY = 1; break;
            }
            movePlayer(&player, deltaX, deltaY); // Move player based on input
        }
    }

    // Cleanup and exit
    delwin(game_win); delwin(message_win); endwin();
    return 0;
}

struct timespec get_mode_delay(int mode) {
    int delay_ms = mode == 0 ? EASY_MODE_DELAY_MS : HARD_MODE_DELAY_MS;
    struct timespec ts = { .tv_sec = delay_ms / 1000, .tv_nsec = (delay_ms % 1000) * 1000000L };
    return ts;
}
