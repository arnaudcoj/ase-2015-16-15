#include <stdio.h>
#include <stdlib.h>

#include "switch.h"

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;

void f_ping(void *arg);
void f_pong(void *arg);

int main(int argc, char *argv[])
{
  create_ctx(16384, f_ping, NULL);
  create_ctx(16384, f_pong, NULL);

  yield();

  exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
  int i = 100;
  while(i--) {
    printf("A") ;
    yield();
    printf("B") ;
    yield();
    printf("C") ;
    yield();
  }
}

void f_pong(void *args)
{
  int i = 10;
  while(i--) {
    printf("1") ;
    yield();
    printf("2") ;
    yield();
  }
} 
