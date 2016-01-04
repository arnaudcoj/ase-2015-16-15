CC=gcc
CFLAGS=-m32

all:pingpong pingpongpang

pingpong: switch.o hw.o pingpong.c  
	$(CC) $(CFLAGS) -o $@  $^

pingpongpang: switch.o hw.o pingpongpang.c  
	$(CC) $(CFLAGS) -o $@  $^

switch.o: switch.c
	$(CC) $(CFLAGS) -c $^

hw.o: hw.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *~ *.o pingpong pingpongpang
