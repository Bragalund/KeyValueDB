#ifndef EKSAMENSINNLEVERING_MAIN_H

#define EKSAMENSINNLEVERING_MAIN_H

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct NODE {
    char *pszName; //Peker til navn på denne noden
    unsigned long ulIntVal; //unsigned long, som holde null eller en numerisk verdi
    char *pszString;
    struct _NODE *pNextNode;
    struct _NODE *pDownNodes;
} NODE;


#endif //EKSAMENSINNLEVERING_MAIN_H
