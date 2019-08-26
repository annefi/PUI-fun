#include <stdio.h>
#include <string.h>

#include "ace_br_1dy.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp,SD_id;
  struct ace_br_1dy_avg testdata;
  int16 ii,jj,kk,retval;
  int16 nrec;

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
  if ((SD_id=SDstart(argv[1], DFACC_RDONLY))==FAIL)
      {
	fprintf(stderr, "SDstart: could not open hdf file\n");
	exit(-1);
      }

  nrec = init_rd_acebr_1dy(hdf_fp, SD_id,"r");
  if (nrec<=0) {
     exit(1);
  }

  ii=0;
  while((retval= read_acebr_1dy(&testdata,ii++))!=-1) {
	printf("%8d %4d %4d %f  %f\n", 
	    ii,testdata.ACE_epoch_time,testdata.year,testdata.DOY,testdata.H_450_SEP);
       
/*	printf("%4d time = %8d : %s", 
	    ii,testdata.ACE_epoch_time,testdata.timestr);
	printf("\tEPAM rates = %f %f %f lt=%f\n",
	    testdata.H_730_EPM, testdata.Ion_67_EPM, testdata.e_45_EPM,
	    testdata.EPM_livetime);
	printf("\tSEPICA rates = %f %f %f %f lt=%f\n",
	    testdata.H_450_SEP, testdata.H_8M_SEP, testdata.He_390_SEP,
	    testdata.He_7M_SEP, testdata.EPM_livetime);
	printf("\t %f %f %f %f\n",
	    testdata.C_13M_SEP, testdata.O_10M_SEP, testdata.MgSi_6M_SEP,
	    testdata.Fe_3M_SEP);
*/	    
  }
  printf("number of records = %d\n",nrec);

  /* all done, close HDF file */

  close_rd_acebr_1dy();
  Vend(hdf_fp);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  exit(0);
}
    
