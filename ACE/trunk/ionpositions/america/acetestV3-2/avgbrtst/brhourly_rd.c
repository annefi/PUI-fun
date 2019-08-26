#include <stdio.h>
#include <string.h>

#include "ace_br_1hr.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp,SD_id;
  struct ace_br_1hr_avg testdata;
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

  nrec = init_rd_acebr_1hr(hdf_fp, SD_id,"r");
  if( nrec <= 0) {
      exit(-1);
  }

  ii=0;
  while((retval= read_acebr_1hr(&testdata,ii++))!=-1) {
	printf("%4d %4d %f   %f\n", 
	    ii,testdata.year,testdata.DOY,testdata.SW_spd_SWP);
  }

  /* all done, close HDF file */

  close_rd_acebr_1hr();
  Vend(hdf_fp);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  exit(0);
}
    
