#include <stdio.h>
#include <string.h>

#include "L1SisEventCycle.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct L1SisEventCycle testdata;
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

  if( init_rd_L1SisEventCycle(hdf_fp, sd_id) ==0) {
    fprintf(stderr,"No sis event cycle data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_L1SisEventCycle(&testdata,ii++))!=FAIL) {
	printf("Clock=%d Nev=%d Contflag=%d\n",
	testdata.ClockCycle,testdata.NumberEvents,
	testdata.ContinuationFlag);
  }

  /* all done, close HDF file */

  close_rd_L1SisEventCycle();
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
    
