#include <stdio.h>
#include <string.h>

#include "mag_avgvec.h"
#include "df.h"
#include "mfhdf.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct MagAvgVec *testdata;
  int ii,jj,retval;
  int32 numrec;

  if (argc!=2)
    {
      printf("Usage: mag_avgvec_rd hdf_file\n");
      exit(1);
    }

  testdata=malloc(sizeof(struct MagAvgVec));

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
  numrec=init_rd_mag_avgvec(hdf_fp, sd_id, "r");
  if( numrec<=0) {
    fprintf(stderr,"No mag vector data\n");
    exit(-1);
  }

  printf("  readout      collection      b_x        b_y        b_z      b_sigma\n");
  ii=0;
  while((retval= read_mag_avgvec(testdata,ii))!=-1) {
	  printf("%10u   %10u  ",
		 testdata->sctime_readout,testdata->sctime_collection);
	  printf("%10.4f %10.4f %10.4f %10.4f\n", 
		 testdata->b_inertial[0], testdata->b_inertial[1], 
		 testdata->b_inertial[2],testdata->b_sigma);
	  ii++;
  }

  /* all done, close HDF file */

  close_rd_mag_avgvec();
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


