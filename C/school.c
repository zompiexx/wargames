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

void strip_newline(char* str) {
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
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

    printf("Enter name: ");
    fgets(new_student.name, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.name);

    printf("Enter class: ");
    fgets(new_student.class, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.class);

    printf("Enter course: ");
    fgets(new_student.course, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.course);

    printf("Enter grade: ");
    new_student.grade = getchar();
    getchar(); // consume the '\n' left by getchar

    printf("Enter teacher: ");
    fgets(new_student.teacher, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.teacher);

    printf("Enter period: ");
    fgets(new_student.period, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.period);

    printf("Enter room: ");
    fgets(new_student.room, MAX_FIELD_LENGTH, stdin);
    strip_newline(new_student.room);

    students[student_count++] = new_student;
}

void read_data() {
	student_count = 0;
    FILE* file = fopen("students.txt", "r");
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

void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void search_data(char *query) {
    int found = 0;
    char name[MAX_FIELD_LENGTH];

    to_lower_case(query);  // convert the query to lower case

    for (int i = 0; i < student_count; i++) {
        strcpy(name, students[i].name);
        to_lower_case(name);  // convert the student name to lower case

        if (strstr(name, query) != NULL) {
            if (!found) {
                printf("\nSTUDENT RECORD: %s\n", students[i].name);
                printf("\n   CLASS #    COURSE TITLE         GRADE    TEACHER    PERIOD   ROOM\n");
                printf("______________________________________________________________________\n\n");
                found = 1;
            }
            
            printf("   %-10s %-20s %c        %-10s %-8s %s\n", students[i].class, students[i].course, 
                    students[i].grade, students[i].teacher, students[i].period, students[i].room);
        }
    }

    if (!found) {
        printf("No match found for the given query\n");
    } else {
        printf("\n");
    }
}


void output_data() {
    for (int i = 0; i < student_count; i++) {
        printf("Student: %s, %s, %s, %c, %s, %s, %s\n", students[i].name, students[i].class, 
               students[i].course, students[i].grade, students[i].teacher, students[i].period, students[i].room);
    }
}

void show_menu() {
    int choice;
    char query[MAX_FIELD_LENGTH];
    while (1) {
		printf("\n");
        printf("MENU:\n");
        printf("1. INPUT STUDENT DATA\n");
        printf("2. STORE STUDENT DATA TO A FILE\n");
        printf("3. READ STUDENT DATA FROM FILE\n");
        printf("4. SEARCH FOR A STUDENT\n");
        printf("5. DISPLAY ALL STUDENT DATA\n");
        printf("6. EXIT\n\n");
        printf("SELECT OPTION: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character left by scanf
        switch (choice) {
            case 1:
                input_data();
                break;
            case 2:
                store_data();
                break;
            case 3:
                read_data();
                break;
            case 4:
                printf("Enter search query: ");
                fgets(query, MAX_FIELD_LENGTH, stdin);
                query[strcspn(query, "\n")] = 0; // remove the newline character left by fgets
                search_data(query);
                break;
            case 5:
                output_data();
                break;
            case 6:
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
	
	
	while (1) {
		clear_screen();
		delayed_print("PDP 11/270 PRB TIP #45                                                TTY 34/984\n");
		delayed_print("WELCOME TO THE SEATTLE PUBLIC SCHOOL DISTRICT DATANET\n");
		delayed_print("\n");

		delayed_print("PLEASE LOGON WITH USER PASSWORD: ");
		tcgetattr(STDIN_FILENO, &term);
    	term_orig = term; // Save original settings

    	// Turn off ECHO
    	term.c_lflag &= ~ECHO;
    	tcsetattr(STDIN_FILENO, TCSANOW, &term);
		fgets(password, sizeof(password), stdin);
		// Restore original terminal settings
    	tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
		
        // Remove trailing newline character
        password[strcspn(password, "\n")] = '\0';

        // Convert input to lowercase
        for (int i = 0; password[i]; i++) {
            input[i] = tolower(password[i]);
        }

	if (strcmp(password, "pencil") == 0) {
            delayed_print("\n");
			break;  // Exit the while loop
            
	} else {
				delayed_print("\n");
				delayed_print("INVALID PASSWORD\n");
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
		read_data();
		show_menu();
        
        exit(0);
      
}



