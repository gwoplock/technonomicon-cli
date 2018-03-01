OBJS = client.o
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 --pedantic-errors -c
LFLAGS = -lncurses

.PHONY: all

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o client

clean:
	rm -f $(OBJS)
	rm -f client