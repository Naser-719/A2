/**
 * @file leaderboard.h
 * @brief Functions and structures for managing a game leaderboard.
 *
 * This file contains the definitions for the leaderboard management system,
 * including structures for player data, leaderboard data, and functions to
 * initialize, update, and display the leaderboard.
 */

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <ncurses.h>

#define MAX_PLAYERS 5 ///< The maximum number of players on the leaderboard.
#define NAME_LENGTH 50 ///< The maximum length of a player's name.

/**
 * @struct Player
 * @brief Represents a single player's score data.
 *
 * This structure holds the name and score of a single player.
 */
typedef struct {
    char name[NAME_LENGTH]; ///< The player's name.
    int score; ///< The player's score.
} LeaderboardPlayer;

/**
 * @struct Leaderboard
 * @brief Represents the game's leaderboard.
 *
 * This structure contains an array of `Player` structures to represent
 * the top players in the game.
 */
typedef struct {
    LeaderboardPlayer players[MAX_PLAYERS]; ///< Array of top players.
} Leaderboard;

/**
 * @brief Initializes a leaderboard to empty values.
 *
 * Sets up a leaderboard with default names and scores. This function
 * should be called before using the leaderboard.
 *
 * @param lb A pointer to the leaderboard to initialize.
 * @note Assumes 0 is the lowest possible score.
 */
void initializeLeaderboard(Leaderboard *lb);

/**
 * @brief Updates the leaderboard with a new score.
 *
 * If the new score is high enough, updates the leaderboard to include
 * the new player and score, displacing the lowest score if necessary.
 *
 * @param lb A pointer to the leaderboard to update.
 * @param playerName The name of the player.
 * @param playerScore The player's score.
 * @attention This function modifies the leaderboard in place.
 */
void updateLeaderboard(Leaderboard *lb, const char* playerName, int playerScore);

/**
 * @brief Displays the leaderboard in a ncurses window.
 *
 * Creates and displays a new ncurses window showing the top players
 * and their scores.
 *
 * @param lb A pointer to the leaderboard to display.
 * @note This function initializes and finalizes ncurses. It should not
 *       be called if ncurses is already in use.
 * @warning The function blocks for user input before closing the leaderboard window.
 * @see initializeLeaderboard, updateLeaderboard
 */
void displayLeaderboard(const Leaderboard *lb);

#endif // LEADERBOARD_H
