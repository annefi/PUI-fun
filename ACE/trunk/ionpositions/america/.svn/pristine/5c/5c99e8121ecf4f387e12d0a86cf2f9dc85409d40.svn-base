#include <stdio.h>
#include <string.h>

#include "s3_dspare_contr.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct s3s_dspare_contr a3;
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

  numrec = init_rd_s3_dspare_contr(hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica dspare_contr data\n");
      exit(-1);
  }

  jj=0;
  while((retval= read_s3_dspare_contr(&a3,jj++))!=FAIL) {
    /* print out  the control structure */
    printf("\n  The structure control \n");
    printf("Space craft time = %d \n",a3.sctime); 
    for (ii=0;ii<3;ii++) {
      printf("Mode[%d]=%d \n",ii,a3.Mode[ii]);
      printf("Delay[%d]=%d \n",ii,a3.Delay[ii]);
      printf("Lim30k[%d]=%d \n",ii,a3.Lim30k[ii]);
      printf("Lim30k_delta[%d]=%d \n",ii,a3.Lim30k_delta[ii]);
      printf("Lim2k[%d]=%d \n",ii,a3.Lim2k[ii]);
      printf("Lim2k_delta[%d]=%d \n",ii,a3.Lim2k_delta[ii]);
      printf("Lim75[%d]=%d \n",ii,a3.Lim75[ii]);
      printf("Lim75_delta[%d]=%d \n",ii,a3.Lim75_delta[ii]);
      printf("PhaThres_low[%d]=%d \n",ii,a3.PhaThres_low[ii]);
      printf("PhaThres_hi[%d]=%d \n",ii,a3.PhaThres_hi[ii]);
      printf("PressCtrl_1[%d]=%d \n",ii,a3.PressCtrl_1[ii]);
      printf("PressCtrl_2[%d]=%d \n",ii,a3.PressCtrl_2[ii]);
      printf("PressCmd_1[%d]=%d \n",ii,a3.PressCmd_1[ii]);
      printf("PressCmd_2[%d]=%d \n",ii,a3.PressCmd_2[ii]);
      printf("PressCmd_3[%d]=%d \n",ii,a3.PressCmd_3[ii]);
    }
    for (ii=0;ii<3;ii++) {
      printf("Mode_Cmd[%d]=%d \n",ii,a3.Mode_Cmd[ii]);
      printf("Delay_Cmd[%d]=%d \n",ii,a3.Delay_Cmd[ii]);
      printf("Lim30k_Cmd[%d]=%d \n",ii,a3.Lim30k_Cmd[ii]);
      printf("Lim30k_delta_Cmd[%d]=%d \n",ii,a3.Lim30k_delta_Cmd[ii]);
      printf("Lim2k_Cmd[%d]=%d \n",ii,a3.Lim2k_Cmd[ii]);
      printf("Lim2k_delta_Cmd[%d]=%d \n",ii,a3.Lim2k_delta_Cmd[ii]);
      printf("Lim75_Cmd[%d]=%d \n",ii,a3.Lim75_Cmd[ii]);
      printf("Lim75_delta_Cmd[%d]=%d \n",ii,a3.Lim75_delta_Cmd[ii]);
      printf("PhaThres_low_Cmd[%d]=%d \n",ii,a3.PhaThres_low_Cmd[ii]);
      printf("PhaThres_hi_Cmd[%d]=%d \n",ii,a3.PhaThres_hi_Cmd[ii]);
      printf("PressCtrl_1_Cmd[%d]=%d \n",ii,a3.PressCtrl_1_Cmd[ii]);
      printf("PressCtrl_2_Cmd[%d]=%d \n",ii,a3.PressCtrl_2_Cmd[ii]);
      printf("PressCmd_1_Cmd[%d]=%d \n",ii,a3.PressCmd_1_Cmd[ii]);
      printf("PressCmd_2_Cmd[%d]=%d \n",ii,a3.PressCmd_2_Cmd[ii]);
      printf("PressCmd_3_Cmd[%d]=%d \n",ii,a3.PressCmd_3_Cmd[ii]);
    }
  }

  /* all done, close HDF file */

  close_rd_s3_dspare_contr();
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
    









