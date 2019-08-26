#include <stdio.h>
#include <string.h>

#include "s3_dspare_cmd.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct s3s_dspare_cmd a2;
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
  
  numrec = init_rd_s3_dspare_cmd (hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica dspare_cmd data\n");
      exit(-1);
  }

  jj=0;
  while((retval= read_s3_dspare_cmd(&a2,jj++))!=FAIL) {
    /* print out the command structure */
    printf("\n  The structure command \n");
    printf("Space craft time = %d \n",a2.sctime); 
    for (ii=0;ii<55;ii++) {
      printf("SCommand1[%d]=%d \n",ii,a2.SCommand1[ii]);
      printf("SCommand2[%d]=%d \n",ii,a2.SCommand2[ii]);
      printf("SCommand3[%d]=%d \n",ii,a2.SCommand3[ii]);
     }
    printf("Pressure_set_1[%d]=%d \n",0,a2.Pressure_set_1[0]);
    printf("Pressure_set_1[%d]=%d \n",1,a2.Pressure_set_1[1]);
    printf("Pressure_set_1[%d]=%d \n",2,a2.Pressure_set_1[2]);
    printf("Pressure_set_2[%d]=%d \n",0,a2.Pressure_set_2[0]);
    printf("Pressure_set_2[%d]=%d \n",1,a2.Pressure_set_2[1]);
    printf("Pressure_set_2[%d]=%d \n",2,a2.Pressure_set_2[2]);
    printf("Pressure_set_3[%d]=%d \n",0,a2.Pressure_set_3[0]);
    printf("Pressure_set_3[%d]=%d \n",1,a2.Pressure_set_3[1]);
    printf("Pressure_set_3[%d]=%d \n",2,a2.Pressure_set_3[2]);
    printf("BITChannel_1[%d]=%d \n",0,a2.BITChannel_1[0]);
    printf("BITChannel_1[%d]=%d \n",1,a2.BITChannel_1[1]);
    printf("BITChannel_1[%d]=%d \n",2,a2.BITChannel_1[2]);
    printf("BITChannel_2[%d]=%d \n",0,a2.BITChannel_2[0]);
    printf("BITChannel_2[%d]=%d \n",1,a2.BITChannel_2[1]);
    printf("BITChannel_2[%d]=%d \n",2,a2.BITChannel_2[2]);
    printf("BITChannel_3[%d]=%d \n",0,a2.BITChannel_3[0]);
    printf("BITChannel_3[%d]=%d \n",1,a2.BITChannel_3[1]);
    printf("BITChannel_3[%d]=%d \n",2,a2.BITChannel_3[2]);
    printf("DAC0Channel_1[%d]=%d \n",0,a2.DAC0Channel_1[0]);
    printf("DAC0Channel_1[%d]=%d \n",1,a2.DAC0Channel_1[1]);
    printf("DAC0Channel_1[%d]=%d \n",2,a2.DAC0Channel_1[2]);
    printf("DAC0Channel_2[%d]=%d \n",0,a2.DAC0Channel_2[0]);
    printf("DAC0Channel_2[%d]=%d \n",1,a2.DAC0Channel_2[1]);
    printf("DAC0Channel_2[%d]=%d \n",2,a2.DAC0Channel_2[2]);
    printf("DAC0Channel_3[%d]=%d \n",0,a2.DAC0Channel_3[0]);
    printf("DAC0Channel_3[%d]=%d \n",1,a2.DAC0Channel_3[1]);
    printf("DAC0Channel_3[%d]=%d \n",2,a2.DAC0Channel_3[2]);
    printf("DAC1Channel_1[%d]=%d \n",0,a2.DAC1Channel_1[0]);
    printf("DAC1Channel_1[%d]=%d \n",1,a2.DAC1Channel_1[1]);
    printf("DAC1Channel_1[%d]=%d \n",2,a2.DAC1Channel_1[2]);
    printf("DAC1Channel_2[%d]=%d \n",0,a2.DAC1Channel_2[0]);
    printf("DAC1Channel_2[%d]=%d \n",1,a2.DAC1Channel_2[1]);
    printf("DAC1Channel_2[%d]=%d \n",2,a2.DAC1Channel_2[2]);
  }

  /* all done, close HDF file */

  close_rd_s3_dspare_cmd();
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
    









