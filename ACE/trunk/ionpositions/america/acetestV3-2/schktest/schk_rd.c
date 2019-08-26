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
/*	  printf("\nsc clock = %8d MainBusVolt=%u\nSCIPhaAng\n",
	  testdata.sc_clk,testdata.MainBusVolt);
	  for(jj=0;jj<16;jj++) printf(" %4x", testdata.SCIPhaAng[jj]);
	  printf("\nFormatID\n");
	  for(jj=0;jj<16;jj++)printf(" %2x",(0xf0&testdata.FormatID[jj])>>4);
	  printf("\nSunSenTop\n");
	  for(jj=0;jj<16;jj++)printf(" %1x",(0x08&testdata.FormatID[jj])>>3);
*/	  
	  printf("\nSunSenSide\n");
	  for(jj=0;jj<16;jj++)printf(" %1x",(0x04&testdata.FormatID[jj])>>2);
/*	  printf("\nSunSensor\n");
	  for(jj=0;jj<11;jj++)printf(" %2x",(0xff00&testdata.SunSensor[jj])>>8);
	  printf("   ");
	  for(jj=0;jj<11;jj++)printf(" %2x",(0x00ff&testdata.SunSensor[jj]));
*/	  
/*	  printf("\n  %4x %4x   %4x %4x %4x   %4x %4x %4x   %4x\n",
	   testdata.SunPulPhaAng0 ,testdata.SunPulPhaAng8, 
	   testdata.LastSPTT0[0], testdata.LastSPTT0[1], testdata.LastSPTT0[2],
	   testdata.LastSPTT8[0], testdata.LastSPTT8[1], testdata.LastSPTT8[2],
	   testdata.ADCPhaAng);
*/	   
  }
  printf("Number of records = %d\n",numrec);

  /* all done, close HDF file */

  close_rd_schskp();
  fprintf(stderr,"VS detached \n");
  Vend(hdf_fp);
  fprintf(stderr,"VS ended \n");
  if (SDend(sd_id)==FAIL) {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  fprintf(stderr,"file closed \n");
  

  exit(0);
}
    
