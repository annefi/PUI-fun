#include <stdio.h>
#include <string.h>

#include "s3_smatrix.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct smatrix testdata;
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

  numrec = init_rd_s3_smatrix(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica smatrix data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_s3_smatrix(&testdata,ii))!=-1) {
    printf("%10u %14.3f %3d \n", 
	    testdata.sctime_readout, testdata.sctime_collection,
	    testdata.QAC);
	ii++;
	for(kk=0;kk<60;kk++)  {
	    printf("%4x ",testdata.MATRIX[kk]);
	    if(kk%12==11) printf("\n");
	}
	printf("\n");
  }

  /* all done, close HDF interface */

  close_rd_s3_smatrix();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    




