#include "headerfiles/KeyValueDB.h"

typedef struct NODE {
    char *pszName; //Peker til navn på denne noden
    unsigned long ulIntVal; //unsigned long, som holde null eller en numerisk verdi
    char *pszString;
    struct _NODE *pNextNode;
    struct _NODE *pDownNodes;
} NODE;

struct NODE* createNode(char *pszName, unsigned long ulIntVal, char *pszString);

int main() {

    struct NODE* head;

    char *someName;
    someName = "Henrik";
    NODE* someNode = createNode(someName, NULL, "Henriks data string");
    head = someNode;

    char *someOtherName;
    someOtherName = "Knut";
    struct NODE* someOtherNode;
    someOtherNode = createNode(someOtherName, NULL, "Knut sin data string.");

    head->pNextNode = someOtherNode;

    printf("%s \n", head->pszName);

    head = head->pNextNode;

    printf("%s", head->pszName);

    free(someNode);
    free(someOtherNode);
    return 0;
}

struct NODE* createNode(char *pszName, unsigned long ulIntVal, char *pszString) {
    struct NODE *pNewNode =(struct NODE*) malloc(sizeof(struct NODE));
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