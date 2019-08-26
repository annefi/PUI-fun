/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: mag_fft.h,v 1.7 1997/05/07 18:44:38 jeff Exp  */

#include "mag_fft.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_mag_fft;
static int32 vdata_id_mag_fft;

static int32 sds_id_mag_fft1;

  /* 1518 is the size of mag_fft.h + 1 added line */
char Vgrp_descrp_MagFFTSet[1518];

/****----  init create function  ----****/

int32 init_cr_mag_fft(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_mag_fft();

  void print_mag_fft_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_mag_fft = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_mag_fft_error("init_cr_mag_fft -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_mag_fft, "VG_MagFFTSet"); 
  Vsetclass(vgrp_id_mag_fft, "VG_MAG_FFT");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_MagFFTSet" )) ==FAIL) {
    print_mag_fft_error("init_cr_mag_fft -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_mag_fft(Vgrp_descrp_MagFFTSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_mag_fft_error("init_cr_mag_fft -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_MagFFTSet, sizeof(Vgrp_descrp_MagFFTSet))) ==FAIL) {
    print_mag_fft_error("init_cr_mag_fft -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_mag_fft = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_mag_fft_error("init_cr_mag_fft -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_mag_fft, "MagFFTSet");
  VSsetclass(vdata_id_mag_fft, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_mag_fft, vdata_id_mag_fft)) ==FAIL) {
    print_mag_fft_error("init_cr_mag_fft -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_mag_fft, "sctime_readout", DFNT_UINT32, (1) )) {
    print_mag_fft_error("init_cr_mag_fft -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_fft, "sctime_collection", DFNT_UINT32, (1) )) {
    print_mag_fft_error("init_cr_mag_fft -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_fft, "QAC", DFNT_UINT32, (1) )) {
    print_mag_fft_error("init_cr_mag_fft -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_fft, "fft_statbits", DFNT_UINT16, (MJ_FFT_CYC) )) {
    print_mag_fft_error("init_cr_mag_fft -> VSfdefine: Couldn't define fft_statbits");
    retval = -1;
  }

  if (VSsetfields(vdata_id_mag_fft,"sctime_readout, sctime_collection, QAC, fft_statbits")){
    print_mag_fft_error("init_cr_mag_fft -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 10;
  dim_sizes[2] = FFTBIN;
  if((sds_id_mag_fft1 = SDcreate(sd_id, "MagFFTSet_fft_val", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_mag_fft_error("init_cr_mag_fft -> SDcreate: Couldn't create MagFFTSet_fft_val");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_mag_fft1)) == FAIL)
    print_mag_fft_error("init_cr_mag_fft -> SDidtoref: Couldn't get ref for MagFFTSet_fft_val");

  if((Vaddtagref(vgrp_id_mag_fft, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_mag_fft_error("init_cr_mag_fft -> Vaddtagref: Couldn't add SDS MagFFTSet_fft_val to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_mag_fft(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_mag_fft(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_mag_fft(struct MagFFTSet MagFFTSet_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_mag_fft_error();
void pack_mag_fft();

  odata = (uint8 *) malloc(sizeof(struct MagFFTSet));
  pack_mag_fft(odata, &MagFFTSet_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_mag_fft, recnum)==-1) {
		print_mag_fft_error("write_mag_fft -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_mag_fft, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_mag_fft_error("write_mag_fft -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 10;
  edges[2] = FFTBIN;
  if (SDwritedata(sds_id_mag_fft1,start,NULL,edges, (VOIDP)(MagFFTSet_struc.fft_val)) ==FAIL)
    print_mag_fft_error("write_mag_fft -> SDwritedata: Problem writing fft_val data.");

  memset(&MagFFTSet_struc, 0, sizeof(struct MagFFTSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_mag_fft()
{
  VSdetach(vdata_id_mag_fft);
  Vdetach(vgrp_id_mag_fft);
  SDendaccess(sds_id_mag_fft1);
}

/*----     init access function    ----*/

int32 init_acc_mag_fft(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_mag_fft_error();

  if((sds_index1=SDnametoindex(sd_id, "MagFFTSet_fft_val" )) ==FAIL) {
      print_mag_fft_error("init_acc_mag_fft -> SDnametoindex: Couldn't find MagFFTSet_fft_val");
      return(-1);
  }
  if((sds_id_mag_fft1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_mag_fft_error("init_acc_mag_fft -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "MagFFTSet")) <= 0 ) {
    print_mag_fft_error("init_acc_mag_fft -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_mag_fft = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_mag_fft_error("init_acc_mag_fft -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_mag_fft, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_mag_fft,"sctime_readout, sctime_collection, QAC, fft_statbits")) {
      print_mag_fft_error("init_acc_mag_fft -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_mag_fft(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_mag_fft(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_mag_fft(struct MagFFTSet *MagFFTSet_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_mag_fft_error();
void unpack_mag_fft();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct MagFFTSet));
  VSinquire(vdata_id_mag_fft, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_mag_fft, recnum_rd)==FAIL) {
          print_mag_fft_error("read_mag_fft -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 10;
  edges[2] = FFTBIN;

  if(SDreaddata(sds_id_mag_fft1,start,NULL,edges, (VOIDP)(MagFFTSet_struc->fft_val )) ==FAIL) {
    print_mag_fft_error("read_mag_fft -> SDreaddata: Couldn't read fft_val");
    retval = -1;
  }
  if(VSread(vdata_id_mag_fft, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_mag_fft_error("read_mag_fft -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_mag_fft(odata, MagFFTSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_mag_fft()
{
  VSdetach(vdata_id_mag_fft);
  SDendaccess(sds_id_mag_fft1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_mag_fft(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_mag_fft_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_MagFFTSet" )) ==FAIL)
    print_mag_fft_error("rd_Vgrp_mag_fft -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_mag_fft_error("rd_Vgrp_mag_fft -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_mag_fft_error("rd_Vgrp_mag_fft -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_mag_fft_error("rd_Vgrp_mag_fft -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_MagFFTSet, HDstrlen(Vgrp_descrp_MagFFTSet)) ==FAIL)
    print_mag_fft_error("rd_Vgrp_mag_fft -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_MagFFTSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_mag_fft_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_mag_fft.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_mag_fft(uint8 *data, struct MagFFTSet *MagFFTSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &MagFFTSet_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagFFTSet_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagFFTSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagFFTSet_ptr->fft_statbits[0], ((2)*(MJ_FFT_CYC)) );
   ptr+= ((2)*(MJ_FFT_CYC));
}

/*----   unpack function    ----*/

void unpack_mag_fft(uint8 *data, struct MagFFTSet *MagFFTSet_ptr)
{
int32 ptr=0;

   memcpy(&MagFFTSet_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagFFTSet_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagFFTSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagFFTSet_ptr->fft_statbits[0], data+ptr,  ((2)*(MJ_FFT_CYC)) );
   ptr+= ((2)*(MJ_FFT_CYC));
}
int32 get_vgrp_id_mag_fft() {return(vgrp_id_mag_fft);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_mag_fft(char *wr_strval)
{
  strcpy(wr_strval, "The file 'mag_fft.h' is shown below, it was used to create the data in the Vgroup named 'VG_MagFFTSet'.\n\n");
  strcat(wr_strval,"/* Id: mag_fft.h,v 1.7 1997/05/07 18:44:38 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define FFTBIN 32                /* 32 FFT frequency bins            */\n");
  strcat(wr_strval,"#define MJ_FFT_CYC 5             /* Major frames per FFT cycle       */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct MagFFTSet                 /* setkey=fG                           */\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 sctime_readout;       /* 32 bit spacecraft readout time  */\n");
  strcat(wr_strval,"  uint32 sctime_collection;       /* 32 bit spacecraft collection time  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 QAC;			/* number of missing frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint16 fft_statbits[MJ_FFT_CYC];   /* bits 15-9 - unused (=0) */\n");
  strcat(wr_strval,"				     /* bit  8    = Rg (ST5 bit 2) */\n");
  strcat(wr_strval,"				     /* lsByte    = ST6         */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 fft_val[10][FFTBIN];\n");
  strcat(wr_strval,"  /* first index = 0 -> X-axis FFT transform real output    */\n");
  strcat(wr_strval,"  /* first index = 1 -> Y-axis FFT transform real output    */\n");
  strcat(wr_strval,"  /* first index = 2 -> Z-axis FFT transform real output    */\n");
  strcat(wr_strval,"  /* first index = 3 -> X-Y cross-spectra real output       */\n");
  strcat(wr_strval,"  /* first index = 4 -> X-Y cross-spectra imaginary output  */\n");
  strcat(wr_strval,"  /* first index = 5 -> X-Z cross-spectra real output       */\n");
  strcat(wr_strval,"  /* first index = 6 -> X-Z cross-spectra imaginary output  */\n");
  strcat(wr_strval,"  /* first index = 7 -> Y-Z cross-spectra real output       */\n");
  strcat(wr_strval,"  /* first index = 8 -> Y-Z cross-spectra imaginary output  */\n");
  strcat(wr_strval,"  /* first index = 9 -> magnitude FFT transform real output */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
