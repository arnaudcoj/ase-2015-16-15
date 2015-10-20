/* ------------------------------
   $Id: mkhd.c,v 1.4 2004/10/12 09:16:57 marquet Exp $
   ------------------------------------------------------------

   Create and intialize a drive using the hardware simulator.
   Philippe Marquet, october 2002

   A minimal example of a program using the ATA interface.
   It is given to the students as such.
   
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "config_hardware.h"
#include "hardware.h"
#define SECTORSIZE 1024

unsigned int c, s;

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
  _out(HDA_DATAREGS, (c>>8) & 0xFF);
  _out(HDA_DATAREGS +1, c & 0xFF);
  _out(HDA_DATAREGS +2, (s>>8) & 0xFF);
  _out(HDA_DATAREGS +3, s & 0xFF);
  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);
  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS, 1);
  _out(HDA_CMDREG, CMD_READ);
  _sleep(HDA_IRQ);
}

void dummy(){}

int chk_hda(){
  int sectorsize;
  _out(HDA_CMDREG, CMD_DSKINFO);
  sectorsize = _in(HDA_SECTORSIZE);
  return SECTORSIZE == sectorsize;
}

int main(int argc, char **argv){
  unsigned int i;
    
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
  if(!chk_hda())
    exit(EXIT_FAILURE);

  dmps();
  
  /* and exit! */
  exit(EXIT_SUCCESS);
}
