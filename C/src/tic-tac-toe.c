//Wargames Movie Simulator
//Written by Andy Glenn
//(c) 2023

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define SIZE 3

static int cpu_threshold = 65; //this is the cpu_threshold - set a lower value for a fast system
static int cpu_threshold_trigger = 3; //this is the number of times the cpu_threshold needs to be met
static int cpu_threshold_trigger_count = 0; //this counts the number of times the cpu_threshold has been triggered
static int previous_utilization = 0;
static int peak_utilization = 0;
static char cpu_overload = 'N';

char board[SIZE][SIZE]; // Game board

void fix_backspace_key() {
	char system_command[100];
	snprintf(system_command, sizeof(system_command), "stty erase ^H");
    system(system_command);
}

void clear_screen() {
    printf("\033[H\033[J");
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void draw_nought(int row_offset, int col_offset) {
    char nought[7][14] = {
        //{' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '#', '#', ' '},
        {' ', '#', ' ', ' ', '#'},
        {' ', '#', ' ', ' ', '#'},
        {' ', '#', ' ', ' ', '#'},
        {' ', ' ', '#', '#', ' '}
        //{' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            gotoxy(col_offset + j, row_offset + i);
            printf("\033[34m");
            printf("%c", nought[i][j]);
            printf("\033[0m");
        }
    }
}

void draw_cross(int row_offset, int col_offset) {
    char cross[7][14] = {
        //{' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' ', '#'},
        {' ', ' ', '#', '#', ' '},
        {' ', ' ', '#', '#', ' '},
        {' ', ' ', '#', '#', ' '},
        {' ', '#', ' ', ' ', '#'}
        //{' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            gotoxy(col_offset + j, row_offset + i);
            printf("\033[31m");
            printf("%c", cross[i][j]);
            printf("\033[0m");
        }
    }
}

void draw_grid() {
int rows = 24, cols = 80;
    int cell_size = 7; // Grid cell size
    int grid_size = 3; // 3x3 grid

    int start_row = (rows - (cell_size * grid_size)) / 2;
    int start_col = cols - ((cell_size * 2) * grid_size + 1); // Right-justify the grid

    for (int i = 0; i <= grid_size; i++) {
        gotoxy(start_col, start_row + i * cell_size);
        for (int j = 0; j < (cell_size *2) * grid_size; j++) {
            printf("*");
        }
    }

    for (int i = 0; i <= grid_size; i++) {
        for (int j = 0; j < (cell_size * grid_size) + 1; j++) {
            gotoxy(start_col + i * (cell_size * 2), start_row + j);
            printf("*");
        }
    }

    char row_labels[] = {'a', 'b', 'c'};
    for (int row = 0; row < grid_size; row++) {
        for (int col = 1; col <= grid_size; col++) {
            int x = start_col + (col - 1) * (cell_size *2) + ((cell_size *2) / 2);
            int y = start_row + row * cell_size + cell_size - 1;
            gotoxy(x, y);
            printf("%c%d", row_labels[row], col);
        }
    }
}

void reset_board() {
    clear_screen();
    draw_grid();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '\0';
        }
    }
}


char get_side_choice() {
    char side;
    gotoxy(0, 1);
    printf("SELECT SIDE (O OR X):\n");
    gotoxy(0, 2);
    scanf(" %c", &side);
    side=toupper(side);
    gotoxy(0, 1);
    printf("                     \n");
    printf("                     \n");


    while (side != 'X' && side != 'O') {
        gotoxy(0, 1);
        printf("INVALID OPTION       \n");
        printf("                     \n");
        usleep(2000000);
        
        gotoxy(0, 1);
        printf("SELECT SIDE (O OR X):\n");
        gotoxy(0, 2);
        scanf(" %c", &side);
        side=toupper(side);
        gotoxy(0, 1);
        printf("                     \n");
        printf("                     \n");
    }
    
    return side;
}

void get_grid_choice(int *row, int *col, char player) {
    char row_choice;
    gotoxy(0, 1);
    printf("PLAYER %d, SELECT SQUARE:\n", player + 1);
    gotoxy(0, 2);
    scanf(" %c%d", &row_choice, col);
    gotoxy(0, 1);
    printf("                         \n");
    printf("                         \n");

    *row = row_choice - 'a';
    *col -= 1;

    while (*row < 0 || *row >= SIZE || *col < 0 || *col >= SIZE || board[*row][*col] != '\0') {
        gotoxy(0, 1);
        printf("INVALID SQUARE           \n");
        printf("                         \n");
        usleep(2000000);

        gotoxy(0, 1);
        printf("PLAYER %d, SELECT SQUARE:\n", player + 1);
        gotoxy(0, 2);
        scanf(" %c%d", &row_choice, col);
        gotoxy(0, 1);
        printf("                         \n");
        printf("                         \n");
        *row = row_choice - 'a';
        *col -= 1;
    }
}

bool check_winner(char symbol) {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
    }
    // Check columns
    for (int i = 0; i < SIZE; i++) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return true;
        }
    }
    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return true;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return true;
    }

    return false;
}

bool check_draw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '\0') {
                return false; // If any square is empty, it's not a draw
            }
        }
    }
    return true; // All squares are filled without a winner
}

void draw_symbol(int row, int col, char symbol) {
    int cell_size = 7; // Grid cell size
    int grid_size = 3; // 3x3 grid
    int rows = 24, cols = 80;
    int start_row = (rows - (cell_size * grid_size)) / 2;
    int start_col = cols - (cell_size * grid_size + 1);
    int x = (start_col + col * (cell_size * 2) - (cell_size * 2)) - 2;
    int y = start_row + row * cell_size + (cell_size / 2) - 2;
    char command[200];

    if (symbol == 'O') {
        draw_nought(y, x);
    } else {
        draw_cross(y, x);
    }
    snprintf(command, sizeof(command), "aplay samples/learn.wav -q &");
    system(command);
}

void get_player_choice(int *row, int *col, char side) {
    char row_choice;
    gotoxy(0, 1);
    printf("SELECT SQUARE (%c):\n",side);
    gotoxy(0, 2);
    scanf(" %c%d", &row_choice, col);
    gotoxy(0, 1);
    printf("                   \n");
    printf("                   \n");

    *row = row_choice - 'a';
    *col -= 1;

    while (*row < 0 || *row >= SIZE || *col < 0 || *col >= SIZE || board[*row][*col] != '\0') {
        gotoxy(0, 1);
        printf("INVALID SQUARE     \n");
        printf("                   \n");
        usleep(2000000);
        gotoxy(0, 1);
        printf("                   \n");
        printf("                   \n");
        gotoxy(0, 1);
        printf("SELECT SQUARE (%c):\n",side);
        gotoxy(0, 2);
        scanf(" %c%d", &row_choice, col);
        gotoxy(0, 1);
        printf("                   \n");
        printf("                   \n");

        *row = row_choice - 'a';
        *col -= 1;
    }
}

int minimax(char board[SIZE][SIZE], int depth, bool isMax, char computerSide, char playerSide) {
    char winner = '\0';
    if (check_winner(computerSide)) return +10 - depth;
    if (check_winner(playerSide)) return -10 + depth;
    if (check_draw()) return 0;

    if (isMax) {
        int bestVal = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == '\0') {
                    board[i][j] = computerSide;
                    int value = minimax(board, depth + 1, !isMax, computerSide, playerSide);
                    bestVal = (value > bestVal) ? value : bestVal;
                    board[i][j] = '\0'; // Undo move
                }
            }
        }
        return bestVal;
    } else {
        int bestVal = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == '\0') {
                    board[i][j] = playerSide;
                    int value = minimax(board, depth + 1, !isMax, computerSide, playerSide);
                    bestVal = (value < bestVal) ? value : bestVal;
                    board[i][j] = '\0'; // Undo move
                }
            }
        }
        return bestVal;
    }
}

void get_computer_choice(int *row, int *col, char side) {
    int bestVal = -1000;
    int moveRow = -1;
    int moveCol = -1;
    char playerSide = (side == 'X') ? 'O' : 'X';

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '\0') {
                board[i][j] = side;
                int moveVal = minimax(board, 0, false, side, playerSide);
                board[i][j] = '\0'; // Undo move
                if (moveVal > bestVal) {
                    moveRow = i;
                    moveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    *row = moveRow;
    *col = moveCol;
}

int get_number_of_users() {
    int users;
    gotoxy(0, 1);
    printf("PLAYERS (0, 1, or 2):\n");
    gotoxy(0, 2);
    scanf("%d", &users);
    gotoxy(0, 1);
    printf("                     \n");
    printf("                     ");

    while (users < 0 || users > 2) {
        gotoxy(0, 1);
        printf("INVALID OPTION   \n");
        printf("                 ");
        usleep(2000000);
        gotoxy(0, 1);  
        printf("PLAYERS (0, 1, or 2):\n");
        gotoxy(0, 2);
        scanf("%d", &users);
        gotoxy(0, 1);
        printf("                     \n");
        printf("                     ");
    }
    return users;
}

void get_cpu_times(long long *idle, long long *total) {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/stat");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);

    char cpu[10];
    long long user, nice, system, idle_time, iowait, irq, softirq, steal;
    sscanf(buffer, "%s %lld %lld %lld %lld %lld %lld %lld %lld", cpu, &user, &nice, &system, &idle_time, &iowait, &irq, &softirq, &steal);

    *idle = idle_time + iowait;
    *total = user + nice + system + idle_time + iowait + irq + softirq + steal;

    fclose(fp);
}

void monitor_cpu_utilization() {
    char command[200];
    long long prev_idle, prev_total, idle, total;
    get_cpu_times(&prev_idle, &prev_total);
    usleep(5000); // Sleep for 5 milliseconds
    get_cpu_times(&idle, &total);

    long long total_diff = total - prev_total;
    long long idle_diff = idle - prev_idle;

    int current_utilization = 100 * (total_diff - idle_diff) / total_diff;

    if (current_utilization > peak_utilization) {
        peak_utilization = current_utilization;
    }

    gotoxy(0, 19);
    //printf("CPU Utilization: %03d%%\n", current_utilization);
    printf("CPU PEAK UTILIZATION: %03d%%\n", peak_utilization);
    printf("CPU THRESHOLD COUNT : %d\n", cpu_threshold_trigger_count);
    printf("CPU OVERLOAD        : %c\n", cpu_overload);

    if (current_utilization >= previous_utilization + cpu_threshold || peak_utilization >= previous_utilization + cpu_threshold) {
        cpu_threshold_trigger_count=cpu_threshold_trigger_count+1;
        if(cpu_threshold_trigger_count > cpu_threshold_trigger) {      
            cpu_overload = 'Y';
            gotoxy(0, 21);
            printf("CPU OVERLOAD        : %c\n", cpu_overload);
            gotoxy(0, 15);
            printf("\033[31m");
            printf("SYSTEM OVERLOAD\n");
            snprintf(command, sizeof(command), "aplay samples/caught-in-a-loop.wav -q");
            system(command);
            usleep(2000000);
            printf("\033[5m");
            printf("MISSILE SYSTEMS OFF-LINE\n");
            printf("\033[0m");
            gotoxy(0, 23);
            snprintf(command, sizeof(command), "aplay samples/short-circuit-sound.wav -q");
            system(command);
            usleep(5000000);
            exit(1); // check for this condition where this program is called
        }
    }

    previous_utilization = current_utilization;
}

int main() {
    fix_backspace_key();
    int users;
    char player1, player2;
    char command[200];

    start_game:;

    srand(time(NULL));
    clear_screen();
    reset_board();
    draw_grid();

    users = get_number_of_users();

    if (users == 2) {
        player1 = get_side_choice();
        gotoxy(1, 2);
        printf("                                  "); // Print spaces over the previous prompt
        player2 = (player1 == 'X') ? 'O' : 'X';

        int turn = 0;
        while (true) {
            int row, col;
            char side = (turn == 0) ? player1 : player2;

            get_player_choice(&row, &col, side);
            gotoxy(1, 3);
            printf("                                  "); // Print spaces over the previous prompt
            board[row][col] = side;
            draw_symbol(row, col, side);

            if (check_winner(side)) {
                gotoxy(0, 6);
                printf("PLAY %d WINS!\n\n", turn + 1);
                break;
            }

            if (check_draw()) {
                gotoxy(0, 6);
                printf("IT'S A DRAW!\n\n");
                break;
            }

            turn = 1 - turn; // Alternate between players
        }
        char playagain;
        gotoxy(0,23);
        printf("PLAY AGAIN (Y/N): ");
        scanf("%s", &playagain);
        if (playagain == 'Y' || playagain == 'y') {
            goto start_game;
        }
    } else if (users == 1) {
        char playerSide = get_side_choice();
        gotoxy(1, 2);
        printf("                                  "); // Print spaces over the previous prompt
        char computerSide = (playerSide == 'X') ? 'O' : 'X';

        while (true) {
            int row, col;

            get_player_choice(&row, &col, playerSide);
            gotoxy(1, 3);
            printf("                                  "); // Print spaces over the previous prompt
            board[row][col] = playerSide;
            draw_symbol(row, col, playerSide);
            if (check_winner(playerSide)) {
                gotoxy(0, 6);
                printf("PLAYER WINS!\n\n");
                break;
            }
            if (check_draw()) {
                gotoxy(0, 6);
                printf("IT'S A DRAW!\n\n");
                break;
            }

            get_computer_choice(&row, &col, computerSide);
            board[row][col] = computerSide;
            draw_symbol(row, col, computerSide);
            if (check_winner(computerSide)) {
                gotoxy(0, 6);
                printf("COMPUTER WINS PLAYING %c!\n\n", computerSide);
                break;
            }
            if (check_draw()) {
                gotoxy(0, 6);
                printf("IT'S A DRAW!\n\n");
                break;
            }
        }
        char playagain;
        gotoxy(0,23);
        printf("PLAY AGAIN (Y/N): ");
        scanf("%s", &playagain);
        if (playagain == 'Y' || playagain == 'y') {
            goto start_game;
        }
    } else if (users == 0) {
        char sides[2] = {'X', 'O'};
        int turn = 0;
        int game_count = 1;
        int games = 0;
        int move_delay = 2000000;

        gotoxy(0, 1);
        printf("                              ");
        gotoxy(0, 1);
        printf("HOW MANY GAMES: \n");
        gotoxy(0, 2);
        scanf("%d",&games);
        gotoxy(0, 1);
        printf("                              \n");
        printf("                              ");
      
        while(games<=0) {
            gotoxy(0, 1);
            printf("                              ");
            gotoxy(0, 1);
            printf("HOW MANY GAMES (>0): ");
            gotoxy(0, 2);
            scanf("%d",&games);
            gotoxy(0, 1);
            printf("                              \n");
            printf("                              ");
        }

        game_loop:
        reset_board();

        // The random first move
        int randomRow = rand() % 3;  // random number between 0 and 2
        int randomCol = rand() % 3;  // random number between 0 and 2
        board[randomRow][randomCol] = sides[turn];
        draw_symbol(randomRow, randomCol, sides[turn]);
        gotoxy(0, 22);
        fflush(stdout); // flush the output buffer
        usleep(move_delay/game_count);
        turn = 1 - turn;  // Alternate the turn immediately after the first move

        while (true) {
            int row, col;
            char side = sides[turn];

            get_computer_choice(&row, &col, side);
            board[row][col] = side;
            draw_symbol(row, col, side);
            fflush(stdout); // flush the output buffer
            monitor_cpu_utilization();
            usleep(move_delay/game_count);
            
            if (check_winner(side)) {
                gotoxy(0, 5);
                printf("GAME NUMBER: %d\n",game_count);
                printf("COMPUTER PLAYING %c WINS!\n\n", side);
                break;
            }

            if (check_draw()) {
                gotoxy(0, 5);
                printf("GAME NUMBER: %d\n",game_count);
                printf("IT'S A DRAW!\n\n");
                break;
            }

            turn = 1 - turn; // Alternate between the computer playing 'x' and 'o'
        }
        game_count=game_count+1;
        usleep(move_delay/game_count);
        if(game_count < games+1) {
            goto game_loop;
        } else {
            char playagain;
            gotoxy(0,23);
            printf("PLAY AGAIN (Y/N): ");
            scanf("%s", &playagain);
            if (playagain == 'Y' || playagain == 'y') {
                goto start_game;
            }
        }
    }
    gotoxy(0, 23);
    return 0;
}
