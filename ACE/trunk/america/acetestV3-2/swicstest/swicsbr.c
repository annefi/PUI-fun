#include <stdio.h>
#include <string.h>

#include "swics_br.h"
#include "df.h"
#include "cfortran.h"

              PROTOCCALLSFSUB0(SWICS_PARMS, swics_parms)
#define SWICS_BR() CCALLSFSUB0(SWICS_PARMS, swics_parms)

typedef struct {
    int32 time_sec[6], DPPS[60][6];
    int32 EDB[60][6], RATE[5][60][6];
} SWICS_IN_DEF;

#define Swics_in COMMON_BLOCK(INPUT,input)
COMMON_BLOCK_DEF(SWICS_IN_DEF, Swics_in);

typedef struct {
    float32 V_He, Vth_He, Vth_He_Err, Vth_O6, Vth_O6_Err;
    float32 CorTemp, CorTemp_Err, Den_He_O, Den_He_O_Err;
    float32 Den_Fe_O, Den_Fe_O_Err, Mark;
} SWICS_OUT_DEF;

#define Swics_out COMMON_BLOCK(OUTPUT,output)
COMMON_BLOCK_DEF(SWICS_OUT_DEF, Swics_out);

SWICS_IN_DEF Swics_in;
SWICS_OUT_DEF Swics_out;

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct Swics_br testdata;
  int ii,jj,kk,retval;
  static int cyclim[15] = {5,4,5,4,5,4,5,5,4,4,4,5,5,4,5};

  int SRcycle=0, cycnum=0;
  Swics_in.time_sec[5]=0;

  if (argc!=2) { 
      printf("Usage: %s hdf_file\n",argv[0]);
      exit(1);
    }

  /* open hdf input file */

  if ((hdf_fp=Hopen(argv[1], DFACC_RDONLY, 0))==FAIL) {
      fprintf(stderr, "Hopen: could not open hdf file\n");
      exit(-1);
    }
  Vstart(hdf_fp);
  if ((SD_id=SDstart(argv[1], DFACC_RDONLY))==FAIL) {
      fprintf(stderr, "SDstart: could not open hdf file\n");
      exit(-1);
    }

 if( init_rd_swics_br(hdf_fp, SD_id, "r") <= 0) {
     fprintf(stderr,"No swics browse data\n");
         exit(-1);
 }
 

  /* read and print data */
  ii=0;
  while((retval=read_swics_br(&testdata,ii++))!=-1) {
/*
    printf("ii=%4d %10u %10u SR:%d\n", 
	ii, testdata.bin_start, testdata.bin_end, SRcycle);
*/

    Swics_in.time_sec[SRcycle]=testdata.bin_start;
    printf("binstart= %d, SR= %2d\n",Swics_in.time_sec[SRcycle],SRcycle);
    for(jj=0;jj<60;jj++) {
	Swics_in.EDB[jj][SRcycle] = testdata.edb[jj];
	Swics_in.DPPS[jj][SRcycle] = testdata.dpps[jj];
	/* Should not have to divide by 8 for real data */
	for(kk=0;kk<5;kk++)
	    Swics_in.RATE[kk][jj][SRcycle] = testdata.rate[kk][jj];

        printf("edb= %3d dppsvolts= %3d  rates= %7d %7d %7d %7d %7d\n",
        Swics_in.EDB[jj][SRcycle], Swics_in.DPPS[jj][SRcycle],
        Swics_in.RATE[0][jj][SRcycle], Swics_in.RATE[1][jj][SRcycle],
        Swics_in.RATE[2][jj][SRcycle], Swics_in.RATE[3][jj][SRcycle],
        Swics_in.RATE[4][jj][SRcycle]);

    }

    SRcycle++;
    if(SRcycle==5) {
	/* printf(" %d : %d \n", cycnum, SRcycle); */
	SWICS_BR();
	SRcycle=0;
	printf("V_He = %f\n",Swics_out.V_He);
	printf("Vth_He = %f~%f\n",Swics_out.Vth_He,Swics_out.Vth_He_Err);
	printf("Vth_O6 = %f~%f\n",Swics_out.Vth_O6,Swics_out.Vth_O6_Err);
	printf("Cor_temp = %f~%f\n",Swics_out.CorTemp,Swics_out.CorTemp_Err);
	printf("Den_He_O = %f~%f\n",Swics_out.Den_He_O,Swics_out.Den_He_O_Err);
	printf("Den_Fe_O = %f~%f\n\n",Swics_out.Den_Fe_O,Swics_out.Den_Fe_O_Err);
	cycnum++;
        Swics_in.time_sec[4]=0;
    }
  }


  /* all done, close HDF interface */

  close_rd_swics_br();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
