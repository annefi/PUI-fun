#include <stdio.h>
#include <string.h>

#include "s3_smonitor.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct smonitor testdata;
  int ii,jj,kk,ll,retval;
  int FILL[72];
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

  numrec = init_rd_s3_smonitor(hdf_fp, SD_id, "r");
  if(numrec <=0 ) {
      fprintf(stderr,"No sepica smonitor data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_s3_smonitor(&testdata,ii))!=-1) {
    printf("ii=%4d %10u %14.3f %3d\n", 
	    ii++, testdata.sctime_readout, testdata.sctime_collection,
	    testdata.QAC);

	for(kk=0;kk<SMON_N;kk++)  { 
	    for(ll=0;ll<SMON_S;ll++)  {
		printf("%4x ",testdata.MONITOR[kk][ll]);
	    }
	    printf("\n");
	}
	printf("%4x %4x %4x %4x\n\n", 
	    testdata.FILL[0],testdata.FILL[1],
	    testdata.FILL[2],testdata.FILL[3]);
  }

  /* all done, close HDF interface */

  close_rd_s3_smonitor();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
