//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
#include <ncurses.h>
#include <stdlib.h> // for srand, rand
#include <time.h>   // for time, nanosleep
#include "blocks.h" // for block 
#include "player.h"  // for player definitions and functions
#include "map.h"     // for map definitions and functions
#include "main.h"


int main() {
    initscr(); start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK); init_pair(2, COLOR_CYAN, COLOR_BLACK);
    cbreak(); noecho(); curs_set(0); // Setup ncurses

    startScreen();
    WINDOW *game_win = newwin(30, 80, 0, 0); WINDOW *message_win = newwin(5, 80, 30, 0);
    displayInstructions(message_win); 
    keypad(game_win, TRUE); nodelay(game_win, TRUE); // Non-blocking input

    int frame_delay = 50; // Milliseconds to delay each frame for game responsiveness
    timeout(frame_delay); // Set how long getch waits for input

    game_loop(game_win, message_win);

 
    // Cleanup and exit
    delwin(game_win); delwin(message_win); endwin();
    return 0;
}



// struct timespec get_mode_delay(int mode) {
//     int delay_ms = mode == 0 ? EASY_MODE_DELAY_MS : HARD_MODE_DELAY_MS;
//     struct timespec ts = { .tv_sec = delay_ms / 1000, .tv_nsec = (delay_ms % 1000) * 1000000L };
//     return ts;
// }
