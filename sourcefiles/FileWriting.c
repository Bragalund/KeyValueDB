#include "../headerfiles/FileWriting.h"
#include "../headerfiles/Validation.h"


FILE* openOrCreateFile(char *filename) {
    FILE *fp;

    if (testIfFileExists(filename)) {
        fp = fopen(filename, "r+");
    } else {
        fp = fopen(filename, "w+");
    }
    return fp;
}

bool testIfFileExists(char *filename) {
    if (access(filename, F_OK) != -1) {
        return true;
    }
    return false;
}

void closeFile(FILE* file){
    fclose(file);
}

