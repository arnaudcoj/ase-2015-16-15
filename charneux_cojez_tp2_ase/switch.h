#ifndef SWITCH_H
#define SWITCH_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CTX_MAGIC 0x2B00B1E5

typedef void (func_t) (void*);
enum ctx_state_e {CTX_INIT, CTX_EXEC, CTX_END};

struct ctx_s {
  char* ctx_base;
  void* ctx_esp;
  void* ctx_ebp;
  enum ctx_state_e ctx_state;
  func_t* ctx_f;
  void* ctx_args;
  unsigned int ctx_magic;
};


static struct ctx_s* current_ctx;

int init_ctx(struct ctx_s* ctx, int stack_size, func_t* f, void* args);
void switch_to_ctx (struct ctx_s* ctx);
static void start_current_ctx (void);
void free_ctx(struct ctx_s* ctx);

#endif //SWITCH_H
