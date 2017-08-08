
//=============================File: frog.h======================================

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


#ifndef FROG_HEADER
#define FROG_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include"console.h"
#include "globals.h"
#include "string.h"
#include "list.h"

#define PLAYER_ANIM_TILES 2
#define PLAYER_HEIGHT 2

#define DEFAULT_FROG_ROW 21
#define DEFAULT_FROG_COL 39


int frog_row;
int frog_col;

int prev_row;
int prev_col;

int frogSleep;
int lives;

char live[2];

static char* PLAYER_GRAPHIC[PLAYER_ANIM_TILES][PLAYER_HEIGHT+1] = {
  {"@@",
   "<>"},
  {"--",
   "<>"}
};

void setUpFrog();
void *drawFrog(void *dummy );
void updateFrogRow(int frogRow);
void updateFrogCol(int frogCol);

#endif