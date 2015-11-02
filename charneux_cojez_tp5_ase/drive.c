#include "drive.h"

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer){
  int i;
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
  for(i = 0; i < SECTORSIZE; i++)
    buffer[i] = MASTERBUFFER[i];
  
}

void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer) {
  printf("to be implemented\n");
}

void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value) {
  _out(HDA_DATAREGS, (cylinder>>8) & 0xFF);
  _out(HDA_DATAREGS +1, cylinder & 0xFF);
  _out(HDA_DATAREGS +2, (sector>>8) & 0xFF);
  _out(HDA_DATAREGS +3, sector & 0xFF);
  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);
  _out(HDA_DATAREGS, (nsector>>8) & 0xFF);
  _out(HDA_DATAREGS +1, nsector & 0xFF);
  _out(HDA_DATAREGS +2, (value>>24) & 0xFF);
  _out(HDA_DATAREGS +3, (value>>16) & 0xFF);
  _out(HDA_DATAREGS +4, (value>>8) & 0xFF);
  _out(HDA_DATAREGS +5, value & 0xFF);
  _out(HDA_CMDREG, CMD_FORMAT);
  _sleep(HDA_IRQ);
  
}

void chk_hda (void) {
  int sectorsize;
  _out(HDA_CMDREG, CMD_DSKINFO);
  sectorsize = (_in(HDA_DATAREGS +4) << 8) +  _in(HDA_DATAREGS +5);
  assert( SECTORSIZE == sectorsize);
}
