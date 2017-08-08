
//=============================File: gameController.h======================================

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


#ifndef GAME_CONTROLLER_HEADER
#define GAME_CONTROLLER_HEADER

#include<stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include "frog.h"
#include "log.h"
#include "globals.h"

#define GAME_ROWS 24
#define GAME_COLS 80


static char *GAME_BOARD[] = {
"                                   Lives:",
"/------\\          /------\\          /------\\          /------\\          /------\\",
"|      |          |      |          |      |          |      |          |      |",
"+      +----------+      +----------+      +----------+      +----------+      +",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"",
"",
"",
"" };


pthread_cond_t  lives_cv;

struct logInfo {
    int logRow;
	int logCol;
	int logDirection;
	int numOfTicks;
	int offscreen;
};



extern int lives;
extern char live[2];

extern int frogStopper;
extern int frog_row;
extern int frog_col;

extern int prev_row;
extern int prev_col;

int liveCounter[5];

void startTheGame();

void *runTheGame(void *dummy);

void *refreshByThread(void *dummy);

void *getCharKeyboard();

void *spanRow1();

void *spanRow2();

void *spanRow3();

void *spanRow4();

void *upkeepManager();

#endif
