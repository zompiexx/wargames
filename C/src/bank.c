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
#include <termios.h>

#define CHARACTER_DELAY 5000  // 1000 = 1ms
#define MAX_BUFFER_LENGTH 1024

void fix_backspace_key() {
	char system_command[100];
	snprintf(system_command, sizeof(system_command), "stty erase ^H");
    system(system_command);
}

void clear_screen() {
    printf("\033[2J\033[H");
}

void delayed_print(const char* str) {
    for (int i = 0; str[i]; i++) {
        putchar(str[i]);
        fflush(stdout);
        usleep(CHARACTER_DELAY);
    }
}

void bank_computer() {
    char input[100];
    char username[50];
    char password[100];
    struct termios term, term_orig;
    char buffer[MAX_BUFFER_LENGTH];
    int attempts = 0;
    while (1) {
        clear_screen();
        delayed_print("TGS SYSTEM A-45 34:34:33                                              Y-1293.323\n");
        delayed_print("UNION MARINE BANK - SOUTHWEST REGIONAL DATA CENTER\n\n");
        delayed_print("LOGON    > ");
        fgets(username, sizeof(username), stdin); // fgets to replace scanf
        username[strcspn(username, "\n")] = '\0'; // remove trailing newline

        delayed_print("PASSWORD > ");
        tcgetattr(STDIN_FILENO, &term);
        term_orig = term; // Save original settings

        // Turn off ECHO
        term.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        // New code
        int c;
        int i = 0;
        while ((c = getchar()) != '\n' && c != EOF && i < sizeof(password) - 1) {
            password[i++] = c;
            putchar('*');
            fflush(stdout); // flush the output buffer
        }
        password[i] = '\0';

        // Restore original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);

        // Convert input to lowercase
        for (int j = 0; password[j]; j++) {
            input[j] = tolower(password[j]);
        }
        delayed_print("\nINVALID USER ACCOUNT\n");
        delayed_print("--DISCONNECTED--\n");
        usleep(1000000);
        exit(0);
    }
}

int main() {
    fix_backspace_key();
    bank_computer();
	return 0;
}
