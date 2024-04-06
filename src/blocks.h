//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
/*
 * Function prototypes for block handling in the game Skyfall.
 * This header file contains the prototypes of functions used to
 * create, move, render, and detect collisions of falling blocks in the game.
 */

#ifndef BLOCKS_H
#define BLOCKS_H


#include <ncurses.h>
#include <stdbool.h>

#define MAX_BLOCKS 10


/*
 *  Represents a single falling block.
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

/*
 * Initialize all blocks in the game.
 *
 * Sets up the blocks array and initializes each block to inactive status.
 */
void initialize_blocks();

/*
 * Creates a new block and places it at the top of the screen.
 * index The index of the block in the blocks array.
 * width The width of the new block
 * height The height of the new block
 * speed The falling speed of the new block.
 *
 * This function initializes a block at the given index in the blocks array,
 * setting its size, initial position, and falling speed.
 */
void create_block(int index, int width, int height, int speed);

/*
 * this  updates the position of each active block.
 *
 * Moves each active block down the screen according to its speed.
 * Deactivates blocks that have moved past the bottom of the screen.
 */
void update_blocks_position();

/*
 * this draws the blocks on the given window.
 * win A pointer to the ncurses window where the blocks will be rendered.
 *
 * This function iterates over all active blocks and draws them on the
 * specified ncurses window.
 */
void render_blocks(WINDOW *win);

/*
 * Checks for collision between the player and any block.
 * playerX The X coordinate of the player.
 * playerY The Y coordinate of the player.
 * playerWidth The width of the player.
 * playerHeight The height of the player.
 *  true if there is a collision, false otherwise.
 *
 * Performs bounding box collision detection between the player and all active blocks.
 * Assumes that the player is a rectangle for the purposes of collision detection.
 */
bool check_collision_with_player(int playerX, int playerY, int playerWidth, int playerHeight);

/*
 * this Spawns a new block** by finding an *inactive* block and initializing it.
 *
 * This function iterates through the global `blocks` array to locate an
 * inactive block. When it finds one, it sets the block with random dimensions
 * and a predefined speed, then marks it as active.
 *
 * this ensures that the random number generator is initialized with `srand()`
 * before calling this function to ensure that block sizes are truly random.
 * it  activate more than one block per call.
 *
 */
void spawn_new_block();

#endif // BLOCKS_H
