#include <stdio.h>
#include <string.h>

#include "s3_sstatus.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct sstatus testdata;
  int ii,jj,kk,retval;
  int32 numrec;

  if (argc!=2)
    {
      printf("Usage: %s hdf_file\n",argv[0]);
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

  numrec = init_rd_s3_sstatus(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica s3_sstatus data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_s3_sstatus(&testdata,ii))!=-1) {
    printf("ii=%4d %10u %3d %3x %4x\n", 
	    ii++, testdata.sctime_readout, testdata.QAC, testdata.STACMD[0],
	    testdata.STARET[0]);
  }

  /* all done, close HDF interface */

  close_rd_s3_sstatus();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
