// Defines the structure and functions for the player character in the game.

#ifndef PLAYER_H
#define PLAYER_H

// Represents the player's position with x and y coordinates.
typedef struct {
    int x; // Horizontal position of the player
    int y; // Vertical position of the player
} Player;

// Initializes the player's position to predefined coordinates.
void initPlayer(Player *player);

// Moves the player horizontally based on the input.
void movePlayer(Player *player, int deltaX);

// Draws the player character on the console.
void drawPlayer(const Player *player);

#endif // PLAYER_H
