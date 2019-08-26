#include <stdio.h>
#include <string.h>

#include "epam.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct EpamData testdata;
  int ii,jj,kk,retval;
  int32 numrec;

  int lastclk=0;

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

  numrec = init_rd_epam_data(hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No epam data\n");
      exit(-1);
  }

  ii=0;
  while((retval= read_epam_data(&testdata,ii++))!=FAIL) {
	  printf("rec=%4d sc clock = %8d QAC=%3x \n", 
	    ii,testdata.sctime_readout,testdata.QAC);
	  lastclk=testdata.sctime_readout;
	  
	  for(jj=0;jj<21;jj++) printf("%2x ",testdata.data[0][jj]);
	  printf("\n");
	  printf("Sun Pulse Data\n");
	  for(jj=0;jj<8;jj++) printf(" %8x", testdata.SunPulDat[0][jj]);
	  printf("\n");
	  for(jj=0;jj<8;jj++) printf(" %8x", testdata.SunPulDat[1][jj]);
	  printf("\n");
	  printf("Sun Pulse Latch\n");
	  for(jj=0;jj<8;jj++) printf(" %8x", testdata.SunPulLat[0][jj]);
	  printf("\n");
	  for(jj=0;jj<8;jj++) printf(" %8x", testdata.SunPulLat[1][jj]);
	  printf("\n");
	  printf("Phase Angle\n");
	  for(jj=0;jj<16;jj++) printf(" %4x", testdata.PhaseAng[jj]);
	  printf("\n");
  }

  /* all done, close HDF file */

  close_rd_epam_data();
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
    




