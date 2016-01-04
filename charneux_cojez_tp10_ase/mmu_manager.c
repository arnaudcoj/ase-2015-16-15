#include "mmu_manager.h"


static void mmu_handler1(void) {
  unsigned int vaddr = _in(MMU_FAULT_ADDR);
  unsigned int vpage = (vaddr >> 12) & 0xfff;
  struct tlbe_s tlbe;
  int ppage = 1;
   
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

static void mmu_handler2(void) {
  unsigned int vaddr = _in(MMU_FAULT_ADDR);
  unsigned int vpage = (vaddr >> 12) & 0xfff;
  
  if(vm_mapping[vpage].vm_allocated) { 
    tlbe.tlb_vpage = vpage;	
    tlbe.tlb_ppage = vm_mapping[vpage].vm_ppage;
    tlbe.tlb_acces = 0x7;
    tlbe.tlb_valid = 0x1;

    _out(TLB_ADD_ENTRY, *(int*)&tlbe);

  } else {
    
    if(pm_mapping[rr_ppage].pm_allocated) {
      store_to_swap(pm_mapping[rr_ppage].pm_vpage, rr_ppage);
      tlbe.tlb_ppage = rr_ppage;
      _out(TLB_DEL_ENTRY, *(int*) (&tlbe));

      pm_mapping[rr_ppage].pm_allocated = 0;
      vm_mapping[pm_mapping[rr_ppage].pm_vpage].vm_allocated = 0;
    
      if(fetch_from_swap(vpage, rr_ppage))
	fprintf(stderr, "no information to fetch\n");
    }
  
    tlbe.tlb_ppage = rr_ppage;
    tlbe.tlb_vpage = vpage;
    tlbe.tlb_acces = 0x7;
    tlbe.tlb_valid = 0x1;

    _out(TLB_ADD_ENTRY, *(int*) (&tlbe)); 

    vm_mapping[vpage].vm_ppage = rr_ppage;
    vm_mapping[vpage].vm_allocated = 1;
    pm_mapping[rr_ppage].pm_vpage = vpage;
    pm_mapping[rr_ppage].pm_allocated = 1;
  
    rr_ppage++;
    if(rr_ppage >= PM_PAGES)
      rr_ppage = 1;
  }
  return;  
}

static void init_pm_map(struct pmapping_s pm_map[], int map_length) {
  int i;
  
  for(i = 0; i < map_length; i++)
    pm_map[i].pm_allocated = 0;

  return;
}

static void init_vm_map(struct vmapping_s vm_map[], int map_length) {
  int i;
  
  for(i = 0; i < map_length; i++)
    vm_map[i].vm_allocated = 0;

  return;
}

static void init_kernel(int handler) {
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }
  
  if(init_swap("swap_file") == -1) {
    fprintf(stderr, "Error in swap initialization\n");
    exit(EXIT_FAILURE);
  }

  if(handler == MMU_HANDLER_SIMPLE)
    IRQVECTOR[MMU_IRQ] = mmu_handler1;
  else if(handler == MMU_HANDLER_COMPLETE)
    IRQVECTOR[MMU_IRQ] = mmu_handler2;

  init_vm_map(vm_mapping, VM_PAGES);
  init_pm_map(pm_mapping, PM_PAGES);
  
  _mask(0x1001);

  return;
}

static void usage(void) {
  fprintf(stderr, "usage : ./mmu_manager <handler> <operation>\n\thandler :\n\t\t 0. 1 page (defaut)\n\t\t 1. Toute la memoire\n \toperation :\n\t\t 0. addition (defaut)\n\t\t 1. multiplication\n");
}

int main(int argc, char **argv) {
  /* Par défaut handler avec 1 page et operation = addition */
  int handler = 0;
  int operation = 0;
  int arg1, arg2;

  if(argc == 3) {
    arg1 = atoi(argv[1]);
    if(arg1 == MMU_HANDLER_SIMPLE || arg1 == MMU_HANDLER_COMPLETE) {
      handler = arg1;

      arg2 = atoi(argv[2]);
      if(arg2 == MATRIX_ADD || arg2 == MATRIX_MUL)
	operation = arg2;
      else
	usage();
    }
    else
      usage();
  }
  else 
    usage();
    
  init_kernel(handler);
  user_process(operation);

  return EXIT_SUCCESS;
}

