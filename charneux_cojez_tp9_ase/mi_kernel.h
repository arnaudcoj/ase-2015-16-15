#ifndef MI_KERNEL_H
#define MI_KERNEL_H

#include "config_hardware.h"
#include "mi_user.h"
#include <hardware.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned current_ctx;

struct tlbe_s {
  unsigned int tlb_rfu:8;
  unsigned int tlb_vpage:12;
  unsigned int tlb_ppage:8;
  unsigned int tlb_acces:3;
  unsigned int tlb_valid:1;
};

void mmu_handler(void);

#endif //MI_KERNEL_H
