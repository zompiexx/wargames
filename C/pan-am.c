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
#define MAX_PASSENGERS 2
#define NAME_LENGTH 30

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
    char input[100];
    char buffer[200];
    int choice;
    char destination[100];
    int passengers_number = 0;
    char passenger_name[MAX_PASSENGERS][NAME_LENGTH];
    double fare = 1164.1;
    double tax = 70.9;
    double total_fare, total_tax, total;

    usleep(1000000);
	
    while(1) {	
        clear_screen();
        delayed_print("007:2312:435:936                                       PAN-AM RESERVATION SYSTEM\n");
        delayed_print("TERMINAL STATUS: ACTIVE\n\n");
        delayed_print("  1.  FLIGHT SCHEDULES\n");
        delayed_print("  2.  CREDIT CHECK\n");
        delayed_print("  3.  PASSENGER INFORMATION\n");
        delayed_print("  4.  SYSTEM STATUS FUNCTIONS\n");
        delayed_print("  5.  ALTERNATE ROUTINGS\n\n");
        delayed_print("MENU CHOICE: ");

        fgets(input, sizeof(input), stdin);

        if(input[0] == '\n') {
            usleep(1000000);
            break;
        }

        choice = atoi(input);  // convert string to int

        if(choice == 1){
            delayed_print("You selected FLIGHT SCHEDULES\n");
            usleep(1000000);
            // add flight schedules functionality here: start
            // add flight schedules functionality here: end
        }
        else if(choice == 2){
            delayed_print("You selected CREDIT CHECK\n");
            usleep(1000000);
            // add credit check functionality here: start
            // add credit check functionality here: end
        }
        else if(choice == 3){
            delayed_print("You selected PASSENGER INFORMATION\n");
            usleep(1000000);
            // add passenger information functionality here: start
            clear_screen();
            delayed_print("007:2312:435:936                                       PAN-AM RESERVATION SYSTEM\n");
            delayed_print("DESTINATION         : ");
            fgets(destination, sizeof(destination), stdin);
            
            // Convert destination to uppercase
            for (int i = 0; destination[i]; i++) {
                destination[i] = toupper(destination[i]);
            }

                      
            while(1) {
                clear_screen();
                delayed_print("007:2312:435:936                                       PAN-AM RESERVATION SYSTEM\n");
                delayed_print("DESTINATION         : ");
                delayed_print(destination);
                delayed_print("POINT OF DEPARTURE  : CHICAGO/O'HARE\n");
                delayed_print("\n009:4277:019:907                                        DATE OF ISSUE : 03/10/82\n");
                delayed_print("\n                                           DEPART DATE : 08/18/83    FLIGHT: 114\n");
                delayed_print("\n                            CARRIER:   FLIGHT:   CLASS:   DATE:   TIME:  STATUS:\n");
                delayed_print("                              PANAM       114       Q     18AUG  0815A    OK\n");
                delayed_print("FROM: CHICAGO/O'HARE\n"); 
                delayed_print("  TO: ");
                delayed_print(destination);
                delayed_print("\nNUMBER OF PASSENGERS  : ");
                scanf("%d", &passengers_number);
                if(passengers_number > MAX_PASSENGERS) {
                    sprintf(buffer, "MAX = %d\n", MAX_PASSENGERS);
                    delayed_print(buffer); 
                    usleep(1000000);
                }
                else {
                    break;
                }
            }
            getchar();  // consume newline

            for (int i = 0; i < passengers_number; i++) {
                sprintf(buffer, "NAME OF PASSENGER #  %d: ", i+1);
                delayed_print(buffer);
                fgets(passenger_name[i], NAME_LENGTH, stdin);
            }

            printf("\n");

            total_fare = fare * passengers_number;
            total_tax = tax * passengers_number;
            total = total_fare + total_tax;

            sprintf(buffer, "FARE:  %.2f", total_fare);
            delayed_print(buffer);
            delayed_print("   GJATWA  SLM  TWA  GJA\n");
            sprintf(buffer, "TAX:   %.2f\n", total_tax);
            delayed_print(buffer);
            sprintf(buffer, "TOTAL: %.2f\n", total);
            delayed_print(buffer);
            delayed_print("REQUEST: SPEC DATA\n\n");
            delayed_print("                         PRESS 'ENTER' KEY TO RETURN TO MENU");
            getchar();  // Wait for a carriage return
            usleep(1000000);
            // add passenger information functionality here: end
        }
        else if(choice == 4){
            delayed_print("You selected SYSTEM STATUS FUNCTIONS\n");
            usleep(1000000);
            // add system status functions functionality here: start
            // add system status functions functionality here: end
        }
        else if(choice == 5){
            delayed_print("You selected ALTERNATE ROUTINGS\n");
            usleep(1000000);
            // add alternate routings functionality here: start
            // add alternate routings functionality here: end
        }
        else{
            delayed_print("INVALID OPTION\n");
            usleep(1000000);
        }
    }

    delayed_print("CLOSING CONNECTION\n");
    delayed_print("--DISCONNECTED--\n");
    usleep(1000000);

    return 0;
}
