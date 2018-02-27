OBJS = main.o net.o commands/parse.o commands/view.o
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 --pedantic-errors -c

.PHONY: all

all: $(OBJS)
	 $(CC) $(LFLAGS) $(OBJS) -o server


clean:
	 rm -f $(OBJS)
