#ifndef EKSAMENSINNLEVERING_FILEREADER_H
#define EKSAMENSINNLEVERING_FILEREADER_H

#include "KeyValueDB.h"

bool isString(char* value);
char *getLine(FILE *file, long *lineNumber);
char **getAllLinesInFile(FILE *file);
long getSizeOfFileBySeek(FILE *fr, long sizeToBeRemoved);

#endif //EKSAMENSINNLEVERING_FILEREADER_H
