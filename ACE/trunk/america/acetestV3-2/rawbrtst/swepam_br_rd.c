#include <stdio.h>
#include <string.h>

#include "swepam_bri.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id, AN_id;
  struct SwepamI_br testdata;
  int ii,jj,kk,ll,retval;

  if (argc!=2)
    {
      printf("Usage: %s hdf_file\n",argv[0]);
      exit(1);
    }

  /* open hdf input file */

  if ((hdf_fp=Hopen(argv[1], DFACC_RDONLY, 0))==FAIL)
    {
      fprintf(stderr, "Hopen: could not open hdf file\n");
      exit(-1);
    }
  Vstart(hdf_fp);
  if ((SD_id=SDstart(argv[1], DFACC_RDONLY))==FAIL)
    {
      fprintf(stderr, "SDstart: could not open hdf file\n");
      exit(-1);
    }

  if( init_rd_swepam_br(hdf_fp, SD_id,"r") <= 0) {
    fprintf(stderr, "No swepam browse data\n");
    exit(-1);
    }

  /* read and print data */
  ii=0;
  while((retval=read_swepam_br(&testdata,ii))!=-1) {
    printf("ii=%4d %13.2f %13.2f\n", 
	ii++, testdata.bin_start, testdata.bin_end);
    printf("  flag=%2d np=%8.3e he_ratio=%8.3e speed=%8.3e Trr=%8.3e\n",
	testdata.flag3d, testdata.np, testdata.he_ratio, 
	testdata.speed, testdata.Trr);
  }

  /* all done, close HDF interface */

  close_rd_swepam_br();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
