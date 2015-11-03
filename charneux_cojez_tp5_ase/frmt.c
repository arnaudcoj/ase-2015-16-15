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

void frmt(void){
  
  unsigned int ncyl, nsect, i;
  ncyl = nsect = 0;
  _out(HDA_CMDREG, CMD_DSKINFO);
  ncyl = (_in(HDA_DATAREGS) << 8) +  _in(HDA_DATAREGS +1);
  nsect = (_in(HDA_DATAREGS + 2) << 8) +  _in(HDA_DATAREGS +3);

  for(i = 0; i < ncyl; i++)
    format_sector(i, 0, nsect, 0);
}

int main(int argc, char **argv){
  unsigned int i;
  
  /* init hardware */
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  /* Interrupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);
  chk_hda();

  frmt();
  
  /* and exit! */
  exit(EXIT_SUCCESS);
}
