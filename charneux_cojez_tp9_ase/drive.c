#include "drive.h"

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer){
  read_sector_n(cylinder, sector, buffer, SECTORSIZE);
}

void read_sector_n(unsigned int cylinder, unsigned int sector, unsigned char *buffer, unsigned int size) {
  int i;
  assert(size <= SECTORSIZE);
  _out(HDA_DATAREGS, (cylinder>>8) & 0xFF);
  _out(HDA_DATAREGS +1,cylinder & 0xFF);
  _out(HDA_DATAREGS +2, (sector>>8) & 0xFF);
  _out(HDA_DATAREGS +3, sector & 0xFF);
  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);

  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS +1, 1);
  _out(HDA_CMDREG, CMD_READ);
  _sleep(HDA_IRQ);

  for(i = 0; i < size; i++)
    buffer[i] = MASTERBUFFER[i];
}

void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer) {
  write_sector_n(cylinder, sector, buffer, SECTORSIZE);
}

void write_sector_n(unsigned int cylinder, unsigned int sector, const unsigned char *buffer, unsigned size) {
  int i;
  _out(HDA_DATAREGS, (cylinder>>8) & 0xFF);
  _out(HDA_DATAREGS +1, cylinder & 0xFF);
  _out(HDA_DATAREGS +2, (sector>>8) & 0xFF);
  _out(HDA_DATAREGS +3, sector & 0xFF);
  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);

  for(i = 0; i < size; i++)
    MASTERBUFFER[i] = buffer[i];

  _out(HDA_DATAREGS, 0x00);
  _out(HDA_DATAREGS +1, 0x01);
  _out(HDA_CMDREG, CMD_WRITE);
  _sleep(HDA_IRQ);
}


void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value) {
  int i;
  for(i=sector; i< (sector + nsector); i++){
    _out(HDA_DATAREGS, (cylinder>>8) & 0xFF);
    _out(HDA_DATAREGS +1, cylinder & 0xFF);
    _out(HDA_DATAREGS +2, (i>>8) & 0xFF);
    _out(HDA_DATAREGS +3, i & 0xFF);
    _out(HDA_CMDREG, CMD_SEEK);
    _sleep(HDA_IRQ);

    _out(HDA_DATAREGS, 0x00);
    _out(HDA_DATAREGS +1, 0x01);
    _out(HDA_DATAREGS +2, (value>>24) & 0xFF);
    _out(HDA_DATAREGS +3, (value>>16) & 0xFF);
    _out(HDA_DATAREGS +4, (value>>8) & 0xFF);
    _out(HDA_DATAREGS +5, value & 0xFF);
    _out(HDA_CMDREG, CMD_FORMAT);
    _sleep(HDA_IRQ);
  }
}

void chk_hda (void) {
  int sectorsize;
  _out(HDA_CMDREG, CMD_DSKINFO);
  sectorsize = (_in(HDA_DATAREGS +4) << 8) +  _in(HDA_DATAREGS +5);
  assert( SECTORSIZE == sectorsize);
}

static void empty_it() {
  return;
}

void init_master(void) {
  char *config_str;
  int i;

  config_str = getenv("HW_CONFIG");
  assert(config_str);

  if(init_hardware(config_str) == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }
  
  /* Interrupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);
  chk_hda();
}
