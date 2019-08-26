#include <stdio.h>
#include <string.h>

#include "mag_avgvec.h"
#include "mag_vector.h"
#include "mag_snapshot.h"
#include "mag_fft.h"
#include "mag_hskp.h"
#include "schskp.h"
#include "sunpulsetime.h"
#include "df.h"
#include "mfhdf.h"

int32 hdf_fp_in, sd_id_in;
int32 hdf_fp_out, sd_id_out;
int32 numrecsunp;

void main(argc, argv)
int argc;
char *argv[];
{
  struct MagAvgVec magavgvecdata;
  struct MagVectorSet magvecdata;
  struct MagFFTSet magfftdata;
  struct MagHskpSet maghskpdata;
  struct MagSnapSet magsnapdata;
  struct SCHskpData schkdata;
  struct ACEsunpulsetime sunpulsetimedata;
  int ii,jj,retval;
  int32 numrec;
  int32 StartHDF_in(), StartHDF_out();

  if (argc!=3) {
      printf("Usage: %s hdf_inputfile hdf_outputfile\n",argv[0]);
      exit(1);
    }

  /* open hdf input file */
  StartHDF_in(argv[1]);

  if( (numrec=init_rd_mag_vec_in(hdf_fp_in, sd_id_in, "r")) <= 0) {
	fprintf(stderr,"No mag vector data\n"); exit(-1);
    }
  if( (numrec=init_rd_mag_avgvec_in(hdf_fp_in, sd_id_in, "r")) <= 0) {
	fprintf(stderr,"No mag avgvector data\n"); exit(-1);
    }
  if( (numrec=init_rd_mag_fft_in(hdf_fp_in, sd_id_in, "r")) <= 0) {
	fprintf(stderr,"No mag fft data\n"); exit(-1);
    }
  if( (numrec=init_rd_mag_snap_in(hdf_fp_in, sd_id_in, "r")) <= 0) {
	fprintf(stderr,"No mag snap data\n"); exit(-1);
    }
  if( (numrec=init_rd_mag_hskp_in(hdf_fp_in, sd_id_in), "r") <= 0) {
	fprintf(stderr,"No mag hskp data\n"); exit(-1);
    }
  if( (numrec=init_rd_schskp_in(hdf_fp_in, sd_id_in, "r")) <= 0) {
	fprintf(stderr,"No schskp data\n"); exit(-1);
    }
  if( (numrecsunp=init_acc_sunpulsetime_in(hdf_fp_in, sd_id_in, "r")) <= 0) {
	fprintf(stderr,"No sunpulsetime data\n");
    }

  StartHDF_out(argv[2]);

  ii=0;
  while((retval= read_mag_vec_in(&magvecdata,ii++))!=-1) 
    write_mag_vec_out(magvecdata,-1);

  ii=0;
  while((retval= read_mag_avgvec_in(&magavgvecdata,ii++))!=-1) 
    write_mag_avgvec_out(magavgvecdata,-1);

  ii=0;
  while((retval= read_mag_fft_in(&magfftdata,ii++))!=-1) 
    write_mag_fft_out(magfftdata,-1);

  ii=0;
  while((retval= read_mag_hskp_in(&maghskpdata,ii++))!=-1) 
    write_mag_hskp_out(maghskpdata,-1);

  ii=0;
  while((retval= read_mag_snap_in(&magsnapdata,ii++))!=-1)
    write_mag_snap_out(magsnapdata,-1);

  ii=0;
  while((retval= read_schskp_in(&schkdata,ii++))!=-1) 
    write_schskp_out(schkdata,-1);

  ii=0;
  if(numrecsunp > 0) {
  while((retval= read_sunpulsetime_in(&sunpulsetimedata,ii++))!=-1) 
    write_sunpulsetime_out(sunpulsetimedata,-1);
  }

  /* all done, close HDF files */

  close_rd_mag_vec_in();
  close_rd_mag_avgvec_in();
  close_rd_mag_fft_in();
  close_rd_mag_snap_in();
  close_rd_mag_hskp_in();
  close_rd_schskp_in();
  close_rd_sunpulsetime_in();

  Vend(hdf_fp_in);
  if (SDend(sd_id_in)==FAIL) {
      fprintf(stderr, "SDend: could not close input hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp_in)==FAIL) {
      fprintf(stderr, "Hclose: could not close input hdf file\n");
      exit(-1);
    }

  close_wr_mag_vec_out();
  close_wr_mag_avgvec_out();
  close_wr_mag_fft_out();
  close_wr_mag_snap_out();
  close_wr_mag_hskp_out();
  close_wr_schskp_out();
  if(numrecsunp>0)
    close_wr_sunpulsetime_out();

  Vend(hdf_fp_out);
  if (SDend(sd_id_out)==FAIL) {
      fprintf(stderr, "SDend: could not close input hdf file\n");
      exit(-1);
    }
  if (Hclose(hdf_fp_out)==FAIL) {
      fprintf(stderr, "Hclose: could not close output hdf file\n");
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
    return(0);
}

int32 StartHDF_out(char *out_fname) {
int32 an_id_out;

  if ((hdf_fp_out=Hopen(out_fname, DFACC_ALL, 0))==FAIL) {
      fprintf(stderr, "Hopen: could not open hdf output file: %s\n",out_fname);
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
	HEprint(stderr,0); exit(-1);
    }
  if( init_cr_mag_avgvec_out(hdf_fp_out, sd_id_out, an_id_out, 
	    "ACE MAG Average Vector data") ==FAIL) {
	fprintf(stderr,"Error creating MAG average vector data\n");
	HEprint(stderr,0); exit(-1);
    }
  if( init_cr_mag_fft_out(hdf_fp_out, sd_id_out, an_id_out, 
	    "ACE MAG FFT data") ==FAIL) {
	fprintf(stderr,"Error creating MAG FFT data\n");
	HEprint(stderr,0); exit(-1);
    }
  if( init_cr_mag_snap_out(hdf_fp_out, sd_id_out, an_id_out, 
	    "ACE MAG Snapshot data") ==FAIL) {
	fprintf(stderr,"Error creating MAG Snapshot data\n");
	HEprint(stderr,0); exit(-1);
    }
  if( init_cr_mag_hskp_out(hdf_fp_out, sd_id_out, an_id_out, 
	    "ACE MAG HK data") ==FAIL) {
	fprintf(stderr,"Error creating MAG HK data\n");
	HEprint(stderr,0); exit(-1);
    }
  if( init_cr_schskp_out(hdf_fp_out, sd_id_out, an_id_out, 
	    "ACE SC HK data") ==FAIL) {
	fprintf(stderr,"Error creating SC HK data\n");
	HEprint(stderr,0); exit(-1);
    }
if (numrecsunp>0) {
  if( init_cr_sunpulsetime_out(hdf_fp_out, sd_id_out, an_id_out, 
	    "ACE sunpulsetime data") ==FAIL) {
	fprintf(stderr,"Error creating sunpulsetime data\n");
	HEprint(stderr,0); exit(-1);
    }
}

  return(0);
}
