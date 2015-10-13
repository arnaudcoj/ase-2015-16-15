#include "switch.h"

void init_ctx(struct ctx_s* ctx, int stack_size, func_t* f, void* args) {
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
  irq_disable();
  while(ctx->ctx_state == CTX_END || ctx->ctx_state == CTX_BLQ){
    if(ctx->ctx_state == CTX_END){
      if(current_ctx == ctx){
        asm("movl %0, %%esp" "\n" "movl %1, %%ebp"
        :
        : "r"(main_ctx->ctx_esp), "r"(main_ctx->ctx_ebp)
        :);
        return;
      } else {
        free(ctx->ctx_base);
        current_ctx -> ctx_next = ctx->ctx_next;
        free(ctx);
        ctx = current_ctx->ctx_next;
      }
    }
    else if(ctx->ctx_state == CTX_BLQ)
      ctx = ctx -> ctx_next;
  }
  irq_enable();

  if(current_ctx)
    asm("movl %%esp, %0" "\n" "movl %%ebp, %1"
	: "=r"(current_ctx->ctx_esp), "=r"(current_ctx->ctx_ebp)
	:
	:);
  else {
    main_ctx = malloc(sizeof(struct ctx_s));
    asm("movl %%esp, %0" "\n" "movl %%ebp, %1"
	: "=r"(main_ctx->ctx_esp), "=r"(main_ctx->ctx_ebp)
	:
	:);
  }
	
  irq_disable();
  current_ctx = ctx;

  asm("movl %0, %%esp" "\n" "movl %1, %%ebp"
      :
      : "r"(current_ctx->ctx_esp), "r"(current_ctx->ctx_ebp)
      :);
  irq_enable();
  if(current_ctx->ctx_state == CTX_INIT)
    start_current_ctx();
}

static void yield(){

  if(current_ctx)
    switch_to_ctx(current_ctx->ctx_next);
  else if(ring_ctx)
    switch_to_ctx(ring_ctx);
  else
    return;
}

void create_ctx(int stack_size, func_t* f, void* args){
  struct ctx_s * new = malloc(sizeof(struct ctx_s));
  init_ctx(new, stack_size, f, args);
  if(ring_ctx){
    new->ctx_next = ring_ctx->ctx_next;
    ring_ctx->ctx_next = new;  
  } else {
    new->ctx_next = new;
    ring_ctx = new;
  }
}

void start_sched(){
  setup_irq(TIMER_IRQ, yield);
  start_hw();
  yield();
}


static void start_current_ctx (void) {
  current_ctx->ctx_state = CTX_EXEC;
  current_ctx->ctx_f(current_ctx->ctx_args);
  current_ctx->ctx_state = CTX_END;
  yield();
  exit(EXIT_SUCCESS);
}

void sem_init(struct sem_s * sem, unsigned int val){
  sem -> sem_cpt = val;
  sem -> sem_first_ctx = NULL;
}
void sem_down(struct sem_s * sem){
  irq_disable();
  sem -> sem_cpt --;
  if(sem -> sem_cpt < 0){
    current_ctx -> ctx_state = CTX_BLQ;
    current_ctx -> ctx_next_same_sem = sem -> sem_first_ctx;
    sem -> sem_first_ctx = current_ctx;
    irq_enable();
    yield();
  } else {
    irq_enable();
  }
}
void sem_up(struct sem_s * sem){
  irq_disable();
  sem->sem_cpt ++;
  if(sem -> sem_cpt <= 0){
    struct ctx_s *c = sem->sem_first_ctx;
    c->ctx_state = CTX_EXEC;
    sem -> sem_first_ctx = c -> ctx_next_same_sem;
  }
  irq_enable();
}


