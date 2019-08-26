/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: level2_record_doy.h,v 1.1 2000/08/02 00:47:11 asc Exp  */

#include "level2_record_doy.h"
#include "df.h"

int32 vgrp_id_level2_record_doy_all;
static int32 vdata_id_level2_record_doy_all;

  /* 606 is the size of level2_record_doy.h + 1 added line */
char Vgrp_descrp_level2_record_doy[606];

/****----  init create function  ----****/

int32 init_cr_level2_record_doy_all(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_level2_record_doy_all();

  void print_level2_record_doy_all_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_level2_record_doy_all = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_level2_record_doy_all, "VG_level2_record_doy"); 
  Vsetclass(vgrp_id_level2_record_doy_all, "VG_LEVEL2_RECORD_DOY");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_level2_record_doy" )) ==FAIL) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_level2_record_doy_all(Vgrp_descrp_level2_record_doy);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_level2_record_doy, sizeof(Vgrp_descrp_level2_record_doy))) ==FAIL) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_level2_record_doy_all = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_level2_record_doy_all, "level2_record_doy");
  VSsetclass(vdata_id_level2_record_doy_all, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_level2_record_doy_all, vdata_id_level2_record_doy_all)) ==FAIL) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_level2_record_doy_all, "record_number", DFNT_INT32, (1) )) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> VSfdefine: Couldn't define record_number");
    retval = -1;
  }
  if (VSfdefine(vdata_id_level2_record_doy_all, "year", DFNT_INT32, (1) )) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> VSfdefine: Couldn't define year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_level2_record_doy_all, "day", DFNT_INT32, (1) )) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> VSfdefine: Couldn't define day");
    retval = -1;
  }
  if (VSfdefine(vdata_id_level2_record_doy_all, "days_jan_1_1996", DFNT_INT32, (1) )) {
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> VSfdefine: Couldn't define days_jan_1_1996");
    retval = -1;
  }

  if (VSsetfields(vdata_id_level2_record_doy_all,"record_number, year, day, days_jan_1_1996")){
    print_level2_record_doy_all_error("init_cr_level2_record_doy_all -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_level2_record_doy_all(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_level2_record_doy_all(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_level2_record_doy_all(struct level2_record_doy level2_record_doy_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_level2_record_doy_all_error();
void pack_level2_record_doy_all();

  odata = (uint8 *) malloc(sizeof(struct level2_record_doy));
  pack_level2_record_doy_all(odata, &level2_record_doy_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_level2_record_doy_all, recnum)==-1) {
		print_level2_record_doy_all_error("write_level2_record_doy_all -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_level2_record_doy_all, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_level2_record_doy_all_error("write_level2_record_doy_all -> VSwrite: Couldn't write data.");

  memset(&level2_record_doy_struc, 0, sizeof(struct level2_record_doy));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_level2_record_doy_all()
{
  VSdetach(vdata_id_level2_record_doy_all);
  Vdetach(vgrp_id_level2_record_doy_all);
}

/*----     init access function    ----*/

int32 init_acc_level2_record_doy_all(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_level2_record_doy_all_error();


  if ((vdata_ref = VSfind(hdf_fp, "level2_record_doy")) <= 0 ) {
    print_level2_record_doy_all_error("init_acc_level2_record_doy_all -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_level2_record_doy_all = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_level2_record_doy_all_error("init_acc_level2_record_doy_all -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_level2_record_doy_all, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_level2_record_doy_all,"record_number, year, day, days_jan_1_1996")) {
      print_level2_record_doy_all_error("init_acc_level2_record_doy_all -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_level2_record_doy_all(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_level2_record_doy_all(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_level2_record_doy_all(struct level2_record_doy *level2_record_doy_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_level2_record_doy_all_error();
void unpack_level2_record_doy_all();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct level2_record_doy));
  VSinquire(vdata_id_level2_record_doy_all, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_level2_record_doy_all, recnum_rd)==FAIL) {
          print_level2_record_doy_all_error("read_level2_record_doy_all -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_level2_record_doy_all, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_level2_record_doy_all_error("read_level2_record_doy_all -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_level2_record_doy_all(odata, level2_record_doy_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_level2_record_doy_all()
{
  VSdetach(vdata_id_level2_record_doy_all);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_level2_record_doy_all(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_level2_record_doy_all_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_level2_record_doy" )) ==FAIL)
    print_level2_record_doy_all_error("rd_Vgrp_level2_record_doy_all -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_level2_record_doy_all_error("rd_Vgrp_level2_record_doy_all -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_level2_record_doy_all_error("rd_Vgrp_level2_record_doy_all -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_level2_record_doy_all_error("rd_Vgrp_level2_record_doy_all -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_level2_record_doy, HDstrlen(Vgrp_descrp_level2_record_doy)) ==FAIL)
    print_level2_record_doy_all_error("rd_Vgrp_level2_record_doy_all -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_level2_record_doy);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_level2_record_doy_all_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_level2_record_doy_all.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_level2_record_doy_all(uint8 *data, struct level2_record_doy *level2_record_doy_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &level2_record_doy_ptr->record_number, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &level2_record_doy_ptr->year, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &level2_record_doy_ptr->day, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &level2_record_doy_ptr->days_jan_1_1996, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_level2_record_doy_all(uint8 *data, struct level2_record_doy *level2_record_doy_ptr)
{
int32 ptr=0;

   memcpy(&level2_record_doy_ptr->record_number, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&level2_record_doy_ptr->year, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&level2_record_doy_ptr->day, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&level2_record_doy_ptr->days_jan_1_1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_level2_record_doy_all() {return(vgrp_id_level2_record_doy_all);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_level2_record_doy_all(char *wr_strval)
{
  strcpy(wr_strval, "The file 'level2_record_doy.h' is shown below, it was used to create the data in the Vgroup named 'VG_level2_record_doy'.\n\n");
  strcat(wr_strval,"/* Id: level2_record_doy.h,v 1.1 2000/08/02 00:47:11 asc Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* record year/DOY association */\n");
  strcat(wr_strval,"struct level2_record_doy {\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  int32   record_number;             /* record number */\n");
  strcat(wr_strval,"  int32   year;                      /* integer year */\n");
  strcat(wr_strval,"  int32   day;                       /* integer day of year */\n");
  strcat(wr_strval,"  int32   days_jan_1_1996;           /* days since January 1, 1996 UT 0 hr*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
