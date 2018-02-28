OBJS = pipes.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) pipes.c -o pipes $(CLIBS)

clean:
	rm -f pipes

fclean: clean

re: fclean all

test: all
	$(CC) $(CFLAGS) pipes.c $(CLIBS)
	./a.out
	./a.out "taco"
	./a.out 1234
	./a.out t.a.c.o
	./a.out "one" "two" "three"
	rm -f a.out