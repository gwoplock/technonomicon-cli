#include <arpa/inet.h>
#include <curses.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const char *HOSTNAME = "localhost";
const int AF = AF_INET;
const int PORT = 6969;

int main () {
    int tcp_socket;
    struct hostent *host;
    struct sockaddr_in sockaddr;
    struct sockaddr addr;
    char request [256];
    char command [20];
    char *file;

    /* Attempt opening socket */
    tcp_socket = socket (AF, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        printf ("Error opening socket!\n");
        goto error_quit;
    }

    /* Attempt to retrieve host */
    host = gethostbyname (HOSTNAME);
    if (!host) {
        printf ("Error resolving hostname: %s\n", HOSTNAME);
        goto error;
    }
    printf ("Got host: %s\n", host->h_name);
    printf ("Addresses:\n");
    for (int cx = 0; *(host->h_addr_list + cx); cx++) {
        printf ("    %s\n", inet_ntoa (*(struct in_addr*)(host->h_addr_list + cx)));
    }

    /* Create some necessary vars */
    sockaddr.sin_family = AF;
    sockaddr.sin_port = htons (PORT);
    memcpy (&sockaddr.sin_addr.s_addr, *host->h_addr_list, host->h_length);
    memcpy (&addr, &sockaddr, sizeof (struct sockaddr));

    /* Attempt to connect */
    if (connect (tcp_socket, &addr, sizeof (addr)) < 0) {
        printf ("Error connecting to socket!\n");
        goto error;
    }

    memset (request, 0, 256);
    sprintf (request, "technonomicon");
    printf ("Request: %s\n", request);

    /* Attempt a request */
    if (send (tcp_socket, request, strlen (request), 0) < 0) {
        printf ("Error sending request!\n");
        goto error;
    }

    /* Attempt to get response */
    if (recv (tcp_socket, request, 255, 0) < 0) {
        printf ("Error getting response!\n");
        goto error;
    }

    WINDOW *pad;
    initscr ();
    scrollok (stdscr, 1);
    
    printw ("%s\n", request);
    while (1) {
        printw ("technonomicon> ");
        getstr (command);

        if (!strcasecmp (command, "quit"))
            break;

        /* Attempt a request */
        if (send (tcp_socket, command, strlen (request), 0) < 0) {
            printw ("Error sending request!\n");
            goto error_ncurses;
        }

        memset (request, 0, 256);
        /* Attempt to get response */
        if (recv (tcp_socket, request, 8, 0) < 0) {
            printw ("Error getting response!\n");
            goto error_ncurses;
        }
        
        uint64_t size = *(uint64_t*)request;
        file = calloc (size, 1);
        if (!file) {
            printf ("Unable to allocate space for file.\n");
            goto error_ncurses;
        }

        /* Attempt to read file */
        if (recv (tcp_socket, file, size, 0) < 0) {
            printw ("Error getting file!\n");
            goto error_ncurses;
        }

        int maxy, maxx;
        getmaxyx (stdscr, maxy, maxx);
        pad = newpad (500, maxx);
        mvwprintw (pad, 0, 0, "%s", file);
        for (int cx = 0; cx < 10; cx++) {
            prefresh (pad, cx, 0, 0, 0, 20, 20);
            wgetch (pad);
        }

        free (file);
    }

    curs_set (1);
    endwin ();

    /* Cleanup */
    close (tcp_socket);
    return 0;

error_ncurses:
    endwin ();
error:
    close (tcp_socket);
error_quit:
    return -1;
}
