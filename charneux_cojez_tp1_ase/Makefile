CC=gcc
CFLAGS=-m32

all: try_mul display_stack

display_stack: display_stack.c 
	$(CC) $(CFLAGS) -o $@ $^

try_mul: try.o try_mul.c  
	$(CC) $(CFLAGS) -o $@  $^

try.o: try.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *~ *.o display_stack try_mul
