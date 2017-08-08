
//=============================File: globals.h======================================

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


#include <pthread.h>
#include <time.h>

pthread_mutexattr_t frog_attributes;
pthread_mutex_t frog_mutex;

pthread_mutexattr_t log_row_attributes;
pthread_mutex_t log_row_mutex;

pthread_mutexattr_t console_attributes;
pthread_mutex_t console_mutex;

pthread_mutexattr_t upkeep_attributes;
pthread_mutex_t upkeep_mutex;

pthread_mutexattr_t keyboard_attributes;
pthread_mutex_t keyboard_mutex;

pthread_mutexattr_t refresh_attributes;
pthread_mutex_t refresh_mutex;

pthread_mutexattr_t join_attributes;
pthread_mutex_t join_mutex;

int gameOver;
