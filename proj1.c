/*
Program Name: Semester Project
Author Name: Jared Herne
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj1.h"


char *description_source[]={"iTunes", "Skype", "Microsoft Word", "Microsoft Excel", "Microsoft Outlook", "Remote Desktop", "Instagram", "Zoom", "Facebook", "Canvas", "Microsoft Visual Studio", "Twitter"};
int mem[7]={7000,3000,9000,2000,1400,2300,4100};


//Prints the main menu choices
void print_main_menu()
{
	printf("*******************************************************\n");
	printf("                Main Menu\n");
	printf("*******************************************************\n");

	printf("\tP\t\tProcess list\n");
	printf("\tD\t\tDisplay list\n");
	printf("\tA\t\tAdd process\n");
	printf("\tE\t\tKill process\n");
	printf("\tS\t\tSort by age\n");
	printf("\tM\t\tSort by memory\n");
	printf("\tT\t\tTerminate\n");
	printf("\tR\t\tRe-sort by process time\n");
	printf("\tV\t\tSet Priority\n");
	
	printf("*******************************************************\n");
}

//Propogates a process with random data
void generate_random_process(struct process *P)
{
	static int id = 1011;
	static int visited = 0;
	int j;

	j = sizeof(description_source) / sizeof(char*);

	if(visited == 0)
		visited = 1;
	else
		id++;
	P->date = 0;
	P->processID = id;
	P->processMemory = mem[rand() % 7];
	P->processTime = 1 + (rand() % 3) + 2 * (rand() % 3);
	strcpy(P->description, description_source[rand() % j]);
	P->priority = -2 + (rand() % 5);

	P->next=NULL;
}
