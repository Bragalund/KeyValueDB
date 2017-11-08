#include <assert.h>
#include "headerfiles/KeyValueDB.h"

typedef struct NODE {
    char *pszName; //Peker til navn på denne noden
    unsigned long ulIntVal; //unsigned long, som holde null eller en numerisk verdi
    char *pszString;
    struct _NODE *pNextNode;
    struct _NODE *pDownNodes;
} NODE;

char **parsePathToNode(char *path, const char a_delim);

NODE *lookupNode(char **allPaths, char *nodeName, NODE *rootNode);

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

    char **tempAllPaths = malloc(4 * 256 * sizeof(char));
    tempAllPaths[0] = "Root.Knut = \"Ok\"\n";
    tempAllPaths[1] = "Root.Henrik = \"Cancel\"\n";
    tempAllPaths[2] = "Root.Henrik.Fredrik = \"Update your software\"\n";

    int countOfNodes = 0;
    struct NODE *head;

    NODE *rootNode = createNode("Root", NULL, "Henriks data string");
    countOfNodes++;
    head = rootNode;

    struct NODE *knutNode;
    knutNode = createNode("Knut", NULL, "OK");
    countOfNodes++;

    struct NODE *henrikNode;
    henrikNode = createNode("Henrik", NULL, "Cancel");
    countOfNodes++;

    struct NODE *fredrikNode;
    fredrikNode = createNode("Fredrik", NULL, "Update your software");
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

    NODE* someNode = lookupNode(tempAllPaths, "Fredrik", rootNode);
    if(someNode != NULL){
        printf("Minneadressen til noden er: %s", &someNode);
    }else{
        printf("Noden finnes ikke.");
    }

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

NODE *lookupNode(char **allPaths, char *nodeName, NODE *rootNode) {
    char **parsedPath;
    NODE *head = malloc(sizeof(NODE));
    head = rootNode;
    NODE *temp = rootNode;
    int k = 0;

    while (allPaths[k] != NULL) {
        if (strstr(allPaths[k], nodeName) != NULL) {
            char *path = allPaths[k];
            printf("%s", path);

            parsedPath = parsePathToNode(path, '.');
            int m = 0;
            while (parsedPath[m] != NULL) {
                printf("%s \n", parsedPath[m]);
                printf("Navn på head-node: %s \n", head->pszName);
                if(strcmp(head->pDownNodes, allPaths[m]) != 0){
                    head = head->pDownNodes;
                }else if(strcmp(head->pNextNode, allPaths[m]) != 0){
                    head = head->pNextNode;
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
    char tempPath[256];
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