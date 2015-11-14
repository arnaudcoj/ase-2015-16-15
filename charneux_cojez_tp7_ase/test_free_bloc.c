#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
  unsigned int bloc, rn, max_blocs;
  
  srand(time(NULL));
  
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

  max_blocs = get_n_free_blocs();

  while((bloc = new_bloc()) != NULL_BLOC)
    printf("got bloc n°%d\n", bloc);

  if(get_n_free_blocs())
    printf("disk is not full\n");
  else
    printf("disk is full\n");

  rn = rand() % max_blocs;
  
  while(rn--) {
    free_bloc(rn);
    printf("bloc n°%d freed\n", rn);
  }

  printf("%d free blocs\n", get_n_free_blocs());

  i = 0;
  while(get_n_free_blocs()) {
    bloc = new_bloc();
    printf("got bloc n°%d\n", bloc);
    i++;
  }

  printf("Retourne %d\n", i);
  return i;
}
