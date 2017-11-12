#include "Main.h"
#include "NodeMethods.h"
#include "Utils.h"


struct NODE *createNode(char *pszName, unsigned long ulIntVal, char *pszString) {
    struct NODE *pNewNode = (struct NODE *) malloc(sizeof(struct NODE));
    pNewNode->pszName = pszName;
    if (pszString != NULL) {
        pNewNode->pszString = pszString;
    } else {
        pNewNode->ulIntVal = ulIntVal;
    }
    pNewNode->pDownNodes = NULL;
    pNewNode->pNextNode = NULL;

    return pNewNode;
}

bool hasValidUnderNode(struct NODE *pointNode, char *nodeName) {
    if (pointNode->pDownNodes != NULL) {

        struct NODE *tempDownNode = pointNode->pDownNodes;
        if (strcmp(tempDownNode->pszName, nodeName) == 0) {
            return true;
        }
    }
    return false;
}

NODE *getLastNodeOnSameLevel(NODE *pointNode) {
    struct NODE *tempNextNode;
    tempNextNode = pointNode;
    while (tempNextNode->pNextNode != NULL) {
        tempNextNode = tempNextNode->pNextNode;
    }
    return tempNextNode;
}

NODE *nodeOnSameLevel(char *nodeName, NODE *pointNode) {
    struct NODE *tempNextNode = pointNode->pNextNode;
    while (tempNextNode != NULL) {
        if (strcmp(tempNextNode->pszName, nodeName) == 0) {
            return tempNextNode;
        } else {
            tempNextNode = tempNextNode->pNextNode;
        }
    }
    return NULL;
}

bool addToNodeDown(NODE *pointNode, NODE *newNode) {
    pointNode->pDownNodes = newNode;
    if (pointNode->pDownNodes != NULL) {
        return true;
    }
    return false;
}

bool addToNodeNext(NODE *pointNode, NODE *newNode) {
    pointNode->pNextNode = newNode;
    if (pointNode->pNextNode != NULL) {
        return true;
    }
    return false;
}

NODE **createAllNodes(char **pathsFromFile, char **valuesFromFile, NODE *rootNode) {
    struct NODE *head;
    head = rootNode;
    int countOfNodesInAllnodes = 1;
    NODE **allNodes = malloc(sizeof(NODE) * 50);
    allNodes[0] = head;
    int counter = 0;
    while (pathsFromFile[counter] != NULL) {


        char **tempNodeNames;
        tempNodeNames = parsePathToNode(pathsFromFile[counter], '.');

        NODE *subHead = NULL;
        // Sjekker om pathen har eksisterende side/under-noder. Flytter head dit.
        int levelInPath = 0;
        while (tempNodeNames[levelInPath] != NULL) {
            char *nodeName = tempNodeNames[levelInPath];

            if (levelInPath == 0) {

                NODE *tempNode = nodeOnSameLevel(nodeName, rootNode);
                if (tempNode != NULL) {
                    //printf("Node %s finnes fra før. \n", tempNode->pszName);
                    head = tempNode;
                } else {
                    NODE *lastNodeOnSameLevel = getLastNodeOnSameLevel(rootNode);
                    NODE *tempNewNode = createNode(nodeName, NULL, NULL);
                    head = tempNewNode;
                    allNodes[countOfNodesInAllnodes] = tempNewNode;
                    countOfNodesInAllnodes++;
                    addToNodeNext(lastNodeOnSameLevel, tempNewNode);
                    //printf("created node %s \n", tempNewNode->pszName);
                }
            } else if (levelInPath == 1) {
                //printf("head is %s\n", head->pszName);
                //printf("nodename %s \n", nodeName);
                if (hasValidUnderNode(head, nodeName)) {
                    //printf("node down for %s exists \n", head->pszName);
                    subHead = head->pDownNodes;
                } else {
                    unsigned long someUnsignedLong = NULL;
                    char *loglevel = "loglevel ";
                    if (strcmp(nodeName, loglevel) == 0) {
                        someUnsignedLong = atoi(valuesFromFile[counter]);
                        //printf("Node %s has value %lu \n", nodeName, someUnsignedLong);
                    }

                    NODE *tempNewNode = createNode(nodeName, someUnsignedLong, NULL);
                    //printf("Creates downNode %s of %s \n", tempNewNode->pszName, head->pszName);
                    addToNodeDown(head, tempNewNode);
                    allNodes[countOfNodesInAllnodes] = tempNewNode;
                    countOfNodesInAllnodes++;
                    subHead = tempNewNode;
                }

            } else if (levelInPath == 2) {
                //printf("subHead er %s \n", subHead->pszName);
                if (subHead->pDownNodes != NULL) {
                    //printf("subhead down node was not NULL\n");
                    NODE *subSubNode = subHead->pDownNodes;
                    NODE *someNextNode = nodeOnSameLevel(nodeName, subSubNode);
                    if (someNextNode == NULL) {
                        NODE *lastNodeOnSameLevel = getLastNodeOnSameLevel(subSubNode);

                        char *someString = NULL;
                        unsigned long someUnsignedLong = NULL;
                        if (isDigit(valuesFromFile[counter])) {
                            someUnsignedLong = atoi(valuesFromFile[counter]);
                        } else {
                            someString = valuesFromFile[counter];
                        }

                        NODE *newTempNode = createNode(nodeName, someUnsignedLong, someString);
                        addToNodeNext(lastNodeOnSameLevel, newTempNode);
                        allNodes[countOfNodesInAllnodes] = newTempNode;
                        countOfNodesInAllnodes++;
                    } else {
                        printf("SubSubNode did exist? Strange...\n");
                    }
                } else {
                    //printf("Down node for %s is NULL \n", subHead->pszName);
                    NODE *tempNewNode = createNode(nodeName, NULL, NULL);
                    //printf("Created Node: %s \n", tempNewNode->pszName);
                    addToNodeDown(subHead, tempNewNode);
                    allNodes[countOfNodesInAllnodes] = tempNewNode;
                    countOfNodesInAllnodes++;
                }
            }

            levelInPath++;
        }

        counter++;
    }
    return allNodes;
}

void printAllNodes(NODE** allNodes){
    int q = 0;
    while (allNodes[q] != NULL) {
        printf("[%d] Nodenavn: %s \n", q, allNodes[q]->pszName);
        if (allNodes[q]->ulIntVal != NULL) {
            printf("Has value: %lu \n", allNodes[q]->ulIntVal);
        } else if (allNodes[q]->pszString != NULL) {
            printf("Has value: %s \n", allNodes[q]->pszString);
        }
        q++;
    }
}

void freeAllNodes(NODE** allNodes){
    int klm =0;
    while(allNodes[klm] != NULL){
        free(allNodes[klm]);
        klm++;
    }
}

NODE *lookupNode(char **allPaths, char *nodeName, NODE *rootNode) {
    char **parsedPath;
    char **parsedOnSpace;
    NODE *head;
    head = rootNode;
    NODE *temp = rootNode;
    int k = 0;

    while (allPaths[k] != NULL) {
        if (strstr(allPaths[k], nodeName) != NULL) {
            char *path = allPaths[k];
            //printf("Path is: %s \n", path);

            parsedPath = parsePathToNode(path, '.');

            int m = 1;
            while (parsedPath[m] != NULL) {
                //printf("parsedPath[M] er: %s \n", parsedPath[m]);
                parsedOnSpace = parsePathToNode(parsedPath[m], ' ');

                int q = 0;
                while (parsedOnSpace[q] != NULL) {
                    //printf("parsedOnSpace er: %s \n", parsedOnSpace[q]);
                    //printf("Navn på head-node: %s \n", head->pszName);


                    NODE *tempDownNode;
                    tempDownNode = head->pDownNodes;

                    NODE *tempNextNode;
                    tempNextNode = head->pNextNode;


                    int whereToMoveHead = 0;

                    if (tempDownNode != NULL) {
                        if (strcmp(tempDownNode->pszName, parsedOnSpace[q]) == 0) {
                            whereToMoveHead = 1;
                        }
                    }


                    if (tempNextNode != NULL) {
                        if (strcmp(tempNextNode->pszName, parsedOnSpace[q]) == 0) {
                            whereToMoveHead = 2;
                        }
                    }


                    if (whereToMoveHead == 1) {
                        head = tempDownNode;
                    } else if (whereToMoveHead == 2) {
                        head = tempNextNode;
                    }

                    //printf("Navn på head-node etter flytt: %s \n", head->pszName);
                    q++;
                }
                if (head->pszName == nodeName) {
                    printf("Endelig navn på head etter lookup: %s \n", head->pszName);
                    break;
                }

                m++;
            }
        }
        k++;
    }

    return head;
}