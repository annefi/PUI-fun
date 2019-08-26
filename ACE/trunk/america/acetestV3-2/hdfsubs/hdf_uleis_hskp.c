/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: uleis_hskp.h,v 1.8 1997/11/14 23:57:55 steves Exp  */

#include "uleis_hskp.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_uleis_hskp;
static int32 vdata_id_uleis_hskp;

static int32 sds_id_uleis_hskp1, sds_id_uleis_hskp2;

  /* 3573 is the size of uleis_hskp.h + 1 added line */
char Vgrp_descrp_UHskpSet[3573];

/****----  init create function  ----****/

int32 init_cr_uleis_hskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_uleis_hskp();

  void print_uleis_hskp_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_uleis_hskp = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_uleis_hskp, "VG_UHskpSet"); 
  Vsetclass(vgrp_id_uleis_hskp, "VG_ULEIS_HSKP");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_UHskpSet" )) ==FAIL) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_uleis_hskp(Vgrp_descrp_UHskpSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_UHskpSet, sizeof(Vgrp_descrp_UHskpSet))) ==FAIL) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_uleis_hskp = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_uleis_hskp, "UHskpSet");
  VSsetclass(vdata_id_uleis_hskp, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_uleis_hskp, vdata_id_uleis_hskp)) ==FAIL) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_uleis_hskp, "output_sctime", DFNT_UINT32, (1) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "collect_sctime", DFNT_UINT32, (1) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "QAC", DFNT_UINT32, (1) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "chk_sum_chk", DFNT_UINT8, (1) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define chk_sum_chk");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "dump_flg", DFNT_UINT8, (129) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define dump_flg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "stat_tlm_flg", DFNT_UINT8, (129) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define stat_tlm_flg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "DeckTemp", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define DeckTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "lvps_voltage", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define lvps_voltage");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "total_cur", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define total_cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "lvps_cur_analg", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define lvps_cur_analg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "heater_cur", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define heater_cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "telescp_temp", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define telescp_temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "analg_elect_temp", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define analg_elect_temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "dpu_temp", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define dpu_temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "UPowBits", DFNT_UINT8, (8) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define UPowBits");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "PhaseAng", DFNT_UINT8, (NUMFRM) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define PhaseAng");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_hskp, "SunSenID", DFNT_UINT8, (NUMFRM) )) {
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSfdefine: Couldn't define SunSenID");
    retval = -1;
  }

  if (VSsetfields(vdata_id_uleis_hskp,"output_sctime, collect_sctime, QAC, chk_sum_chk, dump_flg, stat_tlm_flg, DeckTemp, lvps_voltage, total_cur, lvps_cur_analg, heater_cur, telescp_temp, analg_elect_temp, dpu_temp, UPowBits, PhaseAng, SunSenID")){
    print_uleis_hskp_error("init_cr_uleis_hskp -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 2;
  dim_sizes[2] = 8;
  if((sds_id_uleis_hskp1 = SDcreate(sd_id, "UHskpSet_SunPulLat", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_uleis_hskp_error("init_cr_uleis_hskp -> SDcreate: Couldn't create UHskpSet_SunPulLat");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_uleis_hskp1)) == FAIL)
    print_uleis_hskp_error("init_cr_uleis_hskp -> SDidtoref: Couldn't get ref for UHskpSet_SunPulLat");

  if((Vaddtagref(vgrp_id_uleis_hskp, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_uleis_hskp_error("init_cr_uleis_hskp -> Vaddtagref: Couldn't add SDS UHskpSet_SunPulLat to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 2;
  dim_sizes[2] = 8;
  if((sds_id_uleis_hskp2 = SDcreate(sd_id, "UHskpSet_SunPulDat", DFNT_UINT32, rank, dim_sizes)) == FAIL)
    print_uleis_hskp_error("init_cr_uleis_hskp -> SDcreate: Couldn't create UHskpSet_SunPulDat");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_uleis_hskp2)) == FAIL)
    print_uleis_hskp_error("init_cr_uleis_hskp -> SDidtoref: Couldn't get ref for UHskpSet_SunPulDat");

  if((Vaddtagref(vgrp_id_uleis_hskp, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_uleis_hskp_error("init_cr_uleis_hskp -> Vaddtagref: Couldn't add SDS UHskpSet_SunPulDat to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_uleis_hskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_uleis_hskp(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_uleis_hskp(struct UHskpSet UHskpSet_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_uleis_hskp_error();
void pack_uleis_hskp();

  odata = (uint8 *) malloc(sizeof(struct UHskpSet));
  pack_uleis_hskp(odata, &UHskpSet_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_uleis_hskp, recnum)==-1) {
		print_uleis_hskp_error("write_uleis_hskp -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_uleis_hskp, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_uleis_hskp_error("write_uleis_hskp -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 2;
  edges[2] = 8;
  if (SDwritedata(sds_id_uleis_hskp1,start,NULL,edges, (VOIDP)(UHskpSet_struc.SunPulLat)) ==FAIL)
    print_uleis_hskp_error("write_uleis_hskp -> SDwritedata: Problem writing SunPulLat data.");

  edges[1] = 2;
  edges[2] = 8;
  if (SDwritedata(sds_id_uleis_hskp2,start,NULL,edges, (VOIDP)(UHskpSet_struc.SunPulDat)) ==FAIL)
    print_uleis_hskp_error("write_uleis_hskp -> SDwritedata: Problem writing SunPulDat data.");

  memset(&UHskpSet_struc, 0, sizeof(struct UHskpSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_uleis_hskp()
{
  VSdetach(vdata_id_uleis_hskp);
  Vdetach(vgrp_id_uleis_hskp);
  SDendaccess(sds_id_uleis_hskp1);
  SDendaccess(sds_id_uleis_hskp2);
}

/*----     init access function    ----*/

int32 init_acc_uleis_hskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  int32 vdata_ref;
  int32 num_rec;

  void print_uleis_hskp_error();

  if((sds_index1=SDnametoindex(sd_id, "UHskpSet_SunPulLat" )) ==FAIL) {
      print_uleis_hskp_error("init_acc_uleis_hskp -> SDnametoindex: Couldn't find UHskpSet_SunPulLat");
      return(-1);
  }
  if((sds_id_uleis_hskp1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_uleis_hskp_error("init_acc_uleis_hskp -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "UHskpSet_SunPulDat" )) ==FAIL) {
      print_uleis_hskp_error("init_acc_uleis_hskp -> SDnametoindex: Couldn't find UHskpSet_SunPulDat");
      return(-1);
  }
  if((sds_id_uleis_hskp2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_uleis_hskp_error("init_acc_uleis_hskp -> SDselect: Couldn't select sds_index2");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "UHskpSet")) <= 0 ) {
    print_uleis_hskp_error("init_acc_uleis_hskp -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_uleis_hskp = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_uleis_hskp_error("init_acc_uleis_hskp -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_uleis_hskp, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_uleis_hskp,"output_sctime, collect_sctime, QAC, chk_sum_chk, dump_flg, stat_tlm_flg, DeckTemp, lvps_voltage, total_cur, lvps_cur_analg, heater_cur, telescp_temp, analg_elect_temp, dpu_temp, UPowBits, PhaseAng, SunSenID")) {
      print_uleis_hskp_error("init_acc_uleis_hskp -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_uleis_hskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_uleis_hskp(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_uleis_hskp(struct UHskpSet *UHskpSet_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_uleis_hskp_error();
void unpack_uleis_hskp();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct UHskpSet));
  VSinquire(vdata_id_uleis_hskp, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_uleis_hskp, recnum_rd)==FAIL) {
          print_uleis_hskp_error("read_uleis_hskp -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 2;
  edges[2] = 8;

  if(SDreaddata(sds_id_uleis_hskp1,start,NULL,edges, (VOIDP)(UHskpSet_struc->SunPulLat )) ==FAIL) {
    print_uleis_hskp_error("read_uleis_hskp -> SDreaddata: Couldn't read SunPulLat");
    retval = -1;
  }
  edges[1] = 2;
  edges[2] = 8;

  if(SDreaddata(sds_id_uleis_hskp2,start,NULL,edges, (VOIDP)(UHskpSet_struc->SunPulDat )) ==FAIL) {
    print_uleis_hskp_error("read_uleis_hskp -> SDreaddata: Couldn't read SunPulDat");
    retval = -1;
  }
  if(VSread(vdata_id_uleis_hskp, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_uleis_hskp_error("read_uleis_hskp -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_uleis_hskp(odata, UHskpSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_uleis_hskp()
{
  VSdetach(vdata_id_uleis_hskp);
  SDendaccess(sds_id_uleis_hskp1);
  SDendaccess(sds_id_uleis_hskp2);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_uleis_hskp(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_uleis_hskp_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_UHskpSet" )) ==FAIL)
    print_uleis_hskp_error("rd_Vgrp_uleis_hskp -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_uleis_hskp_error("rd_Vgrp_uleis_hskp -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_uleis_hskp_error("rd_Vgrp_uleis_hskp -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_uleis_hskp_error("rd_Vgrp_uleis_hskp -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_UHskpSet, HDstrlen(Vgrp_descrp_UHskpSet)) ==FAIL)
    print_uleis_hskp_error("rd_Vgrp_uleis_hskp -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_UHskpSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_uleis_hskp_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_uleis_hskp.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_uleis_hskp(uint8 *data, struct UHskpSet *UHskpSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &UHskpSet_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UHskpSet_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UHskpSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UHskpSet_ptr->chk_sum_chk, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UHskpSet_ptr->dump_flg[0], ((1)*(129)) );
   ptr+= ((1)*(129));
   memcpy(data+ptr, &UHskpSet_ptr->stat_tlm_flg[0], ((1)*(129)) );
   ptr+= ((1)*(129));
   memcpy(data+ptr, &UHskpSet_ptr->DeckTemp[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->lvps_voltage[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->total_cur[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->lvps_cur_analg[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->heater_cur[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->telescp_temp[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->analg_elect_temp[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->dpu_temp[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->UPowBits[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &UHskpSet_ptr->PhaseAng[0], ((1)*(NUMFRM)) );
   ptr+= ((1)*(NUMFRM));
   memcpy(data+ptr, &UHskpSet_ptr->SunSenID[0], ((1)*(NUMFRM)) );
   ptr+= ((1)*(NUMFRM));
}

/*----   unpack function    ----*/

void unpack_uleis_hskp(uint8 *data, struct UHskpSet *UHskpSet_ptr)
{
int32 ptr=0;

   memcpy(&UHskpSet_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UHskpSet_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UHskpSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UHskpSet_ptr->chk_sum_chk, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UHskpSet_ptr->dump_flg[0], data+ptr,  ((1)*(129)) );
   ptr+= ((1)*(129));
   memcpy(&UHskpSet_ptr->stat_tlm_flg[0], data+ptr,  ((1)*(129)) );
   ptr+= ((1)*(129));
   memcpy(&UHskpSet_ptr->DeckTemp[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->lvps_voltage[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->total_cur[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->lvps_cur_analg[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->heater_cur[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->telescp_temp[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->analg_elect_temp[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->dpu_temp[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->UPowBits[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&UHskpSet_ptr->PhaseAng[0], data+ptr,  ((1)*(NUMFRM)) );
   ptr+= ((1)*(NUMFRM));
   memcpy(&UHskpSet_ptr->SunSenID[0], data+ptr,  ((1)*(NUMFRM)) );
   ptr+= ((1)*(NUMFRM));
}
int32 get_vgrp_id_uleis_hskp() {return(vgrp_id_uleis_hskp);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_uleis_hskp(char *wr_strval)
{
  strcpy(wr_strval, "The file 'uleis_hskp.h' is shown below, it was used to create the data in the Vgroup named 'VG_UHskpSet'.\n\n");
  strcat(wr_strval,"/* Id: uleis_hskp.h,v 1.8 1997/11/14 23:57:55 steves Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define NUMFRM 128		/* number of minor frames in a cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct UHskpSet\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;		/* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;	/* time for beginning of data collection */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 QAC;			/* number of missing frames in this cycle */\n");
  strcat(wr_strval,"  uint8 chk_sum_chk;	      /* 0 means chk_sum test passed; 1 means failed */\n");
  strcat(wr_strval,"                              /*   also in uleis_statblk_trl.h               */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   /* position flag (1 = yes, 0 = no) of dump data in each mnr frm */\n");
  strcat(wr_strval,"   /* puts the total for this minor frame in last array element */\n");
  strcat(wr_strval,"  uint8 dump_flg[129];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   /* position flag (1 = yes, 0 = no) of Status TLM data in each mnr frm */\n");
  strcat(wr_strval,"   /* puts the total for this minor frame in last array element */\n");
  strcat(wr_strval,"  uint8 stat_tlm_flg[129];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 DeckTemp[8];		/* mf 0  - Instrument Deck Temp: near ULEIS */\n");
  strcat(wr_strval,"  uint8 lvps_voltage[8];	/* mf 9  - lvps voltage */\n");
  strcat(wr_strval,"  uint8 total_cur[8];		/* mf 10 - total current */\n");
  strcat(wr_strval,"  uint8 lvps_cur_analg[8];	/* mf 10 - analog elect. lvps current */\n");
  strcat(wr_strval,"  uint8 heater_cur[8];		/* mf 10 - Internal & I/F Heater Current */\n");
  strcat(wr_strval,"  uint8 telescp_temp[8];	/* mf 12 - telescope temperature */\n");
  strcat(wr_strval,"  uint8 analg_elect_temp[8];	/* mf 12 - analog electr. temp. (internal) */\n");
  strcat(wr_strval,"  uint8 dpu_temp[8];		/* mf 12 - dpu temperature (internal) */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 UPowBits[8];		/* power switching and ordinance array */\n");
  strcat(wr_strval,"/*- ULEIS power switching and ordinance (start bit count at 1, not 0) -*/\n");
  strcat(wr_strval,"/*  element postn 7: Internal Heaters         bit pos 20 of 112 (ON/OFF) */\n");
  strcat(wr_strval,"/*  element postn 6: Interface Heater         bit pos 21 of 112 (ON/OFF) */\n");
  strcat(wr_strval,"/*  element postn 5: Main System Power        bit pos 24 of 112 (ON/OFF) */\n");
  strcat(wr_strval,"/*  element postn 4: Pyro A Arm (ICI-1SE192F) bit pos 60 of 112 (ON/OFF) */\n");
  strcat(wr_strval,"/*  element postn 3: Pyro B Arm (ICI-1SE192F) bit pos 63 of 112 (ON/OFF) */\n");
  strcat(wr_strval,"/*  element postn 2: 0                                                   */\n");
  strcat(wr_strval,"/*  element postn 1: 0                                                   */\n");
  strcat(wr_strval,"/*  element postn 0: 0                                                   */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* sunpulse data */\n");
  strcat(wr_strval,"  uint8  PhaseAng[NUMFRM];   /* Phase angle for each frame in this cycle*/\n");
  strcat(wr_strval,"  uint8  SunSenID[NUMFRM];   /* bits 7-2=0, bit1=sunsentop,bit0=sunsenside*/\n");
  strcat(wr_strval,"  uint16 SunPulLat[2][8];     /* sun pulse latched at mn frm 0&8 [2] */\n");
  strcat(wr_strval,"			     /* over the 8 [8] major frame cycle */\n");
  strcat(wr_strval,"			     /* SC spin clock value at the time of the sun */\n");
  strcat(wr_strval,"			     /* pulse */\n");
  strcat(wr_strval,"  uint32 SunPulDat[2][8];    /* Time of sun pulse */\n");
  strcat(wr_strval,"		/* bits 31-24 : unused */\n");
  strcat(wr_strval,"		/* bits 23-20 : Mnr frame */\n");
  strcat(wr_strval,"		/* bits 19-10 : sub secont count (684.75 cnts=1 sec)*/\n");
  strcat(wr_strval,"		/* bits  9- 8 : ID bits, 00=err,01=top,10=side,11=neither */\n");
  strcat(wr_strval,"		/* bits  7- 0 : Y angle measurment (Grey code) */\n");
  strcat(wr_strval,"		/* */\n");
  strcat(wr_strval,"		/*   From C&DH Specification (mf0:index1=0, mf8:index1=1) */\n");
  strcat(wr_strval,"		/* For the time tag in Science minor frame 0: for a minor */\n");
  strcat(wr_strval,"		/* frame ID of 0, the sun pulse would have occured in the */\n");
  strcat(wr_strval,"		/* current major frame.  For a minor frame ID of 1 to 15, */\n");
  strcat(wr_strval,"		/* the sun pulse would have occured in the previous major */\n");
  strcat(wr_strval,"		/* frame */\n");
  strcat(wr_strval,"		/* For the time tag in Science minor frame 8: for a minor */\n");
  strcat(wr_strval,"		/* frame ID of 0-8, the sun pulse would have occured in the */\n");
  strcat(wr_strval,"		/* current major frame.  For a minor frame ID of 9 to 15, */\n");
  strcat(wr_strval,"		/* the sun pulse would have occured in the previous major */\n");
  strcat(wr_strval,"		/* frame */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
