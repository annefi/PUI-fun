#include <stdio.h>
#include "hdfi.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int16 data_valid;    /* -1 if scclock out of bounds */
  float64 scclock;     /* use float64 for spacecraft clock, since some */
                       /* ancillary functions need sub-second resolution */
  float64 pos_gci[3];  /* J2000 GCI spacecraft position */

  int32 ACE_position_J2GCI();  /* function in ancil_subs.c */
  int32 init_ACEancillary();  /* function in ancil_subs.c */

  if (argc!=3) {
      printf("Usage: get_position hdf_file scclock\n");
      exit(1);
  }
  scclock = atof(argv[2]);

  /* load the data from the HDF file, this only needs to be done once */
  /* init_ACEancillary() exits if there is an error */

  init_ACEancillary(argv[1]);

  /* get the J2000 GCI position corresponding to the spacecraft clock */
  
  data_valid = ACE_position_J2GCI(scclock, pos_gci);
  if(data_valid == -1) fprintf(stdout,"scclock out of bounds\n");
  fprintf(stdout,"%f  %f  %f\n",pos_gci[0],pos_gci[1],pos_gci[2]);

  exit(0);
}
    
