/* get_aosr_struct.c - for a given spacecraft clock value, obtain the complete */
/* set of ACE attitude/orbit data, from the ACE_ANCIL.HDF database. */

/* Note: the function init_ACEancillary() reads the complete database into memory. */
/* It should only be called once */

/* Note: the function ACE_aosr() returns attitude/orbit data corresponding to a */
/* given spacecraft clock. The function interpolates between data points from the */
/* ACE_ANCIL.HDF database */

#include <stdio.h>
#include "hdfi.h"
#include "aosr.h"

main(argc, argv)
int argc;
char *argv[];
{
  float64 scclock;     /* use float64 for spacecraft clock, since some */
                       /* ancillary functions need sub-second resolution */
  struct attorb_entry aosr_struct;
  int32 retval;

  int32 ACE_aosr();           /* function in ancil_subs.c */
  int32 init_ACEancillary();  /* function in ancil_subs.c */
  void print_aosr();

  if (argc!=3) {
      printf("Usage: get_aosr_struct hdf_file scclock\n");
      exit(1);
  }
  scclock = atof(argv[2]);

  /* load the data from the HDF file */
  /* init_ACEancillary() exits if there is an error */

  init_ACEancillary(argv[1]);

  /* get the aosr structure corresponding to the spacecraft clock */
  if((retval=ACE_aosr(scclock, &aosr_struct)) == -1){
     fprintf(stdout,"scclock out of bounds\n");
  }
  else {
     if(retval==1)
	fprintf(stdout,"Warning: spacecraft maneuvering\n");
     print_aosr(aosr_struct);
  }

  exit(0);
}
    
void print_aosr(struct attorb_entry aosr)
{
    fprintf(stdout,"\n");
    fprintf(stdout,"time = %lu\n",aosr.sctime);
    fprintf(stdout,"ISTP time = %ld, %ld\n",aosr.istp_time[0],aosr.istp_time[1]);
    /* new code */
    fprintf(stdout,"UT_time = %s\n",aosr.UT_time);
    fprintf(stdout,"status = %d\n",aosr.state);
    fprintf(stdout,"attJ   = %22.10e %22.10e %22.10e\n",
        aosr.att_J2GCI[0],aosr.att_J2GCI[1],aosr.att_J2GCI[2]);
    fprintf(stdout,"attRTN = %22.10e %22.10e %22.10e\n",
        aosr.att_RTN[0],aosr.att_RTN[1],aosr.att_RTN[2]);
    fprintf(stdout,"attGSE = %22.10e %22.10e %22.10e\n",
        aosr.att_GSE[0],aosr.att_GSE[1],aosr.att_GSE[2]);
    fprintf(stdout,"attGSM = %22.10e %22.10e %22.10e\n",
        aosr.att_GSM[0],aosr.att_GSM[1],aosr.att_GSM[2]);
    fprintf(stdout,"attHSEb = %22.10e %22.10e %22.10e\n",
        aosr.att_HSEb[0],aosr.att_HSEb[1],aosr.att_HSEb[2]);
    fprintf(stdout,"attHS = %22.10e %22.10e %22.10e\n",
        aosr.att_HS[0],aosr.att_HS[1],aosr.att_HS[2]);

    fprintf(stdout,"spinJ  = %22.10e %22.10e %22.10e\n",
        aosr.spin_J2GCI[0],aosr.spin_J2GCI[1],aosr.spin_J2GCI[2]);
    fprintf(stdout,"spinRTN= %22.10e %22.10e %22.10e\n",
        aosr.spin_RTN[0],aosr.spin_RTN[1],aosr.spin_RTN[2]);
    fprintf(stdout,"spinGSE= %22.10e %22.10e %22.10e\n",
        aosr.spin_GSE[0],aosr.spin_GSE[1],aosr.spin_GSE[2]);

    fprintf(stdout,"posJ   = %22.10e %22.10e %22.10e\n",
        aosr.pos_J2GCI[0],aosr.pos_J2GCI[1],aosr.pos_J2GCI[2]);
    fprintf(stdout,"posGSE = %22.10e %22.10e %22.10e\n",
        aosr.pos_GSE[0],aosr.pos_GSE[1],aosr.pos_GSE[2]);
    fprintf(stdout,"posGSM = %22.10e %22.10e %22.10e\n",
        aosr.pos_GSM[0],aosr.pos_GSM[1],aosr.pos_GSM[2]);
    fprintf(stdout,"posHSEb = %22.10e %22.10e %22.10e\n",
        aosr.pos_HSEb[0],aosr.pos_HSEb[1],aosr.pos_HSEb[2]);
    fprintf(stdout,"posHS = %22.10e %22.10e %22.10e\n",
        aosr.pos_HS[0],aosr.pos_HS[1],aosr.pos_HS[2]);
    fprintf(stdout,"velJ   = %22.10e %22.10e %22.10e\n",
        aosr.vel_J2GCI[0],aosr.vel_J2GCI[1],aosr.vel_J2GCI[2]);
    fprintf(stdout,"velGSE = %22.10e %22.10e %22.10e\n",
        aosr.vel_GSE[0],aosr.vel_GSE[1],aosr.vel_GSE[2]);
    fprintf(stdout,"velGSM = %22.10e %22.10e %22.10e\n",
        aosr.vel_GSM[0],aosr.vel_GSM[1],aosr.vel_GSM[2]);
    fprintf(stdout,"velHSEb = %22.10e %22.10e %22.10e\n",
        aosr.vel_HSEb[0],aosr.vel_HSEb[1],aosr.vel_HSEb[2]);
    fprintf(stdout,"velHS = %22.10e %22.10e %22.10e\n",
        aosr.vel_HS[0],aosr.vel_HS[1],aosr.vel_HS[2]);
    fprintf(stdout,"\n");
}

