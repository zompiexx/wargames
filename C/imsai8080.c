#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define clrscr() printf("\e[1;1H\e[2J")
int main(){
	clrscr();
	char command[1];
	char schpass[1];
	char student[1];
	char grade[2];
	sleep(1);
	printf("64K CP/M VERS. 2.2 MCL030210-D-F8\n");
	printf("\n");
	imsai8080:
	printf("A>");
	scanf("%s", command);
	if(strcmp(command,"cls")==0)
	{
		clrscr();
		goto imsai8080;
	} 
	if(strcmp(command,"bye")==0)
	{
		printf("INT disabled and HALT Op-Code reached at 0101\n");
		goto bye;
	}
	if(strcmp(command,"dir")==0)
	{
		printf("A: BYE     COM : CLS     COM : DIALER  COM: DIR     COM\n");
		printf("A: KERMIT  COM\n");
		goto imsai8080;
	}   
	if(strcmp(command,"kermit")==0)
	{
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
		if(strcmp(command,"connect")==0)
		{
			printf("Connected to remote host.  Type Control-C to return\n");
			printf("type Control-? for command list\n");
			sleep(2);
			printf("ATDT3115554855\n");
			sleep(5);
			clrscr();
			printf("PDP 11/270 PRB TIP #45                                                TTY 34/984\n");
			printf("WELCOME TO THE SEATTLE PUBLIC SCHOOL DISTRICT DATANET\n");
			printf("\n");
			schlogon:
			printf("PLEASE LOGON WITH USER PASSWORD: ");
			scanf("%s",schpass);
			if(strcmp(schpass,"pencil")==0)
			{
				student:
				printf("PLEASE ENTER STUDENT NAME: ");
				scanf("%s",student);
			}
			else {
				printf("INVALID PASSWORD\n");
				printf("\n");
				goto schlogon;
			}
            if (strcmp(student,"exit")==0)
            {
                printf("\n");
                printf("--DISCONNECTED--\n");
                printf("\n");
                goto kermit;
            }
			if(strcmp(student,"lightman")==0)
			{
				printf("\n");
				printf("STUDENT RECORD: Lightman, David L.\n");
				printf("\n");
				printf("     CLASS #    COURSE TITLE         GRADE    TEACHER    PERIOD    ROOM\n");
				printf("   ______________________________________________________________________\n");
				printf("\n");
				printf("      S-202     BIOLOGY 2              ");
				printf("F");
				printf("      LIGGET       3       214\n");
				printf("      E-314     ENGLISH 11B            D      TURMAN       5       172\n");
				printf("      H-221     WORLD HISTORY 11B      C      DWYMER       2       108\n");
				printf("      M-106     TRIG 2                 B      DICKERSON    4       315\n");
				printf("      PE-02     PHYSICAL EDUCATION     C      COMSTOCK     1       GYM\n");
				printf("      M-122     CALCULUS 1             B      LOGAN        6       240\n");
				printf("\n");
				goto student;
			}
			if(strcmp(student,"mack")==0)
			{
				printf("\n");
				printf("STUDENT RECORD: Mack, Jennifer K.\n");
				printf("\n");
				printf("     CLASS #    COURSE TITLE         GRADE    TEACHER    PERIOD    ROOM\n");
				printf("   ______________________________________________________________________\n");
				printf("\n");
				printf("      S-202     BIOLOGY 2              ");
				printf("F");
				printf("      LIGGET       3       214\n");
				printf("      E-325     ENGLISH 11B            A      ROBINSON     1       114\n");
				printf("      H-221     WORLD HISTORY 11B      B      DWYER        2       108\n");
				printf("      M-104     GEOMETRY 2             D      HALQUIST     4       307\n");
				printf("      B-107     ECONOMICS              D      MARKS        5       122\n");
				printf("      PE-02     PHYSICAL EDUCATION     C      COMSTOCK     6       GYM\n");
				printf("\n");
				goto student;
			}
            else {
                printf("\n");
                printf("NO STUDENT RECORD FOUND\n");
                printf("\n");
                goto student;
            }
		}
	goto kermit;   
	}
	printf("%s", command);
	printf("? \n");
	printf("\n");
	goto imsai8080;
	bye:
	return 0;
}
