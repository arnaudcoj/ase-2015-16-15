#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "switch.h"

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;

void f_ping(void *arg);
void f_pong(void *arg);

int main(int argc, char *argv[])
{
  create_ctx(16384, f_ping, NULL);
  create_ctx(16384, f_pong, NULL);
  start_sched();
  // le sleep sert a attendre 1 seconde, dans le cas contraire, l'application fini trop vite pour pouvoir réaliser le ping pong
  printf("\ntest retour au main\n");
  exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
  int i = 10000;
  while(i--){
    printf("A") ;
    printf("B") ;
    printf("C") ;
  }
}

void f_pong(void *args)
{
  int i = 10000;
  while(i--) {
    printf("1") ;
    printf("2") ;
  }
} 
