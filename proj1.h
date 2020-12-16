#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*  **************************************************************


/* *************************************************
   ****************************************************
     
	          for processes

**************************************************
****************************************   */
#ifndef DONE

struct process {
		char description[35];
		unsigned long processID;
		unsigned long processTime;
		unsigned long processMemory;
		unsigned long date;
		char priority;
		struct process *next;
};

#define DONE
#endif

void generate_random_process(struct process *P);
void print_main_menu();

struct process *resort(struct process *P);
struct process *sortByDate(struct process *P);

