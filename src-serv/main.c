#include "net.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

void signalHandler( int signum ) {
    (void) signum;
    printf("clearing child");
    fflush(stdout);
    wait(NULL);
}

int main()
{
    //printf("starting");
    fflush(stdout);
     signal(SIGCHLD, signalHandler);
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
