#ifndef MMU_MANAGER_H
#define MMU_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hardware.h>
#include "hw_config.h"
#include "swap.c"

struct tlbe_s {
  unsigned int tlb_rfu:8;
  unsigned int tlb_vpage:12;
  unsigned int tlb_ppage:8;
  unsigned int tlb_acces:3;
  unsigned int tlb_valid:1;
};

struct tlbe_s tlbe;
int current_vpage = -1;

extern void user_process();

#endif
