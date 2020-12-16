/*
Program Name: Semester Project
Author Name: Jared Herne
Class Time and Day: Friday 1:30 - 4:20pm
Description: This program mimics a task manager as it preforms operations on processes. This 
	program creates, sorts, adds, kills, writes to a txt file, and displayes linked list data 
	based on user input. All data is semi-randomly generated.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "proj2.h"


int main()
{
	srand(time(NULL));

	char X = 'Q';
	int list_size;
	char buffer[100];
	struct process *listptr, *tmpptr;
	unsigned id_to_be_gone,id;

	printf(">>>>> Enter a value > 0:\n");
	gets(buffer);
	list_size = atoi(buffer);
	if (list_size <= 0)
		return printf("terminating ..........\n");

	listptr = list_intialize(list_size);
    while((X != 'T') && (listptr != NULL))
	{
		print_main_menu();
		printf(">>>>> Enter a command ");

	    while((X = getchar()) == '\n');
		X = toupper(X);

		switch(X)
		{
			case 'P':
			//Process list
				listptr = processList(listptr);
				break;
			
			case 'D':
			//Display list
				displayList(listptr);
				break;
			
			case 'A':
			//Add process
				listptr = addProcess(listptr);
				break;
			
			case 'E':
			//kill process
				displayList (listptr);
				getchar();
				printf(">>>>> Choose an ID number\n");
				id_to_be_gone = (unsigned) atoi(gets(buffer));
				if((tmpptr = killProcess(listptr,  id_to_be_gone)) != NULL)
					listptr = tmpptr;
				break;

			case 'M':
			//Sort by memory
				listptr = sortByMemory(listptr);
				break;

			case 'S':
			//Sort by date
				listptr = sortByDate(listptr);
				break;
			
			case 'T':
			//Terminate
				early_terminate_write(listptr);
				break;

			case 'V':	
			//Set Priority
				getchar();
				displayList(listptr);
				printf(">>>>> Choose an ID number\n");
				id = (unsigned)atoi(gets(buffer));
				if (setPriority(listptr,  id) == NULL)
					printf("ID is not in list...\n");
				break;
			
			case 'R':
			//Re-sort by process time
				listptr = resort(listptr);
				break;
		}
    
	}
	return 1;
}
