/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: cris_level2_data_rare_1024s.h,v 1.1 2000/08/01 23:44:59 asc Exp  */

#include "cris_level2_data_rare_1024s.h"
#include "df.h"

int32 vgrp_id_cris_level2_data_rare_1024s;
static int32 vdata_id_cris_level2_data_rare_1024s;

  /* 2536 is the size of cris_level2_data_rare_1024s.h + 1 added line */
char Vgrp_descrp_CRIS_data_rare_1024s[2536];

/****----  init create function  ----****/

int32 init_cr_cris_level2_data_rare_1024s(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_cris_level2_data_rare_1024s();

  void print_cris_level2_data_rare_1024s_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_cris_level2_data_rare_1024s = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_cris_level2_data_rare_1024s, "VG_CRIS_data_rare_1024s"); 
  Vsetclass(vgrp_id_cris_level2_data_rare_1024s, "VG_CRIS_LEVEL2_DATA_RARE_1024S");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_CRIS_data_rare_1024s" )) ==FAIL) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_cris_level2_data_rare_1024s(Vgrp_descrp_CRIS_data_rare_1024s);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_CRIS_data_rare_1024s, sizeof(Vgrp_descrp_CRIS_data_rare_1024s))) ==FAIL) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_cris_level2_data_rare_1024s = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_cris_level2_data_rare_1024s, "CRIS_data_rare_1024s");
  VSsetclass(vdata_id_cris_level2_data_rare_1024s, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_cris_level2_data_rare_1024s, vdata_id_cris_level2_data_rare_1024s)) ==FAIL) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "year", DFNT_INT32, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "day", DFNT_INT32, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define day");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "hr", DFNT_INT32, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define hr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "min", DFNT_INT32, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "sec", DFNT_FLOAT32, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define sec");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "fp_year", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define fp_year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "fp_doy", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define fp_doy");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "ACEepoch", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define ACEepoch");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_B", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_B");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_F", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_F");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Na", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Na");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Al", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Al");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_P", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_P");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Cl", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Cl");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Ar", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Ar");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_K", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_K");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Ca", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Ca");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Sc", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Sc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Ti", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Ti");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_V", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Cr", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Cr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Mn", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Mn");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Co", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Co");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "flux_rare_Ni", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define flux_rare_Ni");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_B", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_B");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_F", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_F");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Na", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Na");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Al", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Al");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_P", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_P");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Cl", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Cl");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Ar", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Ar");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_K", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_K");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Ca", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Ca");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Sc", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Sc");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Ti", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Ti");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_V", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Cr", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Cr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Mn", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Mn");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Co", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Co");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "cnt_rare_Ni", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define cnt_rare_Ni");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_rare_1024s, "livetime", DFNT_FLOAT32, (1) )) {
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSfdefine: Couldn't define livetime");
    retval = -1;
  }

  if (VSsetfields(vdata_id_cris_level2_data_rare_1024s,"year, day, hr, min, sec, fp_year, fp_doy, ACEepoch, flux_rare_B, flux_rare_F, flux_rare_Na, flux_rare_Al, flux_rare_P, flux_rare_Cl, flux_rare_Ar, flux_rare_K, flux_rare_Ca, flux_rare_Sc, flux_rare_Ti, flux_rare_V, flux_rare_Cr, flux_rare_Mn, flux_rare_Co, flux_rare_Ni, cnt_rare_B, cnt_rare_F, cnt_rare_Na, cnt_rare_Al, cnt_rare_P, cnt_rare_Cl, cnt_rare_Ar, cnt_rare_K, cnt_rare_Ca, cnt_rare_Sc, cnt_rare_Ti, cnt_rare_V, cnt_rare_Cr, cnt_rare_Mn, cnt_rare_Co, cnt_rare_Ni, livetime")){
    print_cris_level2_data_rare_1024s_error("init_cr_cris_level2_data_rare_1024s -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_cris_level2_data_rare_1024s(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_cris_level2_data_rare_1024s(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_cris_level2_data_rare_1024s(struct CRIS_data_rare_1024s CRIS_data_rare_1024s_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_cris_level2_data_rare_1024s_error();
void pack_cris_level2_data_rare_1024s();

  odata = (uint8 *) malloc(sizeof(struct CRIS_data_rare_1024s));
  pack_cris_level2_data_rare_1024s(odata, &CRIS_data_rare_1024s_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_cris_level2_data_rare_1024s, recnum)==-1) {
		print_cris_level2_data_rare_1024s_error("write_cris_level2_data_rare_1024s -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_cris_level2_data_rare_1024s, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_cris_level2_data_rare_1024s_error("write_cris_level2_data_rare_1024s -> VSwrite: Couldn't write data.");

  memset(&CRIS_data_rare_1024s_struc, 0, sizeof(struct CRIS_data_rare_1024s));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_cris_level2_data_rare_1024s()
{
  VSdetach(vdata_id_cris_level2_data_rare_1024s);
  Vdetach(vgrp_id_cris_level2_data_rare_1024s);
}

/*----     init access function    ----*/

int32 init_acc_cris_level2_data_rare_1024s(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_cris_level2_data_rare_1024s_error();


  if ((vdata_ref = VSfind(hdf_fp, "CRIS_data_rare_1024s")) <= 0 ) {
    print_cris_level2_data_rare_1024s_error("init_acc_cris_level2_data_rare_1024s -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_cris_level2_data_rare_1024s = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_cris_level2_data_rare_1024s_error("init_acc_cris_level2_data_rare_1024s -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_cris_level2_data_rare_1024s, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_cris_level2_data_rare_1024s,"year, day, hr, min, sec, fp_year, fp_doy, ACEepoch, flux_rare_B, flux_rare_F, flux_rare_Na, flux_rare_Al, flux_rare_P, flux_rare_Cl, flux_rare_Ar, flux_rare_K, flux_rare_Ca, flux_rare_Sc, flux_rare_Ti, flux_rare_V, flux_rare_Cr, flux_rare_Mn, flux_rare_Co, flux_rare_Ni, cnt_rare_B, cnt_rare_F, cnt_rare_Na, cnt_rare_Al, cnt_rare_P, cnt_rare_Cl, cnt_rare_Ar, cnt_rare_K, cnt_rare_Ca, cnt_rare_Sc, cnt_rare_Ti, cnt_rare_V, cnt_rare_Cr, cnt_rare_Mn, cnt_rare_Co, cnt_rare_Ni, livetime")) {
      print_cris_level2_data_rare_1024s_error("init_acc_cris_level2_data_rare_1024s -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_cris_level2_data_rare_1024s(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_cris_level2_data_rare_1024s(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_cris_level2_data_rare_1024s(struct CRIS_data_rare_1024s *CRIS_data_rare_1024s_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_cris_level2_data_rare_1024s_error();
void unpack_cris_level2_data_rare_1024s();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct CRIS_data_rare_1024s));
  VSinquire(vdata_id_cris_level2_data_rare_1024s, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_cris_level2_data_rare_1024s, recnum_rd)==FAIL) {
          print_cris_level2_data_rare_1024s_error("read_cris_level2_data_rare_1024s -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_cris_level2_data_rare_1024s, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_cris_level2_data_rare_1024s_error("read_cris_level2_data_rare_1024s -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_cris_level2_data_rare_1024s(odata, CRIS_data_rare_1024s_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_cris_level2_data_rare_1024s()
{
  VSdetach(vdata_id_cris_level2_data_rare_1024s);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_cris_level2_data_rare_1024s(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_cris_level2_data_rare_1024s_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_CRIS_data_rare_1024s" )) ==FAIL)
    print_cris_level2_data_rare_1024s_error("rd_Vgrp_cris_level2_data_rare_1024s -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_cris_level2_data_rare_1024s_error("rd_Vgrp_cris_level2_data_rare_1024s -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_cris_level2_data_rare_1024s_error("rd_Vgrp_cris_level2_data_rare_1024s -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_cris_level2_data_rare_1024s_error("rd_Vgrp_cris_level2_data_rare_1024s -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_CRIS_data_rare_1024s, HDstrlen(Vgrp_descrp_CRIS_data_rare_1024s)) ==FAIL)
    print_cris_level2_data_rare_1024s_error("rd_Vgrp_cris_level2_data_rare_1024s -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_CRIS_data_rare_1024s);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_cris_level2_data_rare_1024s_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_cris_level2_data_rare_1024s.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_cris_level2_data_rare_1024s(uint8 *data, struct CRIS_data_rare_1024s *CRIS_data_rare_1024s_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->year, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->day, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->hr, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->min, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->sec, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->fp_year, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->fp_doy, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->ACEepoch, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_B[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_F[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Na[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Al[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_P[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Cl[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Ar[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_K[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Ca[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Sc[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Ti[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_V[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Cr[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Mn[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Co[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->flux_rare_Ni[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_B[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_F[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Na[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Al[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_P[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Cl[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Ar[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_K[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Ca[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Sc[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Ti[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_V[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Cr[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Mn[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Co[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->cnt_rare_Ni[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_rare_1024s_ptr->livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_cris_level2_data_rare_1024s(uint8 *data, struct CRIS_data_rare_1024s *CRIS_data_rare_1024s_ptr)
{
int32 ptr=0;

   memcpy(&CRIS_data_rare_1024s_ptr->year, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_rare_1024s_ptr->day, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_rare_1024s_ptr->hr, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_rare_1024s_ptr->min, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_rare_1024s_ptr->sec, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_rare_1024s_ptr->fp_year, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_rare_1024s_ptr->fp_doy, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_rare_1024s_ptr->ACEepoch, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_B[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_F[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Na[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Al[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_P[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Cl[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Ar[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_K[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Ca[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Sc[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Ti[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_V[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Cr[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Mn[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Co[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->flux_rare_Ni[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_B[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_F[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Na[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Al[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_P[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Cl[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Ar[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_K[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Ca[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Sc[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Ti[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_V[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Cr[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Mn[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Co[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->cnt_rare_Ni[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_rare_1024s_ptr->livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_cris_level2_data_rare_1024s() {return(vgrp_id_cris_level2_data_rare_1024s);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_cris_level2_data_rare_1024s(char *wr_strval)
{
  strcpy(wr_strval, "The file 'cris_level2_data_rare_1024s.h' is shown below, it was used to create the data in the Vgroup named 'VG_CRIS_data_rare_1024s'.\n\n");
  strcat(wr_strval,"/* Id: cris_level2_data_rare_1024s.h,v 1.1 2000/08/01 23:44:59 asc Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"cris_sizes.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* rare elements */\n");
  strcat(wr_strval,"struct CRIS_data_rare_1024s {\n");
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
  strcat(wr_strval,"  float32 flux_rare_B[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_F[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Na[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Al[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_P[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Cl[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Ar[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_K[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Ca[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Sc[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Ti[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_V[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Cr[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Mn[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Co[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 flux_rare_Ni[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float32 cnt_rare_B[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_F[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Na[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Al[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_P[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Cl[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Ar[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_K[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Ca[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Sc[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Ti[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_V[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Cr[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Mn[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Co[NUMBER_OF_ENERGY_LEVELS]; \n");
  strcat(wr_strval,"  float32 cnt_rare_Ni[NUMBER_OF_ENERGY_LEVELS]; \n");
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
  strcat(wr_strval,"\n");
  return(0);
}
