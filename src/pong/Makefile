OBJS = pongclient.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) pongclient.c -o pong $(CLIBS)

clean:
	rm -f pong

fclean: clean

re: fclean all