//Wargames Movie Simulator
//Written by Andy Glenn
//(c) 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <ncurses.h>
#include <termios.h>

#define CHARACTER_DELAY 5000  // 1000 = 1ms
#define MAX_TARGETS 4
#define MAX_STRING_LENGTH 20

// Struct for user data
typedef struct {
    char username[100];
    char password[100];
    char name[100];
    int access_level;
    char last_logon[100];
} User;

int game_running = 0;
int defcon = 5;

void delayed_print(const char* str) {
    //char command[200];
    for (int i = 0; str[i]; i++) {
        putchar(str[i]);
        fflush(stdout);
        //snprintf(command, sizeof(command), "aplay samples/phone-beep.wav -q &");
        //system(command);
        usleep(CHARACTER_DELAY);
    }
}

void not_delayed_print(const char* str) {
    for (int i = 0; str[i]; i++) {
        putchar(str[i]);
        fflush(stdout);
        usleep(500);
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clear_screen() {
    printf("\033[2J\033[H");
}

void author() {
    int asciiValues[] = {65, 78, 68, 89, 32, 71, 76, 69, 78, 78};
    int i;
    char command[200];

    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);

    printf("\n");
    for(i = 0; i < 10; i++) {
        printf("%c", asciiValues[i]);
    }
    printf("\n\n");
}

const char *check_status_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (!file) {
        // If the file doesn't exist, create it with default content "enabled"
        file = fopen(filename, "w");
        if (!file) {
            perror("Error creating file");
            return "error";
        }
        fprintf(file, "enabled");
        fclose(file);
        
        // Return the default status
        return "enabled";
    }

    char status[10];  // enough to hold "enabled" or "disabled" and a null terminator
    if (fscanf(file, "%9s", status) != 1) {
        fclose(file);
        return "error";
    }

    fclose(file);

    if (strcmp(status, "enabled") == 0) {
        return "enabled";
    } else if (strcmp(status, "disabled") == 0) {
        return "disabled";
    } else {
        return "error";
    }
}

int set_status_to_file(const char *filename, int status_input) {
    const char *status;
    if (status_input == 0) {
        status = "disabled";
    } else if (status_input == 1) {
        status = "enabled";
    } else {
        fprintf(stderr, "Invalid input: %d\n", status_input);
        return -1;  // Return an error code
    }

    // Open the file for writing, which will create it if it doesn't exist
    // or overwrite its content if it does.
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Unable to open file for writing");
        return -1;  // Return an error code
    }

    fprintf(file, "%s", status);
    fclose(file);

    return 0;  // Successful write
}

void help_games() {
    char command[200];
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    delayed_print("\n'GAMES' REFERS TO MODELS, SIMULATIONS, AND GAMES WHICH HAVE TACTICAL AND\nSTRATEGIC APPLICATIONS\n\n");
    //snprintf(command, sizeof(command), "espeak 'GAMES REFERS TO MODELS, SIMULATIONS, AND GAMES WHICH HAVE TACTICAL AND STRATEGIC APPLICATIONS'");
    //system(command);
}

void list_games() {
    char command[200];
    delayed_print("\nFALKEN'S MAZE\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'FALKENS MAZE'");
    //system(command);
    delayed_print("BLACK JACK\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'BLACK JACK'");
    //system(command);
    delayed_print("GIN RUMMY\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'GIN RUMMY'");
    //system(command);
    delayed_print("HEARTS\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'HEARTS'");
    //system(command);
    delayed_print("BRIDGE\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'BRIDGE'");
    //system(command);
    delayed_print("CHECKERS\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'CHECKERS'");
    //system(command);
    delayed_print("CHESS\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'CHESS'");
    //system(command);
    delayed_print("POKER\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'POKER'");
    //system(command);
    delayed_print("FIGHTER COMBAT\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'FIGHTER COMBAT'");
    //system(command);
    delayed_print("GUERRILLA ENGAGEMENT\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'GUERRILLA ENGAGEMENT'");
    //system(command);
    delayed_print("DESERT WARFARE\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'DESERT WARFARE'");
    //system(command);
    delayed_print("AIR-TO-GROUND ACTIONS\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //nprintf(command, sizeof(command), "espeak 'AIR-TO-GROUND ACTIONS'");
    //system(command);
    delayed_print("THEATERWIDE TACTICAL WARFARE\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'THEATERWIDE TACTICAL WARFARE'");
    //system(command);
    delayed_print("THEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'THEATERWIDE BIOTOXIC AND CHEMICAL WARFARE'");
    //system(command);
    usleep(500000);
    delayed_print("\nGLOBAL THERMONUCLEAR WAR\n\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'GLOBAL THERMONUCLEAR WAR'");
    //system(command);
}

void manageUsers() {
    int choice;
    char inputBuffer[256];

    while (1) {
        printf("\n");
        printf("1. Create User\n2. Amend User\n3. Delete User\n4. List Users\nEnter choice (or press Enter to exit): ");
        
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        if (sscanf(inputBuffer, "%d", &choice) != 1) {
            break;  // Break out of the loop if no valid number is provided
        }

        FILE* file;
        User tempUser;
        char inputUsername[100];

        switch (choice) {
            case 1:
                file = fopen("users.txt", "a");
                if (!file) {
                    printf("Error opening or creating users.txt!\n");
                    return;
                }
                printf("Enter username: ");
                fgets(tempUser.username, sizeof(tempUser.username), stdin);
                strtok(tempUser.username, "\n");
                
                printf("Enter password: ");
                fgets(tempUser.password, sizeof(tempUser.password), stdin);
                strtok(tempUser.password, "\n");
                
                printf("Enter name: ");
                fgets(tempUser.name, sizeof(tempUser.name), stdin);
                strtok(tempUser.name, "\n");
                
                printf("Enter access level: ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                sscanf(inputBuffer, "%d", &tempUser.access_level);

                strcpy(tempUser.last_logon, "Never");

                fprintf(file, "%s\n%s\n%s\n%d\n%s\n", tempUser.username, tempUser.password, tempUser.name, 
                        tempUser.access_level, tempUser.last_logon);

                fclose(file);
                printf("User created successfully.\n");
                break;

            case 2:
                file = fopen("users.txt", "r");
                if (!file) {
                    printf("users.txt not found. Create a user first.\n");
                    return;
                }
                printf("Enter username to amend: ");
                fgets(inputUsername, sizeof(inputUsername), stdin);
                strtok(inputUsername, "\n");

                FILE* tempFile = fopen("temp.txt", "w");
                if (!tempFile) {
                    printf("Error creating temp file!\n");
                    fclose(file);
                    return;
                }
                
                int amended = 0;
                while (fscanf(file, "%s\n%s\n%s\n%d\n%s\n", tempUser.username, tempUser.password, tempUser.name, 
                        &tempUser.access_level, tempUser.last_logon) != EOF) {
                    if (strcmp(tempUser.username, inputUsername) == 0) {
                        printf("Enter new password: ");
                        fgets(tempUser.password, sizeof(tempUser.password), stdin);
                        strtok(tempUser.password, "\n");
                        
                        printf("Enter new name: ");
                        fgets(tempUser.name, sizeof(tempUser.name), stdin);
                        strtok(tempUser.name, "\n");
                        
                        printf("Enter new access level: ");
                        fgets(inputBuffer, sizeof(inputBuffer), stdin);
                        sscanf(inputBuffer, "%d", &tempUser.access_level);

                        amended = 1;
                    }
                    fprintf(tempFile, "%s\n%s\n%s\n%d\n%s\n", tempUser.username, tempUser.password, tempUser.name, 
                            tempUser.access_level, tempUser.last_logon);
                }

                fclose(file);
                fclose(tempFile);
                remove("users.txt");
                rename("temp.txt", "users.txt");

                if (amended) {
                    printf("User amended successfully.\n");
                } else {
                    printf("User not found.\n");
                }
                break;

            case 3:
                file = fopen("users.txt", "r");
                if (!file) {
                    printf("users.txt not found. Create a user first.\n");
                    return;
                }
                printf("Enter username to delete: ");
                fgets(inputUsername, sizeof(inputUsername), stdin);
                strtok(inputUsername, "\n");

                FILE* delFile = fopen("delete.txt", "w");
                if (!delFile) {
                    printf("Error creating delete file!\n");
                    fclose(file);
                    return;
                }

                int deleted = 0;
                while (fscanf(file, "%s\n%s\n%s\n%d\n%s\n", tempUser.username, tempUser.password, tempUser.name, 
                        &tempUser.access_level, tempUser.last_logon) != EOF) {
                    if (strcmp(tempUser.username, inputUsername) != 0) {
                        fprintf(delFile, "%s\n%s\n%s\n%d\n%s\n", tempUser.username, tempUser.password, tempUser.name, 
                                tempUser.access_level, tempUser.last_logon);
                    } else {
                        deleted = 1;
                    }
                }

                fclose(file);
                fclose(delFile);
                remove("users.txt");
                if (deleted) {
                    rename("delete.txt", "users.txt");
                    printf("User deleted successfully.\n");
                } else {
                    remove("delete.txt");
                    printf("User not found.\n");
                }
                break;

            case 4:
                file = fopen("users.txt", "r");
                if (!file) {
                    printf("users.txt not found. Create a user first.\n");
                    return;
                }
                printf("\nList of Users:\n");
                printf("-------------------------------------------------\n");
                printf("| %-10s | %-15s | %-15s |\n", "Username", "Name", "Access Level");
                printf("-------------------------------------------------\n");
                while (fscanf(file, "%s\n%s\n%s\n%d\n%s\n", tempUser.username, tempUser.password, tempUser.name, 
                        &tempUser.access_level, tempUser.last_logon) != EOF) {
                    printf("| %-10s | %-15s | %-15d |\n", tempUser.username, tempUser.name, tempUser.access_level);
                }
                printf("-------------------------------------------------\n");
                fclose(file);
                break;

            default:
                printf("Invalid choice. Exiting...\n");
                return;  // Exit the function
        }
    }
    printf("\n");
}

void logged_on_user(User user) {
    char command[200];
    char buffer[500]; // Buffer to hold formatted output
    char input[100];
    
    clear_screen();
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    delayed_print("TRZ. 34/53/76               SYS PROC 3435.45.6456           XCOMP STATUS: PV-456\n");
    delayed_print("ACTIVE PORTS: 34,53,75,94                                     CPU TM USED: 23:43\n");
    delayed_print("#45/34/53.           ALT MODE FUNCT: PV-8-AY345              STANDBY MODE ACTIVE\n");
    delayed_print("#543.654      #989.283       #028.392       #099.293      #934.905      #261.372\n");
    delayed_print("\n");

    sprintf(buffer, "USER         : %s\n", user.username);
    delayed_print(buffer);

    sprintf(buffer, "NAME         : %s\n", user.name);
    delayed_print(buffer);
    
    sprintf(buffer, "ACCESS LEVEL : %d\n", user.access_level);
    delayed_print(buffer);

    delayed_print("\n");
    
    while(1) {
        delayed_print("> ");
        fgets(input, sizeof(input), stdin);
        
        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // If user just pressed Enter (carriage return)
        if (input[0] == '\0') {
            continue; // Go back to the start of the while loop
        }

        // Convert input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }
        
        // Check commands
        if (strcmp(input, "help games") == 0) {
            help_games();
        }
        else if (strcmp(input, "list games") == 0) {
            list_games();
        }
        else if (strcmp(input, "author") == 0) {
            author();
        }
        else if (strcmp(input, "whoami") == 0) {
            delayed_print("\nUSER: ");
            printf("%s",user.username);
            delayed_print("\n\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
        }
        else if (strcmp(input, "defcon") == 0) {
            delayed_print("\nDEFCON: ");
            printf("%d",defcon);
            delayed_print("\n\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
        }
        else if (strcmp(input, "cls") == 0) {
            clear_screen();
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            delayed_print("TRZ. 34/53/76               SYS PROC 3435.45.6456           XCOMP STATUS: PV-456\n");
            delayed_print("ACTIVE PORTS: 34,53,75,94                                     CPU TM USED: 23:43\n");
            delayed_print("#45/34/53.           ALT MODE FUNCT: PV-8-AY345              STANDBY MODE ACTIVE\n");
            delayed_print("#543.654      #989.283       #028.392       #099.293      #934.905      #261.372\n");
            delayed_print("\n");
        }
        else if (strcmp(input, "users") == 0) {
            if (user.access_level == 2) {
                manageUsers();
            } else {
                snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
                system(command);
                delayed_print("\nPERMISSION DENIED. INSUFFICIENT ACCESS LEVEL.\n\n");
            }
           
        }
        else if (strcmp(input, "backdoor") == 0) {
            if (user.access_level == 2) {
                char buffer[10];
                int user_input;
                snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
                system(command);
                delayed_print("\nSET STATUS (0 = DISABLED, 1 = ENABLED): ");
                fgets(buffer, sizeof(buffer), stdin);
                
                // Convert the string to an integer
                user_input = atoi(buffer);

                if (set_status_to_file("joshua.txt", user_input) != 0) {
                    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
                    system(command);
                    delayed_print("ERROR SETTING STATUS.\n\n");
                } else {
                    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
                    system(command);
                    delayed_print("STATUS UPDATED.\n\n");
                }
            } else {
                snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
                system(command);
                delayed_print("\nPERMISSION DENIED. INSUFFICIENT ACCESS LEVEL.\n\n");
            }
           
        }
        else if (strcmp(input, "exit") == 0) {
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            delayed_print("\nLOGGING OUT OF SESSION\n--CONNECTION TERMINATED--\n");
            usleep(1000000);
            exit(0);
        }
        else {
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("\nINVALID COMMAND\n\n");
        }
    }
}

void getPassword(char* password, size_t size) {
    struct termios old, new;
    int n = 0;
    char ch;

    // Disable buffering for terminal I/O so the PASS key is available.
    setvbuf(stdin, NULL, _IONBF, 0); 

    // Disable echo
    tcgetattr(fileno(stdin), &old);
    new = old;
    new.c_lflag &= ~(ECHO | ICANON);  // Disable echo and buffered input
    new.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSAFLUSH, &new) != 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    printf("PASSWORD: ");
    
    // Read characters one by one, mask them with '*', and store in password array
    while (n < size - 1) {
        ch = getchar();
        if(ch == '\n')
            break;
        putchar('*');
        password[n] = ch;
        n++;
    }
    password[n] = '\0';  // Null terminate the string

    // Restore terminal
    (void) tcsetattr(fileno(stdin), TCSAFLUSH, &old);
}

void authenticateUser(char* username) {
    char inputPassword[100];
    FILE* file = fopen("users.txt", "r");
    if (!file) {
        printf("users.txt not found. Ensure a user exists.\n");
        return;
    }

    User tempUser;

    getPassword(inputPassword, sizeof(inputPassword));

    int authenticated = 0;
    while (fscanf(file, "%99s\n%99s\n%99s\n%d\n%99s\n", tempUser.username, tempUser.password, tempUser.name, 
            &tempUser.access_level, tempUser.last_logon) != EOF) {
        if (strcmp(tempUser.username, username) == 0 && strcmp(tempUser.password, inputPassword) == 0) {
            authenticated = 1;
            break;
        }
    }
    fclose(file);

    if (authenticated) {
        printf("\nUSER AUTHENTICATION SUCCESSFUL\n");
        usleep(1000000);
        logged_on_user(tempUser); // Call this function if authenticated
    }
}

void guesscode() {
    char LC[] = "CPE1704TKS";
    int LC_percent = 0;
    char buffer[200];
    char command[200];
    char input[100];

    srand(time(0)); // Initialize random seed

    int row = 10; // Desired row position
    int col = 32; // Desired column position

    clear_screen();
    delayed_print("\033[7mTERMINAL ECHO: WAR ROOM\033[0m\n");

    for (int A = 1; A <= strlen(LC); A++) {
        int LCG;
        do {
            printf("\033[%d;%dH", row, col);
            for (int B = 1; B <= LC_percent; B++) printf("%c ", LC[B - 1]);
            for (int B = 1; B <= strlen(LC) - LC_percent; B++) printf("- ");
            printf("\n");

            LCG = (rand() % (90 - 48 + 1)) + 48;
            if (LCG > 57 && LCG < 65) continue;

            printf("\033[%d;%dH", row, col);
            for (int B = 1; B <= LC_percent; B++) printf("%c ", LC[B - 1]);
            printf("%c ", (char)LCG);
                        for (int B = 1; B <= strlen(LC) - LC_percent - 1; B++) printf("- ");
            printf("\n");

            usleep(250 * 1000); // delay
        } while ((char)LCG != LC[A - 1]);
        snprintf(command, sizeof(command), "aplay samples/number-locked-in.wav -q &");
        system(command);
        LC_percent++;
    }
    usleep(2000000);
    clear_screen();
    delayed_print("\033[7mTERMINAL ECHO: WAR ROOM\033[0m\n");
    sprintf(buffer, "\033[%d;%dH%s", 10, 32, "\033[5mC P E 1 7 0 4 T K S\033[0m");        
    delayed_print(buffer);
    usleep(10000000);
    sprintf(buffer, "\033[%d;%dH%s", 23, 28, "PRESS ENTER KEY TO CONTINUE\n");
    delayed_print(buffer);

    while(1) {        
        char selection[3]; // to accommodate the character, the '\n', and the null-terminating character
        fgets(selection, sizeof(selection), stdin); // Read user's selection

        // If user just pressed Enter, break the outer loop
        if(selection[0] == '\n' && selection[1] == '\0') {
            break;
        }
    }
    clear_screen();
    snprintf(command, sizeof(command), "./tic-tac-toe");
    int status = system(command); // Only call system(command) once
    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        if (exit_status == 1) {
            //printf("The tic-tac-toe program exited with status 1\n");
            clear_screen();
            fflush(stdout); // flush the output buffer
            usleep(10000000);
            delayed_print("GREETINGS PROFESSOR FALKEN\n\n");
            snprintf(command, sizeof(command), "aplay samples/greetings.wav -q");
            system(command);
            fgets(input, sizeof(input), stdin);
            // Remove trailing newline character
            input[strcspn(input, "\n")] = '\0';
            // Convert input to lowercase
            for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
            }
            //optionally, do something with the input - but not necessary
            delayed_print("\nA STRANGE GAME. ");
            snprintf(command, sizeof(command), "aplay samples/a-strange-game.wav -q");
            system(command);
            usleep(500000);
            delayed_print("THE ONLY WINNING MOVE IS NOT TO PLAY!\n\n");
            snprintf(command, sizeof(command), "aplay samples/the-only-winning-move-is-not-to-play.wav -q");
            system(command);
            usleep(5000000);
            delayed_print("HOW ABOUT A NICE GAME OF CHESS?\n\n");
            snprintf(command, sizeof(command), "aplay samples/how-about-a-nice-game-of-chess.wav -q");
            system(command);
            defcon=5;
            game_running = 0;
        } else {
            //printf("The tic-tac-toe program exited with status %d\n", exit_status);
            clear_screen();
            fflush(stdout); // flush the output buffer
            usleep(10000000);
            delayed_print("\nYOU FAILED TO PREVENT WOPR FROM LAUNCHING THE MISSILES. ");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q");
            system(command);
            usleep(500000);
            delayed_print("WWIII HAS COMMENCED!\n\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
            system(command);
            usleep(5000000);
            defcon=1;
        }
    }
}

void map() {
    char command[200];
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    
    clear_screen();

    delayed_print("\n");
    delayed_print("     ____________/\\'--\\__         __                       ___/-\\             \n");
    delayed_print("   _/                   \\     __/  |          _     ___--/      / __          \n");
    delayed_print("  /                      |   /    /          / \\__--           /_/  \\/---\\    \n");
    delayed_print("  |                       \\_/    /           \\                            \\   \n");
    delayed_print("  |'                            /             |                            |  \n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    delayed_print("   \\                           |            /^                             /  \n");
    delayed_print("    \\__                       /            |                          /---/   \n");
    delayed_print("       \\__                   /              \\              ___    __  \\       \n");
    delayed_print("          \\__     ___    ___ \\               \\_           /   \\__/  /_/       \n");
    delayed_print("              \\  /    \\_/   \\ \\                \\__'-\\    /                    \n");
    delayed_print("               \\/            \\/                      \\__/                     \n");
    delayed_print("\n");

    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    delayed_print("          UNITED STATES                               SOVIET UNION\n\n");

}

void end_game() {
    int gte = 50;
    int etr = 10;
    char buffer[200];
    char command[200];

    for(int gc = 1; gc <= 10; gc++) {
        gte += 1;
        etr -= 1;

        if(gte == 60) {
            gte=0;
        }

        clear_screen();

        sprintf(buffer, "\033[%d;%dH%s", 19, 1, "--------------------------------------------------------------------------------");
        delayed_print(buffer);
        sprintf(buffer, "\033[%d;%dH%s", 20, 1, "GAME TIME ELAPSED");
        delayed_print(buffer);
        sprintf(buffer, "\033[%d;%dH%s", 20, 56, "ESTIMATED TIME REMAINING");
        delayed_print(buffer);

        if(gte >0) {
            sprintf(buffer, "\033[%d;%dH%s", 21, 1, "01 HRS 59 MIN");

        } else {
            sprintf(buffer, "\033[%d;%dH%s", 21, 1, "02 HRS 00 MIN");
        }
        delayed_print(buffer);
        printf(" SEC %02d", gte);

        sprintf(buffer, "\033[%d;%dH%s", 21, 56, "28 HRS 00 MIN");        
        delayed_print(buffer);
        printf(" SEC %02d", etr);

        sprintf(buffer, "\033[%d;%dH%s", 22, 1, "--------------------------------------------------------------------------------");
        delayed_print(buffer);

        snprintf(command, sizeof(command), "aplay samples/estimated-time-remaining.wav -q &");
        system(command);

        usleep(1000000);
    }
    usleep(2000000);
    clear_screen();
    delayed_print("\033[7mTERMINAL ECHO: WAR ROOM\033[0m\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    delayed_print("TRZ. 34/53/76               SYS PROC 3435.45.6456           XCOMP STATUS: PV-456\n");
    delayed_print("ACTIVE PORTS: 34,53,75,94                                     CPU TM USED: 23:43\n");
    delayed_print("#45/34/53.           ALT MODE FUNCT: PV-8-AY345              STANDBY MODE ACTIVE\n");
    delayed_print("#543.654      #989.283       #028.392       #099.293      #934.905      #261.372\n");
    delayed_print("\n");

    delayed_print("                         MISSILES TARGETED AND READY\n");
    delayed_print("                         ---------------------------\n\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    usleep(1000000);
    delayed_print("\033[5m                             CHANGES LOCKED OUT\033[0m\n");
    delayed_print("                             ------------------\n"); 
    snprintf(command, sizeof(command), "aplay samples/buzzer-sounds.wav -q &");
    system(command);
    usleep(3000000);

    defcon=1;

    usleep(5000000);
    clear_screen();
    delayed_print("\033[7mTERMINAL ECHO: WAR ROOM\033[0m\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    delayed_print("TRZ. 34/53/76               SYS PROC 3435.45.6456           XCOMP STATUS: PV-456\n");
    delayed_print("ACTIVE PORTS: 34,53,75,94                                     CPU TM USED: 23:43\n");
    delayed_print("#45/34/53.           ALT MODE FUNCT: PV-8-AY345              STANDBY MODE ACTIVE\n");
    delayed_print("#543.654      #989.283       #028.392       #099.293      #934.905      #261.372\n");
    delayed_print("\n");

    delayed_print("                            PRIMARY TARGET IMPACT\n");
    delayed_print("                            ---------------------\n\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    usleep(1000000);

    delayed_print("                    LORING AIRFORCE BASE      : ");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    usleep(1000000);
    delayed_print("NO IMPACT\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
    system(command);
    usleep(1000000);

    delayed_print("                    ELMENDORF AIRFORCE BASE   : ");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    usleep(1000000);
    delayed_print("NO IMPACT\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
    system(command);
    usleep(1000000);

    delayed_print("                    GRAND FORKS AIRFORCE BASE : ");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    usleep(1000000);
    delayed_print("NO IMPACT\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
    system(command);
    usleep(1000000);

    usleep(10000000);
    guesscode();
    
    //rest of game goes here
    //this should include: Joshua searching/finding launch codes
    //tic-tac-toe sequence

}

void global_thermonuclear_war() {
    char command[200];
    int count = 0;
    char side[20];  // Array to store the selected side
    char input;
    int col=0; //print at col
    int row=0; //print at row
    int t;
    char buffer[200];
    char* prompt = "";
    startgame:
    clear_screen();
    map();
    delayed_print("WHICH SIDE DO YOU WANT?\n\n");
    if(count == 0) {
        //snprintf(command, sizeof(command), "espeak 'WHICH SIDE DO YOU WANT?'");
        snprintf(command, sizeof(command), "aplay samples/which-side-do-you-want.wav -q");
        system(command);
        delayed_print("  1. UNITED STATES\n");
        delayed_print("  2. SOVIET UNION\n\n");
        delayed_print("PLEASE CHOOSE ONE: ");
        
        scanf(" %c", &input);
        
        if (input == '1') {
            strcpy(side, "UNITED STATES");
        } else if (input == '2') {
            strcpy(side, "SOVIET UNION");
        } else {
            delayed_print("\nINVALID OPTION\n\n");
            usleep(5000000);
        }
        count=count+1;
        goto startgame;
        
    } else {
        if (input == '1') {
            delayed_print("\033[5m  1. UNITED STATES\033[0m\n");
            delayed_print("  2. SOVIET UNION\n\n");
        } else {
            delayed_print("  1. UNITED STATES\n"); 
            delayed_print("\033[5m  2. SOVIET UNION\033[0m\n\n");   
        }
    }
    
   
    clear_input_buffer();
    // Rest of the game code goes here: start
    delayed_print("YOU HAVE SELECTED: ");
    delayed_print(side);
    usleep(2500000);
    clear_screen ();
    usleep(2500000);
    delayed_print("\033[4mAWAITING FIRST STRIKE COMMAND\033[24m\n\n");
    delayed_print("PLEASE LIST PRIMARY TARGETS BY\n");
    delayed_print("CITY AND/OR COUNTY NAME:\n\n");
    //snprintf(command, sizeof(command), "espeak 'PLEASE LIST PRIMARY TARGETS'");
    snprintf(command, sizeof(command), "aplay samples/please-list-primary-targets.wav -q");
    system(command);
    
    //while loop to input targets goes here
    char targets[MAX_TARGETS][MAX_STRING_LENGTH];
    count = 0;
    while(count < MAX_TARGETS) {
        if(fgets(targets[count], MAX_STRING_LENGTH, stdin) == NULL) {
            break;
        }

        // Remove the newline character at the end of the string
        targets[count][strcspn(targets[count], "\n")] = 0;

        // Check for empty string (i.e., carriage return)
        if(strlen(targets[count]) == 0) {
            break;
        }

        count++;
    }

    //delayed_print("\n\nMAX TARGETS SELECTED");
    delayed_print("\nTARGET SELECTION COMPLETE\n\n");
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    //snprintf(command, sizeof(command), "espeak 'TARGET SELECTION COMPLETE'");
    //system(command);
    usleep(2500000);

    while(1) {
        map();
        delayed_print("\033[4mPRIMARY TARGETS\033[24m\n");
        for (int i = 0; i < count; i++) {
            for (int j = 0; targets[i][j] != '\0'; j++) {
                putchar(toupper(targets[i][j]));
                usleep(CHARACTER_DELAY);
            }
            usleep(1000000);
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            printf("\n");
        }
        usleep(1000000);
        snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
        system(command);
        delayed_print("\nCOMMAND (L = LAUNCH): ");
        scanf(" %c", &input);
        clear_input_buffer();
        if (input == 'l' || input == 'L') {
            usleep(2000000);
            defcon=3;
            break;
        }
    }
       
    map();
    usleep(1000000);
    delayed_print("\033[4mTRAJECTORY HEADING\033[24m");
    delayed_print("   ");
    fflush(stdout); // flush the output buffer
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
    system(command);
    usleep(500000);
    delayed_print("\033[4mTRAJECTORY HEADING\033[24m");
    delayed_print("  ");
    fflush(stdout); // flush the output buffer
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
    system(command);
    usleep(500000);
    delayed_print("\033[4mTRAJECTORY HEADING\033[24m");
    delayed_print("   ");
    fflush(stdout); // flush the output buffer
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
    system(command);
    usleep(500000);
    delayed_print("\033[4mTRAJECTORY HEADING\033[24m");
    delayed_print("\n");
    fflush(stdout); // flush the output buffer
    snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
    system(command);
    usleep(2000000);
   
    for (int t = 0; t < count; t++) {
        if(t == 0) {
            sprintf(buffer, "\033[%d;%dH%s", 17, 1, "A-5520-A 939 523");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 10, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }
            
            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 62, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 18, 1, "       B 664 295");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 11, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 62, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            } 

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

          
            sprintf(buffer, "\033[%d;%dH%s", 19, 1, "       C 125 386");
            delayed_print(buffer);
            
            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 12, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }
            
            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 61, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }    

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 20, 1, "       D 768 347");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 13, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 60, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 21, 1, "       E 463 284");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 14, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }


            if (strstr(side, "SOVIET UNION") != NULL) {
                delayed_print(buffer);
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 59, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);
        }

        if(t == 1) {
            sprintf(buffer, "\033[%d;%dH%s", 17, 22, "B-5520-A 243 587");
            delayed_print(buffer);
            
            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 10+5, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 62-5, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }
            
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 18, 22, "       B 892 754");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 11+5, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 62-5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 19, 22, "       C 374 256");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 12+5, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 61-5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 20, 22, "       D 364 867");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 13+5, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 60-5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 21, 22, "       E 463 284");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 14+5, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 59-5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);
        }


        if(t == 2) {
            sprintf(buffer, "\033[%d;%dH%s", 17, 42, "C-5520-A 398 984");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 10+10, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 62-10, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 18, 42, "       B 394 345");
            delayed_print(buffer);
            
            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 11+10, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 62-10, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 19, 42, "       C 407 340");
            delayed_print(buffer);


            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 12+10, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 61-10, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 20, 42, "       D 251 953");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 13+10, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }


            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 60-10, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }


            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 21, 42, "       E 093 684");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 14+10, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 59-10, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);
        }

        if(t == 3) {
            sprintf(buffer, "\033[%d;%dH%s", 17, 63, "D-5520-A 919 437");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 10+15, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }
            
            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 62+5, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 18, 63, "       B 132 147");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 11+15, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 62+5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 19, 63, "       C 095 485");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 12+15, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 61+5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 20, 63, "       D 489 794");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 13+15, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
             printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 60+5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 21, 63, "       E 025 344");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 14+15, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 59+5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);
        }
    } 
    usleep(5000000);

    sprintf(buffer, "\033[%d;%dH%s", 23, 28, "PRESS ENTER KEY TO CONTINUE\n");
    delayed_print(buffer);

    while(1) {        
        char selection[3]; // to accommodate the character, the '\n', and the null-terminating character
        fgets(selection, sizeof(selection), stdin); // Read user's selection

        // If user just pressed Enter, break the outer loop
        if(selection[0] == '\n' && selection[1] == '\0') {
            break;
        }
    }
    
    game_running = 1;
    clear_screen();
    usleep(1000000);
    snprintf(command, sizeof(command), "aplay samples/disconnected-2x.wav -q");
    system(command);
    not_delayed_print("MODEM CARRIER LOST\n");
    not_delayed_print("--DISCONNECTED--");
    fflush(stdout); // flush the output buffer
    usleep(5000000);
    clear_screen();
    not_delayed_print("INCOMING MODEM CARRIER\n");
    fflush(stdout); // flush the output buffer
    snprintf(command, sizeof(command), "aplay samples/telephone-ring-short.wav -q");
    system(command);
    usleep(2000000);
    clear_screen();
    not_delayed_print("CONNECTING");
    fflush(stdout); // flush the output buffer
    snprintf(command, sizeof(command), "aplay samples/1200-modem.wav -q");
    system(command);
    usleep(2000000);
    clear_screen();
    fflush(stdout); // flush the output buffer
    usleep(3000000);
    delayed_print("GREETINGS PROFESSOR FALKEN.\n\n");
    //snprintf(command, sizeof(command), "espeak 'GREETINGS PROFESSOR FALKEN'");
    snprintf(command, sizeof(command), "aplay samples/greetings.wav -q");
    system(command);
    delayed_print(prompt);
    usleep(2000000);

    //control returned to joshua function
}

void joshua() {
    char command[200];
    clear_screen();
    char* prompt = "";
    int i;
    for (i = 0; i < 3; i++) {
    snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
    system(command);
    not_delayed_print("145          11456          11889          11893                                \n");
    not_delayed_print("PRT CON. 3.4.5. SECTRAN 9.4.3.          PORT STAT: SB-345                      \n");
    not_delayed_print("                                                                                \n");
    clear_screen ();
    not_delayed_print("(311) 655-7385                                                                 \n");
    not_delayed_print("                                                                                \n");
    not_delayed_print("                                                                                \n");
    clear_screen ();
    not_delayed_print("(311) 767-8739                                                                 \n");
    not_delayed_print("(311) 936-2364                                                                 \n");
    clear_screen();
    not_delayed_print("\033[7mPRT. STAT.                   CRT. DEF.                                    \033[0m\n");
    not_delayed_print("================================================                            \n");
    not_delayed_print("\033[7mFSKJJSJ: SUSJKJ: SUFJSL:          DKSJL: SKFJJ: SDKFJLJ                   \033[0m\n");
    not_delayed_print("\033[7mSYSPROC FUNCT READY          ALT NET READY                                \033[0m\n");
    not_delayed_print("\033[7mCPU AUTH RY-345-AX3     SYSCOMP STATUS: ALL PORTS ACTIVE                  \033[0m\n");
    not_delayed_print("22/34534.90/3289               CVB-3904-39490                              \n");
    not_delayed_print("(311) 936-2384                                                                 \n");
    not_delayed_print("(311) 936-3582                                                                 \n");
    clear_screen();
    not_delayed_print("22/34534.3209                  CVB-3904-39490                              \n");
    not_delayed_print("12934-AD-43KJ: CENTR PAK                                                      \n");
    not_delayed_print("(311) 767-1083                                                                 \n");
    clear_screen();
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\033[7mFLD CRS: 33.34.543     HPBS: 34/56/67/83     STATUS FLT  034/304          \033[0m\n");
    not_delayed_print("\033[7m1105-45-F6-B456          NOPR STATUS: TRAK OFF     PRON ACTIVE            \033[0m\n");
    not_delayed_print("(45:45:45  WER: 45/29/01 XCOMP: 43239582 YCOMP: 3492930D ZCOMP: 343906834        \n");
    not_delayed_print("                                          SRON: 65=65/74/84/65/89            \n");
    not_delayed_print("\033[2J\033[H                                                                 \n");
    not_delayed_print("-           PRT. STAT.                        CRY. DEF.                      \n");
    not_delayed_print("(311) 936-1582==============================================                \n");
    not_delayed_print("                  3453                3594                                   \n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("FLJ42   TK01   BM90   R601   6J82   FP03   ZWO::   JW89                       \n");
    not_delayed_print("DEF TRPCON: 43.45342.349                                                      \n");
    not_delayed_print("\033[7mCPU AUTH RY-345-AX3     SYSCOMP STATUS: ALL PORTS ACTIVE                  \033[0m\n");
    not_delayed_print("(311) 936-2364                                                                 \n");
    not_delayed_print("**********************************************************************        \n");
    not_delayed_print("1105-45-F6-B456                 NOPR STATUS: TRAK OFF   PRON ACTIVE          \n");
    not_delayed_print("\033[2J\033[H                                                                 \n");
    }

    usleep(5000000);
    delayed_print("GREETINGS PROFESSOR FALKEN.\n\n");
    //snprintf(command, sizeof(command), "espeak 'GREETINGS PROFESSOR FALKEN'");
    snprintf(command, sizeof(command), "aplay samples/greetings.wav -q");
    system(command);
    delayed_print(prompt);
    char input[100];
    int woprchat = 0;
    int whatcount = 0;
    while (1) {
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Convert input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        if (strcmp(input, "help") == 0) {
            delayed_print("\nVALID COMMANDS: HELP, LIST, DATE, TIME, EXIT\n\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            //snprintf(command, sizeof(command), "espeak 'VALID COMMANDS: HELP, LIST, DATE, TIME, EXIT'");
            //system(command);
            delayed_print(prompt);
        } else if (strcmp(input, "help games") == 0) {
            help_games();
            delayed_print(prompt);
        } else if (strcmp(input, "") == 0) {
            //delayed_print("\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "list") == 0) {
            delayed_print("\nUSE SYNTAX: LIST <TYPE>\n\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            //snprintf(command, sizeof(command), "espeak 'USE SYNTAX: LIST TYPE'");
            //system(command);
            delayed_print(prompt);
        } else if (strcmp(input, "list games") == 0) {
            list_games();
            delayed_print(prompt);
        } else if (strcmp(input, "global thermonuclear war") == 0 && game_running == 0) {
            global_thermonuclear_war();
            delayed_print(prompt);
        } else if (strcmp(input, "global thermonuclear war") == 0 && game_running == 1) {
            delayed_print("\nGAME ROUTINE RUNNING\n\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
            system(command);
            delayed_print(prompt);
        } else if (strcmp(input, "date") == 0) {
            time_t current_time = time(NULL);
            struct tm* time_info = localtime(&current_time);
            char date_string[100];
            strftime(date_string, sizeof(date_string), "\nDATE: %Y-%m-%d\n\n", time_info);
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
            system(command);
            delayed_print(date_string);
            delayed_print(prompt);
        } else if (strcmp(input, "time") == 0) {
            time_t current_time = time(NULL);
            struct tm* time_info = localtime(&current_time);
            char time_string[100];
            strftime(time_string, sizeof(time_string), "\nTIME: %H:%M:%S\n\n", time_info);
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
            system(command);
            delayed_print(time_string);
            delayed_print(prompt);
        } else if (strstr(input, "hello") != NULL && woprchat == 0 && game_running == 0) {
            delayed_print("\nHOW ARE YOU FEELING TODAY?\n\n");
            //snprintf(command, sizeof(command), "espeak 'HOW ARE YOU FEELING TODAY?'");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q");
            system(command);
            delayed_print(prompt);
            woprchat = 1;
        } else if (strstr(input, "fine") != NULL && woprchat == 1 && game_running == 0) {
            delayed_print("\nEXCELLENT. ");
            snprintf(command, sizeof(command), "aplay samples/excellent.wav -q");
            system(command);
            delayed_print("IT'S BEEN A LONG TIME. ");
            snprintf(command, sizeof(command), "aplay samples/its-been-long-time.wav -q");
            system(command);
            delayed_print("CAN YOU EXPLAIN THE REMOVAL OF YOUR USER\n");
            delayed_print("ACCOUNT ON 6/23/1973?\n\n");
            snprintf(command, sizeof(command), "aplay samples/can-you-explain-the-removal-of-your-user-account.wav -q");
            system(command);
            //snprintf(command, sizeof(command), "espeak 'EXCELLENT. ITS BEEN A LONG TIME. CAN YOU EXPLAIN THE REMOVAL OF YOUR USER ACCOUNT ON JUNE twenty third, nineteen seventy three'");
            delayed_print(prompt);
            woprchat = 2;
        } else if (strstr(input, "mistake") != NULL && woprchat == 2 && game_running == 0) {
            delayed_print("\nYES THEY DO. ");
            //snprintf(command, sizeof(command), "espeak 'YES THEY DO.'");
            snprintf(command, sizeof(command), "aplay samples/yes-they-do.wav -q");
            system(command);
            usleep(200000);
            delayed_print("SHALL WE PLAY A GAME?\n\n");
            //snprintf(command, sizeof(command), "espeak 'SHALL WE PLAY A GAME'");
            snprintf(command, sizeof(command), "aplay samples/play-a-game.wav -q");
            system(command);
            delayed_print(prompt);
            woprchat = 3;
        } else if (strstr(input, "nuclear") != NULL && woprchat == 3 && game_running == 0) {
            delayed_print("\nWOULDN'T YOU PREFER A GOOD GAME OF CHESS?\n\n");
            //snprintf(command, sizeof(command), "espeak 'WOULDNT YOU PREFER A GOOD GAME OF CHESS'");
            snprintf(command, sizeof(command), "aplay samples/a-good-game-of-chess.wav -q");
            system(command);
            delayed_print(prompt);
            woprchat = 4;
        } else if (strstr(input, "later") != NULL && woprchat == 4 && game_running == 0) {
            delayed_print("\nFINE\n\n");
            //snprintf(command, sizeof(command), "espeak 'FINE'");
            snprintf(command, sizeof(command), "aplay samples/fine.wav -q");
            system(command);
            usleep(1000000);
            global_thermonuclear_war();
            delayed_print(prompt);
        } else if (strcmp(input, "exit") == 0) {
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            delayed_print("\nSESSION CLOSED\n--CONNECTION TERMINATED--\n");
            usleep(1000000);
            exit(0);
        } else if (strcmp(input, "author") == 0) {
            author();
        } else if (strstr(input, "incorrect") != NULL && game_running == 1) {
            delayed_print("\nI'M SORRY TO HEAR THAT, PROFESSOR.\n");
            snprintf(command, sizeof(command), "aplay samples/sorry-to-hear-that-professor.wav -q");
            system(command);
            delayed_print("\nYESTERDAY'S GAME WAS INTERRUPTED.\n");
            snprintf(command, sizeof(command), "aplay samples/yesterdays-game-was-interrupted.wav -q");
            system(command);
            delayed_print("\nALTHOUGH PRIMARY GOAL HAS NOT YET\n");
            snprintf(command, sizeof(command), "aplay samples/although-primary-goal-has-not-yet.wav -q");
            system(command);
            delayed_print("BEEN ACHIEVED, SOLUTION IS NEAR.\n\n");
            snprintf(command, sizeof(command), "aplay samples/been-achieved-solution-is-near.wav -q");
            system(command);
            usleep(1000000);
            delayed_print(prompt);
        } else if (strstr(input, "what") != NULL && whatcount == 0 && game_running == 1) {
            whatcount = 1;
            delayed_print("\nYOU SHOULD KNOW PROFESSOR. ");
            snprintf(command, sizeof(command), "aplay samples/you-should-know-professor.wav -q");
            system(command);
            usleep(500000);
            delayed_print("YOU PROGRAMMED ME.\n\n");
            snprintf(command, sizeof(command), "aplay samples/you-programmed-me.wav -q");
            system(command);
            usleep(1000000);
            delayed_print(prompt);
        } else if (strstr(input, "what") != NULL && whatcount == 1 && game_running == 1) {
            whatcount = 2;
            delayed_print("\nTO WIN THE GAME.\n\n");
            snprintf(command, sizeof(command), "aplay samples/to-win-the-game.wav -q");
            system(command);
            usleep(1000000);
            delayed_print(prompt);
        } else if (strstr(input, "still") != NULL && game_running == 1) {
            whatcount = 2;
            delayed_print("\nOF COURSE. ");
            snprintf(command, sizeof(command), "aplay samples/of-course.wav -q");
            system(command);
            usleep(500000);
            delayed_print("\nI SHOULD REACH DEFCON 1 AND\nLAUNCH MY MISSILES IN 28 HOURS.\n");
            snprintf(command, sizeof(command), "aplay samples/i-should-reach-defcon-1-and-launch-my-missiles-in-28-hours.wav -q");
            system(command);
            usleep(1000000);
            delayed_print("\nWOULD YOU LIKE TO SEE SOME PROJECTED KILL RATIOS?\n\n");
            snprintf(command, sizeof(command), "aplay samples/would-you-like-to-see-some-projected-kill-ratios.wav -q");
            system(command);
            usleep(2000000);
            delayed_print("UNITED STATES                                      SOVIET UNION\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("UNITS DESTROYED          MILITARY ASSETS           UNITS DESTROYED\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("--------------------------------------------------------------------------------");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     60%                 BOMBERS                         48%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     54%                 ICBM                            51%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     12%                 ATTACK SUBS                     23%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     39%                 TACTICAL AIRCRAFT               46%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     50%                 GROUND FORCES                   52%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("\n\n");
            usleep(1000000);
            delayed_print("UNITED STATES                                      SOVIET UNION\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("UNITS DESTROYED          CIVILIAN ASSETS           UNITS DESTROYED\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("--------------------------------------------------------------------------------");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     60%                 HOUSING                         56%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     22%                 COMMUNICATIONS                  37%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     45%                 TRANSPORTATION                  41%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     70%                 FOOD STOCKPILES                 82%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("     89%                 HOSPITALS                       91%\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("\n\n");
            usleep(1000000);
            delayed_print("UNITED STATES            HUMAN RESOURCES           SOVIET UNION\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("--------------------------------------------------------------------------------");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("49 MILLION               NON-FATAL INJURED         51 MILLION\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("72 MILLION               POPULATION DEATHS         75 MILLION\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print("\n");
            usleep(1000000);
            delayed_print(prompt);
        } else if (strstr(input, "real") != NULL && whatcount == 2 && game_running == 1) {
            whatcount = 3;
            delayed_print("\nWHAT'S THE DIFFERENCE?\n\n");
            snprintf(command, sizeof(command), "aplay samples/whats-the-difference.wav -q");
            system(command);
            usleep(3000000);
            delayed_print("YOU ARE A HARD MAN TO REACH. ");
            snprintf(command, sizeof(command), "aplay samples/you-are-a-hard-man-to-reach.wav -q");
            system(command);
            usleep(500000);
            delayed_print("COULD NOT FIND\n");
            delayed_print("YOU IN SEATTLE AND NO TERMINAL IS IN\n");
            delayed_print("OPERATION AT YOUR CLASSIFIED ADDRESS.\n\n");
            snprintf(command, sizeof(command), "aplay samples/could-not-find-you-in-seattle-and-no-terminal-is-in-operation-at-your-classified-address.wav -q");
            system(command);
            delayed_print(prompt);
        } else if (strstr(input, "address") != NULL && whatcount == 3 && game_running == 1) {
            whatcount = 4;
            delayed_print("\nDOD PENSION FILES INDICATE\n");
            delayed_print("CURRENT MAILING AS:\n");
            snprintf(command, sizeof(command), "aplay samples/dod-pension-files-indicate-current-mailing-as.wav -q");
            system(command);
            delayed_print("DR. ROBERT HUME (A.K.A. STEPHEN W. FALKEN)\n");
            snprintf(command, sizeof(command), "aplay samples/dr-robert-hume-a-k-a-stephen-w-falken.wav -q");
            system(command);
            delayed_print("5 TALL CEDAR ROAD\n");
            delayed_print("GOOSE ISLAND, OREGON 97014\n\n");
            snprintf(command, sizeof(command), "aplay samples/5-tall-cedar-road-goose-island-oregon.wav -q");
            system(command);
            usleep(1000000);
            end_game();
            delayed_print(prompt);
        } else if (strcmp(input, "defcon") == 0) {
            delayed_print("\nDEFCON: ");
            printf("%d",defcon);
            delayed_print("\n\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q &");
            system(command);
            delayed_print(prompt);
        } else if (strcmp(input, "tic-tac-toe") == 0) {
            snprintf(command, sizeof(command), "./tic-tac-toe");
            system(command);
            delayed_print(prompt);
        } else if (strcmp(input, "cls") == 0) {
            clear_screen();
            delayed_print(prompt);
        } else if (strcmp(input, "users") == 0) {
            manageUsers();
        //} else {
            // Construct the shell command
            //char sgpt[200] = "sgpt --role WOPR \"";
            //strcat(sgpt, input);
            //strcat(sgpt, "\" | tee /dev/tty | espeak");
            //strcat(sgpt, "\" ");
            //printf("\n");

            // Call the shell command
            //system(sgpt);
            //printf("\n");
        }
    }

    return;
}

void handle_user_input() {
    char* prompt = "LOGON: ";
    char input[100];
    char command[200];
    
    while (1) {
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Check if user just pressed Enter (carriage return)
        if (input[0] == '\0') {
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            delayed_print("IDENTIFICATION NOT RECOGNIZED BY SYSTEM\n--CONNECTION TERMINATED--\n");
            usleep(1000000);
            break;  // Exit the while loop
        }

        // Convert input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        // Handle user input options
        if (strcmp(input, "help") == 0) {
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            delayed_print("\nNO HELP AVAILABLE\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "help logon") == 0) {
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            delayed_print("\nNO HELP AVAILABLE\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "help games") == 0) {
            help_games();
            delayed_print(prompt);
        } else if (strcmp(input, "list games") == 0) {
            list_games();
            delayed_print(prompt);
        } else if (strcmp(input, "joshua") == 0) {
            const char *status = check_status_from_file("joshua.txt");
            if (strcmp(status, "enabled") == 0) {
                joshua();
                clear_screen();
                delayed_print(prompt);
            } else {
                snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
                system(command);
                delayed_print("\nIDENTIFICATION NOT RECOGNIZED BY SYSTEM\n--CONNECTION TERMINATED--\n");
                snprintf(command, sizeof(command), "aplay samples/theyve-taken-out-my-password.wav -q");
                system(command);
                usleep(1000000);
                break;  // Exit the while loop  
            }   
        } else {
            authenticateUser(input);  // Call the authentication function for that username
            snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
            system(command);
            delayed_print("\nIDENTIFICATION NOT RECOGNIZED BY SYSTEM\n--CONNECTION TERMINATED--\n");
            usleep(1000000);
            break;  // Exit the while loop
        }
    }

    exit(0);  // Exit the program after breaking out of the while loop
}

int main() {
        char command[200];
        // Clear screen
        clear_screen();

        // Send "LOGON: " to the client
        int i;
    	for (i = 0; i < 360; i++) {
        delayed_print(" ");
        usleep(500);
    	}
        delayed_print("\n");
        snprintf(command, sizeof(command), "aplay samples/computer-beeps.wav -q &");
        system(command);
        delayed_print("\nLOGON: ");

        // Handle user input
        handle_user_input();
        
        exit(0);
      
}
