CC = gcc
CFLAGS = -Wall -Werror -W

modif_bmp: tp6.O
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^
