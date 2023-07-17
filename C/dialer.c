#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void clear_input_buffer();
void print_with_padding(const char* prefix, int pf, const char* padding, int number, int alignment);
void clear_screen();
void dialer();

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void string_to_lowercase(char str[]) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void print_with_padding(const char* prefix, int pf, const char* padding, int number, int alignment) {
    printf("%s %3d %s %2d", prefix, pf, padding, number);
    for (int i = 0; i < alignment; i++) {
        printf(" ");
    }
}

void clear_screen() {
    printf("\033[2J\033[H");
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
        // printf("The input character is: %c\n", input);
        if (input == 's' || input == 'S') {
            goto numcheck;
        }
        if (input == 'x' || input == 'X') {
            exit(0);    
        }
        if (input == 'v' || input == 'V') {
            system_list:
            clear_screen();
            printf("                  NUMBERS FOR WHICH CARRIER TONES WERE DETECTED:\n\n");
            if (hits == 0) {
                printf("                                NO SYSTEMS FOUND\n\n");
                printf("         NOTE: TYPE LOAD AND PRESS ENTER KEY TO RESTORE SCAN RESULTS\n");
            } else {
                for (int a = 1; a <= hits; a++) {
                    printf("                                ");
                    printf("%c", (char)a+64);
                    printf(" (311) %d %d", pfx[a], num[a]);
                    printf("\n");
                }
            }
            printf("\n\n                        PRESS ENTER KEY TO RETURN TO MENU\n");
            printf("                        OR SELECT SYSTEM: ");

            char input_string[6];
          
            fgets(input_string, sizeof(input_string), stdin);
            input_string[strcspn(input_string, "\n")] = '\0';
            string_to_lowercase(input_string);
            if((strcmp(input_string, "a") == 0) && hits >=1){
                //do something for system a
                printf("\n                                ");
                printf("SYSTEM A SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if((strcmp(input_string, "b") == 0) && hits >=2){
                //do something for system b
                printf("\n                                ");                
                printf("SYSTEM B SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if((strcmp(input_string, "c") == 0) && hits >=3){
                //do something for system c
                printf("\n                                ");
                printf("SYSTEM C SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if((strcmp(input_string, "d") == 0) && hits >=4){
                //do something for system d
                printf("\n                                ");
                printf("SYSTEM D SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if((strcmp(input_string, "e") == 0) && hits >=5){
                //do something for system e
                printf("\n                                ");
                printf("SYSTEM E SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if((strcmp(input_string, "f") == 0) && hits >=6){
                //do something for system f
                printf("\n                                ");
                printf("SYSTEM F SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if((strcmp(input_string, "g") == 0) && hits >=7){
                //do something for system g
                printf("\n                                ");
                printf("SYSTEM G SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if((strcmp(input_string, "h") == 0) && hits >=8){
                //do something for system h
                printf("\n                                ");
                printf("SYSTEM H SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if((strcmp(input_string, "i") == 0) && hits >=9){
                //do something for system i
                printf("\n                                ");
                printf("SYSTEM I SELECTED\n");
                usleep(2000000);
                goto system_list;
            } else if(strcmp(input_string, "load") == 0) {
                //do something for system i
                hits=9;
                printf("\n                                ");
                printf("SYSTEM LIST LOADED\n");
                usleep(2000000);
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
    clear_screen();
    printf("HOW MANY NUMBERS FOR EACH PREFIX TO DIAL (MAX = 9999): ");
    int nd;
    scanf(" %d", &nd);
    if (nd > 9999 || nd < 1) {
        printf("MAX = 9999\n");
        usleep(2000000);
        nd=0;
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
    char z[6] = "";

    for (int i = 1; i <= nd; i++) {
        if (ln == 0 || i == 10 || i == 100 || i == 1000) {
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

            if (ln == 0 && i == 1) {
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
            print_with_padding("\033[7m(311)", pf1, z, i, 3);
            printf("\033[0m ");
        } else {
            print_with_padding("(311)", pf1, z, i, 3);
            printf(" ");
        }
        usleep(500);
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
            print_with_padding("\033[7m(311)", pf2, z, i, 3);
            printf("\033[0m ");
        } else {
            print_with_padding("(311)", pf2, z, i, 3);
            printf(" ");
        }
        usleep(500);
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
            print_with_padding("\033[7m(311)", pf3, z, i, 3);
            printf("\033[0m ");
        } else {
            print_with_padding("(311)", pf3, z, i, 3);
            printf(" ");
        }
        usleep(500);
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
            print_with_padding("\033[7m(311)", pf4, z, i, 3);
            printf("\033[0m \n");
        } else {
            print_with_padding("(311)", pf4, z, i, 3);
            printf(" \n");
        }
        usleep(500);
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

