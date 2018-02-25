#include "view.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

const char *basePath = "./docs/";

int openFile(char *file)
{
    char *fullPath = calloc(sizeof(char), strlen(basePath) + strlen(file));
    strcpy(fullPath, basePath);
    strcpy(fullPath, file);
    int ret = open(fullPath, O_RDONLY);
    if (ret < 0)
    {
        //error
    }
    free(fullPath);
    return ret;
}

void view(int fdSock, struct Command* cmd){
    int fd = openFile(cmd->fullCommand[1]);
    struct stat st;
    fstat(fd, &st);
    char* ret = calloc(sizeof(char*), st.st_size);
    FILE* fileptr = fdopen(fd, "r");
    fread(ret, 1, st.st_size, fileptr); 
    fclose(fileptr);
    close(fd);
    write(fdSock, &st.st_size, sizeof(st.st_size));
    write(fdSock, ret, st.st_size);
    free(ret);
}

/*int openFile(char *file)
{
    char *fullPath = calloc(sizeof(char), strlen(basePath) + strlen(file));
    strcpy(fullPath, basePath);
    strcpy(fullPath, file);
    int ret = open(fullPath, O_RDONLY);
    if (ret < 0)
    {
        //error
    }
    free(fullPath);
    return ret;
}

char *view(char *file)
{
    int fd = openFile(file);
    struct stat st;
    fstat(fd, &st);
    char* ret = calloc(sizeof(char*), st.st_size);
    FILE* fileptr = fdopen(fd, "r");
    fread(ret, 1, st.st_size, fileptr); 
    fclose(fileptr);
    close(fd);
    return ret;
}
*/