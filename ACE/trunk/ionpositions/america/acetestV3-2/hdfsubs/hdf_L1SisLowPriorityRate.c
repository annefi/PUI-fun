/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisLowPriorityRate.h,v 1.3 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisLowPriorityRate.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_L1SisLowPriorityRate;
static int32 vdata_id_L1SisLowPriorityRate;

static int32 sds_id_L1SisLowPriorityRate1;

  /* 8397 is the size of L1SisLowPriorityRate.h + 1 added line */
char Vgrp_descrp_L1SisLowPriorityRate[8397];

/****----  init create function  ----****/

int32 init_cr_L1SisLowPriorityRate(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_L1SisLowPriorityRate();

  void print_L1SisLowPriorityRate_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisLowPriorityRate = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisLowPriorityRate, "VG_L1SisLowPriorityRate"); 
  Vsetclass(vgrp_id_L1SisLowPriorityRate, "VG_L1SISLOWPRIORITYRATE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisLowPriorityRate" )) ==FAIL) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisLowPriorityRate(Vgrp_descrp_L1SisLowPriorityRate);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisLowPriorityRate, sizeof(Vgrp_descrp_L1SisLowPriorityRate))) ==FAIL) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisLowPriorityRate = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisLowPriorityRate, "L1SisLowPriorityRate");
  VSsetclass(vdata_id_L1SisLowPriorityRate, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisLowPriorityRate, vdata_id_L1SisLowPriorityRate)) ==FAIL) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "ClockCycle", DFNT_UINT32, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define ClockCycle");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "Second1996", DFNT_UINT32, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "microsecond", DFNT_UINT32, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM1a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM1ha", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM1ha");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM2ha", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM2ha");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT1a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT3a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT4a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT4a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT5a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT5a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT6a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT6a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT7a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT7a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT8a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT8a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM12a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM12a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsMora", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsMora");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsHora", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsHora");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsHiza", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsHiza");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsMaybeHiza", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsMaybeHiza");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsZ2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsZ2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsMaybeZ2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsMaybeZ2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsMaybeZ1a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsMaybeZ1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM1b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM1hb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM1hb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM2hb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM2hb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT1b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT3b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT4b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT4b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT5b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT5b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT6b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT6b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT7b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT7b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsT8b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsT8b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsM12b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsM12b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsMorb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsMorb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsHorb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsHorb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsHizb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsHizb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsMaybeHizb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsMaybeHizb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsZ2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsZ2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsMaybeZ2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsMaybeZ2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsMaybeZ1b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsMaybeZ1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsRejFast", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsRejFast");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsStimCoin", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsStimCoin");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsHazard", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsHazard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsAdc2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsAdc2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsAdc3a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsAdc3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsAdc2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsAdc2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsAdc3b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsAdc3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsCoinRate0", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsCoinRate0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "RejcntsCoinRate1", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define RejcntsCoinRate1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM1a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM1ha", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM1ha");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM2ha", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM2ha");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT1a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT3a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT4a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT4a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT5a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT5a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT6a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT6a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT7a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT7a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT8a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT8a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM12a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM12a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsMora", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsMora");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsHora", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsHora");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsHiza", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsHiza");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsMaybeHiza", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsMaybeHiza");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsZ2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsZ2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsMaybeZ2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsMaybeZ2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsMaybeZ1a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsMaybeZ1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM1b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM1hb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM1hb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM2hb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM2hb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT1b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT3b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT4b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT4b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT5b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT5b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT6b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT6b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT7b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT7b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsT8b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsT8b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsM12b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsM12b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsMorb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsMorb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsHorb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsHorb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsHizb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsHizb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsMaybeHizb", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsMaybeHizb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsZ2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsZ2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsMaybeZ2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsMaybeZ2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsMaybeZ1b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsMaybeZ1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsRejFast", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsRejFast");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsStimCoin", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsStimCoin");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsHazard", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsHazard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsAdc2a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsAdc2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsAdc3a", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsAdc3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsAdc2b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsAdc2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsAdc3b", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsAdc3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsCoinRate0", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsCoinRate0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "VldcntsCoinRate1", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define VldcntsCoinRate1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "EventBuffer", DFNT_UINT16, (NUM_SIS_EVT_BUFFERS) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define EventBuffer");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "clasacc", DFNT_UINT16, (NUM_SIS_EVT_CLASSES) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define clasacc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "clastot", DFNT_UINT16, (NUM_SIS_EVT_CLASSES) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define clastot");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "livetim", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define livetim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "helivet", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define helivet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "hylivet", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define hylivet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "ntagint", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define ntagint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "nvldint", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define nvldint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "nevproc", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define nevproc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "nrtproc", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define nrtproc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "nbadid", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define nbadid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "ncebful", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define ncebful");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "nrebful", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define nrebful");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "nhdwrej", DFNT_UINT16, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define nhdwrej");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM1a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM1ha", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM1ha");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM2ha", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM2ha");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT1a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT3a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT4a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT4a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT5a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT5a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT6a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT6a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT7a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT7a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT8a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT8a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM12a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM12a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsMora", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsMora");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsHora", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsHora");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsHiza", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsHiza");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsMaybeHiza", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsMaybeHiza");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsZ2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsZ2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsMaybeZ2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsMaybeZ2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsMaybeZ1a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsMaybeZ1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM1b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM1hb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM1hb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM2hb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM2hb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT1b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT3b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT4b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT4b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT5b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT5b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT6b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT6b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT7b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT7b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsT8b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsT8b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsM12b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsM12b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsMorb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsMorb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsHorb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsHorb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsHizb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsHizb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsMaybeHizb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsMaybeHizb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsZ2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsZ2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsMaybeZ2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsMaybeZ2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsMaybeZ1b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsMaybeZ1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsRejFast", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsRejFast");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsStimCoin", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsStimCoin");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsHazard", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsHazard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsAdc2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsAdc2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsAdc3a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsAdc3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsAdc2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsAdc2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsAdc3b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsAdc3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsCoinRate0", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsCoinRate0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityRejcntsCoinRate1", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityRejcntsCoinRate1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM1a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM1ha", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM1ha");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM2ha", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM2ha");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT1a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT3a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT4a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT4a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT5a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT5a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT6a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT6a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT7a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT7a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT8a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT8a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM12a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM12a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsMora", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsMora");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsHora", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsHora");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsHiza", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsHiza");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsMaybeHiza", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsMaybeHiza");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsZ2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsZ2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsMaybeZ2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsMaybeZ2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsMaybeZ1a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsMaybeZ1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM1b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM1hb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM1hb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM2hb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM2hb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT1b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT3b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT4b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT4b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT5b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT5b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT6b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT6b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT7b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT7b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsT8b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsT8b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsM12b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsM12b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsMorb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsMorb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsHorb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsHorb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsHizb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsHizb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsMaybeHizb", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsMaybeHizb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsZ2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsZ2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsMaybeZ2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsMaybeZ2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsMaybeZ1b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsMaybeZ1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsRejFast", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsRejFast");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsStimCoin", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsStimCoin");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsHazard", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsHazard");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsAdc2a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsAdc2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsAdc3a", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsAdc3a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsAdc2b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsAdc2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsAdc3b", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsAdc3b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsCoinRate0", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsCoinRate0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityVldcntsCoinRate1", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityVldcntsCoinRate1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityEventBuffer", DFNT_UINT8, (NUM_SIS_EVT_BUFFERS) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityEventBuffer");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityClasacc", DFNT_UINT8, (NUM_SIS_EVT_CLASSES) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityClasacc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityClastot", DFNT_UINT8, (NUM_SIS_EVT_CLASSES) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityClastot");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityLivetim", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityLivetim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityHelivet", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityHelivet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityHylivet", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityHylivet");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNtagint", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNtagint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNvldint", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNvldint");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNevproc", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNevproc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNrtproc", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNrtproc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNbadid", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNbadid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNcebful", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNcebful");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNrebful", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNrebful");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNhdwrej", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNhdwrej");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisLowPriorityRate, "QualityNumberEvents", DFNT_UINT8, (1) )) {
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSfdefine: Couldn't define QualityNumberEvents");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisLowPriorityRate,"ClockCycle, Second1996, microsecond, RejcntsM1a, RejcntsM1ha, RejcntsM2a, RejcntsM2ha, RejcntsT1a, RejcntsT2a, RejcntsT3a, RejcntsT4a, RejcntsT5a, RejcntsT6a, RejcntsT7a, RejcntsT8a, RejcntsM12a, RejcntsMora, RejcntsHora, RejcntsHiza, RejcntsMaybeHiza, RejcntsZ2a, RejcntsMaybeZ2a, RejcntsMaybeZ1a, RejcntsM1b, RejcntsM1hb, RejcntsM2b, RejcntsM2hb, RejcntsT1b, RejcntsT2b, RejcntsT3b, RejcntsT4b, RejcntsT5b, RejcntsT6b, RejcntsT7b, RejcntsT8b, RejcntsM12b, RejcntsMorb, RejcntsHorb, RejcntsHizb, RejcntsMaybeHizb, RejcntsZ2b, RejcntsMaybeZ2b, RejcntsMaybeZ1b, RejcntsRejFast, RejcntsStimCoin, RejcntsHazard, RejcntsAdc2a, RejcntsAdc3a, RejcntsAdc2b, RejcntsAdc3b, RejcntsCoinRate0, RejcntsCoinRate1, VldcntsM1a, VldcntsM1ha, VldcntsM2a, VldcntsM2ha, VldcntsT1a, VldcntsT2a, VldcntsT3a, VldcntsT4a, VldcntsT5a, VldcntsT6a, VldcntsT7a, VldcntsT8a, VldcntsM12a, VldcntsMora, VldcntsHora, VldcntsHiza, VldcntsMaybeHiza, VldcntsZ2a, VldcntsMaybeZ2a, VldcntsMaybeZ1a, VldcntsM1b, VldcntsM1hb, VldcntsM2b, VldcntsM2hb, VldcntsT1b, VldcntsT2b, VldcntsT3b, VldcntsT4b, VldcntsT5b, VldcntsT6b, VldcntsT7b, VldcntsT8b, VldcntsM12b, VldcntsMorb, VldcntsHorb, VldcntsHizb, VldcntsMaybeHizb, VldcntsZ2b, VldcntsMaybeZ2b, VldcntsMaybeZ1b, VldcntsRejFast, VldcntsStimCoin, VldcntsHazard, VldcntsAdc2a, VldcntsAdc3a, VldcntsAdc2b, VldcntsAdc3b, VldcntsCoinRate0, VldcntsCoinRate1, EventBuffer, clasacc, clastot, livetim, helivet, hylivet, ntagint, nvldint, nevproc, nrtproc, nbadid, ncebful, nrebful, nhdwrej, QualityRejcntsM1a, QualityRejcntsM1ha, QualityRejcntsM2a, QualityRejcntsM2ha, QualityRejcntsT1a, QualityRejcntsT2a, QualityRejcntsT3a, QualityRejcntsT4a, QualityRejcntsT5a, QualityRejcntsT6a, QualityRejcntsT7a, QualityRejcntsT8a, QualityRejcntsM12a, QualityRejcntsMora, QualityRejcntsHora, QualityRejcntsHiza, QualityRejcntsMaybeHiza, QualityRejcntsZ2a, QualityRejcntsMaybeZ2a, QualityRejcntsMaybeZ1a, QualityRejcntsM1b, QualityRejcntsM1hb, QualityRejcntsM2b, QualityRejcntsM2hb, QualityRejcntsT1b, QualityRejcntsT2b, QualityRejcntsT3b, QualityRejcntsT4b, QualityRejcntsT5b, QualityRejcntsT6b, QualityRejcntsT7b, QualityRejcntsT8b, QualityRejcntsM12b, QualityRejcntsMorb, QualityRejcntsHorb, QualityRejcntsHizb, QualityRejcntsMaybeHizb, QualityRejcntsZ2b, QualityRejcntsMaybeZ2b, QualityRejcntsMaybeZ1b, QualityRejcntsRejFast, QualityRejcntsStimCoin, QualityRejcntsHazard, QualityRejcntsAdc2a, QualityRejcntsAdc3a, QualityRejcntsAdc2b, QualityRejcntsAdc3b, QualityRejcntsCoinRate0, QualityRejcntsCoinRate1, QualityVldcntsM1a, QualityVldcntsM1ha, QualityVldcntsM2a, QualityVldcntsM2ha, QualityVldcntsT1a, QualityVldcntsT2a, QualityVldcntsT3a, QualityVldcntsT4a, QualityVldcntsT5a, QualityVldcntsT6a, QualityVldcntsT7a, QualityVldcntsT8a, QualityVldcntsM12a, QualityVldcntsMora, QualityVldcntsHora, QualityVldcntsHiza, QualityVldcntsMaybeHiza, QualityVldcntsZ2a, QualityVldcntsMaybeZ2a, QualityVldcntsMaybeZ1a, QualityVldcntsM1b, QualityVldcntsM1hb, QualityVldcntsM2b, QualityVldcntsM2hb, QualityVldcntsT1b, QualityVldcntsT2b, QualityVldcntsT3b, QualityVldcntsT4b, QualityVldcntsT5b, QualityVldcntsT6b, QualityVldcntsT7b, QualityVldcntsT8b, QualityVldcntsM12b, QualityVldcntsMorb, QualityVldcntsHorb, QualityVldcntsHizb, QualityVldcntsMaybeHizb, QualityVldcntsZ2b, QualityVldcntsMaybeZ2b, QualityVldcntsMaybeZ1b, QualityVldcntsRejFast, QualityVldcntsStimCoin, QualityVldcntsHazard, QualityVldcntsAdc2a, QualityVldcntsAdc3a, QualityVldcntsAdc2b, QualityVldcntsAdc3b, QualityVldcntsCoinRate0, QualityVldcntsCoinRate1, QualityEventBuffer, QualityClasacc, QualityClastot, QualityLivetim, QualityHelivet, QualityHylivet, QualityNtagint, QualityNvldint, QualityNevproc, QualityNrtproc, QualityNbadid, QualityNcebful, QualityNrebful, QualityNhdwrej, QualityNumberEvents")){
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = NUM_SIS_EVT_BUFFERS;
  dim_sizes[2] = NUM_SIS_EVT_CLASSES;
  if((sds_id_L1SisLowPriorityRate1 = SDcreate(sd_id, "L1SisLowPriorityRate_NumberEvents", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> SDcreate: Couldn't create L1SisLowPriorityRate_NumberEvents");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_L1SisLowPriorityRate1)) == FAIL)
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> SDidtoref: Couldn't get ref for L1SisLowPriorityRate_NumberEvents");

  if((Vaddtagref(vgrp_id_L1SisLowPriorityRate, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_L1SisLowPriorityRate_error("init_cr_L1SisLowPriorityRate -> Vaddtagref: Couldn't add SDS L1SisLowPriorityRate_NumberEvents to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisLowPriorityRate(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisLowPriorityRate(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisLowPriorityRate(struct L1SisLowPriorityRate L1SisLowPriorityRate_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_L1SisLowPriorityRate_error();
void pack_L1SisLowPriorityRate();

  odata = (uint8 *) malloc(sizeof(struct L1SisLowPriorityRate));
  pack_L1SisLowPriorityRate(odata, &L1SisLowPriorityRate_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_L1SisLowPriorityRate, recnum)==-1) {
		print_L1SisLowPriorityRate_error("write_L1SisLowPriorityRate -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisLowPriorityRate, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisLowPriorityRate_error("write_L1SisLowPriorityRate -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = NUM_SIS_EVT_BUFFERS;
  edges[2] = NUM_SIS_EVT_CLASSES;
  if (SDwritedata(sds_id_L1SisLowPriorityRate1,start,NULL,edges, (VOIDP)(L1SisLowPriorityRate_struc.NumberEvents)) ==FAIL)
    print_L1SisLowPriorityRate_error("write_L1SisLowPriorityRate -> SDwritedata: Problem writing NumberEvents data.");

  memset(&L1SisLowPriorityRate_struc, 0, sizeof(struct L1SisLowPriorityRate));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisLowPriorityRate()
{
  VSdetach(vdata_id_L1SisLowPriorityRate);
  Vdetach(vgrp_id_L1SisLowPriorityRate);
  SDendaccess(sds_id_L1SisLowPriorityRate1);
}

/*----     init access function    ----*/

int32 init_acc_L1SisLowPriorityRate(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisLowPriorityRate_error();

  if((sds_index1=SDnametoindex(sd_id, "L1SisLowPriorityRate_NumberEvents" )) ==FAIL) {
      print_L1SisLowPriorityRate_error("init_acc_L1SisLowPriorityRate -> SDnametoindex: Couldn't find L1SisLowPriorityRate_NumberEvents");
      return(-1);
  }
  if((sds_id_L1SisLowPriorityRate1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_L1SisLowPriorityRate_error("init_acc_L1SisLowPriorityRate -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "L1SisLowPriorityRate")) <= 0 ) {
    print_L1SisLowPriorityRate_error("init_acc_L1SisLowPriorityRate -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisLowPriorityRate = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisLowPriorityRate_error("init_acc_L1SisLowPriorityRate -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisLowPriorityRate, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisLowPriorityRate,"ClockCycle, Second1996, microsecond, RejcntsM1a, RejcntsM1ha, RejcntsM2a, RejcntsM2ha, RejcntsT1a, RejcntsT2a, RejcntsT3a, RejcntsT4a, RejcntsT5a, RejcntsT6a, RejcntsT7a, RejcntsT8a, RejcntsM12a, RejcntsMora, RejcntsHora, RejcntsHiza, RejcntsMaybeHiza, RejcntsZ2a, RejcntsMaybeZ2a, RejcntsMaybeZ1a, RejcntsM1b, RejcntsM1hb, RejcntsM2b, RejcntsM2hb, RejcntsT1b, RejcntsT2b, RejcntsT3b, RejcntsT4b, RejcntsT5b, RejcntsT6b, RejcntsT7b, RejcntsT8b, RejcntsM12b, RejcntsMorb, RejcntsHorb, RejcntsHizb, RejcntsMaybeHizb, RejcntsZ2b, RejcntsMaybeZ2b, RejcntsMaybeZ1b, RejcntsRejFast, RejcntsStimCoin, RejcntsHazard, RejcntsAdc2a, RejcntsAdc3a, RejcntsAdc2b, RejcntsAdc3b, RejcntsCoinRate0, RejcntsCoinRate1, VldcntsM1a, VldcntsM1ha, VldcntsM2a, VldcntsM2ha, VldcntsT1a, VldcntsT2a, VldcntsT3a, VldcntsT4a, VldcntsT5a, VldcntsT6a, VldcntsT7a, VldcntsT8a, VldcntsM12a, VldcntsMora, VldcntsHora, VldcntsHiza, VldcntsMaybeHiza, VldcntsZ2a, VldcntsMaybeZ2a, VldcntsMaybeZ1a, VldcntsM1b, VldcntsM1hb, VldcntsM2b, VldcntsM2hb, VldcntsT1b, VldcntsT2b, VldcntsT3b, VldcntsT4b, VldcntsT5b, VldcntsT6b, VldcntsT7b, VldcntsT8b, VldcntsM12b, VldcntsMorb, VldcntsHorb, VldcntsHizb, VldcntsMaybeHizb, VldcntsZ2b, VldcntsMaybeZ2b, VldcntsMaybeZ1b, VldcntsRejFast, VldcntsStimCoin, VldcntsHazard, VldcntsAdc2a, VldcntsAdc3a, VldcntsAdc2b, VldcntsAdc3b, VldcntsCoinRate0, VldcntsCoinRate1, EventBuffer, clasacc, clastot, livetim, helivet, hylivet, ntagint, nvldint, nevproc, nrtproc, nbadid, ncebful, nrebful, nhdwrej, QualityRejcntsM1a, QualityRejcntsM1ha, QualityRejcntsM2a, QualityRejcntsM2ha, QualityRejcntsT1a, QualityRejcntsT2a, QualityRejcntsT3a, QualityRejcntsT4a, QualityRejcntsT5a, QualityRejcntsT6a, QualityRejcntsT7a, QualityRejcntsT8a, QualityRejcntsM12a, QualityRejcntsMora, QualityRejcntsHora, QualityRejcntsHiza, QualityRejcntsMaybeHiza, QualityRejcntsZ2a, QualityRejcntsMaybeZ2a, QualityRejcntsMaybeZ1a, QualityRejcntsM1b, QualityRejcntsM1hb, QualityRejcntsM2b, QualityRejcntsM2hb, QualityRejcntsT1b, QualityRejcntsT2b, QualityRejcntsT3b, QualityRejcntsT4b, QualityRejcntsT5b, QualityRejcntsT6b, QualityRejcntsT7b, QualityRejcntsT8b, QualityRejcntsM12b, QualityRejcntsMorb, QualityRejcntsHorb, QualityRejcntsHizb, QualityRejcntsMaybeHizb, QualityRejcntsZ2b, QualityRejcntsMaybeZ2b, QualityRejcntsMaybeZ1b, QualityRejcntsRejFast, QualityRejcntsStimCoin, QualityRejcntsHazard, QualityRejcntsAdc2a, QualityRejcntsAdc3a, QualityRejcntsAdc2b, QualityRejcntsAdc3b, QualityRejcntsCoinRate0, QualityRejcntsCoinRate1, QualityVldcntsM1a, QualityVldcntsM1ha, QualityVldcntsM2a, QualityVldcntsM2ha, QualityVldcntsT1a, QualityVldcntsT2a, QualityVldcntsT3a, QualityVldcntsT4a, QualityVldcntsT5a, QualityVldcntsT6a, QualityVldcntsT7a, QualityVldcntsT8a, QualityVldcntsM12a, QualityVldcntsMora, QualityVldcntsHora, QualityVldcntsHiza, QualityVldcntsMaybeHiza, QualityVldcntsZ2a, QualityVldcntsMaybeZ2a, QualityVldcntsMaybeZ1a, QualityVldcntsM1b, QualityVldcntsM1hb, QualityVldcntsM2b, QualityVldcntsM2hb, QualityVldcntsT1b, QualityVldcntsT2b, QualityVldcntsT3b, QualityVldcntsT4b, QualityVldcntsT5b, QualityVldcntsT6b, QualityVldcntsT7b, QualityVldcntsT8b, QualityVldcntsM12b, QualityVldcntsMorb, QualityVldcntsHorb, QualityVldcntsHizb, QualityVldcntsMaybeHizb, QualityVldcntsZ2b, QualityVldcntsMaybeZ2b, QualityVldcntsMaybeZ1b, QualityVldcntsRejFast, QualityVldcntsStimCoin, QualityVldcntsHazard, QualityVldcntsAdc2a, QualityVldcntsAdc3a, QualityVldcntsAdc2b, QualityVldcntsAdc3b, QualityVldcntsCoinRate0, QualityVldcntsCoinRate1, QualityEventBuffer, QualityClasacc, QualityClastot, QualityLivetim, QualityHelivet, QualityHylivet, QualityNtagint, QualityNvldint, QualityNevproc, QualityNrtproc, QualityNbadid, QualityNcebful, QualityNrebful, QualityNhdwrej, QualityNumberEvents")) {
      print_L1SisLowPriorityRate_error("init_acc_L1SisLowPriorityRate -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisLowPriorityRate(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisLowPriorityRate(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisLowPriorityRate(struct L1SisLowPriorityRate *L1SisLowPriorityRate_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisLowPriorityRate_error();
void unpack_L1SisLowPriorityRate();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct L1SisLowPriorityRate));
  VSinquire(vdata_id_L1SisLowPriorityRate, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisLowPriorityRate, recnum_rd)==FAIL) {
          print_L1SisLowPriorityRate_error("read_L1SisLowPriorityRate -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = NUM_SIS_EVT_BUFFERS;
  edges[2] = NUM_SIS_EVT_CLASSES;

  if(SDreaddata(sds_id_L1SisLowPriorityRate1,start,NULL,edges, (VOIDP)(L1SisLowPriorityRate_struc->NumberEvents )) ==FAIL) {
    print_L1SisLowPriorityRate_error("read_L1SisLowPriorityRate -> SDreaddata: Couldn't read NumberEvents");
    retval = -1;
  }
  if(VSread(vdata_id_L1SisLowPriorityRate, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisLowPriorityRate_error("read_L1SisLowPriorityRate -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisLowPriorityRate(odata, L1SisLowPriorityRate_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisLowPriorityRate()
{
  VSdetach(vdata_id_L1SisLowPriorityRate);
  SDendaccess(sds_id_L1SisLowPriorityRate1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisLowPriorityRate(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisLowPriorityRate_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisLowPriorityRate" )) ==FAIL)
    print_L1SisLowPriorityRate_error("rd_Vgrp_L1SisLowPriorityRate -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisLowPriorityRate_error("rd_Vgrp_L1SisLowPriorityRate -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisLowPriorityRate_error("rd_Vgrp_L1SisLowPriorityRate -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisLowPriorityRate_error("rd_Vgrp_L1SisLowPriorityRate -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisLowPriorityRate, HDstrlen(Vgrp_descrp_L1SisLowPriorityRate)) ==FAIL)
    print_L1SisLowPriorityRate_error("rd_Vgrp_L1SisLowPriorityRate -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisLowPriorityRate);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisLowPriorityRate_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisLowPriorityRate.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisLowPriorityRate(uint8 *data, struct L1SisLowPriorityRate *L1SisLowPriorityRate_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->ClockCycle, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM1a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM1ha, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM2ha, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT1a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT3a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT4a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT5a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT6a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT7a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT8a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM12a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsMora, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsHora, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsHiza, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsMaybeHiza, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsZ2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsMaybeZ2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsMaybeZ1a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM1b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM1hb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM2hb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT1b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT3b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT4b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT5b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT6b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT7b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsT8b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsM12b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsMorb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsHorb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsHizb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsMaybeHizb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsZ2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsMaybeZ2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsMaybeZ1b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsRejFast, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsStimCoin, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsHazard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsAdc2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsAdc3a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsAdc2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsAdc3b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsCoinRate0, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->RejcntsCoinRate1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM1a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM1ha, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM2ha, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT1a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT3a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT4a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT5a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT6a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT7a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT8a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM12a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsMora, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsHora, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsHiza, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsMaybeHiza, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsZ2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsMaybeZ2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsMaybeZ1a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM1b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM1hb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM2hb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT1b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT3b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT4b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT5b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT6b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT7b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsT8b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsM12b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsMorb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsHorb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsHizb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsMaybeHizb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsZ2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsMaybeZ2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsMaybeZ1b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsRejFast, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsStimCoin, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsHazard, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsAdc2a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsAdc3a, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsAdc2b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsAdc3b, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsCoinRate0, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->VldcntsCoinRate1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->EventBuffer[0], ((2)*(NUM_SIS_EVT_BUFFERS)) );
   ptr+= ((2)*(NUM_SIS_EVT_BUFFERS));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->clasacc[0], ((2)*(NUM_SIS_EVT_CLASSES)) );
   ptr+= ((2)*(NUM_SIS_EVT_CLASSES));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->clastot[0], ((2)*(NUM_SIS_EVT_CLASSES)) );
   ptr+= ((2)*(NUM_SIS_EVT_CLASSES));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->livetim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->helivet, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->hylivet, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->ntagint, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->nvldint, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->nevproc, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->nrtproc, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->nbadid, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->ncebful, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->nrebful, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->nhdwrej, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM1ha, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM2ha, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT3a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT4a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT5a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT6a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT7a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT8a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM12a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsMora, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsHora, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsHiza, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsMaybeHiza, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsZ2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsMaybeZ2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsMaybeZ1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM1hb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM2hb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT3b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT4b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT5b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT6b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT7b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsT8b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsM12b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsMorb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsHorb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsHizb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsMaybeHizb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsZ2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsMaybeZ2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsMaybeZ1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsRejFast, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsStimCoin, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsHazard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsAdc2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsAdc3a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsAdc2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsAdc3b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsCoinRate0, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityRejcntsCoinRate1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM1ha, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM2ha, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT3a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT4a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT5a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT6a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT7a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT8a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM12a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsMora, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsHora, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsHiza, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsMaybeHiza, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsZ2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsMaybeZ2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsMaybeZ1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM1hb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM2hb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT3b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT4b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT5b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT6b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT7b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsT8b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsM12b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsMorb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsHorb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsHizb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsMaybeHizb, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsZ2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsMaybeZ2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsMaybeZ1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsRejFast, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsStimCoin, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsHazard, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsAdc2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsAdc3a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsAdc2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsAdc3b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsCoinRate0, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityVldcntsCoinRate1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityEventBuffer[0], ((1)*(NUM_SIS_EVT_BUFFERS)) );
   ptr+= ((1)*(NUM_SIS_EVT_BUFFERS));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityClasacc[0], ((1)*(NUM_SIS_EVT_CLASSES)) );
   ptr+= ((1)*(NUM_SIS_EVT_CLASSES));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityClastot[0], ((1)*(NUM_SIS_EVT_CLASSES)) );
   ptr+= ((1)*(NUM_SIS_EVT_CLASSES));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityLivetim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityHelivet, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityHylivet, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNtagint, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNvldint, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNevproc, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNrtproc, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNbadid, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNcebful, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNrebful, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNhdwrej, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisLowPriorityRate_ptr->QualityNumberEvents, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_L1SisLowPriorityRate(uint8 *data, struct L1SisLowPriorityRate *L1SisLowPriorityRate_ptr)
{
int32 ptr=0;

   memcpy(&L1SisLowPriorityRate_ptr->ClockCycle, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM1a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM1ha, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM2ha, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT1a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT3a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT4a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT5a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT6a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT7a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT8a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM12a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsMora, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsHora, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsHiza, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsMaybeHiza, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsZ2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsMaybeZ2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsMaybeZ1a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM1b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM1hb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM2hb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT1b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT3b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT4b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT5b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT6b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT7b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsT8b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsM12b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsMorb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsHorb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsHizb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsMaybeHizb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsZ2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsMaybeZ2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsMaybeZ1b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsRejFast, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsStimCoin, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsHazard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsAdc2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsAdc3a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsAdc2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsAdc3b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsCoinRate0, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->RejcntsCoinRate1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM1a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM1ha, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM2ha, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT1a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT3a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT4a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT5a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT6a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT7a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT8a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM12a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsMora, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsHora, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsHiza, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsMaybeHiza, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsZ2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsMaybeZ2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsMaybeZ1a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM1b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM1hb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM2hb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT1b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT3b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT4b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT5b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT6b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT7b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsT8b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsM12b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsMorb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsHorb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsHizb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsMaybeHizb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsZ2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsMaybeZ2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsMaybeZ1b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsRejFast, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsStimCoin, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsHazard, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsAdc2a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsAdc3a, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsAdc2b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsAdc3b, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsCoinRate0, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->VldcntsCoinRate1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->EventBuffer[0], data+ptr,  ((2)*(NUM_SIS_EVT_BUFFERS)) );
   ptr+= ((2)*(NUM_SIS_EVT_BUFFERS));
   memcpy(&L1SisLowPriorityRate_ptr->clasacc[0], data+ptr,  ((2)*(NUM_SIS_EVT_CLASSES)) );
   ptr+= ((2)*(NUM_SIS_EVT_CLASSES));
   memcpy(&L1SisLowPriorityRate_ptr->clastot[0], data+ptr,  ((2)*(NUM_SIS_EVT_CLASSES)) );
   ptr+= ((2)*(NUM_SIS_EVT_CLASSES));
   memcpy(&L1SisLowPriorityRate_ptr->livetim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->helivet, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->hylivet, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->ntagint, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->nvldint, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->nevproc, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->nrtproc, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->nbadid, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->ncebful, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->nrebful, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->nhdwrej, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM1ha, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM2ha, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT3a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT4a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT5a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT6a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT7a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT8a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM12a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsMora, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsHora, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsHiza, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsMaybeHiza, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsZ2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsMaybeZ2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsMaybeZ1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM1hb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM2hb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT3b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT4b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT5b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT6b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT7b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsT8b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsM12b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsMorb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsHorb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsHizb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsMaybeHizb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsZ2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsMaybeZ2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsMaybeZ1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsRejFast, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsStimCoin, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsHazard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsAdc2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsAdc3a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsAdc2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsAdc3b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsCoinRate0, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityRejcntsCoinRate1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM1ha, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM2ha, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT3a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT4a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT5a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT6a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT7a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT8a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM12a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsMora, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsHora, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsHiza, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsMaybeHiza, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsZ2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsMaybeZ2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsMaybeZ1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM1hb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM2hb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT3b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT4b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT5b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT6b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT7b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsT8b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsM12b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsMorb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsHorb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsHizb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsMaybeHizb, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsZ2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsMaybeZ2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsMaybeZ1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsRejFast, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsStimCoin, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsHazard, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsAdc2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsAdc3a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsAdc2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsAdc3b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsCoinRate0, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityVldcntsCoinRate1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityEventBuffer[0], data+ptr,  ((1)*(NUM_SIS_EVT_BUFFERS)) );
   ptr+= ((1)*(NUM_SIS_EVT_BUFFERS));
   memcpy(&L1SisLowPriorityRate_ptr->QualityClasacc[0], data+ptr,  ((1)*(NUM_SIS_EVT_CLASSES)) );
   ptr+= ((1)*(NUM_SIS_EVT_CLASSES));
   memcpy(&L1SisLowPriorityRate_ptr->QualityClastot[0], data+ptr,  ((1)*(NUM_SIS_EVT_CLASSES)) );
   ptr+= ((1)*(NUM_SIS_EVT_CLASSES));
   memcpy(&L1SisLowPriorityRate_ptr->QualityLivetim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityHelivet, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityHylivet, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNtagint, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNvldint, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNevproc, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNrtproc, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNbadid, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNcebful, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNrebful, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNhdwrej, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisLowPriorityRate_ptr->QualityNumberEvents, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_L1SisLowPriorityRate() {return(vgrp_id_L1SisLowPriorityRate);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisLowPriorityRate(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisLowPriorityRate.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisLowPriorityRate'.\n\n");
  strcat(wr_strval,"/* Id: L1SisLowPriorityRate.h,v 1.3 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisLowPriorityRate.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisLowPriorityRate\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockCycle;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint16 RejcntsM1a;\n");
  strcat(wr_strval,"   uint16 RejcntsM1ha;\n");
  strcat(wr_strval,"   uint16 RejcntsM2a;\n");
  strcat(wr_strval,"   uint16 RejcntsM2ha;\n");
  strcat(wr_strval,"   uint16 RejcntsT1a;\n");
  strcat(wr_strval,"   uint16 RejcntsT2a;\n");
  strcat(wr_strval,"   uint16 RejcntsT3a;\n");
  strcat(wr_strval,"   uint16 RejcntsT4a;\n");
  strcat(wr_strval,"   uint16 RejcntsT5a;\n");
  strcat(wr_strval,"   uint16 RejcntsT6a;\n");
  strcat(wr_strval,"   uint16 RejcntsT7a;\n");
  strcat(wr_strval,"   uint16 RejcntsT8a;\n");
  strcat(wr_strval,"   uint16 RejcntsM12a;\n");
  strcat(wr_strval,"   uint16 RejcntsMora;\n");
  strcat(wr_strval,"   uint16 RejcntsHora;\n");
  strcat(wr_strval,"   uint16 RejcntsHiza;\n");
  strcat(wr_strval,"   uint16 RejcntsMaybeHiza;\n");
  strcat(wr_strval,"   uint16 RejcntsZ2a;\n");
  strcat(wr_strval,"   uint16 RejcntsMaybeZ2a;\n");
  strcat(wr_strval,"   uint16 RejcntsMaybeZ1a;\n");
  strcat(wr_strval,"   uint16 RejcntsM1b;\n");
  strcat(wr_strval,"   uint16 RejcntsM1hb;\n");
  strcat(wr_strval,"   uint16 RejcntsM2b;\n");
  strcat(wr_strval,"   uint16 RejcntsM2hb;\n");
  strcat(wr_strval,"   uint16 RejcntsT1b;\n");
  strcat(wr_strval,"   uint16 RejcntsT2b;\n");
  strcat(wr_strval,"   uint16 RejcntsT3b;\n");
  strcat(wr_strval,"   uint16 RejcntsT4b;\n");
  strcat(wr_strval,"   uint16 RejcntsT5b;\n");
  strcat(wr_strval,"   uint16 RejcntsT6b;\n");
  strcat(wr_strval,"   uint16 RejcntsT7b;\n");
  strcat(wr_strval,"   uint16 RejcntsT8b;\n");
  strcat(wr_strval,"   uint16 RejcntsM12b;\n");
  strcat(wr_strval,"   uint16 RejcntsMorb;\n");
  strcat(wr_strval,"   uint16 RejcntsHorb;\n");
  strcat(wr_strval,"   uint16 RejcntsHizb;\n");
  strcat(wr_strval,"   uint16 RejcntsMaybeHizb;\n");
  strcat(wr_strval,"   uint16 RejcntsZ2b;\n");
  strcat(wr_strval,"   uint16 RejcntsMaybeZ2b;\n");
  strcat(wr_strval,"   uint16 RejcntsMaybeZ1b;\n");
  strcat(wr_strval,"   uint16 RejcntsRejFast;\n");
  strcat(wr_strval,"   uint16 RejcntsStimCoin;\n");
  strcat(wr_strval,"   uint16 RejcntsHazard;\n");
  strcat(wr_strval,"   uint16 RejcntsAdc2a;\n");
  strcat(wr_strval,"   uint16 RejcntsAdc3a;\n");
  strcat(wr_strval,"   uint16 RejcntsAdc2b;\n");
  strcat(wr_strval,"   uint16 RejcntsAdc3b;\n");
  strcat(wr_strval,"   uint16 RejcntsCoinRate0;\n");
  strcat(wr_strval,"   uint16 RejcntsCoinRate1;\n");
  strcat(wr_strval,"   uint16 VldcntsM1a;\n");
  strcat(wr_strval,"   uint16 VldcntsM1ha;\n");
  strcat(wr_strval,"   uint16 VldcntsM2a;\n");
  strcat(wr_strval,"   uint16 VldcntsM2ha;\n");
  strcat(wr_strval,"   uint16 VldcntsT1a;\n");
  strcat(wr_strval,"   uint16 VldcntsT2a;\n");
  strcat(wr_strval,"   uint16 VldcntsT3a;\n");
  strcat(wr_strval,"   uint16 VldcntsT4a;\n");
  strcat(wr_strval,"   uint16 VldcntsT5a;\n");
  strcat(wr_strval,"   uint16 VldcntsT6a;\n");
  strcat(wr_strval,"   uint16 VldcntsT7a;\n");
  strcat(wr_strval,"   uint16 VldcntsT8a;\n");
  strcat(wr_strval,"   uint16 VldcntsM12a;\n");
  strcat(wr_strval,"   uint16 VldcntsMora;\n");
  strcat(wr_strval,"   uint16 VldcntsHora;\n");
  strcat(wr_strval,"   uint16 VldcntsHiza;\n");
  strcat(wr_strval,"   uint16 VldcntsMaybeHiza;\n");
  strcat(wr_strval,"   uint16 VldcntsZ2a;\n");
  strcat(wr_strval,"   uint16 VldcntsMaybeZ2a;\n");
  strcat(wr_strval,"   uint16 VldcntsMaybeZ1a;\n");
  strcat(wr_strval,"   uint16 VldcntsM1b;\n");
  strcat(wr_strval,"   uint16 VldcntsM1hb;\n");
  strcat(wr_strval,"   uint16 VldcntsM2b;\n");
  strcat(wr_strval,"   uint16 VldcntsM2hb;\n");
  strcat(wr_strval,"   uint16 VldcntsT1b;\n");
  strcat(wr_strval,"   uint16 VldcntsT2b;\n");
  strcat(wr_strval,"   uint16 VldcntsT3b;\n");
  strcat(wr_strval,"   uint16 VldcntsT4b;\n");
  strcat(wr_strval,"   uint16 VldcntsT5b;\n");
  strcat(wr_strval,"   uint16 VldcntsT6b;\n");
  strcat(wr_strval,"   uint16 VldcntsT7b;\n");
  strcat(wr_strval,"   uint16 VldcntsT8b;\n");
  strcat(wr_strval,"   uint16 VldcntsM12b;\n");
  strcat(wr_strval,"   uint16 VldcntsMorb;\n");
  strcat(wr_strval,"   uint16 VldcntsHorb;\n");
  strcat(wr_strval,"   uint16 VldcntsHizb;\n");
  strcat(wr_strval,"   uint16 VldcntsMaybeHizb;\n");
  strcat(wr_strval,"   uint16 VldcntsZ2b;\n");
  strcat(wr_strval,"   uint16 VldcntsMaybeZ2b;\n");
  strcat(wr_strval,"   uint16 VldcntsMaybeZ1b;\n");
  strcat(wr_strval,"   uint16 VldcntsRejFast;\n");
  strcat(wr_strval,"   uint16 VldcntsStimCoin;\n");
  strcat(wr_strval,"   uint16 VldcntsHazard;\n");
  strcat(wr_strval,"   uint16 VldcntsAdc2a;\n");
  strcat(wr_strval,"   uint16 VldcntsAdc3a;\n");
  strcat(wr_strval,"   uint16 VldcntsAdc2b;\n");
  strcat(wr_strval,"   uint16 VldcntsAdc3b;\n");
  strcat(wr_strval,"   uint16 VldcntsCoinRate0;\n");
  strcat(wr_strval,"   uint16 VldcntsCoinRate1;\n");
  strcat(wr_strval,"   uint16 EventBuffer[NUM_SIS_EVT_BUFFERS];\n");
  strcat(wr_strval,"   uint16 clasacc[NUM_SIS_EVT_CLASSES];\n");
  strcat(wr_strval,"   uint16 clastot[NUM_SIS_EVT_CLASSES];\n");
  strcat(wr_strval,"   uint16 livetim;\n");
  strcat(wr_strval,"   uint16 helivet;\n");
  strcat(wr_strval,"   uint16 hylivet;\n");
  strcat(wr_strval,"   uint16 ntagint;\n");
  strcat(wr_strval,"   uint16 nvldint;\n");
  strcat(wr_strval,"   uint16 nevproc;\n");
  strcat(wr_strval,"   uint16 nrtproc;\n");
  strcat(wr_strval,"   uint16 nbadid;\n");
  strcat(wr_strval,"   uint16 ncebful;\n");
  strcat(wr_strval,"   uint16 nrebful;\n");
  strcat(wr_strval,"   uint16 nhdwrej;\n");
  strcat(wr_strval,"   uint16 NumberEvents[NUM_SIS_EVT_BUFFERS][NUM_SIS_EVT_CLASSES];\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM1a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM1ha;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM2a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM2ha;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT1a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT2a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT3a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT4a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT5a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT6a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT7a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT8a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM12a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsMora;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsHora;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsHiza;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsMaybeHiza;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsZ2a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsMaybeZ2a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsMaybeZ1a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM1b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM1hb;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM2b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM2hb;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT1b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT2b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT3b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT4b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT5b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT6b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT7b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsT8b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsM12b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsMorb;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsHorb;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsHizb;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsMaybeHizb;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsZ2b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsMaybeZ2b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsMaybeZ1b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsRejFast;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsStimCoin;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsHazard;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsAdc2a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsAdc3a;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsAdc2b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsAdc3b;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsCoinRate0;\n");
  strcat(wr_strval,"   uint8  QualityRejcntsCoinRate1;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM1a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM1ha;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM2a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM2ha;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT1a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT2a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT3a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT4a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT5a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT6a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT7a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT8a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM12a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsMora;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsHora;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsHiza;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsMaybeHiza;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsZ2a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsMaybeZ2a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsMaybeZ1a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM1b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM1hb;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM2b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM2hb;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT1b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT2b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT3b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT4b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT5b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT6b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT7b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsT8b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsM12b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsMorb;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsHorb;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsHizb;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsMaybeHizb;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsZ2b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsMaybeZ2b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsMaybeZ1b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsRejFast;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsStimCoin;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsHazard;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsAdc2a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsAdc3a;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsAdc2b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsAdc3b;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsCoinRate0;\n");
  strcat(wr_strval,"   uint8  QualityVldcntsCoinRate1;\n");
  strcat(wr_strval,"   uint8  QualityEventBuffer[NUM_SIS_EVT_BUFFERS];\n");
  strcat(wr_strval,"   uint8  QualityClasacc[NUM_SIS_EVT_CLASSES];\n");
  strcat(wr_strval,"   uint8  QualityClastot[NUM_SIS_EVT_CLASSES];\n");
  strcat(wr_strval,"   uint8  QualityLivetim;\n");
  strcat(wr_strval,"   uint8  QualityHelivet;\n");
  strcat(wr_strval,"   uint8  QualityHylivet;\n");
  strcat(wr_strval,"   uint8  QualityNtagint;\n");
  strcat(wr_strval,"   uint8  QualityNvldint;\n");
  strcat(wr_strval,"   uint8  QualityNevproc;\n");
  strcat(wr_strval,"   uint8  QualityNrtproc;\n");
  strcat(wr_strval,"   uint8  QualityNbadid;\n");
  strcat(wr_strval,"   uint8  QualityNcebful;\n");
  strcat(wr_strval,"   uint8  QualityNrebful;\n");
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
  strcat(wr_strval,"/* Note: All rates are compressed.                                   */\n");
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
