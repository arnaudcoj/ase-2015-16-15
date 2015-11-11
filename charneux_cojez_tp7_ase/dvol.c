#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"

struct mbr_s mbr;

static void
list()
{
  int i;
  struct vol_s vol;
  printf("Il y a %d partition(s)\n", mbr.mbr_n_vol);
  for(i = 0; i< mbr.mbr_n_vol; i++){
    vol = mbr.mbr_vol[i];
    printf("vol n°%d, commence (%d,%d) volume : %d\n", i, vol.vol_first_cylinder, vol.vol_first_sector, vol.vol_n_bloc);
  }
}

static void empty_it() {
  return;
}

int
main(int argc, char **argv)
{
  int i;
  /* init master drive and load MBR */  
  init_master();
  
  /* Interrupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);
  chk_hda();

  load_mbr();
  list();
  
  /* make gcc -W happy */
  exit(EXIT_SUCCESS);
}
