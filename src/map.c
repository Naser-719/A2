//Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
#include "map.h"


int best_time; 

// Function declarations
struct timespec get_mode_delay(int mode) {
    int delay_ms = mode == 0 ? EASY_MODE_DELAY_MS : HARD_MODE_DELAY_MS;
    struct timespec ts = { .tv_sec = delay_ms / 1000, .tv_nsec = (delay_ms % 1000) * 1000000L };
    return ts;
}



void startScreen() {
    // Start color functionality
    start_color();
    init_pair(3, COLOR_RED, COLOR_BLACK);

    // Calculate the position to center the title "SKYFALL"
    const char *title = "SKYFALL";
    const char *prompt = "Press any key to start";
    int title_len = strlen(title),  prompt_len = strlen(prompt);

    int title_x = (SCREEN_WIDTH - title_len) / 2;
    int title_y = SCREEN_HEIGHT / 2 - 1; // Position the title one line above the center

    // Calculate the position to place the prompt right below "SKYFALL"
    int prompt_x = (SCREEN_WIDTH - prompt_len) / 2;
    int prompt_y = SCREEN_HEIGHT / 2; // Center line

    // Clear the screen
    clear();

    // Set the color and print "SKYFALL" in red, bold
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(title_y, title_x, "%s", title);
    attroff(COLOR_PAIR(3) | A_BOLD);

    // Print "Press any key to start" right below "SKYFALL"
    mvprintw(prompt_y, prompt_x, "%s", prompt);

    best_time = load_best_time();
    mvprintw(prompt_y+1, prompt_x-0.5, "Best time to beat-> %d sec", best_time);

    // Refresh the screen to show the text
    refresh();

    // Wait for any key press to continue
    getch();
}

void save_best_time(int bestTime) {
    FILE *file = fopen("best_time.txt", "w"); // Open the file in write mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d", bestTime); // Write the best time
    fclose(file); // Close the file
}

int load_best_time() {
    int bestTime;
    FILE *file = fopen("best_time.txt", "r"); // Open the file in read mode
    if (file == NULL) {
        printf("Error opening file or file does not exist. Starting with default best time.\n");
        return -1;  
    }
    fscanf(file, "%d", &bestTime); // Read the best time
    fclose(file); // Close the file
    return bestTime;
}

void displayInstructions(WINDOW *win, char power_up) {
    werase(win); // Clear previous instructions

    // Draw the borders and print instructions
    box(win, '|', '-'); // Draw box borders
    mvwprintw(win, 1, 1, "Instructions:Dodge the blocks to survive.'P'= pause,'q'= quit");
    if(power_up == 'i'){
        mvwprintw(win, 2, 2, "--ACTIVATED Immunity (20 sec)--, 's' = Activate Easy mode (20 sec)");
    } else if(power_up == 's'){
        mvwprintw(win, 2, 2, "'I' = Activate Immunity (20 sec), --ACTIVATED Easy mode (20 sec)--");
    } else {
        mvwprintw(win, 2, 2, "'I' = Activate Immunity (20 sec), 's' = Activate Easy mode (20 sec)");
    }
    wrefresh(win); // Refresh to show instructions
}


void display_window(WINDOW *win) {
    // Clear the window before drawing
    werase(win);

    // Activate color pair 1 for blue borders
    wattron(win, COLOR_PAIR(1));
    // Draw the level boundaries with '*', using color pair 1
    box(win, '*', '*'); // Draw box borders with '*'
    wattroff(win, COLOR_PAIR(1)); // Deactivate color pair 1

    // Activate color pair 2 for the light blue bottom border
    wattron(win, COLOR_PAIR(2));
    // Draw the bottom line in light blue
    mvwhline(win, 29, 1, '*', 78); // Assuming the window height is 30
    wattroff(win, COLOR_PAIR(2)); // Deactivate color pair 2

    // Refresh the window to display the new content
    wrefresh(win);
}

void delay(int milliseconds) {
    clock_t start_time = clock();
    long wait_ticks = milliseconds * (CLOCKS_PER_SEC / 1000);
    while (clock() < start_time + wait_ticks);
}

void gameOver(WINDOW *message_win, int total_time) {
    if(total_time> best_time){
        best_time = total_time;
        save_best_time(best_time);
    }

    werase(message_win); // Clear the instruction window
    mvwprintw(message_win, 1, 1, "Game Over! Press 'Q' to quit. Time survived: %d seconds!", total_time);
    wrefresh(message_win);
    int ch;
    do {
        ch = wgetch(message_win); // Wait for 'Q' to quit
    } while (ch != 'q' && ch != 'Q');
}


void game_loop(WINDOW *game_win, WINDOW *message_win) {
    bool immunity = false, slow_mode = false;
    time_t immunity_time = time(NULL);
    int slow_down_start = 0, slow_down_once = 0, immunity_once = 0;

    srand(time(NULL)); // Seed RNG
    initialize_blocks(); // Setup blocks
    Player player; initPlayer(&player); // Initialize player

    int mode = 0; time_t start_time = time(NULL); // Game mode setup


    display_window(game_win); // Display the initial level
    drawPlayer(game_win, &player); // Draw the player on the game window
    displayInstructions(message_win, 0); // Display instructions in the message window

    bool game_running = true;
    while (game_running) {
        if(immunity == true){
            if(difftime(time(NULL), immunity_time)> POWERUP_TIME){
                immunity = false;
                displayInstructions(message_win, 0);
            }
        }

        if (difftime(time(NULL), start_time) >= (HARD_MODE_START+slow_down_start) && mode == 0) {
                mode = 1; display_window(game_win); // Switch to hard mode
                slow_mode = false;
                displayInstructions(message_win, 0);
            }
        
        spawn_new_block(); update_blocks_position(); // Update blocks

        if (immunity == false){
            if (check_collision_with_player(player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT)) {
                gameOver(message_win, difftime(time(NULL), start_time)); // Display game over message and wait for 'q'
                break; 
            }
        }

        werase(game_win); display_window(game_win);
        drawPlayer(game_win, &player); render_blocks(game_win); wrefresh(game_win); // Draw state
        mvwprintw(message_win, 3, 3, "Current Mode: %s", mode == 0 ? "Easy" : "Hard");
        wrefresh(message_win);

	    delay(mode == 0 ? EASY_MODE_DELAY_MS : HARD_MODE_DELAY_MS);
        int ch = wgetch(game_win); // Non-blocking input read
        
        switch(ch) {
            case KEY_LEFT:
                movePlayer(&player, -1, 0); break;
            case KEY_RIGHT:
                movePlayer(&player, 1, 0); break;
            case KEY_UP:
                movePlayer(&player, 0, -1); break;
            case KEY_DOWN:
                movePlayer(&player, 0, 1); break;

            case 's':
                if((difftime(time(NULL), start_time) > HARD_MODE_START) && (slow_down_once ==0) && (immunity==false)){
                    mode = 0;
                    slow_mode = true;
                    slow_down_start = difftime(time(NULL), start_time)-HARD_MODE_START+POWERUP_TIME; 
                    slow_down_once += 1;
                    displayInstructions(message_win, 115); //115 for 's'
                } break;

            case 'i':
                if (immunity_once==0 && slow_mode== false){
                    immunity = true;
                    immunity_once = 1;
                    immunity_time = time(NULL);
                    displayInstructions(message_win, 105); //105 for 'i'
                } break;
            case 'p':
                pause_game(ch, message_win);
                break;

            case 'q':
                game_running = quit_game(ch, message_win);
                break;
        }

        drawPlayer(game_win, &player);
        // Refresh the game window to show any updates
        wrefresh(game_win);
        }
}



bool quit_game(int ch, WINDOW *message_win){
    // Ask if the user really wants to quit
    werase(message_win);
    mvwprintw(message_win, 1, 1, "Do you want to quit? (y/n) ");
    wrefresh(message_win);
    do {
        ch = wgetch(message_win); // Wait for 'y' or 'n'
    } while (ch != 'y' && ch != 'n');

    if (ch == 'y') {
        return false; // Exit the loop and end the game
    } else {
        werase(message_win); // Clear the quit message
        displayInstructions(message_win, 0); // Redisplay instructions
    }
    return true;
}


void pause_game(int ch, WINDOW *message_win){
    werase(message_win);
    mvwprintw(message_win, 1, 1, "Game is paused. Press 'P' to continue playing the game.\t");
    wrefresh(message_win);
    while(1){
        ch = wgetch(message_win); // Wait for p or P
        if (ch == 'p' || ch == 'P') break;
    } 

    werase(message_win); // Clear the quit message
    displayInstructions(message_win,0); // Redisplay instructions
    wrefresh(message_win);
}