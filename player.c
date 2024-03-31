// player.c

#include "player.h"
#include <ncurses.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30

void initPlayer(Player *player) {
    player->x = SCREEN_WIDTH / 2; // Center horizontally
    player->y = SCREEN_HEIGHT - 5; // A little above the bottom
}

void movePlayer(Player *player, int deltaX) {
    player->x += deltaX;
    if (player->x < 1) {
        player->x = 1; // Keep player within the left boundary
    } else if (player->x > SCREEN_WIDTH - 1) {
        player->x = SCREEN_WIDTH - 1; // Keep player within the right boundary
    }
}

void drawPlayer(const Player *player) {
    clear(); // Clear the screen before redrawing
    mvprintw(player->y - 3, player->x, "O "); // Draw the head
    mvprintw(player->y - 2, player->x - 1, "/|\\"); // Draw arms and torso
    mvprintw(player->y - 1, player->x - 1, "/ \\"); // Draw legs
}
