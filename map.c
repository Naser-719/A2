#include <ncurses.h>
#include <stdbool.h>

// Function declarations
void startScreen();
void displayInstructions(WINDOW *win);
void game_loop(WINDOW *game_win, WINDOW *message_win);
void display_level(WINDOW *win, int level);

void startScreen() {
    clear();
    printw("Press any key to start...\n");
    refresh();
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
    mvwprintw(win, 1, 1, "Instructions: Dodge the blocks to survive.");
    wrefresh(win); // Refresh to show instructions
}

void display_level(WINDOW *win, int level) {
    werase(win); // Clear the window
    
    // Draw the level boundaries with '*'
    box(win, '*', '*'); // Use '*' for the box borders
    
    // Optionally, add level-specific objects here
    
    wrefresh(win); // Refresh the window to display the new content
}

void game_loop(WINDOW *game_win, WINDOW *message_win) {
    int ch;
    bool paused = false;
    int level = 1; // Starting level

    display_level(game_win, level); // Display the initial level
    displayInstructions(message_win); // Display instructions in the message window

    while (1) {
        if (paused) {
            mvwprintw(message_win, 2, 2, "Game is paused. Press 'p' to continue.");
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
