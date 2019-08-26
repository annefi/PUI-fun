#include <stdio.h>
#include <string.h>

#include "sunpulsetime.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp,sd_id;
  struct ACEsunpulsetime testdata;
  int ii,jj,retval;
  float64 lastsptime;
  int32 numrec;

  if (argc!=2) { printf("Usage: rd_hdf hdf_file\n"); exit(1); }

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

  numrec = init_rd_sunpulsetime(hdf_fp, sd_id, "r");
  if( numrec <= 0) {
    fprintf(stderr,"No sun pulse time data\n");
    exit(-1);
    }

  ii=0;
  lastsptime=0;
  while((retval= read_sunpulsetime(&testdata,ii++))!=-1) {
    printf("%12.5f %d %12.5f\n",
	testdata.SPtime, testdata.flag, testdata.SPtime-lastsptime);
    lastsptime=testdata.SPtime;
  }
  printf("Number of records = %d\n",numrec);
  
  /* all done, close HDF file */

  close_rd_sunpulsetime();
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
    
