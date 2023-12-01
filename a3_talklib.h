#ifndef _A3_Q1_H_
#define _A3_Q1_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#define MAX_LEN 300

typedef struct {
	short hours;
	short minutes;
	short seconds;
	char* title;
	char* overview;
} Talk;

Talk* createTalk(short hours, short minutes, short seconds, const char* title, const char* overview);

void clearTalk(Talk* talk);

int* lookupTalkByTitle(Talk **array, int size, const char* title);

int compareTalksByDuration(const void *p1, const void *p2);

int compareTalksByTitle(const void *p1, const void *p2);

Talk* getATalk(FILE* filePtr);
FILE* openFile();
int closeTalk();
// void printBanner();
void printOptions();

#endif