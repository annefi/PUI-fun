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

  if( init_rd_s3_edb(hdf_fp, sd_id, "r") <= 0) {
    fprintf(stderr,"No S3 edb data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_s3_edb(&testdata,ii++))!=FAIL) {
	  printf("ii=%8d sc clock = %8u coll=%f", 
	     ii,testdata.sctime_readout, testdata.ACEepoch_collection);
	  printf("  %3x \n", testdata.QAC);
	  for(kk=0;kk<12;kk++){ printf(" %2x", testdata.QACarr[kk]); }
	  printf("\n");
	  for(kk=0;kk<1;kk++){
	      printf("%2d\t",kk);
	      for(jj=0;jj<203;jj++) {
		    printf("%2x ",testdata.data[kk][jj]);
		    if(jj%16==15) printf("\n\t");
		    }
	      printf("\n");
	  }
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
    
