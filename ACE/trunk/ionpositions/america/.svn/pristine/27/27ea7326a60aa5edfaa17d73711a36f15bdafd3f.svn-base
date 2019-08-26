#include <stdio.h>
#include <string.h>

#include "epam_br.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id, AN_id;
  struct Epam_br testdata;
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

  if( init_rd_epam_br(hdf_fp, SD_id,"r") <= 0) {
    fprintf(stderr,"No epam browse data\n");
    exit(-1);
    }

  /* read and print data */
  ii=0;
  while((retval=read_epam_br(&testdata,ii++))!=-1) {
	printf("ii=%4d %f %f lt=%f\n", 
	    ii, testdata.bin_start, testdata.bin_end , testdata.EPAM_livetime);
	printf("\tP3:%9.3e fp6p:%9.3e W1:%9.3e W1/fp6p: %6.3f\n",
	    testdata.P3, testdata.fp6p, testdata.W1, testdata.W1/testdata.fp6p);
	/*
	printf("\tP1:%9.3e P3:%9.3e P5:%9.3e P7:%9.3e\n",
	    testdata.P1, testdata.P3, testdata.P5, testdata.P7);
	*/
  }

  /* all done, close HDF interface */

  close_rd_epam_br();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
