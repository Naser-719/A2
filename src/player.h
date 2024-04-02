// Defines the structure and functions for the player character in the game.

#ifndef PLAYER_H
#define PLAYER_H

#include<ncurses.h>

// Represents the player's position with x and y coordinates.
typedef struct {
    int x; // Horizontal position of the player
    int y; // Vertical position of the player
} Player;

// Initializes the player's position to predefined coordinates.
void initPlayer(Player *player);

// Moves the player based on the input. Now includes both deltaX (horizontal) and deltaY (vertical) movement.
void movePlayer(Player *player, int deltaX, int deltaY);

// Draws the player character on the console.
void drawPlayer(WINDOW *win, const Player *player);

#endif // PLAYER_H
