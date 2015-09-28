#include "try.h"

void kill_the_segfault(void) {
  wait(0);
  return;
}

int try (struct ctx_s *pctx, func_t *f, int arg) {  
  asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
       : "=r"(pctx->ctx_ebp), "=r"(pctx->ctx_esp)
       :
       :);
  
  return f(arg);
}


int throw (struct ctx_s *pctx, int val) {
  static int throw_val;
  throw_val = val;

  kill_the_segfault();

  asm ("movl %0, %%ebp" "\n\t" "movl %1, %%esp" 
       :
       : "r"(pctx->ctx_ebp),"r"(pctx->ctx_esp)
       :);

  return throw_val;
}

