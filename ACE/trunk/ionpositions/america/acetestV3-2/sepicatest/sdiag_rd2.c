#include <stdio.h>
#include <string.h>

#if 0
#include "s3_sdiag.h"
#else
/* $Id: s3_sdiag.h,v 1.3 1997/10/26 19:29:25 jeff Exp $	     */
#include "hdfi.h"

#define SEP_DIAG_CYCLEN    88
#define SEP_DIAG_CYCPERSR  60

struct sdiag{
	uint32 sctime_readout;	/* 32 bit spacecraft time  */
	uint32 sctime_collection;/* 32 bit spacecraft time  */

	uint32 QAC;	/* number of missing frames in this SR */

	uint32 elements; /* Number of diag events in this structure. */
		     /* Should always be 240 when concat is not 1. */

	uint8  concat; /* Sequence number for this struture will be */
		       /* greater than one for cases where the number of */
		       /* events exceeds the standard size.  In these cases */
		       /* concat will count down from N to 1, where N is */
			/* the total number of spha structure in this SR. */

	uint16 numevts[SEP_DIAG_CYCPERSR];  /* number of events in EDB */

	uint16 DIAG[4*SEP_DIAG_CYCPERSR][SEP_DIAG_CYCLEN];/*engineering data*/
};
#endif

#include "df.h"

void main(argc, argv)
int argc;
char *argv[];
{
  int32 hdf_fp, SD_id;
  struct sdiag testdata;
  int ii,jj,retval;
  int i,j,k,l;
  
  int headers = 0;
  int elements;
  int event;

  if (argc < 2)
  {
      printf("Usage: %s hdf_file [-h] \n",argv[0]);
      exit(1);
  }
  
  if (argc >=3 && argv[2][0] == '-' && argv[2][1] == 'h')
    headers = 1;

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

  if( init_rd_s3_sdiag(hdf_fp, SD_id, "r") <= 0) {
    fprintf(stderr,"No s3 diag 2 data\n");
    exit(-1);
    }

  /* read and print data */
  ii=0;
  while((retval=read_s3_sdiag(&testdata,ii))!=-1)
  {
    if (headers)
    {
       printf("ii=%4d T=%10u "  "T=%14.3f "  "Q=%4d con=%d nevt=%d ", 
	            ii++, 
	            testdata.sctime_readout, 
	            testdata.sctime_collection, 
	            testdata.QAC, 
	            testdata.concat, 
   	            testdata.numevts);

       for(jj = 0 ; jj < SEP_DIAG_CYCPERSR ; jj++) 
   	   printf("%2d ",testdata.numevts[jj]);
     	 printf("\n");
    }    
    else
    {
#if 0
       elements = 0;
       
       for(i = 0 ; i < SEP_DIAG_CYCPERSR ; ++i)
       {
         for(j = 0 ; j < testdata.numevts[i] ; ++j)
         {
            ++elements;

            k = 4 * i + j;
                       
            for(l = 0 ; l < SEP_DIAG_CYCLEN ; ++l) 
	            printf("%4d ",testdata.DIAG[i][j][l] & 0x7FF);  /* spacecraft
sets msb every four words */
/*	            printf("%4d ",testdata.DIAG[k][l] & 0x7FF);     spacecraft
sets msb every four words */
            printf("\n");
         }
   	 }

   	 if (elements != testdata.elements)
   	   fprintf(stderr,"wrong element count: %4d %4d %4d\n",
   	                  ii,
   	                  testdata.elements,
   	                  elements);
#endif     
      l=0;
      for(i = 0 ; i < SEP_DIAG_CYCPERSR ; i++) {
         for(j = 0 ; j < testdata.numevts[i] ; j++) {
            printf("%d %d", testdata.sctime_readout, j);
            for(k = 0 ; k < SEP_DIAG_CYCLEN ; k++) {
	       /* spacecraft sets msb every four words */
               printf(" %d",testdata.DIAG[l+j][k] & 0x7FF);
	    }
	    printf("\n");
	 }
	 l+=j;
      }
      
   	++ii;
    }
  }

  /* all done, close HDF interface */

  close_rd_s3_sdiag();
  Vend(hdf_fp);
  SDend(SD_id);
  if (Hclose(hdf_fp)==FAIL) {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      HEprint(stderr,0);
      exit(-1);
    }
  exit(0);
}
                                  


