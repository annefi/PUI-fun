/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_smatrix.h,v 1.6 1998/12/07 18:12:39 ad Exp  */

#include "s3_smatrix.h"
#include "df.h"

int32 vgrp_id_s3_smatrix;
static int32 vdata_id_s3_smatrix;

  /* 1493 is the size of s3_smatrix.h + 1 added line */
char Vgrp_descrp_smatrix[1493];

/****----  init create function  ----****/

int32 init_cr_s3_smatrix(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_smatrix();

  void print_s3_smatrix_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_smatrix = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_smatrix, "VG_smatrix"); 
  Vsetclass(vgrp_id_s3_smatrix, "VG_S3_SMATRIX");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_smatrix" )) ==FAIL) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_smatrix(Vgrp_descrp_smatrix);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_smatrix, sizeof(Vgrp_descrp_smatrix))) ==FAIL) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_smatrix = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_smatrix, "smatrix");
  VSsetclass(vdata_id_s3_smatrix, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_smatrix, vdata_id_s3_smatrix)) ==FAIL) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_smatrix, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_smatrix, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_smatrix, "QAC", DFNT_UINT32, (1) )) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_smatrix, "MATRIX", DFNT_UINT16, (SMAT_N) )) {
    print_s3_smatrix_error("init_cr_s3_smatrix -> VSfdefine: Couldn't define MATRIX");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_smatrix,"sctime_readout, sctime_collection, QAC, MATRIX")){
    print_s3_smatrix_error("init_cr_s3_smatrix -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_smatrix(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_smatrix(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_smatrix(struct smatrix smatrix_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_smatrix_error();
void pack_s3_smatrix();

  odata = (uint8 *) malloc(sizeof(struct smatrix));
  pack_s3_smatrix(odata, &smatrix_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_smatrix, recnum)==-1) {
		print_s3_smatrix_error("write_s3_smatrix -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_smatrix, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_smatrix_error("write_s3_smatrix -> VSwrite: Couldn't write data.");

  memset(&smatrix_struc, 0, sizeof(struct smatrix));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_smatrix()
{
  VSdetach(vdata_id_s3_smatrix);
  Vdetach(vgrp_id_s3_smatrix);
}

/*----     init access function    ----*/

int32 init_acc_s3_smatrix(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_smatrix_error();


  if ((vdata_ref = VSfind(hdf_fp, "smatrix")) <= 0 ) {
    print_s3_smatrix_error("init_acc_s3_smatrix -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_smatrix = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_smatrix_error("init_acc_s3_smatrix -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_smatrix, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_smatrix,"sctime_readout, sctime_collection, QAC, MATRIX")) {
      print_s3_smatrix_error("init_acc_s3_smatrix -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_smatrix(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_smatrix(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_smatrix(struct smatrix *smatrix_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_smatrix_error();
void unpack_s3_smatrix();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct smatrix));
  VSinquire(vdata_id_s3_smatrix, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_smatrix, recnum_rd)==FAIL) {
          print_s3_smatrix_error("read_s3_smatrix -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_smatrix, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_smatrix_error("read_s3_smatrix -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_smatrix(odata, smatrix_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_smatrix()
{
  VSdetach(vdata_id_s3_smatrix);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_smatrix(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_smatrix_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_smatrix" )) ==FAIL)
    print_s3_smatrix_error("rd_Vgrp_s3_smatrix -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_smatrix_error("rd_Vgrp_s3_smatrix -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_smatrix_error("rd_Vgrp_s3_smatrix -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_smatrix_error("rd_Vgrp_s3_smatrix -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_smatrix, HDstrlen(Vgrp_descrp_smatrix)) ==FAIL)
    print_s3_smatrix_error("rd_Vgrp_s3_smatrix -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_smatrix);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_smatrix_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_smatrix.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_smatrix(uint8 *data, struct smatrix *smatrix_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &smatrix_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &smatrix_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &smatrix_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &smatrix_ptr->MATRIX[0], ((2)*(SMAT_N)) );
   ptr+= ((2)*(SMAT_N));
}

/*----   unpack function    ----*/

void unpack_s3_smatrix(uint8 *data, struct smatrix *smatrix_ptr)
{
int32 ptr=0;

   memcpy(&smatrix_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&smatrix_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&smatrix_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&smatrix_ptr->MATRIX[0], data+ptr,  ((2)*(SMAT_N)) );
   ptr+= ((2)*(SMAT_N));
}
int32 get_vgrp_id_s3_smatrix() {return(vgrp_id_s3_smatrix);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_smatrix(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_smatrix.h' is shown below, it was used to create the data in the Vgroup named 'VG_smatrix'.\n\n");
  strcat(wr_strval,"/* Id: s3_smatrix.h,v 1.6 1998/12/07 18:12:39 ad Exp $	     */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SMAT_N     60  /* number of matrix rate channels */\n");
  strcat(wr_strval,"#define SMAT_S     1  /* number of sectors */\n");
  strcat(wr_strval,"#define SMAT_CYC   6  /* number of cycles per SR = 60 / 10 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval," /* total size (in bytes) of SMAT data (including slack) in a full SR */\n");
  strcat(wr_strval,"#define SMAT_TSZ   540 \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* size (in bytes) of SMAT cycle (including slack) */\n");
  strcat(wr_strval,"#define SMAT_CSZ   SMAT_TSZ/SMAT_CYC \n");
  strcat(wr_strval,"#define SMAT_ESZ   SMAT_TSZ/60  /* size (in bytes) of SMAT area in EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Matrix rates are collected over 10 spins and output during the next */\n");
  strcat(wr_strval,"/* 10 spins(or edb's). There are 6 matrix rate collection cycles per */\n");
  strcat(wr_strval,"/* Science Record */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_readout: spacecraft clock of first minor frame of the */\n");
  strcat(wr_strval,"/* first edb of the matrix rate output cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_collection:  time of the start of the first spin in the */\n");
  strcat(wr_strval,"/* collection cycle, in spacecraft clock time units */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* smatrix structure contains SEPICA matrix rates for 1 10-spin collection cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct smatrix{\n");
  strcat(wr_strval,"   uint32 sctime_readout;  /* 32 bit spacecraft time  */\n");
  strcat(wr_strval,"   float64 sctime_collection; /* spacecraft time, sub-second resolution */\n");
  strcat(wr_strval,"   uint32 QAC;     /* number of missing frames in this 10-spin cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   uint16 MATRIX[SMAT_N]; /* 49 Matrix rates, 11 fill */\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  return(0);
}
