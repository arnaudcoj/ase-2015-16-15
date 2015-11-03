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
  int i;
  printf("to be implemented\n");
  _out(HDA_DATAREGS, (cylinder>>8) & 0xFF);
  _out(HDA_DATAREGS +1, cylinder & 0xFF);
  _out(HDA_DATAREGS +2, (sector>>8) & 0xFF);
  _out(HDA_DATAREGS +3, sector & 0xFF);
  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);

  /*version avec caractere à la fin de buff*/
  /*for(i = 0; i < SECTORSIZE; i++)
    MASTERBUFFER[i] = buffer[i];*/

  /* v2 */
  for(i = 0; i < strlen((const char * )buffer) && i<SECTORSIZE; i++)
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
