/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_mpha.h,v 1.2 1997/05/06 19:11:02 jeff Exp  */

#include "s3_mpha.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_mpha;
static int32 vdata_id_s3_mpha;

static int32 sds_id_s3_mpha1, sds_id_s3_mpha2, sds_id_s3_mpha3, sds_id_s3_mpha4, sds_id_s3_mpha5, sds_id_s3_mpha6;

  /* 1150 is the size of s3_mpha.h + 1 added line */
char Vgrp_descrp_mpha[1150];

/****----  init create function  ----****/

int32 init_cr_s3_mpha(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2, sds_ref_w3, sds_ref_w4, sds_ref_w5, sds_ref_w6;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_mpha();

  void print_s3_mpha_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_mpha = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_mpha_error("init_cr_s3_mpha -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_mpha, "VG_mpha"); 
  Vsetclass(vgrp_id_s3_mpha, "VG_S3_MPHA");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_mpha" )) ==FAIL) {
    print_s3_mpha_error("init_cr_s3_mpha -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_mpha(Vgrp_descrp_mpha);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_mpha_error("init_cr_s3_mpha -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_mpha, sizeof(Vgrp_descrp_mpha))) ==FAIL) {
    print_s3_mpha_error("init_cr_s3_mpha -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_mpha = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_mpha_error("init_cr_s3_mpha -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_mpha, "mpha");
  VSsetclass(vdata_id_s3_mpha, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_mpha, vdata_id_s3_mpha)) ==FAIL) {
    print_s3_mpha_error("init_cr_s3_mpha -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_mpha, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_mpha_error("init_cr_s3_mpha -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mpha, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_mpha_error("init_cr_s3_mpha -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mpha, "QAC", DFNT_UINT32, (1) )) {
    print_s3_mpha_error("init_cr_s3_mpha -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mpha, "concat", DFNT_UINT8, (1) )) {
    print_s3_mpha_error("init_cr_s3_mpha -> VSfdefine: Couldn't define concat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mpha, "elements", DFNT_UINT32, (1) )) {
    print_s3_mpha_error("init_cr_s3_mpha -> VSfdefine: Couldn't define elements");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_mpha,"sctime_readout, sctime_collection, QAC, concat, elements")){
    print_s3_mpha_error("init_cr_s3_mpha -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWIMS_PHA_CYCLEN;
  dim_sizes[2] = SWIMS_PHA_CYCPERSR;
  if((sds_id_s3_mpha1 = SDcreate(sd_id, "mpha_range", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDcreate: Couldn't create mpha_range");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_mpha1)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDidtoref: Couldn't get ref for mpha_range");

  if((Vaddtagref(vgrp_id_s3_mpha, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> Vaddtagref: Couldn't add SDS mpha_range to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWIMS_PHA_CYCLEN;
  dim_sizes[2] = SWIMS_PHA_CYCPERSR;
  if((sds_id_s3_mpha2 = SDcreate(sd_id, "mpha_sector", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDcreate: Couldn't create mpha_sector");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_s3_mpha2)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDidtoref: Couldn't get ref for mpha_sector");

  if((Vaddtagref(vgrp_id_s3_mpha, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> Vaddtagref: Couldn't add SDS mpha_sector to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWIMS_PHA_CYCLEN;
  dim_sizes[2] = SWIMS_PHA_CYCPERSR;
  if((sds_id_s3_mpha3 = SDcreate(sd_id, "mpha_stamp", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDcreate: Couldn't create mpha_stamp");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w3 = SDidtoref(sds_id_s3_mpha3)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDidtoref: Couldn't get ref for mpha_stamp");

  if((Vaddtagref(vgrp_id_s3_mpha, DFTAG_NDG, sds_ref_w3)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> Vaddtagref: Couldn't add SDS mpha_stamp to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWIMS_PHA_CYCLEN;
  dim_sizes[2] = SWIMS_PHA_CYCPERSR;
  if((sds_id_s3_mpha4 = SDcreate(sd_id, "mpha_stopk1", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDcreate: Couldn't create mpha_stopk1");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w4 = SDidtoref(sds_id_s3_mpha4)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDidtoref: Couldn't get ref for mpha_stopk1");

  if((Vaddtagref(vgrp_id_s3_mpha, DFTAG_NDG, sds_ref_w4)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> Vaddtagref: Couldn't add SDS mpha_stopk1 to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWIMS_PHA_CYCLEN;
  dim_sizes[2] = SWIMS_PHA_CYCPERSR;
  if((sds_id_s3_mpha5 = SDcreate(sd_id, "mpha_stopk2", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDcreate: Couldn't create mpha_stopk2");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w5 = SDidtoref(sds_id_s3_mpha5)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDidtoref: Couldn't get ref for mpha_stopk2");

  if((Vaddtagref(vgrp_id_s3_mpha, DFTAG_NDG, sds_ref_w5)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> Vaddtagref: Couldn't add SDS mpha_stopk2 to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWIMS_PHA_CYCLEN;
  dim_sizes[2] = SWIMS_PHA_CYCPERSR;
  if((sds_id_s3_mpha6 = SDcreate(sd_id, "mpha_tof", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDcreate: Couldn't create mpha_tof");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w6 = SDidtoref(sds_id_s3_mpha6)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> SDidtoref: Couldn't get ref for mpha_tof");

  if((Vaddtagref(vgrp_id_s3_mpha, DFTAG_NDG, sds_ref_w6)) == FAIL)
    print_s3_mpha_error("init_cr_s3_mpha -> Vaddtagref: Couldn't add SDS mpha_tof to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_mpha(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_mpha(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_mpha(struct mpha mpha_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_mpha_error();
void pack_s3_mpha();

  odata = (uint8 *) malloc(sizeof(struct mpha));
  pack_s3_mpha(odata, &mpha_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_mpha, recnum)==-1) {
		print_s3_mpha_error("write_s3_mpha -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_mpha, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_mpha_error("write_s3_mpha -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_mpha1,start,NULL,edges, (VOIDP)(mpha_struc.range)) ==FAIL)
    print_s3_mpha_error("write_s3_mpha -> SDwritedata: Problem writing range data.");

  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_mpha2,start,NULL,edges, (VOIDP)(mpha_struc.sector)) ==FAIL)
    print_s3_mpha_error("write_s3_mpha -> SDwritedata: Problem writing sector data.");

  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_mpha3,start,NULL,edges, (VOIDP)(mpha_struc.stamp)) ==FAIL)
    print_s3_mpha_error("write_s3_mpha -> SDwritedata: Problem writing stamp data.");

  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_mpha4,start,NULL,edges, (VOIDP)(mpha_struc.stopk1)) ==FAIL)
    print_s3_mpha_error("write_s3_mpha -> SDwritedata: Problem writing stopk1 data.");

  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_mpha5,start,NULL,edges, (VOIDP)(mpha_struc.stopk2)) ==FAIL)
    print_s3_mpha_error("write_s3_mpha -> SDwritedata: Problem writing stopk2 data.");

  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_mpha6,start,NULL,edges, (VOIDP)(mpha_struc.tof)) ==FAIL)
    print_s3_mpha_error("write_s3_mpha -> SDwritedata: Problem writing tof data.");

  memset(&mpha_struc, 0, sizeof(struct mpha));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_mpha()
{
  VSdetach(vdata_id_s3_mpha);
  Vdetach(vgrp_id_s3_mpha);
  SDendaccess(sds_id_s3_mpha1);
  SDendaccess(sds_id_s3_mpha2);
  SDendaccess(sds_id_s3_mpha3);
  SDendaccess(sds_id_s3_mpha4);
  SDendaccess(sds_id_s3_mpha5);
  SDendaccess(sds_id_s3_mpha6);
}

/*----     init access function    ----*/

int32 init_acc_s3_mpha(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  static int32 sds_index3;
  static int32 sds_index4;
  static int32 sds_index5;
  static int32 sds_index6;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_mpha_error();

  if((sds_index1=SDnametoindex(sd_id, "mpha_range" )) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDnametoindex: Couldn't find mpha_range");
      return(-1);
  }
  if((sds_id_s3_mpha1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "mpha_sector" )) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDnametoindex: Couldn't find mpha_sector");
      return(-1);
  }
  if((sds_id_s3_mpha2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDselect: Couldn't select sds_index2");
      return(-1);
  }
  if((sds_index3=SDnametoindex(sd_id, "mpha_stamp" )) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDnametoindex: Couldn't find mpha_stamp");
      return(-1);
  }
  if((sds_id_s3_mpha3=SDselect(sd_id, sds_index3)) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDselect: Couldn't select sds_index3");
      return(-1);
  }
  if((sds_index4=SDnametoindex(sd_id, "mpha_stopk1" )) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDnametoindex: Couldn't find mpha_stopk1");
      return(-1);
  }
  if((sds_id_s3_mpha4=SDselect(sd_id, sds_index4)) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDselect: Couldn't select sds_index4");
      return(-1);
  }
  if((sds_index5=SDnametoindex(sd_id, "mpha_stopk2" )) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDnametoindex: Couldn't find mpha_stopk2");
      return(-1);
  }
  if((sds_id_s3_mpha5=SDselect(sd_id, sds_index5)) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDselect: Couldn't select sds_index5");
      return(-1);
  }
  if((sds_index6=SDnametoindex(sd_id, "mpha_tof" )) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDnametoindex: Couldn't find mpha_tof");
      return(-1);
  }
  if((sds_id_s3_mpha6=SDselect(sd_id, sds_index6)) ==FAIL) {
      print_s3_mpha_error("init_acc_s3_mpha -> SDselect: Couldn't select sds_index6");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "mpha")) <= 0 ) {
    print_s3_mpha_error("init_acc_s3_mpha -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_mpha = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_mpha_error("init_acc_s3_mpha -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_mpha, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_mpha,"sctime_readout, sctime_collection, QAC, concat, elements")) {
      print_s3_mpha_error("init_acc_s3_mpha -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_mpha(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_mpha(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_mpha(struct mpha *mpha_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_mpha_error();
void unpack_s3_mpha();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct mpha));
  VSinquire(vdata_id_s3_mpha, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_mpha, recnum_rd)==FAIL) {
          print_s3_mpha_error("read_s3_mpha -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_mpha1,start,NULL,edges, (VOIDP)(mpha_struc->range )) ==FAIL) {
    print_s3_mpha_error("read_s3_mpha -> SDreaddata: Couldn't read range");
    retval = -1;
  }
  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_mpha2,start,NULL,edges, (VOIDP)(mpha_struc->sector )) ==FAIL) {
    print_s3_mpha_error("read_s3_mpha -> SDreaddata: Couldn't read sector");
    retval = -1;
  }
  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_mpha3,start,NULL,edges, (VOIDP)(mpha_struc->stamp )) ==FAIL) {
    print_s3_mpha_error("read_s3_mpha -> SDreaddata: Couldn't read stamp");
    retval = -1;
  }
  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_mpha4,start,NULL,edges, (VOIDP)(mpha_struc->stopk1 )) ==FAIL) {
    print_s3_mpha_error("read_s3_mpha -> SDreaddata: Couldn't read stopk1");
    retval = -1;
  }
  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_mpha5,start,NULL,edges, (VOIDP)(mpha_struc->stopk2 )) ==FAIL) {
    print_s3_mpha_error("read_s3_mpha -> SDreaddata: Couldn't read stopk2");
    retval = -1;
  }
  edges[1] = SWIMS_PHA_CYCLEN;
  edges[2] = SWIMS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_mpha6,start,NULL,edges, (VOIDP)(mpha_struc->tof )) ==FAIL) {
    print_s3_mpha_error("read_s3_mpha -> SDreaddata: Couldn't read tof");
    retval = -1;
  }
  if(VSread(vdata_id_s3_mpha, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_mpha_error("read_s3_mpha -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_mpha(odata, mpha_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_mpha()
{
  VSdetach(vdata_id_s3_mpha);
  SDendaccess(sds_id_s3_mpha1);
  SDendaccess(sds_id_s3_mpha2);
  SDendaccess(sds_id_s3_mpha3);
  SDendaccess(sds_id_s3_mpha4);
  SDendaccess(sds_id_s3_mpha5);
  SDendaccess(sds_id_s3_mpha6);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_mpha(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_mpha_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_mpha" )) ==FAIL)
    print_s3_mpha_error("rd_Vgrp_s3_mpha -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_mpha_error("rd_Vgrp_s3_mpha -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_mpha_error("rd_Vgrp_s3_mpha -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_mpha_error("rd_Vgrp_s3_mpha -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_mpha, HDstrlen(Vgrp_descrp_mpha)) ==FAIL)
    print_s3_mpha_error("rd_Vgrp_s3_mpha -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_mpha);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_mpha_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swims_mpha.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_mpha(uint8 *data, struct mpha *mpha_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &mpha_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mpha_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mpha_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mpha_ptr->concat, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &mpha_ptr->elements, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_mpha(uint8 *data, struct mpha *mpha_ptr)
{
int32 ptr=0;

   memcpy(&mpha_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mpha_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mpha_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mpha_ptr->concat, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&mpha_ptr->elements, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_s3_mpha() {return(vgrp_id_s3_mpha);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_mpha(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_mpha.h' is shown below, it was used to create the data in the Vgroup named 'VG_mpha'.\n\n");
  strcat(wr_strval,"/* Id: s3_mpha.h,v 1.2 1997/05/06 19:11:02 jeff Exp $           */\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SWIMS_PHA_CYCLEN    99           \n");
  strcat(wr_strval,"#define SWIMS_PHA_CYCPERSR  60      \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct mpha  {\n");
  strcat(wr_strval,"           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  QAC;         /*  number of missing frames in this SR */\n");
  strcat(wr_strval,"           uint8   concat;      /*  is the number of mpha structs     */\n");
  strcat(wr_strval,"           uint32  elements;    /*  number of pha events      */         \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"           uint8   range[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"           uint8   sector[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"           uint16  stamp[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"           uint16  stopk1[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"           uint16  stopk2[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"           uint16  tof[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"     \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
