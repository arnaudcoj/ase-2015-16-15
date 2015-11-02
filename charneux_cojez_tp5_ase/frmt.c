#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "config_hardware.h"
#include "hardware.h"
#include "drive.h"

static void empty_it(){
  return;
}

void frmt(){

  unsigned int c, s;
  c = s = 0;
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
  chk_hda();

  format_sector(0,0,1,0);
  /* and exit! */
  exit(EXIT_SUCCESS);
}
