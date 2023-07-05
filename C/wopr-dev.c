#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define CHARACTER_DELAY 5000  // 1000 = 1ms
#define MAX_TARGETS 100




void delayed_print(const char* str) {
    for (int i = 0; str[i]; i++) {
        putchar(str[i]);
        fflush(stdout);
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

void clear_screen() {
    printf("\033[2J\033[H");
}

void global_thermonuclear_war() {
    //char command[200];
    startgame:
    clear_screen();
    usleep(500000);
    delayed_print("                            GLOBAL THERMONUCLEAR WAR\n\n");
    delayed_print("\n");
    delayed_print("      ___    ____             ____                   _______________\n");
    delayed_print("     |   \\__/    \\_____      /    |              ___/               \\\n");
    delayed_print("     |                 \\    /    /           ___/                    \\______\n");
    delayed_print("     |                  \\__/    /           /                               \\\n");
    delayed_print("     |                           \\        _/                                 |\n");
    delayed_print("     |        UNITED STATES       |      /           SOVIET UNION       ____/\n");
    delayed_print("      \\                           /     /                          ____/\n");
    delayed_print("        \\                        /     |                          /\n");
    delayed_print("          \\________          __/       \\          _____   /\\_    /\n");
    delayed_print("                   \\__      /            \\__    _/     \\_/   \\__/\n");
    delayed_print("                      \\____/                \\__/\n");
    delayed_print("\n");
    delayed_print("WHICH SIDE DO YOU WANT?\n\n");
    //snprintf(command, sizeof(command), "espeak 'WHICH SIDE DO YOU WANT?'");
    //system(command);
    delayed_print("  1. UNITED STATES\n");
    delayed_print("\033[5m  2. SOVIET UNION\033[0m\n\n");
    delayed_print("PLEASE CHOOSE ONE: ");
    char side[20];  // Array to store the selected side
    char input;
    scanf(" %c", &input);

    if (input == '1') {
        strcpy(side, "UNITED STATES");
    } else if (input == '2') {
        strcpy(side, "SOVIET UNION");
    } else {
        delayed_print("\nINVALID OPTION\n\n");
        usleep(5000000);
        goto startgame;
    }
   
    // Rest of the game code goes here: start
    delayed_print("YOU HAVE SELECTED: ");
    delayed_print(side);
    usleep(2500000);
    clear_screen ();
    usleep(2500000);
    delayed_print("PLEASE LIST PRIMARY TARGETS BY\n");
    delayed_print("CITY AND/OR COUNTY NAME:\n\n");
    //snprintf(command, sizeof(command), "espeak 'PLEASE LIST PRIMARY TARGETS'");
    //system(command);
    //while loop to input targets goes here
    //delayed_print("\n\nMAX TARGETS SELECTED");
    delayed_print("\n\nTARGET SELECTION COMPLETE\n\n");
    //snprintf(command, sizeof(command), "espeak 'TARGET SELECTION COMPLETE'");
    //system(command);
    usleep(2500000);
    
    //delayed_print("LISTING PRIMARY TARGETS:\n\n");

    // Rest of the game code goes here: finish
    usleep(10000000);
    clear_screen();
    delayed_print("\nA STRANGE GAME. ");
    //snprintf(command, sizeof(command), "espeak 'A STRANGE GAME'");
    //system(command);
    usleep(500000);
    delayed_print("THE ONLY WINNING MOVE IS NOT TO PLAY!\n\n");
    //snprintf(command, sizeof(command), "espeak 'THE ONLY WINNING MOVE IS NOT TO PLAY!'");
    //system(command);
}


void joshua() {
    clear_screen();
    char* prompt = "";
    int i;
    for (i = 0; i < 2; i++) {
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
    not_delayed_print("\033[7mFLD CRS: 33.34.543     HPBS: 34/56/67/83     STATUS FLT  034/304          \033[0m\n");
    not_delayed_print("\033[7m1105-45-F6-B456          NOPR STATUS: TRAK OFF     PRON ACTIVE            \033[0m\n");
    not_delayed_print("(45:45:45  WER: 45/29/01 XCOMP: 43239582 YCOMP: 3492930D ZCOMP: 343906834        \n");
    not_delayed_print("                                          SRON: 65=65/74/84/65/89            \n");
    not_delayed_print("\033[2J\033[H                                                                 \n");
    not_delayed_print("-           PRT. STAT.                        CRY. DEF.                      \n");
    not_delayed_print("(311) 936-1582==============================================                \n");
    not_delayed_print("                  3453                3594                                   \n");
    not_delayed_print("FLJ42   TK01   BM90   R601   6J82   FP03   ZWO::   JW89                       \n");
    not_delayed_print("DEF TRPCON: 43.45342.349                                                      \n");
    not_delayed_print("\033[7mCPU AUTH RY-345-AX3     SYSCOMP STATUS: ALL PORTS ACTIVE                  \033[0m\n");
    not_delayed_print("(311) 936-2364                                                                 \n");
    not_delayed_print("**********************************************************************        \n");
    not_delayed_print("1105-45-F6-B456                 NOPR STATUS: TRAK OFF   PRON ACTIVE          \n");
    not_delayed_print("\033[2J\033[H                                                                 \n");

    }

    usleep(500000);
    delayed_print("GREETINGS PROFESSOR FALKEN.\n\n");
    //char command[100];
    //snprintf(command, sizeof(command), "espeak 'GREETINGS PROFESSOR FALKEN'");
    //system(command);
    delayed_print(prompt);
    char input[100];
    int woprchat = 0;
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
            delayed_print(prompt);
        } else if (strcmp(input, "help games") == 0) {
            delayed_print("\n'GAMES' REFERS TO MODELS, SIMULATIONS, AND GAMES WHICH HAVE TACTICAL AND\nSTRATEGIC APPLICATIONS\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "") == 0) {
            delayed_print("\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "list") == 0) {
            delayed_print("\nUSE SYNTAX: LIST <SUBJECT> (E.G. LIST GAMES)\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "list games") == 0) {
            delayed_print("\nBLACK JACK\nGIN RUMMY\nHEARTS\nBRIDGE\nCHESS\nPOKER\nFIGHTER COMBAT\nGUERRILLA ENGAGEMENT\nDESERT WARFARE\nAIR-TO-GROUND ACTIONS\nTHEATERWIDE TACTICAL WARFARE\nTHEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n\n");
            usleep(500000);
            delayed_print("GLOBAL THERMONUCLEAR WAR\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "global thermonuclear war") == 0) {
            global_thermonuclear_war();
            delayed_print(prompt);
        } else if (strcmp(input, "date") == 0) {
            time_t current_time = time(NULL);
            struct tm* time_info = localtime(&current_time);
            char date_string[100];
            strftime(date_string, sizeof(date_string), "\nDATE: %Y-%m-%d\n\n", time_info);
            delayed_print(date_string);
            delayed_print(prompt);
        } else if (strcmp(input, "time") == 0) {
            time_t current_time = time(NULL);
            struct tm* time_info = localtime(&current_time);
            char time_string[100];
            strftime(time_string, sizeof(time_string), "\nTIME: %H:%M:%S\n\n", time_info);
            delayed_print(time_string);
            delayed_print(prompt);
        } else if (strstr(input, "hello") != NULL && woprchat == 0) {
            delayed_print("\nHOW ARE YOU FEELING TODAY?\n\n");
            //char command[200];
            //snprintf(command, sizeof(command), "espeak 'HOW ARE YOU FEELING TODAY?'");
            //system(command);
            delayed_print(prompt);
            woprchat = 1;
        } else if (strstr(input, "fine") != NULL && woprchat == 1) {
            delayed_print("\nEXCELLENT. IT'S BEEN A LONG TIME. CAN YOU EXPLAIN THE REMOVAL OF YOUR USER\n");
            delayed_print("ACCOUNT ON 6/23/1973?\n\n");
            //char command[200];
            //snprintf(command, sizeof(command), "espeak 'EXCELLENT. ITS BEEN A LONG TIME. CAN YOU EXPLAIN THE REMOVAL OF YOUR USER ACCOUNT ON JUNE twenty third, nineteen seventy three'");
            //system(command);
            delayed_print(prompt);
            woprchat = 2;
        } else if (strstr(input, "mistake") != NULL && woprchat == 2) {
            delayed_print("\nYES THEY DO. ");
            //char command[200];
            //snprintf(command, sizeof(command), "espeak 'YES THEY DO.'");
            //system(command);
            usleep(200000);
            delayed_print("SHALL WE PLAY A GAME?\n\n");
            //snprintf(command, sizeof(command), "espeak 'SHALL WE PLAY A GAME'");
            //system(command);
            delayed_print(prompt);
            woprchat = 3;
        } else if (strstr(input, "nuclear") != NULL && woprchat == 3) {
            delayed_print("\nWOULDN'T YOU PREFER A GOOD GAME OF CHESS?\n\n");
            //char command[200];
            //snprintf(command, sizeof(command), "espeak 'WOULDNT YOU PREFER A GOOD GAME OF CHESS'");
            //system(command);
            delayed_print(prompt);
            woprchat = 4;
        } else if (strstr(input, "later") != NULL && woprchat == 4) {
            delayed_print("\nFINE\n\n");
            //char command[200];
            //snprintf(command, sizeof(command), "espeak 'FINE'");
            //system(command);
            usleep(1000000);
            global_thermonuclear_war();
            delayed_print(prompt);
        } else if (strcmp(input, "exit") == 0) {
            delayed_print("\nSESSION CLOSED\n--CONNECTION TERMINATED--\n");
            usleep(1000000);
            exit(0);
        } else {
            delayed_print("\nINVALID COMMAND: ");
            delayed_print(input);
            delayed_print("\n\n");
            delayed_print(prompt);
        }
    }

    return;
}

void handle_user_input() {
    char* prompt = "LOGON: ";
    char input[100];
    while (1) {
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Convert input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        // Handle user input options
        if (strcmp(input, "help") == 0) {
            delayed_print("\nNO HELP AVAILABLE\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "help logon") == 0) {
            delayed_print("\nNO HELP AVAILABLE\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "help games") == 0) {
            delayed_print("\n'GAMES' REFERS TO MODELS, SIMULATIONS, AND GAMES WHICH HAVE TACTICAL AND\nSTRATEGIC APPLICATIONS\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "list games") == 0) {
            delayed_print("\nBLACK JACK\nGIN RUMMY\nHEARTS\nBRIDGE\nCHESS\nPOKER\nFIGHTER COMBAT\nGUERRILLA ENGAGEMENT\nDESERT WARFARE\nAIR-TO-GROUND ACTIONS\nTHEATERWIDE TACTICAL WARFARE\nTHEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n\n");
            usleep(500000);
            delayed_print("GLOBAL THERMONUCLEAR WAR\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "joshua") == 0) {
            joshua();
            clear_screen();
            delayed_print(prompt);
        } else {
            delayed_print("IDENTIFICATION NOT RECOGNIZED BY SYSTEM\n--CONNECTION TERMINATED--\n");
            usleep(1000000);
            break;  // Exit the while loop
        }
    }

    exit(0);  // Exit the program after breaking out of the while loop
}

int main() {

        // Clear screen
        clear_screen();

        // Send "LOGON: " to the client
        int i;
    	for (i = 0; i < 360; i++) {
        delayed_print(" ");
        usleep(500);
    	}
        delayed_print("\n");
        delayed_print("\nLOGON: ");

        // Handle user input
        handle_user_input();
        
        exit(0);
      
}
