#include "swap.h"

char init_swap(const char *path) {
  swap_file = fopen (path, "w+");
  if(swap_file == NULL)
    return -1;
  return 0;
}

char store_to_swap(int vpage, int ppage) {
  if(fseek(swap_file, vpage * PAGE_SIZE, SEEK_SET) == -1)
    return -1;
  if(fwrite( (void*) ( (int) physical_memory + ppage * PAGE_SIZE), 1, PAGE_SIZE, swap_file) == -1)
    return -1;
  return 0;
}
  
char fetch_from_swap(int vpage, int ppage) {
  if(fseek(swap_file, vpage * PAGE_SIZE, SEEK_SET) == -1)
    return -1;
  if(fread( (void*) ( (int) physical_memory + ppage * PAGE_SIZE), 1, PAGE_SIZE, swap_file) == -1)
    return -1;
  return 0;
}
