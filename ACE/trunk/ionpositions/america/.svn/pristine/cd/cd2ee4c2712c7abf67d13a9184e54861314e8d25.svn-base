#include <stdio.h>
#include <string.h>

#include "ace_br_5min.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp,SD_id;
  struct ace_br_5min_avg testdata;
  int ii,jj,kk,retval;
  int nrec;

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
  if ((SD_id=SDstart(argv[1], DFACC_RDONLY))==FAIL)
      {
	fprintf(stderr, "SDstart: could not open hdf file\n");
	exit(-1);
      }

  nrec=init_rd_acebr_5min(hdf_fp, SD_id,"r");
  if (nrec<=0) {
     fprintf(stderr,"no 5min browse data!\n");
     exit(1);
  }

  ii=0;
  while((retval= read_acebr_5min(&testdata,ii++))!=-1) {
	printf("%4d %4d %f   %f   %f\n", 
	    ii,testdata.year,testdata.DOY,testdata.H_den_SWP,testdata.SW_spd_SWP);
  }

  /* all done, close HDF file */

  close_rd_acebr_5min();
  Vend(hdf_fp);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  exit(0);
}
    
