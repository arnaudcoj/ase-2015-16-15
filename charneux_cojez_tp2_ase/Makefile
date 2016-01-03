CC=gcc
CFLAGS=-m32

all:pingpong pingpongpang testSwitch

pingpong: switch.o pingpong.c  
	$(CC) $(CFLAGS) -o $@  $^

pingpongpang: switch.o pingpongpang.c  
	$(CC) $(CFLAGS) -o $@  $^
	
testSwitch: switch.o testSwitch.c  
	$(CC) $(CFLAGS) -o $@  $^

switch.o: switch.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *~ *.o pingpong pingpongpang
