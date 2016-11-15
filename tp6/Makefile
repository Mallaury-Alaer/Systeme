CC = gcc
CFLAGS = -Wall -Werror -W

modif_bmp: tp6.o main.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^
