#include <stdio.h>
#include <string.h>

#include "s3_dspare_alarm.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, sd_id;
  struct s3s_dspare_alarm a4;
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

  numrec = init_rd_s3_dspare_alarm(hdf_fp, sd_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica dspare_alarm data\n");
      exit(-1);
  }

  ii=0;
  while((retval= read_s3_dspare_alarm(&a4,ii++))!=FAIL) {

    /* printout the alarm monitoring structure */
    printf("Space craft time = %d \n",a4.sctime); 
    printf("AlarmDelay_set=%d \n",a4.AlarmDelay_set);
    printf("AlarmDis=%d \n",a4.AlarmDis);
    printf("AlarmPres=%d \n",a4.AlarmPres);
    printf("AlarmLV=%d \n",a4.AlarmLV);
    printf("AlarmV1Open_set=%d \n",a4.AlarmV1Open_set);
    printf("AlarmV2Open_set=%d \n",a4.AlarmV2Open_set);
    printf("AlarmV3Open_set=%d \n",a4.AlarmV3Open_set);
    printf("AlarmPC1P_min=%d \n",a4.AlarmPC1P_min);
    printf("AlarmPC1P_max=%d \n",a4.AlarmPC1P_max);
    printf("AlarmPC2P_min=%d \n",a4.AlarmPC2P_min);
    printf("AlarmPC2P_max=%d \n",a4.AlarmPC2P_max);
    printf("AlarmPC3P_min=%d \n",a4.AlarmPC3P_min);
    printf("AlarmPC3P_max=%d \n",a4.AlarmPC3P_max);
    printf("AlarmP5V_min=%d \n",a4.AlarmP5V_min);
    printf("AlarmP5V_max=%d \n",a4.AlarmP5V_max);
    printf("AlarmP5I_min=%d \n",a4.AlarmP5I_min);
    printf("AlarmP5I_max=%d \n",a4.AlarmP5I_max);
    printf("AlarmM5V_min=%d \n",a4.AlarmM5V_min);   
    printf("AlarmM5V_max=%d \n",a4.AlarmM5V_max);   
    printf("AlarmM5I_min=%d \n",a4.AlarmM5I_min);   
    printf("AlarmM5I_max=%d \n",a4.AlarmM5I_max);   
    printf("AlarmP15V_min=%d \n",a4.AlarmP15V_min);   
    printf("AlarmP15V_max=%d \n",a4.AlarmP15V_max);   
    printf("AlarmP15I_min=%d \n",a4.AlarmP15I_min);   
    printf("AlarmP15I_max=%d \n",a4.AlarmP15I_max);   
    printf("AlarmM15V_min=%d \n",a4.AlarmM15V_min);   
    printf("AlarmM15V_max=%d \n",a4.AlarmM15V_max);   
    printf("AlarmM15I_min=%d \n",a4.AlarmM15I_min);   
    printf("AlarmM15I_max=%d \n",a4.AlarmM15I_max);   
    printf("Alarm75V_min=%d \n",a4.Alarm75V_min);   
    printf("Alarm75V_max=%d \n",a4.Alarm75V_max);   
    printf("Alarm75I_min=%d \n",a4.Alarm75I_min);   
    printf("Alarm75I_max=%d \n",a4.Alarm75I_max);   
    printf("Alarm2kV_min=%d \n",a4.Alarm2kV_min);   
    printf("Alarm2kV_max=%d \n",a4.Alarm2kV_max);   
    printf("Alarm2kI_min=%d \n",a4.Alarm2kI_min);   
    printf("Alarm2kI_max=%d \n",a4.Alarm2kI_max);   
    printf("Alarm2kAV_min=%d \n",a4.Alarm2kAV_min);   
    printf("Alarm2kAV_max=%d \n",a4.Alarm2kAV_max);   
    printf("Alarm2kBV_min=%d \n",a4.Alarm2kBV_min);   
    printf("Alarm2kBV_max=%d \n",a4.Alarm2kBV_max);   
    printf("Alarm2kCV_min=%d \n",a4.Alarm2kCV_min);   
    printf("Alarm2kCV_max=%d \n",a4.Alarm2kCV_max);   
    printf("Alarm30kV_min=%d \n",a4.Alarm30kV_min);   
    printf("Alarm30kV_max=%d \n",a4.Alarm30kV_max);   
    printf("Alarm30kI_min=%d \n",a4.Alarm30kI_min);   
    printf("Alarm30kI_max=%d \n",a4.Alarm30kI_max);   
    printf("AlarmDisV_min=%d \n",a4.AlarmDisV_min);   
    printf("AlarmDisV_max=%d \n",a4.AlarmDisV_max);   
    printf("AlarmDisI_min=%d \n",a4.AlarmDisI_min);   
    printf("AlarmDisI_max=%d \n",a4.AlarmDisI_max);   
  }

  /* all done, close HDF file */

  close_rd_s3_dspare_alarm();
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
    









