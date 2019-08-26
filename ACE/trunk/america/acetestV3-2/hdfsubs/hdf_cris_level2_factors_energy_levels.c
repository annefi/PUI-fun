/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: cris_level2_factors_energy_levels.h,v 1.1 2000/08/01 23:49:14 asc Exp  */

#include "cris_level2_factors_energy_levels.h"
#include "df.h"

int32 vgrp_id_cris_level2_factors_energy_levels;
static int32 vdata_id_cris_level2_factors_energy_levels;

  /* 617 is the size of cris_level2_factors_energy_levels.h + 1 added line */
char Vgrp_descrp_CRIS_factors_energy_levels[617];

/****----  init create function  ----****/

int32 init_cr_cris_level2_factors_energy_levels(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_cris_level2_factors_energy_levels();

  void print_cris_level2_factors_energy_levels_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_cris_level2_factors_energy_levels = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_cris_level2_factors_energy_levels, "VG_CRIS_factors_energy_levels"); 
  Vsetclass(vgrp_id_cris_level2_factors_energy_levels, "VG_CRIS_LEVEL2_FACTORS_ENERGY_LEVELS");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_CRIS_factors_energy_levels" )) ==FAIL) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_cris_level2_factors_energy_levels(Vgrp_descrp_CRIS_factors_energy_levels);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_CRIS_factors_energy_levels, sizeof(Vgrp_descrp_CRIS_factors_energy_levels))) ==FAIL) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_cris_level2_factors_energy_levels = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_cris_level2_factors_energy_levels, "CRIS_factors_energy_levels");
  VSsetclass(vdata_id_cris_level2_factors_energy_levels, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_cris_level2_factors_energy_levels, vdata_id_cris_level2_factors_energy_levels)) ==FAIL) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_cris_level2_factors_energy_levels, "z_number", DFNT_UINT8, (1) )) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> VSfdefine: Couldn't define z_number");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_factors_energy_levels, "energy_min", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> VSfdefine: Couldn't define energy_min");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_factors_energy_levels, "energy_max", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> VSfdefine: Couldn't define energy_max");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_factors_energy_levels, "geo_factor", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> VSfdefine: Couldn't define geo_factor");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_factors_energy_levels, "spallation", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> VSfdefine: Couldn't define spallation");
    retval = -1;
  }
  if (VSfdefine(vdata_id_cris_level2_factors_energy_levels, "SOFT", DFNT_FLOAT32, (NUMBER_OF_ENERGY_LEVELS) )) {
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> VSfdefine: Couldn't define SOFT");
    retval = -1;
  }

  if (VSsetfields(vdata_id_cris_level2_factors_energy_levels,"z_number, energy_min, energy_max, geo_factor, spallation, SOFT")){
    print_cris_level2_factors_energy_levels_error("init_cr_cris_level2_factors_energy_levels -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_cris_level2_factors_energy_levels(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_cris_level2_factors_energy_levels(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_cris_level2_factors_energy_levels(struct CRIS_factors_energy_levels CRIS_factors_energy_levels_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_cris_level2_factors_energy_levels_error();
void pack_cris_level2_factors_energy_levels();

  odata = (uint8 *) malloc(sizeof(struct CRIS_factors_energy_levels));
  pack_cris_level2_factors_energy_levels(odata, &CRIS_factors_energy_levels_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_cris_level2_factors_energy_levels, recnum)==-1) {
		print_cris_level2_factors_energy_levels_error("write_cris_level2_factors_energy_levels -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_cris_level2_factors_energy_levels, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_cris_level2_factors_energy_levels_error("write_cris_level2_factors_energy_levels -> VSwrite: Couldn't write data.");

  memset(&CRIS_factors_energy_levels_struc, 0, sizeof(struct CRIS_factors_energy_levels));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_cris_level2_factors_energy_levels()
{
  VSdetach(vdata_id_cris_level2_factors_energy_levels);
  Vdetach(vgrp_id_cris_level2_factors_energy_levels);
}

/*----     init access function    ----*/

int32 init_acc_cris_level2_factors_energy_levels(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_cris_level2_factors_energy_levels_error();


  if ((vdata_ref = VSfind(hdf_fp, "CRIS_factors_energy_levels")) <= 0 ) {
    print_cris_level2_factors_energy_levels_error("init_acc_cris_level2_factors_energy_levels -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_cris_level2_factors_energy_levels = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_cris_level2_factors_energy_levels_error("init_acc_cris_level2_factors_energy_levels -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_cris_level2_factors_energy_levels, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_cris_level2_factors_energy_levels,"z_number, energy_min, energy_max, geo_factor, spallation, SOFT")) {
      print_cris_level2_factors_energy_levels_error("init_acc_cris_level2_factors_energy_levels -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_cris_level2_factors_energy_levels(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_cris_level2_factors_energy_levels(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_cris_level2_factors_energy_levels(struct CRIS_factors_energy_levels *CRIS_factors_energy_levels_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_cris_level2_factors_energy_levels_error();
void unpack_cris_level2_factors_energy_levels();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct CRIS_factors_energy_levels));
  VSinquire(vdata_id_cris_level2_factors_energy_levels, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_cris_level2_factors_energy_levels, recnum_rd)==FAIL) {
          print_cris_level2_factors_energy_levels_error("read_cris_level2_factors_energy_levels -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_cris_level2_factors_energy_levels, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_cris_level2_factors_energy_levels_error("read_cris_level2_factors_energy_levels -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_cris_level2_factors_energy_levels(odata, CRIS_factors_energy_levels_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_cris_level2_factors_energy_levels()
{
  VSdetach(vdata_id_cris_level2_factors_energy_levels);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_cris_level2_factors_energy_levels(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_cris_level2_factors_energy_levels_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_CRIS_factors_energy_levels" )) ==FAIL)
    print_cris_level2_factors_energy_levels_error("rd_Vgrp_cris_level2_factors_energy_levels -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_cris_level2_factors_energy_levels_error("rd_Vgrp_cris_level2_factors_energy_levels -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_cris_level2_factors_energy_levels_error("rd_Vgrp_cris_level2_factors_energy_levels -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_cris_level2_factors_energy_levels_error("rd_Vgrp_cris_level2_factors_energy_levels -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_CRIS_factors_energy_levels, HDstrlen(Vgrp_descrp_CRIS_factors_energy_levels)) ==FAIL)
    print_cris_level2_factors_energy_levels_error("rd_Vgrp_cris_level2_factors_energy_levels -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_CRIS_factors_energy_levels);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_cris_level2_factors_energy_levels_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_cris_level2_factors_energy_levels.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_cris_level2_factors_energy_levels(uint8 *data, struct CRIS_factors_energy_levels *CRIS_factors_energy_levels_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &CRIS_factors_energy_levels_ptr->z_number, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &CRIS_factors_energy_levels_ptr->energy_min[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_factors_energy_levels_ptr->energy_max[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_factors_energy_levels_ptr->geo_factor[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_factors_energy_levels_ptr->spallation[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(data+ptr, &CRIS_factors_energy_levels_ptr->SOFT[0], ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
}

/*----   unpack function    ----*/

void unpack_cris_level2_factors_energy_levels(uint8 *data, struct CRIS_factors_energy_levels *CRIS_factors_energy_levels_ptr)
{
int32 ptr=0;

   memcpy(&CRIS_factors_energy_levels_ptr->z_number, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&CRIS_factors_energy_levels_ptr->energy_min[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_factors_energy_levels_ptr->energy_max[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_factors_energy_levels_ptr->geo_factor[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_factors_energy_levels_ptr->spallation[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
   memcpy(&CRIS_factors_energy_levels_ptr->SOFT[0], data+ptr,  ((4)*(NUMBER_OF_ENERGY_LEVELS)) );
   ptr+= ((4)*(NUMBER_OF_ENERGY_LEVELS));
}
int32 get_vgrp_id_cris_level2_factors_energy_levels() {return(vgrp_id_cris_level2_factors_energy_levels);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_cris_level2_factors_energy_levels(char *wr_strval)
{
  strcpy(wr_strval, "The file 'cris_level2_factors_energy_levels.h' is shown below, it was used to create the data in the Vgroup named 'VG_CRIS_factors_energy_levels'.\n\n");
  strcat(wr_strval,"/* Id: cris_level2_factors_energy_levels.h,v 1.1 2000/08/01 23:49:14 asc Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"cris_sizes.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct CRIS_factors_energy_levels {\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8   z_number;\n");
  strcat(wr_strval,"  float32 energy_min[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 energy_max[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 geo_factor[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 spallation[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"  float32 SOFT[NUMBER_OF_ENERGY_LEVELS];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
