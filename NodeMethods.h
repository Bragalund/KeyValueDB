//
// Created by bragalund on 12.11.17.
//

#ifndef EKSAMENSINNLEVERING_NODEMETHODS_H
#define EKSAMENSINNLEVERING_NODEMETHODS_H

struct NODE *createNode(char *pszName, unsigned long ulIntVal, char *pszString);

#include "KeyValueDB.h"

NODE *nodeOnSameLevel(char *nodeName, NODE *pointNode);

bool hasValidUnderNode(struct NODE *pointNode, char *nodeName);

NODE *getLastNodeOnSameLevel(NODE *pointNode);

bool addToNodeDown(NODE *pointNode, NODE *newNode);

bool addToNodeNext(NODE *pointNode, NODE *newNode);

NODE **createAllNodes(char **pathsFromFile, char **valuesFromFile, NODE *rootNode);

void printAllNodes(NODE** allNodes);

void freeAllNodes(NODE** allNodes);

NODE *lookupNode(char **allPaths, char *nodeName, NODE *rootNode);

#endif //EKSAMENSINNLEVERING_NODEMETHODS_H
