#include "vol.h"

struct mbr_s mbr;

int cylinder_of_bloc(unsigned int vol, unsigned int bloc) { 
  return mbr.mbr_vol[vol].vol_first_cylinder + (mbr.mbr_vol[vol].vol_first_sector + bloc) / HDA_MAXSECTOR;
}

int sector_of_bloc(unsigned int vol, unsigned int bloc) {
  return (mbr.mbr_vol[vol].vol_first_sector + bloc) % HDA_MAXSECTOR;
}

void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer) {
  unsigned int c, s;
  assert(vol < MAXVOL);
  assert(nbloc < mbr.mbr_vol[vol].vol_n_bloc);
  c = cylinder_of_bloc(vol, nbloc);
  s = sector_of_bloc(vol, nbloc);
  
  read_sector(c, s, buffer);
}

void read_bloc_n(unsigned int vol, unsigned int nbloc, unsigned char *buffer, unsigned int n) {
  unsigned int c, s;
  assert(vol < MAXVOL);
  assert(nbloc < mbr.mbr_vol[vol].vol_n_bloc);
  c = cylinder_of_bloc(vol, nbloc);
  s = sector_of_bloc(vol, nbloc);
  
  read_sector_n(c, s, buffer, n);
}

void write_bloc(unsigned int vol, unsigned int nbloc, const unsigned char *buffer) {
  unsigned int c, s;
  assert(vol < MAXVOL);
  assert(nbloc < mbr.mbr_vol[vol].vol_n_bloc);
  c = cylinder_of_bloc(vol, nbloc);
  s = sector_of_bloc(vol, nbloc);
  
  write_sector(c, s, buffer);
}

void write_bloc_n(unsigned int vol, unsigned int nbloc, const unsigned char *buffer, unsigned int n) {
  unsigned int c, s;
  assert(vol < MAXVOL);
  assert(nbloc < mbr.mbr_vol[vol].vol_n_bloc);
  c = cylinder_of_bloc(vol, nbloc);
  s = sector_of_bloc(vol, nbloc);
  
  write_sector_n(c, s, buffer, n);
}

void format_vol(unsigned int vol) {
  unsigned int c, s;
  assert(vol < MAXVOL);
  c = cylinder_of_bloc(vol, 0);
  s = sector_of_bloc(vol, 0);
  format_sector(c, s, mbr.mbr_vol[vol].vol_n_bloc, 0);
  
}

int load_mbr() {
  assert(SECTORSIZE >= sizeof (struct mbr_s));
  read_sector_n(0, 0, (unsigned char*) &mbr, sizeof mbr);
  if(mbr.mbr_magic != MBR_MAGIC) {
    mbr.mbr_n_vol = 0;
    mbr.mbr_magic = MBR_MAGIC;
    printf("entré dans if de load_mbr()\n");
    return 0;
  }
  return 1;
}

void save_mbr() {
  unsigned char buffer[SECTORSIZE];
  memcpy(buffer, (unsigned char*) &mbr, sizeof mbr);
  write_sector(0,0, buffer);
}


void init_super(unsigned int vol) {
  /*char *current_vol_str;
  int current_vol;
  current_vol_str = getenv("$CURRENT_VOLUME");
  assert(current_vol_str);

  current_vol = atoi(current_vol_str);*/
  
  struct free_bloc_s fb;
  super.super_first_free = 1;
  super.super_n_free = mbr.mbr_vol[vol].vol_n_bloc -1;
  super.super_magic = SUPER_MAGIC;
  super.super_vol = vol;
  
  write_bloc_n(vol, SUPER_BLOC, (unsigned char *) &super, sizeof super);

  fb.free_bloc_size = super.super_n_free;
  fb.free_bloc_next = (unsigned int) NULL_BLOC;

  write_bloc_n(vol, 1, (unsigned char *) &fb, sizeof fb);
}

void load_super(unsigned int vol) {
  read_bloc_n(vol, SUPER_BLOC, (unsigned char *) &super, sizeof super);
}

void save_super() {
  write_bloc_n(super.super_vol, SUPER_BLOC, (unsigned char *) &super, sizeof super);
}

unsigned int new_bloc() {
  struct free_bloc_s fb;
  unsigned int res;
  res = NULL_BLOC;
  
  if(super.super_n_free == 0)
    return NULL_BLOC;

  read_bloc_n(super.super_vol, super.super_first_free, (unsigned char *) &fb, sizeof fb);

    if(fb.free_bloc_size == 1) {
      res = super.super_first_free;
      super.super_n_free--;
      super.super_first_free = fb.free_bloc_next;
      return res;
    }

  res = super.super_first_free;
  super.super_n_free--;
  super.super_first_free++;
  fb.free_bloc_size--;

  write_bloc_n(super.super_vol, super.super_first_free, (unsigned char *) &fb, sizeof fb);
  return res;
}

void free_bloc(unsigned int bloc) {
    struct free_bloc_s fb;
    fb.free_bloc_size = 1;
    fb.free_bloc_next = super.super_first_free;

    write_bloc_n(super.super_vol, bloc, (unsigned char *) &fb, sizeof fb);
    
    super.super_n_free++;
    super.super_first_free = bloc;
}
