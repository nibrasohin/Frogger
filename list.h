
//=============================File: list.h======================================

//-----------------------------------------
// NAME: Nibrasul Islam Ohin
// STUDENT NUMBER: 7763314
// COURSE: COMP 3430, SECTION: A02
// INSTRUCTOR: Jim Young
// ASSIGNMENT: Assignment 2
//
// REMARKS: Implementing the text version of the classic video game “frogger”.
//
//-----------------------------------------


#include<stdlib.h>
#include "globals.h"
#include "gameController.h"

#ifndef LIST_HEADER
#define LIST_HEADER

static struct node *head=NULL;
extern int frog_row;
extern int frog_col;


struct node
{
	struct logTiles *logStruct;
	pthread_t pthreadJoiner;
	struct node *next;
};

void add(struct logTiles *log, pthread_t pthreadId);

int hasWon();
void removeDeadLogs();
void cleanUp();
int validPosition();

#endif