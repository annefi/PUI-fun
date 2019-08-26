#include <stdio.h>
#include <string.h>

#include "s3_dspare_alarmcnt.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct s3s_dspare_alarmcnt a5;
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

  numrec = init_rd_s3_dspare_alarmcnt(hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica dspare_alarmcnt data\n");
      exit(-1);
  }

  ii=0;
  while((retval= read_s3_dspare_alarmcnt(&a5,ii++))!=FAIL) {
    /* printout the alarm monitoring count structure */
    printf("\n  The structure alarm monitoring count: \n");
    printf("Space craft time = %d \n",a5.sctime); 
    printf("AlarmDelay_set_Cnt=%d \n",a5.AlarmDelay_set_Cnt);
    printf("AlarmDis_Cnt=%d \n",a5.AlarmDis_Cnt);
    printf("AlarmPres_Cnt=%d \n",a5.AlarmPres_Cnt);
    printf("AlarmLV_Cnt=%d \n",a5.AlarmLV_Cnt);
    printf("AlarmV1Open_set_Cnt=%d \n",a5.AlarmV1Open_set_Cnt);
    printf("AlarmV2Open_set_Cnt=%d \n",a5.AlarmV2Open_set_Cnt);
    printf("AlarmV3Open_set_Cnt=%d \n",a5.AlarmV3Open_set_Cnt);
    printf("AlarmPC1P_min_Cnt=%d \n",a5.AlarmPC1P_min_Cnt);
    printf("AlarmPC1P_max_Cnt=%d \n",a5.AlarmPC1P_max_Cnt);
    printf("AlarmPC2P_min_Cnt=%d \n",a5.AlarmPC2P_min_Cnt);
    printf("AlarmPC2P_max_Cnt=%d \n",a5.AlarmPC2P_max_Cnt);
    printf("AlarmPC3P_min_Cnt=%d \n",a5.AlarmPC3P_min_Cnt);
    printf("AlarmPC3P_max_Cnt=%d \n",a5.AlarmPC3P_max_Cnt);
    printf("AlarmP5V_min_Cnt=%d \n",a5.AlarmP5V_min_Cnt);
    printf("AlarmP5V_max_Cnt=%d \n",a5.AlarmP5V_max_Cnt);
    printf("AlarmP5I_min_Cnt=%d \n",a5.AlarmP5I_min_Cnt);
    printf("AlarmP5I_max_Cnt=%d \n",a5.AlarmP5I_max_Cnt);
    printf("AlarmM5V_min_Cnt=%d \n",a5.AlarmM5V_min_Cnt);   
    printf("AlarmM5V_max_Cnt=%d \n",a5.AlarmM5V_max_Cnt);   
    printf("AlarmM5I_min_Cnt=%d \n",a5.AlarmM5I_min_Cnt);   
    printf("AlarmM5I_max_Cnt=%d \n",a5.AlarmM5I_max_Cnt);   
    printf("AlarmP15V_min_Cnt=%d \n",a5.AlarmP15V_min_Cnt);   
    printf("AlarmP15V_max_Cnt=%d \n",a5.AlarmP15V_max_Cnt);   
    printf("AlarmP15I_min_Cnt=%d \n",a5.AlarmP15I_min_Cnt);   
    printf("AlarmP15I_max_Cnt=%d \n",a5.AlarmP15I_max_Cnt);   
    printf("AlarmM15V_min_Cnt=%d \n",a5.AlarmM15V_min_Cnt);   
    printf("AlarmM15V_max_Cnt=%d \n",a5.AlarmM15V_max_Cnt);   
    printf("AlarmM15I_min_Cnt=%d \n",a5.AlarmM15I_min_Cnt);   
    printf("AlarmM15I_max_Cnt=%d \n",a5.AlarmM15I_max_Cnt);   
    printf("Alarm75V_min_Cnt=%d \n",a5.Alarm75V_min_Cnt);   
    printf("Alarm75V_max_Cnt=%d \n",a5.Alarm75V_max_Cnt);   
    printf("Alarm75I_min_Cnt=%d \n",a5.Alarm75I_min_Cnt);   
    printf("Alarm75I_max_Cnt=%d \n",a5.Alarm75I_max_Cnt);   
    printf("Alarm2kV_min_Cnt=%d \n",a5.Alarm2kV_min_Cnt);   
    printf("Alarm2kV_max_Cnt=%d \n",a5.Alarm2kV_max_Cnt);   
    printf("Alarm2kI_min_Cnt=%d \n",a5.Alarm2kI_min_Cnt);   
    printf("Alarm2kI_max_Cnt=%d \n",a5.Alarm2kI_max_Cnt);   
    printf("Alarm2kAV_min_Cnt=%d \n",a5.Alarm2kAV_min_Cnt);   
    printf("Alarm2kAV_max_Cnt=%d \n",a5.Alarm2kAV_max_Cnt);   
    printf("Alarm2kBV_min_Cnt=%d \n",a5.Alarm2kBV_min_Cnt);   
    printf("Alarm2kBV_max_Cnt=%d \n",a5.Alarm2kBV_max_Cnt);   
    printf("Alarm2kCV_min_Cnt=%d \n",a5.Alarm2kCV_min_Cnt);   
    printf("Alarm2kCV_max_Cnt=%d \n",a5.Alarm2kCV_max_Cnt);   
    printf("Alarm30kV_min_Cnt=%d \n",a5.Alarm30kV_min_Cnt);   
    printf("Alarm30kV_max_Cnt=%d \n",a5.Alarm30kV_max_Cnt);   
    printf("Alarm30kI_min_Cnt=%d \n",a5.Alarm30kI_min_Cnt);   
    printf("Alarm30kI_max_Cnt=%d \n",a5.Alarm30kI_max_Cnt);   
    printf("AlarmDisV_min_Cnt=%d \n",a5.AlarmDisV_min_Cnt);   
    printf("AlarmDisV_max_Cnt=%d \n",a5.AlarmDisV_max_Cnt);   
    printf("AlarmDisI_min_Cnt=%d \n",a5.AlarmDisI_min_Cnt);   
    printf("AlarmDisI_max_Cnt=%d \n",a5.AlarmDisI_max_Cnt);
  }

  /* all done, close HDF file */

  close_rd_s3_dspare_alarmcnt();
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
    










