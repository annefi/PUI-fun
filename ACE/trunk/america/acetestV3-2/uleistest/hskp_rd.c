#include <stdio.h>
#include <string.h>

#include "uleis_hskp.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct UHskpSet testdata;
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

  numrec = init_rd_uleis_hskp(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No uleis hskp data\n");
      exit(-1);
  }

  /* read and print data */
  printf("Sample of ULEIS housekeeping:\n");
  ii=0;
  while((retval=read_uleis_hskp(&testdata,ii))!=-1) {
    printf("ii=%4d out_sctime=%10u col_sctime=%10u QAC=%3d chksumchk=%d\n", 
	   ii++, testdata.output_sctime, testdata.collect_sctime,
	   testdata.QAC,testdata.chk_sum_chk);
    printf("	   dumps this data block=%4d \n",testdata.dump_flg[128]);
    if (testdata.dump_flg[128]<0)
      for (jj=0; jj<128; jj++)
	printf("jj=%3d %2d ",jj,testdata.dump_flg[jj]);
    printf("	status TLM's this data block=%4d\n",testdata.stat_tlm_flg[128]);

/*
    printf("Instrument Deck Temp: ");
    for(jj=0;jj<8;jj++) 
	printf("%4d ",testdata.DeckTemp[jj]);
*/
    printf("\n");
  }

  /* all done, close HDF interface */

  close_rd_uleis_hskp();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
