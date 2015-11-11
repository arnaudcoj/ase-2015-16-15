#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"
#include "config_hardware.h"

struct mbr_s mbr;
int verbose = 0;

static void
create(int s, int fc, int fs)
{
  struct vol_s vol;
  int i, prit = 0, tmpc, tmps, bDebutAvantDebut, bFinAvantDebut, bDebutApresFin;
  assert(fc < HDA_MAXCYLINDER);
  assert(fs < HDA_MAXSECTOR);
  
  for(i = 0; i<mbr.mbr_n_vol; i++){  
    vol = mbr.mbr_vol[i];
    
    /* dernier cylindre utilisé par le volume */
    tmpc = vol.vol_first_cylinder + (vol.vol_first_sector + vol.vol_n_bloc - 1)/HDA_MAXSECTOR ;
    
    /* dernier secteur utilisé par le volume */
    tmps = (vol.vol_first_sector + vol.vol_n_bloc -1 ) % HDA_MAXSECTOR;
    
    if(verbose)
        printf("debuts : %d, tmps : %d, debutc : %d,  tmpc : %d\n",vol.vol_first_sector, tmps, vol.vol_first_cylinder, tmpc);

    bDebutAvantDebut = (fc == vol.vol_first_cylinder && fs < vol.vol_first_sector)
        || (fc < vol.vol_first_cylinder);
        
    bFinAvantDebut =  ((fc + (fs + s - 1)/HDA_MAXSECTOR) == vol.vol_first_cylinder && ((fs + s -1)%HDA_MAXSECTOR) < vol.vol_first_sector)
        || ((fc + (fs + s - 1)/HDA_MAXSECTOR) < vol.vol_first_cylinder);
     
     if(verbose)    
        printf("finfc : %d, finfs : %d\n", (fc + (fs +s - 1)/HDA_MAXSECTOR), ((fs + s -1)%HDA_MAXSECTOR));
        
    bDebutApresFin = (fc == tmpc && fs > tmps)
        || (fc > tmpc);
    if(verbose)    
        printf("debutavantdebut : %d, finavantdebut : %d, debutapresfin : %d\n", bDebutAvantDebut, bFinAvantDebut, bDebutApresFin);
    /* on test que soit le debut et la fin du nous volume soit avant le debut de l'ancien, soit apres la fin de l'ancien */
    if(!((bDebutAvantDebut && bFinAvantDebut ) || bDebutApresFin)){
      prit = 1;
    }
  }
  if(prit == 1){
    printf("erreur, impossible de créer le volume\n");
    return;
  }
  vol.vol_first_cylinder = fc;
  vol.vol_first_sector = fs;
  vol.vol_n_bloc = s;
  vol.vol_type = VOL_TYPE_STD;
  mbr.mbr_vol[mbr.mbr_n_vol] = vol;
  mbr.mbr_n_vol ++;
  
}

static void empty_it() {
  return;
}

int
main(int argc, char **argv)
{
  int i, s = -1, fc = -1, fs = -1;
  
  for(i = 1; i < argc; i+=2){
    if(!strcmp(argv[i], "-s")){
      s = atoi(argv[i+1]);
    } else if(!strcmp(argv[i], "-fs")){
      fs = atoi(argv[i+1]);
    } else if(!strcmp(argv[i], "-fc")){
      fc = atoi(argv[i+1]);
    } else if(!strcmp(argv[i], "-v")){
      verbose = 1;
      i--;
    } else {
      printf("erreur d'arguments\n");
      exit(EXIT_FAILURE);
    }
  }
  
  if(s == -1 || fs == -1 || fc == -1){
    printf("erreur d'arguments\n");
    exit(EXIT_FAILURE);
  }
  
  /* init master drive and load MBR */  
  init_master();
  /* Interrupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);
  chk_hda();

  load_mbr();
  if(mbr.mbr_n_vol >= MAXVOL){
    printf("nombre maximum de volume créé.\n");
    exit(EXIT_FAILURE);
  }
  
  create(s, fc, fs);
  save_mbr();
  exit(EXIT_SUCCESS);
}
