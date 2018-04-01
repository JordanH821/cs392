CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy
CC = gcc
all:
	$(CC) $(CFLAGS) server.c -o server $(CLIBS)
	$(CC) $(CFLAGS) client.c -o client $(CLIBS)

clean:
	rm -f server
	rm -f client

fclean: clean

re: fclean all