# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

ROOTDIR=.

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic -m32
CFLAGS  += -g -pthread
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= mkhd dmps frmt
OBJECTS	= $(addsuffix .o,\
	  mkhd dmps frmt)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules 
###------------------------------------------------------------

mkhd.o: mkhd.c
	$(CC) $(CFLAGS) -c mkhd.c $(INCDIR)

mkhd: mkhd.o
	$(CC) $(CFLAGS) -o mkhd mkhd.o $(LIBS)

dmps.o: dmps.c
	$(CC) $(CFLAGS) -c dmps.c $(INCDIR)

dmps: dmps.o drive.o
	$(CC) $(CFLAGS) -o dmps dmps.o drive.o $(LIBS)

frmt.o: frmt.c
	$(CC) $(CFLAGS) -c frmt.c $(INCDIR)

frmt: frmt.o drive.o
	$(CC) $(CFLAGS) -o frmt frmt.o drive.o $(LIBS)

drive.o: drive.c
	$(CC) $(CFLAGS) -c drive.c $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
