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

void clear_screen() {
    printf("\033[2J\033[H");
}

int main(){
	clear_screen();
	char command[100];
	char system_command[200];

	sleep(1);
	printf("64K CP/M VERS. 2.2 MCL030210-D-F8\n");
	printf("\n");
	imsai8080:
	printf("A>");
	scanf("%s", command);

	// Remove trailing newline character
    command[strcspn(command, "\n")] = '\0';

    // Convert input to lowercase
    for (int i = 0; command[i]; i++) {
        command[i] = tolower(command[i]);
    }

	if(strcmp(command,"cls")==0) {
		clear_screen();
		goto imsai8080;
	} 
	if(strcmp(command,"bye")==0) {
		printf("INT disabled and HALT Op-Code reached at 0101\n");
		goto bye;
	}
	if(strcmp(command,"dir")==0) {
		printf("A: BYE     COM : CLS     COM : DIALER  COM: DIR     COM\n");
		printf("A: KERMIT  COM\n");
		goto imsai8080;
	} 
    
    if(strcmp(command,"dialer")==0) {
        clear_screen();
        printf("DIALER\n\n");
        sleep(5);
        //start dialer program
        strcpy(command, "./dialer");
        // Execute the command using system()
        system(command);
		goto imsai8080;
	} 
  
	if(strcmp(command,"kermit")==0) {
		printf("Kermit-80 v4.11 configured for Generic CP/M-80 with Generic (Dumb) CRT Terminal\n");
		printf("type selected\n");
		printf("\n");
		printf("For help, type ? at any point in a command\n");
		sleep(2);
		printf("Kermit-80   0I:>set port uc1\n");
		sleep(2);
		kermit:
		printf("Kermit-80   0I:>");
		scanf("%s",command);
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
			snprintf(system_command, sizeof(system_command), "aplay 1200-modem.wav -q");
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
	}
	for(int i = 0; command[i]; i++){
      command[i] = toupper(command[i]);
    }
    printf("%s", command);
	printf("? \n");
	printf("\n");
	goto imsai8080;
	bye:
	return 0;
}

