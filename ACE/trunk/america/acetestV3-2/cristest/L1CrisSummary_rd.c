#include <stdio.h>
#include <string.h>

#include "L1CrisSummary.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct L1CrisSummary testdata;
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

  numrec = init_rd_L1CrisSummary(hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No cris Summary data\n");
      exit(-1);
  }

  ii=0;
  while((retval= read_L1CrisSummary(&testdata,ii++))!=FAIL) {
          printf("%5d ",ii);
	  printf("ClockMinorFrame = %8d ", testdata.ClockMinorFrame);
          printf("Sec1996  = %12d ", testdata.Second1996);
          printf("MJF/MNF =  %1d %2d ", testdata.MajorFrameCount,
                                        testdata.MinorFrameCount);
          printf("MainBusV = %3d ", testdata.MainBusVoltage);
          printf("Cris Current =  %3d ", testdata.CrisCurrent);
          printf("CrisHskp = %2.2x%2.2x%2.2x\n", testdata.CrisHskp[0],
                                                 testdata.CrisHskp[1],
                                                 testdata.CrisHskp[2]);
  }

  /* all done, close HDF file */

  close_rd_L1CrisSummary();
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
    
