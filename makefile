LDFLAGS=-lncurses
CC=gcc
CFLAGS=-W

demetermake: demeter.o product_functions.o
	$(CC) -o demetermake demeter.o product_functions.o 
