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
#define MAX_STUDENTS 100
#define MAX_FIELD_LENGTH 100
#define MAX_BUFFER_LENGTH 1024

typedef struct {
    char name[MAX_FIELD_LENGTH];
    char class[MAX_FIELD_LENGTH];
    char course[MAX_FIELD_LENGTH];
    char grade;
    char teacher[MAX_FIELD_LENGTH];
    char period[MAX_FIELD_LENGTH];
    char room[MAX_FIELD_LENGTH];
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

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

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clear_screen() {
    delayed_print("\033[2J\033[H");
}

void strip_newline(char *str) {
    int len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void store_data() {
    FILE* file = fopen("students.txt", "w");
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s\n%s\n%s\n%c\n%s\n%s\n%s\n", students[i].name, students[i].class, students[i].course, 
                students[i].grade, students[i].teacher, students[i].period, students[i].room);
    }
    fclose(file);
}

void input_data() {
    Student new_student;
    char buffer[MAX_BUFFER_LENGTH];

    snprintf(buffer, MAX_BUFFER_LENGTH, "NAME: ");
    delayed_print(buffer);
    fgets(new_student.name, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.name);

    snprintf(buffer, MAX_BUFFER_LENGTH, "CLASS: ");
    delayed_print(buffer);
    fgets(new_student.class, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.class);

    snprintf(buffer, MAX_BUFFER_LENGTH, "COURSE: ");
    delayed_print(buffer);
    fgets(new_student.course, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.course);

    snprintf(buffer, MAX_BUFFER_LENGTH, "GRADE: ");
    delayed_print(buffer);
    new_student.grade = getchar();
    getchar(); // consume the '\n' left by getchar

    snprintf(buffer, MAX_BUFFER_LENGTH, "TEACHER: ");
    delayed_print(buffer);
    fgets(new_student.teacher, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.teacher);

    snprintf(buffer, MAX_BUFFER_LENGTH, "PERIOD: ");
    delayed_print(buffer);
    fgets(new_student.period, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.period);

    snprintf(buffer, MAX_BUFFER_LENGTH, "ROOM: ");
    delayed_print(buffer);
    fgets(new_student.room, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.room);

    students[student_count++] = new_student;
    store_data();
}

void read_data() {
	student_count = 0;
    FILE* file = fopen("students.txt", "r");

    // If the file does not exist
    if(file == NULL) {
        // Create the file
        file = fopen("students.txt", "w");
        fclose(file);
        // Open the file again for reading
        file = fopen("students.txt", "r");
    }

    Student new_student;
    char line[MAX_FIELD_LENGTH];

    while (fgets(line, MAX_FIELD_LENGTH, file) != NULL) {
        strip_newline(line);
        strcpy(new_student.name, line);

        if(fgets(line, MAX_FIELD_LENGTH, file) == NULL) break;
        strip_newline(line);
        strcpy(new_student.class, line);

        if(fgets(line, MAX_FIELD_LENGTH, file) == NULL) break;
        strip_newline(line);
        strcpy(new_student.course, line);

        new_student.grade = fgetc(file);
        if (new_student.grade == EOF) break;
        fgetc(file); // consume the '\n' left by fgetc

        if(fgets(line, MAX_FIELD_LENGTH, file) == NULL) break;
        strip_newline(line);
        strcpy(new_student.teacher, line);

        if(fgets(line, MAX_FIELD_LENGTH, file) == NULL) break;
        strip_newline(line);
        strcpy(new_student.period, line);

        if(fgets(line, MAX_FIELD_LENGTH, file) == NULL) break;
        strip_newline(line);
        strcpy(new_student.room, line);

        students[student_count++] = new_student;
    }
    fclose(file);
}

// Helper function to convert string to lower case
void to_lower_case(char *str) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void delete_record(int idx) {
    if (idx < student_count - 1) {
        // Shift elements left to overwrite the student record at idx
        for (int i = idx; i < student_count - 1; i++) {
            students[i] = students[i + 1];
        }
    }
    // Decrease student_count to 'remove' the last element
    student_count--;
}

void search_data(char *query) {
    int found = 0;
    int student_indices[MAX_STUDENTS];  // To store indices of the found students
    int found_count = 0;
    char name[MAX_FIELD_LENGTH];
    char buffer[MAX_BUFFER_LENGTH];

    to_lower_case(query);  // convert the query to lower case

    for (int i = 0; i < student_count; i++) {
        strcpy(name, students[i].name);
        to_lower_case(name);  // convert the student name to lower case

        if (strstr(name, query) != NULL) {
            if (!found) {
                snprintf(buffer, MAX_BUFFER_LENGTH, "\nSTUDENT RECORD: %s\n", students[i].name);
                delayed_print(buffer);
                delayed_print("\n   CLASS #    COURSE TITLE         GRADE    TEACHER    PERIOD   ROOM\n");
                delayed_print("______________________________________________________________________\n\n");
                found = 1;
            }

            snprintf(buffer, MAX_BUFFER_LENGTH, "   %-10s %-20s %c        %-10s %-8s %s\n", students[i].class, students[i].course, 
                    students[i].grade, students[i].teacher, students[i].period, students[i].room);
            delayed_print(buffer);

            student_indices[found_count++] = i;  // save index of found student
        }
    }

    if (!found) {
        delayed_print("NO MATCH\n");
    } else {
        delayed_print("\n");
    }

    // If a matching record is found, provide the option to edit, delete the record or return to main menu
    if (found_count > 0) {
        char option;
        char optionBuffer[3];  // Buffer to hold the input and newline character
        delayed_print("OPTIONS: E(DIT), D(ELETE), R(ETURN): ");
        fgets(optionBuffer, 3, stdin);
        option = optionBuffer[0];

        option = toupper(option);

        if (option == 'E') {
            char classNum[MAX_FIELD_LENGTH];
            delayed_print("CLASS TO CHANGE GRADE FOR: ");
            fgets(classNum, MAX_FIELD_LENGTH, stdin);
            strip_newline(classNum); // remove newline character
            to_lower_case(classNum); // convert classNum to lower case

            // find the student with the matching class number
            int idx = -1;
            for (int i = 0; i < found_count; i++) {
                char tempClass[MAX_FIELD_LENGTH];
                strcpy(tempClass, students[student_indices[i]].class);
                to_lower_case(tempClass); // convert class to lower case
                if (strcmp(tempClass, classNum) == 0) {
                    idx = student_indices[i];
                    break;
                }
            }

            if (idx == -1) {
                delayed_print("NO MATCH ON CLASS FOR STUDENT.\n");
            } else {
                delayed_print("NEW GRADE: ");
                char tempGrade = toupper(getchar());
                getchar(); // consume the '\n' left by getchar
                students[idx].grade = tempGrade;
                delayed_print("STUDENT RECORD UPDATED.\n");
                store_data();
            }
        } else if (option == 'D') {
            char classNum[MAX_FIELD_LENGTH];
            delayed_print("CLASS FOR RECORD TO BE DELETED: ");
            fgets(classNum, MAX_FIELD_LENGTH, stdin);
            strip_newline(classNum); // remove newline character
            to_lower_case(classNum); // convert classNum to lower case

            // find the student with the matching class number
            int idx = -1;
            for (int i = 0; i < found_count; i++) {
                char tempClass[MAX_FIELD_LENGTH];
                strcpy(tempClass, students[student_indices[i]].class);
                to_lower_case(tempClass); // convert class to lower case
                if (strcmp(tempClass, classNum) == 0) {
                    idx = student_indices[i];
                    break;
                }
            }

            if (idx == -1) {
                delayed_print("NO MATCH ON CLASS FOR STUDENT.\n");
            } else {
                char confirm;
                char confirmBuffer[3];
                delayed_print("ARE YOU SURE? (Y/N): ");
                fgets(confirmBuffer, 3, stdin);
                confirm = confirmBuffer[0];
                confirm = toupper(confirm);

                if (confirm == 'Y') {
                    delete_record(idx);
                    delayed_print("STUDENT RECORD DELETED.\n");
                    store_data();
                } else {
                    delayed_print("OPERATION CANCELLED.\n");
                }
            }
        } else if (option == 'R' || option == '\r') {
            //delayed_print("Returning to main menu.\n");
            return;
        } else {
            //delayed_print("Invalid option. Returning to main menu.\n");
        }
    }
}

void output_data() {
    char output[MAX_FIELD_LENGTH*7]; // large enough to hold a full line
    for (int i = 0; i < student_count; i++) {
        sprintf(output, "Student: %s, %s, %s, %c, %s, %s, %s\n", students[i].name, students[i].class, 
               students[i].course, students[i].grade, students[i].teacher, students[i].period, students[i].room);
        delayed_print(output);
    }
}

void show_menu() {
    int choice;
    char query[MAX_FIELD_LENGTH];
    char buffer[MAX_BUFFER_LENGTH];
    char choice_str[MAX_FIELD_LENGTH];
    while (1) {
        delayed_print("\n");
        delayed_print("MENU:\n");
        delayed_print("1. INPUT STUDENT DATA\n");
        delayed_print("2. SEARCH FOR A STUDENT\n");
        delayed_print("3. DISPLAY ALL STUDENT DATA\n");
        delayed_print("4. EXIT\n\n");
        delayed_print("SELECT OPTION: ");
        fgets(choice_str, MAX_FIELD_LENGTH, stdin);
        strip_newline(choice_str);
        choice = atoi(choice_str);
        switch (choice) {
            case 1:
                input_data();
                break;
            case 2:
                delayed_print("ENTER SEARCH QUERY: ");
                fgets(query, MAX_FIELD_LENGTH, stdin);
                query[strcspn(query, "\n")] = 0; // remove the newline character left by fgets
                search_data(query);
                break;
            case 3:
                output_data();
                break;
            case 4:
                delayed_print("\n");
                delayed_print("--DISCONNECTED--\n");
                usleep(1000000);
                exit(0);
        }
    }
}

void school_computer() {
    char input[100];
    char password[100];
    struct termios term, term_orig;
    char buffer[MAX_BUFFER_LENGTH];
    int attempts = 0;
    while (1) {
        clear_screen();
        delayed_print("PDP 11/270 PRB TIP #45                                                TTY 34/984\n");
        delayed_print("WELCOME TO THE SEATTLE PUBLIC SCHOOL DISTRICT DATANET\n");
        delayed_print("\n");
        delayed_print("PLEASE LOGON WITH USER PASSWORD: ");
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

        if (strcmp(password, "pencil") == 0) {
            delayed_print("\n");
            break;  // Exit the while loop
        } else {
            delayed_print("\n");
            delayed_print("INVALID PASSWORD\n");
            delayed_print("\n");
            usleep(1000000);
            attempts++;
            if(attempts >= 3){
                delayed_print("TOO MANY UNSUCCESSFUL LOGON ATTEMPTS\n");
                delayed_print("--DISCONNECTED--\n");
                exit(0);
            }
        }
    }
}

int main() {

        // Clear screen
        clear_screen();

        // Send "LOGON: " to the client
        school_computer();
		read_data();
		show_menu();
        
        exit(0);
      
}



