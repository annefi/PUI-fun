/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_dspare_alarm.h,v 1.3 1998/01/30 19:49:30 hemple Exp  */

#include "s3_dspare_alarm.h"
#include "df.h"

int32 vgrp_id_s3_dspare_alarm;
static int32 vdata_id_s3_dspare_alarm;

  /* 2301 is the size of s3_dspare_alarm.h + 1 added line */
char Vgrp_descrp_s3s_dspare_alarm[2301];

/****----  init create function  ----****/

int32 init_cr_s3_dspare_alarm(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_dspare_alarm();

  void print_s3_dspare_alarm_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_dspare_alarm = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_dspare_alarm, "VG_s3s_dspare_alarm"); 
  Vsetclass(vgrp_id_s3_dspare_alarm, "VG_S3_DSPARE_ALARM");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_s3s_dspare_alarm" )) ==FAIL) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_dspare_alarm(Vgrp_descrp_s3s_dspare_alarm);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_s3s_dspare_alarm, sizeof(Vgrp_descrp_s3s_dspare_alarm))) ==FAIL) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_dspare_alarm = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_dspare_alarm, "s3s_dspare_alarm");
  VSsetclass(vdata_id_s3_dspare_alarm, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_dspare_alarm, vdata_id_s3_dspare_alarm)) ==FAIL) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_dspare_alarm, "sctime", DFNT_UINT32, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmDelay_set", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmDelay_set");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmDis", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmDis");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmPres", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmPres");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmLV", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmLV");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmV1Open_set", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmV1Open_set");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmV2Open_set", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmV2Open_set");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmV3Open_set", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmV3Open_set");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmPC1P_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmPC1P_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmPC1P_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmPC1P_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmPC2P_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmPC2P_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmPC2P_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmPC2P_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmPC3P_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmPC3P_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmPC3P_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmPC3P_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmP5V_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmP5V_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmP5V_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmP5V_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmP5I_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmP5I_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmP5I_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmP5I_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmM5V_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmM5V_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmM5V_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmM5V_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmM5I_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmM5I_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmM5I_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmM5I_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmP15V_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmP15V_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmP15V_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmP15V_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmP15I_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmP15I_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmP15I_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmP15I_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmM15V_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmM15V_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmM15V_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmM15V_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmM15I_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmM15I_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmM15I_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmM15I_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm75V_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm75V_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm75V_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm75V_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm75I_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm75I_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm75I_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm75I_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kV_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kV_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kV_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kV_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kI_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kI_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kI_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kI_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kAV_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kAV_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kAV_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kAV_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kBV_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kBV_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kBV_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kBV_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kCV_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kCV_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm2kCV_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm2kCV_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm30kV_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm30kV_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm30kV_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm30kV_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm30kI_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm30kI_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "Alarm30kI_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define Alarm30kI_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmDisV_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmDisV_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmDisV_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmDisV_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmDisI_min", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmDisI_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_alarm, "AlarmDisI_max", DFNT_UINT16, (1) )) {
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSfdefine: Couldn't define AlarmDisI_max");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_dspare_alarm,"sctime, AlarmDelay_set, AlarmDis, AlarmPres, AlarmLV, AlarmV1Open_set, AlarmV2Open_set, AlarmV3Open_set, AlarmPC1P_min, AlarmPC1P_max, AlarmPC2P_min, AlarmPC2P_max, AlarmPC3P_min, AlarmPC3P_max, AlarmP5V_min, AlarmP5V_max, AlarmP5I_min, AlarmP5I_max, AlarmM5V_min, AlarmM5V_max, AlarmM5I_min, AlarmM5I_max, AlarmP15V_min, AlarmP15V_max, AlarmP15I_min, AlarmP15I_max, AlarmM15V_min, AlarmM15V_max, AlarmM15I_min, AlarmM15I_max, Alarm75V_min, Alarm75V_max, Alarm75I_min, Alarm75I_max, Alarm2kV_min, Alarm2kV_max, Alarm2kI_min, Alarm2kI_max, Alarm2kAV_min, Alarm2kAV_max, Alarm2kBV_min, Alarm2kBV_max, Alarm2kCV_min, Alarm2kCV_max, Alarm30kV_min, Alarm30kV_max, Alarm30kI_min, Alarm30kI_max, AlarmDisV_min, AlarmDisV_max, AlarmDisI_min, AlarmDisI_max")){
    print_s3_dspare_alarm_error("init_cr_s3_dspare_alarm -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_dspare_alarm(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_dspare_alarm(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_dspare_alarm(struct s3s_dspare_alarm s3s_dspare_alarm_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_dspare_alarm_error();
void pack_s3_dspare_alarm();

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_alarm));
  pack_s3_dspare_alarm(odata, &s3s_dspare_alarm_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_dspare_alarm, recnum)==-1) {
		print_s3_dspare_alarm_error("write_s3_dspare_alarm -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_dspare_alarm, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_dspare_alarm_error("write_s3_dspare_alarm -> VSwrite: Couldn't write data.");

  memset(&s3s_dspare_alarm_struc, 0, sizeof(struct s3s_dspare_alarm));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_dspare_alarm()
{
  VSdetach(vdata_id_s3_dspare_alarm);
  Vdetach(vgrp_id_s3_dspare_alarm);
}

/*----     init access function    ----*/

int32 init_acc_s3_dspare_alarm(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_dspare_alarm_error();


  if ((vdata_ref = VSfind(hdf_fp, "s3s_dspare_alarm")) <= 0 ) {
    print_s3_dspare_alarm_error("init_acc_s3_dspare_alarm -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_dspare_alarm = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_dspare_alarm_error("init_acc_s3_dspare_alarm -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_dspare_alarm, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_dspare_alarm,"sctime, AlarmDelay_set, AlarmDis, AlarmPres, AlarmLV, AlarmV1Open_set, AlarmV2Open_set, AlarmV3Open_set, AlarmPC1P_min, AlarmPC1P_max, AlarmPC2P_min, AlarmPC2P_max, AlarmPC3P_min, AlarmPC3P_max, AlarmP5V_min, AlarmP5V_max, AlarmP5I_min, AlarmP5I_max, AlarmM5V_min, AlarmM5V_max, AlarmM5I_min, AlarmM5I_max, AlarmP15V_min, AlarmP15V_max, AlarmP15I_min, AlarmP15I_max, AlarmM15V_min, AlarmM15V_max, AlarmM15I_min, AlarmM15I_max, Alarm75V_min, Alarm75V_max, Alarm75I_min, Alarm75I_max, Alarm2kV_min, Alarm2kV_max, Alarm2kI_min, Alarm2kI_max, Alarm2kAV_min, Alarm2kAV_max, Alarm2kBV_min, Alarm2kBV_max, Alarm2kCV_min, Alarm2kCV_max, Alarm30kV_min, Alarm30kV_max, Alarm30kI_min, Alarm30kI_max, AlarmDisV_min, AlarmDisV_max, AlarmDisI_min, AlarmDisI_max")) {
      print_s3_dspare_alarm_error("init_acc_s3_dspare_alarm -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_dspare_alarm(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_dspare_alarm(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_dspare_alarm(struct s3s_dspare_alarm *s3s_dspare_alarm_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_dspare_alarm_error();
void unpack_s3_dspare_alarm();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_alarm));
  VSinquire(vdata_id_s3_dspare_alarm, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_dspare_alarm, recnum_rd)==FAIL) {
          print_s3_dspare_alarm_error("read_s3_dspare_alarm -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_dspare_alarm, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_dspare_alarm_error("read_s3_dspare_alarm -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_dspare_alarm(odata, s3s_dspare_alarm_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_dspare_alarm()
{
  VSdetach(vdata_id_s3_dspare_alarm);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_dspare_alarm(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_dspare_alarm_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_s3s_dspare_alarm" )) ==FAIL)
    print_s3_dspare_alarm_error("rd_Vgrp_s3_dspare_alarm -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_dspare_alarm_error("rd_Vgrp_s3_dspare_alarm -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_dspare_alarm_error("rd_Vgrp_s3_dspare_alarm -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_dspare_alarm_error("rd_Vgrp_s3_dspare_alarm -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_s3s_dspare_alarm, HDstrlen(Vgrp_descrp_s3s_dspare_alarm)) ==FAIL)
    print_s3_dspare_alarm_error("rd_Vgrp_s3_dspare_alarm -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_s3s_dspare_alarm);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_dspare_alarm_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3dspare_alarm.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_dspare_alarm(uint8 *data, struct s3s_dspare_alarm *s3s_dspare_alarm_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &s3s_dspare_alarm_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmDelay_set, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmDis, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmPres, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmLV, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmV1Open_set, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmV2Open_set, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmV3Open_set, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmPC1P_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmPC1P_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmPC2P_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmPC2P_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmPC3P_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmPC3P_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmP5V_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmP5V_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmP5I_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmP5I_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmM5V_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmM5V_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmM5I_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmM5I_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmP15V_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmP15V_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmP15I_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmP15I_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmM15V_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmM15V_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmM15I_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmM15I_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm75V_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm75V_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm75I_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm75I_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kV_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kV_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kI_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kI_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kAV_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kAV_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kBV_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kBV_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kCV_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm2kCV_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm30kV_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm30kV_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm30kI_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->Alarm30kI_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmDisV_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmDisV_max, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmDisI_min, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_alarm_ptr->AlarmDisI_max, ((2)*(1)) );
   ptr+= ((2)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_dspare_alarm(uint8 *data, struct s3s_dspare_alarm *s3s_dspare_alarm_ptr)
{
int32 ptr=0;

   memcpy(&s3s_dspare_alarm_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmDelay_set, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmDis, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmPres, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmLV, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmV1Open_set, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmV2Open_set, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmV3Open_set, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmPC1P_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmPC1P_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmPC2P_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmPC2P_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmPC3P_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmPC3P_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmP5V_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmP5V_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmP5I_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmP5I_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmM5V_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmM5V_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmM5I_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmM5I_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmP15V_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmP15V_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmP15I_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmP15I_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmM15V_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmM15V_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmM15I_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmM15I_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm75V_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm75V_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm75I_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm75I_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kV_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kV_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kI_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kI_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kAV_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kAV_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kBV_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kBV_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kCV_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm2kCV_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm30kV_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm30kV_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm30kI_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->Alarm30kI_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmDisV_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmDisV_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmDisI_min, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_alarm_ptr->AlarmDisI_max, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
}
int32 get_vgrp_id_s3_dspare_alarm() {return(vgrp_id_s3_dspare_alarm);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_dspare_alarm(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_dspare_alarm.h' is shown below, it was used to create the data in the Vgroup named 'VG_s3s_dspare_alarm'.\n\n");
  strcat(wr_strval,"/* Id: s3_dspare_alarm.h,v 1.3 1998/01/30 19:49:30 hemple Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct s3s_dspare_alarm {\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"uint32 sctime; /* 32bit spacecraft time */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* SEPICA limits for alarm monitoring, from EDB 6 */\n");
  strcat(wr_strval,"uint16 AlarmDelay_set;	/* delay 10 min. */\n");
  strcat(wr_strval,"uint16 AlarmDis;	/* 30kV discharge check */\n");
  strcat(wr_strval,"uint16 AlarmPres;	/* pressure check */\n");
  strcat(wr_strval,"uint16 AlarmLV;		/* LV status bit check */\n");
  strcat(wr_strval,"uint16 AlarmV1Open_set;	/* valve 1 open */\n");
  strcat(wr_strval,"uint16 AlarmV2Open_set;	/* valve 2 open */\n");
  strcat(wr_strval,"uint16 AlarmV3Open_set;	/* valve 3 open */\n");
  strcat(wr_strval,"uint16 AlarmPC1P_min;	/* PC1 pressure */\n");
  strcat(wr_strval,"uint16 AlarmPC1P_max;	/* PC1 pressure */\n");
  strcat(wr_strval,"uint16 AlarmPC2P_min;	/* PC2 pressure */\n");
  strcat(wr_strval,"uint16 AlarmPC2P_max;	/* PC2 pressure */\n");
  strcat(wr_strval,"uint16 AlarmPC3P_min;	/* PC3 pressure */\n");
  strcat(wr_strval,"uint16 AlarmPC3P_max;	/* PC3 pressure */\n");
  strcat(wr_strval,"uint16 AlarmP5V_min;	/* +5V */\n");
  strcat(wr_strval,"uint16 AlarmP5V_max;	/* +5V */\n");
  strcat(wr_strval,"uint16 AlarmP5I_min;	/* +5V (I) */\n");
  strcat(wr_strval,"uint16 AlarmP5I_max;	/* +5V (I) */\n");
  strcat(wr_strval,"uint16 AlarmM5V_min;	/* -5V */\n");
  strcat(wr_strval,"uint16 AlarmM5V_max;	/* -5V */\n");
  strcat(wr_strval,"uint16 AlarmM5I_min;	/* -5V (I) */\n");
  strcat(wr_strval,"uint16 AlarmM5I_max;	/* -5V (I) */\n");
  strcat(wr_strval,"uint16 AlarmP15V_min;	/* +15V */\n");
  strcat(wr_strval,"uint16 AlarmP15V_max;	/* +15V */\n");
  strcat(wr_strval,"uint16 AlarmP15I_min;	/* +15V (I) */\n");
  strcat(wr_strval,"uint16 AlarmP15I_max;	/* +15V (I) */\n");
  strcat(wr_strval,"uint16 AlarmM15V_min;	/* -15V */\n");
  strcat(wr_strval,"uint16 AlarmM15V_max;	/* -15V */\n");
  strcat(wr_strval,"uint16 AlarmM15I_min;	/* -15V (I) */\n");
  strcat(wr_strval,"uint16 AlarmM15I_max;	/* -15V (I) */\n");
  strcat(wr_strval,"uint16 Alarm75V_min;	/* 75V */\n");
  strcat(wr_strval,"uint16 Alarm75V_max;	/* 75V */\n");
  strcat(wr_strval,"uint16 Alarm75I_min;	/* 75V (I) */\n");
  strcat(wr_strval,"uint16 Alarm75I_max;	/* 75V (I) */\n");
  strcat(wr_strval,"uint16 Alarm2kV_min;	/* 2kV */\n");
  strcat(wr_strval,"uint16 Alarm2kV_max;	/* 2kV */\n");
  strcat(wr_strval,"uint16 Alarm2kI_min;	/* 2kV (I) */\n");
  strcat(wr_strval,"uint16 Alarm2kI_max;	/* 2kV (I) */\n");
  strcat(wr_strval,"uint16 Alarm2kAV_min;	/* 2kV A */\n");
  strcat(wr_strval,"uint16 Alarm2kAV_max;	/* 2kV A */\n");
  strcat(wr_strval,"uint16 Alarm2kBV_min;	/* 2kV B */\n");
  strcat(wr_strval,"uint16 Alarm2kBV_max;	/* 2kV B */\n");
  strcat(wr_strval,"uint16 Alarm2kCV_min;	/* 2kV C */\n");
  strcat(wr_strval,"uint16 Alarm2kCV_max;	/* 2kV C */\n");
  strcat(wr_strval,"uint16 Alarm30kV_min;	/* 30kV */\n");
  strcat(wr_strval,"uint16 Alarm30kV_max;	/* 30kV */\n");
  strcat(wr_strval,"uint16 Alarm30kI_min;	/* 30kV (I) */\n");
  strcat(wr_strval,"uint16 Alarm30kI_max;	/* 30kV (I) */\n");
  strcat(wr_strval,"uint16 AlarmDisV_min;	/* 30kV discharge */\n");
  strcat(wr_strval,"uint16 AlarmDisV_max;	/* 30kV discharge */\n");
  strcat(wr_strval,"uint16 AlarmDisI_min;	/* 30kV discharge (I) */\n");
  strcat(wr_strval,"uint16 AlarmDisI_max;	/* 30kV discharge (I) */\n");
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
