#include <stdio.h>
#include <string.h>

#include "uleis_stat_tlm.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct UStatTLMSet testdata;
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

  if( init_rd_uleis_stat_tlm(hdf_fp, SD_id, "r") <= 0) {
    fprintf(stderr,"No uleis stat tlm data\n");
    exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_uleis_stat_tlm(&testdata,ii))!=-1) {
    printf("ii=%4d sctime=%10u offset time=%3d QAC=%d \n",ii++, testdata.output_sctime, testdata.stattlmtime_offset, testdata.QAC);
    printf("Sample of status TLM:\n");
    for(jj=0;jj<25;jj++)
	printf("%2x ",testdata.StatusTLM[jj]);
    printf("\n\n");

  }

  /* all done, close HDF interface */

  close_rd_uleis_stat_tlm();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
