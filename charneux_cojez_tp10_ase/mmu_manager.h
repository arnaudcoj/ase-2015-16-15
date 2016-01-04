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

struct pmapping_s {
	unsigned pm_vpage : 12;
	unsigned pm_allocated : 1;
};

struct vmapping_s {
	unsigned vm_ppage : 8;
	unsigned vm_allocated : 1;
};


struct tlbe_s tlbe;

/* for mmu_handler1 */
int current_vpage = -1;

/* for mmu_handler2 */
int rr_ppage = 1;
struct pmapping_s pm_mapping[PM_PAGES];
struct vmapping_s vm_mapping[VM_PAGES];

extern void user_process();

#endif
