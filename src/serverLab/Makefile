OBJS = server.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) server.c -o client $(CLIBS)

clean:
	rm -f client

fclean: clean

re: fclean all