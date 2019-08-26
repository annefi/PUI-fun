/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisHskp.h,v 1.2 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisHskp.h"
#include "df.h"

int32 vgrp_id_L1SisHskp;
static int32 vdata_id_L1SisHskp;

  /* 4564 is the size of L1SisHskp.h + 1 added line */
char Vgrp_descrp_L1SisHskp[4564];

/****----  init create function  ----****/

int32 init_cr_L1SisHskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1SisHskp();

  void print_L1SisHskp_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisHskp = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisHskp, "VG_L1SisHskp"); 
  Vsetclass(vgrp_id_L1SisHskp, "VG_L1SISHSKP");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisHskp" )) ==FAIL) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisHskp(Vgrp_descrp_L1SisHskp);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisHskp, sizeof(Vgrp_descrp_L1SisHskp))) ==FAIL) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisHskp = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisHskp, "L1SisHskp");
  VSsetclass(vdata_id_L1SisHskp, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisHskp, vdata_id_L1SisHskp)) ==FAIL) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisHskp, "ClockCycle", DFNT_UINT32, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define ClockCycle");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "Second1996", DFNT_UINT32, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "microsecond", DFNT_UINT32, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "CycleNumber", DFNT_UINT32, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define CycleNumber");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "CommandTableIndex", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define CommandTableIndex");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorP4V", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorP4V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorP5V", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorP5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorP7V", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorP7V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorM7V", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorM7V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorP13V", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorP13V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorM13V", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorM13V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorP19V", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorP19V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorCurrentA", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorCurrentA");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "MonitorCurrentB", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define MonitorCurrentB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureMotherBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureMotherBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureAnalogBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureAnalogBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperaturePostRegBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperaturePostRegBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureLogicBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureLogicBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureLvpsBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureLvpsBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureHvpsBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureHvpsBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureM1aBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureM1aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureM2bBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureM2bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureT12aBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureT12aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureT34aBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureT34aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureT56aBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureT56aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureT78aBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureT78aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureT12bBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureT12bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureT34bBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureT34bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureT56bBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureT56bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "TemperatureT78bBoard", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define TemperatureT78bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT1a", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT2a", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT3a", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT4a", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT4a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT5a", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT5a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT6a", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT6a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT7a", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT7a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT8a", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT8a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT1b", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT2b", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT3b", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT4b", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT4b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT5b", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT5b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT6b", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT6b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT7b", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT7b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "PostDcT8b", DFNT_UINT16, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define PostDcT8b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "StatusTelemetrySide", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define StatusTelemetrySide");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "StatusRefreshEnable", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define StatusRefreshEnable");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "StatusHeatAuto", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define StatusHeatAuto");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "StatusHeatLevel", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define StatusHeatLevel");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityCycleNumber", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityCycleNumber");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityCommandTableIndex", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityCommandTableIndex");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorP4V", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorP4V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorP5V", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorP5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorP7V", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorP7V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorM7V", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorM7V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorP13V", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorP13V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorM13V", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorM13V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorP19V", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorP19V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorCurrentA", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorCurrentA");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityMonitorCurrentB", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityMonitorCurrentB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureMotherBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureMotherBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureAnalogBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureAnalogBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperaturePostRegBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperaturePostRegBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureLogicBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureLogicBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureLvpsBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureLvpsBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureHvpsBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureHvpsBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureM1aBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureM1aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureM2bBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureM2bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureT12aBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureT12aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureT34aBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureT34aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureT56aBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureT56aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureT78aBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureT78aBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureT12bBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureT12bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureT34bBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureT34bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureT56bBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureT56bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityTemperatureT78bBoard", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityTemperatureT78bBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT1a", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT2a", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT3a", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT4a", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT4a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT5a", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT5a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT6a", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT6a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT7a", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT7a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT8a", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT8a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT1b", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT2b", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT3b", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT4b", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT4b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT5b", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT5b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT6b", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT6b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT7b", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT7b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityPostDcT8b", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityPostDcT8b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityStatusTelemetrySide", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityStatusTelemetrySide");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityStatusRefreshEnable", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityStatusRefreshEnable");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityStatusHeatAuto", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityStatusHeatAuto");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHskp, "QualityStatusHeatLevel", DFNT_UINT8, (1) )) {
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSfdefine: Couldn't define QualityStatusHeatLevel");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisHskp,"ClockCycle, Second1996, microsecond, CycleNumber, CommandTableIndex, MonitorP4V, MonitorP5V, MonitorP7V, MonitorM7V, MonitorP13V, MonitorM13V, MonitorP19V, MonitorCurrentA, MonitorCurrentB, TemperatureMotherBoard, TemperatureAnalogBoard, TemperaturePostRegBoard, TemperatureLogicBoard, TemperatureLvpsBoard, TemperatureHvpsBoard, TemperatureM1aBoard, TemperatureM2bBoard, TemperatureT12aBoard, TemperatureT34aBoard, TemperatureT56aBoard, TemperatureT78aBoard, TemperatureT12bBoard, TemperatureT34bBoard, TemperatureT56bBoard, TemperatureT78bBoard, PostDcT1a, PostDcT2a, PostDcT3a, PostDcT4a, PostDcT5a, PostDcT6a, PostDcT7a, PostDcT8a, PostDcT1b, PostDcT2b, PostDcT3b, PostDcT4b, PostDcT5b, PostDcT6b, PostDcT7b, PostDcT8b, StatusTelemetrySide, StatusRefreshEnable, StatusHeatAuto, StatusHeatLevel, QualityCycleNumber, QualityCommandTableIndex, QualityMonitorP4V, QualityMonitorP5V, QualityMonitorP7V, QualityMonitorM7V, QualityMonitorP13V, QualityMonitorM13V, QualityMonitorP19V, QualityMonitorCurrentA, QualityMonitorCurrentB, QualityTemperatureMotherBoard, QualityTemperatureAnalogBoard, QualityTemperaturePostRegBoard, QualityTemperatureLogicBoard, QualityTemperatureLvpsBoard, QualityTemperatureHvpsBoard, QualityTemperatureM1aBoard, QualityTemperatureM2bBoard, QualityTemperatureT12aBoard, QualityTemperatureT34aBoard, QualityTemperatureT56aBoard, QualityTemperatureT78aBoard, QualityTemperatureT12bBoard, QualityTemperatureT34bBoard, QualityTemperatureT56bBoard, QualityTemperatureT78bBoard, QualityPostDcT1a, QualityPostDcT2a, QualityPostDcT3a, QualityPostDcT4a, QualityPostDcT5a, QualityPostDcT6a, QualityPostDcT7a, QualityPostDcT8a, QualityPostDcT1b, QualityPostDcT2b, QualityPostDcT3b, QualityPostDcT4b, QualityPostDcT5b, QualityPostDcT6b, QualityPostDcT7b, QualityPostDcT8b, QualityStatusTelemetrySide, QualityStatusRefreshEnable, QualityStatusHeatAuto, QualityStatusHeatLevel")){
    print_L1SisHskp_error("init_cr_L1SisHskp -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisHskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisHskp(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisHskp(struct L1SisHskp L1SisHskp_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1SisHskp_error();
void pack_L1SisHskp();

  odata = (uint8 *) malloc(sizeof(struct L1SisHskp));
  pack_L1SisHskp(odata, &L1SisHskp_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1SisHskp, recnum)==-1) {
		print_L1SisHskp_error("write_L1SisHskp -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisHskp, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisHskp_error("write_L1SisHskp -> VSwrite: Couldn't write data.");

  memset(&L1SisHskp_struc, 0, sizeof(struct L1SisHskp));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisHskp()
{
  VSdetach(vdata_id_L1SisHskp);
  Vdetach(vgrp_id_L1SisHskp);
}

/*----     init access function    ----*/

int32 init_acc_L1SisHskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisHskp_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1SisHskp")) <= 0 ) {
    print_L1SisHskp_error("init_acc_L1SisHskp -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisHskp = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisHskp_error("init_acc_L1SisHskp -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisHskp, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisHskp,"ClockCycle, Second1996, microsecond, CycleNumber, CommandTableIndex, MonitorP4V, MonitorP5V, MonitorP7V, MonitorM7V, MonitorP13V, MonitorM13V, MonitorP19V, MonitorCurrentA, MonitorCurrentB, TemperatureMotherBoard, TemperatureAnalogBoard, TemperaturePostRegBoard, TemperatureLogicBoard, TemperatureLvpsBoard, TemperatureHvpsBoard, TemperatureM1aBoard, TemperatureM2bBoard, TemperatureT12aBoard, TemperatureT34aBoard, TemperatureT56aBoard, TemperatureT78aBoard, TemperatureT12bBoard, TemperatureT34bBoard, TemperatureT56bBoard, TemperatureT78bBoard, PostDcT1a, PostDcT2a, PostDcT3a, PostDcT4a, PostDcT5a, PostDcT6a, PostDcT7a, PostDcT8a, PostDcT1b, PostDcT2b, PostDcT3b, PostDcT4b, PostDcT5b, PostDcT6b, PostDcT7b, PostDcT8b, StatusTelemetrySide, StatusRefreshEnable, StatusHeatAuto, StatusHeatLevel, QualityCycleNumber, QualityCommandTableIndex, QualityMonitorP4V, QualityMonitorP5V, QualityMonitorP7V, QualityMonitorM7V, QualityMonitorP13V, QualityMonitorM13V, QualityMonitorP19V, QualityMonitorCurrentA, QualityMonitorCurrentB, QualityTemperatureMotherBoard, QualityTemperatureAnalogBoard, QualityTemperaturePostRegBoard, QualityTemperatureLogicBoard, QualityTemperatureLvpsBoard, QualityTemperatureHvpsBoard, QualityTemperatureM1aBoard, QualityTemperatureM2bBoard, QualityTemperatureT12aBoard, QualityTemperatureT34aBoard, QualityTemperatureT56aBoard, QualityTemperatureT78aBoard, QualityTemperatureT12bBoard, QualityTemperatureT34bBoard, QualityTemperatureT56bBoard, QualityTemperatureT78bBoard, QualityPostDcT1a, QualityPostDcT2a, QualityPostDcT3a, QualityPostDcT4a, QualityPostDcT5a, QualityPostDcT6a, QualityPostDcT7a, QualityPostDcT8a, QualityPostDcT1b, QualityPostDcT2b, QualityPostDcT3b, QualityPostDcT4b, QualityPostDcT5b, QualityPostDcT6b, QualityPostDcT7b, QualityPostDcT8b, QualityStatusTelemetrySide, QualityStatusRefreshEnable, QualityStatusHeatAuto, QualityStatusHeatLevel")) {
      print_L1SisHskp_error("init_acc_L1SisHskp -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisHskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisHskp(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisHskp(struct L1SisHskp *L1SisHskp_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisHskp_error();
void unpack_L1SisHskp();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1SisHskp));
  VSinquire(vdata_id_L1SisHskp, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisHskp, recnum_rd)==FAIL) {
          print_L1SisHskp_error("read_L1SisHskp -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1SisHskp, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisHskp_error("read_L1SisHskp -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisHskp(odata, L1SisHskp_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisHskp()
{
  VSdetach(vdata_id_L1SisHskp);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisHskp(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisHskp_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisHskp" )) ==FAIL)
    print_L1SisHskp_error("rd_Vgrp_L1SisHskp -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisHskp_error("rd_Vgrp_L1SisHskp -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisHskp_error("rd_Vgrp_L1SisHskp -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisHskp_error("rd_Vgrp_L1SisHskp -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisHskp, HDstrlen(Vgrp_descrp_L1SisHskp)) ==FAIL)
    print_L1SisHskp_error("rd_Vgrp_L1SisHskp -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisHskp);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisHskp_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisHskp.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisHskp(uint8 *data, struct L1SisHskp *L1SisHskp_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisHskp_ptr->ClockCycle, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->CycleNumber, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->CommandTableIndex, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorP4V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorP5V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorP7V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorM7V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorP13V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorM13V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorP19V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorCurrentA, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->MonitorCurrentB, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureMotherBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureAnalogBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperaturePostRegBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureLogicBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureLvpsBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureHvpsBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureM1aBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureM2bBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureT12aBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureT34aBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureT56aBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureT78aBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureT12bBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureT34bBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureT56bBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->TemperatureT78bBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT1a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT3a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT4a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT5a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT6a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT7a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT8a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT1b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT3b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT4b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT5b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT6b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT7b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->PostDcT8b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->StatusTelemetrySide, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->StatusRefreshEnable, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->StatusHeatAuto, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->StatusHeatLevel, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityCycleNumber, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityCommandTableIndex, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorP4V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorP5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorP7V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorM7V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorP13V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorM13V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorP19V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorCurrentA, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityMonitorCurrentB, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureMotherBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureAnalogBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperaturePostRegBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureLogicBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureLvpsBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureHvpsBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureM1aBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureM2bBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureT12aBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureT34aBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureT56aBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureT78aBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureT12bBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureT34bBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureT56bBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityTemperatureT78bBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT3a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT4a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT5a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT6a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT7a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT8a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT3b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT4b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT5b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT6b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT7b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityPostDcT8b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityStatusTelemetrySide, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityStatusRefreshEnable, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityStatusHeatAuto, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisHskp_ptr->QualityStatusHeatLevel, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_L1SisHskp(uint8 *data, struct L1SisHskp *L1SisHskp_ptr)
{
int32 ptr=0;

   memcpy(&L1SisHskp_ptr->ClockCycle, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisHskp_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisHskp_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisHskp_ptr->CycleNumber, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisHskp_ptr->CommandTableIndex, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorP4V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorP5V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorP7V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorM7V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorP13V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorM13V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorP19V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorCurrentA, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->MonitorCurrentB, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureMotherBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureAnalogBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperaturePostRegBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureLogicBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureLvpsBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureHvpsBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureM1aBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureM2bBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureT12aBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureT34aBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureT56aBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureT78aBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureT12bBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureT34bBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureT56bBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->TemperatureT78bBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT1a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT3a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT4a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT5a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT6a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT7a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT8a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT1b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT3b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT4b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT5b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT6b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT7b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->PostDcT8b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisHskp_ptr->StatusTelemetrySide, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->StatusRefreshEnable, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->StatusHeatAuto, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->StatusHeatLevel, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityCycleNumber, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityCommandTableIndex, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorP4V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorP5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorP7V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorM7V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorP13V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorM13V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorP19V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorCurrentA, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityMonitorCurrentB, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureMotherBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureAnalogBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperaturePostRegBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureLogicBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureLvpsBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureHvpsBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureM1aBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureM2bBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureT12aBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureT34aBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureT56aBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureT78aBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureT12bBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureT34bBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureT56bBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityTemperatureT78bBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT3a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT4a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT5a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT6a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT7a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT8a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT3b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT4b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT5b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT6b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT7b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityPostDcT8b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityStatusTelemetrySide, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityStatusRefreshEnable, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityStatusHeatAuto, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisHskp_ptr->QualityStatusHeatLevel, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_L1SisHskp() {return(vgrp_id_L1SisHskp);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisHskp(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisHskp.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisHskp'.\n\n");
  strcat(wr_strval,"/* Id: L1SisHskp.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisHskp.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisHskp\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockCycle;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint32 CycleNumber;\n");
  strcat(wr_strval,"   uint16 CommandTableIndex;\n");
  strcat(wr_strval,"   uint16 MonitorP4V;\n");
  strcat(wr_strval,"   uint16 MonitorP5V;\n");
  strcat(wr_strval,"   uint16 MonitorP7V;\n");
  strcat(wr_strval,"   uint16 MonitorM7V;\n");
  strcat(wr_strval,"   uint16 MonitorP13V;\n");
  strcat(wr_strval,"   uint16 MonitorM13V;\n");
  strcat(wr_strval,"   uint16 MonitorP19V;\n");
  strcat(wr_strval,"   uint16 MonitorCurrentA;\n");
  strcat(wr_strval,"   uint16 MonitorCurrentB;\n");
  strcat(wr_strval,"   uint16 TemperatureMotherBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureAnalogBoard;\n");
  strcat(wr_strval,"   uint16 TemperaturePostRegBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureLogicBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureLvpsBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureHvpsBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureM1aBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureM2bBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureT12aBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureT34aBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureT56aBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureT78aBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureT12bBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureT34bBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureT56bBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureT78bBoard;\n");
  strcat(wr_strval,"   uint16 PostDcT1a;\n");
  strcat(wr_strval,"   uint16 PostDcT2a;\n");
  strcat(wr_strval,"   uint16 PostDcT3a;\n");
  strcat(wr_strval,"   uint16 PostDcT4a;\n");
  strcat(wr_strval,"   uint16 PostDcT5a;\n");
  strcat(wr_strval,"   uint16 PostDcT6a;\n");
  strcat(wr_strval,"   uint16 PostDcT7a;\n");
  strcat(wr_strval,"   uint16 PostDcT8a;\n");
  strcat(wr_strval,"   uint16 PostDcT1b;\n");
  strcat(wr_strval,"   uint16 PostDcT2b;\n");
  strcat(wr_strval,"   uint16 PostDcT3b;\n");
  strcat(wr_strval,"   uint16 PostDcT4b;\n");
  strcat(wr_strval,"   uint16 PostDcT5b;\n");
  strcat(wr_strval,"   uint16 PostDcT6b;\n");
  strcat(wr_strval,"   uint16 PostDcT7b;\n");
  strcat(wr_strval,"   uint16 PostDcT8b;\n");
  strcat(wr_strval,"   uint8  StatusTelemetrySide;\n");
  strcat(wr_strval,"   uint8  StatusRefreshEnable;\n");
  strcat(wr_strval,"   uint8  StatusHeatAuto;\n");
  strcat(wr_strval,"   uint8  StatusHeatLevel;\n");
  strcat(wr_strval,"   uint8  QualityCycleNumber;\n");
  strcat(wr_strval,"   uint8  QualityCommandTableIndex;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP4V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP5V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP7V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorM7V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP13V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorM13V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP19V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorCurrentA;\n");
  strcat(wr_strval,"   uint8  QualityMonitorCurrentB;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureMotherBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureAnalogBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperaturePostRegBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureLogicBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureLvpsBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureHvpsBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureM1aBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureM2bBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureT12aBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureT34aBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureT56aBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureT78aBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureT12bBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureT34bBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureT56bBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureT78bBoard;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT1a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT2a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT3a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT4a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT5a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT6a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT7a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT8a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT1b;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT2b;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT3b;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT4b;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT5b;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT6b;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT7b;\n");
  strcat(wr_strval,"   uint8  QualityPostDcT8b;\n");
  strcat(wr_strval,"   uint8  QualityStatusTelemetrySide;\n");
  strcat(wr_strval,"   uint8  QualityStatusRefreshEnable;\n");
  strcat(wr_strval,"   uint8  QualityStatusHeatAuto;\n");
  strcat(wr_strval,"   uint8  QualityStatusHeatLevel;\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockCycle = S/C clock of the first minor frame of the cycle   */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Note: Quality bits are defined in the table below.  If the field  */\n");
  strcat(wr_strval,"/*       which the quality byte is trying to characterize contains   */\n");
  strcat(wr_strval,"/*       multiple bytes, the quality byte associated with the field  */\n");
  strcat(wr_strval,"/*       is the logical \"or\" of the individual quality bytes.        */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Quality bits:                                                     */\n");
  strcat(wr_strval,"/*    0x01 = Format ID error                                         */\n");
  strcat(wr_strval,"/*    0x02 = Minor/major counter error                               */\n");
  strcat(wr_strval,"/*    0x04 = S/C clock error                                         */\n");
  strcat(wr_strval,"/*    0x08 = Sync bit error                                          */\n");
  strcat(wr_strval,"/*    0x10 = Command table index error                               */\n");
  strcat(wr_strval,"/*    0x20 = Cycle number error                                      */\n");
  strcat(wr_strval,"/*    0x40 = Level 0 quality bit                                     */\n");
  strcat(wr_strval,"/*    0x80 = Level 1 quality bit                                     */\n");
  return(0);
}
