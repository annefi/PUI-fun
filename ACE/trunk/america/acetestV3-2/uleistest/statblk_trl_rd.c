#include <stdio.h>
#include <string.h>

#include "uleis_statblk_trl.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct UStatBlkTrlSet testdata;
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

  if( init_rd_uleis_statblk_trl(hdf_fp, SD_id, "r") <= 0) {
    fprintf(stderr,"No uleis stablk trl data\n");
    exit(-1);
  }

  /* read and print data */
  printf("Sample of status block and trailer\n");
  ii=0;
  while((retval=read_uleis_statblk_trl(&testdata,ii))!=-1) {
  printf("ii=%4d out_sctime=%10u QAC=%4d Sync=%4x Spn1mfc=%6d",
	    ii, testdata.output_sctime, testdata.QAC,
	    testdata.Sync,testdata.Spn1MinFrCnt);
  printf("\n");
  ii++;
  }

  /* all done, close HDF interface */

  close_rd_uleis_statblk_trl();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
