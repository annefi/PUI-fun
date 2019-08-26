#include <stdio.h>
#include <string.h>

#include "s3_edb.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct s3_edb testdata;
  int ii,jj,kk,ll,retval;

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
  init_rd_s3_edb(hdf_fp, sd_id,"r");

  ii=0;
  while((retval= read_s3_edb(&testdata,ii++))!=FAIL) {
	  printf("%d  %f  %u   ", testdata.sctime_readout,testdata.ACEepoch_collection,
	  testdata.QAC);
	  for(jj=0;jj<12;jj++)
	     printf("%u ",testdata.QACarr[jj]);
	  printf("\n");
  }

  /* all done, close HDF file */

  close_rd_s3_edb();
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
    
