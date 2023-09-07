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

#define COMMAND_LEN 9     // 8 characters + null terminator
#define EXTENSION_LEN 4   // 3 characters + null terminator
#define ACTION_LEN 100
#define MAX_COMMANDS 1000
#define ENTRIES_PER_LINE 4

typedef struct {
    char command[COMMAND_LEN];
    char extension[EXTENSION_LEN];
    char action[ACTION_LEN];
} Command;

Command commands[MAX_COMMANDS];

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void toUpperCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void clear_screen() {
    printf("\033[2J\033[H");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readFile() {
    FILE *file;
    int index = 0;

    file = fopen("cpm_commands.txt", "r");

    if (file == NULL) {
        file = fopen("cpm_commands.txt", "w");
        if (file == NULL) {
            perror("Error creating cpm_commands.txt");
            exit(EXIT_FAILURE);
        }
        printf("File cpm_commands.txt created successfully.\n");
        fclose(file);
        return;
    }

    while (index < MAX_COMMANDS && fscanf(file, "%8s\n%3s\n%[^\n]\n", commands[index].command, commands[index].extension, commands[index].action) == 3) {
        toLowerCase(commands[index].command);
        toLowerCase(commands[index].extension);
        index++;
    }

    fclose(file);
    //printf("Loaded %d commands from the file.\n", index);
}

void printCommands() {
    char upperCommand[COMMAND_LEN];
    char upperExtension[EXTENSION_LEN];
    int firstCommandInLine = 1; // This flag is to check if the command is the first in a line

    for (int i = 0; i < MAX_COMMANDS && commands[i].command[0] != 0; i++) {
        strcpy(upperCommand, commands[i].command);
        strcpy(upperExtension, commands[i].extension);
        toUpperCase(upperCommand);
        toUpperCase(upperExtension);

        // Print prefix if it's the first command in a line
        if (firstCommandInLine) {
            printf("B: ");
            firstCommandInLine = 0; // Reset the flag
        }

        printf("%s", upperCommand);
        for (int j = strlen(upperCommand); j < 8; j++) {
            printf(" ");
        }
        printf(" %.3s", upperExtension);

        if ((i + 1) % ENTRIES_PER_LINE == 0 || commands[i+1].command[0] == 0) {
            printf("\n");
            firstCommandInLine = 1; // Set the flag for the next line
        } else {
            printf(" : ");
        }
    }
}

void promptAndExecute(const char *inputCommand) {
    char fullCmd[COMMAND_LEN + EXTENSION_LEN + 1];
    char input[COMMAND_LEN + EXTENSION_LEN + 1];
    strncpy(input, inputCommand, sizeof(input) - 1);  // Copy inputCommand to input

    toLowerCase(input);

    for (int i = 0; i < MAX_COMMANDS && commands[i].command[0] != 0; i++) {
        if (strcmp(input, commands[i].command) == 0) {
            //printf("Executing action: %s\n", commands[i].action);
            system(commands[i].action);
            return;
        }

        sprintf(fullCmd, "%s.%s", commands[i].command, commands[i].extension);
        if (strcmp(input, fullCmd) == 0) {
            //printf("Executing action: %s\n", commands[i].action);
            system(commands[i].action);
            return;
        }
    }
	toUpperCase(input);
	printf("%s", input);
	printf("? \n");
	printf("\n");

}

int main(){
	clear_screen();
	char command[100];
	char system_command[200];
	char prompt[3];
	
	strcpy(prompt, "A");

	readFile();

	sleep(1);
	printf("64K CP/M VERS. 2.2 MCL030210-D-F8\n");
	printf("\n");
	imsai8080:
	printf("%s>",prompt);
	//scanf("%s", command);
	fgets(command, sizeof(command), stdin);
	
	if(command[0] == '\0') { // if command is empty
		printf("\n");
    	goto imsai8080;
	}

	// Remove trailing newline character
    command[strcspn(command, "\n")] = '\0';

    // Convert input to lowercase
    for (int i = 0; command[i]; i++) {
        command[i] = tolower(command[i]);
    }

	if(strcmp(command,"cls")==0) {
		clear_screen();
		goto imsai8080;
	} else if(strcmp(command,"b:")==0) {
		strcpy(prompt, "B");
		goto imsai8080;
	} else if(strcmp(command,"a:")==0) {
		strcpy(prompt, "A");
		goto imsai8080;
	} else if(strcmp(command,"bye")==0 && strcmp(prompt,"A")==0) {
		printf("INT disabled and HALT Op-Code reached at 0101\n");
		goto bye;
	} else if(strcmp(command,"dir")==0 && strcmp(prompt,"A")==0) {
		printf("A: BYE      COM : CLS      COM : DIALER   COM : DIR      COM\n");
		printf("A: KERMIT   COM\n");
		goto imsai8080;
	} else if(strcmp(command,"dir a:")==0) {
		printf("A: BYE      COM : CLS      COM : DIALER   COM : DIR      COM\n");
		printf("A: KERMIT   COM\n");
		goto imsai8080;
	} else if(strcmp(command,"dir")==0 && strcmp(prompt,"B")==0) {
		printCommands();
		goto imsai8080;
	} else if(strcmp(command,"dir b:")==0) {
		printCommands();
		goto imsai8080;
	} else if(strcmp(command,"dialer")==0 && strcmp(prompt,"A")==0) {
        clear_screen();
        printf("DIALER\n\n");
        sleep(2);
        //start dialer program
        strcpy(command, "./dialer");
        // Execute the command using system()
        system(command);
		goto imsai8080;
	} else if(strcmp(command,"kermit")==0 && strcmp(prompt,"A")==0) {
		printf("Kermit-80 v4.11 configured for Generic CP/M-80 with Generic (Dumb) CRT Terminal\n");
		printf("type selected\n");
		printf("\n");
		printf("For help, type ? at any point in a command\n");
		sleep(2);
		printf("Kermit-80   0I:>set port uc1\n");
		sleep(2);
		kermit:
		printf("Kermit-80   0I:>");

		fgets(command, sizeof(command), stdin);
		
		if(command[0] == '\0') { // if command is empty
			printf("\n");
    		goto kermit;
		}

		// Remove trailing newline character
    	command[strcspn(command, "\n")] = '\0';

    	// Convert input to lowercase
    	for (int i = 0; command[i]; i++) {
        	command[i] = tolower(command[i]);
    	}

		if(strcmp(command,"?")==0)
		{
			printf("CONNECT to host on selected port\n");
			printf("\n");
		sleep(1);
		}
		if(strcmp(command,"quit")==0)
		{
			goto imsai8080;
		}
		if(strcmp(command,"connect")==0) {
			printf("Connected to remote host.  Type Control-C to return\n");
			printf("type Control-? for command list\n");
			sleep(2);
			printf("ATDT3115554855\n");
			snprintf(system_command, sizeof(system_command), "aplay samples/dtmf-wopr.wav -q");
            system(system_command);
            usleep(250000);
			snprintf(system_command, sizeof(system_command), "aplay samples/1200-modem.wav -q");
    		system(system_command);
			sleep(5);
			clear_screen();
            printf("CONNECTING\n\n");
            sleep(5);
            //connect to school computer
            strcpy(command, "./school");
            // Execute the command using system()
            system(command);
        }
		goto kermit;   
	} else if(command[0] == '\0') { // if command is empty
		goto imsai8080;
	} else if(strcmp(prompt,"B")==0) {
		promptAndExecute(command);
		goto imsai8080;
	} else {
		toUpperCase(command);
    	printf("%s", command);
		printf("? \n");
		printf("\n");
		goto imsai8080;
	}
	
	goto imsai8080;
	bye:
	return 0;
}

