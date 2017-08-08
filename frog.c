
//=============================File: frog.c======================================

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



#include"frog.h"

//sets up and initializes the mutex
void setUpFrog()
{
	pthread_mutexattr_settype(&frog_attributes, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&frog_mutex, &frog_attributes);
}

//draws the frog into the buffer with animation
void *drawFrog(void *dummy )
{
	setUpFrog();
	updateFrogRow(DEFAULT_FROG_ROW);
	updateFrogCol(DEFAULT_FROG_COL);
	prev_row=frog_row;
	prev_col=frog_col;	
	frogSleep=30;
	
	while(!gameOver)
	{
		int i;
		char** tile = PLAYER_GRAPHIC[0];
		for (i = 0; i<PLAYER_ANIM_TILES; i++)
		{
			pthread_mutex_lock(&console_mutex);
			tile = PLAYER_GRAPHIC[i];			
			consoleClearImage(prev_row,prev_col,PLAYER_HEIGHT, strlen(tile[i]));				
			consoleDrawImage(frog_row, frog_col, tile, PLAYER_HEIGHT);
			int returnPos=validPosition();
			pthread_mutex_unlock(&console_mutex);
			if(returnPos==0)	//meaning the frog is in one of the deadzone and so will decrease live
			{
				sleepTicks(5);
				pthread_mutex_lock(&console_mutex);
				sleepTicks(100);
				pthread_mutex_unlock(&console_mutex);
				updateFrogRow(DEFAULT_FROG_ROW);
				updateFrogCol(DEFAULT_FROG_COL);
				prev_row=frog_row;
				prev_col=frog_col;
				pthread_mutex_lock(&upkeep_mutex);
				lives=lives-1;								
				pthread_mutex_unlock(&upkeep_mutex);
			}
			else if(returnPos==2)	//meaning the frog is in one of it's home boxes
			{
				sleepTicks(50);
				updateFrogRow(DEFAULT_FROG_ROW);
				updateFrogCol(DEFAULT_FROG_COL);
				prev_row=frog_row;
				prev_col=frog_col;
			}
			prev_row=frog_row;
			prev_col=frog_col;
			sleepTicks(frogSleep);
		}
	}
	consoleFinish();        
	pthread_exit(NULL);
}

//updates the frog row value surrounding it with frog mutex
void updateFrogRow(int frogRow)
{
	pthread_mutex_lock(&frog_mutex);
	frog_row=frogRow;
	pthread_mutex_unlock(&frog_mutex);
}

//updates the frog column value surrounding it with frog mutex
void updateFrogCol(int frogCol)
{
	pthread_mutex_lock(&frog_mutex);
	frog_col=frogCol;
	pthread_mutex_unlock(&frog_mutex);
}