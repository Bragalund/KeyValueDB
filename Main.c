
#include "Main.h"
#include "NodeMethods.h"
#include "Utils.h"

int main() {

    FILE *file;
    char *filename = "db.txt";

    // opens file and exits program if it does not exist
    file = openFile(filename);

    size_t sizeOfFile;
    char buf[550];

    // finds amount of characters in file
    sizeOfFile = fread(buf, sizeof(*buf), sizeof(buf) / sizeof(*buf), file);

    // puts all chars of buffer into allText
    char *allText = malloc(sizeOfFile * sizeof(char));
    for (int w = 0; w < sizeOfFile; w++) {
        allText[w] = buf[w];
    }

    char **allLinesParsedOnNewLine;
    char **allLinesParsedOnEqual;

    allLinesParsedOnEqual = malloc(256 * sizeof(char));
    allLinesParsedOnNewLine;

    allLinesParsedOnNewLine = parsePathToNode(allText, '\n');

    char **tempArray;
    int f = 0;
    while (allLinesParsedOnNewLine[f] != NULL) {

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

    NODE *rootNode = createNode("Root", NULL, NULL);

    NODE **allNodes = createAllNodes(pathsFromFile, valuesFromFile, rootNode);

    printAllNodes(allNodes);


    fclose(file);
    freeList(tempArray);
    freeList(allLinesParsedOnEqual);
    freeList(allLinesParsedOnNewLine);
    freeList(valuesFromFile);
    freeList(pathsFromFile);
    freeAllNodes(allNodes);


    free(tempArray);
    free(valuesFromFile);
    free(pathsFromFile);
    free(allLinesParsedOnNewLine);
    free(allLinesParsedOnEqual);
    free(allText);
    free(allNodes);
    return 0;
}

//
//bool setInt(unsigned long intValue, char **allPaths, char *nodeName, NODE *rootNode){
//    NODE* someNode =
//    if(someNode->ulIntVal != NULL){
//        someNode->ulIntVal = intValue;
//        return true;
//    }
//    return false;
//}
//
//bool setString(char* stringValue){
//
//}


