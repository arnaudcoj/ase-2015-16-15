#include "switch.h"

int init_ctx(struct ctx_s* ctx, int stack_size, func_t* f, void* args) {
  ctx->ctx_base = malloc(stack_size);
  ctx->ctx_esp = ctx->ctx_base + stack_size - (sizeof(int));
  ctx->ctx_ebp = ctx->ctx_esp;
  ctx->ctx_state = CTX_INIT;
  ctx->ctx_f = f;
  ctx->ctx_args = args;
  ctx->ctx_magic = CTX_MAGIC;
}

void switch_to_ctx (struct ctx_s* ctx) {
  assert(ctx->ctx_magic == CTX_MAGIC);
  assert(ctx->ctx_state == CTX_INIT || ctx->ctx_state == CTX_EXEC);

  if(current_ctx)
    asm("movl %%esp, %0" "\n" "movl %%ebp, %1"
	: "=r"(current_ctx->ctx_esp), "=r"(current_ctx->ctx_ebp)
	:
	:);

  
  current_ctx = ctx;

  asm("movl %0, %%esp" "\n" "movl %1, %%ebp"
      :
      : "r"(current_ctx->ctx_esp), "r"(current_ctx->ctx_ebp)
      :);
  if(current_ctx->ctx_state == CTX_INIT)
    start_current_ctx();
}

static void start_current_ctx (void) {
  current_ctx->ctx_state = CTX_EXEC;
  current_ctx->ctx_f(current_ctx->ctx_args);
  current_ctx->ctx_state = CTX_END;

  printf("\nIT'S WORKING !\n");
  exit(EXIT_SUCCESS);
}
