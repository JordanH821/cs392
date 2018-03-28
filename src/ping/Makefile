OBJS = pingclient.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) pingclient.c -o ping $(CLIBS)

clean:
	rm -f ping

fclean: clean

re: fclean all