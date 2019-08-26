/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1CrisCommandTable.h,v 1.4 1998/05/08 23:15:29 rgr Exp  */

#include "L1CrisCommandTable.h"
#include "df.h"

int32 vgrp_id_L1CrisCommandTable;
static int32 vdata_id_L1CrisCommandTable;

  /* 5036 is the size of L1CrisCommandTable.h + 1 added line */
char Vgrp_descrp_L1CrisCommandTable[5036];

/****----  init create function  ----****/

int32 init_cr_L1CrisCommandTable(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1CrisCommandTable();

  void print_L1CrisCommandTable_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1CrisCommandTable = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1CrisCommandTable, "VG_L1CrisCommandTable"); 
  Vsetclass(vgrp_id_L1CrisCommandTable, "VG_L1CRISCOMMANDTABLE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1CrisCommandTable" )) ==FAIL) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1CrisCommandTable(Vgrp_descrp_L1CrisCommandTable);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1CrisCommandTable, sizeof(Vgrp_descrp_L1CrisCommandTable))) ==FAIL) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1CrisCommandTable = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1CrisCommandTable, "L1CrisCommandTable");
  VSsetclass(vdata_id_L1CrisCommandTable, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1CrisCommandTable, vdata_id_L1CrisCommandTable)) ==FAIL) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1CrisCommandTable, "ClockMinorFrame0", DFNT_UINT32, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define ClockMinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "ClockMinorFrame1", DFNT_UINT32, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define ClockMinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "Second1996MinorFrame0", DFNT_UINT32, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define Second1996MinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "MicrosecondMinorFrame0", DFNT_UINT32, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define MicrosecondMinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "Second1996MinorFrame1", DFNT_UINT32, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define Second1996MinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "MicrosecondMinorFrame1", DFNT_UINT32, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define MicrosecondMinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "NumberCommandEchoes", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define NumberCommandEchoes");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "ecmd", DFNT_UINT8, (6) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define ecmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "phadisc", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define phadisc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "audgflg", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define audgflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "audglim", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define audglim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "valcflg", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define valcflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "samplim", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define samplim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "heflg", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define heflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "hyflg", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define hyflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "preoflg", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define preoflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "hetlim", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define hetlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "hytlim", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define hytlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "htcmd", DFNT_UINT16, (8) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define htcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "rcmd", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define rcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "qctime", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define qctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "ledtime", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define ledtime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "sfmisc", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define sfmisc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "camsel", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define camsel");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "iilima", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define iilima");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "iilimb", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define iilimb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "iilims", DFNT_UINT16, (4) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define iilims");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "lsarr", DFNT_INT16, (20) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define lsarr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "loarr", DFNT_INT16, (20) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define loarr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "laymax", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define laymax");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "remmax", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define remmax");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "b_xoff", DFNT_UINT8, (2) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define b_xoff");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "rngmsk", DFNT_UINT16, (2) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define rngmsk");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "bparams", DFNT_UINT8, (20) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define bparams");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "twotelen", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define twotelen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "gphaen", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define gphaen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "stbfon", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define stbfon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "ncenbox", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define ncenbox");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "b_cenbox", DFNT_UINT16, (64) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define b_cenbox");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "iilim", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define iilim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "iignct", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define iignct");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "iignrf", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define iignrf");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "sftdisc", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define sftdisc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "sftrig0", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define sftrig0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "sftrig1", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define sftrig1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "cdscoff", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define cdscoff");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "tdscoff", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define tdscoff");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "srgbits", DFNT_UINT16, (2) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define srgbits");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "dacvals", DFNT_UINT8, (52) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define dacvals");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "dacsize", DFNT_UINT8, (52) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define dacsize");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "hdisc2", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define hdisc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "hdisc1", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define hdisc1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "hdisc0", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define hdisc0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "mdisc2", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define mdisc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "mdisc1", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define mdisc1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "mdisc0", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define mdisc0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "adcen", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define adcen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "gdiscen", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define gdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "mdiscen", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define mdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "hdiscen", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define hdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "cnoc1", DFNT_UINT16, (7) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define cnoc1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "cnoc2", DFNT_UINT16, (7) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define cnoc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "ihiprr0", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define ihiprr0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "ihiprr1", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define ihiprr1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "stimeid", DFNT_UINT16, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define stimeid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "eidmap", DFNT_UINT8, (256) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define eidmap");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityEcmd", DFNT_UINT8, (6) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityEcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityPhadisc", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityPhadisc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityAudgflg", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityAudgflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityAudglim", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityAudglim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityValcflg", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityValcflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualitySamplim", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualitySamplim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHeflg", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHeflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHyflg", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHyflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityPreoflg", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityPreoflg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHetlim", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHetlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHytlim", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHytlim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHtcmd", DFNT_UINT8, (8) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHtcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityRcmd", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityRcmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityQctime", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityQctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityLedtime", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityLedtime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualitySfmisc", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualitySfmisc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityCamsel", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityCamsel");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityIilima", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityIilima");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityIilimb", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityIilimb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityIilims", DFNT_UINT8, (4) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityIilims");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityLsarr", DFNT_UINT8, (20) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityLsarr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityLoarr", DFNT_UINT8, (20) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityLoarr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityLaymax", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityLaymax");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityRemmax", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityRemmax");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityB_xoff", DFNT_UINT8, (2) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityB_xoff");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityRngmsk", DFNT_UINT8, (2) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityRngmsk");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityBparams", DFNT_UINT8, (20) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityBparams");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityTwotelen", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityTwotelen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityGphaen", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityGphaen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityStbfon", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityStbfon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityNcenbox", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityNcenbox");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityB_cenbox", DFNT_UINT8, (64) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityB_cenbox");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityIilim", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityIilim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityIignct", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityIignct");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityIignrf", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityIignrf");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualitySftdisc", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualitySftdisc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualitySftrig0", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualitySftrig0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualitySftrig1", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualitySftrig1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityCdscoff", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityCdscoff");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityTdscoff", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityTdscoff");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualitySrgbits", DFNT_UINT8, (2) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualitySrgbits");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityDacvals", DFNT_UINT8, (52) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityDacvals");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityDacsize", DFNT_UINT8, (52) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityDacsize");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHdisc2", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHdisc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHdisc1", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHdisc1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHdisc0", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHdisc0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityMdisc2", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityMdisc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityMdisc1", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityMdisc1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityMdisc0", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityMdisc0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityAdcen", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityAdcen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityGdiscen", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityGdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityMdiscen", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityMdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityHdiscen", DFNT_UINT8, (12) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityHdiscen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityCnoc1", DFNT_UINT8, (7) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityCnoc1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityCnoc2", DFNT_UINT8, (7) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityCnoc2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityIhiprr0", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityIhiprr0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityIhiprr1", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityIhiprr1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityStimeid", DFNT_UINT8, (1) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityStimeid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandTable, "QualityEidmap", DFNT_UINT8, (256) )) {
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSfdefine: Couldn't define QualityEidmap");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1CrisCommandTable,"ClockMinorFrame0, ClockMinorFrame1, Second1996MinorFrame0, MicrosecondMinorFrame0, Second1996MinorFrame1, MicrosecondMinorFrame1, NumberCommandEchoes, ecmd, phadisc, audgflg, audglim, valcflg, samplim, heflg, hyflg, preoflg, hetlim, hytlim, htcmd, rcmd, qctime, ledtime, sfmisc, camsel, iilima, iilimb, iilims, lsarr, loarr, laymax, remmax, b_xoff, rngmsk, bparams, twotelen, gphaen, stbfon, ncenbox, b_cenbox, iilim, iignct, iignrf, sftdisc, sftrig0, sftrig1, cdscoff, tdscoff, srgbits, dacvals, dacsize, hdisc2, hdisc1, hdisc0, mdisc2, mdisc1, mdisc0, adcen, gdiscen, mdiscen, hdiscen, cnoc1, cnoc2, ihiprr0, ihiprr1, stimeid, eidmap, QualityEcmd, QualityPhadisc, QualityAudgflg, QualityAudglim, QualityValcflg, QualitySamplim, QualityHeflg, QualityHyflg, QualityPreoflg, QualityHetlim, QualityHytlim, QualityHtcmd, QualityRcmd, QualityQctime, QualityLedtime, QualitySfmisc, QualityCamsel, QualityIilima, QualityIilimb, QualityIilims, QualityLsarr, QualityLoarr, QualityLaymax, QualityRemmax, QualityB_xoff, QualityRngmsk, QualityBparams, QualityTwotelen, QualityGphaen, QualityStbfon, QualityNcenbox, QualityB_cenbox, QualityIilim, QualityIignct, QualityIignrf, QualitySftdisc, QualitySftrig0, QualitySftrig1, QualityCdscoff, QualityTdscoff, QualitySrgbits, QualityDacvals, QualityDacsize, QualityHdisc2, QualityHdisc1, QualityHdisc0, QualityMdisc2, QualityMdisc1, QualityMdisc0, QualityAdcen, QualityGdiscen, QualityMdiscen, QualityHdiscen, QualityCnoc1, QualityCnoc2, QualityIhiprr0, QualityIhiprr1, QualityStimeid, QualityEidmap")){
    print_L1CrisCommandTable_error("init_cr_L1CrisCommandTable -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1CrisCommandTable(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1CrisCommandTable(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1CrisCommandTable(struct L1CrisCommandTable L1CrisCommandTable_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1CrisCommandTable_error();
void pack_L1CrisCommandTable();

  odata = (uint8 *) malloc(sizeof(struct L1CrisCommandTable));
  pack_L1CrisCommandTable(odata, &L1CrisCommandTable_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1CrisCommandTable, recnum)==-1) {
		print_L1CrisCommandTable_error("write_L1CrisCommandTable -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1CrisCommandTable, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1CrisCommandTable_error("write_L1CrisCommandTable -> VSwrite: Couldn't write data.");

  memset(&L1CrisCommandTable_struc, 0, sizeof(struct L1CrisCommandTable));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1CrisCommandTable()
{
  VSdetach(vdata_id_L1CrisCommandTable);
  Vdetach(vgrp_id_L1CrisCommandTable);
}

/*----     init access function    ----*/

int32 init_acc_L1CrisCommandTable(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1CrisCommandTable_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1CrisCommandTable")) <= 0 ) {
    print_L1CrisCommandTable_error("init_acc_L1CrisCommandTable -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1CrisCommandTable = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1CrisCommandTable_error("init_acc_L1CrisCommandTable -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1CrisCommandTable, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1CrisCommandTable,"ClockMinorFrame0, ClockMinorFrame1, Second1996MinorFrame0, MicrosecondMinorFrame0, Second1996MinorFrame1, MicrosecondMinorFrame1, NumberCommandEchoes, ecmd, phadisc, audgflg, audglim, valcflg, samplim, heflg, hyflg, preoflg, hetlim, hytlim, htcmd, rcmd, qctime, ledtime, sfmisc, camsel, iilima, iilimb, iilims, lsarr, loarr, laymax, remmax, b_xoff, rngmsk, bparams, twotelen, gphaen, stbfon, ncenbox, b_cenbox, iilim, iignct, iignrf, sftdisc, sftrig0, sftrig1, cdscoff, tdscoff, srgbits, dacvals, dacsize, hdisc2, hdisc1, hdisc0, mdisc2, mdisc1, mdisc0, adcen, gdiscen, mdiscen, hdiscen, cnoc1, cnoc2, ihiprr0, ihiprr1, stimeid, eidmap, QualityEcmd, QualityPhadisc, QualityAudgflg, QualityAudglim, QualityValcflg, QualitySamplim, QualityHeflg, QualityHyflg, QualityPreoflg, QualityHetlim, QualityHytlim, QualityHtcmd, QualityRcmd, QualityQctime, QualityLedtime, QualitySfmisc, QualityCamsel, QualityIilima, QualityIilimb, QualityIilims, QualityLsarr, QualityLoarr, QualityLaymax, QualityRemmax, QualityB_xoff, QualityRngmsk, QualityBparams, QualityTwotelen, QualityGphaen, QualityStbfon, QualityNcenbox, QualityB_cenbox, QualityIilim, QualityIignct, QualityIignrf, QualitySftdisc, QualitySftrig0, QualitySftrig1, QualityCdscoff, QualityTdscoff, QualitySrgbits, QualityDacvals, QualityDacsize, QualityHdisc2, QualityHdisc1, QualityHdisc0, QualityMdisc2, QualityMdisc1, QualityMdisc0, QualityAdcen, QualityGdiscen, QualityMdiscen, QualityHdiscen, QualityCnoc1, QualityCnoc2, QualityIhiprr0, QualityIhiprr1, QualityStimeid, QualityEidmap")) {
      print_L1CrisCommandTable_error("init_acc_L1CrisCommandTable -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1CrisCommandTable(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1CrisCommandTable(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1CrisCommandTable(struct L1CrisCommandTable *L1CrisCommandTable_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1CrisCommandTable_error();
void unpack_L1CrisCommandTable();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1CrisCommandTable));
  VSinquire(vdata_id_L1CrisCommandTable, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1CrisCommandTable, recnum_rd)==FAIL) {
          print_L1CrisCommandTable_error("read_L1CrisCommandTable -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1CrisCommandTable, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1CrisCommandTable_error("read_L1CrisCommandTable -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1CrisCommandTable(odata, L1CrisCommandTable_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1CrisCommandTable()
{
  VSdetach(vdata_id_L1CrisCommandTable);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1CrisCommandTable(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1CrisCommandTable_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1CrisCommandTable" )) ==FAIL)
    print_L1CrisCommandTable_error("rd_Vgrp_L1CrisCommandTable -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1CrisCommandTable_error("rd_Vgrp_L1CrisCommandTable -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1CrisCommandTable_error("rd_Vgrp_L1CrisCommandTable -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1CrisCommandTable_error("rd_Vgrp_L1CrisCommandTable -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1CrisCommandTable, HDstrlen(Vgrp_descrp_L1CrisCommandTable)) ==FAIL)
    print_L1CrisCommandTable_error("rd_Vgrp_L1CrisCommandTable -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1CrisCommandTable);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1CrisCommandTable_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1CrisCommandTable.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1CrisCommandTable(uint8 *data, struct L1CrisCommandTable *L1CrisCommandTable_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1CrisCommandTable_ptr->ClockMinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->ClockMinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->Second1996MinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->MicrosecondMinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->Second1996MinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->MicrosecondMinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->NumberCommandEchoes, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->ecmd[0], ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->phadisc, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->audgflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->audglim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->valcflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->samplim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->heflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->hyflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->preoflg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->hetlim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->hytlim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->htcmd[0], ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->rcmd, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->qctime, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->ledtime, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->sfmisc, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->camsel, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->iilima, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->iilimb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->iilims[0], ((2)*(4)) );
   ptr+= ((2)*(4));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->lsarr[0], ((2)*(20)) );
   ptr+= ((2)*(20));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->loarr[0], ((2)*(20)) );
   ptr+= ((2)*(20));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->laymax, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->remmax, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->b_xoff[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->rngmsk[0], ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->bparams[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->twotelen, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->gphaen, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->stbfon, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->ncenbox, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->b_cenbox[0], ((2)*(64)) );
   ptr+= ((2)*(64));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->iilim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->iignct, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->iignrf, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->sftdisc, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->sftrig0, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->sftrig1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->cdscoff, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->tdscoff, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->srgbits[0], ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->dacvals[0], ((1)*(52)) );
   ptr+= ((1)*(52));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->dacsize[0], ((1)*(52)) );
   ptr+= ((1)*(52));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->hdisc2[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->hdisc1[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->hdisc0[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->mdisc2[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->mdisc1[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->mdisc0[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->adcen[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->gdiscen[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->mdiscen[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->hdiscen[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->cnoc1[0], ((2)*(7)) );
   ptr+= ((2)*(7));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->cnoc2[0], ((2)*(7)) );
   ptr+= ((2)*(7));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->ihiprr0, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->ihiprr1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->stimeid, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->eidmap[0], ((1)*(256)) );
   ptr+= ((1)*(256));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityEcmd[0], ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityPhadisc, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityAudgflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityAudglim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityValcflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualitySamplim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHeflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHyflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityPreoflg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHetlim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHytlim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHtcmd[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityRcmd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityQctime, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityLedtime, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualitySfmisc, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityCamsel, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityIilima, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityIilimb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityIilims[0], ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityLsarr[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityLoarr[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityLaymax, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityRemmax, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityB_xoff[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityRngmsk[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityBparams[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityTwotelen, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityGphaen, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityStbfon, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityNcenbox, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityB_cenbox[0], ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityIilim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityIignct, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityIignrf, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualitySftdisc, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualitySftrig0, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualitySftrig1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityCdscoff, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityTdscoff, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualitySrgbits[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityDacvals[0], ((1)*(52)) );
   ptr+= ((1)*(52));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityDacsize[0], ((1)*(52)) );
   ptr+= ((1)*(52));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHdisc2[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHdisc1[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHdisc0[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityMdisc2[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityMdisc1[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityMdisc0[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityAdcen[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityGdiscen[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityMdiscen[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityHdiscen[0], ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityCnoc1[0], ((1)*(7)) );
   ptr+= ((1)*(7));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityCnoc2[0], ((1)*(7)) );
   ptr+= ((1)*(7));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityIhiprr0, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityIhiprr1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityStimeid, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandTable_ptr->QualityEidmap[0], ((1)*(256)) );
   ptr+= ((1)*(256));
}

/*----   unpack function    ----*/

void unpack_L1CrisCommandTable(uint8 *data, struct L1CrisCommandTable *L1CrisCommandTable_ptr)
{
int32 ptr=0;

   memcpy(&L1CrisCommandTable_ptr->ClockMinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandTable_ptr->ClockMinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandTable_ptr->Second1996MinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandTable_ptr->MicrosecondMinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandTable_ptr->Second1996MinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandTable_ptr->MicrosecondMinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandTable_ptr->NumberCommandEchoes, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->ecmd[0], data+ptr,  ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(&L1CrisCommandTable_ptr->phadisc, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->audgflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->audglim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->valcflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->samplim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->heflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->hyflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->preoflg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->hetlim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->hytlim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->htcmd[0], data+ptr,  ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(&L1CrisCommandTable_ptr->rcmd, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->qctime, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->ledtime, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->sfmisc, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->camsel, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->iilima, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->iilimb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->iilims[0], data+ptr,  ((2)*(4)) );
   ptr+= ((2)*(4));
   memcpy(&L1CrisCommandTable_ptr->lsarr[0], data+ptr,  ((2)*(20)) );
   ptr+= ((2)*(20));
   memcpy(&L1CrisCommandTable_ptr->loarr[0], data+ptr,  ((2)*(20)) );
   ptr+= ((2)*(20));
   memcpy(&L1CrisCommandTable_ptr->laymax, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->remmax, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->b_xoff[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1CrisCommandTable_ptr->rngmsk[0], data+ptr,  ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(&L1CrisCommandTable_ptr->bparams[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&L1CrisCommandTable_ptr->twotelen, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->gphaen, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->stbfon, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->ncenbox, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->b_cenbox[0], data+ptr,  ((2)*(64)) );
   ptr+= ((2)*(64));
   memcpy(&L1CrisCommandTable_ptr->iilim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->iignct, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->iignrf, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->sftdisc, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->sftrig0, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->sftrig1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->cdscoff, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->tdscoff, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->srgbits[0], data+ptr,  ((2)*(2)) );
   ptr+= ((2)*(2));
   memcpy(&L1CrisCommandTable_ptr->dacvals[0], data+ptr,  ((1)*(52)) );
   ptr+= ((1)*(52));
   memcpy(&L1CrisCommandTable_ptr->dacsize[0], data+ptr,  ((1)*(52)) );
   ptr+= ((1)*(52));
   memcpy(&L1CrisCommandTable_ptr->hdisc2[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->hdisc1[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->hdisc0[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->mdisc2[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->mdisc1[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->mdisc0[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->adcen[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->gdiscen[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->mdiscen[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->hdiscen[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->cnoc1[0], data+ptr,  ((2)*(7)) );
   ptr+= ((2)*(7));
   memcpy(&L1CrisCommandTable_ptr->cnoc2[0], data+ptr,  ((2)*(7)) );
   ptr+= ((2)*(7));
   memcpy(&L1CrisCommandTable_ptr->ihiprr0, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->ihiprr1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->stimeid, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisCommandTable_ptr->eidmap[0], data+ptr,  ((1)*(256)) );
   ptr+= ((1)*(256));
   memcpy(&L1CrisCommandTable_ptr->QualityEcmd[0], data+ptr,  ((1)*(6)) );
   ptr+= ((1)*(6));
   memcpy(&L1CrisCommandTable_ptr->QualityPhadisc, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityAudgflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityAudglim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityValcflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualitySamplim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityHeflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityHyflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityPreoflg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityHetlim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityHytlim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityHtcmd[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&L1CrisCommandTable_ptr->QualityRcmd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityQctime, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityLedtime, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualitySfmisc, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityCamsel, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityIilima, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityIilimb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityIilims[0], data+ptr,  ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(&L1CrisCommandTable_ptr->QualityLsarr[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&L1CrisCommandTable_ptr->QualityLoarr[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&L1CrisCommandTable_ptr->QualityLaymax, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityRemmax, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityB_xoff[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1CrisCommandTable_ptr->QualityRngmsk[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1CrisCommandTable_ptr->QualityBparams[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&L1CrisCommandTable_ptr->QualityTwotelen, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityGphaen, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityStbfon, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityNcenbox, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityB_cenbox[0], data+ptr,  ((1)*(64)) );
   ptr+= ((1)*(64));
   memcpy(&L1CrisCommandTable_ptr->QualityIilim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityIignct, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityIignrf, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualitySftdisc, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualitySftrig0, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualitySftrig1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityCdscoff, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityTdscoff, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualitySrgbits[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&L1CrisCommandTable_ptr->QualityDacvals[0], data+ptr,  ((1)*(52)) );
   ptr+= ((1)*(52));
   memcpy(&L1CrisCommandTable_ptr->QualityDacsize[0], data+ptr,  ((1)*(52)) );
   ptr+= ((1)*(52));
   memcpy(&L1CrisCommandTable_ptr->QualityHdisc2[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityHdisc1[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityHdisc0[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityMdisc2[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityMdisc1[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityMdisc0[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityAdcen[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityGdiscen[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityMdiscen[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityHdiscen[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
   memcpy(&L1CrisCommandTable_ptr->QualityCnoc1[0], data+ptr,  ((1)*(7)) );
   ptr+= ((1)*(7));
   memcpy(&L1CrisCommandTable_ptr->QualityCnoc2[0], data+ptr,  ((1)*(7)) );
   ptr+= ((1)*(7));
   memcpy(&L1CrisCommandTable_ptr->QualityIhiprr0, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityIhiprr1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityStimeid, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandTable_ptr->QualityEidmap[0], data+ptr,  ((1)*(256)) );
   ptr+= ((1)*(256));
}
int32 get_vgrp_id_L1CrisCommandTable() {return(vgrp_id_L1CrisCommandTable);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1CrisCommandTable(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1CrisCommandTable.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1CrisCommandTable'.\n\n");
  strcat(wr_strval,"/* Id: L1CrisCommandTable.h,v 1.4 1998/05/08 23:15:29 rgr Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisCommandTable.h,v $ */\n");
  strcat(wr_strval,"/* $Author: rgr $ */\n");
  strcat(wr_strval,"/* $Date: 1998/05/08 23:15:29 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.4 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1CrisCommandTable\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame0;\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame1;\n");
  strcat(wr_strval,"   uint32 Second1996MinorFrame0;\n");
  strcat(wr_strval,"   uint32 MicrosecondMinorFrame0;\n");
  strcat(wr_strval,"   uint32 Second1996MinorFrame1;\n");
  strcat(wr_strval,"   uint32 MicrosecondMinorFrame1;\n");
  strcat(wr_strval,"   uint16 NumberCommandEchoes;\n");
  strcat(wr_strval,"   uint8  ecmd[6];\n");
  strcat(wr_strval,"   uint16 phadisc;\n");
  strcat(wr_strval,"   uint16 audgflg;\n");
  strcat(wr_strval,"   uint16 audglim;\n");
  strcat(wr_strval,"   uint16 valcflg;\n");
  strcat(wr_strval,"   uint16 samplim;\n");
  strcat(wr_strval,"   uint16 heflg;\n");
  strcat(wr_strval,"   uint16 hyflg;\n");
  strcat(wr_strval,"   uint16 preoflg;\n");
  strcat(wr_strval,"   uint16 hetlim;\n");
  strcat(wr_strval,"   uint16 hytlim;\n");
  strcat(wr_strval,"   uint16 htcmd[8];\n");
  strcat(wr_strval,"   uint16 rcmd;\n");
  strcat(wr_strval,"   uint16 qctime;\n");
  strcat(wr_strval,"   uint16 ledtime;\n");
  strcat(wr_strval,"   uint16 sfmisc;\n");
  strcat(wr_strval,"   uint16 camsel;\n");
  strcat(wr_strval,"   uint16 iilima;\n");
  strcat(wr_strval,"   uint16 iilimb;\n");
  strcat(wr_strval,"   uint16  iilims[4];\n");
  strcat(wr_strval,"   int16  lsarr[20];\n");
  strcat(wr_strval,"   int16  loarr[20];\n");
  strcat(wr_strval,"   uint16 laymax;\n");
  strcat(wr_strval,"   uint16 remmax;\n");
  strcat(wr_strval,"   uint8  b_xoff[2];\n");
  strcat(wr_strval,"   uint16 rngmsk[2];\n");
  strcat(wr_strval,"   uint8  bparams[20];\n");
  strcat(wr_strval,"   uint16 twotelen;\n");
  strcat(wr_strval,"   uint16 gphaen;\n");
  strcat(wr_strval,"   uint16 stbfon;\n");
  strcat(wr_strval,"   uint16 ncenbox;\n");
  strcat(wr_strval,"   uint16 b_cenbox[64];\n");
  strcat(wr_strval,"   uint16 iilim;\n");
  strcat(wr_strval,"   uint16 iignct;\n");
  strcat(wr_strval,"   uint16 iignrf;\n");
  strcat(wr_strval,"   uint16 sftdisc;\n");
  strcat(wr_strval,"   uint16 sftrig0;\n");
  strcat(wr_strval,"   uint16 sftrig1;\n");
  strcat(wr_strval,"   uint16 cdscoff;\n");
  strcat(wr_strval,"   uint16 tdscoff;\n");
  strcat(wr_strval,"   uint16 srgbits[2];\n");
  strcat(wr_strval,"   uint8  dacvals[52];\n");
  strcat(wr_strval,"   uint8  dacsize[52];\n");
  strcat(wr_strval,"   uint8  hdisc2[12];\n");
  strcat(wr_strval,"   uint8  hdisc1[12];\n");
  strcat(wr_strval,"   uint8  hdisc0[12];\n");
  strcat(wr_strval,"   uint8  mdisc2[12];\n");
  strcat(wr_strval,"   uint8  mdisc1[12];\n");
  strcat(wr_strval,"   uint8  mdisc0[12];\n");
  strcat(wr_strval,"   uint8  adcen[12];\n");
  strcat(wr_strval,"   uint8  gdiscen[12];\n");
  strcat(wr_strval,"   uint8  mdiscen[12];\n");
  strcat(wr_strval,"   uint8  hdiscen[12];\n");
  strcat(wr_strval,"   uint16 cnoc1[7];\n");
  strcat(wr_strval,"   uint16 cnoc2[7];\n");
  strcat(wr_strval,"   uint16 ihiprr0;\n");
  strcat(wr_strval,"   uint16 ihiprr1;\n");
  strcat(wr_strval,"   uint16 stimeid;\n");
  strcat(wr_strval,"   uint8  eidmap[256];\n");
  strcat(wr_strval,"   uint8  QualityEcmd[6];\n");
  strcat(wr_strval,"   uint8  QualityPhadisc;\n");
  strcat(wr_strval,"   uint8  QualityAudgflg;\n");
  strcat(wr_strval,"   uint8  QualityAudglim;\n");
  strcat(wr_strval,"   uint8  QualityValcflg;\n");
  strcat(wr_strval,"   uint8  QualitySamplim;\n");
  strcat(wr_strval,"   uint8  QualityHeflg;\n");
  strcat(wr_strval,"   uint8  QualityHyflg;\n");
  strcat(wr_strval,"   uint8  QualityPreoflg;\n");
  strcat(wr_strval,"   uint8  QualityHetlim;\n");
  strcat(wr_strval,"   uint8  QualityHytlim;\n");
  strcat(wr_strval,"   uint8  QualityHtcmd[8];\n");
  strcat(wr_strval,"   uint8  QualityRcmd;\n");
  strcat(wr_strval,"   uint8  QualityQctime;\n");
  strcat(wr_strval,"   uint8  QualityLedtime;\n");
  strcat(wr_strval,"   uint8  QualitySfmisc;\n");
  strcat(wr_strval,"   uint8  QualityCamsel;\n");
  strcat(wr_strval,"   uint8  QualityIilima;\n");
  strcat(wr_strval,"   uint8  QualityIilimb;\n");
  strcat(wr_strval,"   uint8  QualityIilims[4];\n");
  strcat(wr_strval,"   uint8  QualityLsarr[20];\n");
  strcat(wr_strval,"   uint8  QualityLoarr[20];\n");
  strcat(wr_strval,"   uint8  QualityLaymax;\n");
  strcat(wr_strval,"   uint8  QualityRemmax;\n");
  strcat(wr_strval,"   uint8  QualityB_xoff[2];\n");
  strcat(wr_strval,"   uint8  QualityRngmsk[2];\n");
  strcat(wr_strval,"   uint8  QualityBparams[20];\n");
  strcat(wr_strval,"   uint8  QualityTwotelen;\n");
  strcat(wr_strval,"   uint8  QualityGphaen;\n");
  strcat(wr_strval,"   uint8  QualityStbfon;\n");
  strcat(wr_strval,"   uint8  QualityNcenbox;\n");
  strcat(wr_strval,"   uint8  QualityB_cenbox[64];\n");
  strcat(wr_strval,"   uint8  QualityIilim;\n");
  strcat(wr_strval,"   uint8  QualityIignct;\n");
  strcat(wr_strval,"   uint8  QualityIignrf;\n");
  strcat(wr_strval,"   uint8  QualitySftdisc;\n");
  strcat(wr_strval,"   uint8  QualitySftrig0;\n");
  strcat(wr_strval,"   uint8  QualitySftrig1;\n");
  strcat(wr_strval,"   uint8  QualityCdscoff;\n");
  strcat(wr_strval,"   uint8  QualityTdscoff;\n");
  strcat(wr_strval,"   uint8  QualitySrgbits[2];\n");
  strcat(wr_strval,"   uint8  QualityDacvals[52];\n");
  strcat(wr_strval,"   uint8  QualityDacsize[52];\n");
  strcat(wr_strval,"   uint8  QualityHdisc2[12];\n");
  strcat(wr_strval,"   uint8  QualityHdisc1[12];\n");
  strcat(wr_strval,"   uint8  QualityHdisc0[12];\n");
  strcat(wr_strval,"   uint8  QualityMdisc2[12];\n");
  strcat(wr_strval,"   uint8  QualityMdisc1[12];\n");
  strcat(wr_strval,"   uint8  QualityMdisc0[12];\n");
  strcat(wr_strval,"   uint8  QualityAdcen[12];\n");
  strcat(wr_strval,"   uint8  QualityGdiscen[12];\n");
  strcat(wr_strval,"   uint8  QualityMdiscen[12];\n");
  strcat(wr_strval,"   uint8  QualityHdiscen[12];\n");
  strcat(wr_strval,"   uint8  QualityCnoc1[7];\n");
  strcat(wr_strval,"   uint8  QualityCnoc2[7];\n");
  strcat(wr_strval,"   uint8  QualityIhiprr0;\n");
  strcat(wr_strval,"   uint8  QualityIhiprr1;\n");
  strcat(wr_strval,"   uint8  QualityStimeid;\n");
  strcat(wr_strval,"   uint8  QualityEidmap[256];\n");
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
