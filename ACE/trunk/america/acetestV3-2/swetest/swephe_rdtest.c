#include <stdio.h>
#include <string.h>

#include "swepam_dnswe.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct DNSWE testdata;
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

  if( init_rd_swepam_dphe(hdf_fp, SD_id, "r") <= 0) {
    fprintf(stderr,"No swepam dphe data\n");
    exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_swepam_dphe(&testdata,ii))!=-1) {
    printf("ii=%4d %10u  %10u %3d \n", 
	    ii++, testdata.output_sctime,testdata.collect_sctime, testdata.QAC);
	printf("\t");
    for(jj=0;jj<5;jj++) { 
	for(kk=0;kk<6;kk++) 
	    printf("%4d ",testdata.COUNT[jj][kk][0][1]);
	printf("\n\t");
    }
    printf("\n");
  }

  /* all done, close HDF interface */

  close_rd_swepam_dphe();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
