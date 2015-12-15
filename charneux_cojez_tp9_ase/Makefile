# $Id: Makefile,v 1.2 2009/11/17 10:02:37 marquet Exp $
##############################################################################

ROOTDIR=./

CC	=  gcc
CFLAGS	=  -Wall -Werror -ansi -pedantic -m32
CFLAGS  += -std=iso9899:1999
CFLAGS  += -g
LIBDIR  =  $(ROOTDIR)/lib
INCDIR  =  $(ROOTDIR)/include
CFLAGS  += -I$(INCDIR)
LIBS    = -lhardware

###------------------------------
### Main targets
###------------------------------------------------------------
BINARIES= mi_kernel 
OBJECTS	= $(addsuffix .o,\
	  mi_kernel mi_user)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Binaries
###------------------------------------------------------------
mi_kernel : $(OBJECTS)

% : %.o
	$(CC) -m32 -lpthread -o $@ $^ -L$(LIBDIR) $(LIBS)

###------------------------------
### #include dependences
###------------------------------------------------------------
# you may fill these lines with "make depend"

mi_kernel.o: mi_kernel.c
	$(CC) $(CFLAGS) -c $<
mi_user.o: mi_user.c
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean diskclean

diskclean:
	$(RM) vdiskA.bin vdiskB.bin
depend :
	$(CC) $(CFLAGS) -MM $(INCDIR) *.c
