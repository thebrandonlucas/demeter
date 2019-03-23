LDFLAGS=-lncurses
CFLAGS=-W

demetermake: demeter.c product_functions.c auxiliary_functions.c
	gcc -o demeter -std=c11 demeter.c product_functions.c auxiliary_functions.c
