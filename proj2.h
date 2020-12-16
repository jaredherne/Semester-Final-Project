#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

//Function declarations
void space_print(int num);
struct process *list_intialize(unsigned int listsize);
struct process *processList(struct process *P);
void displayList(struct process *P);
struct process *addProcess(struct process *P);
struct process *killProcess(struct process *P, unsigned long  id_to_be_gone);
struct process *sortByMemory(struct process *P);
void early_terminate_write(struct process *P);
void freeList(struct process *P);
struct process *setPriority(struct process *P, unsigned to_be_changed);

