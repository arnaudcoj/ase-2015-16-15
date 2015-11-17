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
#define NULL_BLOC 0
#define SUPER_BLOC 0
#define SUPER_MAGIC 0xDEADBEEF

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

struct super_s {
  unsigned int super_first_free;
  unsigned int super_n_free;
  unsigned int super_magic;
  unsigned int super_vol;
};

struct free_bloc_s {
  unsigned int free_bloc_size;
  unsigned int free_bloc_next;
};

extern struct mbr_s mbr;
extern struct super_s super;
extern unsigned int current_volume;

void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer);
void write_bloc(unsigned int vol, unsigned int nbloc, const unsigned char *buffer);
void format_blocs(unsigned int vol, unsigned int bloc, unsigned int nblocs, unsigned int val);
void format_vol(unsigned int vol);
int load_mbr(void);
void save_mbr(void);
void init_super(unsigned int vol);
unsigned int load_super(unsigned int vol);
void save_super(void);
unsigned int new_bloc(void);
unsigned int new_bloc_zero(void);
void free_bloc(unsigned int bloc);
unsigned int get_current_volume(void);
unsigned int get_n_free_blocs(void);
void read_bloc_n(unsigned int vol, unsigned int nbloc, unsigned char *buffer, unsigned int n);
void write_bloc_n(unsigned int vol, unsigned int nbloc, const unsigned char *buffer, unsigned int n);
#endif
