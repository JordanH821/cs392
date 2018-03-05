OBJS = my_alpha.o my_char.o my_digits.o my_int.o my_num_base.o \
		my_revstr.o my_str.o my_strfind.o my_strindex.o my_strlen.o \
		my_strrindex.o my_strrfind.o my_strcmp.o my_strncmp.o my_strcpy.o \
		my_strncpy.o my_strcat.o my_strdup.o my_strconcat.o my_strnconcat.o my_atoi.o my_vec2str.o my_str2vect.o

OBJSC = my_alpha.c my_char.c my_digits.c my_int.c my_num_base.c \
		my_revstr.c my_str.c my_strfind.c my_strindex.c my_strlen.c \
		my_strrindex.c my_strrfind.c my_strcmp.c my_strncmp.c my_strcpy.c \
		my_strncpy.c my_strcat.c my_strdup.c my_strconcat.c my_strnconcat.c my_atoi.c my_vec2str.c my_str2vect.c

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CC = gcc
all: $(OBJS)
	$(CC) $(CFLAGS) -c $(OBJSC)
	ar -rc libmy.a $(OBJS)
	ranlib libmy.a
	mv libmy.a ../../lib
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OBJS)
	rm -f ../../lib/libmy.a
	rm -f a.out

re: fclean all