#include <stdio.h>
#include <string.h>

#include "mag_fft.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp,sd_id;
  struct MagFFTSet testdata;
  int ii,jj,kk,retval;

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

  if( init_rd_mag_fft(hdf_fp, sd_id, "r") <= 0) {
    fprintf(stderr,"No mag fft data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_mag_fft(&testdata,ii))!=-1) {
	  printf("%4d sc clock = %8d QAC=%u\n", 
	    ii++,testdata.sctime_readout,testdata.QAC);
	  printf("  %4x %4x %4x %4x %4x\n",
	      testdata.fft_statbits[0], testdata.fft_statbits[1], 
	      testdata.fft_statbits[2], testdata.fft_statbits[3], 
	      testdata.fft_statbits[4]);
	  for(jj=0;jj<FFTBIN;jj++) {
	    for(kk=0;kk<10;kk++)
	      printf(" %2x",testdata.fft_val[kk][jj]);
	    printf("\n");
	  }
	  printf("\n");
  }

  /* all done, close HDF file */

  close_rd_mag_fft();
  Vend(hdf_fp);
  if (SDend(sd_id)==FAIL) {
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
    
