/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: cris_level2_data_abundant_256s.h,v 1.1 2000/08/01 23:36:09 asc Exp  */

#include "cris_level2_data_abundant_256s.h"
#include "df.h"

int32 vgrp_id_cris_level2_data_abundant_256s;
static int32 vdata_id_cris_level2_data_abundant_256s;

  /* 1806 is the size of cris_level2_data_abundant_256s.h + 1 added line */
char Vgrp_descrp_CRIS_data_abundant_256s[1806];

/****----  init create function  ----****/

int32 init_cr_cris_level2_data_abundant_256s(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_cris_level2_data_abundant_256s();

  void print_cris_level2_data_abundant_256s_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_cris_level2_data_abundant_256s = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_cris_level2_data_abundant_256s, "VG_CRIS_data_abundant_256s"); 
  Vsetclass(vgrp_id_cris_level2_data_abundant_256s, "VG_CRIS_LEVEL2_DATA_ABUNDANT_256S");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_CRIS_data_abundant_256s" )) ==FAIL) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_cris_level2_data_abundant_256s(Vgrp_descrp_CRIS_data_abundant_256s);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_CRIS_data_abundant_256s, sizeof(Vgrp_descrp_CRIS_data_abundant_256s))) ==FAIL) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_cris_level2_data_abundant_256s = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_cris_level2_data_abundant_256s, "CRIS_data_abundant_256s");
  VSsetclass(vdata_id_cris_level2_data_abundant_256s, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_cris_level2_data_abundant_256s, vdata_id_cris_level2_data_abundant_256s)) ==FAIL) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "year", DFNT_INT32, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "day", DFNT_INT32, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define day");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "hr", DFNT_INT32, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define hr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "min", DFNT_INT32, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "sec", DFNT_FLOAT32, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define sec");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "fp_year", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define fp_year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "fp_doy", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define fp_doy");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "ACEepoch", DFNT_FLOAT64, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define ACEepoch");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "flux_abundant_C", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define flux_abundant_C");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "flux_abundant_N", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define flux_abundant_N");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "flux_abundant_O", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define flux_abundant_O");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "flux_abundant_Ne", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define flux_abundant_Ne");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "flux_abundant_Mg", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define flux_abundant_Mg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "flux_abundant_Si", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define flux_abundant_Si");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "flux_abundant_S", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define flux_abundant_S");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "flux_abundant_Fe", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define flux_abundant_Fe");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "cnt_abundant_C", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define cnt_abundant_C");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "cnt_abundant_N", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define cnt_abundant_N");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "cnt_abundant_O", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define cnt_abundant_O");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "cnt_abundant_Ne", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define cnt_abundant_Ne");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "cnt_abundant_Mg", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define cnt_abundant_Mg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "cnt_abundant_Si", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define cnt_abundant_Si");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "cnt_abundant_S", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define cnt_abundant_S");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "cnt_abundant_Fe", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define cnt_abundant_Fe");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_data_abundant_256s, "livetime", DFNT_FLOAT32, (1) )) {
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSfdefine: Couldn't define livetime");
    retval = -1;
  }

  if (VSsetfields(vdata_id_cris_level2_data_abundant_256s,"year, day, hr, min, sec, fp_year, fp_doy, ACEepoch, flux_abundant_C, flux_abundant_N, flux_abundant_O, flux_abundant_Ne, flux_abundant_Mg, flux_abundant_Si, flux_abundant_S, flux_abundant_Fe, cnt_abundant_C, cnt_abundant_N, cnt_abundant_O, cnt_abundant_Ne, cnt_abundant_Mg, cnt_abundant_Si, cnt_abundant_S, cnt_abundant_Fe, livetime")){
    print_cris_level2_data_abundant_256s_error("init_cr_cris_level2_data_abundant_256s -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_cris_level2_data_abundant_256s(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_cris_level2_data_abundant_256s(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_cris_level2_data_abundant_256s(struct CRIS_data_abundant_256s CRIS_data_abundant_256s_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_cris_level2_data_abundant_256s_error();
void pack_cris_level2_data_abundant_256s();

  odata = (uint8 *) malloc(sizeof(struct CRIS_data_abundant_256s));
  pack_cris_level2_data_abundant_256s(odata, &CRIS_data_abundant_256s_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_cris_level2_data_abundant_256s, recnum)==-1) {
		print_cris_level2_data_abundant_256s_error("write_cris_level2_data_abundant_256s -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_cris_level2_data_abundant_256s, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_cris_level2_data_abundant_256s_error("write_cris_level2_data_abundant_256s -> VSwrite: Couldn't write data.");

  memset(&CRIS_data_abundant_256s_struc, 0, sizeof(struct CRIS_data_abundant_256s));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_cris_level2_data_abundant_256s()
{
  VSdetach(vdata_id_cris_level2_data_abundant_256s);
  Vdetach(vgrp_id_cris_level2_data_abundant_256s);
}

/*----     init access function    ----*/

int32 init_acc_cris_level2_data_abundant_256s(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_cris_level2_data_abundant_256s_error();


  if ((vdata_ref = VSfind(hdf_fp, "CRIS_data_abundant_256s")) <= 0 ) {
    print_cris_level2_data_abundant_256s_error("init_acc_cris_level2_data_abundant_256s -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_cris_level2_data_abundant_256s = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_cris_level2_data_abundant_256s_error("init_acc_cris_level2_data_abundant_256s -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_cris_level2_data_abundant_256s, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_cris_level2_data_abundant_256s,"year, day, hr, min, sec, fp_year, fp_doy, ACEepoch, flux_abundant_C, flux_abundant_N, flux_abundant_O, flux_abundant_Ne, flux_abundant_Mg, flux_abundant_Si, flux_abundant_S, flux_abundant_Fe, cnt_abundant_C, cnt_abundant_N, cnt_abundant_O, cnt_abundant_Ne, cnt_abundant_Mg, cnt_abundant_Si, cnt_abundant_S, cnt_abundant_Fe, livetime")) {
      print_cris_level2_data_abundant_256s_error("init_acc_cris_level2_data_abundant_256s -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_cris_level2_data_abundant_256s(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_cris_level2_data_abundant_256s(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_cris_level2_data_abundant_256s(struct CRIS_data_abundant_256s *CRIS_data_abundant_256s_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_cris_level2_data_abundant_256s_error();
void unpack_cris_level2_data_abundant_256s();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct CRIS_data_abundant_256s));
  VSinquire(vdata_id_cris_level2_data_abundant_256s, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_cris_level2_data_abundant_256s, recnum_rd)==FAIL) {
          print_cris_level2_data_abundant_256s_error("read_cris_level2_data_abundant_256s -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_cris_level2_data_abundant_256s, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_cris_level2_data_abundant_256s_error("read_cris_level2_data_abundant_256s -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_cris_level2_data_abundant_256s(odata, CRIS_data_abundant_256s_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_cris_level2_data_abundant_256s()
{
  VSdetach(vdata_id_cris_level2_data_abundant_256s);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_cris_level2_data_abundant_256s(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_cris_level2_data_abundant_256s_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_CRIS_data_abundant_256s" )) ==FAIL)
    print_cris_level2_data_abundant_256s_error("rd_Vgrp_cris_level2_data_abundant_256s -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_cris_level2_data_abundant_256s_error("rd_Vgrp_cris_level2_data_abundant_256s -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_cris_level2_data_abundant_256s_error("rd_Vgrp_cris_level2_data_abundant_256s -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_cris_level2_data_abundant_256s_error("rd_Vgrp_cris_level2_data_abundant_256s -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_CRIS_data_abundant_256s, HDstrlen(Vgrp_descrp_CRIS_data_abundant_256s)) ==FAIL)
    print_cris_level2_data_abundant_256s_error("rd_Vgrp_cris_level2_data_abundant_256s -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_CRIS_data_abundant_256s);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_cris_level2_data_abundant_256s_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_cris_level2_data_abundant_256s.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_cris_level2_data_abundant_256s(uint8 *data, struct CRIS_data_abundant_256s *CRIS_data_abundant_256s_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->year, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->day, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->hr, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->min, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->sec, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->fp_year, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->fp_doy, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->ACEepoch, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->flux_abundant_C[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->flux_abundant_N[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->flux_abundant_O[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->flux_abundant_Ne[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->flux_abundant_Mg[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->flux_abundant_Si[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->flux_abundant_S[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->flux_abundant_Fe[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->cnt_abundant_C[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->cnt_abundant_N[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->cnt_abundant_O[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->cnt_abundant_Ne[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->cnt_abundant_Mg[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->cnt_abundant_Si[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->cnt_abundant_S[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->cnt_abundant_Fe[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_data_abundant_256s_ptr->livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_cris_level2_data_abundant_256s(uint8 *data, struct CRIS_data_abundant_256s *CRIS_data_abundant_256s_ptr)
{
int32 ptr=0;

   memcpy(&CRIS_data_abundant_256s_ptr->year, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_abundant_256s_ptr->day, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_abundant_256s_ptr->hr, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_abundant_256s_ptr->min, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_abundant_256s_ptr->sec, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&CRIS_data_abundant_256s_ptr->fp_year, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_abundant_256s_ptr->fp_doy, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_abundant_256s_ptr->ACEepoch, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&CRIS_data_abundant_256s_ptr->flux_abundant_C[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->flux_abundant_N[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->flux_abundant_O[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->flux_abundant_Ne[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->flux_abundant_Mg[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->flux_abundant_Si[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->flux_abundant_S[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->flux_abundant_Fe[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->cnt_abundant_C[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->cnt_abundant_N[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->cnt_abundant_O[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->cnt_abundant_Ne[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->cnt_abundant_Mg[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->cnt_abundant_Si[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->cnt_abundant_S[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->cnt_abundant_Fe[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_data_abundant_256s_ptr->livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_cris_level2_data_abundant_256s() {return(vgrp_id_cris_level2_data_abundant_256s);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_cris_level2_data_abundant_256s(char *wr_strval)
{
  strcpy(wr_strval, "The file 'cris_level2_data_abundant_256s.h' is shown below, it was used to create the data in the Vgroup named 'VG_CRIS_data_abundant_256s'.\n\n");
  strcat(wr_strval,"/* Id: cris_level2_data_abundant_256s.h,v 1.1 2000/08/01 23:36:09 asc Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"cris_sizes.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* abundant elements */\n");
  strcat(wr_strval,"struct CRIS_data_abundant_256s {\n");
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
  strcat(wr_strval,"  float32 flux_abundant_C[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_abundant_N[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_abundant_O[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_abundant_Ne[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_abundant_Mg[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_abundant_Si[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_abundant_S[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 flux_abundant_Fe[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float32 cnt_abundant_C[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_abundant_N[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_abundant_O[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_abundant_Ne[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_abundant_Mg[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_abundant_Si[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_abundant_S[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 cnt_abundant_Fe[NUMBER_OF_ENERGY_LEVELS];\n");
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
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  return(0);
}
