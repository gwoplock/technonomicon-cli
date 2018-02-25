#include "view.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

const char *basePath = "./docs/";

int openFile(char *file)
{
    char *fullPath = calloc(sizeof(char), strlen(basePath) + strlen(file));
    strcat(fullPath, basePath);
    strcat(fullPath, file);
    int ret = open(fullPath, O_RDONLY);
    if (ret < 0)
    {
        printf ("Error\n");
        exit (-1);
    }
    free(fullPath);
    return ret;
}

void view(int fdSock, struct Command* cmd){
    int fd = openFile(cmd->fullCommand[1]);
    FILE* fp = fdopen(fd, "r");
    if (!fp) {
        printf ("Error openinf file pointer\n");
        exit (-1);
    }
    fseek(fp, 0L, SEEK_END);
    uint64_t sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    char* ret = calloc(sizeof(char*), sz);

    fread(ret, 1, sz, fp); 
    fclose(fp);
    close(fd);
    write(fdSock, &sz, sizeof(uint64_t));
    write(fdSock, ret, sz * sizeof(uint64_t));
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
