//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
#include <ncurses.h>
#include <stdlib.h>
#include "blocks.h"

// Define constants for the game area
#define GAME_WIDTH 80
#define GAME_HEIGHT 30
#define MAX_BLOCKS 10




Block blocks[MAX_BLOCKS]; 


// Function to initialize blocks
void initialize_blocks() {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        blocks[i].active = false;
    }
}

// Function to create a new block
void create_block(int index, int width, int height, int speed) {
    if (index >= 0 && index < MAX_BLOCKS) {
        blocks[index].width = width;
        blocks[index].height = height;
        blocks[index].posX = rand() % (GAME_WIDTH - width);
        blocks[index].posY = 0; // Start at the top of the game window
        blocks[index].speed = speed;
        blocks[index].active = true;
    }
}

// Function to move the blocks down
void update_blocks_position() {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (blocks[i].active) {
            blocks[i].posY += blocks[i].speed; // Move block down

            // If the block is off the screen, deactivate it
            if (blocks[i].posY >= GAME_HEIGHT) {
                blocks[i].active = false;
            }
        }
    }
}


// Function to draw the blocks on the screen
void render_blocks(WINDOW *win) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (blocks[i].active) {
            for (int y = 0; y < blocks[i].height; ++y) {
                for (int x = 0; x < blocks[i].width; ++x) {
                    mvwaddch(win, blocks[i].posY + y, blocks[i].posX + x, '.'); // Use '.' for larger blocks
                }
            }
        }
    }
}

// Function to check for collision with the player
bool check_collision_with_player(int playerX, int playerY, int playerWidth, int playerHeight) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (blocks[i].active) {
            // Simple bounding box collision detection
            if (playerX < blocks[i].posX + blocks[i].width &&
                playerX + playerWidth > blocks[i].posX &&
                playerY < blocks[i].posY + blocks[i].height &&
                playerY + playerHeight > blocks[i].posY) {
                return true;
            }
        }
    }
    return false;
}



// Find an inactive block and initialize it
void spawn_new_block() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!blocks[i].active) {
            int block_width = rand() % 4 + 1; // Block width between 1 and 4
            int block_height = rand() % 3 + 1; // Block height between 1 and 3
            int block_speed = 1; // Speed of block
            create_block(i, block_width, block_height, block_speed);
            break; // Break after finding the first inactive block
        }
    }
}
