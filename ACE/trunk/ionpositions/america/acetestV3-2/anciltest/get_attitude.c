#include <stdio.h>
#include "hdfi.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int16 data_valid; /* 0 if data of good quality, 1 if poor (during */
                    /*  manouvers, burns ) */
  float64 scclock;     /* use float64 for spacecraft clock, since some */
                       /* ancillary functions need sub-second resolution */
  float64 att_rtn[3];

  int32 ACE_attitude_RTN();  /* function in ancil_subs.c */
  int32 init_ACEancillary();  /* function in ancil_subs.c */

  if (argc!=3) {
      printf("Usage: get_attitude hdf_file scclock\n");
      exit(1);
  }
  scclock = atof(argv[2]);

  /* load the data from the HDF file, this only needs to be done once */
  /* init_ACEancillary() exits if there is an error */

  init_ACEancillary(argv[1]);

  /* get the RTN attitude corresponding to the spacecraft clock */
  
  data_valid = ACE_attitude_RTN(scclock, att_rtn);
  if(data_valid == -1) fprintf(stdout,"scclock out of bounds, or no RTN data\n");
  else if(data_valid > 0) fprintf(stdout,"%d %f  %f  %f\n",
		     data_valid,att_rtn[0],att_rtn[1],att_rtn[2]);
  else
    fprintf(stdout,"%f  %f  %f\n",att_rtn[0],att_rtn[1],att_rtn[2]);

  exit(0);
}
    
