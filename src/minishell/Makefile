OBJS = minishell.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy -lncurses
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) minishell.c -o minishell $(CLIBS)

clean:
	rm -f minishell

fclean: clean

re: fclean all

test: all
	$(CC) $(CFLAGS) minishell.c $(CLIBS)
	./a.out
	./a.out "taco"
	./a.out 1234
	./a.out t.a.c.o
	./a.out "one" "two" "three"
	rm -f a.out