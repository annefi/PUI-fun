#include <stdio.h>
#include <string.h>

#include "L1CrisDiagnosticEvent.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct L1CrisDiagnosticEvent testdata;
  int ii,jj,kk,retval;
  int32 numrec;

  if (argc!=2)
    {
      printf("Usage: rd_hdf hdf_file\n");
      exit(1);
    }

  /* open hdf input file */

  if ((hdf_fp=Hopen(argv[1], DFACC_RDONLY, 0))==FAIL)
    {
      fprintf(stderr, "Hopen: could not open hdf file\n");
      exit(-1);
    }
  Vstart(hdf_fp);

  if ((sd_id=SDstart(argv[1], DFACC_RDONLY))==FAIL)
    {
      fprintf(stderr, "SDstart: could not open hdf file\n");
      exit(-1);
    }

  numrec = init_rd_L1CrisDiagnosticEvent(hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No cris L1 Diagnostic Event data\n");
      exit(-1);
  }

  ii=0;
  while((retval= read_L1CrisDiagnosticEvent(&testdata,ii++))!=FAIL) {
          printf("%5d ",ii);
	  printf("ClockMinorFrame0 = %8d ", testdata.ClockMinorFrame0);
	  printf("ClockMinorFrame1 = %8d ", testdata.ClockMinorFrame1);
          printf("Sec1996  = %12d ", testdata.Second1996MinorFrame0);
          printf("Continuation =  %d\n ", testdata.ContinuationFlag);
  }

  /* all done, close HDF file */

  close_rd_L1CrisDiagnosticEvent();
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
