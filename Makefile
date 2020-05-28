MAIN=sir.c

all:	
	gcc $(MAIN) function.c -lm -o euler
