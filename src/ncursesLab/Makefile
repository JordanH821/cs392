CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy -lncurses
CC = gcc
all:
	$(CC) $(CFLAGS) curse.c -o curse $(CLIBS)

clean:
	rm -f curse

fclean: clean

re: fclean all