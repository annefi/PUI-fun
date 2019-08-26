#include <stdio.h>
#include <string.h>

#include "magframe_out_br.h"
#include "df.h"
#include "mfhdf.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct MagFrm_out_br testdata;
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

  if( init_rd_mag_br(hdf_fp, sd_id,"r") <=0) {
    fprintf(stderr,"No mag vector browse data\n");
    exit(-1);
  }

  ii=0;
  while((retval= read_mag_br(&testdata,ii))!=-1) {
	  printf("%f ", testdata.bin_start);
	  printf("%f ", testdata.bin_end);
	  printf("%4d ", testdata.weight);
	  printf("%12.4f %12.4f %12.4f\n", 
	    testdata.b_out[0], testdata.b_out[1], testdata.b_out[2]);
	  ii++;
	
  }

/*   all done, close HDF file */

  close_rd_mag_br();
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
