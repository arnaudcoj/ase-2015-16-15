#include "mem.h"

static int ppage_of_vaddr(int process, unsigned int vaddr) {
  unsigned int ppage = -1;
  unsigned int vpage = (vaddr >> 12) & 0xfff;
  if((unsigned int) virtual_memory <= vaddr && vaddr < (unsigned int) virtual_memory + VM_SIZE && vpage < N/2) {
      if(current_ctx == 0)
        ppage = vpage +1;
      if(current_ctx ==1)
        ppage = vpage +1 + (N/2);
  }
  return ppage;
}

void mmu_handler(void) {
  unsigned int vaddr = _in(MMU_FAULT_ADDR);
  unsigned int vpage = (vaddr >> 12) & 0xfff;
  struct tlbe_s tlbe;
  int ppage = ppage_of_vaddr(current_ctx, vaddr);
  if(ppage == -1)
    return; /* pas sur */
  tlbe.tlb_ppage = ppage;
  tlbe.tlb_vpage = vpage;
  tlbe.tlb_acces = 0x7;
  tlbe.tlb_valid = 0x1;
  _out(TLB_ADD_ENTRY, *(int*) (&tlbe)); 
}
