#ifndef CONFIG_HARDWARE_H
#define CONFIG_HARDWARE_H

#define HDA_DATAREGS 0x110
#define HDA_CMDREG 0x3F6
#define HDA_IRQ 14
#define HDA_SECTORSIZE 128
#define HDA_MAXCYLINDER 16
#define HDA_MAXSECTOR 16
#define PAGE_SIZE 4096
#define VM_PAGES 4096
#define VM_SIZE VM_PAGES*PAGE_SIZE
#define PM_PAGES 256
#define PM_SIZE PM_PAGES*PAGE_SIZE
#define N 512
#define MMU_ENABLE 1
#define MMU_IRQ 13
#define MMU_FAULT_ADDR 0xCD
#define TLB_ADD_ENTRY 0xCE























#endif
