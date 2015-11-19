#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"

struct mbr_s mbr;
struct super_s super;

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

int
main(int argc, char **argv)
{
  printf("======Display Volume======\n");

  /* init master drive and load MBR */  
  init_master();
  
  load_mbr();
  
  list();
  
  return EXIT_SUCCESS;
}
