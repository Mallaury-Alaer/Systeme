CFLAGS = -Wall -Werror -W
CC = gcc

tp6: tp6.o tp6_1.o tp6_2.o tp6_3.o
	$(CC) $(CFLAGS) -o  $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^
