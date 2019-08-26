/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: uleis_br_db.h,v 1.2 1998/12/09 00:30:48 steves Exp  */

#include "uleis_br_db.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_uleis_br_db;
static int32 vdata_id_uleis_br_db;

static int32 sds_id_uleis_br_db1, sds_id_uleis_br_db2;

  /* 826 is the size of uleis_br_db.h + 1 added line */
char Vgrp_descrp_UleisDB[826];

/****----  init create function  ----****/

int32 init_cr_uleis_br_db(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_uleis_br_db();

  void print_uleis_br_db_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_uleis_br_db = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_uleis_br_db_error("init_cr_uleis_br_db -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_uleis_br_db, "VG_UleisDB"); 
  Vsetclass(vgrp_id_uleis_br_db, "VG_ULEIS_BR_DB");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_UleisDB" )) ==FAIL) {
    print_uleis_br_db_error("init_cr_uleis_br_db -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_uleis_br_db(Vgrp_descrp_UleisDB);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_uleis_br_db_error("init_cr_uleis_br_db -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_UleisDB, sizeof(Vgrp_descrp_UleisDB))) ==FAIL) {
    print_uleis_br_db_error("init_cr_uleis_br_db -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_uleis_br_db = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_uleis_br_db_error("init_cr_uleis_br_db -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_uleis_br_db, "UleisDB");
  VSsetclass(vdata_id_uleis_br_db, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_uleis_br_db, vdata_id_uleis_br_db)) ==FAIL) {
    print_uleis_br_db_error("init_cr_uleis_br_db -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_uleis_br_db, "begin_time_in_sec", DFNT_FLOAT64, (1) )) {
    print_uleis_br_db_error("init_cr_uleis_br_db -> VSfdefine: Couldn't define begin_time_in_sec");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_br_db, "end_time_in_sec", DFNT_FLOAT64, (1) )) {
    print_uleis_br_db_error("init_cr_uleis_br_db -> VSfdefine: Couldn't define end_time_in_sec");
    retval = -1;
  }

  if (VSsetfields(vdata_id_uleis_br_db,"begin_time_in_sec, end_time_in_sec")){
    print_uleis_br_db_error("init_cr_uleis_br_db -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 9;
  dim_sizes[2] = 3;
  if((sds_id_uleis_br_db1 = SDcreate(sd_id, "UleisDB_species", DFNT_FLOAT64, rank, dim_sizes)) == FAIL)
    print_uleis_br_db_error("init_cr_uleis_br_db -> SDcreate: Couldn't create UleisDB_species");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_uleis_br_db1)) == FAIL)
    print_uleis_br_db_error("init_cr_uleis_br_db -> SDidtoref: Couldn't get ref for UleisDB_species");

  if((Vaddtagref(vgrp_id_uleis_br_db, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_uleis_br_db_error("init_cr_uleis_br_db -> Vaddtagref: Couldn't add SDS UleisDB_species to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 7;
  dim_sizes[2] = 4;
  if((sds_id_uleis_br_db2 = SDcreate(sd_id, "UleisDB_detector", DFNT_FLOAT64, rank, dim_sizes)) == FAIL)
    print_uleis_br_db_error("init_cr_uleis_br_db -> SDcreate: Couldn't create UleisDB_detector");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_uleis_br_db2)) == FAIL)
    print_uleis_br_db_error("init_cr_uleis_br_db -> SDidtoref: Couldn't get ref for UleisDB_detector");

  if((Vaddtagref(vgrp_id_uleis_br_db, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_uleis_br_db_error("init_cr_uleis_br_db -> Vaddtagref: Couldn't add SDS UleisDB_detector to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_uleis_br_db(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_uleis_br_db(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_uleis_br_db(struct UleisDB UleisDB_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_uleis_br_db_error();
void pack_uleis_br_db();

  odata = (uint8 *) malloc(sizeof(struct UleisDB));
  pack_uleis_br_db(odata, &UleisDB_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_uleis_br_db, recnum)==-1) {
		print_uleis_br_db_error("write_uleis_br_db -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_uleis_br_db, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_uleis_br_db_error("write_uleis_br_db -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 9;
  edges[2] = 3;
  if (SDwritedata(sds_id_uleis_br_db1,start,NULL,edges, (VOIDP)(UleisDB_struc.species)) ==FAIL)
    print_uleis_br_db_error("write_uleis_br_db -> SDwritedata: Problem writing species data.");

  edges[1] = 7;
  edges[2] = 4;
  if (SDwritedata(sds_id_uleis_br_db2,start,NULL,edges, (VOIDP)(UleisDB_struc.detector)) ==FAIL)
    print_uleis_br_db_error("write_uleis_br_db -> SDwritedata: Problem writing detector data.");

  memset(&UleisDB_struc, 0, sizeof(struct UleisDB));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_uleis_br_db()
{
  VSdetach(vdata_id_uleis_br_db);
  Vdetach(vgrp_id_uleis_br_db);
  SDendaccess(sds_id_uleis_br_db1);
  SDendaccess(sds_id_uleis_br_db2);
}

/*----     init access function    ----*/

int32 init_acc_uleis_br_db(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  int32 vdata_ref;
  int32 num_rec;

  void print_uleis_br_db_error();

  if((sds_index1=SDnametoindex(sd_id, "UleisDB_species" )) ==FAIL) {
      print_uleis_br_db_error("init_acc_uleis_br_db -> SDnametoindex: Couldn't find UleisDB_species");
      return(-1);
  }
  if((sds_id_uleis_br_db1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_uleis_br_db_error("init_acc_uleis_br_db -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "UleisDB_detector" )) ==FAIL) {
      print_uleis_br_db_error("init_acc_uleis_br_db -> SDnametoindex: Couldn't find UleisDB_detector");
      return(-1);
  }
  if((sds_id_uleis_br_db2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_uleis_br_db_error("init_acc_uleis_br_db -> SDselect: Couldn't select sds_index2");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "UleisDB")) <= 0 ) {
    print_uleis_br_db_error("init_acc_uleis_br_db -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_uleis_br_db = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_uleis_br_db_error("init_acc_uleis_br_db -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_uleis_br_db, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_uleis_br_db,"begin_time_in_sec, end_time_in_sec")) {
      print_uleis_br_db_error("init_acc_uleis_br_db -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_uleis_br_db(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_uleis_br_db(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_uleis_br_db(struct UleisDB *UleisDB_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_uleis_br_db_error();
void unpack_uleis_br_db();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct UleisDB));
  VSinquire(vdata_id_uleis_br_db, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_uleis_br_db, recnum_rd)==FAIL) {
          print_uleis_br_db_error("read_uleis_br_db -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 9;
  edges[2] = 3;

  if(SDreaddata(sds_id_uleis_br_db1,start,NULL,edges, (VOIDP)(UleisDB_struc->species )) ==FAIL) {
    print_uleis_br_db_error("read_uleis_br_db -> SDreaddata: Couldn't read species");
    retval = -1;
  }
  edges[1] = 7;
  edges[2] = 4;

  if(SDreaddata(sds_id_uleis_br_db2,start,NULL,edges, (VOIDP)(UleisDB_struc->detector )) ==FAIL) {
    print_uleis_br_db_error("read_uleis_br_db -> SDreaddata: Couldn't read detector");
    retval = -1;
  }
  if(VSread(vdata_id_uleis_br_db, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_uleis_br_db_error("read_uleis_br_db -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_uleis_br_db(odata, UleisDB_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_uleis_br_db()
{
  VSdetach(vdata_id_uleis_br_db);
  SDendaccess(sds_id_uleis_br_db1);
  SDendaccess(sds_id_uleis_br_db2);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_uleis_br_db(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_uleis_br_db_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_UleisDB" )) ==FAIL)
    print_uleis_br_db_error("rd_Vgrp_uleis_br_db -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_uleis_br_db_error("rd_Vgrp_uleis_br_db -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_uleis_br_db_error("rd_Vgrp_uleis_br_db -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_uleis_br_db_error("rd_Vgrp_uleis_br_db -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_UleisDB, HDstrlen(Vgrp_descrp_UleisDB)) ==FAIL)
    print_uleis_br_db_error("rd_Vgrp_uleis_br_db -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_UleisDB);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_uleis_br_db_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_uleis_br_db.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_uleis_br_db(uint8 *data, struct UleisDB *UleisDB_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &UleisDB_ptr->begin_time_in_sec, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &UleisDB_ptr->end_time_in_sec, ((8)*(1)) );
   ptr+= ((8)*(1));
}

/*----   unpack function    ----*/

void unpack_uleis_br_db(uint8 *data, struct UleisDB *UleisDB_ptr)
{
int32 ptr=0;

   memcpy(&UleisDB_ptr->begin_time_in_sec, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&UleisDB_ptr->end_time_in_sec, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
}
int32 get_vgrp_id_uleis_br_db() {return(vgrp_id_uleis_br_db);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_uleis_br_db(char *wr_strval)
{
  strcpy(wr_strval, "The file 'uleis_br_db.h' is shown below, it was used to create the data in the Vgroup named 'VG_UleisDB'.\n\n");
  strcat(wr_strval,"/* Id: uleis_br_db.h,v 1.2 1998/12/09 00:30:48 steves Exp $ */\n");
  strcat(wr_strval,"/* The variables and arrays below are assigned values from the files */\n");
  strcat(wr_strval,"/* in the ~asc/aceprog/uleis_br_db directory */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct UleisDB\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64 begin_time_in_sec; /* seconds since Jan 1 1970 */\n");
  strcat(wr_strval,"  float64 end_time_in_sec;  /* seconds since Jan 1 1970 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/*H,H, 3He, 4He,4He, O,O, Fe,Fe by Rate_assignment, Detectors, Efficiency(Avg)*/\n");
  strcat(wr_strval,"  float64 species[9][3];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/*ULEIS Detector Geometry Factors vs. Iris settings (i.e. motor position)*/\n");
  strcat(wr_strval,"/* D1, D2, D3, D4, D5, D6, D7 by Iris settings of: 100%, 25%, 6%, 1% */\n");
  strcat(wr_strval,"  float64 detector[7][4];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
