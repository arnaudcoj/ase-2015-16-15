#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"

struct mbr_s mbr;
struct super_s super;

int
main(int argc, char **argv)
{
  int vol;

  printf("======Make New File System======\n");
  
  /* init master drive and load MBR */  
  init_master();

  load_mbr();

  vol = get_current_volume();

  init_super(vol);

  printf("Système de fichier initialisé avec succès\n");
  
  return EXIT_SUCCESS;
}
