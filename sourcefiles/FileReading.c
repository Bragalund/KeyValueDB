#include <stdlib.h>
#include "../headerfiles/FileReading.h"

bool isString(char *value) {
    long lastCharIndex = strlen(value);

    //Checks if first and last letters in value is " "
    if (value[0] == '"' && value[lastCharIndex] == '"') {
        return true;
    }
    return false;
}

//char **getAllLinesInFile(FILE *file) {
//    long sizeOfFile = getSizeOfFileBySeek(file);
//    char** allLines=malloc(sizeOfFile * MAX_CHARS_ON_LINE * sizeof(char));
//    for(int i =0;i<sizeOfFile;i++){
//        allLines[i]=getLine(file, i);
//    }
//    return **allLines;
//}
//
//char *getLine(FILE *file, long *lineNumber) {
//
//    char *line = malloc(MAX_CHARS_ON_LINE * sizeof(char));
//    if (fgets(line, lineNumber, file) != NULL) {
//        return line;
//    } else {
//        printf("Something went wrong in getLine (FileReading.c) \n");
//        exit(1);
//    }
//}


//
//long getSizeOfFileBySeek(FILE *fr) {
//    fseek(fr, 0, SEEK_END);
//    long size = ftell(fr);
//    fseek(fr, 0, SEEK_SET);
//    return size;
//}
