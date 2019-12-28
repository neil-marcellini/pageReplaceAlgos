/**
* Name: Neil Marcellini
* Lab/task: Lab 10
* Date: 11/6/19
* This implements the LRU page-replacement algorithm.
**/

#include "../inc/lruList.h"

int *referenceString;
int refStringLength;

FRAME *pageTableTop;
FRAME *leastRecentlyUsed;
int pageTableSize; // current size of page table

int numberOfFramesPerProcess = 0; //max size page table can be
int curRefIndex;

// statistics
int numberOfFaults = 0;

int hitPageNumber;

/*
 * insert pages from a reference string into a page table and measure
 * the page fault rate
 */
int testLRU(int numOfFrames, int *refString, int refStrLen)
{
    // TODO: implement
    // initialize variables
    referenceString = refString;
    refStringLength = refStrLen;
    pageTableTop = NULL;
    leastRecentlyUsed = NULL;
    pageTableSize = 0;
    numberOfFramesPerProcess = numOfFrames;
    hitPageNumber = 0;


    // run algorithm
    for(curRefIndex = 0; curRefIndex < refStringLength; curRefIndex++) {
        insertLRU(referenceString[curRefIndex]);
        displayLRU();
    }
    freePageTableLRU();

    return numberOfFaults;
}

/*
 *	try to insert a page into the page table
 */
void insertLRU(int pageNumber)
{
    // TODO: implement
    int localNum = pageNumber;
    FRAME *referenced = searchLRU(localNum);
    //if not in table and table is not full
    if(pageTableSize < numberOfFramesPerProcess && referenced == NULL) {
        // push onto stack
        FRAME *temp = (FRAME *) malloc(sizeof(FRAME *));
        temp->pageNum = pageNumber;
        temp->up = NULL;
        // if empty
        if(pageTableSize == 0) {
            temp->down = NULL;
            leastRecentlyUsed = temp;
            pageTableTop = temp;
        }
        else {
            pageTableTop->up = temp;
            temp->down = pageTableTop;
            pageTableTop = temp;
        }

        hitPageNumber = -1; // indicates no hits, there was a fault
        pageTableSize++;
    }
    // if it is in table
    else if (referenced != NULL) {
        hitPageNumber = pageNumber;
        if(pageTableSize > 1) {
            // if not on the top and not on the bottom
            if(referenced != pageTableTop && referenced != leastRecentlyUsed) {
                referenced->down->up = referenced->up;
                referenced->up->down = referenced->down;
                referenced->up = NULL;
                referenced->down = pageTableTop;
                pageTableTop->up = referenced;
                pageTableTop = referenced;
            }
            //else if on bottom
            else if(referenced == leastRecentlyUsed) {
                leastRecentlyUsed = referenced->up;
                leastRecentlyUsed->down = NULL;
                referenced->up = NULL;
                referenced->down = pageTableTop;
                pageTableTop->up = referenced;
                pageTableTop = referenced;
            }
        }
    }
    // table is full and page is not there
    else if (pageTableSize == numberOfFramesPerProcess && referenced == NULL) { //page table is full
        //push on stack and get rid of lru
        FRAME *temp = (FRAME *) malloc(sizeof(FRAME *));
        temp->pageNum = pageNumber;
        temp->up = NULL;
        if(pageTableSize == 1) {
            temp->down = NULL;
            pageTableTop = temp;
            leastRecentlyUsed = temp;
        }
        else {
            //push new frame on top
            temp->down = pageTableTop;
            pageTableTop->up = temp;
            pageTableTop = temp;
            //get rid of lru
            leastRecentlyUsed = leastRecentlyUsed->up;
            free(leastRecentlyUsed->down);
            leastRecentlyUsed->down = NULL;
        }
        hitPageNumber = -1; // indicates no hits, there was a fault
    }
}

/**
 * Searches for page pageNumber in the page frame list
 * returns NULL if a frame with pageNumber was not found
 * otherwise, returns a reference to the frame with pageNumber
 */
FRAME *searchLRU(int pageNumberSearch)
{
    // TODO: implement
    FRAME *curFrame = pageTableTop;
    while(curFrame != NULL) {
        if(curFrame->pageNum == pageNumberSearch) {
            return curFrame;
        }
        curFrame = curFrame->down;
    }
    numberOfFaults++;
    return NULL;
}

void displayLRU()
{
    // TODO: implement
    // go through table and print pageNumber and whether it was referrenced or replaced

    FRAME *curFrame = pageTableTop;
    int curIndex = 0;
    printf("%d ->    ", (referenceString[curRefIndex]));
    while(curFrame != NULL) {
        printf("%d", curFrame->pageNum);
        if(curFrame->pageNum == hitPageNumber) {
            printf("<  ");
        }
        else if(curFrame == leastRecentlyUsed && hitPageNumber == -1) { //bottom of stack and fault
            printf("*  ");
        }
        else {
            printf("   "); //spacing
        }
        curFrame = curFrame->down;
        curIndex++;
    }
    printf("\n");

}

void freePageTableLRU()
{
    // TODO: implement
    FRAME *curFrame = pageTableTop;
    while(curFrame->down != NULL) {
        curFrame = curFrame->down;
        free(curFrame->up);
    }
    free(curFrame);
}

