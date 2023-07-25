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

#define CHARACTER_DELAY 5000  // 1000 = 1ms

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

int main(){
	clear_screen();
	char command[100];
	char system_command[200];
    char username[50];
    char password[50];

	usleep(1000000);
    delayed_print("TGS SYSTEM A-45 34:34:33                                              Y-1293.323\n");
    delayed_print("UNION MARINE BANK - SOUTHWEST REGIONAL DATA CENTER\n\n");
    delayed_print("LOGON    > ");
    fgets(username, sizeof(username), stdin); // fgets to replace scanf
    username[strcspn(username, "\n")] = '\0'; // remove trailing newline

    delayed_print("PASSWORD > ");
    fgets(password, sizeof(password), stdin); // fgets to replace scanf
    password[strcspn(password, "\n")] = '\0'; // remove trailing newline
    printf("\n");
    usleep(1000000);

    delayed_print("INVALID LOGON. CLOSING CONNECTION\n");
    delayed_print("--DISCONNECTED--\n");
    usleep(1000000);

	return 0;
}
