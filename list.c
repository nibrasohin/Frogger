

//=============================File: list.c======================================

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


#include "list.h"

//adds a logstruct to the linked list 
void add(struct logTiles *log,pthread_t pthreadId)
{
	struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->logStruct=log;
	temp->pthreadJoiner=pthreadId;
    if (head== NULL)
    {
		head=temp;
		head->next=NULL;
    }
    else
    {
		temp->next=head;
		head=temp;
    }
}

//checks whether the player has already won or not
int hasWon()
{
	int i;
	int result=1;
	for(i=0;i<sizeof(liveCounter)/sizeof(liveCounter[0]) && result;i++)
	{
		if(liveCounter[i]==0)
		{
			result=0;
		}
	}
	return result;
}

//This function removes the deadlogs that have gone offscreen and also joins the log threads that are off screen.
void removeDeadLogs()
{
	struct node *temp=head;
	struct node *prev=temp;
	int rc;
	while(temp!=NULL)
	{
		if(temp!=NULL && temp->next==NULL && temp->logStruct->offscreen==1)
		{
			pthread_mutex_lock(&join_mutex);		
			rc = pthread_join(temp->pthreadJoiner, NULL);
			pthread_mutex_unlock(&join_mutex);								
			free(temp->logStruct);
			prev->next=temp->next;			
			free(temp);
			temp=NULL;
		}
		else if(temp!=NULL && temp->next!=NULL && temp->logStruct->offscreen==1)
		{						
			pthread_mutex_lock(&join_mutex);		
			rc = pthread_join(temp->pthreadJoiner, NULL);
			pthread_mutex_unlock(&join_mutex);								
			free(temp->logStruct);
			prev->next=temp->next;			
			free(temp);
			temp=prev->next;
		}
		else
		{
			prev=temp;
			temp=temp->next;	
		}
	}	
}

//cleans up the remaining logs after the game has ended
void cleanUp()
{
	struct node *temp=head;	
	int rc;
	while(temp!=NULL)
	{		
		pthread_mutex_lock(&join_mutex);		
		rc = pthread_join(temp->pthreadJoiner, NULL);
		pthread_mutex_unlock(&join_mutex);								
		free(temp->logStruct);			
		free(temp);					
		temp=temp->next;
	}	
}

//checks if the frogs position is in a log or in the water or not.
int validPosition()
{
	int result=0;	//will return 0 if the position of the frog is in a deadzone, 
					//return 1 if it's in any of the logs or in the start row
					//return 2 if the frog is in one of its home position
	struct node *temp=head;
	int logRow;
	int logCol;
	if(frog_row==2 )
	{
		if((1<=frog_col  && frog_col<=5))
		{
			result=2;
			liveCounter[0]=1;
		}
		else if((19<=frog_col  && frog_col<=23))
		{
			result=2;
			liveCounter[1]=1;
		}
		else if((37<=frog_col  && frog_col<=41))
		{
			result=2;
			liveCounter[2]=1;
		}
		else if((55<=frog_col  && frog_col<=59))
		{
			result=2;
			liveCounter[3]=1;
		}
		else if((73<=frog_col  && frog_col<=77))
		{
			result=2;
			liveCounter[4]=1;
		}		
	}	
	if(frog_row==21 && 0<=frog_col<=78)
	{		
		result=1;
	}
	while(temp!=NULL && !result)
	{
		logRow=temp->logStruct->logRow;
		logCol=temp->logStruct->logCol;			
		if(frog_row>=logRow && frog_row<=logRow+3 && frog_col>=logCol && frog_col<=logCol+20)
		{			
			result=1;
		}
		temp=temp->next;		
	}
	return result;
}
