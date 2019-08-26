#include <stdio.h>
#include <string.h>

#include "swics_br.h"
#include "df.h"


void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct Swics_br testdata;
  int ii,jj,kk,retval;

  int SRcycle=0, cycnum=0;

  if (argc!=2) { 
      printf("Usage: %s hdf_file\n",argv[0]);
      exit(1);
    }

  /* open hdf input file */

  if ((hdf_fp=Hopen(argv[1], DFACC_RDONLY, 0))==FAIL) {
      fprintf(stderr, "Hopen: could not open hdf file\n");
      exit(-1);
    }
  Vstart(hdf_fp);
  if ((SD_id=SDstart(argv[1], DFACC_RDONLY))==FAIL) {
      fprintf(stderr, "SDstart: could not open hdf file\n");
      exit(-1);
    }

 if( init_rd_swics_br(hdf_fp, SD_id, "r") <= 0) {
     fprintf(stderr,"No swics browse data\n");
         exit(-1);
 }
 

  /* read and print data */
  ii=0;
  while((retval=read_swics_br(&testdata,ii++))!=-1) {
    printf("ii=%4d %10u %10u SR:%d\n", 
	ii, testdata.bin_start, testdata.bin_end, SRcycle);

    for(jj=0;jj<60;jj++) {
        printf("edb= %2d dppsvolts= %3d rates= %7d %7d %7d %7d %7d\n",
        testdata.edb[jj], testdata.dpps[jj],
        testdata.rate[0][jj], testdata.rate[1][jj],
        testdata.rate[2][jj], testdata.rate[3][jj],
        testdata.rate[4][jj]);
    }

    SRcycle++;

  }


  /* all done, close HDF interface */

  close_rd_swics_br();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
