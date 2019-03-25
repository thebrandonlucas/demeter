LDFLAGS=-lncurses
CFLAGS=-W

demetermake: demeter.c product_functions.c auxiliary_functions.c menu.c diary.c
	gcc -o demeter -Wall -std=c11 demeter.c product_functions.c auxiliary_functions.c menu.c diary.c
