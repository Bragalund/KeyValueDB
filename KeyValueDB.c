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


    NODE* rootNode = createNode("Root node", NULL, "Henriks data string");
    head = rootNode;

    struct NODE* knutNode;
    knutNode = createNode("Knut", NULL, "Knut sin data string.");

    struct NODE* henrikNode;
    henrikNode = createNode("Henrik", NULL, "Henrik sin down node");

    head->pNextNode = knutNode;
    head->pDownNodes = henrikNode;

    printf("%s \n", head->pszName);

    head = head->pNextNode;

    printf("%s \n", head->pszName);

    head = rootNode;

    printf("%s \n", head->pszName);

    head = head->pDownNodes;

    printf("%s \n", head->pszName);



    free(henrikNode);
    free(rootNode);
    free(knutNode);
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