CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy -I/home/jbass/ncurses/include -L/home/jbass/ncurses/lib -lncurses
CC = gcc
all:
	$(CC) $(CFLAGS) myselect.c -o myselect $(CLIBS)

clean:
	rm -f myselect

fclean: clean

re: fclean all