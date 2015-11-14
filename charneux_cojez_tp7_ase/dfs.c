#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"

struct mbr_s mbr;
struct super_s super;

void print_super(void) {
  printf("Volume %d\n  Number of free blocs : %d\n  First free bloc's number : %d\n", super.super_vol, super.super_n_free, super.super_first_free);
}

int
main(int argc, char **argv)
{
  int vol;

  printf("======Display File System======\n");
  
  /* init master drive and load MBR */  
  init_master();

  load_mbr();

  vol = get_current_volume();

  load_super(vol);

  print_super();

  return EXIT_SUCCESS;
}

