#include <stdio.h>
#include <string.h>

#include "mag_vector.h"
#include "df.h"
#include "mfhdf.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct MagVectorSet testdata;
  int ii,jj,retval;

  if (argc!=2)
    {
      printf("Usage: rd_hdf hdf_file\n");
      exit(1);
    }

  /* open hdf input file */

  if ((hdf_fp=Hopen(argv[1], DFACC_RDONLY, 0))==FAIL) {
      fprintf(stderr, "Hopen: could not open hdf file\n");
      exit(-1);
    }
  Vstart(hdf_fp);

  if ((sd_id=SDstart(argv[1], DFACC_RDONLY))==FAIL) {
	  fprintf(stderr, "SDstart: could not open hdf file\n");
	  exit(-1);
	}

  if( init_rd_mag_vec(hdf_fp, sd_id, "r") <= 0) {
    fprintf(stderr,"No mag vector data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_mag_vec(&testdata,ii))!=-1) {
	  printf("%4d sc clock = %8d QAC = %d\n", ii++,testdata.sctime_readout, testdata.QAC);
	  for(jj=0;jj<96;jj++)  { printf("%3x %3x %3x  ", 
	      testdata.vector[0][jj], testdata.vector[1][jj], 
	      testdata.vector[2][jj]);
	      if((jj%6)==5) printf("\n");
	  }
  }

  /* all done, close HDF file */

  close_rd_mag_vec();
  Vend(hdf_fp);
  if (SDend(sd_id)==FAIL) {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp)==FAIL) {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  exit(0);
}
