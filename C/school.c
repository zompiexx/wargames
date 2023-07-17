#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define CHARACTER_DELAY 5000  // 1000 = 1ms

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
    delayed_print("\033[2J\033[H");
}

void school_computer() {
    char input[100];
	clear_screen();
	delayed_print("PDP 11/270 PRB TIP #45                                                TTY 34/984\n");
	delayed_print("WELCOME TO THE SEATTLE PUBLIC SCHOOL DISTRICT DATANET\n");
	delayed_print("\n");
	
	while (1) {
		delayed_print("PLEASE LOGON WITH USER PASSWORD: ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Convert input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

	if (strcmp(input, "pencil") == 0) {
              break;  // Exit the while loop
            
	} else {
				delayed_print("\n");
				delayed_print("INVALID PASSWORD\n");
				delayed_print("\n");
				usleep(1000000);

			}
	}
	
	
	while (1) {
		clear_screen();
		delayed_print("PLEASE ENTER STUDENT NAME: ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Convert input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

	if (strcmp(input, "lightman") == 0) {
			delayed_print("\n");
			delayed_print("STUDENT RECORD: Lightman, David L.\n");
			delayed_print("\n");
			delayed_print("     CLASS #    COURSE TITLE         GRADE    TEACHER    PERIOD    ROOM\n");
			delayed_print("   ______________________________________________________________________\n");
			delayed_print("\n");
			delayed_print("      S-202     BIOLOGY 2              ");
			delayed_print("F");
			delayed_print("      LIGGET       3       214\n");
			delayed_print("      E-314     ENGLISH 11B            D      TURMAN       5       172\n");
			delayed_print("      H-221     WORLD HISTORY 11B      C      DWYMER       2       108\n");
			delayed_print("      M-106     TRIG 2                 B      DICKERSON    4       315\n");
			delayed_print("      PE-02     PHYSICAL EDUCATION     C      COMSTOCK     1       GYM\n");
			delayed_print("      M-122     CALCULUS 1             B      LOGAN        6       240\n");
			delayed_print("\n");
			usleep(10000000);
	
	} else if (strcmp(input, "mack") == 0) {
			delayed_print("\n");
			delayed_print("STUDENT RECORD: Mack, Jennifer K.\n");
			delayed_print("\n");
			delayed_print("     CLASS #    COURSE TITLE         GRADE    TEACHER    PERIOD    ROOM\n");
			delayed_print("   ______________________________________________________________________\n");
			delayed_print("\n");
			delayed_print("      S-202     BIOLOGY 2              ");
			delayed_print("F");
			delayed_print("      LIGGET       3       214\n");
			delayed_print("      E-325     ENGLISH 11B            A      ROBINSON     1       114\n");
			delayed_print("      H-221     WORLD HISTORY 11B      B      DWYER        2       108\n");
			delayed_print("      M-104     GEOMETRY 2             D      HALQUIST     4       307\n");
			delayed_print("      B-107     ECONOMICS              D      MARKS        5       122\n");
			delayed_print("      PE-02     PHYSICAL EDUCATION     C      COMSTOCK     6       GYM\n");
			delayed_print("\n");
			usleep(10000000);
			
	} else if (strcmp(input, "exit") == 0) {
            delayed_print("\n");
            delayed_print("--DISCONNECTED--\n");
            delayed_print("\n");
            break;  // Exit the while loop
	
	
	} else {
            delayed_print("\n");
            delayed_print("NO STUDENT RECORD FOUND\n");
            delayed_print("\n");
	    usleep(1000000);

            }
	}
}

int main() {

        // Clear screen
        clear_screen();

        // Send "LOGON: " to the client
        school_computer();
        
        exit(0);
      
}
