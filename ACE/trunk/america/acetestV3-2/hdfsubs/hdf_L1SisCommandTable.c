/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisCommandTable.h,v 1.3 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisCommandTable.h"
#include "df.h"

int32 vgrp_id_L1SisCommandTable;
static int32 vdata_id_L1SisCommandTable;

  /* 5046 is the size of L1SisCommandTable.h + 1 added line */
char Vgrp_descrp_L1SisCommandTable[5046];

/****----  init create function  ----****/

int32 init_cr_L1SisCommandTable(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1SisCommandTable();

  void print_L1SisCommandTable_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisCommandTable = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisCommandTable, "VG_L1SisCommandTable"); 
  Vsetclass(vgrp_id_L1SisCommandTable, "VG_L1SISCOMMANDTABLE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisCommandTable" )) ==FAIL) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisCommandTable(Vgrp_descrp_L1SisCommandTable);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisCommandTable, sizeof(Vgrp_descrp_L1SisCommandTable))) ==FAIL) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisCommandTable = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisCommandTable, "L1SisCommandTable");
  VSsetclass(vdata_id_L1SisCommandTable, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisCommandTable, vdata_id_L1SisCommandTable)) ==FAIL) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisCommandTable, "ClockMinorFrame0", DFNT_UINT32, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define ClockMinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "ClockMinorFrame1", DFNT_UINT32, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define ClockMinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "Second1996MinorFrame0", DFNT_UINT32, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define Second1996MinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "MicrosecondMinorFrame0", DFNT_UINT32, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define MicrosecondMinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "Second1996MinorFrame1", DFNT_UINT32, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define Second1996MinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "MicrosecondMinorFrame1", DFNT_UINT32, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define MicrosecondMinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "NumberCommandEchoes", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define NumberCommandEchoes");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "coinmsk", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define coinmsk");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "stbfon", DFNT_INT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define stbfon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "leakint", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define leakint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "hkbltim", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define hkbltim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "oadjflg", DFNT_INT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define oadjflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "vrefflg", DFNT_INT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define vrefflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "scycflg", DFNT_INT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define scycflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "mtarget", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define mtarget");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "mscale", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define mscale");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "mbounds", DFNT_UINT16, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define mbounds");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "mnav", DFNT_UINT16, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define mnav");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "aulkflg", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define aulkflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "ttpflg", DFNT_INT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define ttpflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "rnglim", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define rnglim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "claslim", DFNT_UINT16, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define claslim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "audgflg", DFNT_INT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define audgflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "audglim", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define audglim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "samplim", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define samplim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "heflg", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define heflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "hyflg", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define hyflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "hetlim", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define hetlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "hytlim", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define hytlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "htcmd", DFNT_UINT8, (4) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define htcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "stmask", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define stmask");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "ecmd", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define ecmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "hiprcmd", DFNT_UINT16, (36) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define hiprcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "sdacval", DFNT_UINT8, (26) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define sdacval");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "sdacsiz", DFNT_UINT8, (26) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define sdacsiz");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "dacval0", DFNT_UINT8, (42) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define dacval0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "dacsiz0", DFNT_UINT8, (42) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define dacsiz0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "dacval1", DFNT_UINT8, (6) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define dacval1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "dacsiz1", DFNT_UINT8, (6) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define dacsiz1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "hdisc2", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define hdisc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "hdisc0", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define hdisc0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "mdisc2", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define mdisc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "mdisc0", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define mdisc0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "adcen", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define adcen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "gdiscen", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define gdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "mdiscen", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define mdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "hdiscen", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define hdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "dirbits", DFNT_UINT8, (32) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define dirbits");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "calen", DFNT_UINT8, (64) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define calen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "compen", DFNT_UINT8, (64) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define compen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "clasmap", DFNT_UINT8, (32) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define clasmap");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "imthresh", DFNT_UINT16, (4) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define imthresh");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "imflag", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define imflag");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "im0arr", DFNT_UINT8, (20) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define im0arr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "im1arr", DFNT_UINT8, (20) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define im1arr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "strplim", DFNT_UINT8, (4) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define strplim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "mcntlim", DFNT_UINT16, (4) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define mcntlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "anglim", DFNT_UINT16, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define anglim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "cnoc1", DFNT_UINT16, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define cnoc1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "cnoc2", DFNT_UINT16, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define cnoc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "stimeid", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define stimeid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "eidmap", DFNT_UINT8, (512) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define eidmap");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "nbadstp", DFNT_UINT16, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define nbadstp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "badstrp", DFNT_UINT16, (16) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define badstrp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityCoinmsk", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityCoinmsk");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityStbfon", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityStbfon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityLeakint", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityLeakint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHkbltim", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHkbltim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityOadjflg", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityOadjflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityVrefflg", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityVrefflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityScycflg", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityScycflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityMtarget", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityMtarget");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityMscale", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityMscale");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityMbounds", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityMbounds");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityMnav", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityMnav");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityAulkflg", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityAulkflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityTtpflg", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityTtpflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityRnglim", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityRnglim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityClaslim", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityClaslim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityAudgflg", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityAudgflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityAudglim", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityAudglim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualitySamplim", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualitySamplim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHeflg", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHeflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHyflg", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHyflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHetlim", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHetlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHytlim", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHytlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHtcmd", DFNT_UINT8, (4) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHtcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityStmask", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityStmask");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityEcmd", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityEcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHiprcmd", DFNT_UINT8, (36) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHiprcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualitySdacval", DFNT_UINT8, (26) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualitySdacval");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualitySdacsiz", DFNT_UINT8, (26) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualitySdacsiz");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityDacval0", DFNT_UINT8, (42) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityDacval0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityDacsiz0", DFNT_UINT8, (42) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityDacsiz0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityDacval1", DFNT_UINT8, (6) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityDacval1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityDacsiz1", DFNT_UINT8, (6) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityDacsiz1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHdisc2", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHdisc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHdisc0", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHdisc0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityMdisc2", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityMdisc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityMdisc0", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityMdisc0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityAdcen", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityAdcen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityGdiscen", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityGdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityMdiscen", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityMdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityHdiscen", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityHdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityDirbits", DFNT_UINT8, (32) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityDirbits");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityCalen", DFNT_UINT8, (64) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityCalen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityCompen", DFNT_UINT8, (64) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityCompen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityClasmap", DFNT_UINT8, (32) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityClasmap");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityImthresh", DFNT_UINT8, (4) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityImthresh");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityImflag", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityImflag");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityIm0arr", DFNT_UINT8, (20) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityIm0arr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityIm1arr", DFNT_UINT8, (20) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityIm1arr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityStrplim", DFNT_UINT8, (4) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityStrplim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityMcntlim", DFNT_UINT8, (4) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityMcntlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityAnglim", DFNT_UINT8, (2) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityAnglim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityCnoc1", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityCnoc1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityCnoc2", DFNT_UINT8, (8) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityCnoc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityStimeid", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityStimeid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityEidmap", DFNT_UINT8, (512) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityEidmap");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityNbadstp", DFNT_UINT8, (1) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityNbadstp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandTable, "QualityBadstrp", DFNT_UINT8, (16) )) {
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSfdefine: Couldn't define QualityBadstrp");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisCommandTable,"ClockMinorFrame0, ClockMinorFrame1, Second1996MinorFrame0, MicrosecondMinorFrame0, Second1996MinorFrame1, MicrosecondMinorFrame1, NumberCommandEchoes, coinmsk, stbfon, leakint, hkbltim, oadjflg, vrefflg, scycflg, mtarget, mscale, mbounds, mnav, aulkflg, ttpflg, rnglim, claslim, audgflg, audglim, samplim, heflg, hyflg, hetlim, hytlim, htcmd, stmask, ecmd, hiprcmd, sdacval, sdacsiz, dacval0, dacsiz0, dacval1, dacsiz1, hdisc2, hdisc0, mdisc2, mdisc0, adcen, gdiscen, mdiscen, hdiscen, dirbits, calen, compen, clasmap, imthresh, imflag, im0arr, im1arr, strplim, mcntlim, anglim, cnoc1, cnoc2, stimeid, eidmap, nbadstp, badstrp, QualityCoinmsk, QualityStbfon, QualityLeakint, QualityHkbltim, QualityOadjflg, QualityVrefflg, QualityScycflg, QualityMtarget, QualityMscale, QualityMbounds, QualityMnav, QualityAulkflg, QualityTtpflg, QualityRnglim, QualityClaslim, QualityAudgflg, QualityAudglim, QualitySamplim, QualityHeflg, QualityHyflg, QualityHetlim, QualityHytlim, QualityHtcmd, QualityStmask, QualityEcmd, QualityHiprcmd, QualitySdacval, QualitySdacsiz, QualityDacval0, QualityDacsiz0, QualityDacval1, QualityDacsiz1, QualityHdisc2, QualityHdisc0, QualityMdisc2, QualityMdisc0, QualityAdcen, QualityGdiscen, QualityMdiscen, QualityHdiscen, QualityDirbits, QualityCalen, QualityCompen, QualityClasmap, QualityImthresh, QualityImflag, QualityIm0arr, QualityIm1arr, QualityStrplim, QualityMcntlim, QualityAnglim, QualityCnoc1, QualityCnoc2, QualityStimeid, QualityEidmap, QualityNbadstp, QualityBadstrp")){
    print_L1SisCommandTable_error("init_cr_L1SisCommandTable -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisCommandTable(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisCommandTable(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisCommandTable(struct L1SisCommandTable L1SisCommandTable_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1SisCommandTable_error();
void pack_L1SisCommandTable();

  odata = (uint8 *) malloc(sizeof(struct L1SisCommandTable));
  pack_L1SisCommandTable(odata, &L1SisCommandTable_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1SisCommandTable, recnum)==-1) {
		print_L1SisCommandTable_error("write_L1SisCommandTable -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisCommandTable, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisCommandTable_error("write_L1SisCommandTable -> VSwrite: Couldn't write data.");

  memset(&L1SisCommandTable_struc, 0, sizeof(struct L1SisCommandTable));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisCommandTable()
{
  VSdetach(vdata_id_L1SisCommandTable);
  Vdetach(vgrp_id_L1SisCommandTable);
}

/*----     init access function    ----*/

int32 init_acc_L1SisCommandTable(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisCommandTable_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1SisCommandTable")) <= 0 ) {
    print_L1SisCommandTable_error("init_acc_L1SisCommandTable -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisCommandTable = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisCommandTable_error("init_acc_L1SisCommandTable -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisCommandTable, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisCommandTable,"ClockMinorFrame0, ClockMinorFrame1, Second1996MinorFrame0, MicrosecondMinorFrame0, Second1996MinorFrame1, MicrosecondMinorFrame1, NumberCommandEchoes, coinmsk, stbfon, leakint, hkbltim, oadjflg, vrefflg, scycflg, mtarget, mscale, mbounds, mnav, aulkflg, ttpflg, rnglim, claslim, audgflg, audglim, samplim, heflg, hyflg, hetlim, hytlim, htcmd, stmask, ecmd, hiprcmd, sdacval, sdacsiz, dacval0, dacsiz0, dacval1, dacsiz1, hdisc2, hdisc0, mdisc2, mdisc0, adcen, gdiscen, mdiscen, hdiscen, dirbits, calen, compen, clasmap, imthresh, imflag, im0arr, im1arr, strplim, mcntlim, anglim, cnoc1, cnoc2, stimeid, eidmap, nbadstp, badstrp, QualityCoinmsk, QualityStbfon, QualityLeakint, QualityHkbltim, QualityOadjflg, QualityVrefflg, QualityScycflg, QualityMtarget, QualityMscale, QualityMbounds, QualityMnav, QualityAulkflg, QualityTtpflg, QualityRnglim, QualityClaslim, QualityAudgflg, QualityAudglim, QualitySamplim, QualityHeflg, QualityHyflg, QualityHetlim, QualityHytlim, QualityHtcmd, QualityStmask, QualityEcmd, QualityHiprcmd, QualitySdacval, QualitySdacsiz, QualityDacval0, QualityDacsiz0, QualityDacval1, QualityDacsiz1, QualityHdisc2, QualityHdisc0, QualityMdisc2, QualityMdisc0, QualityAdcen, QualityGdiscen, QualityMdiscen, QualityHdiscen, QualityDirbits, QualityCalen, QualityCompen, QualityClasmap, QualityImthresh, QualityImflag, QualityIm0arr, QualityIm1arr, QualityStrplim, QualityMcntlim, QualityAnglim, QualityCnoc1, QualityCnoc2, QualityStimeid, QualityEidmap, QualityNbadstp, QualityBadstrp")) {
      print_L1SisCommandTable_error("init_acc_L1SisCommandTable -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisCommandTable(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisCommandTable(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisCommandTable(struct L1SisCommandTable *L1SisCommandTable_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisCommandTable_error();
void unpack_L1SisCommandTable();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1SisCommandTable));
  VSinquire(vdata_id_L1SisCommandTable, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisCommandTable, recnum_rd)==FAIL) {
          print_L1SisCommandTable_error("read_L1SisCommandTable -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1SisCommandTable, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisCommandTable_error("read_L1SisCommandTable -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisCommandTable(odata, L1SisCommandTable_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisCommandTable()
{
  VSdetach(vdata_id_L1SisCommandTable);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisCommandTable(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisCommandTable_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisCommandTable" )) ==FAIL)
    print_L1SisCommandTable_error("rd_Vgrp_L1SisCommandTable -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisCommandTable_error("rd_Vgrp_L1SisCommandTable -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisCommandTable_error("rd_Vgrp_L1SisCommandTable -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisCommandTable_error("rd_Vgrp_L1SisCommandTable -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisCommandTable, HDstrlen(Vgrp_descrp_L1SisCommandTable)) ==FAIL)
    print_L1SisCommandTable_error("rd_Vgrp_L1SisCommandTable -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisCommandTable);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisCommandTable_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisCommandTable.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisCommandTable(uint8 *data, struct L1SisCommandTable *L1SisCommandTable_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisCommandTable_ptr->ClockMinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->ClockMinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->Second1996MinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->MicrosecondMinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->Second1996MinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->MicrosecondMinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->NumberCommandEchoes, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->coinmsk, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->stbfon, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->leakint, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->hkbltim[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->oadjflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->vrefflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->scycflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->mtarget, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->mscale, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->mbounds[0], ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->mnav[0], ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->aulkflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->ttpflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->rnglim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->claslim[0], ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->audgflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->audglim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->samplim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->heflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->hyflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->hetlim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->hytlim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->htcmd[0], ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(data+ptr, &L1SisCommandTable_ptr->stmask, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->ecmd[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->hiprcmd[0], ((2)*(36)) );
   ptr+= ((2)*(36));
   memcpy(data+ptr, &L1SisCommandTable_ptr->sdacval[0], ((1)*(26)) );
   ptr+= ((1)*(26));
   memcpy(data+ptr, &L1SisCommandTable_ptr->sdacsiz[0], ((1)*(26)) );
   ptr+= ((1)*(26));
   memcpy(data+ptr, &L1SisCommandTable_ptr->dacval0[0], ((1)*(42)) );
   ptr+= ((1)*(42));
   memcpy(data+ptr, &L1SisCommandTable_ptr->dacsiz0[0], ((1)*(42)) );
   ptr+= ((1)*(42));
   memcpy(data+ptr, &L1SisCommandTable_ptr->dacval1[0], ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(data+ptr, &L1SisCommandTable_ptr->dacsiz1[0], ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(data+ptr, &L1SisCommandTable_ptr->hdisc2[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->hdisc0[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->mdisc2[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->mdisc0[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->adcen[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->gdiscen[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->mdiscen[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->hdiscen[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->dirbits[0], ((1)*(32)) );
   ptr+= ((1)*(32));
   memcpy(data+ptr, &L1SisCommandTable_ptr->calen[0], ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(data+ptr, &L1SisCommandTable_ptr->compen[0], ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(data+ptr, &L1SisCommandTable_ptr->clasmap[0], ((1)*(32)) );
   ptr+= ((1)*(32));
   memcpy(data+ptr, &L1SisCommandTable_ptr->imthresh[0], ((2)*(4)) );
   ptr+= ((2)*(4));
   memcpy(data+ptr, &L1SisCommandTable_ptr->imflag[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->im0arr[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &L1SisCommandTable_ptr->im1arr[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &L1SisCommandTable_ptr->strplim[0], ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(data+ptr, &L1SisCommandTable_ptr->mcntlim[0], ((2)*(4)) );
   ptr+= ((2)*(4));
   memcpy(data+ptr, &L1SisCommandTable_ptr->anglim[0], ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->cnoc1[0], ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->cnoc2[0], ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->stimeid, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->eidmap[0], ((1)*(512)) );
   ptr+= ((1)*(512));
   memcpy(data+ptr, &L1SisCommandTable_ptr->nbadstp, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->badstrp[0], ((2)*(16)) );
   ptr+= ((2)*(16));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityCoinmsk, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityStbfon, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityLeakint, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHkbltim[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityOadjflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityVrefflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityScycflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityMtarget, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityMscale, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityMbounds[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityMnav[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityAulkflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityTtpflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityRnglim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityClaslim[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityAudgflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityAudglim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualitySamplim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHeflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHyflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHetlim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHytlim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHtcmd[0], ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityStmask, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityEcmd[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHiprcmd[0], ((1)*(36)) );
   ptr+= ((1)*(36));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualitySdacval[0], ((1)*(26)) );
   ptr+= ((1)*(26));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualitySdacsiz[0], ((1)*(26)) );
   ptr+= ((1)*(26));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityDacval0[0], ((1)*(42)) );
   ptr+= ((1)*(42));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityDacsiz0[0], ((1)*(42)) );
   ptr+= ((1)*(42));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityDacval1[0], ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityDacsiz1[0], ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHdisc2[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHdisc0[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityMdisc2[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityMdisc0[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityAdcen[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityGdiscen[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityMdiscen[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityHdiscen[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityDirbits[0], ((1)*(32)) );
   ptr+= ((1)*(32));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityCalen[0], ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityCompen[0], ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityClasmap[0], ((1)*(32)) );
   ptr+= ((1)*(32));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityImthresh[0], ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityImflag[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityIm0arr[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityIm1arr[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityStrplim[0], ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityMcntlim[0], ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityAnglim[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityCnoc1[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityCnoc2[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityStimeid, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityEidmap[0], ((1)*(512)) );
   ptr+= ((1)*(512));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityNbadstp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandTable_ptr->QualityBadstrp[0], ((1)*(16)) );
   ptr+= ((1)*(16));
}

/*----   unpack function    ----*/

void unpack_L1SisCommandTable(uint8 *data, struct L1SisCommandTable *L1SisCommandTable_ptr)
{
int32 ptr=0;

   memcpy(&L1SisCommandTable_ptr->ClockMinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandTable_ptr->ClockMinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandTable_ptr->Second1996MinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandTable_ptr->MicrosecondMinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandTable_ptr->Second1996MinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandTable_ptr->MicrosecondMinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandTable_ptr->NumberCommandEchoes, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->coinmsk, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->stbfon, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->leakint, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->hkbltim[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->oadjflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->vrefflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->scycflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->mtarget, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->mscale, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->mbounds[0], data+ptr,  ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(&L1SisCommandTable_ptr->mnav[0], data+ptr,  ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(&L1SisCommandTable_ptr->aulkflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->ttpflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->rnglim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->claslim[0], data+ptr,  ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(&L1SisCommandTable_ptr->audgflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->audglim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->samplim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->heflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->hyflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->hetlim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->hytlim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->htcmd[0], data+ptr,  ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(&L1SisCommandTable_ptr->stmask, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->ecmd[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->hiprcmd[0], data+ptr,  ((2)*(36)) );
   ptr+= ((2)*(36));
   memcpy(&L1SisCommandTable_ptr->sdacval[0], data+ptr,  ((1)*(26)) );
   ptr+= ((1)*(26));
   memcpy(&L1SisCommandTable_ptr->sdacsiz[0], data+ptr,  ((1)*(26)) );
   ptr+= ((1)*(26));
   memcpy(&L1SisCommandTable_ptr->dacval0[0], data+ptr,  ((1)*(42)) );
   ptr+= ((1)*(42));
   memcpy(&L1SisCommandTable_ptr->dacsiz0[0], data+ptr,  ((1)*(42)) );
   ptr+= ((1)*(42));
   memcpy(&L1SisCommandTable_ptr->dacval1[0], data+ptr,  ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(&L1SisCommandTable_ptr->dacsiz1[0], data+ptr,  ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(&L1SisCommandTable_ptr->hdisc2[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->hdisc0[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->mdisc2[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->mdisc0[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->adcen[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->gdiscen[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->mdiscen[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->hdiscen[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->dirbits[0], data+ptr,  ((1)*(32)) );
   ptr+= ((1)*(32));
   memcpy(&L1SisCommandTable_ptr->calen[0], data+ptr,  ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(&L1SisCommandTable_ptr->compen[0], data+ptr,  ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(&L1SisCommandTable_ptr->clasmap[0], data+ptr,  ((1)*(32)) );
   ptr+= ((1)*(32));
   memcpy(&L1SisCommandTable_ptr->imthresh[0], data+ptr,  ((2)*(4)) );
   ptr+= ((2)*(4));
   memcpy(&L1SisCommandTable_ptr->imflag[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->im0arr[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&L1SisCommandTable_ptr->im1arr[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&L1SisCommandTable_ptr->strplim[0], data+ptr,  ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(&L1SisCommandTable_ptr->mcntlim[0], data+ptr,  ((2)*(4)) );
   ptr+= ((2)*(4));
   memcpy(&L1SisCommandTable_ptr->anglim[0], data+ptr,  ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(&L1SisCommandTable_ptr->cnoc1[0], data+ptr,  ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(&L1SisCommandTable_ptr->cnoc2[0], data+ptr,  ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(&L1SisCommandTable_ptr->stimeid, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->eidmap[0], data+ptr,  ((1)*(512)) );
   ptr+= ((1)*(512));
   memcpy(&L1SisCommandTable_ptr->nbadstp, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisCommandTable_ptr->badstrp[0], data+ptr,  ((2)*(16)) );
   ptr+= ((2)*(16));
   memcpy(&L1SisCommandTable_ptr->QualityCoinmsk, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityStbfon, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityLeakint, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityHkbltim[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->QualityOadjflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityVrefflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityScycflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityMtarget, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityMscale, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityMbounds[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->QualityMnav[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->QualityAulkflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityTtpflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityRnglim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityClaslim[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->QualityAudgflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityAudglim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualitySamplim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityHeflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityHyflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityHetlim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityHytlim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityHtcmd[0], data+ptr,  ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(&L1SisCommandTable_ptr->QualityStmask, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityEcmd[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->QualityHiprcmd[0], data+ptr,  ((1)*(36)) );
   ptr+= ((1)*(36));
   memcpy(&L1SisCommandTable_ptr->QualitySdacval[0], data+ptr,  ((1)*(26)) );
   ptr+= ((1)*(26));
   memcpy(&L1SisCommandTable_ptr->QualitySdacsiz[0], data+ptr,  ((1)*(26)) );
   ptr+= ((1)*(26));
   memcpy(&L1SisCommandTable_ptr->QualityDacval0[0], data+ptr,  ((1)*(42)) );
   ptr+= ((1)*(42));
   memcpy(&L1SisCommandTable_ptr->QualityDacsiz0[0], data+ptr,  ((1)*(42)) );
   ptr+= ((1)*(42));
   memcpy(&L1SisCommandTable_ptr->QualityDacval1[0], data+ptr,  ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(&L1SisCommandTable_ptr->QualityDacsiz1[0], data+ptr,  ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(&L1SisCommandTable_ptr->QualityHdisc2[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityHdisc0[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityMdisc2[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityMdisc0[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityAdcen[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityGdiscen[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityMdiscen[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityHdiscen[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityDirbits[0], data+ptr,  ((1)*(32)) );
   ptr+= ((1)*(32));
   memcpy(&L1SisCommandTable_ptr->QualityCalen[0], data+ptr,  ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(&L1SisCommandTable_ptr->QualityCompen[0], data+ptr,  ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(&L1SisCommandTable_ptr->QualityClasmap[0], data+ptr,  ((1)*(32)) );
   ptr+= ((1)*(32));
   memcpy(&L1SisCommandTable_ptr->QualityImthresh[0], data+ptr,  ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(&L1SisCommandTable_ptr->QualityImflag[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->QualityIm0arr[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&L1SisCommandTable_ptr->QualityIm1arr[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&L1SisCommandTable_ptr->QualityStrplim[0], data+ptr,  ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(&L1SisCommandTable_ptr->QualityMcntlim[0], data+ptr,  ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(&L1SisCommandTable_ptr->QualityAnglim[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1SisCommandTable_ptr->QualityCnoc1[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityCnoc2[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1SisCommandTable_ptr->QualityStimeid, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityEidmap[0], data+ptr,  ((1)*(512)) );
   ptr+= ((1)*(512));
   memcpy(&L1SisCommandTable_ptr->QualityNbadstp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandTable_ptr->QualityBadstrp[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
}
int32 get_vgrp_id_L1SisCommandTable() {return(vgrp_id_L1SisCommandTable);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisCommandTable(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisCommandTable.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisCommandTable'.\n\n");
  strcat(wr_strval,"/* Id: L1SisCommandTable.h,v 1.3 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisCommandTable.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisCommandTable\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame0;\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame1;\n");
  strcat(wr_strval,"   uint32 Second1996MinorFrame0;\n");
  strcat(wr_strval,"   uint32 MicrosecondMinorFrame0;\n");
  strcat(wr_strval,"   uint32 Second1996MinorFrame1;\n");
  strcat(wr_strval,"   uint32 MicrosecondMinorFrame1;\n");
  strcat(wr_strval,"   uint16 NumberCommandEchoes;\n");
  strcat(wr_strval,"   uint16 coinmsk;\n");
  strcat(wr_strval,"   int16  stbfon;\n");
  strcat(wr_strval,"   uint16 leakint;\n");
  strcat(wr_strval,"   uint8  hkbltim[2];\n");
  strcat(wr_strval,"   int16  oadjflg;\n");
  strcat(wr_strval,"   int16  vrefflg;\n");
  strcat(wr_strval,"   int16  scycflg;\n");
  strcat(wr_strval,"   uint16 mtarget;\n");
  strcat(wr_strval,"   uint16 mscale;\n");
  strcat(wr_strval,"   uint16 mbounds[2];\n");
  strcat(wr_strval,"   uint16 mnav[2];\n");
  strcat(wr_strval,"   uint16 aulkflg;\n");
  strcat(wr_strval,"   int16  ttpflg;\n");
  strcat(wr_strval,"   uint16 rnglim;\n");
  strcat(wr_strval,"   uint16 claslim[2];\n");
  strcat(wr_strval,"   int16  audgflg;\n");
  strcat(wr_strval,"   uint16 audglim;\n");
  strcat(wr_strval,"   uint16 samplim;\n");
  strcat(wr_strval,"   uint16 heflg;\n");
  strcat(wr_strval,"   uint16 hyflg;\n");
  strcat(wr_strval,"   uint16 hetlim;\n");
  strcat(wr_strval,"   uint16 hytlim;\n");
  strcat(wr_strval,"   uint8  htcmd[4];\n");
  strcat(wr_strval,"   uint16 stmask;\n");
  strcat(wr_strval,"   uint8  ecmd[2];\n");
  strcat(wr_strval,"   uint16 hiprcmd[36];\n");
  strcat(wr_strval,"   uint8  sdacval[26];\n");
  strcat(wr_strval,"   uint8  sdacsiz[26];\n");
  strcat(wr_strval,"   uint8  dacval0[42];\n");
  strcat(wr_strval,"   uint8  dacsiz0[42];\n");
  strcat(wr_strval,"   uint8  dacval1[6];\n");
  strcat(wr_strval,"   uint8  dacsiz1[6];\n");
  strcat(wr_strval,"   uint8  hdisc2[8];\n");
  strcat(wr_strval,"   uint8  hdisc0[8];\n");
  strcat(wr_strval,"   uint8  mdisc2[8];\n");
  strcat(wr_strval,"   uint8  mdisc0[8];\n");
  strcat(wr_strval,"   uint8  adcen[8];\n");
  strcat(wr_strval,"   uint8  gdiscen[8];\n");
  strcat(wr_strval,"   uint8  mdiscen[8];\n");
  strcat(wr_strval,"   uint8  hdiscen[8];\n");
  strcat(wr_strval,"   uint8  dirbits[32];\n");
  strcat(wr_strval,"   uint8  calen[64];\n");
  strcat(wr_strval,"   uint8  compen[64];\n");
  strcat(wr_strval,"   uint8  clasmap[32];\n");
  strcat(wr_strval,"   uint16 imthresh[4];\n");
  strcat(wr_strval,"   uint8  imflag[2];\n");
  strcat(wr_strval,"   uint8  im0arr[20];\n");
  strcat(wr_strval,"   uint8  im1arr[20];\n");
  strcat(wr_strval,"   uint8  strplim[4];\n");
  strcat(wr_strval,"   uint16 mcntlim[4];\n");
  strcat(wr_strval,"   uint16 anglim[2];\n");
  strcat(wr_strval,"   uint16 cnoc1[8];\n");
  strcat(wr_strval,"   uint16 cnoc2[8];\n");
  strcat(wr_strval,"   uint16 stimeid;\n");
  strcat(wr_strval,"   uint8  eidmap[512];\n");
  strcat(wr_strval,"   uint16 nbadstp;\n");
  strcat(wr_strval,"   uint16 badstrp[16];\n");
  strcat(wr_strval,"   uint8  QualityCoinmsk;\n");
  strcat(wr_strval,"   uint8  QualityStbfon;\n");
  strcat(wr_strval,"   uint8  QualityLeakint;\n");
  strcat(wr_strval,"   uint8  QualityHkbltim[2];\n");
  strcat(wr_strval,"   uint8  QualityOadjflg;\n");
  strcat(wr_strval,"   uint8  QualityVrefflg;\n");
  strcat(wr_strval,"   uint8  QualityScycflg;\n");
  strcat(wr_strval,"   uint8  QualityMtarget;\n");
  strcat(wr_strval,"   uint8  QualityMscale;\n");
  strcat(wr_strval,"   uint8  QualityMbounds[2];\n");
  strcat(wr_strval,"   uint8  QualityMnav[2];\n");
  strcat(wr_strval,"   uint8  QualityAulkflg;\n");
  strcat(wr_strval,"   uint8  QualityTtpflg;\n");
  strcat(wr_strval,"   uint8  QualityRnglim;\n");
  strcat(wr_strval,"   uint8  QualityClaslim[2];\n");
  strcat(wr_strval,"   uint8  QualityAudgflg;\n");
  strcat(wr_strval,"   uint8  QualityAudglim;\n");
  strcat(wr_strval,"   uint8  QualitySamplim;\n");
  strcat(wr_strval,"   uint8  QualityHeflg;\n");
  strcat(wr_strval,"   uint8  QualityHyflg;\n");
  strcat(wr_strval,"   uint8  QualityHetlim;\n");
  strcat(wr_strval,"   uint8  QualityHytlim;\n");
  strcat(wr_strval,"   uint8  QualityHtcmd[4];\n");
  strcat(wr_strval,"   uint8  QualityStmask;\n");
  strcat(wr_strval,"   uint8  QualityEcmd[2];\n");
  strcat(wr_strval,"   uint8  QualityHiprcmd[36];\n");
  strcat(wr_strval,"   uint8  QualitySdacval[26];\n");
  strcat(wr_strval,"   uint8  QualitySdacsiz[26];\n");
  strcat(wr_strval,"   uint8  QualityDacval0[42];\n");
  strcat(wr_strval,"   uint8  QualityDacsiz0[42];\n");
  strcat(wr_strval,"   uint8  QualityDacval1[6];\n");
  strcat(wr_strval,"   uint8  QualityDacsiz1[6];\n");
  strcat(wr_strval,"   uint8  QualityHdisc2[8];\n");
  strcat(wr_strval,"   uint8  QualityHdisc0[8];\n");
  strcat(wr_strval,"   uint8  QualityMdisc2[8];\n");
  strcat(wr_strval,"   uint8  QualityMdisc0[8];\n");
  strcat(wr_strval,"   uint8  QualityAdcen[8];\n");
  strcat(wr_strval,"   uint8  QualityGdiscen[8];\n");
  strcat(wr_strval,"   uint8  QualityMdiscen[8];\n");
  strcat(wr_strval,"   uint8  QualityHdiscen[8];\n");
  strcat(wr_strval,"   uint8  QualityDirbits[32];\n");
  strcat(wr_strval,"   uint8  QualityCalen[64];\n");
  strcat(wr_strval,"   uint8  QualityCompen[64];\n");
  strcat(wr_strval,"   uint8  QualityClasmap[32];\n");
  strcat(wr_strval,"   uint8  QualityImthresh[4];\n");
  strcat(wr_strval,"   uint8  QualityImflag[2];\n");
  strcat(wr_strval,"   uint8  QualityIm0arr[20];\n");
  strcat(wr_strval,"   uint8  QualityIm1arr[20];\n");
  strcat(wr_strval,"   uint8  QualityStrplim[4];\n");
  strcat(wr_strval,"   uint8  QualityMcntlim[4];\n");
  strcat(wr_strval,"   uint8  QualityAnglim[2];\n");
  strcat(wr_strval,"   uint8  QualityCnoc1[8];\n");
  strcat(wr_strval,"   uint8  QualityCnoc2[8];\n");
  strcat(wr_strval,"   uint8  QualityStimeid;\n");
  strcat(wr_strval,"   uint8  QualityEidmap[512];\n");
  strcat(wr_strval,"   uint8  QualityNbadstp;\n");
  strcat(wr_strval,"   uint8  QualityBadstrp[16];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockMinorFrame0 = S/C clock of the start of the instrument    */\n");
  strcat(wr_strval,"/*                       cycle that contains the first byte of the   */\n");
  strcat(wr_strval,"/*                       command table                               */\n");
  strcat(wr_strval,"/*    ClockMinorFrame1 = S/C clock of the end of the instrument      */\n");
  strcat(wr_strval,"/*                       cycle that contains the last byte of the    */\n");
  strcat(wr_strval,"/*                       command table                               */\n");
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
