/* print out all AD590 temperatures available in Science mode, and a selection of
 * PT103 and 0-5V Single-ended analog channels */

#include <stdio.h>
#include <string.h>

#include "schskp.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp,sd_id;
  struct SCHskpData testdata;
  int ii,jj,retval;
  int32 numrec;

  if (argc!=2)
    {
      printf("Usage: rd_hdf hdf_file\n");
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

  numrec = init_rd_schskp(hdf_fp, sd_id, "r");
  if( numrec <= 0) {
    fprintf(stderr,"No schskp data\n");
    exit(-1);
    }

  ii=0;
  while((retval= read_schskp(&testdata,ii++))!=-1) {
     fprintf(stdout," %10u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u %3u\n",
	  testdata.sc_clk,

          /* AD590 Temperature Channels -60 to +100 degrees C */
	  testdata.StarTrkTemp,         /* star tracker */
	  testdata.InstDeckTemp1,       /* near Center by SEPICA I/F */
	  testdata.InstDeckTemp2,       /* near ULEIS Elec Box */
	  testdata.InstDeckTemp3,       /* near EPAM I/F and -X edge */
	  testdata.InstDeckTemp4,       /* near +Y/-X edge */
	  testdata.InstDeckTemp5,       /* near +X/+Y edge, by SWICS I/F */
	  testdata.InstDeckTemp6,       /* near MFI, S3DPU, &SIS I/F */
	  testdata.InstDeckTemp7,       /* near -Y edge */
	  testdata.InstDeckTemp8,       /* near +X edge, by Pylon */
	  testdata.SunSnsrTemp,         /* sun sensor (-X/-Y) */
	  testdata.Cris_IntTemp1,
	  testdata.Cris_IntTemp2,
	  testdata.Sis_IntTemp1,
	  testdata.Sis_IntTemp2,
	  testdata.Swims_IntTemp,
	  testdata.Swics_IntTemp,
	  testdata.Uleis_TelTemp,
	  testdata.Uleis_AnaEleTemp,
	  testdata.Uleis_DPUTemp,
	  testdata.Sepica_IsoTanTemp,
	  testdata.S3DPU_PowSupATemp,
	  testdata.SwepamE_IntTemp,
	  testdata.SwepamI_IntTemp,
	  testdata.TermBoardFuse1Temp,
	  testdata.S3DPU_PowSupBTemp,
	  testdata.TankA1Temp,
	  testdata.TankA2Temp,
	  testdata.TankB1Temp,
	  testdata.TankB2Temp,
	  testdata.LinesATemp,
	  testdata.LinesBTemp,
	  testdata.LinesPosXTemp,
	  testdata.LinesNegXTemp,
	  testdata.Channel30,           /* Inst. Deck, position TBD */
	  testdata.data_3_1[0],         /* +X Side Panel Btw Batt and Term Bds */
	  testdata.data_3_1[5],         /* C&DH Component Oscillator */
	  testdata.data_3_1[6],         /* C&DH Component A Outside Box, near base */
	  testdata.data_3_1[7],         /* C&DH Component B Outside Box, near base */
	  testdata.data_4_1[18],        /* Solid State Recorder A PWRTEMP */
	  testdata.data_5_1[18],        /* Solid State Recorder B PWRTEMP */
	  testdata.data_6_1[16],        /* -Y Side panel near PSDE */
	  testdata.data_6_1[17],        /* -X Side Panel near digital shunt box */
	  testdata.data_7_1[16],        /* Battery 1 Top of Center Cell */
	  testdata.data_7_1[17],        /* Battery 2 top of Cell, Z-end */
	  

          /* PT103 Temperature Channels -100 to +150 degrees C*/
	  testdata.PosXSAPTemp,       /* +X Solar Array Panel Temp */
	  testdata.PosXSAPHTemp,      /* +X Solar Array Panel Hinge Temp */
	  testdata.NegXSAPTemp,       /* -X Solar Array Panel Temp */
	  testdata.NegXSAPHTemp,      /* -X Solar Array Panel Hinge Temp */
	  testdata.MagSenIntTempPosY, /* MAG +Y Sensor interface temp */
	  testdata.MagSenIntTempNegY, /* MAG -Y Sensor interface temp */
	  testdata.data_2_1[0],       /* Aft Deck, center of deck */
	  testdata.data_2_1[5],       /* +X Side Panel Temp #1 */
	  testdata.data_2_1[8],       /* +Y Side panel Temp #1 */
	  testdata.data_2_1[11],      /* -X Side panel Temp #1 */
	  testdata.data_2_1[13],      /* -Y Side panel Temp #1 */
	  

	  /* 0-5V Single-ended Analog Channels. temp range is ??? */
	  testdata.MagInTemp,         /* MAG Inboard temp */
	  testdata.MagOutTemp,        /* MAG Outboard temp */
	  testdata.Epam_LAN1,         /* EPAM LAN 1, Electronics temp thermistor */
	  testdata.Epam_LAN2A,        /* EPAM LAN 2A, Electronics temp thermistor */
	  testdata.Epam_LAN2B         /* EPAM LAN 2B, Sensor temp thermistor */

	  );
  }

  /* all done, close HDF file */

  close_rd_schskp();
  Vend(hdf_fp);
  if (SDend(sd_id)==FAIL) {
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
    
