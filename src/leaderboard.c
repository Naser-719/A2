#include <ncurses.h>
#include "leaderboard.h"
#include <string.h> 

#define MAX_PLAYERS 5
#define NAME_LENGTH 50


void initializeLeaderboard(Leaderboard *lb) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        lb->players[i].score = 0; // Assuming 0 is the lowest possible score.
        strcpy(lb->players[i].name, "Empty");
    }
}



void updateLeaderboard(Leaderboard *lb, const char* playerName, int playerScore) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (playerScore > lb->players[i].score) {
            // Shift lower scores down one position
            for (int j = MAX_PLAYERS - 1; j > i; j--) {
                lb->players[j] = lb->players[j - 1];
            }
            // Insert the new score
            strcpy(lb->players[i].name, playerName);
            lb->players[i].score = playerScore;
            break;
        }
    }
}




void displayLeaderboard(const Leaderboard *lb) {
    int win_width = 30; // Width of the leaderboard window
    int win_height = MAX_PLAYERS + 4; // Height of the window, accounting for the title and padding
    int startx, starty;

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Calculate window position to center it
    startx = (COLS - win_width) / 2;
    starty = (LINES - win_height) / 2;

    // Create a new window for the leaderboard
    WINDOW *win = newwin(win_height, win_width, starty, startx);
    box(win, 0, 0); // Draw a box around the window

    // Display the leaderboard title
    mvwprintw(win, 1, (win_width - 14) / 2, "Top %d Players", MAX_PLAYERS);
    mvwprintw(win, 2, 1, "--------------------------");
    mvwprintw(win, 3, 1, "Name\t\tScore");

    // Display each player and score
    for (int i = 0; i < MAX_PLAYERS; i++) {
        mvwprintw(win, i + 4, 1, "%d. %s\t\t%d", i + 1, lb->players[i].name, lb->players[i].score);
    }

    // Refresh the window to show the leaderboard
    wrefresh(win);

    // Wait for user input to close the leaderboard
    getch();

    // Clean up
    delwin(win);
    endwin();
}
