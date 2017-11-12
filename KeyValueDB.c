#include <assert.h>
#include <ctype.h>
#include "headerfiles/KeyValueDB.h"

typedef struct NODE {
    char *pszName; //Peker til navn på denne noden
    unsigned long ulIntVal; //unsigned long, som holde null eller en numerisk verdi
    char *pszString;
    struct _NODE *pNextNode;
    struct _NODE *pDownNodes;
} NODE;

FILE *openFile(char *filename);

NODE *getLastNodeOnSameLevel(NODE *pointNode);

bool isDigit(char *someString);

void printList(char *listname, char **list);

void freeList(char **stringArray);

char **parsePathToNode(char *path, const char a_delim);

void addToList(char **allLinesParsedOnPunctuation, int index, char *value);

long getSizeOfFileBySeek(FILE *fr);

bool addToNodeDown(NODE *pointNode, NODE *newNode);

bool addToNodeNext(NODE *pointNode, NODE *newNode);

NODE *lookupNode(char **allPaths, char *nodeName, NODE *rootNode);

NODE **createAllNodes(char **pathsFromFile, char **valuesFromFile, NODE *rootNode);

struct NODE *createNode(char *pszName, unsigned long ulIntVal, char *pszString);

int main() {


    char *someLine;
    FILE *file;
    char *filename = "db.txt";

    // opens file and exits program if it does not exist
    file = openFile(filename);
    ssize_t sizeOfLine;
    size_t len = 0;

    size_t sizeOfFile;
    char buf[550];

    // finds amount of characters in file
    sizeOfFile = fread(buf, sizeof(*buf), sizeof(buf) / sizeof(*buf), file);

    // puts all chars of buffer into allText
    char *allText = malloc(sizeOfFile * sizeof(char));
    for (int w = 0; w < sizeOfFile; w++) {
        allText[w] = buf[w];
    }

    int countOfLines = 12;
    int b = 0;
    char **allLinesParsedOnNewLine;
    char **allLinesParsedOnEqual;

    allLinesParsedOnEqual = malloc(256 * sizeof(char));
    allLinesParsedOnNewLine; // = malloc(256 * sizeof(char));

    allLinesParsedOnNewLine = parsePathToNode(allText, '\n');

    int f = 0;
    while (allLinesParsedOnNewLine[f] != NULL) {
        char **tempArray;
        tempArray = parsePathToNode(allLinesParsedOnNewLine[f], '=');
        int d = 0;
        while (tempArray[d] != NULL) {
            addToList(allLinesParsedOnEqual, d + f * 2, tempArray[d]);
            //printf("tempArray[%d] er %s \n",d,tempArray[d]);
            //printf("allLinesParsedOnEqual[%d] er: %s \n",f*2+d,allLinesParsedOnEqual[f*2+d]);
            d++;
        }
        f++;
    }


    char **pathsFromFile;
    char **valuesFromFile;

    pathsFromFile = malloc(256 * sizeof(char));
    valuesFromFile = malloc(256 * sizeof(char));

    int x = 0;
    int indexInLists = 0;
    while (allLinesParsedOnEqual[x] != NULL) {

        indexInLists = x / 2;

        addToList(pathsFromFile, indexInLists, allLinesParsedOnEqual[x]);
        addToList(valuesFromFile, indexInLists, allLinesParsedOnEqual[x + 1]);

        //printf("pathsFromFile[%d] er: %s \n", indexInLists, pathsFromFile[indexInLists]);
        //printf("valuesFromFile[%d] er: %s \n", indexInLists, valuesFromFile[indexInLists]);

        x = x + 2;
    }

    printList("pathsFromFile", pathsFromFile);
    printList("valuesFromFile", valuesFromFile);

    int countOfNodes = 0;
    struct NODE *head;
    NODE *rootNode = createNode("Root", NULL, NULL);
    countOfNodes++;
    head = rootNode;

    NODE **allNodes = createAllNodes(pathsFromFile, valuesFromFile, head);

    int q = 0;
    while (allNodes[q] != NULL) {
        printf("[%d] Nodenavn: %s \n", q, allNodes[q]->pszName);
        if(allNodes[q]->ulIntVal != NULL){
            printf("Has value: %lu \n", allNodes[q]->ulIntVal);
        }
        else if(allNodes[q]->pszString != NULL){
            printf("Has value: %s \n", allNodes[q]->pszString);
        }
        q++;
    }




    fclose(file);

    freeList(allLinesParsedOnEqual);
    freeList(allLinesParsedOnNewLine);

    for (int i = 0; i < countOfNodes; i++) {
        free(allNodes[i]);
    }

    free(valuesFromFile);
    free(pathsFromFile);
    free(allLinesParsedOnNewLine);
    free(allLinesParsedOnEqual);
    free(allText);
    free(allNodes);
    //free(allPaths);
    return 0;
}

void printList(char *listname, char **list) {
    int lol = 0;
    while (list[lol] != NULL) {
        printf("%s[%d] er: %s \n", listname, lol, list[lol]);
        lol++;
    }
}

void freeList(char **stringArray) {
    int index = 0;
    while (stringArray[index] != NULL) {
        free(stringArray[index]);
        stringArray[index] = NULL;
        index++;
    }
}

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

bool isDigit(char *someString) {
    bool isDigit = true;
    int length;
    length = strlen(someString);
    for (int i = 0; i < length; i++) {
        if (!isdigit(someString[i])) {
            isDigit = false;
        }
    }
    return isDigit;
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

bool hasValidUnderNode(NODE *pointNode, char *nodeName) {
    if (pointNode->pDownNodes != NULL) {

        NODE* tempDownNode = pointNode->pDownNodes;
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

        NODE* subHead=NULL;
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
                    printf("created node %s \n", tempNewNode->pszName);
                }
            } else if (levelInPath == 1) {
                //printf("head is %s\n", head->pszName);
                //printf("nodename %s \n", nodeName);
                if (hasValidUnderNode(head, nodeName)){
                    //printf("node down for %s exists \n", head->pszName);
                    subHead = head->pDownNodes;
                }
                else{
                    unsigned long someUnsignedLong = NULL;
                    char* loglevel = "loglevel ";
                    if(strcmp(nodeName, loglevel) == 0){
                        someUnsignedLong = atoi(valuesFromFile[counter]);
                        printf("Node %s has value %lu \n", nodeName, someUnsignedLong);
                        //someUnsignedLong = malloc(sizeof(unsigned long));

                    }

                    NODE *tempNewNode = createNode(nodeName, someUnsignedLong, NULL);
                    printf("Creates downNode %s of %s \n", tempNewNode->pszName ,head->pszName);
                    addToNodeDown(head, tempNewNode);
                    allNodes[countOfNodesInAllnodes] = tempNewNode;
                    countOfNodesInAllnodes++;
                    subHead = tempNewNode;
                }

            } else if (levelInPath == 2) {
                //printf("subHead er %s \n", subHead->pszName);
                if(subHead->pDownNodes !=NULL){
                    //printf("subhead down node was not NULL\n");
                    NODE* subSubNode = subHead->pDownNodes;
                    NODE* someNextNode = nodeOnSameLevel(nodeName, subSubNode);
                    if(someNextNode == NULL){
                        NODE* lastNodeOnSameLevel = getLastNodeOnSameLevel(subSubNode);

                        char* someString = NULL;
                        unsigned long someUnsignedLong = NULL;
                        if(isDigit(valuesFromFile[counter])){
                            someUnsignedLong = atoi(valuesFromFile[counter]);
                        }else{
                            someString = valuesFromFile[counter];
                        }

                        NODE* newTempNode = createNode(nodeName, someUnsignedLong, someString);
                        addToNodeNext(lastNodeOnSameLevel, newTempNode);
                        allNodes[countOfNodesInAllnodes] = newTempNode;
                        countOfNodesInAllnodes++;
                    }else{
                        printf("SubSubNode did exist? Strange...\n");
                    }
                }else{
                    printf("Down node for %s is NULL \n", subHead->pszName);
                    NODE *tempNewNode = createNode(nodeName, NULL, NULL);
                    printf("Created Node: %s \n", tempNewNode->pszName);
                    addToNodeDown(subHead, tempNewNode);
                    allNodes[countOfNodesInAllnodes] = tempNewNode;
                    countOfNodesInAllnodes++;
                }
            }

            levelInPath++;
        }
        //NODE* tempNode = lookupNode(pathsFromFile, tempNodeNames[levelInPath], head);
//
//            if(tempNode != head){
//                head = tempNode;
//                levelInPath++;
//            } else {
//
//                // Creates node with name and string/int-value to node
//                if (levelInPath == 2) {
//
//                    // Adds int value if digits
//                    if (isDigit(valuesFromFile[counter])) {
//                        allNodes[countOfNodesInAllnodes] = createNode(tempNodeNames[levelInPath],
//                                                                      atoi(valuesFromFile[counter]), NULL);
//                        countOfNodesInAllnodes++;
//                    }
//                    // Adds String value if not digits
//                    else {
//                        allNodes[countOfNodesInAllnodes] = createNode(tempNodeNames[levelInPath], NULL, valuesFromFile[counter]);
//                        countOfNodesInAllnodes++;
//                    }
//                }
//                    // Creates node with name
//                else {
//                    NODE* tempNewNode = createNode(tempNodeNames[levelInPath], NULL, NULL);
//                    allNodes[countOfNodesInAllnodes] = tempNewNode;
//
//                    printf("created node %s \n", allNodes[countOfNodesInAllnodes]->pszName);
//
//                    if(levelInPath == 0 && (strcmp(head->pszName, "strings") == 0 || strcmp(head->pszName, "config") == 0)){
//                        printf("Added node %s next to %s \n",tempNewNode->pszName, allNodes[countOfNodesInAllnodes-1]);
//                        addToNodeNext(head, allNodes[countOfNodesInAllnodes]);
//                    }
//                    else if(levelInPath == 1 && (strcmp(head->pszName, "no") == 0 || strcmp(head->pszName, "en") == 0 || strcmp(head->pszName, "loglevel") == 0 || strcmp(head->pszName, "update") == 0)){
//                        addToNodeNext(head, allNodes[countOfNodesInAllnodes]);
//                    }else{
//                        addToNodeDown(head, allNodes[countOfNodesInAllnodes]);
//                    }
//
//
//                    countOfNodesInAllnodes++;
//                }
//                head = allNodes[countOfNodesInAllnodes -1];

        counter++;
    }
    return allNodes;
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

//                    if (tempDownNode != NULL) {
//                        printf("tempDownNode er: %s \n", tempDownNode->pszName);
//                    }

//                    if (tempNextNode != NULL) {
//                        printf("tempNextNode er: %s \n", tempNextNode->pszName);
//                    }

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

char **parsePathToNode(char *path, const char delimiter) {
    char **result = 0;
    size_t count = 0;
    char *tmp = path;
    char *last_punctuation = 0;
    char delim[2];
    delim[0] = delimiter;
    delim[1] = 0;

    while (*tmp) {
        if (delimiter == *tmp) {
            count++;
            last_punctuation = tmp;
        }
        tmp++;
    }
    count += last_punctuation < (path + strlen(path) - 1);
    count++;
    result = malloc(sizeof(char *) * count);
    char tempPath[550];
    strcpy(tempPath, path);
    if (result) {
        size_t idx = 0;
        char *token = strtok(tempPath, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
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


FILE *openFile(char *filename) {
    FILE *file;// = malloc(256 * 12 * sizeof(FILE));
    file = fopen(filename, "r");
    if (file != NULL) {
        return file;
    } else {
        printf("File %s does not exist. \n exiting...\n", filename);
        exit(1);
    }
    return NULL;
}

void addToList(char **allLinesParsedOnEquals, int index, char *value) {

    size_t size = strlen(value);
    char *new_value;

    new_value = malloc(size * sizeof(char));

    if (new_value) {
        new_value = value;
        allLinesParsedOnEquals[index] = new_value;
    }
}

long getSizeOfFileBySeek(FILE *fr) {
    fseek(fr, 0, SEEK_END);
    long size = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    return size;
}