#include "net.h"
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("fork error");
    }
    else if (pid > 0)
    {
        //web server
        while(1);
    }
    else
    {
        int socket = openTechServer();
        techListen(socket);
    }
}
