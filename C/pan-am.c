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
#define FLIGHT_NUMBER_LENGTH 10
#define DEPARTURE_DATE_LENGTH 9
#define DEPARTURE_TIME 5
#define AIRPORT_LENGTH 50
#define SMOKING_LENGTH 2
#define FLIGHT_CARRIER_LENGTH 10
#define FLIGHT_CLASS_LENGTH 2

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
    int passengers_number = 0;
    char passenger_name[MAX_PASSENGERS][NAME_LENGTH];
    double fare = 1164.1;
    double tax = 70.9;
    double total_fare, total_tax, total;

    // New variables
    char flight_carrier[FLIGHT_CARRIER_LENGTH];
    char flight_number[FLIGHT_NUMBER_LENGTH];
    char flight_class[FLIGHT_CLASS_LENGTH];
    char departure_date[DEPARTURE_DATE_LENGTH];
    char departure_time[DEPARTURE_TIME];
    char departure_airport[AIRPORT_LENGTH];
    char destination_airport[AIRPORT_LENGTH];
    char smoking[SMOKING_LENGTH];
    char month[3];
    char day[3];
    char year[3];

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
            fgets(destination_airport, sizeof(destination_airport), stdin);
            
            // Convert destination to uppercase
            for (int i = 0; destination_airport[i]; i++) {
                destination_airport[i] = toupper(destination_airport[i]);
            }

                      
            while(1) {
                clear_screen();
                delayed_print("007:2312:435:936                                       PAN-AM RESERVATION SYSTEM\n");
                delayed_print("DESTINATION         : ");
                delayed_print(destination_airport);
                delayed_print("POINT OF DEPARTURE  : CHICAGO/O'HARE\n");

                //set flight variables: start
                strcpy(departure_airport, "CHICAGO/O'HARE");
                strcpy(flight_carrier, "PANAM");
                strcpy(flight_number, "114");
                strcpy(flight_class, "Q");
                strcpy(departure_date, "081883");
                strcpy(departure_time, "0815");

            

                // Copy two characters starting at index 0 to month.
                strncpy(month, departure_date, 2);
                month[2] = '\0';  // Null-terminate the string.

                // Copy two characters starting at index 2 to day.
                strncpy(day, departure_date+2, 2);
                day[2] = '\0';  // Null-terminate the string.

                // Copy two characters starting at index 4 to year.
                strncpy(year, departure_date+4, 2);
                year[2] = '\0';  // Null-terminate the string.

                delayed_print("\n009:4277:019:907                                        DATE OF ISSUE : 03/10/82\n");
                delayed_print("\n                                           DEPART DATE : 08/18/83    FLIGHT: 114\n");
                delayed_print("\n                          CARRIER:   FLIGHT:   CLASS:   DATE:    TIME:  STATUS:\n");
                sprintf(buffer, "                           %s       %s       %s     %s/%s/%s  %s    OK\n",flight_carrier,flight_number,flight_class, month, day, year,departure_time);
                delayed_print(buffer);
                delayed_print("FROM: CHICAGO/O'HARE\n"); 
                delayed_print("  TO: ");
                delayed_print(destination_airport);
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
