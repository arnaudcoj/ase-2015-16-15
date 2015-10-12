#ifndef SWITCH_H
#define SWITCH_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hw.h"

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
  struct ctx_s * ctx_next;
};


static struct ctx_s* current_ctx = (struct ctx_s *) 0;
static struct ctx_s* ring_ctx = (struct ctx_s *) 0;
static struct ctx_s* main_ctx = (struct ctx_s *) 0;

static void init_ctx(struct ctx_s* ctx, int stack_size, func_t* f, void* args);
static void switch_to_ctx (struct ctx_s* ctx);
static void start_current_ctx (void);
static void yield();
void create_ctx(int stack_size, func_t* f, void* args);
void start_sched();

#endif //SWITCH_H
