CC = gcc
CFLAGS = -Wall -Werror -W

wordsCount: tp5.o tp5_1.o 
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^
