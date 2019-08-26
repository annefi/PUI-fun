#include <stdio.h>
#include <string.h>

#include "swepam_dhskpi.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct DHSKPI testdata;
  int ii,jj,kk,retval;

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

  if( init_rd_swepam_dhskpi(hdf_fp, SD_id, "r") <= 0) {
    fprintf(stderr,"No swepam dkskpi data\n");
    exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_swepam_dhskpi(&testdata,ii))!=-1) {
    printf("ii=%4d %10u %3d \n", ii++, testdata.output_sctime, testdata.QAC);
    for(jj=0;jj<8;jj++)
	printf("\t%3d %3d %3d %3d %5d\n",
	    testdata.SCid[jj], testdata.FmtFC[jj],testdata.FmtID[jj],
	    testdata.EF[jj],testdata.CS[jj]);
  }

  /* all done, close HDF interface */

  close_rd_swepam_dhskpi();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
