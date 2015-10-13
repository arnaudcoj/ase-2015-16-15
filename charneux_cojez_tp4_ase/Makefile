CC=gcc
CFLAGS=-m32
EXEC=prod_cons
OBJ=switch.o hw.o

all: $(EXEC)

%: $(OBJ) %.c  
	$(CC) $(CFLAGS) -o $@  $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *~ *.o $(EXEC)
