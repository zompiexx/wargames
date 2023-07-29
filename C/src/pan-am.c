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

struct Reservation {
    char passenger_name[NAME_LENGTH];
    char flight_carrier[FLIGHT_CARRIER_LENGTH];
    char flight_number[FLIGHT_NUMBER_LENGTH];
    char flight_class[FLIGHT_CLASS_LENGTH];
    char departure_date[DEPARTURE_DATE_LENGTH];
    char departure_time[DEPARTURE_TIME];
    char departure_airport[AIRPORT_LENGTH];
    char destination_airport[AIRPORT_LENGTH];
    char smoking[SMOKING_LENGTH];
};

struct Reservation reservations[MAX_PASSENGERS];

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

void strip_newline(char *str) {
    int length = strlen(str);
    if (str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

void string_to_lower(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void save_reservation(int passengers_number, char passenger_name[][30], char flight_carrier[], char flight_number[], char flight_class[], char departure_date[], char departure_time[], char departure_airport[], char destination_airport[], char smoking[]) {
    // Strip newline characters from all fields
    for (int i = 0; i < passengers_number; i++) {
        strip_newline(passenger_name[i]);
    }
    strip_newline(flight_carrier);
    strip_newline(flight_number);
    strip_newline(flight_class);
    strip_newline(departure_date);
    strip_newline(departure_time);
    strip_newline(departure_airport);
    strip_newline(destination_airport);
    strip_newline(smoking);
    
    // Check if the file exists
    if (access("reservations.txt", F_OK) != -1) {
        // File exists
        FILE *file = fopen("reservations.txt", "r");
        if (file != NULL) {
            char line[200];
            int sameDataExists = 1;
            for (int i = 0; i < passengers_number; i++) {
                // Check if the same data already exists
                fgets(line, sizeof(line), file);
                if (strcmp(line, flight_carrier) != 0) sameDataExists = 0;
                fgets(line, sizeof(line), file);
                if (strcmp(line, flight_number) != 0) sameDataExists = 0;
                fgets(line, sizeof(line), file);
                if (strcmp(line, flight_class) != 0) sameDataExists = 0;
                fgets(line, sizeof(line), file);
                if (strcmp(line, departure_date) != 0) sameDataExists = 0;
                fgets(line, sizeof(line), file);
                if (strcmp(line, departure_time) != 0) sameDataExists = 0;
                fgets(line, sizeof(line), file);
                if (strcmp(line, departure_airport) != 0) sameDataExists = 0;
                fgets(line, sizeof(line), file);
                if (strcmp(line, destination_airport) != 0) sameDataExists = 0;
                fgets(line, sizeof(line), file);
                if (strcmp(line, smoking) != 0) sameDataExists = 0;
                fgets(line, sizeof(line), file);
            }
            fclose(file);
            if (sameDataExists) {
                printf("The same data already exists in the file. Not overwriting it.\n");
                return;
            }
        } else {
            printf("Error opening file.\n");
        }
    }

    // If file doesn't exist or the same data doesn't exist in the file, write the data to the file
    FILE* file = fopen("reservations.txt", "a");
    if(file != NULL) {
        for (int i = 0; i < passengers_number; i++) {
            fprintf(file, "PASSENGER NAME       : %s\n", passenger_name[i]); // use [i] to reference the correct string
            fprintf(file, "FLIGHT CARRIER       : %s\n", flight_carrier);
            fprintf(file, "FLIGHT NUMBER        : %s\n", flight_number);
            fprintf(file, "FLIGHT CLASS         : %s\n", flight_class);
            fprintf(file, "DEPARTURE DATE       : %s\n", departure_date);
            fprintf(file, "DEPARTURE TIME       : %s\n", departure_time);
            fprintf(file, "DEPARTURE AIRPORT    : %s\n", departure_airport);
            fprintf(file, "DESTINATION AIRPORT  : %s\n", destination_airport);
            fprintf(file, "SMOKING              : %s\n", smoking);
            fprintf(file, "\n");
        }
        fclose(file);
    } else {
        printf("Error opening file.\n");
    }

}

void search_reservation() {
    char search_name[NAME_LENGTH];
    char line[200];
    char line_lower[200];  // Lowercase version of the line
    int found = 0;
    char buffer[200];

    clear_screen();
    delayed_print("007:2312:435:936                                       PAN-AM RESERVATION SYSTEM\n");
    delayed_print("SEARCH\n\n");
    delayed_print("PASSENGER NAME: ");
    fgets(search_name, sizeof(search_name), stdin);
    strip_newline(search_name);
    string_to_lower(search_name);  // Convert search_name to lower case

    FILE* file = fopen("reservations.txt", "r");
    if(file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            strcpy(line_lower, line);  // Make a copy of the line
            string_to_lower(line_lower);  // Convert the line copy to lower case
            if (strstr(line_lower, search_name) != NULL) {  // Search in the lowercase line
                found = 1;
                delayed_print("\nRESERVATION FOUND\n\n");
                sprintf(buffer, "%s", line);
                delayed_print(buffer);
                for (int i = 0; i < 9; i++) {  // Print the next 9 lines (reservation details)
                    if (fgets(line, sizeof(line), file)) {
                        sprintf(buffer, "%s", line);
                        delayed_print(buffer);
                    }
                }
                delayed_print("\n");
            }
        }
        fclose(file);
        if (!found) {
            sprintf(buffer, "\nNO RESERVATION FOUND FOR: %s\n\n", search_name);
            delayed_print(buffer);
        }
    } else {
        delayed_print("Error opening file.\n");
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
        delayed_print("  2.  PASSENGER RESERVATIONS\n");
        delayed_print("  3.  SEARCH\n\n");
        delayed_print("MENU CHOICE: ");

        fgets(input, sizeof(input), stdin);

        if(input[0] == '\n') {
            usleep(1000000);
            break;
        }

        choice = atoi(input);  // convert string to int

        if(choice == 1){
            delayed_print("FLIGHT SCHEDULES\n");
            usleep(1000000);
            // add flight schedules functionality here: start
            // add flight schedules functionality here: end
        } else if(choice == 2){
            delayed_print("PASSENGER RESERVATIONS\n");
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

            delayed_print("SMOKING (Y/N)       : ");
            fgets(smoking, sizeof(smoking), stdin);
            
            // Convert destination to uppercase
            for (int i = 0; smoking[i]; i++) {
                smoking[i] = toupper(smoking[i]);
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
                delayed_print("\n               CARRIER:   FLIGHT:   CLASS:   SMOKING:   DATE:     TIME:  STATUS:\n");
                sprintf(buffer, "                %s       %s       %s         %s       %s/%s/%s  %s    OK\n",flight_carrier,flight_number,flight_class, smoking, month, day, year,departure_time);
                delayed_print(buffer);
                delayed_print("\n");
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
            save_reservation(passengers_number, passenger_name, flight_carrier, flight_number, flight_class, departure_date, departure_time, departure_airport, destination_airport, smoking);
            delayed_print("                         PRESS 'ENTER' KEY TO RETURN TO MENU");
            getchar();  // Wait for a carriage return
            usleep(1000000);
            // add passenger information functionality here: end
        } else if(choice == 3){
            delayed_print("SEARCH\n");
            usleep(1000000);
            search_reservation();
            delayed_print("                         PRESS 'ENTER' KEY TO RETURN TO MENU");
            getchar();  // Wait for a carriage return
            usleep(1000000);
        } else{
            delayed_print("INVALID OPTION\n");
            usleep(1000000);
        }
    }

    delayed_print("CLOSING CONNECTION\n");
    delayed_print("--DISCONNECTED--\n");
    usleep(1000000);

    return 0;
}
