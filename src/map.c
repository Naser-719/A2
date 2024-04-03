#include <ncurses.h>
#include <stdbool.h>
#include "player.h"
#include "map.h"
// Function declarations

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
    int start_row = 15; // Start half the height from the top
    int end_row = start_row + 14; // Half the height of the map for the instructions box
    int start_col = 81; // Start right after the map, which is 80 characters wide
    int end_col = 110; // End column of the instructions box

    // Assuming instructions window is separate and has been correctly sized and positioned
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
    keypad(game_win, TRUE); // Make sure this line is here to capture arrow keys


    display_level(game_win, level); // Display the initial level
    drawPlayer(game_win, &player); // Draw the player on the game window
    displayInstructions(message_win); // Display instructions in the message window

    while (1) {
        if (paused) {
           mvwprintw(message_win, 1, 1, "Game is paused. Press 'P' to continue playing the game.\t");
           wrefresh(message_win);
            do {
                ch = wgetch(game_win); // Wait for 'p' to unpause
            } while (ch != 'p');
            paused = false;
            werase(message_win); // Clear the pause message
            displayInstructions(message_win); // Redisplay instructions
        } else {
            ch = wgetch(game_win); // Get user input

            switch(ch) {
                case KEY_LEFT:
                    movePlayer(&player, -1, 0);
                    break;
                case KEY_RIGHT:
                    movePlayer(&player, 1, 0);
                    break;
                case KEY_UP:
                    movePlayer(&player, 0, -1);
                    break;
                case KEY_DOWN:
                    movePlayer(&player, 0, 1);
                    break;
                case 'p':
                    paused = true; // Pause the game
                    break;
                case 'q':
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
                    break;
            }
            display_level(game_win, level); // May need adjustments to avoid overwriting the player
            drawPlayer(game_win, &player);
            // Refresh the game window to show any updates
            wrefresh(game_win);
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
