#ifndef EKSAMENSINNLEVERING_FILEWRITER_H
#define EKSAMENSINNLEVERING_FILEWRITER_H

#include "KeyValueDB.h"

FILE* openOrCreateFile(char *filename);
void closeFile(FILE* file);
bool testIfFileExists(char *filename);

#endif //EKSAMENSINNLEVERING_FILEWRITER_H
