/**
* Name: Neil Marcellini
* Lab/task: Lab 10
* Date: 11/6/19
**/

#ifndef REPLACE_LRULIST_H
#define REPLACE_LRULIST_H

#include "replace.h"

// the page frame list
typedef struct frame {
    int pageNum;
    struct frame *up;
    struct frame *down;
} FRAME;

void insertLRU(int);
FRAME *searchLRU(int);
void displayLRU(void);
void freePageTableLRU(void);

#endif //REPLACE_LRULIST_H
