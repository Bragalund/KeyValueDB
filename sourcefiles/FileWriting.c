#include "../headerfiles/FileWriting.h"


FILE* openFile(char *filename) {
    bool fileExists;
    FILE* file;
    if (access(filename, F_OK) != -1) {
        fileExists = true;
    }
    else{
        fileExists=false;
    }
    if (fileExists) {
        file = fopen(filename, "r+");
    } else {
        printf("File does not exist.\n");
        exit(1);
    }
    return file;
}


