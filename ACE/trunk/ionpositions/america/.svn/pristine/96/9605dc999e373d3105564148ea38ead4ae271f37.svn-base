#include <stdio.h>
#include <string.h>

#include "uleis_br_out.h"
#include "df.h"
#include "mfhdf.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct Uleis_br_out data;
  int ii,jj,retval;

  if (argc!=2)
    {
      printf("Usage: rd_hdf hdf_file\n");
      exit(1);
    }

  /* open hdf input file */

  if ((hdf_fp=Hopen(argv[1], DFACC_RDONLY, 0))==FAIL) {
      fprintf(stderr, "Hopen: could not open hdf file\n");
	HEprint(stderr,0); exit(-1);
    }
  if(Vstart(hdf_fp)==FAIL) {
	fprintf(stderr,"Could not Vstart \n");
	HEprint(stderr,0); exit(-1);
  }
  if ((sd_id=SDstart(argv[1], DFACC_RDONLY))==FAIL) {
	fprintf(stderr, "SDstart: could not open hdf file\n");
	HEprint(stderr,0); exit(-1);
  }

  if( init_acc_uleis_br_out(hdf_fp, sd_id, "r") <= 0) {
    fprintf(stderr,"No uleis browse data\n");
	HEprint(stderr,0); exit(-1);
    }

  ii=0;
  while((retval= read_uleis_br_out(&data,ii))!=-1) {
	  printf("%4d bin_start=%f bin_end=%f\n", ii,data.bin_start ,data.bin_end);
	  printf("     ULEIS_livetime=%f\n", data.ULEIS_livetime);
	for (jj=0; jj<9; jj++){
	  printf("      rate assignment= %2d          rates=%12.3f\n", data.rate_assign[jj], data.brws_rates[jj]);
	}
	printf("\n");
  ii++;
  }

/*   all done, close HDF file */

  close_rd_uleis_br_out();
  Vend(hdf_fp);
  if (SDend(sd_id)==FAIL) {
      fprintf(stderr, "SDend: could not close hdf file\n");
	HEprint(stderr,0); exit(-1);
    }
  if (Hclose(hdf_fp)==FAIL) {
      fprintf(stderr, "Hclose: could not close hdf file\n");
	HEprint(stderr,0); exit(-1);
    }

  exit(0);
}
