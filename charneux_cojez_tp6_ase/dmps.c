#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "config_hardware.h"
#include "hardware.h"
#include "drive.h"

void dump(unsigned char *buffer, unsigned int buffer_size, int ascii_dump, int octal_dump){
    int i,j;
    
    for (i=0; i<buffer_size; i+=16) {
	/* offset */
	printf("%.8o",i);

	/* octal dump */
	if (octal_dump) {
	    for(j=0; j<8; j++)
		printf(" %.2x", buffer[i+j]);
	    printf(" - ");
	    
	    for( ; j<16; j++)
		printf(" %.2x", buffer[i+j]);
	    
	    printf("\n");
	}
	/* ascii dump */
	if (ascii_dump) {
	    printf("%8c", ' ');
	    
	    for(j=0; j<8; j++)
		printf(" %1c ", isprint(buffer[i+j])?buffer[i+j]:' ');
	    printf(" - ");
	    
	    for( ; j<16; j++)
		printf(" %1c ", isprint(buffer[i+j])?buffer[i+j]:' ');
	    
	    printf("\n");
	}
	
    }
}

static void empty_it(){
  return;
}

void dmps(){
  unsigned int c, s;
  c = s = 0;
  _out(HDA_DATAREGS, (c>>8) & 0xFF);
  _out(HDA_DATAREGS +1, c & 0xFF);
  _out(HDA_DATAREGS +2, (s>>8) & 0xFF);
  _out(HDA_DATAREGS +3, s & 0xFF);
  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);
  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS+1, 1);
  _out(HDA_CMDREG, CMD_READ);
  _sleep(HDA_IRQ);
  dump(MASTERBUFFER, SECTORSIZE, 1, 1);
  
}

int main(int argc, char **argv){
  unsigned int i;
  unsigned char buff[SECTORSIZE];
  unsigned int c, s;
  c = s = 0;
  
  /* init hardware */
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  /* Interreupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);
  chk_hda();

  /* Processing parameters */
  if(argc == 3) {
    c = atoi(argv[1]);
    s = atoi(argv[2]);
  } else {
    printf("no parameter given, assuming cylinder 0 & sector 0\n");
  }

  read_sector(c,s,buff);
  
  dump(buff, SECTORSIZE, 1, 1);

  /* and exit! */
  exit(EXIT_SUCCESS);
}
