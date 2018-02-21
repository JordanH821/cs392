OBJS = list.o

OBJSC = list.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) -c $(OBJSC) $(CLIBS)
	ar -rc liblist.a $(OBJS)
	ranlib liblist.a
	mv liblist.a ../../lib
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OBJS)
	rm -f ../../lib/liblist.a
	rm -f a.out

re: fclean all

test: all
	$(CC) $(CFLAGS) ../../test/testlist.c -L../../lib -llist -lmy
	./a.out
	rm -f a.out