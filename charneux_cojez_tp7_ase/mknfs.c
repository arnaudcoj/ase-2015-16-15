#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"

struct mbr_s mbr;
struct super_s super;


static void empty_it() {
  return;
}

int
main(int argc, char **argv)
{
  int i, vol;

  /* init master drive and load MBR */  
  init_master();

  /* Interrupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);
  chk_hda();

  load_mbr();

  vol = get_current_volume();

  init_super(vol);

  return EXIT_SUCCESS;
}
