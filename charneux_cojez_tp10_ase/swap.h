#ifndef SWAP_H
#define SWAP_H

#include <stdio.h>
#include <hardware.h>
#include "hw_config.h"

static FILE *swap_file;

char init_swap(const char *path);
char store_to_swap(int vpage, int ppage);
char fetch_from_swap(int vpage, int ppage);

#endif
