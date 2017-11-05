#include "../headerfiles/FileReading.h"

bool isString(char* value){
    long lastCharIndex = strlen(value);

    //Checks if first and last letters in value is " "
    if(value[0] == '"' && value[lastCharIndex]=='"'){
        return true;
    }
    return false;
}

