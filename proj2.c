/*
Program Name: Semester Project
Author Name: Jared Herne
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj1.h"
#include "proj2.h"


//Increments the priority (up to 2) of a struct with an inputted process ID
struct process *setPriority(struct process *P, unsigned to_be_changed)
{	// (8 points)

	struct process* curr;

	curr = P;
	while (curr != NULL) {
		if (curr->processID == to_be_changed) {
			if (curr->priority != 2)
				curr->priority++;
			return P;
		}
		curr = curr->next;
	}

	return NULL;
}

//Propogates a link list of an inputted size with random data 
struct process *list_intialize(unsigned int listsize)
{	// (25 points)
	
	struct process *head, *temp, *new;
	int i;
	
	if (listsize == 0) {
		printf("INVALID INPUT");
		return NULL;
	}

	head = (struct process*)malloc(sizeof(struct process));
	generate_random_process(head);
	if (listsize == 1)
		return head;

	for (i = 0; i < listsize - 1; i++) {
		temp = head;
		new = (struct process*)malloc(sizeof(struct process));
		generate_random_process(new);

		if (temp->processTime > new->processTime) {
			new->next = temp;
			head = new;
		}
		else
		{
			while (temp->next != NULL)
			{
				if (temp->next->processTime > new->processTime) {
					new->next = temp->next;
					temp->next = new;
					break;
				}
				else
					temp = temp->next;
			}
			temp->next = new;
		}
	}
	return head;	
}

/*In total memory is less than 12000 process time is decremented else only the first 
7 process times and priority 2 structs are decremented. If time = 0, then get rid of
(free) the process. Age each process by 1*/
struct process *processList(struct process *P)
{	// (29 points)

	struct process *curr, *temp;
	unsigned long totalMem = 0;
	int i = 0;

	curr = P;
	while (curr != NULL) {
		totalMem += curr->processMemory;
		curr->date++;
		curr = curr->next;
	}
	curr = P;
	if (totalMem <= 12000)
		while (curr != NULL) {
			curr->processTime--;
			curr = curr->next;
		}
	else {
		while (curr != NULL && i != 7) {
			curr->processTime--;
			i++;
			curr = curr->next;
		}
		while (curr != NULL) {
			if (curr->priority == 2)
				curr->processTime--;
			curr = curr->next;
		}
	}
	curr = P;
	while (curr != NULL) {
		if (curr->processTime == 0) {
			temp = curr;
			curr = curr->next;
			P = killProcess(P, temp->processID);
		}
		else
			curr = curr->next;
	}
	return P;
}

//Displays the linked list along with some totals and averages
void displayList(struct process *P)
{	// (15 points)

	unsigned long totalMem = 0, totalTime = 0, totalPrio = 0, totalDate = 0;
	double averageMem, averageTime, averagePrio, averageDate;
	int numOfProcess = 0;
	int i;

	for (i = 0; i < 55; i++)
		printf("*");
	printf("\n");

	printf("%-35s %-6s %-6s %-10s %-6s %-2s\n\n", "Description", "ID", "Time", "Memory", "Date", "Priority");
	while (P != NULL) {
		printf("%-35s %-6lu %-6lu %-10lu %-6lu %-2d\n", P->description, P->processID, P->processTime, P->processMemory, P->date, P->priority);
		totalMem += P->processMemory;
		totalTime += P->processTime;
		totalPrio += P->priority;
		totalDate += P->date;
		numOfProcess++;
		P = P->next;
	}

	for (i = 0; i < 55; i++)
		printf("*");
	printf("\n");
	
	printf("%-35s %-6s %-6lu %-10lu %-6s %-2s\n", "Totals", "", totalTime, totalMem, "", "");


	averageMem = totalMem / (double)numOfProcess;
	averageTime = totalTime / (double)numOfProcess;
	averagePrio = totalPrio / (double)numOfProcess;
	averageDate = totalDate / (double)numOfProcess;

	printf("%-35s %-6s %-6.2lf %-10.2lf %-6.2lf %-2.2lf\n", "Averages", "", averageTime, averageMem, averageDate, averagePrio);
	printf("Number of Processes = %-15d\n", numOfProcess);

	for (i = 0; i < 55; i++)
		printf("*");
	printf("\n");
}

//Prints a given number of spaces
void space_print(int num)
{
        while(num-- > 0)
                putchar(' ');
}

//Resorts the link list by time and adds a random process sorted by the time
struct process *addProcess(struct process *P)
{	// (10 points)

	struct process* curr, * new;
	
	P = resort(P);

	curr = P;
	new = (struct process*)malloc(sizeof(struct process));
	generate_random_process(new);

	if (curr->processTime > new->processTime) {
		new->next = curr;
		P = new;
		return P;
	}

	while (curr->next != NULL)
	{
		if (curr->next->processTime > new->processTime) {
			new->next = curr->next;
			curr->next = new;
			return P;
		}
		else
			curr = curr->next;
	}
	curr->next = new;
	return P;
}

//Takes an inputted processID and frees that process from the linked list
struct process *killProcess(struct process *P, unsigned long id_to_be_gone)
{	// (10 points)
	
	struct process *curr, *temp;

	curr = P;
	if (curr->processID == id_to_be_gone) {
		temp = P;
		P = P->next;
		free(temp);
		return P;
	}

	while (curr->next != NULL) {
		if (curr->next->processID == id_to_be_gone) {
			temp = curr->next;
			curr->next = temp->next;
			free(temp);
			return P;
		}
		curr = curr->next;
	}

	printf("Invalid process ID\n");
	return NULL;
}

//Sorts the linked list by Memory
struct process *sortByMemory(struct process *P)
{	// (12 points)

	struct process* curr, * temp, * temp2;
	int numOfProcess = 0;
	int i;

	curr = P;
	while (curr != NULL) {
		numOfProcess++;
		curr = curr->next;
	}

	for (i = 0; i < numOfProcess - 1; i++) {
		displayList(P);
		curr = P;
		if (curr->processMemory < curr->next->processMemory) {
			temp = curr->next;
			curr->next = temp->next;
			temp->next = curr;
			P = temp;
			curr = temp;
		}
		while (curr->next->next != NULL) {
			if (curr->next->processMemory < curr->next->next->processMemory) {
				temp = curr->next;
				temp2 = temp->next;
				temp->next = temp2->next;
				temp2->next = temp;
				curr->next = temp2;
				curr = curr->next;
			}
			else
				curr = curr->next;
		}
	}
	return P;
}

//Copies the remaining linked list to a text file, frees the linked list and terminates the program
void early_terminate_write(struct process *P)
{	// (8 points)

	FILE* frp;
	struct process *temp;
	
	temp = P;
	frp = fopen("C:\\Users\\Jared\\Desktop\\new_semProject\\remaining_process.txt", "w");
	if (frp == NULL) {
		printf("Could not open remaining_process.txt\n");
		exit(0);
	}

	fprintf(frp, "%-35s %-6s %-6s %-6s %-6s %-2s\n", "Description", "ID", "Time", "Memory", "Date", "Priority");
	while (temp != NULL) {
		fprintf(frp, "%-35s %-6lu %-6lu %-6lu %-6lu %-2d\n", temp->description, temp->processID, \
			temp->processTime, temp->processMemory, temp->date, temp->priority);
		temp = temp->next;
	}
	fclose(frp);
	freeList(P);
}

//Frees the struct memory and terminates the program
void freeList(struct process *P)
{	// (8 points)

	struct process *head, *temp;
	head = P;
	while (head != NULL) {
		temp = head->next;
		free(head);
		head = temp;
	}
	exit(EXIT_SUCCESS);
}

