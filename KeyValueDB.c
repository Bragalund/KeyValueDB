#include "headerfiles/KeyValueDB.h"
#include "headerfiles/FileReading.h"
#include "headerfiles/FileWriting.h"

int main() {

    typedef struct _NODE {
        char *pszName; //Peker til navn på denne noden
        unsigned long ulIntVal; //unsigned long, som holde null eller en numerisk verdi
        char *pszString;
        struct _NODE *pnNodes[MAX_NODES];
    } NODE;

    char *someName;
    someName = "Henrik";
    struct _NODE someNode;
    someNode.pszName = someName;

    printf("%s \n", someNode.pszName);
    char **allLinesInFile;

    FILE *file = openOrCreateFile("DB.txt");
    allLinesInFile = getAllLinesInFile(file);

    int amountOfLines = sizeof(allLinesInFile)/sizeof(char);
    printf("amountOfLines %i",amountOfLines);

    free(allLinesInFile);
    free(file);
    closeFile(file);
    return 0;
}