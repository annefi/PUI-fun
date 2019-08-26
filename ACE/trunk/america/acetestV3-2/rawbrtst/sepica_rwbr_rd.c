#include <stdio.h>
#include <string.h>

#include "sepica_rwbr.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id, AN_id;
  struct Sepica_rwbr testdata;
  int ii,jj,kk,ll,retval;

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

  if( init_rd_sepica_rwbr(hdf_fp, SD_id,"r") <= 0) {
    fprintf(stderr,"No sepecia rw browse data\n");
    exit(-1);
    }

  /* read and print data */
  ii=0;
  while((retval=read_sepica_rwbr(&testdata,ii))!=-1) {
    printf("ii=%4d %13.2f %13.2f %6.2e %6.2e %6.2e %6.2e ", 
	ii++, testdata.bin_start, testdata.bin_end,testdata.H_lo,
	testdata.H_hi, testdata.He_lo, testdata.He_hi);
    printf("%6.2e %6.2e %6.2e %6.2e  lt=%6.2e\n", 
	testdata.C, testdata.O, testdata.Mg_Si, testdata.Fe,
	testdata.livetime);
  }

  /* all done, close HDF interface */

  close_rd_sepica_rwbr();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
