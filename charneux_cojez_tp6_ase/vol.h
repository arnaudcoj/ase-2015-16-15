#ifndef VOL_H
#define VOL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "config_hardware.h"
#include "hardware.h"
#include "drive.h"

#define SECTORSIZE 256
#define MBR_MAGIC 0xABCDDCBA
#define MAXVOL 5

enum vol_type_e { VOL_TYPE_STD, VOL_TYPE_ANX, VOL_TYPE_OTHER };

struct  vol_s {
  unsigned int vol_first_sector;
  unsigned int vol_first_cylinder;
  unsigned int vol_n_bloc;
  enum vol_type_e vol_type;
};

struct mbr_s {
  struct vol_s mbr_vol[MAXVOL];
  unsigned int mbr_n_vol;
  unsigned int mbr_magic;
};

static struct mbr_s mbr;

void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer);
void write_bloc(unsigned int vol, unsigned int nbloc, const unsigned char *buffer);
void format_vol(unsigned int vol);
int load_mbr();
void save_mbr();

#endif
