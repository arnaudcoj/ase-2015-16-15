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
BINARIES= if_pfile if_nfile if_cfile if_dfile mkvol dvol mknfs dfs
OBJECTS	= $(addsuffix .o,\
	  tools ifile mount drive vol inode)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Binaries
###------------------------------------------------------------
if_cfile : if_cfile.o $(OBJECTS)
if_nfile : if_nfile.o $(OBJECTS)
if_dfile : if_dfile.o $(OBJECTS)
if_pfile : if_pfile.o $(OBJECTS)
mkvol : mkvol.o vol.o drive.o
dvol : dvol.o vol.o drive.o
mknfs : mknfs.o vol.o drive.o
dfs : dfs.o vol.o drive.o

% : %.o
	$(CC) -m32 -lpthread -o $@ $^ -L$(LIBDIR) $(LIBS)

###------------------------------
### #include dependences 
###------------------------------------------------------------
# you may fill these lines with "make depend"
if_cfile.o: if_cfile.c ifile.h inode.h tools.h mount.h
if_dfile.o: if_dfile.c ifile.h inode.h tools.h mount.h
if_nfile.o: if_nfile.c ifile.h inode.h tools.h mount.h
if_pfile.o: if_pfile.c ifile.h inode.h tools.h mount.h
ifile.o: ifile.c inode.h tools.h ifile.h 
mount.o: mount.c config.h tools.h 
tools.o: tools.c tools.h

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

