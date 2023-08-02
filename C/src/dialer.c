//Wargames Movie Simulator
//Written by Andy Glenn
//(c) 2023

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_RECORDS 101
#define MAX_SYSTEM_NAME_LENGTH 31  // updated to 31, to account for the null-terminating character
#define MAX_SYSTEM_ACTION_LENGTH 101  // updated to 101, to account for the null-terminating character

int number_of_systems = 0;  // global variable for the number of systems found in systems_list.txt file

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void string_to_lowercase(char str[]) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void clear_screen() {
    printf("\033[2J\033[H");
}

int read_data_from_file(int system_pfx[], int system_num[], char system_name[][MAX_SYSTEM_NAME_LENGTH], char system_action[][MAX_SYSTEM_ACTION_LENGTH]) {
    FILE *file = fopen("systems_list.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return -1;
    }

    int valid_records = 0;
    for (int a = 1; a < MAX_RECORDS; a++) {
        if (fscanf(file, "%d%d%30s%100s", &system_pfx[a], &system_num[a], system_name[a], system_action[a]) == 4) {
            valid_records++;
        } else {
            break;
        }
    }

    fclose(file);
    
    number_of_systems = valid_records;  // Set the renamed global variable

    return valid_records;
}

void print_arrays(int valid_records, int system_pfx[], int system_num[], char system_name[][MAX_SYSTEM_NAME_LENGTH], char system_action[][MAX_SYSTEM_ACTION_LENGTH]) {
    for (int a = 1; a <= valid_records; a++) {
        printf("Record %d:\n", a);
        printf("system_pfx: %d\n", system_pfx[a]);
        printf("system_num: %d\n", system_num[a]);
        printf("system_name: %s\n", system_name[a]);
        printf("system_action: %s\n", system_action[a]);
        printf("\n"); // For readability
    }
}

void read_and_print_systems_found() {
    int system_pfx[MAX_RECORDS], system_num[MAX_RECORDS];
    char system_name[MAX_RECORDS][MAX_SYSTEM_NAME_LENGTH], system_action[MAX_RECORDS][MAX_SYSTEM_ACTION_LENGTH];
    char system_command[200];

    FILE *file = fopen("systems_found.txt", "a+");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    int record_count = 0; // Keep track of the number of records read

    while(record_count < MAX_RECORDS && !feof(file)) {
        // Read pfx
        if (fscanf(file, "%03d", &system_pfx[record_count]) != 1) {
            break;
        }

        // Read num
        if (fscanf(file, "%04d", &system_num[record_count]) != 1) {
            break;
        }

        // Read system_name
        if (fscanf(file, "%30s", system_name[record_count]) != 1) {
            break;
        }

        // Read system_action
        if (fscanf(file, "%100s", system_action[record_count]) != 1) {
            break;
        }

        record_count++;
    }

    fclose(file);

    // start point
    while(1) {
        clear_screen();
        printf("\n                  NUMBERS FOR WHICH CARRIER TONES WERE DETECTED:\n\n");

        for(int i=0; i < record_count; i++){
            printf("                           ");
            printf("%c: ", 'A' + i);
            printf("(311) ");
            printf("%03d ", system_pfx[i]);
            printf("%04d ", system_num[i]);
            printf("(%s)\n", system_name[i]);
            //printf("(%s)\n", system_action[i]);
        }
        if (record_count == 0) {
            printf("                               NO SYSTEMS FOUND\n");
        }
        
        printf("\n                        PRESS ENTER KEY TO RETURN TO MENU");
        printf("\n                        OR SELECT SYSTEM: ");
        
        char selection[3]; // to accommodate the character, the '\n', and the null-terminating character
        fgets(selection, sizeof(selection), stdin); // Read user's selection

        // If user just pressed Enter, break the outer loop
        if(selection[0] == '\n' && selection[1] == '\0') {
            break;
        }

        int index = toupper(selection[0]) - 'A'; // Convert to upper case and get index
        if (index < 0 || index >= record_count) {
            printf("\n                                     NO MATCH\n");
            usleep(1000000);
        } else {
            //printf("INITIATING CONNECTION %s: %s\n", system_name[index], system_action[index]);
            clear_screen();
            fflush(stdout); // Flush the output buffer to ensure the prompt is displayed
            usleep(1000000);
            printf("ATDT311%03d%04d\n", system_pfx[index], system_num[index]);
            snprintf(system_command, sizeof(system_command), "aplay samples/dtmf-wopr.wav -q");
            system(system_command);
            usleep(250000);
    		snprintf(system_command, sizeof(system_command), "aplay samples/1200-modem.wav -q");
    		system(system_command);
			clear_screen();
            fflush(stdout); // Flush the output buffer to ensure the prompt is displayed
            usleep(2000000);
			printf("CONNECTING\n\n");
            usleep(2000000);
            system(system_action[index]); // Execute the selected system action
        }
    }
}

void saveNumber(int prefix, int num, char *system_name, char *system_action) {
    char buffer[200], line[200];
    char record[800] = {0}; // Array to store a record from file.
    int lineCount = 0;

    sprintf(buffer, "%03d\n%04d\n%s\n%s\n", prefix, num, system_name, system_action); // convert number to string

    // Open the file in read mode to check for duplicate entries, if file exists.
    FILE* file = fopen("systems_found.txt", "r");
    if (file != NULL) {
        while(fgets(line, sizeof(line), file) != NULL) {
            strcat(record, line); // Append the line read to record
            lineCount++;

            // After every 4 lines (a record), compare with buffer
            if(lineCount % 4 == 0) {
                if(strcmp(record, buffer) == 0) { // If entry already exists
                    //printf("Duplicate entry, not writing to file.\n");
                    fclose(file); // Always remember to close the file.
                    return; // Exit the function early
                }
                memset(record, 0, sizeof(record)); // Reset record for next 4 lines
            }
        }
        fclose(file); // Always remember to close the file after reading.
    }

    // If no duplicate entry was found or file didn't exist, append new entry.
    file = fopen("systems_found.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s", buffer); // Write your data
        fclose(file); // Always remember to close the file.
    } else {
        printf("Error opening file!\n");
    }
}

int compareStrings(const void* a, const void* b) {
    return strcmp((char*)a, (char*)b);
}

void dialer(int system_pfx[], int system_num[], char system_name[][MAX_SYSTEM_NAME_LENGTH], char system_action[][MAX_SYSTEM_ACTION_LENGTH]) {
    int data_pfx[] = {437, 936, 399, 437, 767, 399, 936, 767, 437};
    int data_num[] = {1083, 1493, 2364, 2977, 3395, 3582, 3923, 7305, 8739};
    int data_index = 0;
    int hits = 0;
    char input[20];
    char selectedsystem[100];
	char command[100];
    char input_string[6];
    char system_command[200];
    char systems[10000][100]; // An array of strings
    int count = 0; // Variable to keep track of how many systems we've read


    while(1) {
        menu:
        clear_screen();
        printf("DIALER\n\n");
        printf("MENU - (S)CAN, (V)IEW OR E(X)IT: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        printf("\n");

        // printf("The input character is: %c\n", input[0]);
        if (input[0] == 's' || input[0] == 'S') {
            hits=0;
            goto numcheck;
        }
        if (input[0] == 'x' || input[0] == 'X') {
            exit(0);    
        }
        if (input[0] == 'v' || input[0] == 'V') {
            read_and_print_systems_found();
        }
    }

    numcheck:
    int nd_start;
    int nd_end;

    clear_screen();

    printf("START NUMBER (1 - 9999): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    nd_start = atoi(input);  // Converts the string to an integer

    printf("END NUMBER   (1 - 9999): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    nd_end = atoi(input);  // Converts the string to an integer

    if (nd_start < 1 || nd_start > 9999 || nd_end < 0 || nd_end > 9999) {
        printf("\nVALID RANGE (1 - 9999)\n");
        usleep(2000000);
        nd_end=0;
        nd_start=0;
        goto numcheck;
    }

    int ln = 0;
    char hit = 'N';
    int pfxset = 0;
    int pf1 = 399;
    int pf2 = 437;
    int pf3 = 767;
    int pf4 = 936;
    int pf1t = 0;
    int pf2t = 0;
    int pf3t = 0;
    int pf4t = 0;
    int s1=0;
    int s2=0;
    int s3=0;
    int s4=0;
    int s5=0;
    int random_number;
    int n;

    for (int i = nd_start; i <= nd_end; i++) {
        if (ln == 0 || i == (nd_start+10) || i == (nd_start+100) || i == (nd_start+1000)) {
            scan_start:
            clear_screen();
            printf("                    TO SCAN FOR CARRIER TONES, PLEASE LIST\n");
            printf("                         DESIRED AREA CODES AND PREFIXES\n\n");
            printf("AREA               AREA               AREA               AREA\n");
            printf("CODE PRFX NUMBER   CODE PRFX NUMBER   CODE PRFX NUMBER   CODE PRFX NUMBER\n");
            printf("________________________________________________________________________________\n\n");

            if (pfxset == 1) {
                goto pfx_set;
            }

            if (ln == 0 && i == nd_start) {
                    printf("\033[7m");
                    printf("(311) %d          (311) %d          (311) %d          (311) %d       ", pf1, pf2, pf3, pf4);
                    printf("\033[0m\n");

                    printf("\033[%d;%dH%s", 9, 1, "(311) ");

                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    pf1t = atoi(input);

                    printf("\033[%d;%dH%s", 9, 20, "(311) ");

                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    pf2t = atoi(input);

                    printf("\033[%d;%dH%s", 9, 39, "(311) ");

                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    pf3t = atoi(input);

                    printf("\033[%d;%dH%s", 9, 58, "(311) ");

                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    pf4t = atoi(input);

                if (pf1t > 999 || pf2t > 999 || pf3t > 999 || pf4t > 999 || pf1t < 0 || pf2t < 0 || pf3t < 0 || pf4t < 0) {
                    printf("\nINVALID PREFIXES ENTERED - PRESS ENTER KEY TO CONTINUE\n");
                    fflush(stdout); // Flush the output buffer to ensure the prompt is displayed
                    getchar(); // Wait for the Enter key to be pressed
                    clear_screen();
                    goto scan_start;
                } else {
                    pf1 = pf1t;
                    pf2 = pf2t;
                    pf3 = pf3t;
                    pf4 = pf4t;
                    pfxset = 1;
                    goto scan_start;
                }
            }
        }
        pfx_set:

        // Check prefix 1 for hits
        hit = 'N';
        for (n = 1; n < number_of_systems+1; n++) {
            if ((system_pfx[n] == pf1) && (i == system_num[n])) {
                hit = 'Y';
                hits = hits + 1;
                break;
            }
        }
        if (hit == 'Y') {
            printf("\033[7m(311) ");
            printf("%03d %04d", pf1, i);
            printf("\033[0m     ");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
            system(command);
            // Save the hit to the file
            saveNumber(pf1, i, system_name[n], system_action[n]);
        } else {
            printf("(311) ");
            printf("%03d %04d", pf1, i);
            printf("     ");
            random_number = rand() % 10;

            if (random_number == 1 && s1 == 0) {
                //only play this sample once
                s1 = 1;
                snprintf(command, sizeof(command), "aplay samples/sauls-fish-market.wav -q");
                system(command);
            } else if (random_number == 2) {
                snprintf(command, sizeof(command), "aplay samples/phone-busy-1.wav -q");
                system(command); 
            } else if (random_number == 3) {
                snprintf(command, sizeof(command), "aplay samples/hello.wav -q");
                system(command);
            } else if (random_number == 4) {
                snprintf(command, sizeof(command), "aplay samples/disconnected-2x.wav -q");
                system(command);
            } else if (random_number == 5 && s5 == 0) {
                s5 = 1;
                snprintf(command, sizeof(command), "aplay samples/funny-answer-phone.wav -q");
                system(command);
            } else {
                snprintf(command, sizeof(command), "aplay samples/phone-beep.wav -q");
                system(command);
            }
        }
        
        fflush(stdout); // flush the output buffer
        usleep(1000000);
        
        // End of checks for prefix 1

        // Check prefix 2 for hits
        hit = 'N';
        for (n = 1; n < number_of_systems+1; n++) {
            if ((system_pfx[n] == pf2) && (i == system_num[n])) {
                hit = 'Y';
                hits = hits + 1;
                break;
            }
        }
        if (hit == 'Y') {
            printf("\033[7m(311) ");
            printf("%03d %04d", pf2, i);
            printf("\033[0m     ");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
            system(command);
            // Save the hit to the file
            saveNumber(pf2, i, system_name[n], system_action[n]);
        } else {
            printf("(311) ");
            printf("%03d %04d", pf2, i);
            printf("     ");
            random_number = rand() % 10;

            if (random_number == 1 && s1 == 0) {
                //only play this sample once
                s1 = 1;
                snprintf(command, sizeof(command), "aplay samples/sauls-fish-market.wav -q");
                system(command);
            } else if (random_number == 2) {
                snprintf(command, sizeof(command), "aplay samples/phone-busy-1.wav -q");
                system(command); 
            } else if (random_number == 3) {
                snprintf(command, sizeof(command), "aplay samples/hello.wav -q");
                system(command);
            } else if (random_number == 4) {
                snprintf(command, sizeof(command), "aplay samples/disconnected-2x.wav -q");
                system(command);
            } else if (random_number == 5 && s5 == 0) {
                s5 = 1;
                snprintf(command, sizeof(command), "aplay samples/funny-answer-phone.wav -q");
                system(command);
            } else {
                snprintf(command, sizeof(command), "aplay samples/phone-beep.wav -q");
                system(command);
            }
         }

        fflush(stdout); // flush the output buffer
        usleep(1000000);

        // End of checks for prefix 2

        // Check prefix 3 for hits
        hit = 'N';
        for (n = 1; n < number_of_systems+1; n++) {
            if ((system_pfx[n] == pf3) && (i == system_num[n])) {
                hit = 'Y';
                hits = hits + 1;
                break;
            }
        }
        if (hit == 'Y') {
            printf("\033[7m(311) ");
            printf("%03d %04d", pf3, i);
            printf("\033[0m     ");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
            system(command);
            // Save the hit to the file
            saveNumber(pf3, i, system_name[n], system_action[n]);
        } else {
            printf("(311) ");
            printf("%03d %04d", pf3, i);
            printf("     ");
            random_number = rand() % 10;

            if (random_number == 1 && s1 == 0) {
                //only play this sample once
                s1 = 1;
                snprintf(command, sizeof(command), "aplay samples/sauls-fish-market.wav -q");
                system(command);
            } else if (random_number == 2) {
                snprintf(command, sizeof(command), "aplay samples/phone-busy-1.wav -q");
                system(command); 
            } else if (random_number == 3) {
                snprintf(command, sizeof(command), "aplay samples/hello.wav -q");
                system(command);
            } else if (random_number == 4) {
                snprintf(command, sizeof(command), "aplay samples/disconnected-2x.wav -q");
                system(command);
            } else if (random_number == 5 && s5 == 0) {
                s5 = 1;
                snprintf(command, sizeof(command), "aplay samples/funny-answer-phone.wav -q");
                system(command);
            } else {
                snprintf(command, sizeof(command), "aplay samples/phone-beep.wav -q");
                system(command);
            }
        }

        fflush(stdout); // flush the output buffer
        usleep(1000000);
        
        // End of checks for prefix 3

        // Check prefix 4 for hits
        hit = 'N';
        for (n = 1; n < number_of_systems+1; n++) {
            if ((system_pfx[n] == pf4) && (i == system_num[n])) {
                hit = 'Y';
                hits = hits + 1;
                break;
            }
        }
        if (hit == 'Y') {
            printf("\033[7m(311) ");
            printf("%03d %04d", pf4, i);
            printf("\033[0m\n");
            snprintf(command, sizeof(command), "aplay samples/computer-beeps-short.wav -q");
            system(command);
            // Save the hit to the file
            saveNumber(pf4, i, system_name[n], system_action[n]);
        } else {
            printf("(311) ");
            printf("%03d %04d", pf4, i);
            printf("\n");
            random_number = rand() % 10;

            if (random_number == 1 && s1 == 0) {
                //only play this sample once
                s1 = 1;
                snprintf(command, sizeof(command), "aplay samples/sauls-fish-market.wav -q");
                system(command);
            } else if (random_number == 2) {
                snprintf(command, sizeof(command), "aplay samples/phone-busy-1.wav -q");
                system(command); 
            } else if (random_number == 3) {
                snprintf(command, sizeof(command), "aplay samples/hello.wav -q");
                system(command);
            } else if (random_number == 4) {
                snprintf(command, sizeof(command), "aplay samples/disconnected-2x.wav -q");
                system(command);
            } else if (random_number == 5 && s5 == 0) {
                s5 = 1;
                snprintf(command, sizeof(command), "aplay samples/funny-answer-phone.wav -q");
                system(command);
            } else {
                snprintf(command, sizeof(command), "aplay samples/phone-beep.wav -q");
                system(command);
            }
        }

        fflush(stdout); // flush the output buffer
        usleep(1000000);
        
        // End of checks for prefix 4

        ln = ln + 1;
        // check if screen page break needed
        if (ln == 14) {
            ln = 0;
        }
    }
    printf("\n                      PRESS ENTER KEY TO RETURN TO MENU\n");
    fflush(stdout); // Flush the output buffer to ensure the prompt is displayed
    getchar(); // Wait for the Enter key to be pressed
    goto menu;
}

int main() {
    int system_pfx[MAX_RECORDS], system_num[MAX_RECORDS];
    char system_name[MAX_RECORDS][MAX_SYSTEM_NAME_LENGTH];
    char system_action[MAX_RECORDS][MAX_SYSTEM_ACTION_LENGTH];

    int valid_records = read_data_from_file(system_pfx, system_num, system_name, system_action);
    if (valid_records == -1) {
        printf("Error reading the file.\n");
        return -1;
    }

    //for debugging only
    //print_arrays(valid_records, system_pfx, system_num, system_name, system_action);
    //usleep(5000000);

    dialer(system_pfx, system_num, system_name, system_action);  // call the dialer function with appropriate arguments

    exit(0);
}

