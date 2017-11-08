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

bool addToNodeDown(NODE *pointNode, NODE *newNode);

bool addToNodeNext(NODE *pointNode, NODE *newNode);

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
    tempAllPaths[1] = "Root.Henrik = \"Update your software\"\n";
    tempAllPaths[2] = "Root.Henrik.Fredrik = \"Oppdater programvaren\"\n";

    int countOfNodes = 0;
    struct NODE *head;

    NODE *rootNode = createNode("Root", NULL, NULL);
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

    addToNodeNext(head, knutNode);
    addToNodeDown(head, henrikNode);

    head = lookupNode(tempAllPaths, "Henrik", rootNode);
    addToNodeDown(head, fredrikNode);



    NODE *someNode = lookupNode(tempAllPaths, "Fredrik", rootNode);
    if (someNode->pszName != rootNode->pszName) {
        printf("Minneadressen til noden er: %p", someNode);
    } else {
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
    char **parsedOnSpace;
    NODE *head;
    head = rootNode;
    NODE *temp = rootNode;
    int k = 0;

    while (allPaths[k] != NULL) {
        if (strstr(allPaths[k], nodeName) != NULL) {
            char *path = allPaths[k];
            printf("Path is: %s", path);

            parsedPath = parsePathToNode(path, '.');

            int m = 1;
            while (parsedPath[m] != NULL) {
                printf("parsedPath[M] er: %s \n", parsedPath[m]);
                parsedOnSpace = parsePathToNode(parsedPath[m], ' ');

                int q = 0;
                while (parsedOnSpace[q] != NULL) {
                    printf("parsedOnSpace er: %s \n", parsedOnSpace[q]);
                    printf("Navn på head-node: %s \n", head->pszName);


                    NODE *tempDownNode;
                    tempDownNode = head->pDownNodes;
                    if (tempDownNode != NULL) {
                        printf("tempDownNode er: %s \n", tempDownNode->pszName);
                    }
                    NODE *tempNextNode;
                    tempNextNode = head->pNextNode;
                    if (tempNextNode != NULL) {
                        printf("tempNextNode er: %s \n", tempNextNode->pszName);
                    }

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

                    printf("Navn på head-node etter flytt: %s \n", head->pszName);

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

    return
            head;
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
