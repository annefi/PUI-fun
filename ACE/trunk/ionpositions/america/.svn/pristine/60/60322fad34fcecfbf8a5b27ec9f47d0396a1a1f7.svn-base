#include <stdio.h>
#include <string.h>

#include "L1SisHskp.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct L1SisHskp testdata;
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

  ;
  if( init_rd_L1SisHskp(hdf_fp, sd_id) ==0) {
    fprintf(stderr,"No sis house keeping data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_L1SisHskp(&testdata,ii++))!=FAIL) {
	printf("Clock=%d Cycnum=%d TempMB=%d PostDcT1a=%d\n",
	testdata.ClockCycle, testdata.CycleNumber,
	testdata.TemperatureMotherBoard,testdata.PostDcT1a);
  }

  /* all done, close HDF file */

  close_rd_L1SisHskp();
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
    
