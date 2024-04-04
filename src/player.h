// Defines the structure and functions for the player character in the game.

#ifndef PLAYER_H
#define PLAYER_H

#include<ncurses.h>

#define PLAYER_WIDTH 2.5
#define PLAYER_HEIGHT 2.5

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30

// Represents the player's position with x and y coordinates.
typedef struct {
    int x; // Horizontal position of the player
    int y; // Vertical position of the player
    bool slow_down_available;
    bool immunity_available;
} Player;

// Initializes the player's position to predefined coordinates.
void initPlayer(Player *player);

// Moves the player based on the input. Now includes both deltaX (horizontal) and deltaY (vertical) movement.
void movePlayer(Player *player, int deltaX, int deltaY);

// Draws the player character on the console.
void drawPlayer(WINDOW *win, const Player *player);

#endif // PLAYER_H
