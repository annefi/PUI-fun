/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: ace_br_5min.h,v 1.6 2002/01/22 19:13:40 ad Exp  */

#include "ace_br_5min.h"
#include "df.h"

int32 vgrp_id_acebr_5min;
static int32 vdata_id_acebr_5min;

  /* 4129 is the size of ace_br_5min.h + 1 added line */
char Vgrp_descrp_ace_br_5min_avg[4129];

/****----  init create function  ----****/

int32 init_cr_acebr_5min(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_acebr_5min();

  void print_acebr_5min_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_acebr_5min = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_acebr_5min_error("init_cr_acebr_5min -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_acebr_5min, "VG_ace_br_5min_avg"); 
  Vsetclass(vgrp_id_acebr_5min, "VG_ACE_BR_5MIN");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_ace_br_5min_avg" )) ==FAIL) {
    print_acebr_5min_error("init_cr_acebr_5min -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_acebr_5min(Vgrp_descrp_ace_br_5min_avg);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_acebr_5min_error("init_cr_acebr_5min -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_ace_br_5min_avg, sizeof(Vgrp_descrp_ace_br_5min_avg))) ==FAIL) {
    print_acebr_5min_error("init_cr_acebr_5min -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_acebr_5min = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_acebr_5min, "ace_br_5min_avg");
  VSsetclass(vdata_id_acebr_5min, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_acebr_5min, vdata_id_acebr_5min)) ==FAIL) {
    print_acebr_5min_error("init_cr_acebr_5min -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_acebr_5min, "ACE_epoch_time", DFNT_UINT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define ACE_epoch_time");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "timestr", DFNT_UINT8, (30) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define timestr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "year", DFNT_UINT16, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "fp_year", DFNT_FLOAT64, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define fp_year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "DOY", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define DOY");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "doy_curr_year", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define doy_curr_year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_rtn_r_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_rtn_r_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_rtn_t_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_rtn_t_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_rtn_n_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_rtn_n_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_rtn_theta_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_rtn_theta_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_rtn_phi_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_rtn_phi_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_gse_x_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_gse_x_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_gse_y_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_gse_y_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_gse_z_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_gse_z_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_gse_theta_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_gse_theta_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_gse_phi_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_gse_phi_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_magnitude_MAG", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_magnitude_MAG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "B_weight", DFNT_UINT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define B_weight");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "H_lo_SEP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define H_lo_SEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "H_hi_SEP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define H_hi_SEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "He_lo_SEP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define He_lo_SEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "He_hi_SEP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define He_hi_SEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "C_SEP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define C_SEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "O_SEP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define O_SEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "MgSi_SEP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define MgSi_SEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "Fe_SEP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define Fe_SEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "SEP_livetime", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define SEP_livetime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "H_EPAM", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define H_EPAM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "Ion_vlo_EPAM", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define Ion_vlo_EPAM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "Ion_lo_EPAM", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define Ion_lo_EPAM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "Ion_mid_EPAM", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define Ion_mid_EPAM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "Ion_hi_EPAM", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define Ion_hi_EPAM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "e_lo_EPAM", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define e_lo_EPAM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "e_hi_EPAM", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define e_hi_EPAM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "EPAM_livetime", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define EPAM_livetime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "H_lo_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define H_lo_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "H_hi_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define H_hi_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "He3_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define He3_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "He4_lo_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define He4_lo_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "He4_hi_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define He4_hi_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "O_lo_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define O_lo_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "O_hi_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define O_hi_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "Fe_lo_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define Fe_lo_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "Fe_hi_ULS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define Fe_hi_ULS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "ULS_livetime", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define ULS_livetime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "H_den_SWP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define H_den_SWP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "He_ratio_SWP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define He_ratio_SWP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "SW_spd_SWP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define SW_spd_SWP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "Trr_SWP", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define Trr_SWP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "SWP_weight", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define SWP_weight");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "H_lo_SIS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define H_lo_SIS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_acebr_5min, "H_hi_SIS", DFNT_FLOAT32, (1) )) {
    print_acebr_5min_error("init_cr_acebr_5min -> VSfdefine: Couldn't define H_hi_SIS");
    retval = -1;
  }

  if (VSsetfields(vdata_id_acebr_5min,"ACE_epoch_time, timestr, year, fp_year, DOY, doy_curr_year, B_rtn_r_MAG, B_rtn_t_MAG, B_rtn_n_MAG, B_rtn_theta_MAG, B_rtn_phi_MAG, B_gse_x_MAG, B_gse_y_MAG, B_gse_z_MAG, B_gse_theta_MAG, B_gse_phi_MAG, B_magnitude_MAG, B_weight, H_lo_SEP, H_hi_SEP, He_lo_SEP, He_hi_SEP, C_SEP, O_SEP, MgSi_SEP, Fe_SEP, SEP_livetime, H_EPAM, Ion_vlo_EPAM, Ion_lo_EPAM, Ion_mid_EPAM, Ion_hi_EPAM, e_lo_EPAM, e_hi_EPAM, EPAM_livetime, H_lo_ULS, H_hi_ULS, He3_ULS, He4_lo_ULS, He4_hi_ULS, O_lo_ULS, O_hi_ULS, Fe_lo_ULS, Fe_hi_ULS, ULS_livetime, H_den_SWP, He_ratio_SWP, SW_spd_SWP, Trr_SWP, SWP_weight, H_lo_SIS, H_hi_SIS")){
    print_acebr_5min_error("init_cr_acebr_5min -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_acebr_5min(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_acebr_5min(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_acebr_5min(struct ace_br_5min_avg ace_br_5min_avg_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_acebr_5min_error();
void pack_acebr_5min();

  odata = (uint8 *) malloc(sizeof(struct ace_br_5min_avg));
  pack_acebr_5min(odata, &ace_br_5min_avg_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_acebr_5min, recnum)==-1) {
		print_acebr_5min_error("write_acebr_5min -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_acebr_5min, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_acebr_5min_error("write_acebr_5min -> VSwrite: Couldn't write data.");

  memset(&ace_br_5min_avg_struc, 0, sizeof(struct ace_br_5min_avg));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_acebr_5min()
{
  VSdetach(vdata_id_acebr_5min);
  Vdetach(vgrp_id_acebr_5min);
}

/*----     init access function    ----*/

int32 init_acc_acebr_5min(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_acebr_5min_error();


  if ((vdata_ref = VSfind(hdf_fp, "ace_br_5min_avg")) <= 0 ) {
    print_acebr_5min_error("init_acc_acebr_5min -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_acebr_5min = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_acebr_5min_error("init_acc_acebr_5min -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_acebr_5min, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_acebr_5min,"ACE_epoch_time, timestr, year, fp_year, DOY, doy_curr_year, B_rtn_r_MAG, B_rtn_t_MAG, B_rtn_n_MAG, B_rtn_theta_MAG, B_rtn_phi_MAG, B_gse_x_MAG, B_gse_y_MAG, B_gse_z_MAG, B_gse_theta_MAG, B_gse_phi_MAG, B_magnitude_MAG, B_weight, H_lo_SEP, H_hi_SEP, He_lo_SEP, He_hi_SEP, C_SEP, O_SEP, MgSi_SEP, Fe_SEP, SEP_livetime, H_EPAM, Ion_vlo_EPAM, Ion_lo_EPAM, Ion_mid_EPAM, Ion_hi_EPAM, e_lo_EPAM, e_hi_EPAM, EPAM_livetime, H_lo_ULS, H_hi_ULS, He3_ULS, He4_lo_ULS, He4_hi_ULS, O_lo_ULS, O_hi_ULS, Fe_lo_ULS, Fe_hi_ULS, ULS_livetime, H_den_SWP, He_ratio_SWP, SW_spd_SWP, Trr_SWP, SWP_weight, H_lo_SIS, H_hi_SIS")) {
      print_acebr_5min_error("init_acc_acebr_5min -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_acebr_5min(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_acebr_5min(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_acebr_5min(struct ace_br_5min_avg *ace_br_5min_avg_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_acebr_5min_error();
void unpack_acebr_5min();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct ace_br_5min_avg));
  VSinquire(vdata_id_acebr_5min, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_acebr_5min, recnum_rd)==FAIL) {
          print_acebr_5min_error("read_acebr_5min -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_acebr_5min, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_acebr_5min_error("read_acebr_5min -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_acebr_5min(odata, ace_br_5min_avg_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_acebr_5min()
{
  VSdetach(vdata_id_acebr_5min);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_acebr_5min(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_acebr_5min_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_ace_br_5min_avg" )) ==FAIL)
    print_acebr_5min_error("rd_Vgrp_acebr_5min -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_acebr_5min_error("rd_Vgrp_acebr_5min -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_acebr_5min_error("rd_Vgrp_acebr_5min -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_acebr_5min_error("rd_Vgrp_acebr_5min -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_ace_br_5min_avg, HDstrlen(Vgrp_descrp_ace_br_5min_avg)) ==FAIL)
    print_acebr_5min_error("rd_Vgrp_acebr_5min -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_ace_br_5min_avg);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_acebr_5min_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_acebr_5min.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_acebr_5min(uint8 *data, struct ace_br_5min_avg *ace_br_5min_avg_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &ace_br_5min_avg_ptr->ACE_epoch_time, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->timestr[0], ((1)*(30)) );
   ptr+= ((1)*(30));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->year, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->fp_year, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->DOY, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->doy_curr_year, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_rtn_r_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_rtn_t_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_rtn_n_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_rtn_theta_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_rtn_phi_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_gse_x_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_gse_y_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_gse_z_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_gse_theta_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_gse_phi_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_magnitude_MAG, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->B_weight, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->H_lo_SEP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->H_hi_SEP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->He_lo_SEP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->He_hi_SEP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->C_SEP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->O_SEP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->MgSi_SEP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->Fe_SEP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->SEP_livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->H_EPAM, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->Ion_vlo_EPAM, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->Ion_lo_EPAM, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->Ion_mid_EPAM, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->Ion_hi_EPAM, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->e_lo_EPAM, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->e_hi_EPAM, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->EPAM_livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->H_lo_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->H_hi_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->He3_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->He4_lo_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->He4_hi_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->O_lo_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->O_hi_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->Fe_lo_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->Fe_hi_ULS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->ULS_livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->H_den_SWP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->He_ratio_SWP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->SW_spd_SWP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->Trr_SWP, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->SWP_weight, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->H_lo_SIS, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ace_br_5min_avg_ptr->H_hi_SIS, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_acebr_5min(uint8 *data, struct ace_br_5min_avg *ace_br_5min_avg_ptr)
{
int32 ptr=0;

   memcpy(&ace_br_5min_avg_ptr->ACE_epoch_time, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->timestr[0], data+ptr,  ((1)*(30)) );
   ptr+= ((1)*(30));
   memcpy(&ace_br_5min_avg_ptr->year, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&ace_br_5min_avg_ptr->fp_year, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&ace_br_5min_avg_ptr->DOY, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->doy_curr_year, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_rtn_r_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_rtn_t_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_rtn_n_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_rtn_theta_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_rtn_phi_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_gse_x_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_gse_y_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_gse_z_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_gse_theta_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_gse_phi_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_magnitude_MAG, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->B_weight, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->H_lo_SEP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->H_hi_SEP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->He_lo_SEP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->He_hi_SEP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->C_SEP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->O_SEP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->MgSi_SEP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->Fe_SEP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->SEP_livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->H_EPAM, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->Ion_vlo_EPAM, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->Ion_lo_EPAM, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->Ion_mid_EPAM, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->Ion_hi_EPAM, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->e_lo_EPAM, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->e_hi_EPAM, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->EPAM_livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->H_lo_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->H_hi_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->He3_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->He4_lo_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->He4_hi_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->O_lo_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->O_hi_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->Fe_lo_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->Fe_hi_ULS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->ULS_livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->H_den_SWP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->He_ratio_SWP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->SW_spd_SWP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->Trr_SWP, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->SWP_weight, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->H_lo_SIS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ace_br_5min_avg_ptr->H_hi_SIS, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_acebr_5min() {return(vgrp_id_acebr_5min);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_acebr_5min(char *wr_strval)
{
  strcpy(wr_strval, "The file 'ace_br_5min.h' is shown below, it was used to create the data in the Vgroup named 'VG_ace_br_5min_avg'.\n\n");
  strcat(wr_strval,"/* Id: ace_br_5min.h,v 1.6 2002/01/22 19:13:40 ad Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct ace_br_5min_avg {\n");
  strcat(wr_strval,"    uint32  ACE_epoch_time;  /* time at start of bin */\n");
  strcat(wr_strval,"    uint8   timestr[30];     /* time at start of bin, ascii string */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    uint16  year;          /* year at start of bin */\n");
  strcat(wr_strval,"    float64 fp_year;          /* floating_pt year at start of bin */\n");
  strcat(wr_strval,"    float32 DOY;          /* day of year at start of bin */\n");
  strcat(wr_strval,"    float32 doy_curr_year; /* day of year at start of bin, relative */\n");
  strcat(wr_strval,"                           /* to the current year */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    float32 B_rtn_r_MAG;  /* AVG Magnetic field, RTN coordinate, R component */\n");
  strcat(wr_strval,"    float32 B_rtn_t_MAG;  /* AVG Magnetic field, RTN coordinate, T component */\n");
  strcat(wr_strval,"    float32 B_rtn_n_MAG;  /* AVG Magnetic field, RTN coordinate, N component */\n");
  strcat(wr_strval,"    float32 B_rtn_theta_MAG; /* AVG Magnetic field, RTN coordinate, latitude*/\n");
  strcat(wr_strval,"    float32 B_rtn_phi_MAG; /* AVG Magnetic field, RTN coordinate, longitude */\n");
  strcat(wr_strval,"    float32 B_gse_x_MAG;  /* AVG Magnetic field, GSE coordinate, R component */\n");
  strcat(wr_strval,"    float32 B_gse_y_MAG;  /* AVG Magnetic field, GSE coordinate, T component */\n");
  strcat(wr_strval,"    float32 B_gse_z_MAG;  /* AVG Magnetic field, GSE coordinate, N component */\n");
  strcat(wr_strval,"    float32 B_gse_theta_MAG; /* AVG Magnetic field, GSE coordinate, latitude*/\n");
  strcat(wr_strval,"    float32 B_gse_phi_MAG; /* AVG Magnetic field, GSE coordinate, longitude */\n");
  strcat(wr_strval,"    float32 B_magnitude_MAG;  /* AVG Magnetic field, magnitude <|B|> */\n");
  strcat(wr_strval,"    uint32  B_weight;     /* number of vectors used in this average */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    float32 H_lo_SEP;    /* H rate, 0.1-0.8 Mev/n from SEPICA */\n");
  strcat(wr_strval,"    float32 H_hi_SEP;    /* H rate, 0.8-6.0 Mev/n from SEPICA */\n");
  strcat(wr_strval,"    float32 He_lo_SEP;   /* He rate, 0.025-0.75 Mev/n from SEPICA */\n");
  strcat(wr_strval,"    float32 He_hi_SEP;   /* He rate, 0.75-6.0 Mev/n from SEPICA */\n");
  strcat(wr_strval,"    float32 C_SEP;       /* C rate, 1.5-10.7 Mev/n from SEPICA */\n");
  strcat(wr_strval,"    float32 O_SEP;       /* O rate, 1.25-12.6 Mev/n from SEPICA */\n");
  strcat(wr_strval,"    float32 MgSi_SEP;    /* MgSi rate, 0.77-11.54 Mev/n from SEPICA */\n");
  strcat(wr_strval,"    float32 Fe_SEP;      /* Fe rate, 0.36-5.36 Mev/n from SEPICA */\n");
  strcat(wr_strval,"    float32 SEP_livetime; /* SEPICA livetime, if 0 ignore SEP data */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    float32 H_EPAM;      /* H rate,  0.761-0.122 Mev from EPAM */\n");
  strcat(wr_strval,"    float32 Ion_vlo_EPAM; /* Ion rate, 47-65 keV from EPAM */\n");
  strcat(wr_strval,"    float32 Ion_lo_EPAM; /* Ion rate, 112-187 keV from EPAM */\n");
  strcat(wr_strval,"    float32 Ion_mid_EPAM; /* Ion rate, 310-580 keV from EPAM */\n");
  strcat(wr_strval,"    float32 Ion_hi_EPAM; /* Ion rate, 1060-1910 KeV from EPAM */\n");
  strcat(wr_strval,"    float32 e_lo_EPAM;   /* electron rate, 38-53 keV from EPAM */\n");
  strcat(wr_strval,"    float32 e_hi_EPAM;  /* electron rate, 175-315 keV from EPAM */\n");
  strcat(wr_strval,"    float32 EPAM_livetime; /* EPAM livetime. if 0 ignore EPM data */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    float32 H_lo_ULS;    /* H rate, 0.16-0.32 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 H_hi_ULS;    /* H rate, 0.64-1.28 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 He3_ULS;  /* He3 rate, 0.64-1.28 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 He4_lo_ULS;   /* He4 rate, 0.08-0.113 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 He4_hi_ULS;  /* He4 rate, 0.64-0.905 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 O_lo_ULS;    /* O rate, 0.09-0.160 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 O_hi_ULS;    /* O rate,  0.64-1.28 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 Fe_lo_ULS;   /* Fe rate, 0.08-0.160 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 Fe_hi_ULS;   /* Fe rate, 0.64-0.905 Mev/n from ULEIS */\n");
  strcat(wr_strval,"    float32 ULS_livetime; /* ULEIS livetime. if 0 ignore ULS data */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"		/* Negative values are non-physical */\n");
  strcat(wr_strval,"    float32 H_den_SWP;     /* proton number density, cm^-3, from SWEPAM */\n");
  strcat(wr_strval,"    float32 He_ratio_SWP;  /* nHe++/nH+, from SWEPAM */\n");
  strcat(wr_strval,"    float32 SW_spd_SWP;    /* Solar Wind bulk (H) speed from SWEPAM */\n");
  strcat(wr_strval,"    float32 Trr_SWP;       /* (1,1) component of temp tensor along */\n");
  strcat(wr_strval,"			   /* radial direction from SWEPAM */\n");
  strcat(wr_strval,"    float32 SWP_weight;    /* Number of values in average */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   /* Only SIS protons have 5-min averages */\n");
  strcat(wr_strval,"   float32 H_lo_SIS;       /* H rate , > 10 Mev/n from SIS */\n");
  strcat(wr_strval,"   float32 H_hi_SIS;       /* H rate , > 30 Mev/n from SIS */\n");
  strcat(wr_strval,"	   \n");
  strcat(wr_strval,"   /* No 5min averages from CRIS or SWICS */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
