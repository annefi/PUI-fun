#include <stdio.h>
#include "hdfi.h"

void main(argc, argv)
int argc;
char *argv[];
{
  float64 scclock;     /* use float64 for spacecraft clock, since some */
                       /* ancillary functions need sub-second resolution */

  float64 ACEepoch;
  float64 ACEepoch_to_SCclock();
  int32 init_ACEancillary();
  
  
  if (argc!=3) {
      printf("Usage: get_scclock hdf_file ACEepoch\n");
      exit(1);
  }
  ACEepoch = atof(argv[2]);

  /* load the data from the HDF file */
  /* init_ACEancillary() exits if there is an error */
  init_ACEancillary(argv[1]);

  /* get the scclock corresponding to the ACE epoch */
  /* (seconds since Jan 1, 1996 UTC) corresponding */

  if((scclock=ACEepoch_to_SCclock(ACEepoch))==-1.0) {
     fprintf(stdout,"ACEepoch out of bounds\n");
  }
  else
     fprintf(stdout,"%f\n",scclock);
     
  exit(0);
}
    
