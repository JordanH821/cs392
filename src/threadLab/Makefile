CFLAGS = -pthread -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy
CC = gcc
all:
	$(CC) $(CFLAGS) lab6.c -o threadLab $(CLIBS)

clean:
	rm -f threadLab
	rm -f sample

fclean: clean

re: fclean all