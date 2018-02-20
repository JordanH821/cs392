OBJS = list.o

OBJSC = list.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) -c $(OBJSC)
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