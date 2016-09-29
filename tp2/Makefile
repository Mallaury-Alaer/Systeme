CC = gcc
CFLAGS = -Wall -Werror -W

tp2: tp2_main.o tp2_1.o tp2_2.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^


