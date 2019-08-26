#include <stdio.h>
#include <string.h>

#include "uleis_rate.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct URateSet testdata;
  int ii,jj,kk,ll,retval;
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

  numrec = init_rd_uleis_rate(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No uleis rate data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_uleis_rate(&testdata,ii))!=-1) {
    printf("\nii=%4d sctime=%10u QAC=%3d \n", 
	    ii++, testdata.output_sctime, testdata.QAC);

    for(ll=0;ll<U_SPINPRS;ll++) {
	printf("Matrix rates: ");
	printf("Spins %1u:%1u\n",ll*2,ll*2+1);
	for(jj=0;jj<U_MTRX_RATE_SIZE;jj++) {
	    for(kk=0;kk<U_SECTRS;kk++) 
		printf("%3u ", testdata.Matrx[jj][ll][kk]);
	    printf("\n"); 
	    }
	printf("\n"); 
    }


    for(ll=0;ll<U_SPINPRS;ll++) {
	printf("Matrix pair rates: ");
	printf("Spins %1u:%1u\n",ll*2,ll*2+1);
	for(jj=0;jj<U_MTRX_PRS_RATE_SIZE;jj++) {
	    for(kk=0;kk<U_SECTRS;kk++) 
		printf("%3u ", testdata.Matrx_prs[jj][ll][kk]);
	    printf("\n"); 
	    }
	printf("\n"); 
    }

    for(ll=0;ll<U_SPINPRS;ll++) {
	printf("Singles rates: ");
	printf("Spins %1u:%1u\n",ll*2,ll*2+1);
	for(jj=0;jj<U_SNGL_RATE_SIZE;jj++) { 
	    for(kk=0;kk<U_SECTRS;kk++) 
		printf("%6u ", testdata.Single[jj][ll][kk]); 
	    printf("\n"); 
	    }
	printf("\n"); 
    }

  }

  /* all done, close HDF interface */

  close_rd_uleis_rate();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    







