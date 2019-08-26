/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: cris_level2_data_counts.h,v 1.1 2000/08/01 23:43:32 asc Exp  */

#include "cris_level2_data_counts.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_cris_level2_data_counts;
static int32 vdata_id_cris_level2_data_counts;

static int32 sds_id_cris_level2_data_counts1, sds_id_cris_level2_data_counts2, sds_id_cris_level2_data_counts3, sds_id_cris_level2_data_counts4;

  /* 1157 is the size of cris_level2_data_counts.h + 1 added line */
char Vgrp_descrp_CRIS_data_counts[1157];

/****----  init create function  ----****/

int32 init_cr_cris_level2_data_counts(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2, sds_ref_w3, sds_ref_w4;
  int32 dim_sizes[4];
  int32 rank;

  int32 wr_Vgrp_desc_cris_level2_data_counts();

  void print_cris_level2_data_counts_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_cris_level2_data_counts = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_cris_level2_data_counts, "VG_CRIS_data_counts"); 
  Vsetclass(vgrp_id_cris_level2_data_counts, "VG_CRIS_LEVEL2_DATA_COUNTS");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_CRIS_data_counts" )) ==FAIL) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_cris_level2_data_counts(Vgrp_descrp_CRIS_data_counts);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_CRIS_data_counts, sizeof(Vgrp_descrp_CRIS_data_counts))) ==FAIL) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_cris_level2_data_counts = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_cris_level2_data_counts, "CRIS_data_counts");
  VSsetclass(vdata_id_cris_level2_data_counts, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_cris_level2_data_counts, vdata_id_cris_level2_data_counts)) ==FAIL) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_cris_level2_data_counts, "number_of_elements", DFNT_UINT16, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define number_of_elements");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "number_of_data_points_abundant", DFNT_UINT32, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define number_of_data_points_abundant");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "number_of_data_points_rare", DFNT_UINT32, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define number_of_data_points_rare");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "abundant", DFNT_UINT8, (NUMBER_OF_ELEMENTS_ABUNDANT) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define abundant");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "time_increment_abundant", DFNT_UINT32, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define time_increment_abundant");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "start_time_abundant", DFNT_UINT32, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define start_time_abundant");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "stop_time_abundant", DFNT_UINT32, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define stop_time_abundant");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "rare", DFNT_UINT8, (NUMBER_OF_ELEMENTS_RARE) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define rare");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "time_increment_rare", DFNT_UINT32, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define time_increment_rare");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "start_time_rare", DFNT_UINT32, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define start_time_rare");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "stop_time_rare", DFNT_UINT32, (1) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define stop_time_rare");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "time_rare", DFNT_UINT32, (NUMBER_OF_POINTS_RARE) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define time_rare");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_counts, "livetime_rare", DFNT_FLOAT32, (NUMBER_OF_POINTS_RARE) )) {
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSfdefine: Couldn't define livetime_rare");
    retval = -1;
  }

  if (VSsetfields(vdata_id_cris_level2_data_counts,"number_of_elements, number_of_data_points_abundant, number_of_data_points_rare, abundant, time_increment_abundant, start_time_abundant, stop_time_abundant, rare, time_increment_rare, start_time_rare, stop_time_rare, time_rare, livetime_rare")){
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 2;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = NUMBER_OF_POINTS_ABUNDANT;
  if((sds_id_cris_level2_data_counts1 = SDcreate(sd_id, "CRIS_data_counts_time_abundant", DFNT_UINT32, rank, dim_sizes)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> SDcreate: Couldn't create CRIS_data_counts_time_abundant");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_cris_level2_data_counts1)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> SDidtoref: Couldn't get ref for CRIS_data_counts_time_abundant");

  if((Vaddtagref(vgrp_id_cris_level2_data_counts, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> Vaddtagref: Couldn't add SDS CRIS_data_counts_time_abundant to Vgrp");

  rank = 2;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = NUMBER_OF_POINTS_ABUNDANT;
  if((sds_id_cris_level2_data_counts2 = SDcreate(sd_id, "CRIS_data_counts_livetime_abundant", DFNT_FLOAT32, rank, dim_sizes)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> SDcreate: Couldn't create CRIS_data_counts_livetime_abundant");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_cris_level2_data_counts2)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> SDidtoref: Couldn't get ref for CRIS_data_counts_livetime_abundant");

  if((Vaddtagref(vgrp_id_cris_level2_data_counts, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> Vaddtagref: Couldn't add SDS CRIS_data_counts_livetime_abundant to Vgrp");

  rank = 4;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = NUMBER_OF_POINTS_ABUNDANT;
  dim_sizes[2] = NUMBER_OF_ELEMENTS_ABUNDANT;
  dim_sizes[3] = NUMBER_OF_ENERGY_LEVELS;
  if((sds_id_cris_level2_data_counts3 = SDcreate(sd_id, "CRIS_data_counts_Z_events_abundant", DFNT_INT16, rank, dim_sizes)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> SDcreate: Couldn't create CRIS_data_counts_Z_events_abundant");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w3 = SDidtoref(sds_id_cris_level2_data_counts3)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> SDidtoref: Couldn't get ref for CRIS_data_counts_Z_events_abundant");

  if((Vaddtagref(vgrp_id_cris_level2_data_counts, DFTAG_NDG, sds_ref_w3)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> Vaddtagref: Couldn't add SDS CRIS_data_counts_Z_events_abundant to Vgrp");

  rank = 4;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = NUMBER_OF_POINTS_RARE;
  dim_sizes[2] = NUMBER_OF_ELEMENTS_RARE;
  dim_sizes[3] = NUMBER_OF_ENERGY_LEVELS;
  if((sds_id_cris_level2_data_counts4 = SDcreate(sd_id, "CRIS_data_counts_Z_events_rare", DFNT_INT16, rank, dim_sizes)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> SDcreate: Couldn't create CRIS_data_counts_Z_events_rare");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w4 = SDidtoref(sds_id_cris_level2_data_counts4)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> SDidtoref: Couldn't get ref for CRIS_data_counts_Z_events_rare");

  if((Vaddtagref(vgrp_id_cris_level2_data_counts, DFTAG_NDG, sds_ref_w4)) == FAIL)
    print_cris_level2_data_counts_error("init_cr_cris_level2_data_counts -> Vaddtagref: Couldn't add SDS CRIS_data_counts_Z_events_rare to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_cris_level2_data_counts(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_cris_level2_data_counts(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_cris_level2_data_counts(struct CRIS_data_counts CRIS_data_counts_struc, int32 recnum)
{
  int32 start[4], edges[4];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_cris_level2_data_counts_error();
void pack_cris_level2_data_counts();

  odata = (uint8 *) malloc(sizeof(struct CRIS_data_counts));
  pack_cris_level2_data_counts(odata, &CRIS_data_counts_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_cris_level2_data_counts, recnum)==-1) {
		print_cris_level2_data_counts_error("write_cris_level2_data_counts -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_cris_level2_data_counts, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_cris_level2_data_counts_error("write_cris_level2_data_counts -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  edges[0] = 1;

  edges[1] = NUMBER_OF_POINTS_ABUNDANT;
  if (SDwritedata(sds_id_cris_level2_data_counts1,start,NULL,edges, (VOIDP)(CRIS_data_counts_struc.time_abundant)) ==FAIL)
    print_cris_level2_data_counts_error("write_cris_level2_data_counts -> SDwritedata: Problem writing time_abundant data.");

  edges[1] = NUMBER_OF_POINTS_ABUNDANT;
  if (SDwritedata(sds_id_cris_level2_data_counts2,start,NULL,edges, (VOIDP)(CRIS_data_counts_struc.livetime_abundant)) ==FAIL)
    print_cris_level2_data_counts_error("write_cris_level2_data_counts -> SDwritedata: Problem writing livetime_abundant data.");

  edges[1] = NUMBER_OF_POINTS_ABUNDANT;
  edges[2] = NUMBER_OF_ELEMENTS_ABUNDANT;
  edges[3] = NUMBER_OF_ENERGY_LEVELS;
  if (SDwritedata(sds_id_cris_level2_data_counts3,start,NULL,edges, (VOIDP)(CRIS_data_counts_struc.Z_events_abundant)) ==FAIL)
    print_cris_level2_data_counts_error("write_cris_level2_data_counts -> SDwritedata: Problem writing Z_events_abundant data.");

  edges[1] = NUMBER_OF_POINTS_RARE;
  edges[2] = NUMBER_OF_ELEMENTS_RARE;
  edges[3] = NUMBER_OF_ENERGY_LEVELS;
  if (SDwritedata(sds_id_cris_level2_data_counts4,start,NULL,edges, (VOIDP)(CRIS_data_counts_struc.Z_events_rare)) ==FAIL)
    print_cris_level2_data_counts_error("write_cris_level2_data_counts -> SDwritedata: Problem writing Z_events_rare data.");

  memset(&CRIS_data_counts_struc, 0, sizeof(struct CRIS_data_counts));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_cris_level2_data_counts()
{
  VSdetach(vdata_id_cris_level2_data_counts);
  Vdetach(vgrp_id_cris_level2_data_counts);
  SDendaccess(sds_id_cris_level2_data_counts1);
  SDendaccess(sds_id_cris_level2_data_counts2);
  SDendaccess(sds_id_cris_level2_data_counts3);
  SDendaccess(sds_id_cris_level2_data_counts4);
}

/*----     init access function    ----*/

int32 init_acc_cris_level2_data_counts(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  static int32 sds_index3;
  static int32 sds_index4;
  int32 vdata_ref;
  int32 num_rec;

  void print_cris_level2_data_counts_error();

  if((sds_index1=SDnametoindex(sd_id, "CRIS_data_counts_time_abundant" )) ==FAIL) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> SDnametoindex: Couldn't find CRIS_data_counts_time_abundant");
      return(-1);
  }
  if((sds_id_cris_level2_data_counts1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "CRIS_data_counts_livetime_abundant" )) ==FAIL) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> SDnametoindex: Couldn't find CRIS_data_counts_livetime_abundant");
      return(-1);
  }
  if((sds_id_cris_level2_data_counts2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> SDselect: Couldn't select sds_index2");
      return(-1);
  }
  if((sds_index3=SDnametoindex(sd_id, "CRIS_data_counts_Z_events_abundant" )) ==FAIL) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> SDnametoindex: Couldn't find CRIS_data_counts_Z_events_abundant");
      return(-1);
  }
  if((sds_id_cris_level2_data_counts3=SDselect(sd_id, sds_index3)) ==FAIL) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> SDselect: Couldn't select sds_index3");
      return(-1);
  }
  if((sds_index4=SDnametoindex(sd_id, "CRIS_data_counts_Z_events_rare" )) ==FAIL) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> SDnametoindex: Couldn't find CRIS_data_counts_Z_events_rare");
      return(-1);
  }
  if((sds_id_cris_level2_data_counts4=SDselect(sd_id, sds_index4)) ==FAIL) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> SDselect: Couldn't select sds_index4");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "CRIS_data_counts")) <= 0 ) {
    print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_cris_level2_data_counts = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_cris_level2_data_counts, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_cris_level2_data_counts,"number_of_elements, number_of_data_points_abundant, number_of_data_points_rare, abundant, time_increment_abundant, start_time_abundant, stop_time_abundant, rare, time_increment_rare, start_time_rare, stop_time_rare, time_rare, livetime_rare")) {
      print_cris_level2_data_counts_error("init_acc_cris_level2_data_counts -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_cris_level2_data_counts(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_cris_level2_data_counts(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_cris_level2_data_counts(struct CRIS_data_counts *CRIS_data_counts_struc, int32 recnum_rd)
{
int32 start[4], edges[4];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_cris_level2_data_counts_error();
void unpack_cris_level2_data_counts();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct CRIS_data_counts));
  VSinquire(vdata_id_cris_level2_data_counts, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_cris_level2_data_counts, recnum_rd)==FAIL) {
          print_cris_level2_data_counts_error("read_cris_level2_data_counts -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = NUMBER_OF_POINTS_ABUNDANT;

  if(SDreaddata(sds_id_cris_level2_data_counts1,start,NULL,edges, (VOIDP)(CRIS_data_counts_struc->time_abundant )) ==FAIL) {
    print_cris_level2_data_counts_error("read_cris_level2_data_counts -> SDreaddata: Couldn't read time_abundant");
    retval = -1;
  }
  edges[1] = NUMBER_OF_POINTS_ABUNDANT;

  if(SDreaddata(sds_id_cris_level2_data_counts2,start,NULL,edges, (VOIDP)(CRIS_data_counts_struc->livetime_abundant )) ==FAIL) {
    print_cris_level2_data_counts_error("read_cris_level2_data_counts -> SDreaddata: Couldn't read livetime_abundant");
    retval = -1;
  }
  edges[1] = NUMBER_OF_POINTS_ABUNDANT;
  edges[2] = NUMBER_OF_ELEMENTS_ABUNDANT;
  edges[3] = NUMBER_OF_ENERGY_LEVELS;

  if(SDreaddata(sds_id_cris_level2_data_counts3,start,NULL,edges, (VOIDP)(CRIS_data_counts_struc->Z_events_abundant )) ==FAIL) {
    print_cris_level2_data_counts_error("read_cris_level2_data_counts -> SDreaddata: Couldn't read Z_events_abundant");
    retval = -1;
  }
  edges[1] = NUMBER_OF_POINTS_RARE;
  edges[2] = NUMBER_OF_ELEMENTS_RARE;
  edges[3] = NUMBER_OF_ENERGY_LEVELS;

  if(SDreaddata(sds_id_cris_level2_data_counts4,start,NULL,edges, (VOIDP)(CRIS_data_counts_struc->Z_events_rare )) ==FAIL) {
    print_cris_level2_data_counts_error("read_cris_level2_data_counts -> SDreaddata: Couldn't read Z_events_rare");
    retval = -1;
  }
  if(VSread(vdata_id_cris_level2_data_counts, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_cris_level2_data_counts_error("read_cris_level2_data_counts -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_cris_level2_data_counts(odata, CRIS_data_counts_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_cris_level2_data_counts()
{
  VSdetach(vdata_id_cris_level2_data_counts);
  SDendaccess(sds_id_cris_level2_data_counts1);
  SDendaccess(sds_id_cris_level2_data_counts2);
  SDendaccess(sds_id_cris_level2_data_counts3);
  SDendaccess(sds_id_cris_level2_data_counts4);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_cris_level2_data_counts(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_cris_level2_data_counts_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_CRIS_data_counts" )) ==FAIL)
    print_cris_level2_data_counts_error("rd_Vgrp_cris_level2_data_counts -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_cris_level2_data_counts_error("rd_Vgrp_cris_level2_data_counts -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_cris_level2_data_counts_error("rd_Vgrp_cris_level2_data_counts -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_cris_level2_data_counts_error("rd_Vgrp_cris_level2_data_counts -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_CRIS_data_counts, HDstrlen(Vgrp_descrp_CRIS_data_counts)) ==FAIL)
    print_cris_level2_data_counts_error("rd_Vgrp_cris_level2_data_counts -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_CRIS_data_counts);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_cris_level2_data_counts_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_cris_level2_data_counts.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_cris_level2_data_counts(uint8 *data, struct CRIS_data_counts *CRIS_data_counts_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &CRIS_data_counts_ptr->number_of_elements, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->number_of_data_points_abundant, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->number_of_data_points_rare, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->abundant[0], ((1)*(NUMBER_OF_ELEMENTS_ABUNDANT)) );
   ptr+= ((1)*(NUMBER_OF_ELEMENTS_ABUNDANT));
   memcpy(data+ptr, &CRIS_data_counts_ptr->time_increment_abundant, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->start_time_abundant, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->stop_time_abundant, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->rare[0], ((1)*(NUMBER_OF_ELEMENTS_RARE)) );
   ptr+= ((1)*(NUMBER_OF_ELEMENTS_RARE));
   memcpy(data+ptr, &CRIS_data_counts_ptr->time_increment_rare, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->start_time_rare, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->stop_time_rare, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_counts_ptr->time_rare[0], ((4)*(NUMBER_OF_POINTS_RARE)) );
   ptr+= ((4)*(NUMBER_OF_POINTS_RARE));
   memcpy(data+ptr, &CRIS_data_counts_ptr->livetime_rare[0], ((4)*(NUMBER_OF_POINTS_RARE)) );
   ptr+= ((4)*(NUMBER_OF_POINTS_RARE));
}

/*----   unpack function    ----*/

void unpack_cris_level2_data_counts(uint8 *data, struct CRIS_data_counts *CRIS_data_counts_ptr)
{
int32 ptr=0;

   memcpy(&CRIS_data_counts_ptr->number_of_elements, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&CRIS_data_counts_ptr->number_of_data_points_abundant, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_counts_ptr->number_of_data_points_rare, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_counts_ptr->abundant[0], data+ptr,  ((1)*(NUMBER_OF_ELEMENTS_ABUNDANT)) );
   ptr+= ((1)*(NUMBER_OF_ELEMENTS_ABUNDANT));
   memcpy(&CRIS_data_counts_ptr->time_increment_abundant, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_counts_ptr->start_time_abundant, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_counts_ptr->stop_time_abundant, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_counts_ptr->rare[0], data+ptr,  ((1)*(NUMBER_OF_ELEMENTS_RARE)) );
   ptr+= ((1)*(NUMBER_OF_ELEMENTS_RARE));
   memcpy(&CRIS_data_counts_ptr->time_increment_rare, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_counts_ptr->start_time_rare, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_counts_ptr->stop_time_rare, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_counts_ptr->time_rare[0], data+ptr,  ((4)*(NUMBER_OF_POINTS_RARE)) );
   ptr+= ((4)*(NUMBER_OF_POINTS_RARE));
   memcpy(&CRIS_data_counts_ptr->livetime_rare[0], data+ptr,  ((4)*(NUMBER_OF_POINTS_RARE)) );
   ptr+= ((4)*(NUMBER_OF_POINTS_RARE));
}
int32 get_vgrp_id_cris_level2_data_counts() {return(vgrp_id_cris_level2_data_counts);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_cris_level2_data_counts(char *wr_strval)
{
  strcpy(wr_strval, "The file 'cris_level2_data_counts.h' is shown below, it was used to create the data in the Vgroup named 'VG_CRIS_data_counts'.\n\n");
  strcat(wr_strval,"/* Id: cris_level2_data_counts.h,v 1.1 2000/08/01 23:43:32 asc Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"cris_sizes.h\" \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct CRIS_data_counts {\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint16 number_of_elements;\n");
  strcat(wr_strval,"  uint32 number_of_data_points_abundant;\n");
  strcat(wr_strval,"  uint32 number_of_data_points_rare;\n");
  strcat(wr_strval,"  \n");
  strcat(wr_strval,"  uint8   abundant[NUMBER_OF_ELEMENTS_ABUNDANT];\n");
  strcat(wr_strval,"  uint32  time_increment_abundant;\n");
  strcat(wr_strval,"  uint32  start_time_abundant;\n");
  strcat(wr_strval,"  uint32  stop_time_abundant;\n");
  strcat(wr_strval,"  \n");
  strcat(wr_strval,"  uint32  time_abundant[NUMBER_OF_POINTS_ABUNDANT];\n");
  strcat(wr_strval,"  float32 livetime_abundant[NUMBER_OF_POINTS_ABUNDANT];\n");
  strcat(wr_strval,"  int16   Z_events_abundant[NUMBER_OF_POINTS_ABUNDANT][NUMBER_OF_ELEMENTS_ABUNDANT][NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8   rare[NUMBER_OF_ELEMENTS_RARE];\n");
  strcat(wr_strval,"  uint32  time_increment_rare;    \n");
  strcat(wr_strval,"  uint32  start_time_rare;\n");
  strcat(wr_strval,"  uint32  stop_time_rare;\n");
  strcat(wr_strval,"  \n");
  strcat(wr_strval,"  uint32  time_rare[NUMBER_OF_POINTS_RARE];\n");
  strcat(wr_strval,"  float32 livetime_rare[NUMBER_OF_POINTS_RARE];\n");
  strcat(wr_strval,"  int16   Z_events_rare[NUMBER_OF_POINTS_RARE][NUMBER_OF_ELEMENTS_RARE][NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  return(0);
}
