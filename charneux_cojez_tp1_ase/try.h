#ifndef TRY_H
#define TRY_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef int (func_t)(int); /* a function that returns an int from an int */

struct ctx_s {
  void * ctx_esp;
  void * ctx_ebp;  
};

int try (struct ctx_s *pctx, func_t *f, int arg);
int throw (struct ctx_s *pctx, int val);

#endif //TRY_H
