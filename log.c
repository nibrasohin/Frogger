
//=============================File: log.c======================================

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


#include"log.h"

void *drawLog(void *info)
{
	setUpLog();
	struct logInfo *logInfo=info;
	logs *logStructAccessor=malloc(sizeof(logs));
	
	logStructAccessor->logRow=logInfo->logRow;
	logStructAccessor->logCol=logInfo->logCol;
	logStructAccessor->direction=logInfo->logDirection;
	logStructAccessor->numOfTicks=logInfo->numOfTicks;
	logStructAccessor->offscreen=logInfo->offscreen;
	
	add(logStructAccessor,pthread_self());
	
	int logRow=logStructAccessor->logRow;
	int logCol=logStructAccessor->logCol;
	int ticks=logStructAccessor->numOfTicks;
	int direction=logStructAccessor->direction;
	int isOffscreen=logStructAccessor->offscreen;
	
	int k=0;
	while(!(isOffscreen))
	{
		int i;
		for (i = 0; i<LOG_ANIM_TILES; i++)
		{
			int j;
			for(j=0;j<4;j++)
			{
				pthread_mutex_lock(&console_mutex);	
				char** tile = log[i];				
				consoleClearImage(logRow,logCol,LOG_HEIGHT,strlen(tile[0]));
				if(direction==1)
				{				
					logStructAccessor->logCol=logStructAccessor->logCol+1;
				}
				else
				{
					logStructAccessor->logCol=logStructAccessor->logCol-1;
				}
				logCol=logStructAccessor->logCol;				
				consoleDrawImage(logRow,logCol,tile,LOG_HEIGHT);		
				if(frog_row>=logRow && frog_row<=logRow+3 && frog_col>=logCol && frog_col<=logCol+20)
				{
					if(frog_col<=78 && frog_col>=0)
					{
						consoleDrawImage(frog_row, frog_col, PLAYER_GRAPHIC[k], PLAYER_HEIGHT);
						if(direction==1)
						{
							if(frog_col!=78)
							{
								updateFrogCol(frog_col+1);
							}
						}
						else
						{
							if(frog_col!=0)
							{
								updateFrogCol(frog_col-1);
							}
						}
						
					}
				}
				if(direction==1)
				{
					if(logCol>=80)
					{
						isOffscreen=1;
					}
				}
				else
				{
					if(logCol==-21)
					{
						isOffscreen=1;
					}
				}
				pthread_mutex_unlock(&console_mutex);				
				sleepTicks(ticks);				
			}
			k=(k+1)%2;
		}		
	}	
	pthread_exit(NULL);
}



void setUpLog()
{
	pthread_mutexattr_settype(&log_row_attributes, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&log_row_mutex, &log_row_attributes);
}
