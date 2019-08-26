#include <stdio.h>
#include <string.h>

#include "s3_spha.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct spha testdata;
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
  if ((SD_id=SDstart(argv[1], DFACC_RDONLY))==FAIL)
    {
      fprintf(stderr, "SDstart: could not open hdf file\n");
      exit(-1);
    }

  numrec = init_rd_s3_spha(hdf_fp, SD_id, "r");
  if(numrec <= 0) {
      fprintf(stderr,"No sepica s3_pha data\n");
      exit(-1);
  }

  /* read and print data */
  ii=0;
  while((retval=read_s3_spha(&testdata,ii))!=-1) {
    printf("
    \nsctime_readout= %10u sc_coll= %14.3f qac= %2d concat= %2d nevts= %2d edb= %2d\n", 
	    testdata.sctime_readout, testdata.sctime_collection,
	    testdata.QAC,testdata.concat,testdata.numevts,testdata.edb);
    ii++;
    printf("Rg Sec Fn Sy  dZ Eg  E dEg  Eg    Y\n");
    for(jj=0;jj<testdata.numevts;jj++) { 
       printf("%2d %2d %2d %2d %4d %1x %4d %1x %4d %4d\n",
       testdata.range[jj],testdata.sector[jj],testdata.fan[jj],
       testdata.sys[jj],testdata.dZ[jj],testdata.Eg[jj],
       testdata.E[jj],testdata.dEg[jj],testdata.dE[jj],
       testdata.Y[jj]);
    }
  }

  /* all done, close HDF interface */

  close_rd_s3_spha();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
