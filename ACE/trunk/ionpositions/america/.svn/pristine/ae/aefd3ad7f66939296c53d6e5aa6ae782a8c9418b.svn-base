#include <stdio.h>
#include <string.h>

#include "L1SisLowPriorityRate.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct L1SisLowPriorityRate testdata;
  int ii,jj,kk,retval;

  if (argc!=2)
    {
      printf("Usage: %s hdf_file\n",argv[0]);
      exit(1);
    }

  /* open hdf input file */

  if ((hdf_fp=Hopen(argv[1], DFACC_ALL, 0))==FAIL)
    {
      fprintf(stderr, "Hopen: could not open hdf file\n");
      exit(-1);
    }
  Vstart(hdf_fp);

  if ((sd_id=SDstart(argv[1], DFACC_WRITE))==FAIL)
    {
      fprintf(stderr, "SDstart: could not open hdf file\n");
      exit(-1);
    }

  if( init_rd_L1SisLowPriorityRate(hdf_fp, sd_id) ==0) {
    fprintf(stderr,"No sis low priority rate data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_L1SisLowPriorityRate(&testdata,ii++))!=FAIL) {
	printf("Clock=%d RejM1a=%6d RejCoinR0=%6d VldM1a=%6d\n",
	testdata.ClockCycle, testdata.RejcntsM1a, 
	testdata.RejcntsCoinRate0, testdata.VldcntsM1a);
  }

  /* all done, close HDF file */

  close_rd_L1SisLowPriorityRate();
  Vend(hdf_fp);
  if (SDend(sd_id)==FAIL)
    {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  exit(0);
}
    
