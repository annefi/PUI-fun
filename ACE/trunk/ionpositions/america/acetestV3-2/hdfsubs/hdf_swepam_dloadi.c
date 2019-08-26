/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_dloadi.h,v 1.2 1997/07/17 00:07:04 jeff Exp  */

#include "swepam_dloadi.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_swepam_dloadi;
static int32 vdata_id_swepam_dloadi;

static int32 sds_id_swepam_dloadi1, sds_id_swepam_dloadi2, sds_id_swepam_dloadi3, sds_id_swepam_dloadi4;

  /* 1076 is the size of swepam_dloadi.h + 1 added line */
char Vgrp_descrp_DLOADI[1076];

/****----  init create function  ----****/

int32 init_cr_swepam_dloadi(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2, sds_ref_w3, sds_ref_w4;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_swepam_dloadi();

  void print_swepam_dloadi_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_dloadi = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_dloadi, "VG_DLOADI"); 
  Vsetclass(vgrp_id_swepam_dloadi, "VG_SWEPAM_DLOADI");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_DLOADI" )) ==FAIL) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_dloadi(Vgrp_descrp_DLOADI);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_DLOADI, sizeof(Vgrp_descrp_DLOADI))) ==FAIL) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_dloadi = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_dloadi, "DLOADI");
  VSsetclass(vdata_id_swepam_dloadi, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_dloadi, vdata_id_swepam_dloadi)) ==FAIL) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_dloadi, "output_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dloadi, "collect_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dloadi, "QAC", DFNT_UINT8, (1) )) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dloadi, "MinFrmIndx", DFNT_UINT8, (16) )) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSfdefine: Couldn't define MinFrmIndx");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dloadi, "EventFlag", DFNT_UINT8, (16) )) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSfdefine: Couldn't define EventFlag");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dloadi, "DumpRecAdd", DFNT_UINT16, (16) )) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSfdefine: Couldn't define DumpRecAdd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dloadi, "MinFrmChk", DFNT_UINT8, (16) )) {
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSfdefine: Couldn't define MinFrmChk");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_dloadi,"output_sctime, collect_sctime, QAC, MinFrmIndx, EventFlag, DumpRecAdd, MinFrmChk")){
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 16;
  dim_sizes[2] = 3;
  if((sds_id_swepam_dloadi1 = SDcreate(sd_id, "DLOADI_StatRec", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> SDcreate: Couldn't create DLOADI_StatRec");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_swepam_dloadi1)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> SDidtoref: Couldn't get ref for DLOADI_StatRec");

  if((Vaddtagref(vgrp_id_swepam_dloadi, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> Vaddtagref: Couldn't add SDS DLOADI_StatRec to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 16;
  dim_sizes[2] = 6;
  if((sds_id_swepam_dloadi2 = SDcreate(sd_id, "DLOADI_LoadErrRec", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> SDcreate: Couldn't create DLOADI_LoadErrRec");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_swepam_dloadi2)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> SDidtoref: Couldn't get ref for DLOADI_LoadErrRec");

  if((Vaddtagref(vgrp_id_swepam_dloadi, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> Vaddtagref: Couldn't add SDS DLOADI_LoadErrRec to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 16;
  dim_sizes[2] = 26;
  if((sds_id_swepam_dloadi3 = SDcreate(sd_id, "DLOADI_LoadErrFil", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> SDcreate: Couldn't create DLOADI_LoadErrFil");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w3 = SDidtoref(sds_id_swepam_dloadi3)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> SDidtoref: Couldn't get ref for DLOADI_LoadErrFil");

  if((Vaddtagref(vgrp_id_swepam_dloadi, DFTAG_NDG, sds_ref_w3)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> Vaddtagref: Couldn't add SDS DLOADI_LoadErrFil to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 16;
  dim_sizes[2] = 28;
  if((sds_id_swepam_dloadi4 = SDcreate(sd_id, "DLOADI_DumpRecDat", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> SDcreate: Couldn't create DLOADI_DumpRecDat");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w4 = SDidtoref(sds_id_swepam_dloadi4)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> SDidtoref: Couldn't get ref for DLOADI_DumpRecDat");

  if((Vaddtagref(vgrp_id_swepam_dloadi, DFTAG_NDG, sds_ref_w4)) == FAIL)
    print_swepam_dloadi_error("init_cr_swepam_dloadi -> Vaddtagref: Couldn't add SDS DLOADI_DumpRecDat to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_dloadi(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_dloadi(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_dloadi(struct DLOADI DLOADI_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_swepam_dloadi_error();
void pack_swepam_dloadi();

  odata = (uint8 *) malloc(sizeof(struct DLOADI));
  pack_swepam_dloadi(odata, &DLOADI_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_swepam_dloadi, recnum)==-1) {
		print_swepam_dloadi_error("write_swepam_dloadi -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_dloadi, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_dloadi_error("write_swepam_dloadi -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 16;
  edges[2] = 3;
  if (SDwritedata(sds_id_swepam_dloadi1,start,NULL,edges, (VOIDP)(DLOADI_struc.StatRec)) ==FAIL)
    print_swepam_dloadi_error("write_swepam_dloadi -> SDwritedata: Problem writing StatRec data.");

  edges[1] = 16;
  edges[2] = 6;
  if (SDwritedata(sds_id_swepam_dloadi2,start,NULL,edges, (VOIDP)(DLOADI_struc.LoadErrRec)) ==FAIL)
    print_swepam_dloadi_error("write_swepam_dloadi -> SDwritedata: Problem writing LoadErrRec data.");

  edges[1] = 16;
  edges[2] = 26;
  if (SDwritedata(sds_id_swepam_dloadi3,start,NULL,edges, (VOIDP)(DLOADI_struc.LoadErrFil)) ==FAIL)
    print_swepam_dloadi_error("write_swepam_dloadi -> SDwritedata: Problem writing LoadErrFil data.");

  edges[1] = 16;
  edges[2] = 28;
  if (SDwritedata(sds_id_swepam_dloadi4,start,NULL,edges, (VOIDP)(DLOADI_struc.DumpRecDat)) ==FAIL)
    print_swepam_dloadi_error("write_swepam_dloadi -> SDwritedata: Problem writing DumpRecDat data.");

  memset(&DLOADI_struc, 0, sizeof(struct DLOADI));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_dloadi()
{
  VSdetach(vdata_id_swepam_dloadi);
  Vdetach(vgrp_id_swepam_dloadi);
  SDendaccess(sds_id_swepam_dloadi1);
  SDendaccess(sds_id_swepam_dloadi2);
  SDendaccess(sds_id_swepam_dloadi3);
  SDendaccess(sds_id_swepam_dloadi4);
}

/*----     init access function    ----*/

int32 init_acc_swepam_dloadi(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  static int32 sds_index3;
  static int32 sds_index4;
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_dloadi_error();

  if((sds_index1=SDnametoindex(sd_id, "DLOADI_StatRec" )) ==FAIL) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> SDnametoindex: Couldn't find DLOADI_StatRec");
      return(-1);
  }
  if((sds_id_swepam_dloadi1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "DLOADI_LoadErrRec" )) ==FAIL) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> SDnametoindex: Couldn't find DLOADI_LoadErrRec");
      return(-1);
  }
  if((sds_id_swepam_dloadi2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> SDselect: Couldn't select sds_index2");
      return(-1);
  }
  if((sds_index3=SDnametoindex(sd_id, "DLOADI_LoadErrFil" )) ==FAIL) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> SDnametoindex: Couldn't find DLOADI_LoadErrFil");
      return(-1);
  }
  if((sds_id_swepam_dloadi3=SDselect(sd_id, sds_index3)) ==FAIL) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> SDselect: Couldn't select sds_index3");
      return(-1);
  }
  if((sds_index4=SDnametoindex(sd_id, "DLOADI_DumpRecDat" )) ==FAIL) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> SDnametoindex: Couldn't find DLOADI_DumpRecDat");
      return(-1);
  }
  if((sds_id_swepam_dloadi4=SDselect(sd_id, sds_index4)) ==FAIL) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> SDselect: Couldn't select sds_index4");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "DLOADI")) <= 0 ) {
    print_swepam_dloadi_error("init_acc_swepam_dloadi -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_dloadi = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_dloadi_error("init_acc_swepam_dloadi -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_dloadi, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_dloadi,"output_sctime, collect_sctime, QAC, MinFrmIndx, EventFlag, DumpRecAdd, MinFrmChk")) {
      print_swepam_dloadi_error("init_acc_swepam_dloadi -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_dloadi(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_dloadi(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_dloadi(struct DLOADI *DLOADI_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_dloadi_error();
void unpack_swepam_dloadi();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct DLOADI));
  VSinquire(vdata_id_swepam_dloadi, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_dloadi, recnum_rd)==FAIL) {
          print_swepam_dloadi_error("read_swepam_dloadi -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 16;
  edges[2] = 3;

  if(SDreaddata(sds_id_swepam_dloadi1,start,NULL,edges, (VOIDP)(DLOADI_struc->StatRec )) ==FAIL) {
    print_swepam_dloadi_error("read_swepam_dloadi -> SDreaddata: Couldn't read StatRec");
    retval = -1;
  }
  edges[1] = 16;
  edges[2] = 6;

  if(SDreaddata(sds_id_swepam_dloadi2,start,NULL,edges, (VOIDP)(DLOADI_struc->LoadErrRec )) ==FAIL) {
    print_swepam_dloadi_error("read_swepam_dloadi -> SDreaddata: Couldn't read LoadErrRec");
    retval = -1;
  }
  edges[1] = 16;
  edges[2] = 26;

  if(SDreaddata(sds_id_swepam_dloadi3,start,NULL,edges, (VOIDP)(DLOADI_struc->LoadErrFil )) ==FAIL) {
    print_swepam_dloadi_error("read_swepam_dloadi -> SDreaddata: Couldn't read LoadErrFil");
    retval = -1;
  }
  edges[1] = 16;
  edges[2] = 28;

  if(SDreaddata(sds_id_swepam_dloadi4,start,NULL,edges, (VOIDP)(DLOADI_struc->DumpRecDat )) ==FAIL) {
    print_swepam_dloadi_error("read_swepam_dloadi -> SDreaddata: Couldn't read DumpRecDat");
    retval = -1;
  }
  if(VSread(vdata_id_swepam_dloadi, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_dloadi_error("read_swepam_dloadi -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_dloadi(odata, DLOADI_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_dloadi()
{
  VSdetach(vdata_id_swepam_dloadi);
  SDendaccess(sds_id_swepam_dloadi1);
  SDendaccess(sds_id_swepam_dloadi2);
  SDendaccess(sds_id_swepam_dloadi3);
  SDendaccess(sds_id_swepam_dloadi4);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_dloadi(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_dloadi_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_DLOADI" )) ==FAIL)
    print_swepam_dloadi_error("rd_Vgrp_swepam_dloadi -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_dloadi_error("rd_Vgrp_swepam_dloadi -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_dloadi_error("rd_Vgrp_swepam_dloadi -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_dloadi_error("rd_Vgrp_swepam_dloadi -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_DLOADI, HDstrlen(Vgrp_descrp_DLOADI)) ==FAIL)
    print_swepam_dloadi_error("rd_Vgrp_swepam_dloadi -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_DLOADI);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_dloadi_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_dloadi.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_dloadi(uint8 *data, struct DLOADI *DLOADI_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &DLOADI_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DLOADI_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DLOADI_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DLOADI_ptr->MinFrmIndx[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &DLOADI_ptr->EventFlag[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &DLOADI_ptr->DumpRecAdd[0], ((2)*(16)) );
   ptr+= ((2)*(16));
   memcpy(data+ptr, &DLOADI_ptr->MinFrmChk[0], ((1)*(16)) );
   ptr+= ((1)*(16));
}

/*----   unpack function    ----*/

void unpack_swepam_dloadi(uint8 *data, struct DLOADI *DLOADI_ptr)
{
int32 ptr=0;

   memcpy(&DLOADI_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DLOADI_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DLOADI_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DLOADI_ptr->MinFrmIndx[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&DLOADI_ptr->EventFlag[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&DLOADI_ptr->DumpRecAdd[0], data+ptr,  ((2)*(16)) );
   ptr+= ((2)*(16));
   memcpy(&DLOADI_ptr->MinFrmChk[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
}
int32 get_vgrp_id_swepam_dloadi() {return(vgrp_id_swepam_dloadi);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_dloadi(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_dloadi.h' is shown below, it was used to create the data in the Vgroup named 'VG_DLOADI'.\n\n");
  strcat(wr_strval,"/* Id: swepam_dloadi.h,v 1.2 1997/07/17 00:07:04 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct DLOADI              /* Swepam Ion Load Mode*/\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;   /* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;  /* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint8  QAC;             /* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8    MinFrmIndx[16];     /* minor frame index. */\n");
  strcat(wr_strval,"  uint8    EventFlag[16];     /* Event flags. */\n");
  strcat(wr_strval,"  uint8    StatRec[16][3];    /* 3 status record/frame. */\n");
  strcat(wr_strval,"  uint8    LoadErrRec[16][6];    /* 6 byte load error/frame */\n");
  strcat(wr_strval,"  uint8    LoadErrFil[16][26];   /* 26 bytes of load error fill data */\n");
  strcat(wr_strval,"  uint16   DumpRecAdd[16];    /* address of first data byte in dump record */\n");
  strcat(wr_strval,"  uint8    DumpRecDat[16][28]; /* 28 bytes of dump record data/frame */\n");
  strcat(wr_strval,"  uint8    MinFrmChk[16];     /* 2's compliment checksum- 1 per frame */\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"  \n");
  return(0);
}
