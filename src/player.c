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
    if (player->x < 1) {
        player->x = 1;
    } else if (player->x > SCREEN_WIDTH - 2) {
        player->x = SCREEN_WIDTH - 2;
    }

    // Keep player within the vertical boundaries
    if (player->y < 1) {
        player->y = 1;
    } else if (player->y > SCREEN_HEIGHT - 2) {
        player->y = SCREEN_HEIGHT - 2;
    }
}

void drawPlayer(WINDOW *win,const Player *player) {
    clear(); // Clear the screen before redrawing
    mvwprintw(win,player->y - 3, player->x, "O "); // Draw the head
    mvwprintw(win,player->y - 2, player->x - 1, "/|\\"); // Draw arms and torso
    mvwprintw(win,player->y - 1, player->x - 1, "/ \\"); // Draw legs
    wrefresh(win);
}


