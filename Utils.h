//
// Created by bragalund on 12.11.17.
//

#ifndef EKSAMENSINNLEVERING_UTILS_H
#define EKSAMENSINNLEVERING_UTILS_H


#include "KeyValueDB.h"

void printList(char *listname, char **list);

void freeList(char **stringArray);

bool isDigit(char *someString);

char **parsePathToNode(char *path, const char a_delim);

FILE *openFile(char *filename);

void addToList(char **allLinesParsedOnPunctuation, int index, char *value);

#include <stdio.h>



#endif //EKSAMENSINNLEVERING_UTILS_H
