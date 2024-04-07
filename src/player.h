//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh

/**
 * @file player.h
 * @brief Defines the structure and functions for the player character in the game.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <ncurses.h>
#include <stdbool.h>

#define PLAYER_WIDTH 2.5
#define PLAYER_HEIGHT 2.5

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30

/**
 * @struct Player
 * @brief Represents the player character in the game.
 * 
 * This structure holds information about the player's position and available power-ups.
 */
typedef struct {
    int x;
    int y;
    bool slow_down_available; ///< Indicates if the slow-down power-up is available.
    bool immunity_available; ///< Indicates if the immunity power-up is available
} Player;

/**
 * Initializes the player's position to predefined coordinates and sets initial values for power-ups.
 * 
 * @param player A pointer to the Player structure to be initialized.
 */
void initPlayer(Player *player);

/**
 * Moves the player based on the input. Allows for both horizontal and vertical movement.
 * 
 * @param player A pointer to the Player structure whose position is to be updated.
 * @param deltaX The change in the horizontal position (left/right movement).
 * @param deltaY The change in the vertical position (up/down movement).
 */
void movePlayer(Player *player, int deltaX, int deltaY);

/**
 * Draws the player character on the game window.
 * 
 * @param win A pointer to the WINDOW structure where the player should be drawn.
 * @param player A constant pointer to the Player structure to be drawn.
 */
void drawPlayer(WINDOW *win, const Player *player);

#endif // PLAYER_H
