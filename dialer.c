//Wargames Movie Simulator
//Written by Andy Glenn
//(c) 2023

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

void saveNumber(int prefix, char *z, int i) {
    char buffer[50];
    sprintf(buffer, "(311) %d %s %d\n", prefix, z, i); // convert number to string

    FILE* file = fopen("systems.txt", "a+");
    if (file != NULL) {
        char line[50];
        bool found = false;
        while(fgets(line, sizeof(line), file) != NULL) {
            if(strcmp(line, buffer) == 0) {
                found = true;
                break;
            }
        }

        if(!found) {
            fprintf(file, "%s", buffer); // write your data only if it's not found.
        }

        fclose(file); // always remember to close the file.
    } else {
        printf("Error opening file!\n");
    }
}

int compareStrings(const void* a, const void* b) {
    return strcmp((char*)a, (char*)b);
}

void dialer() {
    int data_pfx[] = {437, 936, 399, 437, 767, 399, 936, 767, 437};
    int data_num[] = {1083, 1493, 2364, 2977, 3395, 3582, 3923, 7305, 8739};
    int data_index = 0;
    int hits = 0;
    int pfx[10];
    int num[10];
    char input;
    char selectedsystem[100];
	char command[100];
    char input_string[6];
    char system_command[200];
    char systems[10000][100]; // An array of strings
    int count = 0; // Variable to keep track of how many systems we've read

    for (int a = 1; a <= 10; a++) {
        // Read pfx(a)
        pfx[a] = data_pfx[data_index];

        // Read num(a)
        num[a] = data_num[data_index];

        data_index++;
    }

    while(1) {
        menu:
        clear_screen();
        printf("DIALER\n\n");
        printf("MENU - (S)CAN, (V)IEW OR E(X)IT: ");
        scanf(" %c", &input);
        clear_input_buffer();
        printf("\n");
        count = 0;
        FILE* file = fopen("systems.txt", "r");
        if (file != NULL) {
            //printf("File opened successfully.\n");
            while(fgets(systems[count], sizeof(systems[count]), file) != NULL && count < 10000) {
                systems[count][strcspn(systems[count], "\n")] = 0; // remove newline character
                count++;
            }
            fclose(file);
        }
        // printf("The input character is: %c\n", input);
        if (input == 's' || input == 'S') {
            hits=0;
            goto numcheck;
        }
        if (input == 'x' || input == 'X') {
            exit(0);    
        }
        if (input == 'v' || input == 'V') {
            system_list:
            clear_screen();
            printf("                  NUMBERS FOR WHICH CARRIER TONES WERE DETECTED:\n\n");
            if (count == 0) {
                printf("                                NO SYSTEMS FOUND\n\n");
            } else {
                // Sort systems array
                //qsort(systems, count, sizeof(systems[0]), compareStrings);

                for (int a = 0; a < count; a++) {
                    printf("                                ");
                    printf("%c ", 'A' + a); // Prefix the output with a letter
                    printf("%s\n", systems[a]);
                }
            }
            printf("\n\n                        PRESS ENTER KEY TO RETURN TO MENU\n");
            printf("                        OR SELECT SYSTEM: ");
         
            fgets(input_string, sizeof(input_string), stdin);
            input_string[strcspn(input_string, "\n")] = '\0';
            string_to_lowercase(input_string);
            if(strcmp(input_string, "a") == 0){
                //do something for system a
                printf("\n                                ");
                printf("SYSTEM A SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "b") == 0) {
                //do something for system b
                printf("\n                                ");                
                printf("SYSTEM B SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "c") == 0) {
                //do something for system c
                printf("\n                                ");
                printf("SYSTEM C SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "d") == 0) {
                //do something for system d
                printf("\n                                ");
                printf("SYSTEM D SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "e") == 0) {
                //do something for system e
                printf("\n                                ");
                printf("SYSTEM E SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "f") == 0) {
                //do something for system f
                printf("\n                                ");
                printf("SYSTEM F SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "g") == 0) {
                //do something for system g
                printf("\n                                ");
                printf("SYSTEM G SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "h") == 0) {
                //do something for system h
                printf("\n                                ");
                printf("SYSTEM H SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "i") == 0) {
                //do something for system i
                printf("\n                                ");
                printf("SYSTEM I SELECTED\n");
                usleep(2000000);
                clear_screen();
                printf("CONNECTING\n\n");
                snprintf(system_command, sizeof(system_command), "aplay dial-up-modem-01.wav -q");
                system(system_command);
                usleep(5000000);             
    		    //connect to System I (WOPR)
                strcpy(command, "./wopr");
                // Execute the command using system()
                system(command);
                goto system_list;
            
            } else {
                printf("\n                                ");
                printf("   NO MATCH\n");
                usleep(2000000);
                goto menu;
            }
        }
    }

    numcheck:
    int nd_start;
    int nd_end;

    clear_screen();
    printf("START NUMBER (1 - 9999): ");
    scanf(" %d", &nd_start);
    clear_input_buffer();

    printf("END NUMBER   (1 - 9999): ");
    scanf(" %d", &nd_end);
    clear_input_buffer();

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
    char z[6] = "";
    int random_number;

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
                printf("(311) %d          (311) %d          (311) %d          (311) %d\n", pf1, pf2, pf3, pf4);
                printf("(311) ");
                scanf(" %d", &pf1t);
                clear_input_buffer();
                printf("                   (311) ");
                scanf(" %d", &pf2t);
                clear_input_buffer();
                printf("                                      (311) ");
                scanf(" %d", &pf3t);
                clear_input_buffer();
                printf("                                                         (311) ");
                scanf(" %d", &pf4t);
                clear_input_buffer();

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

        if (i > 0 && i < 10) {
            strcpy(z, "000");
        } else if (i > 9 && i < 100) {
            strcpy(z, "00");
        } else if (i > 99 && i < 1000) {
            strcpy(z, "0");
        } else if (i > 999) {
            strcpy(z, "");
        }

        // Check prefix 1 for hits
        hit = 'N';
        for (int n = 1; n < 10; n++) {
            if ((pfx[n] == pf1) && (i == num[n])) {
                hit = 'Y';
                hits = hits + 1;
            }
        }
        if (hit == 'Y') {
            printf("\033[7m(311) ");
            printf("%d %s %d", pf1, z, i);
            printf("\033[0m    ");
            snprintf(command, sizeof(command), "aplay computer-beeps-short.wav -q");
            system(command);
            // Save the hit to the file
            saveNumber(pf1, z, i);
        } else {
            printf("(311) ");
            printf("%d %s %d", pf1, z, i);
            printf("    ");
            random_number = rand() % 10;

            if (random_number == 1 && s1 == 0) {
                //only play this sample once
                s1 = 1;
                snprintf(command, sizeof(command), "aplay sauls-fish-market.wav -q");
                system(command);
            } else if (random_number == 2) {
                snprintf(command, sizeof(command), "aplay phone-busy-1.wav -q");
                system(command); 
            } else if (random_number == 3) {
                snprintf(command, sizeof(command), "aplay hello.wav -q");
                system(command);
            } else if (random_number == 4) {
                snprintf(command, sizeof(command), "aplay disconnected-2x.wav -q");
                system(command);
            } else if (random_number == 5 && s5 == 0) {
                s5 = 1;
                snprintf(command, sizeof(command), "aplay funny-answer-phone.wav -q");
                system(command);
            } else {
                snprintf(command, sizeof(command), "aplay phone-beep.wav -q");
                system(command);
            }
        }
        
        fflush(stdout); // flush the output buffer
        usleep(1000000);
        
        // End of checks for prefix 1

        // Check prefix 2 for hits
        hit = 'N';
        for (int n = 1; n < 10; n++) {
            if ((pfx[n] == pf2) && (i == num[n])) {
                hit = 'Y';
                hits = hits + 1;
            }
        }
        if (hit == 'Y') {
            printf("\033[7m(311) ");
            printf("%d %s %d", pf2, z, i);
            printf("\033[0m    ");
            snprintf(command, sizeof(command), "aplay computer-beeps-short.wav -q");
            system(command);
             // Save the hit to the file
            saveNumber(pf2, z, i);
        } else {
            printf("(311) ");
            printf("%d %s %d", pf2, z, i);
            printf("    ");
            random_number = rand() % 10;

            if (random_number == 1 && s1 == 0) {
                //only play this sample once
                s1 = 1;
                snprintf(command, sizeof(command), "aplay sauls-fish-market.wav -q");
                system(command);
            } else if (random_number == 2) {
                snprintf(command, sizeof(command), "aplay phone-busy-1.wav -q");
                system(command); 
            } else if (random_number == 3) {
                snprintf(command, sizeof(command), "aplay hello.wav -q");
                system(command);
            } else if (random_number == 4) {
                snprintf(command, sizeof(command), "aplay disconnected-2x.wav -q");
                system(command);
            } else if (random_number == 5 && s5 == 0) {
                s5 = 1;
                snprintf(command, sizeof(command), "aplay funny-answer-phone.wav -q");
                system(command);
            } else {
                snprintf(command, sizeof(command), "aplay phone-beep.wav -q");
                system(command);
            }
         }

        fflush(stdout); // flush the output buffer
        usleep(1000000);

        // End of checks for prefix 2

        // Check prefix 3 for hits
        hit = 'N';
        for (int n = 1; n < 10; n++) {
            if ((pfx[n] == pf3) && (i == num[n])) {
                hit = 'Y';
                hits = hits + 1;
            }
        }
        if (hit == 'Y') {
            printf("\033[7m(311) ");
            printf("%d %s %d", pf3, z, i);
            printf("\033[0m    ");
            snprintf(command, sizeof(command), "aplay computer-beeps-short.wav -q");
            system(command);
            // Save the hit to the file
            saveNumber(pf3, z, i);
        } else {
            printf("(311) ");
            printf("%d %s %d", pf3, z, i);
            printf("    ");
            random_number = rand() % 10;

            if (random_number == 1 && s1 == 0) {
                //only play this sample once
                s1 = 1;
                snprintf(command, sizeof(command), "aplay sauls-fish-market.wav -q");
                system(command);
            } else if (random_number == 2) {
                snprintf(command, sizeof(command), "aplay phone-busy-1.wav -q");
                system(command); 
            } else if (random_number == 3) {
                snprintf(command, sizeof(command), "aplay hello.wav -q");
                system(command);
            } else if (random_number == 4) {
                snprintf(command, sizeof(command), "aplay disconnected-2x.wav -q");
                system(command);
            } else if (random_number == 5 && s5 == 0) {
                s5 = 1;
                snprintf(command, sizeof(command), "aplay funny-answer-phone.wav -q");
                system(command);
            } else {
                snprintf(command, sizeof(command), "aplay phone-beep.wav -q");
                system(command);
            }
        }

        fflush(stdout); // flush the output buffer
        usleep(1000000);
        
        // End of checks for prefix 3

        // Check prefix 4 for hits
        hit = 'N';
        for (int n = 1; n < 10; n++) {
            if ((pfx[n] == pf4) && (i == num[n])) {
                hit = 'Y';
                hits = hits + 1;
            }
        }
        if (hit == 'Y') {
            printf("\033[7m(311) ");
            printf("%d %s %d", pf4, z, i);
            printf("\033[0m\n");
            snprintf(command, sizeof(command), "aplay computer-beeps-short.wav -q");
            system(command);
            // Save the hit to the file
            saveNumber(pf4, z, i);
        } else {
            printf("(311) ");
            printf("%d %s %d", pf4, z, i);
            printf("\n");
            random_number = rand() % 10;

            if (random_number == 1 && s1 == 0) {
                //only play this sample once
                s1 = 1;
                snprintf(command, sizeof(command), "aplay sauls-fish-market.wav -q");
                system(command);
            } else if (random_number == 2) {
                snprintf(command, sizeof(command), "aplay phone-busy-1.wav -q");
                system(command); 
            } else if (random_number == 3) {
                snprintf(command, sizeof(command), "aplay hello.wav -q");
                system(command);
            } else if (random_number == 4) {
                snprintf(command, sizeof(command), "aplay disconnected-2x.wav -q");
                system(command);
            } else if (random_number == 5 && s5 == 0) {
                s5 = 1;
                snprintf(command, sizeof(command), "aplay funny-answer-phone.wav -q");
                system(command);
            } else {
                snprintf(command, sizeof(command), "aplay phone-beep.wav -q");
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
    dialer();

    exit(0);
}

