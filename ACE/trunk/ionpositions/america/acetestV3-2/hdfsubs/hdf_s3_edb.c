/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_edb.h,v 1.1 1997/08/15 20:15:22 jeff Exp  */

#include "s3_edb.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_edb;
static int32 vdata_id_s3_edb;

static int32 sds_id_s3_edb1;

  /* 662 is the size of s3_edb.h + 1 added line */
char Vgrp_descrp_s3_edb[662];

/****----  init create function  ----****/

int32 init_cr_s3_edb(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_edb();

  void print_s3_edb_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_edb = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_edb_error("init_cr_s3_edb -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_edb, "VG_s3_edb"); 
  Vsetclass(vgrp_id_s3_edb, "VG_S3_EDB");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_s3_edb" )) ==FAIL) {
    print_s3_edb_error("init_cr_s3_edb -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_edb(Vgrp_descrp_s3_edb);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_edb_error("init_cr_s3_edb -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_s3_edb, sizeof(Vgrp_descrp_s3_edb))) ==FAIL) {
    print_s3_edb_error("init_cr_s3_edb -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_edb = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_edb_error("init_cr_s3_edb -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_edb, "s3_edb");
  VSsetclass(vdata_id_s3_edb, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_edb, vdata_id_s3_edb)) ==FAIL) {
    print_s3_edb_error("init_cr_s3_edb -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_edb, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_edb_error("init_cr_s3_edb -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_edb, "ACEepoch_collection", DFNT_FLOAT64, (1) )) {
    print_s3_edb_error("init_cr_s3_edb -> VSfdefine: Couldn't define ACEepoch_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_edb, "QAC", DFNT_UINT8, (1) )) {
    print_s3_edb_error("init_cr_s3_edb -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_edb, "QACarr", DFNT_UINT8, (12) )) {
    print_s3_edb_error("init_cr_s3_edb -> VSfdefine: Couldn't define QACarr");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_edb,"sctime_readout, ACEepoch_collection, QAC, QACarr")){
    print_s3_edb_error("init_cr_s3_edb -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 12;
  dim_sizes[2] = 203;
  if((sds_id_s3_edb1 = SDcreate(sd_id, "s3_edb_data", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_edb_error("init_cr_s3_edb -> SDcreate: Couldn't create s3_edb_data");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_edb1)) == FAIL)
    print_s3_edb_error("init_cr_s3_edb -> SDidtoref: Couldn't get ref for s3_edb_data");

  if((Vaddtagref(vgrp_id_s3_edb, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_edb_error("init_cr_s3_edb -> Vaddtagref: Couldn't add SDS s3_edb_data to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_edb(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_edb(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_edb(struct s3_edb s3_edb_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_edb_error();
void pack_s3_edb();

  odata = (uint8 *) malloc(sizeof(struct s3_edb));
  pack_s3_edb(odata, &s3_edb_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_edb, recnum)==-1) {
		print_s3_edb_error("write_s3_edb -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_edb, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_edb_error("write_s3_edb -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 12;
  edges[2] = 203;
  if (SDwritedata(sds_id_s3_edb1,start,NULL,edges, (VOIDP)(s3_edb_struc.data)) ==FAIL)
    print_s3_edb_error("write_s3_edb -> SDwritedata: Problem writing data data.");

  memset(&s3_edb_struc, 0, sizeof(struct s3_edb));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_edb()
{
  VSdetach(vdata_id_s3_edb);
  Vdetach(vgrp_id_s3_edb);
  SDendaccess(sds_id_s3_edb1);
}

/*----     init access function    ----*/

int32 init_acc_s3_edb(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_edb_error();

  if((sds_index1=SDnametoindex(sd_id, "s3_edb_data" )) ==FAIL) {
      print_s3_edb_error("init_acc_s3_edb -> SDnametoindex: Couldn't find s3_edb_data");
      return(-1);
  }
  if((sds_id_s3_edb1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_edb_error("init_acc_s3_edb -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "s3_edb")) <= 0 ) {
    print_s3_edb_error("init_acc_s3_edb -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_edb = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_edb_error("init_acc_s3_edb -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_edb, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_edb,"sctime_readout, ACEepoch_collection, QAC, QACarr")) {
      print_s3_edb_error("init_acc_s3_edb -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_edb(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_edb(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_edb(struct s3_edb *s3_edb_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_edb_error();
void unpack_s3_edb();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct s3_edb));
  VSinquire(vdata_id_s3_edb, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_edb, recnum_rd)==FAIL) {
          print_s3_edb_error("read_s3_edb -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 12;
  edges[2] = 203;

  if(SDreaddata(sds_id_s3_edb1,start,NULL,edges, (VOIDP)(s3_edb_struc->data )) ==FAIL) {
    print_s3_edb_error("read_s3_edb -> SDreaddata: Couldn't read data");
    retval = -1;
  }
  if(VSread(vdata_id_s3_edb, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_edb_error("read_s3_edb -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_edb(odata, s3_edb_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_edb()
{
  VSdetach(vdata_id_s3_edb);
  SDendaccess(sds_id_s3_edb1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_edb(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_edb_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_s3_edb" )) ==FAIL)
    print_s3_edb_error("rd_Vgrp_s3_edb -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_edb_error("rd_Vgrp_s3_edb -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_edb_error("rd_Vgrp_s3_edb -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_edb_error("rd_Vgrp_s3_edb -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_s3_edb, HDstrlen(Vgrp_descrp_s3_edb)) ==FAIL)
    print_s3_edb_error("rd_Vgrp_s3_edb -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_s3_edb);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_edb_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3_edb.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_edb(uint8 *data, struct s3_edb *s3_edb_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &s3_edb_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3_edb_ptr->ACEepoch_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &s3_edb_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3_edb_ptr->QACarr[0], ((1)*(12)) );
   ptr+= ((1)*(12));
}

/*----   unpack function    ----*/

void unpack_s3_edb(uint8 *data, struct s3_edb *s3_edb_ptr)
{
int32 ptr=0;

   memcpy(&s3_edb_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3_edb_ptr->ACEepoch_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&s3_edb_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3_edb_ptr->QACarr[0], data+ptr,  ((1)*(12)) );
   ptr+= ((1)*(12));
}
int32 get_vgrp_id_s3_edb() {return(vgrp_id_s3_edb);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_edb(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_edb.h' is shown below, it was used to create the data in the Vgroup named 'VG_s3_edb'.\n\n");
  strcat(wr_strval,"/* Id: s3_edb.h,v 1.1 1997/08/15 20:15:22 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct s3_edb\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 sctime_readout;         /* 32 bit spacecraft readout time    */\n");
  strcat(wr_strval,"  float64 ACEepoch_collection;  /* Spin start time.  # of sec since 1/1/96 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 QAC;              /* number of missing frame in this cycle */\n");
  strcat(wr_strval,"  uint8 QACarr[12];       /* =1 frame missing (bad), =0 frame OK */ \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 data[12][203];    /* 12 frames of S3DPU data in a complete EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
