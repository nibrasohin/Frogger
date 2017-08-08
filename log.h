
//=============================File: log.h======================================

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


#ifndef LOG_HEADER
#define LOG_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "frog.h"

#define LOG_ANIM_TILES 6
#define LOG_HEIGHT 4


typedef struct logTiles
{
		int logRow;
		int logCol;
		int direction;	//1 means from left to right & 0 means from right to left
		int offscreen;	//1 means offscreen so can be deleted & 0 means still on screen
		int numOfTicks;	//number of ticks that the log will sleep
}logs;



extern int frog_row;
extern int frog_col;

extern int prev_row;
extern int prev_col;

static char* log[LOG_ANIM_TILES][LOG_HEIGHT+1] ={
  {"/===================\\",
   "|                   |",
   "|                   |",
   "\\===================/"},
   {"/===================\\",
   "- x                 +",
   "-    x              +",
   "\\===================/"},
   {"/===================\\",
   "|      x            +",
   "|   x               +",
   "\\===================/"},
   {"/===================\\",
   "-      x            |",
   "-         x         |",
   "\\===================/"},
   {"/===================\\",
   "+            x      |",
   "+         x         |",
   "\\===================/"},
   {"/===================\\",
   "|            x      |",
   "|               x   |",
   "\\===================/"}   
   };

void *drawLog(void *info);
void setUpLog();

#endif