#include <stdio.h>
#include <string.h>

#include "L1SisDiagnosticEvent.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct L1SisDiagnosticEvent testdata;
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

  if( init_rd_L1SisDiagnosticEvent(hdf_fp, sd_id) ==0) {
    fprintf(stderr,"No sis diagnostic event data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_L1SisDiagnosticEvent(&testdata,ii++))!=FAIL) {
	printf("ClockMF0:1 = %d:%d RawStack=%6d, %6d, %6d, %6d\n",
	testdata.ClockMinorFrame0, testdata.ClockMinorFrame1,
	testdata.RawStack[0], testdata.RawStack[1],
	testdata.RawStack[2], testdata.RawStack[3]);
  }

  /* all done, close HDF file */

  close_rd_L1SisDiagnosticEvent();
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
    
