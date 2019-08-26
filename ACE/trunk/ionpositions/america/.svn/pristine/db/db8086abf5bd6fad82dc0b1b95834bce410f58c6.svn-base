#include <stdio.h>
#include <string.h>

#include "swepam_dloade.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct DLOADE testdata;
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

  if( init_rd_swepam_dloade(hdf_fp, SD_id, "r") <= 0) {
    fprintf(stderr,"No swepam dloade data\n");
    exit(-1);
    }

  /* read and print data */
  ii=0;
  while((retval=read_swepam_dloade(&testdata,ii))!=-1) {
    printf("\nii=%4d %10u %3d \n", 
	    ii++, testdata.output_sctime, testdata.QAC);
    for(jj=0;jj<16;jj++) { 
	printf("\t%2x %2x %2x %2x %2x \n", 
		testdata.MinFrmIndx[jj],testdata.EventFlag[jj], 
		testdata.StatRec[jj][0], testdata.StatRec[jj][1], 
		testdata.StatRec[jj][2]);
	printf("\tLoad: %2x %2x %2x %2x %2x %2x \n\tFill:", 
		testdata.LoadErrRec[jj][0], testdata.LoadErrRec[jj][1],
		testdata.LoadErrRec[jj][2], testdata.LoadErrRec[jj][3],
		testdata.LoadErrRec[jj][4], testdata.LoadErrRec[jj][5]);
	for(kk=0;kk<15;kk++) { printf("%2x ", testdata.LoadErrFil[jj][kk]); }
	printf("\n\tDump  Add:%4x  Data:",testdata.DumpRecAdd[jj]);
	for(kk=0;kk<12;kk++) { printf("%2x ", testdata.DumpRecDat[jj][kk]); }
	printf("\n\t");
	for(kk=12;kk<28;kk++) { printf("%2x ", testdata.DumpRecDat[jj][kk]); }
	printf("\n\tFrmChk: %2x\n",testdata.MinFrmChk[jj]);
    }
	printf("\n");
  }

  /* all done, close HDF interface */

  close_rd_swepam_dloade();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
