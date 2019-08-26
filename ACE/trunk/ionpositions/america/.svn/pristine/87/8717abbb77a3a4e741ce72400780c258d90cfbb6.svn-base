#include <stdio.h>
#include <string.h>

#include "s3schk.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct s3schk testdata;
  int ii,jj,kk,retval;

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

  if( init_rd_s3schk(hdf_fp, SD_id, "r") <= 0) {
    fprintf(stderr,"No swims s3 schk data\n");
    exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_s3schk(&testdata,ii))!=-1) {
    printf("ii=%4d %10u %2x %2x %2x %2x \n", 
	    ii++, testdata.sctime_readout, testdata.SepDecTmp,
	    testdata.SepIsoButTmp,testdata.SepLog,
	    testdata.S3Log);
  }

  /* all done, close HDF interface */

  close_rd_s3schk();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
