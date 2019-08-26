/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: cris_level2_data_Bartels.h,v 1.1 2000/08/01 23:43:00 asc Exp  */

#include "cris_level2_data_Bartels.h"
#include "df.h"

int32 vgrp_id_cris_level2_data_Bartels;
static int32 vdata_id_cris_level2_data_Bartels;

  /* 3037 is the size of cris_level2_data_Bartels.h + 1 added line */
char Vgrp_descrp_CRIS_data_Bartels[3037];

/****----  init create function  ----****/

int32 init_cr_cris_level2_data_Bartels(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_cris_level2_data_Bartels();

  void print_cris_level2_data_Bartels_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_cris_level2_data_Bartels = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_cris_level2_data_Bartels, "VG_CRIS_data_Bartels"); 
  Vsetclass(vgrp_id_cris_level2_data_Bartels, "VG_CRIS_LEVEL2_DATA_BARTELS");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_CRIS_data_Bartels" )) ==FAIL) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_cris_level2_data_Bartels(Vgrp_descrp_CRIS_data_Bartels);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_CRIS_data_Bartels, sizeof(Vgrp_descrp_CRIS_data_Bartels))) ==FAIL) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_cris_level2_data_Bartels = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_cris_level2_data_Bartels, "CRIS_data_Bartels");
  VSsetclass(vdata_id_cris_level2_data_Bartels, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_cris_level2_data_Bartels, vdata_id_cris_level2_data_Bartels)) ==FAIL) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "year", DFNT_INT32, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "day", DFNT_INT32, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define day");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "hr", DFNT_INT32, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define hr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "min", DFNT_INT32, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "sec", DFNT_FLOAT32, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define sec");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "fp_year", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define fp_year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "fp_doy", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define fp_doy");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "ACEepoch", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define ACEepoch");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_B", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_B");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_C", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_C");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_N", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_N");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_O", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_O");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_F", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_F");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Ne", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Ne");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Na", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Na");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Mg", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Mg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Al", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Al");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Si", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Si");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_P", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_P");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_S", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_S");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Cl", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Cl");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Ar", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Ar");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_K", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_K");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Ca", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Ca");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Sc", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Sc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Ti", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Ti");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_V", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Cr", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Cr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Mn", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Mn");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Fe", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Fe");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Co", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Co");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "flux_Ni", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define flux_Ni");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_B", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_B");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_C", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_C");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_N", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_N");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_O", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_O");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_F", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_F");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Ne", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Ne");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Na", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Na");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Mg", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Mg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Al", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Al");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Si", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Si");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_P", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_P");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_S", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_S");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Cl", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Cl");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Ar", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Ar");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_K", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_K");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Ca", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Ca");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Sc", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Sc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Ti", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Ti");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_V", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Cr", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Cr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Mn", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Mn");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Fe", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Fe");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Co", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Co");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "cnt_Ni", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define cnt_Ni");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_Bartels, "livetime", DFNT_FLOAT32, (1) )) {
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSfdefine: Couldn't define livetime");
    retval = -1;
  }

  if (VSsetfields(vdata_id_cris_level2_data_Bartels,"year, day, hr, min, sec, fp_year, fp_doy, ACEepoch, flux_B, flux_C, flux_N, flux_O, flux_F, flux_Ne, flux_Na, flux_Mg, flux_Al, flux_Si, flux_P, flux_S, flux_Cl, flux_Ar, flux_K, flux_Ca, flux_Sc, flux_Ti, flux_V, flux_Cr, flux_Mn, flux_Fe, flux_Co, flux_Ni, cnt_B, cnt_C, cnt_N, cnt_O, cnt_F, cnt_Ne, cnt_Na, cnt_Mg, cnt_Al, cnt_Si, cnt_P, cnt_S, cnt_Cl, cnt_Ar, cnt_K, cnt_Ca, cnt_Sc, cnt_Ti, cnt_V, cnt_Cr, cnt_Mn, cnt_Fe, cnt_Co, cnt_Ni, livetime")){
    print_cris_level2_data_Bartels_error("init_cr_cris_level2_data_Bartels -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_cris_level2_data_Bartels(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_cris_level2_data_Bartels(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_cris_level2_data_Bartels(struct CRIS_data_Bartels CRIS_data_Bartels_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_cris_level2_data_Bartels_error();
void pack_cris_level2_data_Bartels();

  odata = (uint8 *) malloc(sizeof(struct CRIS_data_Bartels));
  pack_cris_level2_data_Bartels(odata, &CRIS_data_Bartels_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_cris_level2_data_Bartels, recnum)==-1) {
		print_cris_level2_data_Bartels_error("write_cris_level2_data_Bartels -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_cris_level2_data_Bartels, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_cris_level2_data_Bartels_error("write_cris_level2_data_Bartels -> VSwrite: Couldn't write data.");

  memset(&CRIS_data_Bartels_struc, 0, sizeof(struct CRIS_data_Bartels));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_cris_level2_data_Bartels()
{
  VSdetach(vdata_id_cris_level2_data_Bartels);
  Vdetach(vgrp_id_cris_level2_data_Bartels);
}

/*----     init access function    ----*/

int32 init_acc_cris_level2_data_Bartels(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_cris_level2_data_Bartels_error();


  if ((vdata_ref = VSfind(hdf_fp, "CRIS_data_Bartels")) <= 0 ) {
    print_cris_level2_data_Bartels_error("init_acc_cris_level2_data_Bartels -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_cris_level2_data_Bartels = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_cris_level2_data_Bartels_error("init_acc_cris_level2_data_Bartels -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_cris_level2_data_Bartels, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_cris_level2_data_Bartels,"year, day, hr, min, sec, fp_year, fp_doy, ACEepoch, flux_B, flux_C, flux_N, flux_O, flux_F, flux_Ne, flux_Na, flux_Mg, flux_Al, flux_Si, flux_P, flux_S, flux_Cl, flux_Ar, flux_K, flux_Ca, flux_Sc, flux_Ti, flux_V, flux_Cr, flux_Mn, flux_Fe, flux_Co, flux_Ni, cnt_B, cnt_C, cnt_N, cnt_O, cnt_F, cnt_Ne, cnt_Na, cnt_Mg, cnt_Al, cnt_Si, cnt_P, cnt_S, cnt_Cl, cnt_Ar, cnt_K, cnt_Ca, cnt_Sc, cnt_Ti, cnt_V, cnt_Cr, cnt_Mn, cnt_Fe, cnt_Co, cnt_Ni, livetime")) {
      print_cris_level2_data_Bartels_error("init_acc_cris_level2_data_Bartels -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_cris_level2_data_Bartels(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_cris_level2_data_Bartels(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_cris_level2_data_Bartels(struct CRIS_data_Bartels *CRIS_data_Bartels_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_cris_level2_data_Bartels_error();
void unpack_cris_level2_data_Bartels();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct CRIS_data_Bartels));
  VSinquire(vdata_id_cris_level2_data_Bartels, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_cris_level2_data_Bartels, recnum_rd)==FAIL) {
          print_cris_level2_data_Bartels_error("read_cris_level2_data_Bartels -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_cris_level2_data_Bartels, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_cris_level2_data_Bartels_error("read_cris_level2_data_Bartels -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_cris_level2_data_Bartels(odata, CRIS_data_Bartels_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_cris_level2_data_Bartels()
{
  VSdetach(vdata_id_cris_level2_data_Bartels);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_cris_level2_data_Bartels(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_cris_level2_data_Bartels_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_CRIS_data_Bartels" )) ==FAIL)
    print_cris_level2_data_Bartels_error("rd_Vgrp_cris_level2_data_Bartels -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_cris_level2_data_Bartels_error("rd_Vgrp_cris_level2_data_Bartels -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_cris_level2_data_Bartels_error("rd_Vgrp_cris_level2_data_Bartels -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_cris_level2_data_Bartels_error("rd_Vgrp_cris_level2_data_Bartels -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_CRIS_data_Bartels, HDstrlen(Vgrp_descrp_CRIS_data_Bartels)) ==FAIL)
    print_cris_level2_data_Bartels_error("rd_Vgrp_cris_level2_data_Bartels -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_CRIS_data_Bartels);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_cris_level2_data_Bartels_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_cris_level2_data_Bartels.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_cris_level2_data_Bartels(uint8 *data, struct CRIS_data_Bartels *CRIS_data_Bartels_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &CRIS_data_Bartels_ptr->year, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->day, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->hr, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->min, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->sec, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->fp_year, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->fp_doy, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->ACEepoch, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_B[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_C[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_N[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_O[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_F[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Ne[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Na[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Mg[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Al[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Si[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_P[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_S[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Cl[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Ar[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_K[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Ca[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Sc[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Ti[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_V[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Cr[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Mn[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Fe[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Co[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->flux_Ni[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_B[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_C[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_N[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_O[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_F[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Ne[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Na[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Mg[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Al[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Si[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_P[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_S[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Cl[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Ar[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_K[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Ca[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Sc[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Ti[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_V[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Cr[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Mn[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Fe[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Co[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->cnt_Ni[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_Bartels_ptr->livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_cris_level2_data_Bartels(uint8 *data, struct CRIS_data_Bartels *CRIS_data_Bartels_ptr)
{
int32 ptr=0;

   memcpy(&CRIS_data_Bartels_ptr->year, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_Bartels_ptr->day, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_Bartels_ptr->hr, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_Bartels_ptr->min, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_Bartels_ptr->sec, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_Bartels_ptr->fp_year, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_Bartels_ptr->fp_doy, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_Bartels_ptr->ACEepoch, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_Bartels_ptr->flux_B[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_C[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_N[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_O[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_F[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Ne[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Na[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Mg[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Al[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Si[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_P[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_S[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Cl[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Ar[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_K[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Ca[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Sc[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Ti[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_V[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Cr[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Mn[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Fe[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Co[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->flux_Ni[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_B[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_C[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_N[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_O[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_F[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Ne[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Na[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Mg[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Al[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Si[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_P[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_S[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Cl[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Ar[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_K[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Ca[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Sc[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Ti[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_V[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Cr[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Mn[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Fe[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Co[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->cnt_Ni[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_Bartels_ptr->livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_cris_level2_data_Bartels() {return(vgrp_id_cris_level2_data_Bartels);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_cris_level2_data_Bartels(char *wr_strval)
{
  strcpy(wr_strval, "The file 'cris_level2_data_Bartels.h' is shown below, it was used to create the data in the Vgroup named 'VG_CRIS_data_Bartels'.\n\n");
  strcat(wr_strval,"/* Id: cris_level2_data_Bartels.h,v 1.1 2000/08/01 23:43:00 asc Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"cris_sizes.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct CRIS_data_Bartels {\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* UT time at the start of the periods */\n");
  strcat(wr_strval,"  int32   year;                         /* integer year */\n");
  strcat(wr_strval,"  int32   day;                          /* integer day of year */\n");
  strcat(wr_strval,"  int32   hr;                           /* hour of day */\n");
  strcat(wr_strval,"  int32   min;                          /* min of hour */\n");
  strcat(wr_strval,"  float32 sec;                          /* seconds */\n");
  strcat(wr_strval,"  float64 fp_year;                      /* floating point year */\n");
  strcat(wr_strval,"  float64 fp_doy;                       /* floating point Day of YearDOY */ \n");
  strcat(wr_strval,"  float64 ACEepoch;                     /* UT time in sec since 1/1/96 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float32 flux_B[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_C[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_N[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_O[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_F[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Ne[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_Na[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Mg[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_Al[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Si[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_P[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_S[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_Cl[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Ar[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_K[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Ca[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Sc[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Ti[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_V[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Cr[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Mn[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Fe[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_Co[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_Ni[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float32 cnt_B[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_C[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_N[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_O[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_F[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Ne[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_Na[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Mg[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_Al[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Si[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_P[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_S[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_Cl[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Ar[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_K[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Ca[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Sc[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Ti[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_V[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Cr[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Mn[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Fe[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_Co[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_Ni[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float32 livetime;\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  return(0);
}
