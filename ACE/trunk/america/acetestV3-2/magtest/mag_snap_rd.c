#include <stdio.h>
#include <string.h>

#include "mag_snapshot.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp,sd_id;
  struct MagSnapSet testdata;
  int ii,retval;

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

  if( init_rd_mag_snap(hdf_fp, sd_id, "r") <= 0) {
    fprintf(stderr,"No mag snap data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_mag_snap(&testdata,ii))!=-1) {
	  printf("%4d sc clock = %8d  QAC=%u\n", ii++,testdata.sctime_readout,testdata.QAC);
	  printf("%4x %4x %4x %4x %4x %4x\n",
	    testdata.hxyz[0][0], testdata.hxyz[1][0], testdata.hxyz[2][0],
	    testdata.hxyz[0][1], testdata.hxyz[1][1], testdata.hxyz[2][1]);
  }

  /* all done, close HDF file */

  close_rd_mag_snap();
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
    
