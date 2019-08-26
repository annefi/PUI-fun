#include <stdio.h>
#include <string.h>

#include "L1CrisHighPriorityRate.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct L1CrisHighPriorityRate testdata;
  int ii,jj,kk,retval;
  int32 numrec;

  if (argc!=2)
    {
      printf("Usage: rd_hdf hdf_file\n");
      exit(1);
    }

  /* open hdf input file */

  if ((hdf_fp=Hopen(argv[1], DFACC_RDONLY, 0))==FAIL)
    {
      fprintf(stderr, "Hopen: could not open hdf file\n");
      exit(-1);
    }
  Vstart(hdf_fp);

  if ((sd_id=SDstart(argv[1], DFACC_RDONLY))==FAIL)
    {
      fprintf(stderr, "SDstart: could not open hdf file\n");
      exit(-1);
    }

  numrec = init_rd_L1CrisHighPriorityRate(hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No cris L1 High Priority Rate data\n");
      exit(-1);
  }

  ii=0;
  while((retval= read_L1CrisHighPriorityRate(&testdata,ii++))!=FAIL) {
          printf("%5d ",ii);
	  printf("ClockMinorFrame = %8d ", testdata.ClockMinorFrame);
          printf("Sec1996  = %12d ", testdata.Second1996);
          printf("hp[0] = %8d ", testdata.hp[0]);
          printf("hp[1] = %8d\n", testdata.hp[1]);
  }

  /* all done, close HDF file */

  close_rd_L1CrisHighPriorityRate();
  Vend(hdf_fp);
  if (SDend(sd_id)==FAIL)
    {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  exit(0);
}
    
