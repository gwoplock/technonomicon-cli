#include "net.h"
#include "commands/parse.h"
#include "commands/commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

#define PORT 6969

void sendMOTD(int fd){
write(fd, "welcome to the technonomicon", 28);
}

void handleMessage(int newsockfd)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("die 6");
    }
    else if (pid == 0)
    {

        char buffer[256];

        bzero(buffer, 256);
        int n = read(newsockfd, buffer, 255);
        if (strcmp(buffer, "technonomicon") != 0)
        {
            shutdown(newsockfd, SHUT_WR);
            close(newsockfd);
            exit(0);
        } else{
            sendMOTD(newsockfd);
        }
        bool exitLoop = false;
        bzero(buffer, 256);
        while (!exitLoop)
        {
            n = read(newsockfd, buffer, 255);
            struct Command* cmd = parseCMD(buffer);
            switch (cmd->cmdCode){
                case VIEW:{
                    view(newsockfd, cmd);
                    break;
                }
                case EXIT:{
                    exitLoop = true;
                    break;
                }
                default:{
                    write(newsockfd, "ERRCMD", 6);
                    break;
                }

            }
            bzero(buffer, 256);
        }

        /* if (n < 0)
        {
            printf("die 4");
        }
        printf("Here is the message: %s\n", buffer);
        n = write(newsockfd, "I got your message", 18);
        */
        shutdown(newsockfd, SHUT_WR);
        if (n < 0)
        {
            printf("die 5");
        }
        close(newsockfd);
        exit(0);
    }
    else if (pid > 0)
    {
        return;
    }
}

int openTechServer()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("die 1");
    }
    return sockfd;
}

void techListen(int sockfd)
{
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("die 2");
    }
    listen(sockfd, 5);

    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    while (1)
    {
        int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
        if (newsockfd < 0)
        {
            printf("die 3");
        }
        handleMessage(newsockfd);
    }
    close(sockfd);
}