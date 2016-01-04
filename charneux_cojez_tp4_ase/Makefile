CC=gcc
CFLAGS=-m32
EXEC=prod_cons testSuccess testFailure
OBJ=switch.o hw.o

all: $(EXEC)

prod_cons: $(OBJ) prod_cons.c  
	$(CC) $(CFLAGS) -o $@ $^

testSuccess: $(OBJ) testSuccess.c  
	$(CC) $(CFLAGS) -o $@ $^

testFailure: $(OBJ) testFailure.c  
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *~ *.o *# $(EXEC)
