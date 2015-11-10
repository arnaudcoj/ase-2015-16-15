#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vol.h"
#include "config_hardware.h"

struct mbr_s mbr;

static void
create(int s, int fc, int fs)
{
  struct vol_s vol;
  int i, prit = 0, tmpc, tmps;
  assert(fc < HDA_MAXCYLINDER);
  assert(fs < HDA_MAXSECTOR);
  
  for(i = 0; i<mbr.mbr_n_vol; i++){  
    vol = mbr.mbr_vol[i];
    tmpc = vol.vol_first_cylinder + vol.vol_n_bloc/(HDA_MAXSECTOR) +1;
    tmps = vol.vol_first_sector + vol.vol_n_bloc;


/*      FAUX    */
/*    le debut est dans un secteur*/
/*    if(fc >= vol.vol_first_cylinder && fc < tmpc && fs >= vol.vol_first_sector && fs < tmps){*/
/*      prit = 1;*/
/*    }*/
/*    if((fc + s) >= vol.vol_first_cylinder && (fc + s) < tmpc && (fs) >= vol.vol_first_sector && (fs + s) < tmps){*/
/*      prit = 1;*/
/*    }*/
    
    
    
/*    verifier que le volume ne depasse pas sur dautres volumes et quun autre volume n'est pas dans le nouveau*/
/*    ex */
/*    Il y a 3 partition(s)*/
/*    vol n°0, commence (0,12) volume : 10*/
/*    vol n°1, commence (0,2) volume : 10*/
/*    vol n°2, commence (0,1) volume : 10*/

    
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
  create(s, fc, fs);
  save_mbr();
  exit(EXIT_SUCCESS);
}
