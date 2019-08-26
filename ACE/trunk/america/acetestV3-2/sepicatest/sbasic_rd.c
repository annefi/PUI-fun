#include <stdio.h>
#include <string.h>

#include "s3_sbasic.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct sbasic testdata;
  int ii,jj,kk,ll,retval;
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

  numrec = init_rd_s3_sbasic(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica s3_sbasic data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_s3_sbasic(&testdata,ii))!=-1) {
    printf("%10u %14.3f %3d\n", testdata.sctime_readout,
    testdata.sctime_collection,testdata.QAC);
    ii++;
	for(kk=0;kk<SBAS_N;kk++)  { 
	    for(ll=0;ll<SBAS_S;ll++)  {
		printf("%4x ",testdata.BASIC[kk][ll]);
	    }
	    printf("\n");
	}
	printf("%4x %4x\n\n",testdata.FILL[0],testdata.FILL[1]);
  }

  /* all done, close HDF interface */

  close_rd_s3_sbasic();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
