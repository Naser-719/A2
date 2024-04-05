//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
/**
 * @file blocks.h
 * @brief Function prototypes for block handling in the game Skyfall.
 *
 * This header file contains the prototypes of functions used to
 * create, move, render, and detect collisions of falling blocks in the game.
 */

#ifndef BLOCKS_H
#define BLOCKS_H


#include <ncurses.h>
#include <stdbool.h>

#define MAX_BLOCKS 10


/**
 * @struct Block
 * @brief Represents a single falling block.
 *
 * This structure holds the properties of a block including its dimensions,
 * position, speed, and active status.
 */
typedef struct {
    int width;  ///< The width of the block.
    int height; ///< The height of the block.
    int posX;   ///< The X coordinate of the block.
    int posY;   ///< The Y coordinate of the block.
    int speed;  ///< The speed at which the block falls.
    bool active;///< Indicates whether the block is active (falling) or not.
} Block;


extern Block blocks[MAX_BLOCKS];

/**
 * @brief Initialize all blocks in the game.
 *
 * Sets up the blocks array and initializes each block to inactive status.
 */
void initialize_blocks();

/**
 * @brief Creates a new block and places it at the top of the screen.
 * @param index The index of the block in the blocks array.
 * @param width The width of the new block.
 * @param height The height of the new block.
 * @param speed The falling speed of the new block.
 *
 * This function initializes a block at the given index in the blocks array,
 * setting its size, initial position, and falling speed.
 */
void create_block(int index, int width, int height, int speed);

/**
 * @brief Updates the position of each active block.
 *
 * Moves each active block down the screen according to its speed.
 * Deactivates blocks that have moved past the bottom of the screen.
 */
void update_blocks_position();

/**
 * @brief Draws the blocks on the given window.
 * @param win A pointer to the ncurses window where the blocks will be rendered.
 *
 * This function iterates over all active blocks and draws them on the
 * specified ncurses window.
 */
void render_blocks(WINDOW *win);

/**
 * @brief Checks for collision between the player and any block.
 * @param playerX The X coordinate of the player.
 * @param playerY The Y coordinate of the player.
 * @param playerWidth The width of the player.
 * @param playerHeight The height of the player.
 * @return **true** if there is a collision, **false** otherwise.
 *
 * Performs bounding box collision detection between the player and all active blocks.
 * @note Assumes that the player is a rectangle for the purposes of collision detection.
 */
bool check_collision_with_player(int playerX, int playerY, int playerWidth, int playerHeight);

/**
 * @brief **Spawns a new block** by finding an *inactive* block and initializing it.
 *
 * This function iterates through the global `blocks` array to locate an
 * inactive block. When it finds one, it sets the block with random dimensions
 * and a predefined speed, then marks it as active.
 *
 * @attention Ensure that the random number generator is initialized with `srand()`
 * before calling this function to ensure that block sizes are truly random.
 *
 * @note The function assumes that `MAX_BLOCKS` is defined and represents the maximum
 * number of blocks that can be active at any one time.
 *
 * @note This function relies on the global array `blocks`.
 *
 * @warning This function will activate the first inactive block it finds and will not
 * activate more than one block per call.
 *
 * @see create_block
 * @see MAX_BLOCKS
 * @see blocks
 */
void spawn_new_block();

#endif // BLOCKS_H
