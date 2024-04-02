#include "blocks.h"
#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000 // Delay between moves (in microseconds)

int main() {
    int ch;

    // Initialize ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); // Enable keyboard input
    timeout(0);           // Non-blocking input
    curs_set(0);          // Hide the cursor

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the blocks
    initialize_blocks();

    // Main game loop
    while (true) {
        // Create a block for testing purposes
        // In a real game, you'd have logic to determine when to create blocks
        create_block(0, 3, 1, 1);

        // Update blocks' position
        update_blocks_position();

        // Clear the screen
        clear();

        // Render blocks
        render_blocks(stdscr);

        // Refresh to draw everything on the screen
        refresh();

        // Check for user input
        ch = getch();
        if (ch == 'q') { // Quit the game if 'q' is pressed
            break;
        }

        // Delay before the next loop iteration
        usleep(DELAY);
    }

    // End ncurses
    endwin();

    return 0;
}
