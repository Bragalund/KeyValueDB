#include "main.h"

int main() {

// Preprocessoren setter denne verdien
// Den setter en begrensning på antall undernoder
#define MAX_NODES 10

    typedef struct _NODE {
        char *pszName; //Peker til navn på denne noden
        unsigned long ulIntVal; //unsigned long, som holde null eller en numerisk verdi
        char *pszString;
        struct _NODE *pnNodes[MAX_NODES];
    } NODE;

    printf("%s", "Heihei");

    return 0;
}