#include "mmu_manager.h"

static void mmu_handler(void) {
  unsigned int vaddr = _in(MMU_FAULT_ADDR);
  unsigned int vpage = (vaddr >> 12) & 0xfff;
  struct tlbe_s tlbe;
  int ppage = 1;
  
  if(ppage == -1) {
    fprintf(stderr, "Erreur de segmentation, adresse : %p\n", (void*) _in(MMU_FAULT_ADDR));
    exit(EXIT_FAILURE);
  }
  
  if(current_vpage != -1) {
  
  store_to_swap(current_vpage, ppage);
  tlbe.tlb_ppage = 1;
  _out(TLB_DEL_ENTRY, *(int*) (&tlbe));

  fetch_from_swap(vpage, ppage);
  }
  
  tlbe.tlb_ppage = ppage;
  tlbe.tlb_vpage = vpage;
  tlbe.tlb_acces = 0x7;
  tlbe.tlb_valid = 0x1;

  _out(TLB_ADD_ENTRY, *(int*) (&tlbe)); 

  current_vpage = vpage;

  return;
  }

static void init_kernel(void) {
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }
  
  if(init_swap("swap_file") == -1) {
    fprintf(stderr, "Error in swap initialization\n");
    exit(EXIT_FAILURE);
  }
  
  IRQVECTOR[MMU_IRQ] = mmu_handler;

  _mask(0x1001);
}

int main(int argc, char **argv) {
  init_kernel();
  user_process();

  return EXIT_SUCCESS;
}

