#include <stdio.h>
#include <string.h>

#include "s3_sdiag.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct sdiag testdata;
  int ii,jj,kk,retval;
  int32 numrec;

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

  numrec = init_rd_s3_sdiag(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica diag data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_s3_sdiag(&testdata,ii))!=-1) {
    printf("ii=%4d T=%10u Tcoll=%14.3f Q=%3d con=%d nevt=%d edb=%d\n", 
	ii++, testdata.sctime_readout, testdata.sctime_collection,testdata.QAC, 
	testdata.concat, testdata.numevts, testdata.edb);

    for(jj=0;jj<SEP_DIAG_CYCLEN;jj++) {
	if(jj%11==0) printf("   ");
	printf("%3x ",testdata.DIAG[0][jj]);
	if(jj%11==10) printf("\n");
    }
    printf("\n");
    for(jj=0;jj<SEP_DIAG_CYCLEN;jj++) {
	if(jj%11==0) printf("   ");
	printf("%3x ",testdata.DIAG[1][jj]);
	if(jj%11==10) printf("\n");
    }
    printf("\n");
    for(jj=0;jj<SEP_DIAG_CYCLEN;jj++) {
	if(jj%11==0) printf("   ");
	printf("%3x ",testdata.DIAG[2][jj]);
	if(jj%11==10) printf("\n");
    }
    printf("\n");
    for(jj=0;jj<SEP_DIAG_CYCLEN;jj++) {
	if(jj%11==0) printf("   ");
	printf("%3x ",testdata.DIAG[3][jj]);
	if(jj%11==10) printf("\n");
    }
    printf("\n");
  }
  

  /* all done, close HDF interface */

  close_rd_s3_sdiag();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL) {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      HEprint(stderr,0);
      exit(-1);
    }
  exit(0);
}
    
