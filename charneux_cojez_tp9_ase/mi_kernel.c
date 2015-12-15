#include "mi_kernel.h"
static int current_process;

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

int 
main(int argc, char **argv) 
{
  void *ptr;
  int res;

  /* init_hardware(); */
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  IRQVECTOR[16] = switch_to_process0;
  
  IRQVECTOR[17] = switch_to_process1;
  _mask(0x1001);

  ptr = virtual_memory;

  _int(16);
  memset(ptr, 1, PAGE_SIZE * N/2);
  _int(17);
  memset(ptr, 3, PAGE_SIZE * N/2);

  _int(16);
  res = sum(ptr);
  printf("Resultat du processus 0 : %d\n",res);
  _int(17);
  res = sum(ptr);
  printf("Resultat processus 1 : %d\n",res);
}
