#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"

struct mbr_s mbr;

static void
create(int s, int fc, int fs)
{
  struct vol_s vol;
  vol.vol_first_cylinder = fc;
  vol.vol_first_sector = fs;
  vol.vol_n_bloc = s;
  vol.vol_type = VOL_TYPE_STD;
  mbr.mbr_vol[mbr.mbr_n_vol] = vol;
  mbr.mbr_n_vol ++;
}

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
  

  printf("Il y a %d partition(s)\n", mbr.mbr_n_vol);
  printf("Il y a %d magic(s)\n", mbr.mbr_magic);
  printf("Il y a %d magic(s)\n", MBR_MAGIC);
  create(s, fc, fs);
  printf("Il y a %d partition(s)\n", mbr.mbr_n_vol);
  printf("Il y a %d magic(s)\n", mbr.mbr_magic);
  printf("Il y a %d magic(s)\n", MBR_MAGIC);
  save_mbr();
  printf("Il y a %d partition(s)\n", mbr.mbr_n_vol);
  printf("Il y a %d magic(s)\n", mbr.mbr_magic);
  printf("Il y a %d magic(s)\n", MBR_MAGIC);
  exit(EXIT_SUCCESS);
}
