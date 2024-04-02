#include "blocks.h"
#include <ncurses.h>
#include <stdlib.h> // for srand
#include <time.h>   // for time and nanosleep

#define EASY_MODE_DELAY_MS 120
#define HARD_MODE_DELAY_MS 60
#define HARD_MODE_START 5 // Time in seconds to switch to hard mode

struct timespec get_mode_delay(int mode);

int main() {
    int ch;
    int mode = 0; // Start in easy mode
    time_t start_time = time(NULL);

    // Initialize ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    timeout(0);
    curs_set(0);

    srand(time(NULL));
    initialize_blocks();

    while (true) {
        if (difftime(time(NULL), start_time) >= HARD_MODE_START && mode == 0) {
            mode = 1; // Switch to hard mode
        }

        spawn_new_block();
        update_blocks_position();
        clear();
        render_blocks(stdscr);
        refresh();

        struct timespec ts = get_mode_delay(mode);
        nanosleep(&ts, NULL);

        ch = getch();
        if (ch == 'q') break;
    }

    endwin();
    return 0;
}

struct timespec get_mode_delay(int mode) {
    int delay_ms = mode == 0 ? EASY_MODE_DELAY_MS : HARD_MODE_DELAY_MS;
    struct timespec ts;
    ts.tv_sec = delay_ms / 1000;
    ts.tv_nsec = (delay_ms % 1000) * 1000000L; // Convert milliseconds to nanoseconds
    return ts;
}
