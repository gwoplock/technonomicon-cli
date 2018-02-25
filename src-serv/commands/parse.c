#include "parse.h"
#include <stdlib.h>
#include <string.h>

char** strSplit(char* toSplit, char delim){
    int tokens = 0;
    for (int i = 0; i < strlen(toSplit); i++){
        if(toSplit[i] == delim){
            tokens++;
        }
    }
    char** toRet = calloc(sizeof(char*), tokens+1);
    for(int i = 0, k = 0; i < strlen(toSplit); i++){
        if(toSplit[i] == delim){
            toRet[k] = toSplit + (i - 1);
            toSplit[i] ='\0';
            k++;
        }
    }
    return toRet;
}

struct Command *parseCMD(char* toParse){
   char** tokens = strSplit(toParse, ' ');
   struct Command* toRet = calloc(1, sizeof(struct Command));
   toRet->fullCommand = tokens;
   if(strcmp(tokens[0], "view") == 0){
       toRet->cmdCode = VIEW;
   } else if(strcmp(tokens[0], "exit") == 0){
       toRet->cmdCode = EXIT;
   } else {
       toRet->cmdCode = UNKNOWN;
       //unknown command
   }
   return toRet;
}