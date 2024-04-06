//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
#include <ncurses.h>
#include <stdlib.h> 
#include <time.h> 
#include "blocks.h" 
#include "player.h"  
#include "map.h"     



int main() {
    initscr(); start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK); init_pair(2, COLOR_CYAN, COLOR_BLACK);
    cbreak(); noecho(); curs_set(0); // Setup ncurses

    startScreen();
    WINDOW *game_win = newwin(30, 80, 0, 0); WINDOW *message_win = newwin(5, 80, 30, 0);
    displayInstructions(message_win, 0); 
    keypad(game_win, TRUE); nodelay(game_win, TRUE); // Non-blocking input

    int frame_delay = 50; // Milliseconds to delay each frame for game responsiveness
    timeout(frame_delay); // Set how long getch waits for input

    game_loop(game_win, message_win);

 
    // Cleanup and exit
    delwin(game_win); delwin(message_win); endwin();
    return 0;
}

