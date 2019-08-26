#include <stdio.h>
#include <string.h>

#include "mag_hskp.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp,sd_id;
  struct MagHskpSet testdata;
  int ii,jj,retval;

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

  if( init_rd_mag_hskp(hdf_fp, sd_id, "r") <= 0) {
    fprintf(stderr,"No mag house keeping data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_mag_hskp(&testdata,ii++))!=-1) {
	  printf("%4d sc clock = %8d, QAC = %d\n", ii,
	  testdata.sctime_readout, testdata.QAC);
	  for(jj=0;jj<16;jj++)
	     printf("%1u ",testdata.QACarr[jj]);
	  printf("\n");

      /*
	  printf("  %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %4x\n",
	    testdata.st1a, testdata.st2a, testdata.st3,    testdata.st4, 
	    testdata.st5,  testdata.st6,  testdata.pctemp, testdata.cmon, 
	    testdata.hk1,  testdata.hk2,  testdata.hk3,    testdata.hk4,
	    testdata.hk5,  testdata.sync, testdata.st);
    if(ii%20==0) {
	printf("                          ");
	printf("---Status-------  pc cmn ----HK-------\n");
	printf("rec #                     ");
	printf("1a 2a  3  4  5  6 tmp    1  2  3  4  5 sync st\n");
      }
      */
  }

      /* all done, close HDF file */

  close_rd_mag_hskp();
  fprintf(stderr,"VS detached \n");
  Vend(hdf_fp);
  fprintf(stderr,"VS ended \n");
  if (SDend(sd_id)==FAIL) {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  fprintf(stderr,"file closed \n");
  

  exit(0);
}
    
