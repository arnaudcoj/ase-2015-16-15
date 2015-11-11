#ifndef DRIVE_H
#define DRIVE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "config_hardware.h"
#include "hardware.h"
#define SECTORSIZE 256

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
void read_sector_n(unsigned int cylinder, unsigned int sector, unsigned char *buffer, unsigned int size);
void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer);
void write_sector_n(unsigned int cylinder, unsigned int sector, const unsigned char *buffer, unsigned size);
void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value);
void chk_hda (void);
void init_master(void);

#endif
