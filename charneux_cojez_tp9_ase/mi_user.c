#include "mi_user.h"

int 
sum(void *ptr) 
{
  int i;
  int sum = 0;
    
  for(i = 0; i < PAGE_SIZE * N/2 ; i++)
    sum += ((char*)ptr)[i];
  return sum;
}

void init_user(void) {
  void *ptr;
  int r0, r1;
  
  ptr = virtual_memory;

  _int(SYSCALL_SWTCH_0);
  printf("Remplissage des pages de mémoire du processus 0 avec 1.\n");
  memset(ptr, 1, PAGE_SIZE * N/2);

  _int(SYSCALL_SWTCH_1);
  printf("Remplissage des pages de mémoire du processus 1 avec 3.\n");
  memset(ptr, 3, PAGE_SIZE * N/2);

  _int(SYSCALL_SWTCH_0);
  r0 = sum(ptr);
  printf("Resultat (somme des valeurs en mémoire) du processus 0 : %d\n",r0);
  
  _int(SYSCALL_SWTCH_1);
  r1 = sum(ptr);
  printf("Resultat (somme des valeurs en mémoire)  du processus 1 : %d\n",r1);

  if(r0 * 3 == r1)
    printf("%u * 3 == %u \n", r0, r1);
  else
    printf("%u * 3 != %u \n", r0, r1);
  
}
