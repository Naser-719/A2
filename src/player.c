#include "player.h"
#include <ncurses.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30

void initPlayer(Player *player) {
    player->x = SCREEN_WIDTH / 2; // Center horizontally
    player->y = SCREEN_HEIGHT - 5; // A little above the bottom
}

//movePlayer function for player  movement
void movePlayer(Player *player, int deltaX, int deltaY) {
    player->x += deltaX;
    player->y += deltaY;

    // Keep player within the horizontal boundaries
    if (player->x < 2) {
        player->x = 2;
    } else if (player->x > SCREEN_WIDTH - 4) {
        player->x = SCREEN_WIDTH - 4;
    }

    // Keep player within the vertical boundaries
    if (player->y < 4) {
        player->y = 4;
    } else if (player->y > SCREEN_HEIGHT - 1) {
        player->y = SCREEN_HEIGHT - 1;
    }
}
void drawPlayer(WINDOW *win, const Player *player) {
    // Ensure we don't draw outside of the boundaries.
    // Clear the screen only where it's needed, instead of using clear().

    // Draw the head
    if (player->y - 3 >= 1) {
        mvwprintw(win, player->y - 3, player->x, "O ");
    }
    // Draw arms and torso
    if (player->y - 2 >= 1) {
        mvwprintw(win, player->y - 2, player->x - 1, "/|\\");
    }
    // Draw legs
    if (player->y - 1 >= 1) {
        mvwprintw(win, player->y - 1, player->x - 1, "/ \\");
    }
    
    wrefresh(win); // Refresh the window to display the new content.
}


/*
void drawPlayer(WINDOW *win,const Player *player) {
    clear(); // Clear the screen before redrawing
    mvwprintw(win,player->y - 3, player->x, "O "); // Draw the head
    mvwprintw(win,player->y - 2, player->x - 1, "/|\\"); // Draw arms and torso
    mvwprintw(win,player->y - 1, player->x - 1, "/ \\"); // Draw legs
    wrefresh(win);
}
*/

