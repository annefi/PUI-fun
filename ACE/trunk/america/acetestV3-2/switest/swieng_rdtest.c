#include <stdio.h>
#include <string.h>

#include "swepam_dengi.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct DENGI testdata;
  int ii,jj,retval;

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

  if( init_rd_swepam_dengi(hdf_fp, SD_id, "r") <= 0) {
    fprintf(stderr,"No swepam dengi data\n");
    exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_swepam_dengi(&testdata,ii))!=-1) {
    printf("ii=%4d %10u %3d \n", 
	    ii++, testdata.output_sctime, testdata.QAC);
    for(jj=0;jj<16;jj++) {
    printf("\t%4d %4d %4d %4d %4d %4d %4d\n", 
	    testdata.MinFrmIndx[jj], testdata.EventFlag[jj], 
	    testdata.StatRec[jj][0], testdata.ScalarRecDat[jj][0], 
	    testdata.DumpRecAdd[jj], testdata.DumpRecDat[jj][0], 
	    testdata.MinFrmChk[jj]);
    }
  }

  /* all done, close HDF interface */

  close_rd_swepam_dengi();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    

