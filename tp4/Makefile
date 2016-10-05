CC = gcc
CFLAGS = -Wall -Werror -W

chaines: tp4_main.o tp4_1.o tp4_2.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^
