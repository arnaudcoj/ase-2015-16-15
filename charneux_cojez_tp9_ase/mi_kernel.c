#include "mi_kernel.h"

static void 
switch_to_process0(void) 
{
  current_process = 0;
  _out(MMU_CMD, MMU_RESET);
}

static void
switch_to_process1(void) 
{
  current_process = 1;
  _out(MMU_CMD, MMU_RESET);
}

static int ppage_of_vaddr(int process, unsigned int vaddr) {
  unsigned int ppage = -1;
  unsigned int vpage = (vaddr >> 12) & 0xfff;
  if((unsigned int) virtual_memory <= vaddr && vaddr < (unsigned int) virtual_memory + VM_SIZE && vpage < N/2) {
    if(current_process == 0)
      ppage = vpage +1;
    if(current_process ==1)
      ppage = vpage +1 + (N/2);
  }
  return ppage;
}

static void mmu_handler(void) {
  unsigned int vaddr = _in(MMU_FAULT_ADDR);
  unsigned int vpage = (vaddr >> 12) & 0xfff;
  struct tlbe_s tlbe;
  int ppage = ppage_of_vaddr(current_process, vaddr);
  if(ppage == -1) {
    fprintf(stderr, "Erreur de segmentation, adresse : %p\n", (void*) _in(MMU_FAULT_ADDR));
    exit(EXIT_FAILURE); /* pas sur */
  }
  tlbe.tlb_ppage = ppage;
  tlbe.tlb_vpage = vpage;
  tlbe.tlb_acces = 0x7;
  tlbe.tlb_valid = 0x1;
  _out(TLB_ADD_ENTRY, *(int*) (&tlbe)); 
}


void init_kernel(void) {
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }
  
  IRQVECTOR[MMU_IRQ] = mmu_handler;
  IRQVECTOR[SYSCALL_SWTCH_0] = switch_to_process0;
  IRQVECTOR[SYSCALL_SWTCH_1] = switch_to_process1;

  _mask(0x1001);
}

int 
main(int argc, char **argv) 
{
  init_kernel();
  init_user();
}
