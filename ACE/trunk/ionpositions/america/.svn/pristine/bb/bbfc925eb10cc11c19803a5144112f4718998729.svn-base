#include <stdio.h>
#include <string.h>

#include "uleis_evnt.h"
#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct UEvntSet testdata;
  int ii,jj,kk,ll,mm,retval;

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
      fprintf(stderr, "SDstart: could not access hdf file\n");
      exit(-1);
    }

  if(init_rd_uleis_evnt(hdf_fp, SD_id, "r") <= 0) {
      fprintf(stderr,"No uleis event data\n");
      exit(-1);
  }
  

  /* read and print data */
  ii=0;
  while((retval=read_uleis_evnt(&testdata,ii))!=-1) {
     printf("ii=%4d out_sctime= %u   col_sctime= %u   QAC=%d \n", 
	    ii, testdata.output_sctime, testdata.collect_sctime, testdata.QAC);

     ii++;
     /*
     for(ll=0;ll<10;ll++) for(mm=0;mm<8;mm++) for(kk=0;kk<6;kk++) 
	  if( testdata.event[ll][mm][kk][9]!=0 &&
		  testdata.event[ll][mm][kk][10] !=0)
	      printf("%4u \t %4u\n", testdata.event[ll][mm][kk][9],
		      testdata.event[ll][mm][kk][10]);
	    */

     /*
     printf("Sample of events: \n");
     for(ll=0;ll<10;ll++) {
	printf("Spin = %2u Sector=%2u\n",ll,0);
	for(kk=0;kk<6;kk++) { 
	    for(jj=0;jj<14;jj++)
		printf("%4u ", testdata.event[ll][0][kk][jj]);
	    printf("\n");
	}
	printf("\n");
     }
  */

  }

  /* all done, close HDF interface */

  close_rd_uleis_evnt();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL)
    {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }
  exit(0);
}
    
