#include <stdio.h>
#include "hdfi.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int16 data_valid;    /* -1 if scclock out of bounds */
  float64 scclock;     /* use float64 for spacecraft clock, since some */
                       /* ancillary functions need sub-second resolution */
  float64 vel_gse[3];  /* GSE spacecraft velocity */

  int32 ACE_velocity_GSE();  /* function in ancil_subs.c */
  int32 init_ACEancillary();  /* function in ancil_subs.c */

  if (argc!=3) {
      printf("Usage: get_velocity hdf_file scclock\n");
      exit(1);
  }
  scclock = atof(argv[2]);

  /* load the data from the HDF file, this only needs to be done once */
  /* init_ACEancillary() exits if there is an error */

  init_ACEancillary(argv[1]);

  /* get the GSE velocity corresponding to the spacecraft clock */
  
  data_valid = ACE_velocity_GSE(scclock, vel_gse);
  if(data_valid == -1) fprintf(stdout,"scclock out of bounds\n");
  fprintf(stdout,"%f  %f  %f\n",vel_gse[0],vel_gse[1],vel_gse[2]);

  exit(0);
}
    
