/**
* Name: Neil Marcellini
* Lab/task: Lab 10
* Date: 11/6/19
* This implements the OPT page-replacement algorithm.
**/

#include "../inc/optArray.h"

int *referenceString;
int refStringLength;

// the page frame list
int *pageTable;
int pageTableSize;

int victimIndex;
int hitPageNumber;

// statistics
int numOfFaults;

// this index is used to go through the sequence of pages references
int currentPgeReferenceIndex = 0;

int testOPT(int numOfFrames, int *refString, int refStrLen)
{
    // TODO: implement

    // initialize variables
    numOfFaults = 0;
    hitPageNumber = 0;
    victimIndex = 0;
    referenceString = refString;
    refStringLength = refStrLen;

    //allocate pageTable
    pageTable = (int *) calloc(numOfFrames, sizeof(int));
    pageTableSize = numOfFrames;
    // initialize all elements to -1
    for(int i = 0; i < numOfFrames; i++) {
        pageTable[i] = -1;
    }

    // run algorithm
    for(currentPgeReferenceIndex = 0; currentPgeReferenceIndex < refStringLength; currentPgeReferenceIndex++) {
        insertOPT(referenceString[currentPgeReferenceIndex]);
        displayOPT();
    }

    return numOfFaults;
}

/*
 *	try to insert a page into the page table
 */
void insertOPT(int pageNumber)
{
    int searchVal = searchOPT(pageNumber);

    pageTable[searchVal] = pageNumber;
}

/*
 *  find either an empty slot, or the page, or a victim to evict
 */
int searchOPT(int pageNumber)
{
    // TODO: implement
    int returnIndex = 0;
    bool found = false;
    for(int i = 0; i < pageTableSize && !found; i++) {
        if(pageTable[i] == FREE_SLOT || pageTable[i] == pageNumber) {
            returnIndex = i;
            found = true;
            if(pageTable[i] == pageNumber) {
                hitPageNumber = pageNumber;
                victimIndex = -1; // page fault did not happen
            }
            else {
                numOfFaults++;
                victimIndex = i;
                hitPageNumber = -2; // hit did not happen
            }
        }
    }

    // if table was full and didn't contain the page, find a replacement
    if(!found) {
        //page fault
        numOfFaults++;
        returnIndex = findVictimPageOPT();
        victimIndex = returnIndex;
        hitPageNumber = -2; // hit did not happen
    }

    return returnIndex;
}

int findVictimPageOPT()
{
    // TODO: implement
    int farthestIndex = 0; // page element with farthest next reference
    int farthestReference = 0; //index within reference string of farthest reference
    // for each page in page table
    for(int i = 0; i < pageTableSize; i++) {
        // find next page reference
        int nextRef = refStringLength; // impossible index represents not being referrenced again
        bool found = false;
        int strIndex;
        for(strIndex = currentPgeReferenceIndex; strIndex < refStringLength && !found; strIndex++) {
            // if the page number is found in the reference string
            if((int) referenceString[strIndex] == pageTable[i]) {
                nextRef = strIndex;
                found = true;
            }
        }
        // if it is referenced further in the future or not referrenced at all
        if(nextRef > farthestReference) {
            farthestReference = nextRef;
            farthestIndex = i;
        }
    }
    victimIndex = farthestIndex;
    return farthestIndex;
}

void displayOPT()
{
    // todo: implement
    //6 ->    6*  -1   -1   -1

    printf("%d ->    ", referenceString[currentPgeReferenceIndex]);
    for(int i = 0; i < pageTableSize; i++) {
        printf("%d", pageTable[i]);
        if(hitPageNumber == pageTable[i]) {
            //there was a page hit here
            printf("<  ");
        }
        else if(victimIndex == i) {
            //there was a page fault here
            printf("*  ");
        }
        else {
            printf("   "); // for spacing
        }
    }
    printf("\n");

}

void freePageTableOPT()
{
    // TODO: implement
    free(pageTable);
}
