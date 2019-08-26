/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1CrisLowPriorityRate.h,v 1.3 1997/09/11 00:37:38 jeff Exp  */

#include "L1CrisLowPriorityRate.h"
#include "df.h"

int32 vgrp_id_L1CrisLowPriorityRate;
static int32 vdata_id_L1CrisLowPriorityRate;

  /* 5026 is the size of L1CrisLowPriorityRate.h + 1 added line */
char Vgrp_descrp_L1CrisLowPriorityRate[5026];

/****----  init create function  ----****/

int32 init_cr_L1CrisLowPriorityRate(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1CrisLowPriorityRate();

  void print_L1CrisLowPriorityRate_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1CrisLowPriorityRate = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1CrisLowPriorityRate, "VG_L1CrisLowPriorityRate"); 
  Vsetclass(vgrp_id_L1CrisLowPriorityRate, "VG_L1CRISLOWPRIORITYRATE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1CrisLowPriorityRate" )) ==FAIL) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1CrisLowPriorityRate(Vgrp_descrp_L1CrisLowPriorityRate);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1CrisLowPriorityRate, sizeof(Vgrp_descrp_L1CrisLowPriorityRate))) ==FAIL) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1CrisLowPriorityRate = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1CrisLowPriorityRate, "L1CrisLowPriorityRate");
  VSsetclass(vdata_id_L1CrisLowPriorityRate, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1CrisLowPriorityRate, vdata_id_L1CrisLowPriorityRate)) ==FAIL) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "ClockCycle", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define ClockCycle");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "Second1996", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "microsecond", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "stmco", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define stmco");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "stmoff", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define stmoff");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "z1ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define z1ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "z2ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define z2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "z_gt_2ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define z_gt_2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "z1cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define z1cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "z2cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define z2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "z_gt_2cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define z_gt_2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "hazard", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define hazard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "gh", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define gh");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "mor", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define mor");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "hor", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define hor");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "adc2ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define adc2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "mnrgab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define mnrgab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "adc2cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define adc2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "mnrgcd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define mnrgcd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e1a", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e1b", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e2ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e3ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e4ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e5ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e6ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e7ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e8ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e8ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e9ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e9ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g2ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g3ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g4ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g5ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g6ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g7ab", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e1c", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e1c");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e1d", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e1d");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e2cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e3cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e4cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e5cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e6cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e7cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e8cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e8cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "e9cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define e9cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g2cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g3cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g4cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g5cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g6cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "g7cd", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define g7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "EventBuffer", DFNT_UINT32, (NUM_CRIS_EVT_BUFFERS) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define EventBuffer");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "livetim", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define livetim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "helivet", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define helivet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "hylivet", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define hylivet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "trg0rat", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define trg0rat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "trg1rat", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define trg1rat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "trg01", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define trg01");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "ntagint", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define ntagint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "nvldint", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define nvldint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "nevproc", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define nevproc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "nrtproc", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define nrtproc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "nsfterr", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define nsfterr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "nbadid", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define nbadid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "ncebful", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define ncebful");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "nrebful", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define nrebful");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "nmacsys", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define nmacsys");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "nhdwrej", DFNT_UINT32, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define nhdwrej");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "NumberEvents", DFNT_UINT16, (NUM_CRIS_EVT_BUFFERS) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define NumberEvents");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityStmco", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityStmco");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityStmoff", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityStmoff");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityZ1ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityZ1ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityZ2ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityZ2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityZ_gt_2ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityZ_gt_2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityZ1cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityZ1cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityZ2cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityZ2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityZ_gt_2cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityZ_gt_2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityHazard", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityHazard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityGh", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityGh");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityMor", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityMor");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityHor", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityHor");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityAdc2ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityAdc2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityMnrgab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityMnrgab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityAdc2cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityAdc2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityMnrgcd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityMnrgcd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE1a", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE1b", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE2ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE3ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE4ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE5ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE6ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE7ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE8ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE8ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE9ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE9ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG2ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG2ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG3ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG3ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG4ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG4ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG5ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG5ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG6ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG6ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG7ab", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG7ab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE1c", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE1c");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE1d", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE1d");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE2cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE3cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE4cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE5cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE6cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE7cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE8cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE8cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityE9cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityE9cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG2cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG2cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG3cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG3cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG4cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG4cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG5cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG5cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG6cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG6cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityG7cd", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityG7cd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityEventBuffer", DFNT_UINT8, (NUM_CRIS_EVT_BUFFERS) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityEventBuffer");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityLivetim", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityLivetim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityHelivet", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityHelivet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityHylivet", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityHylivet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityTrg0rat", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityTrg0rat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityTrg1rat", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityTrg1rat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityTrg01", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityTrg01");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNtagint", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNtagint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNvldint", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNvldint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNevproc", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNevproc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNrtproc", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNrtproc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNsfterr", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNsfterr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNbadid", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNbadid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNcebful", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNcebful");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNrebful", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNrebful");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNmacsys", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNmacsys");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNhdwrej", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNhdwrej");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisLowPriorityRate, "QualityNumberEvents", DFNT_UINT8, (1) )) {
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSfdefine: Couldn't define QualityNumberEvents");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1CrisLowPriorityRate,"ClockCycle, Second1996, microsecond, stmco, stmoff, z1ab, z2ab, z_gt_2ab, z1cd, z2cd, z_gt_2cd, hazard, gh, mor, hor, adc2ab, mnrgab, adc2cd, mnrgcd, e1a, e1b, e2ab, e3ab, e4ab, e5ab, e6ab, e7ab, e8ab, e9ab, g2ab, g3ab, g4ab, g5ab, g6ab, g7ab, e1c, e1d, e2cd, e3cd, e4cd, e5cd, e6cd, e7cd, e8cd, e9cd, g2cd, g3cd, g4cd, g5cd, g6cd, g7cd, EventBuffer, livetim, helivet, hylivet, trg0rat, trg1rat, trg01, ntagint, nvldint, nevproc, nrtproc, nsfterr, nbadid, ncebful, nrebful, nmacsys, nhdwrej, NumberEvents, QualityStmco, QualityStmoff, QualityZ1ab, QualityZ2ab, QualityZ_gt_2ab, QualityZ1cd, QualityZ2cd, QualityZ_gt_2cd, QualityHazard, QualityGh, QualityMor, QualityHor, QualityAdc2ab, QualityMnrgab, QualityAdc2cd, QualityMnrgcd, QualityE1a, QualityE1b, QualityE2ab, QualityE3ab, QualityE4ab, QualityE5ab, QualityE6ab, QualityE7ab, QualityE8ab, QualityE9ab, QualityG2ab, QualityG3ab, QualityG4ab, QualityG5ab, QualityG6ab, QualityG7ab, QualityE1c, QualityE1d, QualityE2cd, QualityE3cd, QualityE4cd, QualityE5cd, QualityE6cd, QualityE7cd, QualityE8cd, QualityE9cd, QualityG2cd, QualityG3cd, QualityG4cd, QualityG5cd, QualityG6cd, QualityG7cd, QualityEventBuffer, QualityLivetim, QualityHelivet, QualityHylivet, QualityTrg0rat, QualityTrg1rat, QualityTrg01, QualityNtagint, QualityNvldint, QualityNevproc, QualityNrtproc, QualityNsfterr, QualityNbadid, QualityNcebful, QualityNrebful, QualityNmacsys, QualityNhdwrej, QualityNumberEvents")){
    print_L1CrisLowPriorityRate_error("init_cr_L1CrisLowPriorityRate -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1CrisLowPriorityRate(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1CrisLowPriorityRate(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1CrisLowPriorityRate(struct L1CrisLowPriorityRate L1CrisLowPriorityRate_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1CrisLowPriorityRate_error();
void pack_L1CrisLowPriorityRate();

  odata = (uint8 *) malloc(sizeof(struct L1CrisLowPriorityRate));
  pack_L1CrisLowPriorityRate(odata, &L1CrisLowPriorityRate_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1CrisLowPriorityRate, recnum)==-1) {
		print_L1CrisLowPriorityRate_error("write_L1CrisLowPriorityRate -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1CrisLowPriorityRate, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1CrisLowPriorityRate_error("write_L1CrisLowPriorityRate -> VSwrite: Couldn't write data.");

  memset(&L1CrisLowPriorityRate_struc, 0, sizeof(struct L1CrisLowPriorityRate));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1CrisLowPriorityRate()
{
  VSdetach(vdata_id_L1CrisLowPriorityRate);
  Vdetach(vgrp_id_L1CrisLowPriorityRate);
}

/*----     init access function    ----*/

int32 init_acc_L1CrisLowPriorityRate(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1CrisLowPriorityRate_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1CrisLowPriorityRate")) <= 0 ) {
    print_L1CrisLowPriorityRate_error("init_acc_L1CrisLowPriorityRate -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1CrisLowPriorityRate = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1CrisLowPriorityRate_error("init_acc_L1CrisLowPriorityRate -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1CrisLowPriorityRate, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1CrisLowPriorityRate,"ClockCycle, Second1996, microsecond, stmco, stmoff, z1ab, z2ab, z_gt_2ab, z1cd, z2cd, z_gt_2cd, hazard, gh, mor, hor, adc2ab, mnrgab, adc2cd, mnrgcd, e1a, e1b, e2ab, e3ab, e4ab, e5ab, e6ab, e7ab, e8ab, e9ab, g2ab, g3ab, g4ab, g5ab, g6ab, g7ab, e1c, e1d, e2cd, e3cd, e4cd, e5cd, e6cd, e7cd, e8cd, e9cd, g2cd, g3cd, g4cd, g5cd, g6cd, g7cd, EventBuffer, livetim, helivet, hylivet, trg0rat, trg1rat, trg01, ntagint, nvldint, nevproc, nrtproc, nsfterr, nbadid, ncebful, nrebful, nmacsys, nhdwrej, NumberEvents, QualityStmco, QualityStmoff, QualityZ1ab, QualityZ2ab, QualityZ_gt_2ab, QualityZ1cd, QualityZ2cd, QualityZ_gt_2cd, QualityHazard, QualityGh, QualityMor, QualityHor, QualityAdc2ab, QualityMnrgab, QualityAdc2cd, QualityMnrgcd, QualityE1a, QualityE1b, QualityE2ab, QualityE3ab, QualityE4ab, QualityE5ab, QualityE6ab, QualityE7ab, QualityE8ab, QualityE9ab, QualityG2ab, QualityG3ab, QualityG4ab, QualityG5ab, QualityG6ab, QualityG7ab, QualityE1c, QualityE1d, QualityE2cd, QualityE3cd, QualityE4cd, QualityE5cd, QualityE6cd, QualityE7cd, QualityE8cd, QualityE9cd, QualityG2cd, QualityG3cd, QualityG4cd, QualityG5cd, QualityG6cd, QualityG7cd, QualityEventBuffer, QualityLivetim, QualityHelivet, QualityHylivet, QualityTrg0rat, QualityTrg1rat, QualityTrg01, QualityNtagint, QualityNvldint, QualityNevproc, QualityNrtproc, QualityNsfterr, QualityNbadid, QualityNcebful, QualityNrebful, QualityNmacsys, QualityNhdwrej, QualityNumberEvents")) {
      print_L1CrisLowPriorityRate_error("init_acc_L1CrisLowPriorityRate -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1CrisLowPriorityRate(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1CrisLowPriorityRate(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1CrisLowPriorityRate(struct L1CrisLowPriorityRate *L1CrisLowPriorityRate_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1CrisLowPriorityRate_error();
void unpack_L1CrisLowPriorityRate();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1CrisLowPriorityRate));
  VSinquire(vdata_id_L1CrisLowPriorityRate, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1CrisLowPriorityRate, recnum_rd)==FAIL) {
          print_L1CrisLowPriorityRate_error("read_L1CrisLowPriorityRate -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1CrisLowPriorityRate, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1CrisLowPriorityRate_error("read_L1CrisLowPriorityRate -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1CrisLowPriorityRate(odata, L1CrisLowPriorityRate_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1CrisLowPriorityRate()
{
  VSdetach(vdata_id_L1CrisLowPriorityRate);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1CrisLowPriorityRate(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1CrisLowPriorityRate_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1CrisLowPriorityRate" )) ==FAIL)
    print_L1CrisLowPriorityRate_error("rd_Vgrp_L1CrisLowPriorityRate -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1CrisLowPriorityRate_error("rd_Vgrp_L1CrisLowPriorityRate -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1CrisLowPriorityRate_error("rd_Vgrp_L1CrisLowPriorityRate -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1CrisLowPriorityRate_error("rd_Vgrp_L1CrisLowPriorityRate -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1CrisLowPriorityRate, HDstrlen(Vgrp_descrp_L1CrisLowPriorityRate)) ==FAIL)
    print_L1CrisLowPriorityRate_error("rd_Vgrp_L1CrisLowPriorityRate -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1CrisLowPriorityRate);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1CrisLowPriorityRate_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1CrisLowPriorityRate.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1CrisLowPriorityRate(uint8 *data, struct L1CrisLowPriorityRate *L1CrisLowPriorityRate_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->ClockCycle, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->stmco, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->stmoff, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->z1ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->z2ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->z_gt_2ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->z1cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->z2cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->z_gt_2cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->hazard, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->gh, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->mor, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->hor, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->adc2ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->mnrgab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->adc2cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->mnrgcd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e1a, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e1b, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e2ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e3ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e4ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e5ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e6ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e7ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e8ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e9ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g2ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g3ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g4ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g5ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g6ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g7ab, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e1c, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e1d, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e2cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e3cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e4cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e5cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e6cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e7cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e8cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->e9cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g2cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g3cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g4cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g5cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g6cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->g7cd, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->EventBuffer[0], ((4)*(NUM_CRIS_EVT_BUFFERS)) );
   ptr+= ((4)*(NUM_CRIS_EVT_BUFFERS));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->livetim, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->helivet, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->hylivet, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->trg0rat, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->trg1rat, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->trg01, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->ntagint, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->nvldint, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->nevproc, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->nrtproc, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->nsfterr, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->nbadid, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->ncebful, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->nrebful, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->nmacsys, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->nhdwrej, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->NumberEvents[0], ((2)*(NUM_CRIS_EVT_BUFFERS)) );
   ptr+= ((2)*(NUM_CRIS_EVT_BUFFERS));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityStmco, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityStmoff, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityZ1ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityZ2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityZ_gt_2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityZ1cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityZ2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityZ_gt_2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityHazard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityGh, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityMor, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityHor, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityAdc2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityMnrgab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityAdc2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityMnrgcd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE3ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE4ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE5ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE6ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE7ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE8ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE9ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG2ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG3ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG4ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG5ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG6ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG7ab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE1c, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE1d, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE3cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE4cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE5cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE6cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE7cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE8cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityE9cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG2cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG3cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG4cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG5cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG6cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityG7cd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityEventBuffer[0], ((1)*(NUM_CRIS_EVT_BUFFERS)) );
   ptr+= ((1)*(NUM_CRIS_EVT_BUFFERS));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityLivetim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityHelivet, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityHylivet, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityTrg0rat, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityTrg1rat, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityTrg01, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNtagint, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNvldint, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNevproc, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNrtproc, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNsfterr, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNbadid, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNcebful, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNrebful, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNmacsys, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNhdwrej, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisLowPriorityRate_ptr->QualityNumberEvents, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_L1CrisLowPriorityRate(uint8 *data, struct L1CrisLowPriorityRate *L1CrisLowPriorityRate_ptr)
{
int32 ptr=0;

   memcpy(&L1CrisLowPriorityRate_ptr->ClockCycle, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->stmco, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->stmoff, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->z1ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->z2ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->z_gt_2ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->z1cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->z2cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->z_gt_2cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->hazard, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->gh, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->mor, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->hor, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->adc2ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->mnrgab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->adc2cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->mnrgcd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e1a, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e1b, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e2ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e3ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e4ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e5ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e6ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e7ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e8ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e9ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g2ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g3ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g4ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g5ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g6ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g7ab, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e1c, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e1d, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e2cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e3cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e4cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e5cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e6cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e7cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e8cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->e9cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g2cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g3cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g4cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g5cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g6cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->g7cd, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->EventBuffer[0], data+ptr,  ((4)*(NUM_CRIS_EVT_BUFFERS)) );
   ptr+= ((4)*(NUM_CRIS_EVT_BUFFERS));
   memcpy(&L1CrisLowPriorityRate_ptr->livetim, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->helivet, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->hylivet, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->trg0rat, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->trg1rat, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->trg01, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->ntagint, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->nvldint, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->nevproc, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->nrtproc, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->nsfterr, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->nbadid, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->ncebful, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->nrebful, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->nmacsys, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->nhdwrej, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->NumberEvents[0], data+ptr,  ((2)*(NUM_CRIS_EVT_BUFFERS)) );
   ptr+= ((2)*(NUM_CRIS_EVT_BUFFERS));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityStmco, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityStmoff, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityZ1ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityZ2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityZ_gt_2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityZ1cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityZ2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityZ_gt_2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityHazard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityGh, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityMor, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityHor, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityAdc2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityMnrgab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityAdc2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityMnrgcd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE3ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE4ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE5ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE6ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE7ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE8ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE9ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG2ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG3ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG4ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG5ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG6ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG7ab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE1c, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE1d, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE3cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE4cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE5cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE6cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE7cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE8cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityE9cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG2cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG3cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG4cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG5cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG6cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityG7cd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityEventBuffer[0], data+ptr,  ((1)*(NUM_CRIS_EVT_BUFFERS)) );
   ptr+= ((1)*(NUM_CRIS_EVT_BUFFERS));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityLivetim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityHelivet, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityHylivet, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityTrg0rat, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityTrg1rat, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityTrg01, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNtagint, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNvldint, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNevproc, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNrtproc, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNsfterr, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNbadid, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNcebful, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNrebful, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNmacsys, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNhdwrej, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisLowPriorityRate_ptr->QualityNumberEvents, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_L1CrisLowPriorityRate() {return(vgrp_id_L1CrisLowPriorityRate);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1CrisLowPriorityRate(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1CrisLowPriorityRate.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1CrisLowPriorityRate'.\n\n");
  strcat(wr_strval,"/* Id: L1CrisLowPriorityRate.h,v 1.3 1997/09/11 00:37:38 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisLowPriorityRate.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 00:37:38 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"CrisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1CrisLowPriorityRate\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockCycle;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint32 stmco;\n");
  strcat(wr_strval,"   uint32 stmoff;\n");
  strcat(wr_strval,"   uint32 z1ab;\n");
  strcat(wr_strval,"   uint32 z2ab;\n");
  strcat(wr_strval,"   uint32 z_gt_2ab;\n");
  strcat(wr_strval,"   uint32 z1cd;\n");
  strcat(wr_strval,"   uint32 z2cd;\n");
  strcat(wr_strval,"   uint32 z_gt_2cd;\n");
  strcat(wr_strval,"   uint32 hazard;\n");
  strcat(wr_strval,"   uint32 gh;\n");
  strcat(wr_strval,"   uint32 mor;\n");
  strcat(wr_strval,"   uint32 hor;\n");
  strcat(wr_strval,"   uint32 adc2ab;\n");
  strcat(wr_strval,"   uint32 mnrgab;\n");
  strcat(wr_strval,"   uint32 adc2cd;\n");
  strcat(wr_strval,"   uint32 mnrgcd;\n");
  strcat(wr_strval,"   uint32 e1a;\n");
  strcat(wr_strval,"   uint32 e1b;\n");
  strcat(wr_strval,"   uint32 e2ab;\n");
  strcat(wr_strval,"   uint32 e3ab;\n");
  strcat(wr_strval,"   uint32 e4ab;\n");
  strcat(wr_strval,"   uint32 e5ab;\n");
  strcat(wr_strval,"   uint32 e6ab;\n");
  strcat(wr_strval,"   uint32 e7ab;\n");
  strcat(wr_strval,"   uint32 e8ab;\n");
  strcat(wr_strval,"   uint32 e9ab;\n");
  strcat(wr_strval,"   uint32 g2ab;\n");
  strcat(wr_strval,"   uint32 g3ab;\n");
  strcat(wr_strval,"   uint32 g4ab;\n");
  strcat(wr_strval,"   uint32 g5ab;\n");
  strcat(wr_strval,"   uint32 g6ab;\n");
  strcat(wr_strval,"   uint32 g7ab;\n");
  strcat(wr_strval,"   uint32 e1c;\n");
  strcat(wr_strval,"   uint32 e1d;\n");
  strcat(wr_strval,"   uint32 e2cd;\n");
  strcat(wr_strval,"   uint32 e3cd;\n");
  strcat(wr_strval,"   uint32 e4cd;\n");
  strcat(wr_strval,"   uint32 e5cd;\n");
  strcat(wr_strval,"   uint32 e6cd;\n");
  strcat(wr_strval,"   uint32 e7cd;\n");
  strcat(wr_strval,"   uint32 e8cd;\n");
  strcat(wr_strval,"   uint32 e9cd;\n");
  strcat(wr_strval,"   uint32 g2cd;\n");
  strcat(wr_strval,"   uint32 g3cd;\n");
  strcat(wr_strval,"   uint32 g4cd;\n");
  strcat(wr_strval,"   uint32 g5cd;\n");
  strcat(wr_strval,"   uint32 g6cd;\n");
  strcat(wr_strval,"   uint32 g7cd;\n");
  strcat(wr_strval,"   uint32 EventBuffer[NUM_CRIS_EVT_BUFFERS];\n");
  strcat(wr_strval,"   uint32 livetim;\n");
  strcat(wr_strval,"   uint32 helivet;\n");
  strcat(wr_strval,"   uint32 hylivet;\n");
  strcat(wr_strval,"   uint32 trg0rat;\n");
  strcat(wr_strval,"   uint32 trg1rat;\n");
  strcat(wr_strval,"   uint32 trg01;\n");
  strcat(wr_strval,"   uint32 ntagint;\n");
  strcat(wr_strval,"   uint32 nvldint;\n");
  strcat(wr_strval,"   uint32 nevproc;\n");
  strcat(wr_strval,"   uint32 nrtproc;\n");
  strcat(wr_strval,"   uint32 nsfterr;\n");
  strcat(wr_strval,"   uint32 nbadid;\n");
  strcat(wr_strval,"   uint32 ncebful;\n");
  strcat(wr_strval,"   uint32 nrebful;\n");
  strcat(wr_strval,"   uint32 nmacsys;\n");
  strcat(wr_strval,"   uint32 nhdwrej;\n");
  strcat(wr_strval,"   uint16 NumberEvents[NUM_CRIS_EVT_BUFFERS];\n");
  strcat(wr_strval,"   uint8  QualityStmco;\n");
  strcat(wr_strval,"   uint8  QualityStmoff;\n");
  strcat(wr_strval,"   uint8  QualityZ1ab;\n");
  strcat(wr_strval,"   uint8  QualityZ2ab;\n");
  strcat(wr_strval,"   uint8  QualityZ_gt_2ab;\n");
  strcat(wr_strval,"   uint8  QualityZ1cd;\n");
  strcat(wr_strval,"   uint8  QualityZ2cd;\n");
  strcat(wr_strval,"   uint8  QualityZ_gt_2cd;\n");
  strcat(wr_strval,"   uint8  QualityHazard;\n");
  strcat(wr_strval,"   uint8  QualityGh;\n");
  strcat(wr_strval,"   uint8  QualityMor;\n");
  strcat(wr_strval,"   uint8  QualityHor;\n");
  strcat(wr_strval,"   uint8  QualityAdc2ab;\n");
  strcat(wr_strval,"   uint8  QualityMnrgab;\n");
  strcat(wr_strval,"   uint8  QualityAdc2cd;\n");
  strcat(wr_strval,"   uint8  QualityMnrgcd;\n");
  strcat(wr_strval,"   uint8  QualityE1a;\n");
  strcat(wr_strval,"   uint8  QualityE1b;\n");
  strcat(wr_strval,"   uint8  QualityE2ab;\n");
  strcat(wr_strval,"   uint8  QualityE3ab;\n");
  strcat(wr_strval,"   uint8  QualityE4ab;\n");
  strcat(wr_strval,"   uint8  QualityE5ab;\n");
  strcat(wr_strval,"   uint8  QualityE6ab;\n");
  strcat(wr_strval,"   uint8  QualityE7ab;\n");
  strcat(wr_strval,"   uint8  QualityE8ab;\n");
  strcat(wr_strval,"   uint8  QualityE9ab;\n");
  strcat(wr_strval,"   uint8  QualityG2ab;\n");
  strcat(wr_strval,"   uint8  QualityG3ab;\n");
  strcat(wr_strval,"   uint8  QualityG4ab;\n");
  strcat(wr_strval,"   uint8  QualityG5ab;\n");
  strcat(wr_strval,"   uint8  QualityG6ab;\n");
  strcat(wr_strval,"   uint8  QualityG7ab;\n");
  strcat(wr_strval,"   uint8  QualityE1c;\n");
  strcat(wr_strval,"   uint8  QualityE1d;\n");
  strcat(wr_strval,"   uint8  QualityE2cd;\n");
  strcat(wr_strval,"   uint8  QualityE3cd;\n");
  strcat(wr_strval,"   uint8  QualityE4cd;\n");
  strcat(wr_strval,"   uint8  QualityE5cd;\n");
  strcat(wr_strval,"   uint8  QualityE6cd;\n");
  strcat(wr_strval,"   uint8  QualityE7cd;\n");
  strcat(wr_strval,"   uint8  QualityE8cd;\n");
  strcat(wr_strval,"   uint8  QualityE9cd;\n");
  strcat(wr_strval,"   uint8  QualityG2cd;\n");
  strcat(wr_strval,"   uint8  QualityG3cd;\n");
  strcat(wr_strval,"   uint8  QualityG4cd;\n");
  strcat(wr_strval,"   uint8  QualityG5cd;\n");
  strcat(wr_strval,"   uint8  QualityG6cd;\n");
  strcat(wr_strval,"   uint8  QualityG7cd;\n");
  strcat(wr_strval,"   uint8  QualityEventBuffer[NUM_CRIS_EVT_BUFFERS];\n");
  strcat(wr_strval,"   uint8  QualityLivetim;\n");
  strcat(wr_strval,"   uint8  QualityHelivet;\n");
  strcat(wr_strval,"   uint8  QualityHylivet;\n");
  strcat(wr_strval,"   uint8  QualityTrg0rat;\n");
  strcat(wr_strval,"   uint8  QualityTrg1rat;\n");
  strcat(wr_strval,"   uint8  QualityTrg01;\n");
  strcat(wr_strval,"   uint8  QualityNtagint;\n");
  strcat(wr_strval,"   uint8  QualityNvldint;\n");
  strcat(wr_strval,"   uint8  QualityNevproc;\n");
  strcat(wr_strval,"   uint8  QualityNrtproc;\n");
  strcat(wr_strval,"   uint8  QualityNsfterr;\n");
  strcat(wr_strval,"   uint8  QualityNbadid;\n");
  strcat(wr_strval,"   uint8  QualityNcebful;\n");
  strcat(wr_strval,"   uint8  QualityNrebful;\n");
  strcat(wr_strval,"   uint8  QualityNmacsys;\n");
  strcat(wr_strval,"   uint8  QualityNhdwrej;\n");
  strcat(wr_strval,"   uint8  QualityNumberEvents;\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockCycle = Adjusted S/C clock of the first minor frame of    */\n");
  strcat(wr_strval,"/*                 the cycle in which the rate was accumulated.      */\n");
  strcat(wr_strval,"/*                 The value 256 is subtracted from the S/C clock of */\n");
  strcat(wr_strval,"/*                 the first minor frame of the cycle in which the   */\n");
  strcat(wr_strval,"/*                 low priority rates were readout.                  */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Note: All rates are decompressed.                                 */\n");
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
