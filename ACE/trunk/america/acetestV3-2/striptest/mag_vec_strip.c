#include <stdio.h>
#include <string.h>

#include "mag_vector.h"
#include "df.h"
#include "mfhdf.h"

int32 hdf_fp_in, sd_id_in;
int32 hdf_fp_out, sd_id_out;

void main(argc, argv)
int argc;
char *argv[];
{
  struct MagVectorSet testdata;
  int ii,jj,retval;
  int32 numrec;
  int32 StartHDF_in(), StartHDF_out();

  if (argc!=3) {
      printf("Usage: %s hdf_inputfile hdf_outputfile\n",argv[0]);
      exit(1);
    }

  /* open hdf input file */
  numrec=StartHDF_in(argv[1]);
  StartHDF_out(argv[2]);

  ii=0;
  while((retval= read_mag_vec_in(&testdata,ii++))!=-1) {
      write_mag_vec_out(testdata,-1);
	  /*
	  printf("%4d sc clock = %8d\n", ii++,testdata.sctime_readout);
	  for(jj=0;jj<96;jj++)  { printf("%3x %3x %3x  ", 
	      testdata.vector[0][jj], testdata.vector[1][jj], 
	      testdata.vector[2][jj]);
	      if((jj%6)==5) printf("\n");
	  }
	  */
  }

  /* all done, close HDF files */

  close_rd_mag_vec_in();
  Vend(hdf_fp_in);
  if (SDend(sd_id_in)==FAIL) {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp_in)==FAIL) {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  close_wr_mag_vec_out();
  Vend(hdf_fp_out);
  if (SDend(sd_id_out)==FAIL) {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp_out)==FAIL) {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(-1);
    }

  exit(0);
}

int32 StartHDF_in(char *in_fname) {
int32 retval;

  if ((hdf_fp_in=Hopen(in_fname, DFACC_RDONLY, 0))==FAIL) {
      fprintf(stderr, "Hopen: could not open hdf input file: %s\n",in_fname);
      HEprint(stderr,0);
      exit(-1);
    }
  Vstart(hdf_fp_in);

    if ((sd_id_in=SDstart(in_fname, DFACC_RDONLY))==FAIL) {
	  fprintf(stderr, "SDstart: could not open hdf input file\n");
	  exit(-1);
    }
  if( (retval=init_rd_mag_vec_in(hdf_fp_in, sd_id_in, "r")) <= 0) {
	fprintf(stderr,"No mag vector data\n");
	exit(-1);
    }
    return(retval);
}

int32 StartHDF_out(char *out_fname) {
int32 an_id_out;

  if ((hdf_fp_out=Hopen(out_fname, DFACC_ALL, 0))==FAIL) {
      fprintf(stderr, "Hopen: could not open hdf output file\n");
      exit(-1);
    }
  Vstart(hdf_fp_out);

  if ((sd_id_out=SDstart(out_fname, DFACC_WRITE))==FAIL) {
	fprintf(stderr, "SDstart: could not open hdf output file\n");
	exit(-1);
  }
  if((an_id_out = ANstart(hdf_fp_out))==FAIL) {
      fprintf(stderr,"Couldn't ANstart %s\n",out_fname);
      exit(-1);
  }
  if( init_cr_mag_vec_out(hdf_fp_out, sd_id_out, an_id_out, 
	    "ACE MAG Vector data") ==FAIL) {
	fprintf(stderr,"Error creating MAG vector data\n");
	HEprint(stderr,0);
	exit(-1);
    }

  return(0);
}















