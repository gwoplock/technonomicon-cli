OBJS = client.o
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 --pedantic-errors -c
LFLAGS = -lncurses

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o client
