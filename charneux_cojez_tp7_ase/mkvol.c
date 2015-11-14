#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"
#include "config_hardware.h"

struct mbr_s mbr;
struct super_s super;
int verbose = 0;

static int
create(int s, int fc, int fs)
{
  struct vol_s vol;
  int i, prit = 0, tmpc, tmps, bDebutAvantDebut, bFinAvantDebut, bDebutApresFin;
  if(0 >= fc || fc >= HDA_MAXCYLINDER) {
    printf("incorrect value fc : 0 < fc < %d (max cylinder)\n", HDA_MAXCYLINDER);
    return 1;
  }
  
  if(0 >= fs || fs >= HDA_MAXSECTOR) {
    printf("incorrect value fs : 0 < fc < %d (max sector)\n", HDA_MAXSECTOR);
    return 1;
  }

  if(0 >= s || s >= HDA_MAXSECTOR*HDA_MAXCYLINDER) {
    printf("incorrect value s : 0 < s < %d (max capacity)\n", HDA_MAXSECTOR*HDA_MAXCYLINDER);
    return 1;
  }
  
  
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
    /* on test que soit le debut et la fin du nouveau volume soit avant le debut de l'ancien, soit apres la fin de l'ancien */
    if(!((bDebutAvantDebut && bFinAvantDebut ) || bDebutApresFin)){
      prit = 1;
    }
  }
  if(prit == 1){
    printf("erreur, impossible de créer le volume\n");
    return 0;
  }
  vol.vol_first_cylinder = fc;
  vol.vol_first_sector = fs;
  vol.vol_n_bloc = s;
  vol.vol_type = VOL_TYPE_STD;
  mbr.mbr_vol[mbr.mbr_n_vol] = vol;
  mbr.mbr_n_vol ++;

  return 1;
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
      printf("erreur d'arguments, usage :\n\t./mkvol -fc <premier cylindre> -fs <premier secteur> -s <nb de secteurs> [-v (verbose)]\n");
      return EXIT_FAILURE;
    }
  }
  
  if(s == -1 || fs == -1 || fc == -1){
    printf("erreur d'arguments, usage :\n\t./mkvol -fc <premier cylindre> -fs <premier secteur> -s <nb de secteurs> [-v (verbose)]\n");
    return EXIT_FAILURE;
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
    return EXIT_FAILURE;
  }

  if(!create(s, fc, fs))
    return EXIT_FAILURE;
  
  save_mbr();
  return EXIT_SUCCESS;
}
