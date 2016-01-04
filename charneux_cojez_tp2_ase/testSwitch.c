#include <stdio.h>
#include <stdlib.h>

#include "switch.h"

struct ctx_s ctx1;
struct ctx_s ctx2;
struct ctx_s ctx3;

void f1(void *arg);
void f2(void *arg);
void f3(void *arg);

int main(int argc, char *argv[])
{
  init_ctx(&ctx1, 16384, f1, NULL);
  printf("initialisation ctx1\n");
  init_ctx(&ctx2, 16384, f2, NULL);
  printf("initialisation ctx2\n");
  init_ctx(&ctx3, 16384, f3, NULL);
  printf("initialisation ctx3\n");
  
  printf("switch to ctx1\n");
  switch_to_ctx(&ctx1);
  printf("retour au main\n");
  exit(EXIT_SUCCESS);
}

void f1(void *args)
{
  printf("Entrée dans le ctx1\n") ;
  printf("switch to ctx2\n");
  switch_to_ctx(&ctx2);
  printf("Retour dans ctx1\n") ;
  printf("switch to ctx3\n");
  switch_to_ctx(&ctx3);
  printf("fin ctx1 \n");
}

void f2(void *args)
{
    printf("Entrée dans ctx2\n") ;
    printf("switch to ctx1\n");
    switch_to_ctx(&ctx1);
    printf("fin ctx2 \n");
} 


void f3(void *args)
{
    printf("Entrée dans ctx3\n") ;
    printf("fin ctx\n");
} 
