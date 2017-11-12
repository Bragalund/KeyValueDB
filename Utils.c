
#include "KeyValueDB.h"
#include "Utils.h"

void printList(char *listname, char **list) {
    int lol = 0;
    while (list[lol] != NULL) {
        printf("%s[%d] er: %s \n", listname, lol, list[lol]);
        lol++;
    }
}

void freeList(char **stringArray) {
    int index = 0;
    while (stringArray[index] != NULL) {
        free(stringArray[index]);
        stringArray[index] = NULL;
        index++;
    }
}

bool isDigit(char *someString) {
    bool isDigit = true;
    int length;
    length = strlen(someString);
    for (int i = 0; i < length; i++) {
        if (!isdigit(someString[i])) {
            isDigit = false;
        }
    }
    return isDigit;
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
    char tempPath[550];
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

FILE *openFile(char *filename) {
    FILE *file;// = malloc(256 * 12 * sizeof(FILE));
    file = fopen(filename, "r");
    if (file != NULL) {
        return file;
    } else {
        printf("File %s does not exist. \n exiting...\n", filename);
        exit(1);
    }
    return NULL;
}

void addToList(char **allLinesParsedOnEquals, int index, char *value) {

    size_t size = strlen(value);
    char *new_value;

    new_value = malloc(size * sizeof(char));

    if (new_value) {
        new_value = value;
        allLinesParsedOnEquals[index] = new_value;
    }
}