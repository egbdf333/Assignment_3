#include "a3_talklib.h"

const char delimiter[] = " ";
const char QUOTE_DELIMITER[] = "\"";
const char EOL_DELIMITER[] = "\n";

Talk* getATalk(FILE* stream) {
    char line[MAX_LEN], *result, *result1, *emptyResult;
    char line2[MAX_LEN];
    char line3[MAX_LEN];
    char line4[MAX_LEN];
    char* currentWord;
    char* currentOverviewWord;
    short hours;
    short minutes;
    short seconds;
    char* title;
    char* overview;

    result = fgets(line, MAX_LEN, stream);
    currentWord = strtok(result, delimiter);
    currentWord = strtok(NULL, delimiter);
    hours = atoi(currentWord);
    for (int i = 0; i < 2; i++) {
        currentWord = strtok(NULL, delimiter);
    }
    minutes = atoi(currentWord);
    for (int i = 0; i < 2; i++) {
        currentWord = strtok(NULL, delimiter);
    }
    seconds = atoi(currentWord);
    
    result = fgets(line2, MAX_LEN, stream);
    currentWord = strtok(result, QUOTE_DELIMITER);
    currentWord = strtok(NULL, QUOTE_DELIMITER);
    title = currentWord;

    result1 = fgets(line3, MAX_LEN, stream);
    currentOverviewWord = strtok(result1, delimiter);
    currentOverviewWord = strtok(NULL, EOL_DELIMITER);
    overview = currentOverviewWord;

    emptyResult = fgets(line4, MAX_LEN, stream);

    Talk* myTalk = createTalk(hours, minutes, seconds, title, overview);

    return myTalk;
}

// used in talk function
int getArrayLength(const char* userArray) {
    int arrayLength = 0;
    
    for (int i = 0; userArray[i] != '\0'; i++) {
        arrayLength += 1;
    }
    arrayLength = arrayLength + 1;
    return arrayLength;
}

// used in talk function
char* deepCopyString(const char* userString, int arraySize) {

    char* newStringPointer = (char*)malloc(arraySize * sizeof (char));

    for (int i = 0; i < arraySize - 1; i++) { 
        newStringPointer[i] = '\0';
    }

    char* currentPointer = newStringPointer;
    int i = 0;

    for (i = 0; i < arraySize - 1; i++) {
        *currentPointer = userString[i];
        currentPointer++;
    }
    newStringPointer[i] = '\0';
    return newStringPointer;
}

Talk* createTalk(short hours, short minutes, short seconds, const char* title, const char* overview) {

    int sizeOfTitle = getArrayLength(title);
    int sizeOfOverview = getArrayLength(overview);

    char* talkTitle;
    talkTitle = deepCopyString(title, sizeOfTitle);
    char* talkOverview;
    talkOverview = deepCopyString(overview, sizeOfOverview);

    Talk *currentTalk = (Talk*)malloc(sizeof(Talk));
    currentTalk->hours = hours;
    currentTalk->minutes = minutes;
    currentTalk->seconds = seconds;
    currentTalk->title = talkTitle;
    currentTalk->overview = talkOverview;

    return currentTalk;
}

void clearTalk(Talk* talk) {

    if (talk == NULL) {
        return;
    }
    free(talk->title);
    talk->title = NULL;
    free(talk->overview);
    talk->overview = NULL;
}

int* lookupTalkByTitle(Talk **array, int size, const char* title) {
    // printf("Looking for [%s]\n", title);
    int counter = 0;
    for (int i = 0; i < size; i++) {
        // printf("Searched title: [%s]\nTitle %d: [%s]\n", title, i, array[i]->title);
        if (strstr(array[i]->title, title) != NULL) {
            printf("Talk #%d\n%dh%dm%ds\n%s\n%s\n", counter, array[i]->hours, array[i]->minutes, array[i]->seconds, array[i]->title, array[i]->overview);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            counter++;
        }
    }
    if (counter == 0) {
        printf("No such talk on record.\n");
    }
}

int compareTalksByDuration(const void *p1, const void *p2) {
    // Returns 1 if p1 > p2, 0 if same, -1 if p1 < p2
    Talk** talk1 = (Talk**)p1;
    Talk** talk2 = (Talk**)p2;
    Talk* talk1ptr;
    Talk* talk2ptr;
    talk1ptr = *talk1;
    talk2ptr = *talk2;

    int talk1Time, talk2Time;
    talk1Time = ((talk1ptr->hours * 60) + talk1ptr->minutes) * 60 + talk1ptr->seconds;
    talk2Time = ((talk2ptr->hours * 60) + talk2ptr->minutes) * 60 + talk2ptr->seconds;
    int compResult;
    if (talk1Time > talk2Time) {
        compResult = 1;
    } else if (talk1Time < talk2Time) {
        compResult = -1;
    } else {
        compResult = 0;
    }
    return compResult;
}

int compareTalksByTitle(const void *p1, const void *p2) {
    // printf("Running compareTalksByTitle\n");
    Talk** talk1 = (Talk**)p1;
    Talk** talk2 = (Talk**)p2;
    Talk* talk1ptr;
    Talk* talk2ptr;
    talk1ptr = *talk1;
    talk2ptr = *talk2;
    int strcmp1;
    int strcmp2;
    int cmpResult;
    int calcResult;
    cmpResult = strcmp(talk1ptr->title, talk2ptr->title);
    // printf("Title 1: %s\nTitle 2: %s\ncmpResult: %d\n~~~~~~\n\n", talk1ptr->title, talk2ptr->title, cmpResult);
    if (cmpResult > 0) {
        calcResult = 1;
    } else if (cmpResult < 0) {
        calcResult = -1;
    } else {
        calcResult = 0;
    }
    return calcResult;
}

