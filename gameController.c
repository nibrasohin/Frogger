
//=============================File: gameController.c======================================

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



#include "gameController.h"

//This method initializes everything and creates a thread that starts different component threads of the game
void startTheGame()
{
	gameOver=0;
	pthread_t gameStarter;	
	pthread_cond_init (&lives_cv, NULL);
	int rc;	
	rc = pthread_create(&gameStarter, NULL, runTheGame, NULL);
	 if (rc){
	   printf("ERROR-return code from pthread_create() is %d\n", rc);
	   exit(-1);
	 }
	 
	 
	 while(!gameOver)
	 {
		pthread_mutex_lock(&upkeep_mutex);
		pthread_cond_wait(&lives_cv, &upkeep_mutex);
		pthread_mutex_unlock(&upkeep_mutex);
	 }	 
	 cleanUp();	 
	 rc = pthread_join(gameStarter, NULL);
	 if (rc){
	   printf("ERROR-return code from pthread_join() for gameStarter is %d\n", rc);
	   exit(-1);
	 }
	 finalKeypress(); /* wait for final key before killing curses and game */	 
}


//This function starts differnt pupose threads to run the game
void *runTheGame(void *dummy)
{
	if(consoleInit(GAME_ROWS, GAME_COLS, GAME_BOARD))
	{				
		pthread_t upkeep;
		int rc = pthread_create(&upkeep, NULL, upkeepManager, NULL);
		if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		}
				
		pthread_t frogThread;
		rc = pthread_create(&frogThread, NULL, drawFrog, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		 }
		 
		pthread_t runRow1;
		rc = pthread_create(&runRow1, NULL, spanRow1, NULL);
		if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		}
		pthread_t runRow2;
		rc = pthread_create(&runRow2, NULL, spanRow2, NULL);
		if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		}  
		   pthread_t runRow3;
		rc = pthread_create(&runRow3, NULL, spanRow3, NULL);
		if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		}
		pthread_t runRow4;
		rc = pthread_create(&runRow4, NULL, spanRow4, NULL);
		if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		}
		 pthread_t refresh;
		 rc = pthread_create(&refresh, NULL, refreshByThread, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		 }
		 
		 pthread_t keyboard;	
		 rc = pthread_create(&keyboard, NULL, getCharKeyboard, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		 }
			
		 //Pthread joiners
		 rc = pthread_join(upkeep, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_join() for upkeep thread is %d\n", rc);
		   exit(-1);
		 }
		 rc = pthread_join(frogThread, NULL);		 
		 if (rc){
		   printf("ERROR-return code from pthread_join() for frog thread is %d\n", rc);
		   exit(-1);
		 }
		 
		 rc = pthread_join(refresh, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_join() for refresh thread is %d\n", rc);
		   exit(-1);
		 }
		
		 rc = pthread_join(keyboard, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_join() for keyboard is %d\n", rc);
		   exit(-1);
		 }
		 
		 rc = pthread_join(runRow1, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_join() for runRow1 is %d\n", rc);
		   exit(-1);
		 }
		 
		 rc = pthread_join(runRow2, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_join() for runRow2 is %d\n", rc);
		   exit(-1);
		 }
		 
		 rc = pthread_join(runRow3, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_join() for runRow3 is %d\n", rc);
		   exit(-1);
		 }	 
		 rc = pthread_join(runRow4, NULL);
		 if (rc){
		   printf("ERROR-return code from pthread_join() for runRow4 is %d\n", rc);
		   exit(-1);
		 }
		 
	}
	pthread_exit(NULL);
}

void *refreshByThread(void *dummy)
{	
	while(!gameOver)
	{
		sleepTicks(3);		
		pthread_mutex_lock(&console_mutex);
		consoleRefresh();
		pthread_mutex_unlock(&console_mutex);		
	}
	pthread_exit(NULL);
}


void *upkeepManager()
{
	lives=4;
	sprintf(live,"%d",lives);	
	int prevLive=live[0]-'0';	
	int prev=lives;
	while(lives>0)
	{
		sleepTicks(2);		
		if(hasWon())
		{
			pthread_mutex_lock(&console_mutex);
			putBanner("Yeppiii You won the game!");
			pthread_mutex_unlock(&console_mutex);
			pthread_cond_signal(&lives_cv);
			gameOver=1;	
			lives=0;
		}
		else
		{			
			pthread_mutex_lock(&upkeep_mutex);
			pthread_mutex_lock(&console_mutex);			
			sprintf(live,"%d",lives);
			if(lives!=0)
			{
				putString(live, 0, 41, 1);
			}
			pthread_mutex_unlock(&console_mutex);
			pthread_mutex_unlock(&upkeep_mutex);
		}		
		pthread_mutex_lock(&upkeep_mutex);
		prev=lives;
		pthread_mutex_unlock(&upkeep_mutex);
		removeDeadLogs();
	}
	removeDeadLogs();	
	gameOver=1;	
	pthread_mutex_lock(&console_mutex);
	putBanner("Game Over! Do or do not there's no try!");
	pthread_mutex_unlock(&console_mutex);
	pthread_cond_signal(&lives_cv);
	pthread_exit(NULL);
}

void *spanRow1()
{
	while(!gameOver)
	{
		struct logInfo *logInformation;
		logInformation = malloc(sizeof(struct logInfo));
		logInformation->logRow=16;
		logInformation->logCol=-21;
		logInformation->logDirection=1;
		logInformation->numOfTicks=6;
		logInformation->offscreen=0;		
		pthread_t logRow1Thread;
		int rc = pthread_create(&logRow1Thread, NULL, drawLog, logInformation);
		 if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		 }
		 sleepTicks(200);
		 sleepTicks(rand()%200);
		 free(logInformation);
	}
	
	pthread_exit(NULL);
}

//spans logs for row 2
void *spanRow2()
{
	while(!gameOver)
	{
		struct logInfo *logInformation;
		logInformation = malloc(sizeof(struct logInfo));
		logInformation->logRow=12;
		logInformation->logCol=80;
		logInformation->logDirection=0;
		logInformation->numOfTicks=5;
		logInformation->offscreen=0;	
		pthread_t logRow2Thread;
		int rc = pthread_create(&logRow2Thread, NULL, drawLog, logInformation);
		 if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		 }
		 sleepTicks(200);
		 sleepTicks(rand()%250);
		 free(logInformation);
	}
	pthread_exit(NULL);
}

//spans logs for row 3
void *spanRow3()
{
	while(!gameOver)
	{
		struct logInfo *logInformation;
		logInformation = malloc(sizeof(struct logInfo));
		logInformation->logRow=8;
		logInformation->logCol=-21;
		logInformation->logDirection=1;
		logInformation->numOfTicks=4;
		logInformation->offscreen=0;	
		pthread_t logRow3Thread;
		int rc = pthread_create(&logRow3Thread, NULL, drawLog, logInformation);
		 if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		 }
		 sleepTicks(250);
		 sleepTicks(rand()%200);
		 free(logInformation);		 
	}
	pthread_exit(NULL);
}

//spans logs for row 4
void *spanRow4()
{
	while(!gameOver)
	{
		struct logInfo *logInformation;
		logInformation = malloc(sizeof(struct logInfo));
		logInformation->logRow=4;
		logInformation->logCol=80;
		logInformation->logDirection=0;
		logInformation->numOfTicks=3;
		logInformation->offscreen=0;	
		pthread_t logRow4Thread;
		int rc = pthread_create(&logRow4Thread, NULL, drawLog, logInformation);
		 if (rc){
		   printf("ERROR-return code from pthread_create() is %d\n", rc);
		   exit(-1);
		 }
		 sleepTicks(250);
		 sleepTicks(rand()%200);
		 free(logInformation);			 
	}
	pthread_exit(NULL);
}


//This method reads the inputs from the keyboards and makes the frog move according to the input
void *getCharKeyboard()
{
	
	while(!gameOver)
	{
		fd_set set;
		FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        struct timespec timeout = getTimeout(1); /* duration of one tick */
        int ret = pselect(FD_SETSIZE, &set, NULL, NULL, &timeout, NULL);
		if(ret!=0)
		{
			sleepTicks(2);		
			char c=getchar();
			pthread_mutex_lock(&keyboard_mutex);
			if(c=='w')
			{
				if(frog_row>0)
				{								
					if(frog_row==5)
					{
						if((1<=frog_col  && frog_col<=5))
						{
							if(liveCounter[0]!=1)
							{
								updateFrogRow(frog_row-3);
								liveCounter[0]=1;
							}
						}
						else if((19<=frog_col  && frog_col<=23))
						{
							
							if(liveCounter[1]!=1)
							{
								updateFrogRow(frog_row-3);
								liveCounter[1]=2;
							}
						}
						else if((37<=frog_col  && frog_col<=41))
						{
							if(liveCounter[2]!=1)
							{
								updateFrogRow(frog_row-3);
								liveCounter[2]=1;
							}
						}
						else if((55<=frog_col  && frog_col<=59))
						{
							if(liveCounter[3]!=1)
							{
								updateFrogRow(frog_row-3);
								liveCounter[3]=1;
							}
						}
						else if((73<=frog_col  && frog_col<=77))
						{
							if(liveCounter[4]!=1)
							{
								updateFrogRow(frog_row-3);
								liveCounter[4]=1;
							}
						}
					}
					else if(frog_row>2)
					{
						updateFrogRow(frog_row-4);	
					}				
				}			
			}
			else if(c=='a')
			{
				if(frog_col==1)
				{
					updateFrogCol(frog_col-1);
				}
				else if(frog_col>0)
				{
					updateFrogCol(frog_col-2);
				}
			}
			else if(c=='s')
			{
				if(frog_row==2)
				{
					updateFrogRow(frog_row+3);
				}
				else if(frog_row<=17)
				{
					updateFrogRow(frog_row+4);
				}
			}
			else if(c=='d')
			{
				if(frog_col==77)
				{
					updateFrogCol(frog_col+1);
				}
				else if(frog_col<78)
				{
					updateFrogCol(frog_col+2);
				}
			}
			pthread_mutex_unlock(&keyboard_mutex);
		}
		else if(ret==-1)
		{
			printf("ERROR-return code from pselect is %d\n", ret);
		    exit(-1);
		}
	}
	consoleFinish();        
	pthread_exit(NULL);
}
