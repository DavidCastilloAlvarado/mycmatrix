#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <signal.h>

#define YAPE_TEXT "YAPE"
#define YAPE_HEIGHT 31
#define YAPE_WIDTH  37
int yape_shape[YAPE_HEIGHT][YAPE_WIDTH] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,1,1,1,1,1,},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,0,0,1,0,},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,},
    {0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,},
    {0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0,0,0,},
    {0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,1,1,1,0,0,1,1,0,1,1,0,0,0,1,0,},
    {0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,0,1,1,1,0,},
    {0,0,0,0,0,0,1,1,0,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,},
    {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
};

typedef struct {
    int x;
    int y;
    int length;
    int speed;
    char *chars;
    int *boldness;
} Column;

Column *columns;
int num_columns;
int max_rows, max_cols;
int running = 1;

void finish(int sig) {
    running = 0;
}

char get_random_char() {
    // Matrix-style characters
    const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#$%^&*()_+-=[]{}|;:,.<>?/~`";
    return chars[rand() % (sizeof(chars) - 1)];
}

char get_yape_char(int x, int y) {
    // Return a character from "YAPE" based on which letter we're in
    int min_letter_width = 12;
    int min_total_width = min_letter_width * 4;
    int target_width = (max_cols * 50) / 100;  // Fixed at 50% of screen width
    
    if (target_width < min_total_width) {
        target_width = min_total_width;
    }
    
    int yape_start_col = (max_cols - target_width) / 2;
    int rel_x = x - yape_start_col;
    
    int quarter = target_width / 4;
    
    if (rel_x < quarter) return 'Y';
    else if (rel_x < quarter * 2) return 'A';
    else if (rel_x < quarter * 3) return 'P';
    else return 'E';
}

// Calculate if position is inside YAPE shape - scaled to window
int is_in_yape_shape(int x, int y) {
    // Scale YAPE to fit within screen bounds
    int min_letter_width = 3;
    int min_total_width = min_letter_width * 4;
    int target_width = (max_cols * 50) / 100;  // Fixed at 50% of screen width
    
    if (target_width < min_total_width) {
        target_width = min_total_width;
    }
    
    // Stretch height independently to 98% of screen
    int target_height = (max_rows * 98) / 100;
    
    // Center the YAPE text
    int yape_start_row = (max_rows - target_height) / 2;
    int yape_start_col = (max_cols - target_width) / 2;
    
    int rel_y = y - yape_start_row;
    int rel_x = x - yape_start_col;
    
    if (rel_y >= 0 && rel_y < target_height && rel_x >= 0 && rel_x < target_width) {
        // Scale coordinates to original YAPE dimensions
        int yape_y = (rel_y * YAPE_HEIGHT) / target_height;
        int yape_x = (rel_x * YAPE_WIDTH) / target_width;
        
        if (yape_y >= 0 && yape_y < YAPE_HEIGHT && yape_x >= 0 && yape_x < YAPE_WIDTH) {
            return yape_shape[yape_y][yape_x];
        }
    }
    return 0;
}

// Calculate distance to nearest YAPE character - scaled version
float distance_to_yape(int x, int y) {
    // Use scaled dimensions - match the scaling in is_in_yape_shape
    int min_letter_width = 12;
    int min_total_width = min_letter_width * 4;
    int target_width = (max_cols * 50) / 100;  // Fixed at 50% of screen width
    
    if (target_width < min_total_width) {
        target_width = min_total_width;
    }
    
    // Stretch height independently to 98% of screen
    int target_height = (max_rows * 98) / 100;
    
    int yape_start_row = (max_rows - target_height) / 2;
    int yape_start_col = (max_cols - target_width) / 2;
    
    // Quick check: if we're inside the bounding box, check precisely
    int rel_y = y - yape_start_row;
    int rel_x = x - yape_start_col;
    
    if (rel_y >= 0 && rel_y < target_height && rel_x >= 0 && rel_x < target_width) {
        // We're in the bounding box, check if in shape
        if (is_in_yape_shape(x, y)) {
            return 0.0;
        }
    }
    
    // Calculate distance to bounding box
    float min_dist = 1000000.0;
    
    // Distance to edges of bounding box
    if (y < yape_start_row) {
        float dy = yape_start_row - y;
        min_dist = dy * dy;
    } else if (y >= yape_start_row + target_height) {
        float dy = y - (yape_start_row + target_height - 1);
        min_dist = dy * dy;
    }
    
    if (x < yape_start_col) {
        float dx = yape_start_col - x;
        min_dist += dx * dx;
    } else if (x >= yape_start_col + target_width) {
        float dx = x - (yape_start_col + target_width - 1);
        min_dist += dx * dx;
    }
    
    return min_dist;
}

void init_column(Column *col, int x) {
    col->x = x;
    col->y = rand() % max_rows - max_rows;
    col->length = 40 + rand() % 30;  // Longer columns (20-50 chars instead of 10-30)
    col->speed = 1 + rand() % 3;
    col->chars = malloc(col->length * sizeof(char));
    col->boldness = malloc(col->length * sizeof(int));
    
    for (int i = 0; i < col->length; i++) {
        col->chars[i] = get_random_char();
        col->boldness[i] = 0;
    }
}

void update_column(Column *col) {
    col->y += col->speed;
    
    // Reset column when it goes off screen
    if (col->y - col->length > max_rows) {
        init_column(col, col->x);
    }
    
    // Update characters and calculate boldness based on YAPE proximity
    for (int i = 0; i < col->length; i++) {
        int char_y = col->y - i;
        if (char_y >= 0 && char_y < max_rows) {
            // Check if in YAPE shape - ONLY the actual letter pixels
            if (is_in_yape_shape(col->x, char_y)) {
                col->boldness[i] = 3; // Very bold - inside letter
                // Use YAPE letters in the shape, change less frequently
                if (rand() % 30 == 0) {
                    col->chars[i] = get_yape_char(col->x, char_y);
                }
            } else {
                // For everything else (including spaces between letters), use normal behavior
                col->boldness[i] = 0; // Normal rain
                // Normal characters change frequently
                if (rand() % 8 == 0) {
                    col->chars[i] = get_random_char();
                }
            }
        } else {
            if (rand() % 8 == 0) {
                col->chars[i] = get_random_char();
            }
        }
    }
}

void draw_column(Column *col) {
    for (int i = 0; i < col->length; i++) {
        int y = col->y - i;
        if (y >= 0 && y < max_rows && col->x >= 0 && col->x < max_cols) {
            // Set color based on position
            int color_pair = 1;
            int attr = 0;
            
            if (i == 0) {
                // Head of the column - bright white
                color_pair = 3;
                attr = A_BOLD;
            } else {
                // Apply boldness based on proximity to YAPE
                switch (col->boldness[i]) {
                    case 3: // Inside YAPE - BRIGHT yellow and BOLD
                        if (is_in_yape_shape(col->x, y)) {
                            color_pair = 4;  // Yellow
                            attr = A_BOLD | A_REVERSE;
                        } else {
                            color_pair = 2;
                            attr = A_BOLD;
                        }
                        break;
                    case 2: // Near YAPE - bright green
                        color_pair = 2;
                        attr = A_BOLD;
                        break;
                    case 1: // Medium distance - normal green
                        color_pair = 2;
                        attr = A_NORMAL;
                        break;
                    case 0: // Normal rain - use standard green
                        color_pair = 2;
                        attr = A_NORMAL;
                        break;
                }
            }
            
            attron(COLOR_PAIR(color_pair) | attr);
            mvaddch(y, col->x, col->chars[i]);
            attroff(COLOR_PAIR(color_pair) | attr);
        }
    }
}

int main() {
    srand(time(NULL));
    
    // Setup signal handler
    signal(SIGINT, finish);
    signal(SIGTERM, finish);
    
    // Initialize ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    
    // Initialize color pairs
    init_pair(1, COLOR_GREEN, COLOR_BLACK);      // Dim green
    init_pair(2, COLOR_GREEN, COLOR_BLACK);      // Normal green  
    init_pair(3, COLOR_WHITE, COLOR_BLACK);      // White for head
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);     // Yellow for YAPE
    
    getmaxyx(stdscr, max_rows, max_cols);
    
    // Initialize columns - create 2x density for more rain
    num_columns = max_cols * 2;
    columns = malloc(num_columns * sizeof(Column));
    
    for (int i = 0; i < num_columns; i++) {
        init_column(&columns[i], i % max_cols);  // Map multiple columns to same x position
        columns[i].y -= rand() % max_rows; // Full stagger for overlapping columns
    }
    
    // Main loop
    while (running) {
        int ch = getch();
        if (ch == 'q' || ch == 'Q' || ch == 27) { // q, Q, or ESC
            break;
        }
        
        // Update screen dimensions dynamically (handles window resize)
        int new_rows, new_cols;
        getmaxyx(stdscr, new_rows, new_cols);
        
        // If window was resized, adjust columns
        if (new_cols != max_cols || new_rows != max_rows) {
            max_rows = new_rows;
            max_cols = new_cols;
            
            // Reallocate columns if width changed
            if (new_cols != num_columns) {
                for (int i = 0; i < num_columns; i++) {
                    free(columns[i].chars);
                    free(columns[i].boldness);
                }
                free(columns);
                
                num_columns = max_cols * 2;
                columns = malloc(num_columns * sizeof(Column));
                
                for (int i = 0; i < num_columns; i++) {
                    init_column(&columns[i], i % max_cols);
                    columns[i].y -= rand() % max_rows;
                }
            }
        }
        
        erase();
        
        // Update and draw all columns
        for (int i = 0; i < num_columns; i++) {
            update_column(&columns[i]);
            draw_column(&columns[i]);
        }
        
        refresh();
        usleep(40000); // 40ms delay (faster for more constant rain)
    }
    
    // Cleanup
    for (int i = 0; i < num_columns; i++) {
        free(columns[i].chars);
        free(columns[i].boldness);
    }
    free(columns);
    
    endwin();
    return 0;
}
