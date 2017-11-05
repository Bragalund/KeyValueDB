#include "../headerfiles/KeyValueDB.h"

int main() {

    typedef struct _NODE {
        char *pszName; //Peker til navn på denne noden
        unsigned long ulIntVal; //unsigned long, som holde null eller en numerisk verdi
        char *pszString;
        struct _NODE *pnNodes[MAX_NODES];
    } NODE;

    char* someName;
    someName="Henrik";
    struct _NODE someNode;
    someNode.pszName=someName;

    printf("%s \n", someNode.pszName);

    return 0;
}