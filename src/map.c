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

// Function declarations
struct timespec get_mode_delay(int mode) {
    int delay_ms = mode == 0 ? EASY_MODE_DELAY_MS : HARD_MODE_DELAY_MS;
    struct timespec ts = { .tv_sec = delay_ms / 1000, .tv_nsec = (delay_ms % 1000) * 1000000L };
    return ts;
}


void startScreen() {
    // Start color functionality
    start_color();
    init_pair(3, COLOR_RED, COLOR_BLACK);

    // Calculate the position to center the title "SKYFALL"
    const char *title = "SKYFALL";
    const char *prompt = "Press any key to start";
    int title_len = strlen(title);
    int prompt_len = strlen(prompt);
    int title_x = (SCREEN_WIDTH - title_len) / 2;
    int title_y = SCREEN_HEIGHT / 2 - 1; // Position the title one line above the center

    // Calculate the position to place the prompt right below "SKYFALL"
    int prompt_x = (SCREEN_WIDTH - prompt_len) / 2;
    int prompt_y = SCREEN_HEIGHT / 2; // Center line

    // Clear the screen
    clear();

    // Set the color and print "SKYFALL" in red, bold
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(title_y, title_x, "%s", title);
    attroff(COLOR_PAIR(3) | A_BOLD);

    // Print "Press any key to start" right below "SKYFALL"
    mvprintw(prompt_y, prompt_x, "%s", prompt);

    // Refresh the screen to show the text
    refresh();

    // Wait for any key press to continue
    getch();
}


void displayInstructions(WINDOW *win) {
    werase(win); // Clear previous instructions

    // Draw the borders and print instructions
    box(win, '|', '-'); // Draw box borders
    mvwprintw(win, 1, 1, "Instructions:Dodge the blocks to survive.'P'= pause,'q'= quit");
    wrefresh(win); // Refresh to show instructions
}


void display_level(WINDOW *win, int level) {
    // Clear the window before drawing
    werase(win);

    // Activate color pair 1 for blue borders
    wattron(win, COLOR_PAIR(1));
    // Draw the level boundaries with '*', using color pair 1
    box(win, '*', '*'); // Draw box borders with '*'
    wattroff(win, COLOR_PAIR(1)); // Deactivate color pair 1

    // Activate color pair 2 for the light blue bottom border
    wattron(win, COLOR_PAIR(2));
    // Draw the bottom line in light blue
    mvwhline(win, 29, 1, '*', 78); // Assuming the window height is 30
    wattroff(win, COLOR_PAIR(2)); // Deactivate color pair 2

    // Refresh the window to display the new content
    wrefresh(win);
}


void game_loop(WINDOW *game_win, WINDOW *message_win) {

    srand(time(NULL)); // Seed RNG
    initialize_blocks(); // Setup blocks
    Player player; initPlayer(&player); // Initialize player

    int mode = 0; time_t start_time = time(NULL); // Game mode setup


    // display_level(game_win, level); // Display the initial level
    drawPlayer(game_win, &player); // Draw the player on the game window
    displayInstructions(message_win); // Display instructions in the message window

    while (1) {
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

            switch (ch) {
                case 'p':
                    werase(message_win);
                    mvwprintw(message_win, 1, 1, "Game is paused. Press 'P' to continue playing the game.\t");
                    wrefresh(message_win);
                    while(1){
                        ch = wgetch(message_win); // Wait for p or P
                        if (ch == 'p' || ch == 'P') break;
                    } 

                    werase(message_win); // Clear the quit message
                    displayInstructions(message_win); // Redisplay instructions
                    wrefresh(message_win);
                    break;
                // Handle other inputs (e.g., movement, quit)
                case 'q':
                case 'Q':
                    // Implement quit confirmation here
                    break;
                // Handle movement inputs
                default:
                    // Update game state
                    break;
            }
            // display_level(game_win, level); // May need adjustments to avoid overwriting the player
            drawPlayer(game_win, &player);
            // Refresh the game window to show any updates
            wrefresh(game_win);
        }
    }



