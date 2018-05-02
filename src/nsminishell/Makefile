OBJS = nsminishell.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy -lncurses
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) nsminishell.c -o nsminishell $(CLIBS)

clean:
	rm -f nsminishell

fclean: clean

re: fclean all
