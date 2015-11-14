#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "vol.h"

struct mbr_s mbr;
struct super_s super;

int
main(int argc, char **argv)
{
  int i, vol;
  unsigned int bloc, rn, max_blocs;

  printf("======Test Free Bloc Library======\n");
  
  srand(time(NULL));
  
  /* init master drive and load MBR */  
  init_master();

  load_mbr();

  vol = get_current_volume();

  init_super(vol);

  max_blocs = get_n_free_blocs();
  
  printf("* fait appel à la fonction new_bloc() jusqu’à ce qu’elle retourne une erreur\n");

  while((bloc = new_bloc()) != NULL_BLOC)
    printf("got bloc n°%d\n", bloc);

  printf("* vérifie que le disque est plein\n");
  
  if(get_n_free_blocs())
    printf("disk is not full\n");
  else
    printf("disk is full\n");

  printf("* itère un nombre aléatoire de fois sur la libération d’un bloc free_bloc()\n");
  rn = rand() % max_blocs +1;

  while(rn) {
    free_bloc(rn);
    printf("bloc n°%d freed\n", rn);
    rn--;
  }

  printf("* affiche le statut du disque (taille libre)\n");

  printf("%d free blocs\n", get_n_free_blocs());

  printf("* alloue des blocs tant que le disque est non plein et retourne le nombre de blocs ayant pu être alloués\n");
  
  i = 0;
  while(get_n_free_blocs() > 0) {
    bloc = new_bloc();
    printf("got bloc n°%d\n", bloc);
    i++;
    }

  save_super();
  printf("Retourne %d\n", i);
  return i;
}
