/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1CrisHskp.h,v 1.2 1997/09/11 00:37:38 jeff Exp  */

#include "L1CrisHskp.h"
#include "df.h"

int32 vgrp_id_L1CrisHskp;
static int32 vdata_id_L1CrisHskp;

  /* 7407 is the size of L1CrisHskp.h + 1 added line */
char Vgrp_descrp_L1CrisHskp[7407];

/****----  init create function  ----****/

int32 init_cr_L1CrisHskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1CrisHskp();

  void print_L1CrisHskp_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1CrisHskp = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1CrisHskp, "VG_L1CrisHskp"); 
  Vsetclass(vgrp_id_L1CrisHskp, "VG_L1CRISHSKP");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1CrisHskp" )) ==FAIL) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1CrisHskp(Vgrp_descrp_L1CrisHskp);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1CrisHskp, sizeof(Vgrp_descrp_L1CrisHskp))) ==FAIL) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1CrisHskp = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1CrisHskp, "L1CrisHskp");
  VSsetclass(vdata_id_L1CrisHskp, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1CrisHskp, vdata_id_L1CrisHskp)) ==FAIL) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1CrisHskp, "ClockCycle", DFNT_UINT32, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define ClockCycle");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "Second1996", DFNT_UINT32, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "microsecond", DFNT_UINT32, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "CommandTableIndex", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define CommandTableIndex");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorP5V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorP5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorP6V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorP6V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorM6V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorM6V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorP7V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorP7V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorM7V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorM7V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorP12V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorP12V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorM12V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorM12V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorP13V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorP13V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorM13V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorM13V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorP15V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorP15V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorP19V", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorP19V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorMcp1", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorMcp1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorMcp2", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorMcp2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorHvps1I", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorHvps1I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorHvps2I", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorHvps2I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorHvps3I", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorHvps3I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorHvps4I", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorHvps4I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorSoftPsaI", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorSoftPsaI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "MonitorSoftPsbI", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define MonitorSoftPsbI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureMotherBoardElect", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureMotherBoardElect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureMotherBoardDet", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureMotherBoardDet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureMotherBoardC", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureMotherBoardC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureAnalogBoard", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureAnalogBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperaturePostRegBoard", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperaturePostRegBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureLogicBoard", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureLogicBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureE12Elect", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureE12Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureE12Det", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureE12Det");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureE34Elect", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureE34Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureE34Det", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureE34Det");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureE56Elect", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureE56Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureE56Det", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureE56Det");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureE789Elect", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureE789Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureE789Det", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureE789Det");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureLvps", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureLvps");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureHvps", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureHvps");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureFiberPlaneTop0", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureFiberPlaneTop0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureFiberPlaneTop1", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureFiberPlaneTop1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureFiberPlaneMid", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureFiberPlaneMid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureFiberPlaneBot", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureFiberPlaneBot");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureImageInt1Side", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureImageInt1Side");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureImageInt1Rear", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureImageInt1Rear");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureCamera1Elect", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureCamera1Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureHvps1", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureHvps1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureImageInt2Side", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureImageInt2Side");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureImageInt2Rear", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureImageInt2Rear");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureCamera2Elect", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureCamera2Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "TemperatureHvps2", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define TemperatureHvps2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE1a", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE1b", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE2ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE3ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE4ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE5ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE6ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE7ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE8ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE8ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE9ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE9ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG2ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG3ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG4ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG5ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG6ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG7ab", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE1c", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE1c");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE1d", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE1d");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE2cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE3cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE4cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE5cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE6cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE7cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE8cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE8cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcE9cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcE9cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG2cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG3cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG4cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG5cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG6cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "PostDcG7cd", DFNT_UINT16, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define PostDcG7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG2ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG3ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG4ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG5ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG6ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG7ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacE9ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacE9ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG2cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG3cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG4cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG5cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG6cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacG7cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacG7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "DacE9cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define DacE9cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "HeaterCcdA", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define HeaterCcdA");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "HeaterCcdB", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define HeaterCcdB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "HeaterCris", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define HeaterCris");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "StatusTmSide", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define StatusTmSide");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "StatusRefresh", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define StatusRefresh");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityCommandTableIndex", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityCommandTableIndex");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorP5V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorP5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorP6V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorP6V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorM6V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorM6V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorP7V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorP7V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorM7V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorM7V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorP12V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorP12V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorM12V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorM12V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorP13V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorP13V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorM13V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorM13V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorP15V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorP15V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorP19V", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorP19V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorMcp1", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorMcp1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorMcp2", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorMcp2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorHvps1I", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorHvps1I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorHvps2I", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorHvps2I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorHvps3I", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorHvps3I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorHvps4I", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorHvps4I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorSoftPsaI", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorSoftPsaI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityMonitorSoftPsbI", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityMonitorSoftPsbI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureMotherBoardElect", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureMotherBoardElect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureMotherBoardDet", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureMotherBoardDet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureMotherBoardC", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureMotherBoardC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureAnalogBoard", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureAnalogBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperaturePostRegBoard", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperaturePostRegBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureLogicBoard", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureLogicBoard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureE12Elect", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureE12Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureE12Det", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureE12Det");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureE34Elect", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureE34Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureE34Det", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureE34Det");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureE56Elect", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureE56Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureE56Det", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureE56Det");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureE789Elect", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureE789Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureE789Det", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureE789Det");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureLvps", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureLvps");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureHvps", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureHvps");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureFiberPlaneTop0", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureFiberPlaneTop0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureFiberPlaneTop1", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureFiberPlaneTop1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureFiberPlaneMid", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureFiberPlaneMid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureFiberPlaneBot", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureFiberPlaneBot");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureImageInt1Side", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureImageInt1Side");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureImageInt1Rear", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureImageInt1Rear");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureCamera1Elect", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureCamera1Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureHvps1", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureHvps1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureImageInt2Side", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureImageInt2Side");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureImageInt2Rear", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureImageInt2Rear");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureCamera2Elect", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureCamera2Elect");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityTemperatureHvps2", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityTemperatureHvps2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE1a", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE1b", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE2ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE3ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE4ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE5ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE6ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE7ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE8ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE8ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE9ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE9ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG2ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG3ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG4ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG5ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG6ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG7ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE1c", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE1c");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE1d", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE1d");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE2cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE3cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE4cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE5cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE6cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE7cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE8cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE8cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcE9cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcE9cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG2cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG3cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG4cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG5cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG6cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityPostDcG7cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityPostDcG7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG2ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG3ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG4ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG5ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG6ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG7ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacE9ab", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacE9ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG2cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG3cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG4cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG5cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG6cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacG7cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacG7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityDacE9cd", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityDacE9cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityHeaterCcdA", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityHeaterCcdA");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityHeaterCcdB", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityHeaterCcdB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityHeaterCris", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityHeaterCris");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityStatusTmSide", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityStatusTmSide");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisHskp, "QualityStatusRefresh", DFNT_UINT8, (1) )) {
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSfdefine: Couldn't define QualityStatusRefresh");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1CrisHskp,"ClockCycle, Second1996, microsecond, CommandTableIndex, MonitorP5V, MonitorP6V, MonitorM6V, MonitorP7V, MonitorM7V, MonitorP12V, MonitorM12V, MonitorP13V, MonitorM13V, MonitorP15V, MonitorP19V, MonitorMcp1, MonitorMcp2, MonitorHvps1I, MonitorHvps2I, MonitorHvps3I, MonitorHvps4I, MonitorSoftPsaI, MonitorSoftPsbI, TemperatureMotherBoardElect, TemperatureMotherBoardDet, TemperatureMotherBoardC, TemperatureAnalogBoard, TemperaturePostRegBoard, TemperatureLogicBoard, TemperatureE12Elect, TemperatureE12Det, TemperatureE34Elect, TemperatureE34Det, TemperatureE56Elect, TemperatureE56Det, TemperatureE789Elect, TemperatureE789Det, TemperatureLvps, TemperatureHvps, TemperatureFiberPlaneTop0, TemperatureFiberPlaneTop1, TemperatureFiberPlaneMid, TemperatureFiberPlaneBot, TemperatureImageInt1Side, TemperatureImageInt1Rear, TemperatureCamera1Elect, TemperatureHvps1, TemperatureImageInt2Side, TemperatureImageInt2Rear, TemperatureCamera2Elect, TemperatureHvps2, PostDcE1a, PostDcE1b, PostDcE2ab, PostDcE3ab, PostDcE4ab, PostDcE5ab, PostDcE6ab, PostDcE7ab, PostDcE8ab, PostDcE9ab, PostDcG2ab, PostDcG3ab, PostDcG4ab, PostDcG5ab, PostDcG6ab, PostDcG7ab, PostDcE1c, PostDcE1d, PostDcE2cd, PostDcE3cd, PostDcE4cd, PostDcE5cd, PostDcE6cd, PostDcE7cd, PostDcE8cd, PostDcE9cd, PostDcG2cd, PostDcG3cd, PostDcG4cd, PostDcG5cd, PostDcG6cd, PostDcG7cd, DacG2ab, DacG3ab, DacG4ab, DacG5ab, DacG6ab, DacG7ab, DacE9ab, DacG2cd, DacG3cd, DacG4cd, DacG5cd, DacG6cd, DacG7cd, DacE9cd, HeaterCcdA, HeaterCcdB, HeaterCris, StatusTmSide, StatusRefresh, QualityCommandTableIndex, QualityMonitorP5V, QualityMonitorP6V, QualityMonitorM6V, QualityMonitorP7V, QualityMonitorM7V, QualityMonitorP12V, QualityMonitorM12V, QualityMonitorP13V, QualityMonitorM13V, QualityMonitorP15V, QualityMonitorP19V, QualityMonitorMcp1, QualityMonitorMcp2, QualityMonitorHvps1I, QualityMonitorHvps2I, QualityMonitorHvps3I, QualityMonitorHvps4I, QualityMonitorSoftPsaI, QualityMonitorSoftPsbI, QualityTemperatureMotherBoardElect, QualityTemperatureMotherBoardDet, QualityTemperatureMotherBoardC, QualityTemperatureAnalogBoard, QualityTemperaturePostRegBoard, QualityTemperatureLogicBoard, QualityTemperatureE12Elect, QualityTemperatureE12Det, QualityTemperatureE34Elect, QualityTemperatureE34Det, QualityTemperatureE56Elect, QualityTemperatureE56Det, QualityTemperatureE789Elect, QualityTemperatureE789Det, QualityTemperatureLvps, QualityTemperatureHvps, QualityTemperatureFiberPlaneTop0, QualityTemperatureFiberPlaneTop1, QualityTemperatureFiberPlaneMid, QualityTemperatureFiberPlaneBot, QualityTemperatureImageInt1Side, QualityTemperatureImageInt1Rear, QualityTemperatureCamera1Elect, QualityTemperatureHvps1, QualityTemperatureImageInt2Side, QualityTemperatureImageInt2Rear, QualityTemperatureCamera2Elect, QualityTemperatureHvps2, QualityPostDcE1a, QualityPostDcE1b, QualityPostDcE2ab, QualityPostDcE3ab, QualityPostDcE4ab, QualityPostDcE5ab, QualityPostDcE6ab, QualityPostDcE7ab, QualityPostDcE8ab, QualityPostDcE9ab, QualityPostDcG2ab, QualityPostDcG3ab, QualityPostDcG4ab, QualityPostDcG5ab, QualityPostDcG6ab, QualityPostDcG7ab, QualityPostDcE1c, QualityPostDcE1d, QualityPostDcE2cd, QualityPostDcE3cd, QualityPostDcE4cd, QualityPostDcE5cd, QualityPostDcE6cd, QualityPostDcE7cd, QualityPostDcE8cd, QualityPostDcE9cd, QualityPostDcG2cd, QualityPostDcG3cd, QualityPostDcG4cd, QualityPostDcG5cd, QualityPostDcG6cd, QualityPostDcG7cd, QualityDacG2ab, QualityDacG3ab, QualityDacG4ab, QualityDacG5ab, QualityDacG6ab, QualityDacG7ab, QualityDacE9ab, QualityDacG2cd, QualityDacG3cd, QualityDacG4cd, QualityDacG5cd, QualityDacG6cd, QualityDacG7cd, QualityDacE9cd, QualityHeaterCcdA, QualityHeaterCcdB, QualityHeaterCris, QualityStatusTmSide, QualityStatusRefresh")){
    print_L1CrisHskp_error("init_cr_L1CrisHskp -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1CrisHskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1CrisHskp(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1CrisHskp(struct L1CrisHskp L1CrisHskp_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1CrisHskp_error();
void pack_L1CrisHskp();

  odata = (uint8 *) malloc(sizeof(struct L1CrisHskp));
  pack_L1CrisHskp(odata, &L1CrisHskp_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1CrisHskp, recnum)==-1) {
		print_L1CrisHskp_error("write_L1CrisHskp -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1CrisHskp, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1CrisHskp_error("write_L1CrisHskp -> VSwrite: Couldn't write data.");

  memset(&L1CrisHskp_struc, 0, sizeof(struct L1CrisHskp));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1CrisHskp()
{
  VSdetach(vdata_id_L1CrisHskp);
  Vdetach(vgrp_id_L1CrisHskp);
}

/*----     init access function    ----*/

int32 init_acc_L1CrisHskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1CrisHskp_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1CrisHskp")) <= 0 ) {
    print_L1CrisHskp_error("init_acc_L1CrisHskp -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1CrisHskp = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1CrisHskp_error("init_acc_L1CrisHskp -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1CrisHskp, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1CrisHskp,"ClockCycle, Second1996, microsecond, CommandTableIndex, MonitorP5V, MonitorP6V, MonitorM6V, MonitorP7V, MonitorM7V, MonitorP12V, MonitorM12V, MonitorP13V, MonitorM13V, MonitorP15V, MonitorP19V, MonitorMcp1, MonitorMcp2, MonitorHvps1I, MonitorHvps2I, MonitorHvps3I, MonitorHvps4I, MonitorSoftPsaI, MonitorSoftPsbI, TemperatureMotherBoardElect, TemperatureMotherBoardDet, TemperatureMotherBoardC, TemperatureAnalogBoard, TemperaturePostRegBoard, TemperatureLogicBoard, TemperatureE12Elect, TemperatureE12Det, TemperatureE34Elect, TemperatureE34Det, TemperatureE56Elect, TemperatureE56Det, TemperatureE789Elect, TemperatureE789Det, TemperatureLvps, TemperatureHvps, TemperatureFiberPlaneTop0, TemperatureFiberPlaneTop1, TemperatureFiberPlaneMid, TemperatureFiberPlaneBot, TemperatureImageInt1Side, TemperatureImageInt1Rear, TemperatureCamera1Elect, TemperatureHvps1, TemperatureImageInt2Side, TemperatureImageInt2Rear, TemperatureCamera2Elect, TemperatureHvps2, PostDcE1a, PostDcE1b, PostDcE2ab, PostDcE3ab, PostDcE4ab, PostDcE5ab, PostDcE6ab, PostDcE7ab, PostDcE8ab, PostDcE9ab, PostDcG2ab, PostDcG3ab, PostDcG4ab, PostDcG5ab, PostDcG6ab, PostDcG7ab, PostDcE1c, PostDcE1d, PostDcE2cd, PostDcE3cd, PostDcE4cd, PostDcE5cd, PostDcE6cd, PostDcE7cd, PostDcE8cd, PostDcE9cd, PostDcG2cd, PostDcG3cd, PostDcG4cd, PostDcG5cd, PostDcG6cd, PostDcG7cd, DacG2ab, DacG3ab, DacG4ab, DacG5ab, DacG6ab, DacG7ab, DacE9ab, DacG2cd, DacG3cd, DacG4cd, DacG5cd, DacG6cd, DacG7cd, DacE9cd, HeaterCcdA, HeaterCcdB, HeaterCris, StatusTmSide, StatusRefresh, QualityCommandTableIndex, QualityMonitorP5V, QualityMonitorP6V, QualityMonitorM6V, QualityMonitorP7V, QualityMonitorM7V, QualityMonitorP12V, QualityMonitorM12V, QualityMonitorP13V, QualityMonitorM13V, QualityMonitorP15V, QualityMonitorP19V, QualityMonitorMcp1, QualityMonitorMcp2, QualityMonitorHvps1I, QualityMonitorHvps2I, QualityMonitorHvps3I, QualityMonitorHvps4I, QualityMonitorSoftPsaI, QualityMonitorSoftPsbI, QualityTemperatureMotherBoardElect, QualityTemperatureMotherBoardDet, QualityTemperatureMotherBoardC, QualityTemperatureAnalogBoard, QualityTemperaturePostRegBoard, QualityTemperatureLogicBoard, QualityTemperatureE12Elect, QualityTemperatureE12Det, QualityTemperatureE34Elect, QualityTemperatureE34Det, QualityTemperatureE56Elect, QualityTemperatureE56Det, QualityTemperatureE789Elect, QualityTemperatureE789Det, QualityTemperatureLvps, QualityTemperatureHvps, QualityTemperatureFiberPlaneTop0, QualityTemperatureFiberPlaneTop1, QualityTemperatureFiberPlaneMid, QualityTemperatureFiberPlaneBot, QualityTemperatureImageInt1Side, QualityTemperatureImageInt1Rear, QualityTemperatureCamera1Elect, QualityTemperatureHvps1, QualityTemperatureImageInt2Side, QualityTemperatureImageInt2Rear, QualityTemperatureCamera2Elect, QualityTemperatureHvps2, QualityPostDcE1a, QualityPostDcE1b, QualityPostDcE2ab, QualityPostDcE3ab, QualityPostDcE4ab, QualityPostDcE5ab, QualityPostDcE6ab, QualityPostDcE7ab, QualityPostDcE8ab, QualityPostDcE9ab, QualityPostDcG2ab, QualityPostDcG3ab, QualityPostDcG4ab, QualityPostDcG5ab, QualityPostDcG6ab, QualityPostDcG7ab, QualityPostDcE1c, QualityPostDcE1d, QualityPostDcE2cd, QualityPostDcE3cd, QualityPostDcE4cd, QualityPostDcE5cd, QualityPostDcE6cd, QualityPostDcE7cd, QualityPostDcE8cd, QualityPostDcE9cd, QualityPostDcG2cd, QualityPostDcG3cd, QualityPostDcG4cd, QualityPostDcG5cd, QualityPostDcG6cd, QualityPostDcG7cd, QualityDacG2ab, QualityDacG3ab, QualityDacG4ab, QualityDacG5ab, QualityDacG6ab, QualityDacG7ab, QualityDacE9ab, QualityDacG2cd, QualityDacG3cd, QualityDacG4cd, QualityDacG5cd, QualityDacG6cd, QualityDacG7cd, QualityDacE9cd, QualityHeaterCcdA, QualityHeaterCcdB, QualityHeaterCris, QualityStatusTmSide, QualityStatusRefresh")) {
      print_L1CrisHskp_error("init_acc_L1CrisHskp -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1CrisHskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1CrisHskp(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1CrisHskp(struct L1CrisHskp *L1CrisHskp_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1CrisHskp_error();
void unpack_L1CrisHskp();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1CrisHskp));
  VSinquire(vdata_id_L1CrisHskp, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1CrisHskp, recnum_rd)==FAIL) {
          print_L1CrisHskp_error("read_L1CrisHskp -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1CrisHskp, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1CrisHskp_error("read_L1CrisHskp -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1CrisHskp(odata, L1CrisHskp_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1CrisHskp()
{
  VSdetach(vdata_id_L1CrisHskp);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1CrisHskp(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1CrisHskp_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1CrisHskp" )) ==FAIL)
    print_L1CrisHskp_error("rd_Vgrp_L1CrisHskp -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1CrisHskp_error("rd_Vgrp_L1CrisHskp -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1CrisHskp_error("rd_Vgrp_L1CrisHskp -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1CrisHskp_error("rd_Vgrp_L1CrisHskp -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1CrisHskp, HDstrlen(Vgrp_descrp_L1CrisHskp)) ==FAIL)
    print_L1CrisHskp_error("rd_Vgrp_L1CrisHskp -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1CrisHskp);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1CrisHskp_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1CrisHskp.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1CrisHskp(uint8 *data, struct L1CrisHskp *L1CrisHskp_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1CrisHskp_ptr->ClockCycle, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->CommandTableIndex, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorP5V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorP6V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorM6V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorP7V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorM7V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorP12V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorM12V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorP13V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorM13V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorP15V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorP19V, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorMcp1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorMcp2, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorHvps1I, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorHvps2I, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorHvps3I, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorHvps4I, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorSoftPsaI, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->MonitorSoftPsbI, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureMotherBoardElect, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureMotherBoardDet, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureMotherBoardC, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureAnalogBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperaturePostRegBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureLogicBoard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureE12Elect, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureE12Det, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureE34Elect, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureE34Det, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureE56Elect, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureE56Det, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureE789Elect, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureE789Det, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureLvps, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureHvps, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureFiberPlaneTop0, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureFiberPlaneTop1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureFiberPlaneMid, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureFiberPlaneBot, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureImageInt1Side, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureImageInt1Rear, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureCamera1Elect, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureHvps1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureImageInt2Side, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureImageInt2Rear, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureCamera2Elect, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->TemperatureHvps2, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE1a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE1b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE2ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE3ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE4ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE5ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE6ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE7ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE8ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE9ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG2ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG3ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG4ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG5ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG6ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG7ab, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE1c, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE1d, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE2cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE3cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE4cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE5cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE6cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE7cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE8cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcE9cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG2cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG3cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG4cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG5cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG6cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->PostDcG7cd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG3ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG4ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG5ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG6ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG7ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacE9ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG3cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG4cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG5cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG6cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacG7cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->DacE9cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->HeaterCcdA, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->HeaterCcdB, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->HeaterCris, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->StatusTmSide, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->StatusRefresh, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityCommandTableIndex, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorP5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorP6V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorM6V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorP7V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorM7V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorP12V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorM12V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorP13V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorM13V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorP15V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorP19V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorMcp1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorMcp2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorHvps1I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorHvps2I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorHvps3I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorHvps4I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorSoftPsaI, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityMonitorSoftPsbI, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureMotherBoardElect, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureMotherBoardDet, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureMotherBoardC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureAnalogBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperaturePostRegBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureLogicBoard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureE12Elect, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureE12Det, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureE34Elect, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureE34Det, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureE56Elect, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureE56Det, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureE789Elect, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureE789Det, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureLvps, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureHvps, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureFiberPlaneTop0, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureFiberPlaneTop1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureFiberPlaneMid, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureFiberPlaneBot, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureImageInt1Side, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureImageInt1Rear, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureCamera1Elect, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureHvps1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureImageInt2Side, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureImageInt2Rear, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureCamera2Elect, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityTemperatureHvps2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE3ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE4ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE5ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE6ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE7ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE8ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE9ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG3ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG4ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG5ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG6ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG7ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE1c, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE1d, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE3cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE4cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE5cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE6cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE7cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE8cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcE9cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG3cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG4cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG5cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG6cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityPostDcG7cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG3ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG4ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG5ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG6ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG7ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacE9ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG3cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG4cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG5cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG6cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacG7cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityDacE9cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityHeaterCcdA, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityHeaterCcdB, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityHeaterCris, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityStatusTmSide, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisHskp_ptr->QualityStatusRefresh, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_L1CrisHskp(uint8 *data, struct L1CrisHskp *L1CrisHskp_ptr)
{
int32 ptr=0;

   memcpy(&L1CrisHskp_ptr->ClockCycle, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisHskp_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisHskp_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisHskp_ptr->CommandTableIndex, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorP5V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorP6V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorM6V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorP7V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorM7V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorP12V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorM12V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorP13V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorM13V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorP15V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorP19V, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorMcp1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorMcp2, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorHvps1I, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorHvps2I, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorHvps3I, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorHvps4I, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorSoftPsaI, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->MonitorSoftPsbI, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureMotherBoardElect, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureMotherBoardDet, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureMotherBoardC, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureAnalogBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperaturePostRegBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureLogicBoard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureE12Elect, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureE12Det, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureE34Elect, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureE34Det, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureE56Elect, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureE56Det, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureE789Elect, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureE789Det, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureLvps, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureHvps, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureFiberPlaneTop0, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureFiberPlaneTop1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureFiberPlaneMid, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureFiberPlaneBot, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureImageInt1Side, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureImageInt1Rear, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureCamera1Elect, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureHvps1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureImageInt2Side, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureImageInt2Rear, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureCamera2Elect, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->TemperatureHvps2, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE1a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE1b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE2ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE3ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE4ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE5ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE6ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE7ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE8ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE9ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG2ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG3ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG4ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG5ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG6ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG7ab, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE1c, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE1d, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE2cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE3cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE4cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE5cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE6cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE7cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE8cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcE9cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG2cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG3cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG4cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG5cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG6cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->PostDcG7cd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisHskp_ptr->DacG2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG3ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG4ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG5ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG6ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG7ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacE9ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG3cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG4cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG5cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG6cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacG7cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->DacE9cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->HeaterCcdA, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->HeaterCcdB, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->HeaterCris, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->StatusTmSide, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->StatusRefresh, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityCommandTableIndex, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorP5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorP6V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorM6V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorP7V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorM7V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorP12V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorM12V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorP13V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorM13V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorP15V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorP19V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorMcp1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorMcp2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorHvps1I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorHvps2I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorHvps3I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorHvps4I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorSoftPsaI, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityMonitorSoftPsbI, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureMotherBoardElect, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureMotherBoardDet, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureMotherBoardC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureAnalogBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperaturePostRegBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureLogicBoard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureE12Elect, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureE12Det, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureE34Elect, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureE34Det, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureE56Elect, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureE56Det, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureE789Elect, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureE789Det, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureLvps, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureHvps, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureFiberPlaneTop0, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureFiberPlaneTop1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureFiberPlaneMid, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureFiberPlaneBot, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureImageInt1Side, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureImageInt1Rear, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureCamera1Elect, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureHvps1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureImageInt2Side, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureImageInt2Rear, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureCamera2Elect, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityTemperatureHvps2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE3ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE4ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE5ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE6ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE7ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE8ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE9ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG3ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG4ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG5ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG6ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG7ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE1c, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE1d, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE3cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE4cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE5cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE6cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE7cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE8cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcE9cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG3cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG4cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG5cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG6cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityPostDcG7cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG3ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG4ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG5ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG6ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG7ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacE9ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG3cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG4cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG5cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG6cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacG7cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityDacE9cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityHeaterCcdA, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityHeaterCcdB, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityHeaterCris, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityStatusTmSide, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisHskp_ptr->QualityStatusRefresh, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_L1CrisHskp() {return(vgrp_id_L1CrisHskp);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1CrisHskp(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1CrisHskp.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1CrisHskp'.\n\n");
  strcat(wr_strval,"/* Id: L1CrisHskp.h,v 1.2 1997/09/11 00:37:38 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisHskp.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 00:37:38 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1CrisHskp\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockCycle;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint16 CommandTableIndex;\n");
  strcat(wr_strval,"   uint16 MonitorP5V;\n");
  strcat(wr_strval,"   uint16 MonitorP6V;\n");
  strcat(wr_strval,"   uint16 MonitorM6V;\n");
  strcat(wr_strval,"   uint16 MonitorP7V;\n");
  strcat(wr_strval,"   uint16 MonitorM7V;\n");
  strcat(wr_strval,"   uint16 MonitorP12V;\n");
  strcat(wr_strval,"   uint16 MonitorM12V;\n");
  strcat(wr_strval,"   uint16 MonitorP13V;\n");
  strcat(wr_strval,"   uint16 MonitorM13V;\n");
  strcat(wr_strval,"   uint16 MonitorP15V;\n");
  strcat(wr_strval,"   uint16 MonitorP19V;\n");
  strcat(wr_strval,"   uint16 MonitorMcp1;\n");
  strcat(wr_strval,"   uint16 MonitorMcp2;\n");
  strcat(wr_strval,"   uint16 MonitorHvps1I;\n");
  strcat(wr_strval,"   uint16 MonitorHvps2I;\n");
  strcat(wr_strval,"   uint16 MonitorHvps3I;\n");
  strcat(wr_strval,"   uint16 MonitorHvps4I;\n");
  strcat(wr_strval,"   uint16 MonitorSoftPsaI;\n");
  strcat(wr_strval,"   uint16 MonitorSoftPsbI;\n");
  strcat(wr_strval,"   uint16 TemperatureMotherBoardElect;\n");
  strcat(wr_strval,"   uint16 TemperatureMotherBoardDet;\n");
  strcat(wr_strval,"   uint16 TemperatureMotherBoardC;\n");
  strcat(wr_strval,"   uint16 TemperatureAnalogBoard;\n");
  strcat(wr_strval,"   uint16 TemperaturePostRegBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureLogicBoard;\n");
  strcat(wr_strval,"   uint16 TemperatureE12Elect;\n");
  strcat(wr_strval,"   uint16 TemperatureE12Det;\n");
  strcat(wr_strval,"   uint16 TemperatureE34Elect;\n");
  strcat(wr_strval,"   uint16 TemperatureE34Det;\n");
  strcat(wr_strval,"   uint16 TemperatureE56Elect;\n");
  strcat(wr_strval,"   uint16 TemperatureE56Det;\n");
  strcat(wr_strval,"   uint16 TemperatureE789Elect;\n");
  strcat(wr_strval,"   uint16 TemperatureE789Det;\n");
  strcat(wr_strval,"   uint16 TemperatureLvps;\n");
  strcat(wr_strval,"   uint16 TemperatureHvps;\n");
  strcat(wr_strval,"   uint16 TemperatureFiberPlaneTop0;\n");
  strcat(wr_strval,"   uint16 TemperatureFiberPlaneTop1;\n");
  strcat(wr_strval,"   uint16 TemperatureFiberPlaneMid;\n");
  strcat(wr_strval,"   uint16 TemperatureFiberPlaneBot;\n");
  strcat(wr_strval,"   uint16 TemperatureImageInt1Side;\n");
  strcat(wr_strval,"   uint16 TemperatureImageInt1Rear;\n");
  strcat(wr_strval,"   uint16 TemperatureCamera1Elect;\n");
  strcat(wr_strval,"   uint16 TemperatureHvps1;\n");
  strcat(wr_strval,"   uint16 TemperatureImageInt2Side;\n");
  strcat(wr_strval,"   uint16 TemperatureImageInt2Rear;\n");
  strcat(wr_strval,"   uint16 TemperatureCamera2Elect;\n");
  strcat(wr_strval,"   uint16 TemperatureHvps2;\n");
  strcat(wr_strval,"   uint16 PostDcE1a;\n");
  strcat(wr_strval,"   uint16 PostDcE1b;\n");
  strcat(wr_strval,"   uint16 PostDcE2ab;\n");
  strcat(wr_strval,"   uint16 PostDcE3ab;\n");
  strcat(wr_strval,"   uint16 PostDcE4ab;\n");
  strcat(wr_strval,"   uint16 PostDcE5ab;\n");
  strcat(wr_strval,"   uint16 PostDcE6ab;\n");
  strcat(wr_strval,"   uint16 PostDcE7ab;\n");
  strcat(wr_strval,"   uint16 PostDcE8ab;\n");
  strcat(wr_strval,"   uint16 PostDcE9ab;\n");
  strcat(wr_strval,"   uint16 PostDcG2ab;\n");
  strcat(wr_strval,"   uint16 PostDcG3ab;\n");
  strcat(wr_strval,"   uint16 PostDcG4ab;\n");
  strcat(wr_strval,"   uint16 PostDcG5ab;\n");
  strcat(wr_strval,"   uint16 PostDcG6ab;\n");
  strcat(wr_strval,"   uint16 PostDcG7ab;\n");
  strcat(wr_strval,"   uint16 PostDcE1c;\n");
  strcat(wr_strval,"   uint16 PostDcE1d;\n");
  strcat(wr_strval,"   uint16 PostDcE2cd;\n");
  strcat(wr_strval,"   uint16 PostDcE3cd;\n");
  strcat(wr_strval,"   uint16 PostDcE4cd;\n");
  strcat(wr_strval,"   uint16 PostDcE5cd;\n");
  strcat(wr_strval,"   uint16 PostDcE6cd;\n");
  strcat(wr_strval,"   uint16 PostDcE7cd;\n");
  strcat(wr_strval,"   uint16 PostDcE8cd;\n");
  strcat(wr_strval,"   uint16 PostDcE9cd;\n");
  strcat(wr_strval,"   uint16 PostDcG2cd;\n");
  strcat(wr_strval,"   uint16 PostDcG3cd;\n");
  strcat(wr_strval,"   uint16 PostDcG4cd;\n");
  strcat(wr_strval,"   uint16 PostDcG5cd;\n");
  strcat(wr_strval,"   uint16 PostDcG6cd;\n");
  strcat(wr_strval,"   uint16 PostDcG7cd;\n");
  strcat(wr_strval,"   uint8  DacG2ab;\n");
  strcat(wr_strval,"   uint8  DacG3ab;\n");
  strcat(wr_strval,"   uint8  DacG4ab;\n");
  strcat(wr_strval,"   uint8  DacG5ab;\n");
  strcat(wr_strval,"   uint8  DacG6ab;\n");
  strcat(wr_strval,"   uint8  DacG7ab;\n");
  strcat(wr_strval,"   uint8  DacE9ab;\n");
  strcat(wr_strval,"   uint8  DacG2cd;\n");
  strcat(wr_strval,"   uint8  DacG3cd;\n");
  strcat(wr_strval,"   uint8  DacG4cd;\n");
  strcat(wr_strval,"   uint8  DacG5cd;\n");
  strcat(wr_strval,"   uint8  DacG6cd;\n");
  strcat(wr_strval,"   uint8  DacG7cd;\n");
  strcat(wr_strval,"   uint8  DacE9cd;\n");
  strcat(wr_strval,"   uint8  HeaterCcdA;\n");
  strcat(wr_strval,"   uint8  HeaterCcdB;\n");
  strcat(wr_strval,"   uint8  HeaterCris;\n");
  strcat(wr_strval,"   uint8  StatusTmSide;\n");
  strcat(wr_strval,"   uint8  StatusRefresh;\n");
  strcat(wr_strval,"   uint8  QualityCommandTableIndex;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP5V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP6V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorM6V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP7V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorM7V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP12V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorM12V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP13V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorM13V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP15V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorP19V;\n");
  strcat(wr_strval,"   uint8  QualityMonitorMcp1;\n");
  strcat(wr_strval,"   uint8  QualityMonitorMcp2;\n");
  strcat(wr_strval,"   uint8  QualityMonitorHvps1I;\n");
  strcat(wr_strval,"   uint8  QualityMonitorHvps2I;\n");
  strcat(wr_strval,"   uint8  QualityMonitorHvps3I;\n");
  strcat(wr_strval,"   uint8  QualityMonitorHvps4I;\n");
  strcat(wr_strval,"   uint8  QualityMonitorSoftPsaI;\n");
  strcat(wr_strval,"   uint8  QualityMonitorSoftPsbI;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureMotherBoardElect;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureMotherBoardDet;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureMotherBoardC;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureAnalogBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperaturePostRegBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureLogicBoard;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureE12Elect;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureE12Det;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureE34Elect;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureE34Det;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureE56Elect;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureE56Det;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureE789Elect;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureE789Det;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureLvps;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureHvps;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureFiberPlaneTop0;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureFiberPlaneTop1;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureFiberPlaneMid;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureFiberPlaneBot;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureImageInt1Side;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureImageInt1Rear;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureCamera1Elect;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureHvps1;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureImageInt2Side;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureImageInt2Rear;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureCamera2Elect;\n");
  strcat(wr_strval,"   uint8  QualityTemperatureHvps2;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE1a;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE1b;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE2ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE3ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE4ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE5ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE6ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE7ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE8ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE9ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG2ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG3ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG4ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG5ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG6ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG7ab;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE1c;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE1d;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE2cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE3cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE4cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE5cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE6cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE7cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE8cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcE9cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG2cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG3cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG4cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG5cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG6cd;\n");
  strcat(wr_strval,"   uint8  QualityPostDcG7cd;\n");
  strcat(wr_strval,"   uint8  QualityDacG2ab;\n");
  strcat(wr_strval,"   uint8  QualityDacG3ab;\n");
  strcat(wr_strval,"   uint8  QualityDacG4ab;\n");
  strcat(wr_strval,"   uint8  QualityDacG5ab;\n");
  strcat(wr_strval,"   uint8  QualityDacG6ab;\n");
  strcat(wr_strval,"   uint8  QualityDacG7ab;\n");
  strcat(wr_strval,"   uint8  QualityDacE9ab;\n");
  strcat(wr_strval,"   uint8  QualityDacG2cd;\n");
  strcat(wr_strval,"   uint8  QualityDacG3cd;\n");
  strcat(wr_strval,"   uint8  QualityDacG4cd;\n");
  strcat(wr_strval,"   uint8  QualityDacG5cd;\n");
  strcat(wr_strval,"   uint8  QualityDacG6cd;\n");
  strcat(wr_strval,"   uint8  QualityDacG7cd;\n");
  strcat(wr_strval,"   uint8  QualityDacE9cd;\n");
  strcat(wr_strval,"   uint8  QualityHeaterCcdA;\n");
  strcat(wr_strval,"   uint8  QualityHeaterCcdB;\n");
  strcat(wr_strval,"   uint8  QualityHeaterCris;\n");
  strcat(wr_strval,"   uint8  QualityStatusTmSide;\n");
  strcat(wr_strval,"   uint8  QualityStatusRefresh;\n");
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
