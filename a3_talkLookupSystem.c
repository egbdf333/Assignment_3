#include "a3_talklib.h"
#include <stdio.h>

int getline(char* line, int max) {
    if (fgets(line, max, stdin) == NULL) {
        return 0;
    } else {
        int lastIndex = strlen(line) - 1;
        if (line[lastIndex] == '\n') {
            line[lastIndex] = '\0';
        }
        // printf("Your line is [%s]\n", line);
        return strlen(line);
    }
}

FILE* openFile() {

    char fileName[20];
    printf("Enter the full name of the file (with extension: abc.txt): ");
    scanf("%s", &fileName);
    FILE* fptr;
    fptr = fopen(fileName, "rb");
    
    if (fptr == NULL) {
        printf("Error in opening the file. Please check if it is available.\n");
    }
    return fptr;
}

void printBanner() {
    printf("| this is a fancy banner | wow so fancy | this is awesome! |\n| =-=-=-=-=-=-=- | CS Talks Lookup System | =-=-=-=-=-=-=- |\n| =-=-=-=-=-=-=-=-=-=-=-= | Linus | =-=-=-=-=-=-=-=-=-=-=- |\n| =-=-=-=-=-=-=-=-=-=-= | 301554378 | =-=-=-=-=-=-=-=-=-=- |\n| =-=-=-=-=-=-=-=-=-= | lpa44@sfu.ca | =-=-=-=-=-=-=-=-=-= |\n| wOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO |\n");
}

void printOptions() {
    printf("============================================================\n");
    printf("Press numbers 1-5 for the following options and then enter:\n");
    printf("Option 1: Load a talks file\n");
    printf("Option 2: List talks sorted by duration\n");
    printf("Option 3: List talks sorted by title\n");
    printf("Option 4: Look up a talk\n");
    printf("Option 5: Exit program\n");
    printf("Option: ");
}

int main() {

    printBanner();
    int optionNum = 0;
    FILE* fptr = NULL;
    int used = 0;
    int capacity = 16;
    Talk** talkArray = (Talk**)malloc(sizeof(Talk*)*capacity);

    while (optionNum != 6) {
        optionNum = 0;
        printOptions();
        scanf("%d%*c", &optionNum);

        switch (optionNum) {
            case 1:
                if (fptr != NULL) {
                    for (int i = 0; i < capacity; i++) {
                        clearTalk(talkArray[i]);
                    }
                    for (int i = 0; i < capacity; i++) {
                        free(talkArray[i]);
                    }
                    fclose(fptr);
                    fptr = NULL;
                    used = 0;
                    capacity = 16;
                    // printf("Successfully cleared talks\n");
                    talkArray = (Talk**)realloc(talkArray, sizeof(Talk*)*capacity);
                    // printf("Successfully reallocd talkArray back to original size\n");
                }
                fptr = openFile();
                if (fptr == NULL) {
                    break;
                }
                // printf("File opened successfully");
                int talkCounter = 0;
                int c;
                while ((c = fgetc(fptr)) != EOF) {
                    talkArray[talkCounter] = getATalk(fptr);
                    talkCounter++;
                    // printf("Talk conter is now %d\n", talkCounter);
                    used++;
                    // printf("Talk usage is %d\n", used);
                    if (used == capacity) {
                        capacity *= 2;
                        talkArray = (Talk**)realloc(talkArray, sizeof(Talk*)*capacity);
                    }
                }
                printf("%d entries read.\n", talkCounter);
                // printf("TalkArray is using up %d out of %d talks\n", used, capacity);
                break;
            case 2:
                if (fptr == NULL) {
                    printf("Error in sorting the file, please check if it is available.\n");
                    break;
                }
                qsort(talkArray, talkCounter, sizeof(Talk*), compareTalksByDuration);
                for (int i = 0; i < talkCounter; i++) {
                    printf("Talk #%d\n%dh%dm%ds\n%s\n%s\n", i + 1, talkArray[i]->hours, talkArray[i]->minutes, talkArray[i]->seconds, talkArray[i]->title, talkArray[i]->overview);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                }
                break;
            case 3:
                if (fptr == NULL) {
                    printf("Error in sorting the file, please check if it is available.\n");
                    break;
                }
                printf("Listing talks by title:\n\n");
                qsort(talkArray, talkCounter, sizeof(Talk*), compareTalksByTitle);
                for (int i = 0; i < talkCounter; i++) {
                    printf("Talk #%d\n%dh%dm%ds\n%s\n%s\n", i + 1, talkArray[i]->hours, talkArray[i]->minutes, talkArray[i]->seconds, talkArray[i]->title, talkArray[i]->overview);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                }
                break;
            case 4:
                if (fptr == NULL) {
                    printf("Error in sorting the file, please check if it is available.\n");
                    break;
                }
                printf("What is the title of the talk, enter in part or as a whole (50 characters max.)? ");
                char searchTitle[50] = "";
                printf("Current title: [%s]\n", searchTitle);
                char* titlePtr = searchTitle;
                int maxLength = 50;
                int strLength;
                // scanf("%[^\n]%*c", &searchTitle);
                strLength = getline(titlePtr, maxLength);
                // printf("Search title: %s\nlength: %d\n", titlePtr, strLength);
                lookupTalkByTitle(talkArray, talkCounter, titlePtr);
                // optionNum = 6;
                break;
            case 5:
                optionNum = 6;
                break;
        }
    }


    printf("Exited the interface.\n");

    if (fptr != NULL) {
        for (int i = 0; i < capacity; i++) {
            clearTalk(talkArray[i]);
        }
        for (int i = 0; i < capacity; i++) {
            free(talkArray[i]);
        }
        free(talkArray);
        fclose(fptr);
    }
    printf("File closed. Program Terminating...");
}