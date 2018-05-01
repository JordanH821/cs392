CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy -lncurses
CC = gcc
all:
	$(CC) $(CFLAGS) snake.c -o snake $(CLIBS)

clean:
	rm -f snake

fclean: clean

re: fclean all