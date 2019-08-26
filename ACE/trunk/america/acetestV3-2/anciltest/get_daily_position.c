/* get GSE position of ACE spacecraft at beginning of each day of mission */

#include <stdio.h>
#include "hdfi.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int16 data_valid;    /* -1 if scclock out of bounds */
  float64 scclock_max, scclock;     /* use float64 for spacecraft clock, since some */
                       /* ancillary functions need sub-second resolution */
  float64 pos_gse[3];  /* GSE spacecraft position */

  int32 ACE_position_GSE();  /* function in ancil_subs.c */
  int32 init_ACEancillary();  /* function in ancil_subs.c */

  if (argc!=3) {
      printf("Usage: %s hdf_file scclock_max\n",argv[0]);
      exit(1);
  }
  scclock_max = atof(argv[2]);

  /* load the data from the HDF file, this only needs to be done once */
  /* init_ACEancillary() exits if there is an error */

  init_ACEancillary(argv[1]);

  /* get the GSE position corresponding to the spacecraft clock */

  scclock = 29495.0;

  while(scclock < scclock_max) {
     data_valid = ACE_position_GSE(scclock, pos_gse);
     if(data_valid != -1)
        fprintf(stdout," %d %f  %f  %f\n",(int)scclock, pos_gse[0],pos_gse[1],pos_gse[2]);
     scclock += 86400.0;
  }

  exit(0);
}
    
