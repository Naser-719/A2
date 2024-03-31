#include <ncurses.h>
#include <stdbool.h>

/* Function declarations */
void startScreen();
void displayInstructions(WINDOW *win);
void game_loop(WINDOW *game_win, WINDOW *message_win);
void display_level(WINDOW *win, int level);

/* Displays the start screen with a prompt for the player to press any key to start the game. */
void startScreen() {
    clear();
    printw("Press any key to start...\n");
    refresh();
    getch();
}

/* 
   Displays game instructions within a specified window.
   This includes drawing a box around the instructions and printing the text inside.
*/
void displayInstructions(WINDOW *win) {
    werase(win);
    box(win, '|', '-');
    mvwprintw(win, 1, 1, "Instructions: Dodge the blocks to survive.");
    wrefresh(win);
}

/* 
   Clears the given window and draws the level layout, including boundaries.
   The level's layout can be customized based on the level number provided.
*/
void display_level(WINDOW *win, int level) {
    werase(win);
    box(win, '*', '*');
    wrefresh(win);
}

/* 
   The main game loop which handles game state, including pausing and quitting.
   It responds to user input for game control (e.g., 'p' to pause, 'q' to quit) and refreshes
   the game window to reflect any changes or player actions.
*/
void game_loop(WINDOW *game_win, WINDOW *message_win) {
    int ch;
    bool paused = false;
    int level = 1;

    display_level(game_win, level);
    displayInstructions(message_win);

    while (1) {
        if (paused) {
            mvwprintw(message_win, 2, 2, "Game is paused. Press 'p' to continue.");
            wrefresh(message_win);
            do {
                ch = wgetch(game_win);
            } while (ch != 'p');
            paused = false;
            werase(message_win);
            displayInstructions(message_win);
        } else {
            ch = wgetch(game_win);

            if (ch == 'q') {
                werase(message_win);
                mvwprintw(message_win, 1, 1, "Do you want to quit? (y/n) ");
                wrefresh(message_win);
                do {
                    ch = wgetch(message_win);
                } while (ch != 'y' && ch != 'n');

                if (ch == 'y') {
                    break;
                } else {
                    werase(message_win);
                    displayInstructions(message_win);
                }
            } else if (ch == 'p') {
                paused = true;
            }
        }
        wrefresh(game_win);
    }
}

/* 
   The main function sets up the ncurses environment, creates windows for the game and instructions,
   runs the game loop, and then cleans up before exiting.
*/
int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int rows = 30, cols = 80;
    WINDOW *game_win = newwin(rows, cols, 0, 0);
    WINDOW *message_win = newwin(5, cols, rows, 0);

    startScreen();
    game_loop(game_win, message_win);

    delwin(game_win);
    delwin(message_win);
    endwin();

    return 0;
}
