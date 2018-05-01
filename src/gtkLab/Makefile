CFLAGS = `pkg-config --cflags gtk+-3.0` -g -Wall -Werror --pedantic -I../../include
CLIBS = -L../../lib -lmy `pkg-config --libs gtk+-3.0`
CC = gcc
all:
	$(CC) $(CFLAGS) gtkLab.c -o gtkLab $(CLIBS)

clean:
	rm -f gtkLab

fclean: clean

re: fclean all