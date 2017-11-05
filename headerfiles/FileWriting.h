#ifndef EKSAMENSINNLEVERING_FILEWRITER_H
#define EKSAMENSINNLEVERING_FILEWRITER_H

#include "KeyValueDB.h"

bool testIfFileExists(char* filename);
FILE* openOrCreateFile(char *filename);

#endif //EKSAMENSINNLEVERING_FILEWRITER_H
