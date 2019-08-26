/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_dspare_alarmcnt.h,v 1.3 1998/01/30 19:50:07 hemple Exp  */

#include "s3_dspare_alarmcnt.h"
#include "df.h"

int32 vgrp_id_s3_dspare_alarmcnt;
static int32 vdata_id_s3_dspare_alarmcnt;

  /* 2531 is the size of s3_dspare_alarmcnt.h + 1 added line */
char Vgrp_descrp_s3s_dspare_alarmcnt[2531];

/****----  init create function  ----****/

int32 init_cr_s3_dspare_alarmcnt(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_dspare_alarmcnt();

  void print_s3_dspare_alarmcnt_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_dspare_alarmcnt = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_dspare_alarmcnt, "VG_s3s_dspare_alarmcnt"); 
  Vsetclass(vgrp_id_s3_dspare_alarmcnt, "VG_S3_DSPARE_ALARMCNT");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_s3s_dspare_alarmcnt" )) ==FAIL) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_dspare_alarmcnt(Vgrp_descrp_s3s_dspare_alarmcnt);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_s3s_dspare_alarmcnt, sizeof(Vgrp_descrp_s3s_dspare_alarmcnt))) ==FAIL) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_dspare_alarmcnt = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_dspare_alarmcnt, "s3s_dspare_alarmcnt");
  VSsetclass(vdata_id_s3_dspare_alarmcnt, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_dspare_alarmcnt, vdata_id_s3_dspare_alarmcnt)) ==FAIL) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "sctime", DFNT_UINT32, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmDelay_set_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmDelay_set_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmDis_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmDis_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmPres_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmPres_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmLV_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmLV_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmV1Open_set_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmV1Open_set_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmV2Open_set_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmV2Open_set_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmV3Open_set_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmV3Open_set_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmPC1P_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmPC1P_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmPC1P_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmPC1P_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmPC2P_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmPC2P_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmPC2P_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmPC2P_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmPC3P_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmPC3P_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmPC3P_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmPC3P_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmP5V_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmP5V_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmP5V_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmP5V_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmP5I_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmP5I_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmP5I_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmP5I_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmM5V_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmM5V_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmM5V_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmM5V_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmM5I_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmM5I_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmM5I_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmM5I_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmP15V_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmP15V_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmP15V_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmP15V_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmP15I_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmP15I_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmP15I_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmP15I_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmM15V_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmM15V_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmM15V_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmM15V_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmM15I_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmM15I_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmM15I_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmM15I_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm75V_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm75V_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm75V_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm75V_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm75I_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm75I_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm75I_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm75I_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kV_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kV_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kV_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kV_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kI_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kI_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kI_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kI_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kAV_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kAV_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kAV_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kAV_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kBV_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kBV_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kBV_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kBV_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kCV_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kCV_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm2kCV_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm2kCV_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm30kV_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm30kV_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm30kV_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm30kV_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm30kI_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm30kI_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "Alarm30kI_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define Alarm30kI_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmDisV_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmDisV_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmDisV_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmDisV_max_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmDisI_min_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmDisI_min_Cnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarmcnt, "AlarmDisI_max_Cnt", DFNT_UINT8, (1) )) {
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSfdefine: Couldn't define AlarmDisI_max_Cnt");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_dspare_alarmcnt,"sctime, AlarmDelay_set_Cnt, AlarmDis_Cnt, AlarmPres_Cnt, AlarmLV_Cnt, AlarmV1Open_set_Cnt, AlarmV2Open_set_Cnt, AlarmV3Open_set_Cnt, AlarmPC1P_min_Cnt, AlarmPC1P_max_Cnt, AlarmPC2P_min_Cnt, AlarmPC2P_max_Cnt, AlarmPC3P_min_Cnt, AlarmPC3P_max_Cnt, AlarmP5V_min_Cnt, AlarmP5V_max_Cnt, AlarmP5I_min_Cnt, AlarmP5I_max_Cnt, AlarmM5V_min_Cnt, AlarmM5V_max_Cnt, AlarmM5I_min_Cnt, AlarmM5I_max_Cnt, AlarmP15V_min_Cnt, AlarmP15V_max_Cnt, AlarmP15I_min_Cnt, AlarmP15I_max_Cnt, AlarmM15V_min_Cnt, AlarmM15V_max_Cnt, AlarmM15I_min_Cnt, AlarmM15I_max_Cnt, Alarm75V_min_Cnt, Alarm75V_max_Cnt, Alarm75I_min_Cnt, Alarm75I_max_Cnt, Alarm2kV_min_Cnt, Alarm2kV_max_Cnt, Alarm2kI_min_Cnt, Alarm2kI_max_Cnt, Alarm2kAV_min_Cnt, Alarm2kAV_max_Cnt, Alarm2kBV_min_Cnt, Alarm2kBV_max_Cnt, Alarm2kCV_min_Cnt, Alarm2kCV_max_Cnt, Alarm30kV_min_Cnt, Alarm30kV_max_Cnt, Alarm30kI_min_Cnt, Alarm30kI_max_Cnt, AlarmDisV_min_Cnt, AlarmDisV_max_Cnt, AlarmDisI_min_Cnt, AlarmDisI_max_Cnt")){
    print_s3_dspare_alarmcnt_error("init_cr_s3_dspare_alarmcnt -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_dspare_alarmcnt(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_dspare_alarmcnt(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_dspare_alarmcnt(struct s3s_dspare_alarmcnt s3s_dspare_alarmcnt_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_dspare_alarmcnt_error();
void pack_s3_dspare_alarmcnt();

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_alarmcnt));
  pack_s3_dspare_alarmcnt(odata, &s3s_dspare_alarmcnt_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_dspare_alarmcnt, recnum)==-1) {
		print_s3_dspare_alarmcnt_error("write_s3_dspare_alarmcnt -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_dspare_alarmcnt, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_dspare_alarmcnt_error("write_s3_dspare_alarmcnt -> VSwrite: Couldn't write data.");

  memset(&s3s_dspare_alarmcnt_struc, 0, sizeof(struct s3s_dspare_alarmcnt));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_dspare_alarmcnt()
{
  VSdetach(vdata_id_s3_dspare_alarmcnt);
  Vdetach(vgrp_id_s3_dspare_alarmcnt);
}

/*----     init access function    ----*/

int32 init_acc_s3_dspare_alarmcnt(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_dspare_alarmcnt_error();


  if ((vdata_ref = VSfind(hdf_fp, "s3s_dspare_alarmcnt")) <= 0 ) {
    print_s3_dspare_alarmcnt_error("init_acc_s3_dspare_alarmcnt -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_dspare_alarmcnt = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_dspare_alarmcnt_error("init_acc_s3_dspare_alarmcnt -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_dspare_alarmcnt, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_dspare_alarmcnt,"sctime, AlarmDelay_set_Cnt, AlarmDis_Cnt, AlarmPres_Cnt, AlarmLV_Cnt, AlarmV1Open_set_Cnt, AlarmV2Open_set_Cnt, AlarmV3Open_set_Cnt, AlarmPC1P_min_Cnt, AlarmPC1P_max_Cnt, AlarmPC2P_min_Cnt, AlarmPC2P_max_Cnt, AlarmPC3P_min_Cnt, AlarmPC3P_max_Cnt, AlarmP5V_min_Cnt, AlarmP5V_max_Cnt, AlarmP5I_min_Cnt, AlarmP5I_max_Cnt, AlarmM5V_min_Cnt, AlarmM5V_max_Cnt, AlarmM5I_min_Cnt, AlarmM5I_max_Cnt, AlarmP15V_min_Cnt, AlarmP15V_max_Cnt, AlarmP15I_min_Cnt, AlarmP15I_max_Cnt, AlarmM15V_min_Cnt, AlarmM15V_max_Cnt, AlarmM15I_min_Cnt, AlarmM15I_max_Cnt, Alarm75V_min_Cnt, Alarm75V_max_Cnt, Alarm75I_min_Cnt, Alarm75I_max_Cnt, Alarm2kV_min_Cnt, Alarm2kV_max_Cnt, Alarm2kI_min_Cnt, Alarm2kI_max_Cnt, Alarm2kAV_min_Cnt, Alarm2kAV_max_Cnt, Alarm2kBV_min_Cnt, Alarm2kBV_max_Cnt, Alarm2kCV_min_Cnt, Alarm2kCV_max_Cnt, Alarm30kV_min_Cnt, Alarm30kV_max_Cnt, Alarm30kI_min_Cnt, Alarm30kI_max_Cnt, AlarmDisV_min_Cnt, AlarmDisV_max_Cnt, AlarmDisI_min_Cnt, AlarmDisI_max_Cnt")) {
      print_s3_dspare_alarmcnt_error("init_acc_s3_dspare_alarmcnt -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_dspare_alarmcnt(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_dspare_alarmcnt(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_dspare_alarmcnt(struct s3s_dspare_alarmcnt *s3s_dspare_alarmcnt_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_dspare_alarmcnt_error();
void unpack_s3_dspare_alarmcnt();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_alarmcnt));
  VSinquire(vdata_id_s3_dspare_alarmcnt, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_dspare_alarmcnt, recnum_rd)==FAIL) {
          print_s3_dspare_alarmcnt_error("read_s3_dspare_alarmcnt -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_dspare_alarmcnt, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_dspare_alarmcnt_error("read_s3_dspare_alarmcnt -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_dspare_alarmcnt(odata, s3s_dspare_alarmcnt_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_dspare_alarmcnt()
{
  VSdetach(vdata_id_s3_dspare_alarmcnt);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_dspare_alarmcnt(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_dspare_alarmcnt_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_s3s_dspare_alarmcnt" )) ==FAIL)
    print_s3_dspare_alarmcnt_error("rd_Vgrp_s3_dspare_alarmcnt -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_dspare_alarmcnt_error("rd_Vgrp_s3_dspare_alarmcnt -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_dspare_alarmcnt_error("rd_Vgrp_s3_dspare_alarmcnt -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_dspare_alarmcnt_error("rd_Vgrp_s3_dspare_alarmcnt -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_s3s_dspare_alarmcnt, HDstrlen(Vgrp_descrp_s3s_dspare_alarmcnt)) ==FAIL)
    print_s3_dspare_alarmcnt_error("rd_Vgrp_s3_dspare_alarmcnt -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_s3s_dspare_alarmcnt);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_dspare_alarmcnt_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3dspare_alarmcnt.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_dspare_alarmcnt(uint8 *data, struct s3s_dspare_alarmcnt *s3s_dspare_alarmcnt_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmDelay_set_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmDis_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmPres_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmLV_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmV1Open_set_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmV2Open_set_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmV3Open_set_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmPC1P_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmPC1P_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmPC2P_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmPC2P_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmPC3P_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmPC3P_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmP5V_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmP5V_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmP5I_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmP5I_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmM5V_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmM5V_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmM5I_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmM5I_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmP15V_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmP15V_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmP15I_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmP15I_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmM15V_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmM15V_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmM15I_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmM15I_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm75V_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm75V_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm75I_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm75I_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kV_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kV_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kI_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kI_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kAV_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kAV_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kBV_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kBV_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kCV_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm2kCV_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm30kV_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm30kV_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm30kI_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->Alarm30kI_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmDisV_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmDisV_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmDisI_min_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3s_dspare_alarmcnt_ptr->AlarmDisI_max_Cnt, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_dspare_alarmcnt(uint8 *data, struct s3s_dspare_alarmcnt *s3s_dspare_alarmcnt_ptr)
{
int32 ptr=0;

   memcpy(&s3s_dspare_alarmcnt_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmDelay_set_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmDis_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmPres_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmLV_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmV1Open_set_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmV2Open_set_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmV3Open_set_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmPC1P_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmPC1P_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmPC2P_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmPC2P_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmPC3P_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmPC3P_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmP5V_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmP5V_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmP5I_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmP5I_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmM5V_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmM5V_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmM5I_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmM5I_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmP15V_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmP15V_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmP15I_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmP15I_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmM15V_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmM15V_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmM15I_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmM15I_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm75V_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm75V_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm75I_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm75I_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kV_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kV_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kI_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kI_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kAV_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kAV_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kBV_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kBV_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kCV_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm2kCV_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm30kV_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm30kV_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm30kI_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->Alarm30kI_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmDisV_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmDisV_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmDisI_min_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3s_dspare_alarmcnt_ptr->AlarmDisI_max_Cnt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3_dspare_alarmcnt() {return(vgrp_id_s3_dspare_alarmcnt);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_dspare_alarmcnt(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_dspare_alarmcnt.h' is shown below, it was used to create the data in the Vgroup named 'VG_s3s_dspare_alarmcnt'.\n\n");
  strcat(wr_strval,"/* Id: s3_dspare_alarmcnt.h,v 1.3 1998/01/30 19:50:07 hemple Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct s3s_dspare_alarmcnt {\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"uint32 sctime; /* 32bit spacecraft time */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* SEPICA counters for alarm violations, from EDB 7 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"uint8 AlarmDelay_set_Cnt;	/* delay 10 min. */\n");
  strcat(wr_strval,"uint8 AlarmDis_Cnt;		/* 30kV discharge check */\n");
  strcat(wr_strval,"uint8 AlarmPres_Cnt;		/* pressure check */\n");
  strcat(wr_strval,"uint8 AlarmLV_Cnt;		/* LV status bit check */\n");
  strcat(wr_strval,"uint8 AlarmV1Open_set_Cnt;	/* valve 1 open */\n");
  strcat(wr_strval,"uint8 AlarmV2Open_set_Cnt;	/* valve 2 open */\n");
  strcat(wr_strval,"uint8 AlarmV3Open_set_Cnt;	/* valve 3 open */\n");
  strcat(wr_strval,"uint8 AlarmPC1P_min_Cnt;	/* PC1 pressure */\n");
  strcat(wr_strval,"uint8 AlarmPC1P_max_Cnt;	/* PC1 pressure */\n");
  strcat(wr_strval,"uint8 AlarmPC2P_min_Cnt;	/* PC2 pressure */\n");
  strcat(wr_strval,"uint8 AlarmPC2P_max_Cnt;	/* PC2 pressure */\n");
  strcat(wr_strval,"uint8 AlarmPC3P_min_Cnt;	/* PC3 pressure */\n");
  strcat(wr_strval,"uint8 AlarmPC3P_max_Cnt;	/* PC3 pressure */\n");
  strcat(wr_strval,"uint8 AlarmP5V_min_Cnt;	        /* +5V */\n");
  strcat(wr_strval,"uint8 AlarmP5V_max_Cnt;   	/* +5V */\n");
  strcat(wr_strval,"uint8 AlarmP5I_min_Cnt;	        /* +5V (I) */\n");
  strcat(wr_strval,"uint8 AlarmP5I_max_Cnt;	        /* +5V (I) */\n");
  strcat(wr_strval,"uint8 AlarmM5V_min_Cnt;	        /* -5V */\n");
  strcat(wr_strval,"uint8 AlarmM5V_max_Cnt;	        /* -5V */\n");
  strcat(wr_strval,"uint8 AlarmM5I_min_Cnt;    	/* -5V (I) */\n");
  strcat(wr_strval,"uint8 AlarmM5I_max_Cnt;	        /* -5V (I) */\n");
  strcat(wr_strval,"uint8 AlarmP15V_min_Cnt;	/* +15V */\n");
  strcat(wr_strval,"uint8 AlarmP15V_max_Cnt;	/* +15V */\n");
  strcat(wr_strval,"uint8 AlarmP15I_min_Cnt;	/* +15V (I) */\n");
  strcat(wr_strval,"uint8 AlarmP15I_max_Cnt;	/* +15V (I) */\n");
  strcat(wr_strval,"uint8 AlarmM15V_min_Cnt;	/* -15V */\n");
  strcat(wr_strval,"uint8 AlarmM15V_max_Cnt;	/* -15V */\n");
  strcat(wr_strval,"uint8 AlarmM15I_min_Cnt;	/* -15V (I) */\n");
  strcat(wr_strval,"uint8 AlarmM15I_max_Cnt;	/* -15V (I) */\n");
  strcat(wr_strval,"uint8 Alarm75V_min_Cnt;		/* 75V */\n");
  strcat(wr_strval,"uint8 Alarm75V_max_Cnt;		/* 75V */\n");
  strcat(wr_strval,"uint8 Alarm75I_min_Cnt;		/* 75V (I) */\n");
  strcat(wr_strval,"uint8 Alarm75I_max_Cnt;		/* 75V (I) */\n");
  strcat(wr_strval,"uint8 Alarm2kV_min_Cnt;		/* 2kV */\n");
  strcat(wr_strval,"uint8 Alarm2kV_max_Cnt;		/* 2kV */\n");
  strcat(wr_strval,"uint8 Alarm2kI_min_Cnt;		/* 2kV (I) */\n");
  strcat(wr_strval,"uint8 Alarm2kI_max_Cnt;		/* 2kV (I) */\n");
  strcat(wr_strval,"uint8 Alarm2kAV_min_Cnt;	/* 2kV A */\n");
  strcat(wr_strval,"uint8 Alarm2kAV_max_Cnt;	/* 2kV A */\n");
  strcat(wr_strval,"uint8 Alarm2kBV_min_Cnt;	/* 2kV B */\n");
  strcat(wr_strval,"uint8 Alarm2kBV_max_Cnt;	/* 2kV B */\n");
  strcat(wr_strval,"uint8 Alarm2kCV_min_Cnt;	/* 2kV C */\n");
  strcat(wr_strval,"uint8 Alarm2kCV_max_Cnt;	/* 2kV C */\n");
  strcat(wr_strval,"uint8 Alarm30kV_min_Cnt;	/* 30kV */\n");
  strcat(wr_strval,"uint8 Alarm30kV_max_Cnt;	/* 30kV */\n");
  strcat(wr_strval,"uint8 Alarm30kI_min_Cnt;	/* 30kV (I) */\n");
  strcat(wr_strval,"uint8 Alarm30kI_max_Cnt;	/* 30kV (I) */\n");
  strcat(wr_strval,"uint8 AlarmDisV_min_Cnt;	/* 30kV discharge */\n");
  strcat(wr_strval,"uint8 AlarmDisV_max_Cnt;	/* 30kV discharge */\n");
  strcat(wr_strval,"uint8 AlarmDisI_min_Cnt;	/* 30kV discharge (I) */\n");
  strcat(wr_strval,"uint8 AlarmDisI_max_Cnt;	/* 30kV discharge (I) */\n");
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
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  return(0);
}
