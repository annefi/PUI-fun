/* this program demonstrates how to access two different hdf data files */
/* from the same C program */
#include <stdio.h>
#include <string.h>

#include "uleis_hskp.h"
#include "uleis_br_out.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 l1_fp, br_fp, l1_SD_id, br_SD_id;
  struct UHskpSet l1data;
  struct Uleis_br_out brdata;
  int ii,jj,kk,retval;
  int32 l1_numrec, br_numrec;

  if (argc!=3)
    {
      printf("Usage: %s l1_hdf_file raw_browse_hdf_file\n",argv[0]);
      exit(1);
    }

  /* open level1 input file */

  if ((l1_fp=Hopen(argv[1], DFACC_RDONLY, 0))==FAIL)
    {
      fprintf(stderr, "Hopen: could not open level 1 hdf file\n");
      exit(-1);
    }
  Vstart(l1_fp);
  if ((l1_SD_id=SDstart(argv[1], DFACC_RDONLY))==FAIL)
    {
      fprintf(stderr, "SDstart: could not open level 1 hdf file\n");
      exit(-1);
    }

  l1_numrec = init_rd_uleis_hskp(l1_fp, l1_SD_id, "r");
  if(l1_numrec <= 0) {
      fprintf(stderr,"No uleis hskp data\n");
      exit(-1);
  }

  /* open browse input file */

  if ((br_fp=Hopen(argv[2], DFACC_RDONLY, 0))==FAIL)
    {
      fprintf(stderr, "Hopen: could not open browse hdf file\n");
      exit(-1);
    }
  Vstart(br_fp);
  if ((br_SD_id=SDstart(argv[2], DFACC_RDONLY))==FAIL)
    {
      fprintf(stderr, "SDstart: could not open browse hdf file\n");
      exit(-1);
    }

  br_numrec = init_rd_uleis_br_out(br_fp, br_SD_id, "r");
  if(br_numrec <= 0) {
      fprintf(stderr,"No uleis raw browse data\n");
      exit(-1);
  }

  /* read and print housekeeping data */
  printf("Sample of ULEIS housekeeping:\n");
  ii=0;
  while((retval=read_uleis_hskp(&l1data,ii))!=-1) {
    printf("ii=%4d out_sctime=%10u col_sctime=%10u QAC=%3d chksumchk=%d\n", 
	   ii++, l1data.output_sctime, l1data.collect_sctime,
	   l1data.QAC,l1data.chk_sum_chk);
  }

  /* read and print browse data */  
  ii=0;
  while((retval= read_uleis_br_out(&brdata,ii))!=-1) {
     printf("%4d bin_start=%f bin_end=%f\n", ii,brdata.bin_start ,brdata.bin_end);
     printf("     ULEIS_livetime=%f\n", brdata.ULEIS_livetime);
     for (jj=0; jj<9; jj++){
       printf("      rate assignment= %2d          rates=%12.3f\n", brdata.rate_assign[jj], brdata.brws_rates[jj]);
     }
     printf("\n");
     ii++;
  }

  /* all done, close HDF interface */

  close_rd_uleis_hskp();
  Vend(l1_fp);
  SDend(l1_SD_id);
  if (Hclose(l1_fp)==FAIL) {
      fprintf(stderr, "Hclose: could not close level 1 hdf file\n");
      exit(-1);
  }

  close_rd_uleis_br_out();
  Vend(br_fp);
  SDend(br_SD_id);
  if (Hclose(br_fp)==FAIL) {
      fprintf(stderr, "Hclose: could not close browse hdf file\n");
      exit(-1);
  }

exit(0);
}
    
