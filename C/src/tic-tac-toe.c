#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


#define SIZE 3

char board[SIZE][SIZE]; // Game board

void clear_screen() {
    printf("\033[H\033[J");
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void draw_nought(int row_offset, int col_offset) {
    char nought[7][7] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '#', '#', '#', ' ', ' '},
        {' ', '#', ' ', ' ', ' ', '#', ' '},
        {' ', '#', ' ', ' ', ' ', '#', ' '},
        {' ', '#', ' ', ' ', ' ', '#', ' '},
        {' ', ' ', '#', '#', '#', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            gotoxy(col_offset + j, row_offset + i);
            printf("%c", nought[i][j]);
        }
    }
}

void draw_cross(int row_offset, int col_offset) {
    char cross[7][7] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' ', ' ', '#', ' '},
        {' ', ' ', '#', ' ', '#', ' ', ' '},
        {' ', ' ', ' ', '#', ' ', ' ', ' '},
        {' ', ' ', '#', ' ', '#', ' ', ' '},
        {' ', '#', ' ', ' ', ' ', '#', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            gotoxy(col_offset + j, row_offset + i);
            printf("%c", cross[i][j]);
        }
    }
}

void draw_grid() {
int rows = 24, cols = 80;
    int cell_size = 7; // Grid cell size
    int grid_size = 3; // 3x3 grid

    int start_row = (rows - (cell_size * grid_size)) / 2;
    int start_col = cols - (cell_size * grid_size + 1); // Right-justify the grid

    for (int i = 0; i <= grid_size; i++) {
        gotoxy(start_col, start_row + i * cell_size);
        for (int j = 0; j < cell_size * grid_size; j++) {
            printf("*");
        }
    }

    for (int i = 0; i <= grid_size; i++) {
        for (int j = 0; j < cell_size * grid_size; j++) {
            gotoxy(start_col + i * cell_size, start_row + j);
            printf("*");
        }
    }

    char row_labels[] = {'a', 'b', 'c'};
    for (int row = 0; row < grid_size; row++) {
        for (int col = 1; col <= grid_size; col++) {
            int x = start_col + (col - 1) * cell_size + (cell_size / 2);
            int y = start_row + row * cell_size + cell_size - 1;
            gotoxy(x - 1, y);
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
    printf("Choose your side (x/o): ");
    scanf(" %c", &side);

    while (side != 'x' && side != 'o') {
        gotoxy(0, 1);
        printf("Invalid choice! Choose your side (x/o): ");
        scanf(" %c", &side);
    }
    
    return side;
}

void get_grid_choice(int *row, int *col, char player) {
    char row_choice;
    gotoxy(0, 3 + player);
    printf("Player %d, choose grid square (e.g., a1): ", player + 1);
    scanf(" %c%d", &row_choice, col);
    gotoxy(0, 7);
    printf("                              ");

    *row = row_choice - 'a';
    *col -= 1;

    while (*row < 0 || *row >= SIZE || *col < 0 || *col >= SIZE || board[*row][*col] != '\0') {
        gotoxy(0, 3 + player);
        printf("Invalid square! Player %d, choose grid square (e.g., a1): ", player + 1);
        gotoxy(0, 7);
        printf("                              ");
        scanf(" %c%d", &row_choice, col);
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
    int x = start_col + col * cell_size + (cell_size / 2) - 2;
    int y = start_row + row * cell_size + (cell_size / 2) - 2;

    if (symbol == 'o') {
        draw_nought(y, x);
    } else {
        draw_cross(y, x);
    }
}

void get_player_choice(int *row, int *col, char side) {
    char row_choice;
    gotoxy(0, 5);
    printf("Choose grid square (e.g., a1): ");
    scanf(" %c%d", &row_choice, col);
    gotoxy(0, 7);
    printf("                              ");

    *row = row_choice - 'a';
    *col -= 1;

    while (*row < 0 || *row >= SIZE || *col < 0 || *col >= SIZE || board[*row][*col] != '\0') {
        gotoxy(0, 5);
        printf("Invalid square! Choose grid square (e.g., a1): ");
        scanf(" %c%d", &row_choice, col);
        gotoxy(1, 7);
        printf("                              ");
        *row = row_choice - 'a';
        *col -= 1;
    }
}

void get_computer_choice(int *row, int *col, char side) {
    do {
        *row = rand() % SIZE;
        *col = rand() % SIZE;
    } while (board[*row][*col] != '\0');
}

int get_number_of_users() {
    int users;
    gotoxy(0, 1);
    printf("Enter number of users (0, 1, or 2): ");
    scanf("%d", &users);

    while (users < 0 || users > 2) {
        gotoxy(0, 1);
        printf("Invalid number! Enter number of users (0, 1, or 2): ");
        scanf("%d", &users);
    }
    return users;
}

int main() {
    int users;
    char player1, player2;
    char command[200];

    srand(time(NULL));
    clear_screen();
    draw_grid();

    users = get_number_of_users();
    gotoxy(1, 1);
    printf("                                        "); // Print spaces over the previous prompt

    if (users == 2) {
        player1 = get_side_choice();
        gotoxy(1, 2);
        printf("                                        "); // Print spaces over the previous prompt
        player2 = (player1 == 'x') ? 'o' : 'x';

        int turn = 0;
        while (true) {
            int row, col;
            char side = (turn == 0) ? player1 : player2;

            get_player_choice(&row, &col, side);
            gotoxy(1, 3);
            printf("                                        "); // Print spaces over the previous prompt
            board[row][col] = side;
            draw_symbol(row, col, side);

            if (check_winner(side)) {
                gotoxy(0, 6);
                printf("Player %d wins!\n\n", turn + 1);
                break;
            }

            if (check_draw()) {
                gotoxy(0, 6);
                printf("It's a draw!\n\n");
                break;
            }

            turn = 1 - turn; // Alternate between players
        }
    } else if (users == 1) {
        char playerSide = get_side_choice();
        gotoxy(1, 2);
        printf("                                        "); // Print spaces over the previous prompt
        char computerSide = (playerSide == 'x') ? 'o' : 'x';

        while (true) {
            int row, col;

            get_player_choice(&row, &col, playerSide);
            gotoxy(1, 3);
            printf("                                        "); // Print spaces over the previous prompt
            board[row][col] = playerSide;
            draw_symbol(row, col, playerSide);
            if (check_winner(playerSide)) {
                gotoxy(0, 6);
                printf("Player wins!\n\n");
                break;
            }
            if (check_draw()) {
                gotoxy(0, 6);
                printf("It's a draw!\n\n");
                break;
            }

            get_computer_choice(&row, &col, computerSide);
            board[row][col] = computerSide;
            draw_symbol(row, col, computerSide);
            if (check_winner(computerSide)) {
                gotoxy(0, 6);
                printf("Computer wins playing %c!\n\n", computerSide);
                break;
            }
            if (check_draw()) {
                gotoxy(0, 6);
                printf("It's a draw!\n\n");
                break;
            }
        }
    } else if (users == 0) {
        char sides[2] = {'x', 'o'};
        int turn = 0;
        int game_count = 1;
        int games = 0;
        int move_delay = 2000000;

        gotoxy(0, 1);
        printf("                              ");
        gotoxy(0, 1);
        printf("How Many Games: ");
        scanf("%d",&games);
        game_start:
        reset_board();

        while (true) {
            int row, col;
            char side = sides[turn];

            get_computer_choice(&row, &col, side);
            board[row][col] = side;
            draw_symbol(row, col, side);
            snprintf(command, sizeof(command), "aplay samples/learn.wav -q &");
            system(command);
            fflush(stdout); // flush the output buffer
            usleep(move_delay/game_count);
            
            if (check_winner(side)) {
                gotoxy(0, 5);
                printf("Game Number: %d\n",game_count);
                printf("Computer playing %c wins!\n\n", side);
                break;
            }

            if (check_draw()) {
                gotoxy(0, 5);
                printf("Game Number: %d\n",game_count);
                printf("It's a draw!\n\n");
                break;
            }

            turn = 1 - turn; // Alternate between the computer playing 'x' and 'o'
        }
        game_count=game_count+1;
        usleep(move_delay/game_count);
        if(game_count < games+1) {
            goto game_start;
        }
    }

    return 0;
}