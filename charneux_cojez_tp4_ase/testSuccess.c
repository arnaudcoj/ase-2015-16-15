#include "switch.h"
#define N 1                       /* nombre de places dans le tampon */

struct sem_s mutex, vide, plein;
int cpt = 0;

void producteur (void * args);
void consommateur (void * args);
void produire_objet(void);
void utiliser_objet(void);

int main(void){
  sem_init(&mutex, 1);                /* controle d'acces au tampon */
  sem_init(&vide, N);                 /* nb de places libres */
  sem_init(&plein, 0);                /* nb de places occupees */
  create_ctx(16384, producteur, NULL);
  create_ctx(16384, consommateur, NULL);
  start_sched();
  printf("\ntest retour au main\n");

return EXIT_SUCCESS;
}

void producteur (void * args)
{
  int i = 3;
  while (i--) {
    sem_down(&vide);                  /* dec. nb places libres */
    sem_down(&mutex);                 /* entree en section critique */
   // mettre_objet();              /* mettre l'objet dans le tampon */
    produire_objet();           /* produire l'objet suivant */
    sem_up(&mutex);                   /* sortie de section critique */
    sem_up(&plein);                   /* inc. nb place occupees */
  }
}

void consommateur (void * args)
{
  int i = 2;
  while (i--) {
    sem_down(&plein);                 /* dec. nb emplacements occupes */
    sem_down(&mutex);                 /* entree section critique */
   // retirer_objet ();           /* retire un objet du tampon */
    utiliser_objet();            /* utiliser l'objet */
    sem_up(&mutex);                   /* sortie de la section critique */
    sem_up(&vide);                    /* inc. nb emplacements libres */
  }
}

void produire_objet(void){
  printf("production\n");
  printf("tampon : %i/%i\n", cpt, N);
  cpt ++;
  printf("tampon : %i/%i\n", cpt, N);
}

void utiliser_objet(void){
  printf("consommation\n");
  printf("tampon : %i/%i\n", cpt, N);
  cpt--;
  printf("tampon : %i/%i\n", cpt, N);
}
