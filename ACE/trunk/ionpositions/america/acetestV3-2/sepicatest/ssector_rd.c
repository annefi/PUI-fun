#include <stdio.h>
#include <string.h>

#include "s3_ssector.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct ssector testdata;
  int ii,jj,kk,ll,retval;
  int SECTOR1[960];
  int mm;
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

  numrec = init_rd_s3_ssector(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica s3_ssector data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_s3_ssector(&testdata,ii))!=-1) {
    printf("ii=%4d %10u %14.3f %3d\n", 
	    ii++, testdata.sctime_readout, testdata.sctime_collection,
	    testdata.QAC);

	for(kk=0;kk<SSEC_N;kk++)  { 
	    for(ll=0;ll<SSEC_S;ll++)  {
		printf("%4x ",testdata.SECTOR[kk][ll]);
	    }
	    printf("\n");
	}
	printf("\n");
  }

  /* all done, close HDF interface */

  close_rd_s3_ssector();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
