/* get_ACE_epoch.c - for a given spacecraft clock value, calculate ACE_Epoch, */
/* using spacecraft clock calibration data from the ACE_ANCIL.HDF database. */

/* Note: the function init_ACEancillary() reads the complete database into memory. */
/* It should only be called once */

/* Note: the function SCclock_to_ACEepoch() returns ACE_Epoch corresponding to a */
/* given spacecraft clock.  ACE_epoch is seconds since 00:00:00Z Jan 1, 1996 UTC. */

#include <stdio.h>
#include "hdfi.h"

void main(argc, argv)
int argc;
char *argv[];
{
  float64 scclock;     /* use float64 for spacecraft clock, since some */
                       /* ancillary functions need sub-second resolution */

  float64 ACEepoch;
  float64 SCclock_to_ACEepoch();
  int32 init_ACEancillary();
  
  
  if (argc!=3) {
      printf("Usage: get_ACEepoch hdf_file scclock\n");
      exit(1);
  }
  scclock = atof(argv[2]);

  /* load the data from the HDF file */
  /* init_ACEancillary() exits if there is an error */
  init_ACEancillary(argv[1]);

  /* get the ACE epoch (seconds since Jan 1, 1996 UTC) corresponding */
  /* to the scclock */
  if((ACEepoch=SCclock_to_ACEepoch(scclock))==-1.0) {
     fprintf(stdout,"scclock out of bounds\n");
  }
  else
     fprintf(stdout,"%f\n",ACEepoch);
     
  exit(0);
}
    
