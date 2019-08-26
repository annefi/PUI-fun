#include <stdio.h>
#include <string.h>

#include "s3_dhk.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct sshdhk testdata;
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

  numrec = init_rd_s3_dhk(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica s3_dhk data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  printf("sctime_readout QAC EDB SPINCTR SUNSECTOR RECORDCTR SECTOR7LEN SECTOR0LEN\n");
  while((retval=read_s3_dhk(&testdata,ii))!=-1) {
    printf("%10u %3d ", testdata.sctime, testdata.QAC);
    printf("%2d %8d %6d %4d %4d %4d\n",
	testdata.EDB, testdata.SPINCTR, testdata.SUNSECTOR,
	testdata.RECORDCTR, testdata.SECTOR7LEN,testdata.SECTOR0LEN);
    ii++;
  }

  /* all done, close HDF interface */

  close_rd_s3_dhk();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
