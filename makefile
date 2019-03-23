LDFLAGS=-lncurses
CC=gcc
CFLAGS=-W

demetermake: demeter.o product_functions.o auxiliary_functions.o
	$(CC) -o demeter demeter.o product_functions.o auxiliary_functions.o
