/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_dengi.h,v 1.2 1997/07/17 00:07:04 jeff Exp  */

#include "swepam_dengi.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_swepam_dengi;
static int32 vdata_id_swepam_dengi;

static int32 sds_id_swepam_dengi1, sds_id_swepam_dengi2, sds_id_swepam_dengi3;

  /* 1023 is the size of swepam_dengi.h + 1 added line */
char Vgrp_descrp_DENGI[1023];

/****----  init create function  ----****/

int32 init_cr_swepam_dengi(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2, sds_ref_w3;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_swepam_dengi();

  void print_swepam_dengi_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_dengi = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_dengi, "VG_DENGI"); 
  Vsetclass(vgrp_id_swepam_dengi, "VG_SWEPAM_DENGI");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_DENGI" )) ==FAIL) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_dengi(Vgrp_descrp_DENGI);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_DENGI, sizeof(Vgrp_descrp_DENGI))) ==FAIL) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_dengi = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_dengi, "DENGI");
  VSsetclass(vdata_id_swepam_dengi, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_dengi, vdata_id_swepam_dengi)) ==FAIL) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_dengi, "output_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dengi, "collect_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dengi, "QAC", DFNT_UINT8, (1) )) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dengi, "MinFrmIndx", DFNT_UINT8, (16) )) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSfdefine: Couldn't define MinFrmIndx");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dengi, "EventFlag", DFNT_UINT8, (16) )) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSfdefine: Couldn't define EventFlag");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dengi, "DumpRecAdd", DFNT_UINT16, (16) )) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSfdefine: Couldn't define DumpRecAdd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dengi, "MinFrmChk", DFNT_UINT8, (16) )) {
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSfdefine: Couldn't define MinFrmChk");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_dengi,"output_sctime, collect_sctime, QAC, MinFrmIndx, EventFlag, DumpRecAdd, MinFrmChk")){
    print_swepam_dengi_error("init_cr_swepam_dengi -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 16;
  dim_sizes[2] = 3;
  if((sds_id_swepam_dengi1 = SDcreate(sd_id, "DENGI_StatRec", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> SDcreate: Couldn't create DENGI_StatRec");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_swepam_dengi1)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> SDidtoref: Couldn't get ref for DENGI_StatRec");

  if((Vaddtagref(vgrp_id_swepam_dengi, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> Vaddtagref: Couldn't add SDS DENGI_StatRec to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 16;
  dim_sizes[2] = 16;
  if((sds_id_swepam_dengi2 = SDcreate(sd_id, "DENGI_ScalarRecDat", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> SDcreate: Couldn't create DENGI_ScalarRecDat");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_swepam_dengi2)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> SDidtoref: Couldn't get ref for DENGI_ScalarRecDat");

  if((Vaddtagref(vgrp_id_swepam_dengi, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> Vaddtagref: Couldn't add SDS DENGI_ScalarRecDat to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 16;
  dim_sizes[2] = 28;
  if((sds_id_swepam_dengi3 = SDcreate(sd_id, "DENGI_DumpRecDat", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> SDcreate: Couldn't create DENGI_DumpRecDat");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w3 = SDidtoref(sds_id_swepam_dengi3)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> SDidtoref: Couldn't get ref for DENGI_DumpRecDat");

  if((Vaddtagref(vgrp_id_swepam_dengi, DFTAG_NDG, sds_ref_w3)) == FAIL)
    print_swepam_dengi_error("init_cr_swepam_dengi -> Vaddtagref: Couldn't add SDS DENGI_DumpRecDat to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_dengi(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_dengi(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_dengi(struct DENGI DENGI_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_swepam_dengi_error();
void pack_swepam_dengi();

  odata = (uint8 *) malloc(sizeof(struct DENGI));
  pack_swepam_dengi(odata, &DENGI_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_swepam_dengi, recnum)==-1) {
		print_swepam_dengi_error("write_swepam_dengi -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_dengi, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_dengi_error("write_swepam_dengi -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 16;
  edges[2] = 3;
  if (SDwritedata(sds_id_swepam_dengi1,start,NULL,edges, (VOIDP)(DENGI_struc.StatRec)) ==FAIL)
    print_swepam_dengi_error("write_swepam_dengi -> SDwritedata: Problem writing StatRec data.");

  edges[1] = 16;
  edges[2] = 16;
  if (SDwritedata(sds_id_swepam_dengi2,start,NULL,edges, (VOIDP)(DENGI_struc.ScalarRecDat)) ==FAIL)
    print_swepam_dengi_error("write_swepam_dengi -> SDwritedata: Problem writing ScalarRecDat data.");

  edges[1] = 16;
  edges[2] = 28;
  if (SDwritedata(sds_id_swepam_dengi3,start,NULL,edges, (VOIDP)(DENGI_struc.DumpRecDat)) ==FAIL)
    print_swepam_dengi_error("write_swepam_dengi -> SDwritedata: Problem writing DumpRecDat data.");

  memset(&DENGI_struc, 0, sizeof(struct DENGI));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_dengi()
{
  VSdetach(vdata_id_swepam_dengi);
  Vdetach(vgrp_id_swepam_dengi);
  SDendaccess(sds_id_swepam_dengi1);
  SDendaccess(sds_id_swepam_dengi2);
  SDendaccess(sds_id_swepam_dengi3);
}

/*----     init access function    ----*/

int32 init_acc_swepam_dengi(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  static int32 sds_index3;
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_dengi_error();

  if((sds_index1=SDnametoindex(sd_id, "DENGI_StatRec" )) ==FAIL) {
      print_swepam_dengi_error("init_acc_swepam_dengi -> SDnametoindex: Couldn't find DENGI_StatRec");
      return(-1);
  }
  if((sds_id_swepam_dengi1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_swepam_dengi_error("init_acc_swepam_dengi -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "DENGI_ScalarRecDat" )) ==FAIL) {
      print_swepam_dengi_error("init_acc_swepam_dengi -> SDnametoindex: Couldn't find DENGI_ScalarRecDat");
      return(-1);
  }
  if((sds_id_swepam_dengi2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_swepam_dengi_error("init_acc_swepam_dengi -> SDselect: Couldn't select sds_index2");
      return(-1);
  }
  if((sds_index3=SDnametoindex(sd_id, "DENGI_DumpRecDat" )) ==FAIL) {
      print_swepam_dengi_error("init_acc_swepam_dengi -> SDnametoindex: Couldn't find DENGI_DumpRecDat");
      return(-1);
  }
  if((sds_id_swepam_dengi3=SDselect(sd_id, sds_index3)) ==FAIL) {
      print_swepam_dengi_error("init_acc_swepam_dengi -> SDselect: Couldn't select sds_index3");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "DENGI")) <= 0 ) {
    print_swepam_dengi_error("init_acc_swepam_dengi -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_dengi = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_dengi_error("init_acc_swepam_dengi -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_dengi, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_dengi,"output_sctime, collect_sctime, QAC, MinFrmIndx, EventFlag, DumpRecAdd, MinFrmChk")) {
      print_swepam_dengi_error("init_acc_swepam_dengi -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_dengi(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_dengi(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_dengi(struct DENGI *DENGI_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_dengi_error();
void unpack_swepam_dengi();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct DENGI));
  VSinquire(vdata_id_swepam_dengi, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_dengi, recnum_rd)==FAIL) {
          print_swepam_dengi_error("read_swepam_dengi -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 16;
  edges[2] = 3;

  if(SDreaddata(sds_id_swepam_dengi1,start,NULL,edges, (VOIDP)(DENGI_struc->StatRec )) ==FAIL) {
    print_swepam_dengi_error("read_swepam_dengi -> SDreaddata: Couldn't read StatRec");
    retval = -1;
  }
  edges[1] = 16;
  edges[2] = 16;

  if(SDreaddata(sds_id_swepam_dengi2,start,NULL,edges, (VOIDP)(DENGI_struc->ScalarRecDat )) ==FAIL) {
    print_swepam_dengi_error("read_swepam_dengi -> SDreaddata: Couldn't read ScalarRecDat");
    retval = -1;
  }
  edges[1] = 16;
  edges[2] = 28;

  if(SDreaddata(sds_id_swepam_dengi3,start,NULL,edges, (VOIDP)(DENGI_struc->DumpRecDat )) ==FAIL) {
    print_swepam_dengi_error("read_swepam_dengi -> SDreaddata: Couldn't read DumpRecDat");
    retval = -1;
  }
  if(VSread(vdata_id_swepam_dengi, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_dengi_error("read_swepam_dengi -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_dengi(odata, DENGI_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_dengi()
{
  VSdetach(vdata_id_swepam_dengi);
  SDendaccess(sds_id_swepam_dengi1);
  SDendaccess(sds_id_swepam_dengi2);
  SDendaccess(sds_id_swepam_dengi3);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_dengi(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_dengi_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_DENGI" )) ==FAIL)
    print_swepam_dengi_error("rd_Vgrp_swepam_dengi -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_dengi_error("rd_Vgrp_swepam_dengi -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_dengi_error("rd_Vgrp_swepam_dengi -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_dengi_error("rd_Vgrp_swepam_dengi -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_DENGI, HDstrlen(Vgrp_descrp_DENGI)) ==FAIL)
    print_swepam_dengi_error("rd_Vgrp_swepam_dengi -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_DENGI);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_dengi_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_dengi.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_dengi(uint8 *data, struct DENGI *DENGI_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &DENGI_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DENGI_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DENGI_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DENGI_ptr->MinFrmIndx[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &DENGI_ptr->EventFlag[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &DENGI_ptr->DumpRecAdd[0], ((2)*(16)) );
   ptr+= ((2)*(16));
   memcpy(data+ptr, &DENGI_ptr->MinFrmChk[0], ((1)*(16)) );
   ptr+= ((1)*(16));
}

/*----   unpack function    ----*/

void unpack_swepam_dengi(uint8 *data, struct DENGI *DENGI_ptr)
{
int32 ptr=0;

   memcpy(&DENGI_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DENGI_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DENGI_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DENGI_ptr->MinFrmIndx[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&DENGI_ptr->EventFlag[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&DENGI_ptr->DumpRecAdd[0], data+ptr,  ((2)*(16)) );
   ptr+= ((2)*(16));
   memcpy(&DENGI_ptr->MinFrmChk[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
}
int32 get_vgrp_id_swepam_dengi() {return(vgrp_id_swepam_dengi);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_dengi(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_dengi.h' is shown below, it was used to create the data in the Vgroup named 'VG_DENGI'.\n\n");
  strcat(wr_strval,"/* Id: swepam_dengi.h,v 1.2 1997/07/17 00:07:04 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct DENGI               /* Engineering Mode */\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;   /* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;  /* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint8  QAC;             /* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8  MinFrmIndx[16];    /* minor frame index (0-127). element[0]=NULL*/\n");
  strcat(wr_strval,"  uint8  EventFlag[16];     /* Event flags. element 0 not reported */\n");
  strcat(wr_strval,"  uint8  StatRec[16][3];    /* 3 status record/frame. frame 0 no data */\n");
  strcat(wr_strval,"  uint16 ScalarRecDat[16][16]; /* 16 Data Channel words per Scaler Record */\n");
  strcat(wr_strval,"  uint16 DumpRecAdd[16];   /* address of 1st byte of memory dump */\n");
  strcat(wr_strval,"  uint8  DumpRecDat[16][28];   /* memory dump data */\n");
  strcat(wr_strval,"  uint8  MinFrmChk[16];     /* 2's compliment checksum */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
