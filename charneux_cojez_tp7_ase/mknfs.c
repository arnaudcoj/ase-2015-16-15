#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"

struct mbr_s mbr;

static void empty_it() {
  return;
}

int
main(int argc, char **argv)
{
  int i, s = 2, fc = 0, fs = 1;
  /* init master drive and load MBR */  
  init_master();
  
  /* Interrupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);
  chk_hda();

  load_mbr();

}
