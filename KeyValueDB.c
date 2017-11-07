#include <assert.h>
#include "headerfiles/KeyValueDB.h"

typedef struct NODE {
    char *pszName; //Peker til navn på denne noden
    unsigned long ulIntVal; //unsigned long, som holde null eller en numerisk verdi
    char *pszString;
    struct _NODE *pNextNode;
    struct _NODE *pDownNodes;
} NODE;

char** parsePathToNode(char* path,const char a_delim);
NODE *lookupNode(char **allPaths, char *nodeName, NODE* rootNode);

struct NODE *createNode(char *pszName, unsigned long ulIntVal, char *pszString);

int main() {

    char *textfile = "strings.no.header = \"Oppdatering\"\n"
            "strings.no.text = \"Oppdater programvaren\"\n"
            "strings.no.button_cancel = \"Avbryt\"\n"
            "string.en.header = \"Updating\"\n"
            "strings.en.text = \"Update your software\"\n"
            "strings.en.button_ok = \"Ok\"\n"
            "strings.en.button_cancel = \"Cancel\"\n"
            "config.loglevel = 1\n"
            "config.update.interval = 32\n"
            "config.update.server1 = \"http://www.aspenberg.no\"\n"
            "config.update.timeout = 20";

    char **allPaths = malloc(10 * 256 * sizeof(char));
    allPaths[0] = "strings.no.header = \"Oppdatering\"\n";
    allPaths[1] = "strings.no.text = \"Oppdater programvaren\"\n";
    allPaths[2] = "strings.no.button_cancel = \"Avbryt\"\n";
    allPaths[3] = "string.en.header = \"Updating\"\n";
    allPaths[4] = "strings.en.text = \"Update your software\"\n";
    allPaths[5] = "strings.en.button_ok = \"Ok\"\n";
    allPaths[6] = "strings.en.button_cancel = \"Cancel\"\n";
    allPaths[7] = "config.loglevel = 1\n";
    allPaths[8] = "config.update.interval = 32\n";
    allPaths[9] = "config.update.server1 = \"http://www.aspenberg.no\"\n";
    allPaths[10] = "config.update.timeout = 20";
    allPaths[11] = NULL;

    int countOfNodes = 0;
    struct NODE *head;

    NODE *rootNode = createNode("Root", NULL, "Henriks data string");
    countOfNodes++;
    head = rootNode;


    struct NODE *knutNode;
    knutNode = createNode("Knut", NULL, "Knut sin data string.");
    countOfNodes++;

    struct NODE *henrikNode;
    henrikNode = createNode("Henrik", NULL, "Henrik sin down node");
    countOfNodes++;

    struct NODE *fredrikNode;
    fredrikNode = createNode("Fredrik", NULL, "Fredrik sin down down node");
    countOfNodes++;

    NODE **allNodes = malloc(20 * sizeof(NODE));
    allNodes[0] = rootNode;
    allNodes[1] = knutNode;
    allNodes[2] = henrikNode;
    allNodes[3] = fredrikNode;

    head->pNextNode = knutNode;
    head->pDownNodes = henrikNode;
    printf("%s \n", head->pszName);
    head = head->pNextNode;
    printf("%s \n", head->pszName);
    head = rootNode;
    printf("%s \n", head->pszName);
    head = head->pDownNodes;
    printf("%s \n", head->pszName);
    head->pDownNodes = fredrikNode;


    lookupNode(allPaths, "header", rootNode);

    for (int i = 0; i < countOfNodes; i++) {
        free(allNodes[i]);
    }
    free(allNodes);
    free(allPaths);
    return 0;
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

NODE *lookupNode(char **allPaths, char *nodeName, NODE* rootNode) {

    NODE* temp = rootNode;
    int k=0;
    while(allPaths[k] != NULL){
        if(strstr(allPaths[k], nodeName) != NULL){
            char* path=allPaths[k];
            printf("%s \n", path);
        }
        k++;
    }


    return NULL;
}

char** parsePathToNode(char* path,const char delimiter){

    return NULL;
}