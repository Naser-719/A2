#include <ncurses.h>
#include <stdlib.h> // For rand(), srand()
#include <string.h> // For strlen()
#include <time.h>   // For time(), difftime()
#include "player.h" // Assumed header for Player functions and structure
#include "blocks.h" // Assumed header for block functions and structure

#define DELAY 30000         // Delay in microseconds
#define GAME_WIDTH 80       // Width of the game area
#define GAME_HEIGHT 30      // Height of the game area



void startScreen() {
    clear();
    printw("Press any key to start...\n");
    refresh();
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
    Player player;
    int ch;
    bool paused = false;
    int level = 1; // Starting level

    initPlayer(&player); // Initialize the player position
    keypad(game_win, TRUE); // Enable keyboard input for game window

    display_level(game_win, level); // Display the initial level
    drawPlayer(game_win, &player); // Draw the player on the game window
    displayInstructions(message_win); // Display instructions in the message window

    while (1) {
        if (paused) {
            // Display paused message
            mvwprintw(message_win, 1, 1, "Game is paused. Press 'P' to continue...");
            wrefresh(message_win);

            // Wait for 'P' to unpause
            do {
                ch = wgetch(game_win);
                if (ch == 'p' || ch == 'P') {
                    paused = false;
                    // Clear the pause message before resuming
                    werase(message_win);
                    displayInstructions(message_win); // Redisplay instructions
                }
            } while (paused);
        } else {
            // Game is not paused, continue with logic
            ch = wgetch(game_win); // Get user input

            switch (ch) {
                case 'p':
                case 'P':
                    paused = true; // Toggle pause state
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

            if (!paused) {
                // Game logic (e.g., updating game state, checking collisions)
                display_level(game_win, level); // Refresh the game window
                drawPlayer(game_win, &player); // Draw the player
                wrefresh(game_win); // Refresh window to show updates
            }
        }
    }
}



/*
void game_loop(WINDOW *game_win, WINDOW *message_win) {
    int ch;
    bool paused = false;
    int level = 1; // Starting level

    display_level(game_win, level); // Display the initial level
    displayInstructions(message_win); // Display instructions in the message window

    while (1) {
        if (paused) {
            mvwprintw(message_win, 1, 1, "Game is paused. Press 'p' to continue.");
            wrefresh(message_win);
            do {
                ch = wgetch(game_win); // Wait for 'p' to unpause
            } while (ch != 'p');
            paused = false;
            werase(message_win); // Clear the pause message
            displayInstructions(message_win); // Redisplay instructions
        } else {
            ch = wgetch(game_win); // Get user input

            if (ch == 'q') {
                // Ask if the user really wants to quit
                werase(message_win);
                mvwprintw(message_win, 1, 1, "Do you want to quit? (y/n) ");
                wrefresh(message_win);
                do {
                    ch = wgetch(message_win); // Wait for 'y' or 'n'
                } while (ch != 'y' && ch != 'n');

                if (ch == 'y') {
                    break; // Exit the loop and end the game
                } else {
                    werase(message_win); // Clear the quit message
                    displayInstructions(message_win); // Redisplay instructions
                }
            } else if (ch == 'p') {
                paused = true; // Pause the game
            }
        }

        // TODO: Add the rest of your game logic here

        // Refresh the game window to show any updates
        wrefresh(game_win);
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE); // Enable function keys

    int rows = 30, cols = 80;
    WINDOW *game_win = newwin(rows, cols, 0, 0);
    WINDOW *message_win = newwin(5, cols, rows, 0); // Adjusted height for instructions

    startScreen();
    game_loop(game_win, message_win);

    delwin(game_win);
    delwin(message_win);
    endwin();

    return 0;
}
*/
