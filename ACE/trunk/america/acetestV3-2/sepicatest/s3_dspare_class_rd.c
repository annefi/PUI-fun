#include <stdio.h>
#include <string.h>

#include "s3_dspare_class.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct s3s_dspare_class a1;
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

  if ((sd_id=SDstart(argv[1], DFACC_RDONLY))==FAIL)
    {
      fprintf(stderr, "SDstart: could not open hdf file\n");
      exit(-1);
    }

  numrec = init_rd_s3_dspare_class(hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica dspare_class data\n");
      exit(-1);
  }

  jj=0;
  while((retval= read_s3_dspare_class(&a1,jj++))!=FAIL) {
    /* print out the structure class */
    printf("\n  The structure class \n");
    printf("Space craft time = %d \n",a1.sctime); 
    for (ii=0;ii<256;ii++) {
      printf("sbitable[%d]=%d \n",ii,a1.sbitable[ii]);
    }
    for (ii=0;ii<256;ii++) {
      printf("srctable[%d]=%d \n",ii,a1.srctable[ii]);
    }
    for (ii=0;ii<480;ii++) {
      printf("sdetable[%d]=%d \n",ii,a1.sdetable[ii]);
    }
    for (ii=0;ii<16;ii++) {
      printf("scos[%d]=%d \n",ii,a1.scos[ii]);
    }
    for (ii=0;ii<32;ii++) {
      printf("scos2[%d]=%d \n",ii,a1.scos2[ii]);
    }
    printf("SlndE_Emin0=%d \n",a1.SlndE_Emin0);
    printf("SlndE_Emin1=%d \n",a1.SlndE_Emin1);
    printf("SlndE_MinClass=%f \n",a1.SlndE_MinClass);
    printf("SlndE_MaxClass=%f \n",a1.SlndE_MaxClass);
    printf("SlndE_Eoffset0=%f \n",a1.SlndE_Eoffset0);
    printf("SlndE_Eoffset1=%f \n",a1.SlndE_Eoffset1);
    printf("SlndE_E00=%f \n",a1.SlndE_E00);
    printf("SlndE_E01=%f \n",a1.SlndE_E01);
    printf("SlndE_E1=%f \n",a1.SlndE_E1);
    printf("SlndE_Cosine=%f \n",a1.SlndE_Cosine);

    printf("SlnE_Emin0=%d \n",a1.SlnE_Emin0);
    printf("SlnE_Emin1=%d \n",a1.SlnE_Emin1);
    printf("SlnE_MinClass=%f \n",a1.SlnE_MinClass);
    printf("SlnE_MaxClass=%f \n",a1.SlnE_MaxClass);
    printf("SlnE_Eoffset0=%f \n",a1.SlnE_Eoffset0);
    printf("SlnE_Eoffset1=%f \n",a1.SlnE_Eoffset1);
    printf("SlnE_E00=%f \n",a1.SlnE_E00);
    printf("SlnE_E01=%f \n",a1.SlnE_E01);
    printf("SlnE_E1=%f \n",a1.SlnE_E1);

    printf("SY_focal=%d \n",a1.SY_focal);
    printf("SY_Cosine=%f \n",a1.SY_Cosine);
    printf("SY_Y1=%f \n",a1.SY_Y1);
    printf("SQ_MaxQ=%d \n",a1.SQ_MaxQ);
    printf("SQ_Q10=%f \n",a1.SQ_Q10);
    printf("SQ_Q11=%f \n",a1.SQ_Q11);
    for (ii=0;ii<31;ii++) {
      printf("spseq[%d]=%d \n",ii,a1.spseq[ii]);
    }
  }
  /* all done, close HDF file */

  close_rd_s3_dspare_class();
  Vend(hdf_fp);
  if (SDend(sd_id)==FAIL)
    {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  exit(0);

}
    









