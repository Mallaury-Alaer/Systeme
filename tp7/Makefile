CC = gcc
CFLAGS = -Wall -Werror -W

iutsh: tp7.o ligne_commande.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^