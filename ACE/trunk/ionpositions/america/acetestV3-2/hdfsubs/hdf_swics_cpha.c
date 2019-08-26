/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_cpha.h,v 1.2 1997/05/06 19:09:53 jeff Exp  */

#include "s3_cpha.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_cpha;
static int32 vdata_id_s3_cpha;

static int32 sds_id_s3_cpha1, sds_id_s3_cpha2, sds_id_s3_cpha3, sds_id_s3_cpha4;

  /* 1021 is the size of s3_cpha.h + 1 added line */
char Vgrp_descrp_cpha[1021];

/****----  init create function  ----****/

int32 init_cr_s3_cpha(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2, sds_ref_w3, sds_ref_w4;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_cpha();

  void print_s3_cpha_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_cpha = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_cpha_error("init_cr_s3_cpha -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_cpha, "VG_cpha"); 
  Vsetclass(vgrp_id_s3_cpha, "VG_S3_CPHA");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_cpha" )) ==FAIL) {
    print_s3_cpha_error("init_cr_s3_cpha -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_cpha(Vgrp_descrp_cpha);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_cpha_error("init_cr_s3_cpha -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_cpha, sizeof(Vgrp_descrp_cpha))) ==FAIL) {
    print_s3_cpha_error("init_cr_s3_cpha -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_cpha = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_cpha_error("init_cr_s3_cpha -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_cpha, "cpha");
  VSsetclass(vdata_id_s3_cpha, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_cpha, vdata_id_s3_cpha)) ==FAIL) {
    print_s3_cpha_error("init_cr_s3_cpha -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_cpha, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_cpha_error("init_cr_s3_cpha -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_cpha, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_cpha_error("init_cr_s3_cpha -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_cpha, "QAC", DFNT_UINT32, (1) )) {
    print_s3_cpha_error("init_cr_s3_cpha -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_cpha, "concat", DFNT_UINT8, (1) )) {
    print_s3_cpha_error("init_cr_s3_cpha -> VSfdefine: Couldn't define concat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_cpha, "elements", DFNT_UINT32, (1) )) {
    print_s3_cpha_error("init_cr_s3_cpha -> VSfdefine: Couldn't define elements");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_cpha,"sctime_readout, sctime_collection, QAC, concat, elements")){
    print_s3_cpha_error("init_cr_s3_cpha -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWICS_PHA_CYCLEN;
  dim_sizes[2] = SWICS_PHA_CYCPERSR;
  if((sds_id_s3_cpha1 = SDcreate(sd_id, "cpha_range", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> SDcreate: Couldn't create cpha_range");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_cpha1)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> SDidtoref: Couldn't get ref for cpha_range");

  if((Vaddtagref(vgrp_id_s3_cpha, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> Vaddtagref: Couldn't add SDS cpha_range to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWICS_PHA_CYCLEN;
  dim_sizes[2] = SWICS_PHA_CYCPERSR;
  if((sds_id_s3_cpha2 = SDcreate(sd_id, "cpha_sector", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> SDcreate: Couldn't create cpha_sector");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_s3_cpha2)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> SDidtoref: Couldn't get ref for cpha_sector");

  if((Vaddtagref(vgrp_id_s3_cpha, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> Vaddtagref: Couldn't add SDS cpha_sector to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWICS_PHA_CYCLEN;
  dim_sizes[2] = SWICS_PHA_CYCPERSR;
  if((sds_id_s3_cpha3 = SDcreate(sd_id, "cpha_energy", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> SDcreate: Couldn't create cpha_energy");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w3 = SDidtoref(sds_id_s3_cpha3)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> SDidtoref: Couldn't get ref for cpha_energy");

  if((Vaddtagref(vgrp_id_s3_cpha, DFTAG_NDG, sds_ref_w3)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> Vaddtagref: Couldn't add SDS cpha_energy to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWICS_PHA_CYCLEN;
  dim_sizes[2] = SWICS_PHA_CYCPERSR;
  if((sds_id_s3_cpha4 = SDcreate(sd_id, "cpha_time", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> SDcreate: Couldn't create cpha_time");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w4 = SDidtoref(sds_id_s3_cpha4)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> SDidtoref: Couldn't get ref for cpha_time");

  if((Vaddtagref(vgrp_id_s3_cpha, DFTAG_NDG, sds_ref_w4)) == FAIL)
    print_s3_cpha_error("init_cr_s3_cpha -> Vaddtagref: Couldn't add SDS cpha_time to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_cpha(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_cpha(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_cpha(struct cpha cpha_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_cpha_error();
void pack_s3_cpha();

  odata = (uint8 *) malloc(sizeof(struct cpha));
  pack_s3_cpha(odata, &cpha_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_cpha, recnum)==-1) {
		print_s3_cpha_error("write_s3_cpha -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_cpha, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_cpha_error("write_s3_cpha -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = SWICS_PHA_CYCLEN;
  edges[2] = SWICS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_cpha1,start,NULL,edges, (VOIDP)(cpha_struc.range)) ==FAIL)
    print_s3_cpha_error("write_s3_cpha -> SDwritedata: Problem writing range data.");

  edges[1] = SWICS_PHA_CYCLEN;
  edges[2] = SWICS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_cpha2,start,NULL,edges, (VOIDP)(cpha_struc.sector)) ==FAIL)
    print_s3_cpha_error("write_s3_cpha -> SDwritedata: Problem writing sector data.");

  edges[1] = SWICS_PHA_CYCLEN;
  edges[2] = SWICS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_cpha3,start,NULL,edges, (VOIDP)(cpha_struc.energy)) ==FAIL)
    print_s3_cpha_error("write_s3_cpha -> SDwritedata: Problem writing energy data.");

  edges[1] = SWICS_PHA_CYCLEN;
  edges[2] = SWICS_PHA_CYCPERSR;
  if (SDwritedata(sds_id_s3_cpha4,start,NULL,edges, (VOIDP)(cpha_struc.time)) ==FAIL)
    print_s3_cpha_error("write_s3_cpha -> SDwritedata: Problem writing time data.");

  memset(&cpha_struc, 0, sizeof(struct cpha));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_cpha()
{
  VSdetach(vdata_id_s3_cpha);
  Vdetach(vgrp_id_s3_cpha);
  SDendaccess(sds_id_s3_cpha1);
  SDendaccess(sds_id_s3_cpha2);
  SDendaccess(sds_id_s3_cpha3);
  SDendaccess(sds_id_s3_cpha4);
}

/*----     init access function    ----*/

int32 init_acc_s3_cpha(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  static int32 sds_index3;
  static int32 sds_index4;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_cpha_error();

  if((sds_index1=SDnametoindex(sd_id, "cpha_range" )) ==FAIL) {
      print_s3_cpha_error("init_acc_s3_cpha -> SDnametoindex: Couldn't find cpha_range");
      return(-1);
  }
  if((sds_id_s3_cpha1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_cpha_error("init_acc_s3_cpha -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "cpha_sector" )) ==FAIL) {
      print_s3_cpha_error("init_acc_s3_cpha -> SDnametoindex: Couldn't find cpha_sector");
      return(-1);
  }
  if((sds_id_s3_cpha2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_s3_cpha_error("init_acc_s3_cpha -> SDselect: Couldn't select sds_index2");
      return(-1);
  }
  if((sds_index3=SDnametoindex(sd_id, "cpha_energy" )) ==FAIL) {
      print_s3_cpha_error("init_acc_s3_cpha -> SDnametoindex: Couldn't find cpha_energy");
      return(-1);
  }
  if((sds_id_s3_cpha3=SDselect(sd_id, sds_index3)) ==FAIL) {
      print_s3_cpha_error("init_acc_s3_cpha -> SDselect: Couldn't select sds_index3");
      return(-1);
  }
  if((sds_index4=SDnametoindex(sd_id, "cpha_time" )) ==FAIL) {
      print_s3_cpha_error("init_acc_s3_cpha -> SDnametoindex: Couldn't find cpha_time");
      return(-1);
  }
  if((sds_id_s3_cpha4=SDselect(sd_id, sds_index4)) ==FAIL) {
      print_s3_cpha_error("init_acc_s3_cpha -> SDselect: Couldn't select sds_index4");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "cpha")) <= 0 ) {
    print_s3_cpha_error("init_acc_s3_cpha -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_cpha = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_cpha_error("init_acc_s3_cpha -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_cpha, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_cpha,"sctime_readout, sctime_collection, QAC, concat, elements")) {
      print_s3_cpha_error("init_acc_s3_cpha -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_cpha(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_cpha(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_cpha(struct cpha *cpha_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_cpha_error();
void unpack_s3_cpha();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct cpha));
  VSinquire(vdata_id_s3_cpha, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_cpha, recnum_rd)==FAIL) {
          print_s3_cpha_error("read_s3_cpha -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SWICS_PHA_CYCLEN;
  edges[2] = SWICS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_cpha1,start,NULL,edges, (VOIDP)(cpha_struc->range )) ==FAIL) {
    print_s3_cpha_error("read_s3_cpha -> SDreaddata: Couldn't read range");
    retval = -1;
  }
  edges[1] = SWICS_PHA_CYCLEN;
  edges[2] = SWICS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_cpha2,start,NULL,edges, (VOIDP)(cpha_struc->sector )) ==FAIL) {
    print_s3_cpha_error("read_s3_cpha -> SDreaddata: Couldn't read sector");
    retval = -1;
  }
  edges[1] = SWICS_PHA_CYCLEN;
  edges[2] = SWICS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_cpha3,start,NULL,edges, (VOIDP)(cpha_struc->energy )) ==FAIL) {
    print_s3_cpha_error("read_s3_cpha -> SDreaddata: Couldn't read energy");
    retval = -1;
  }
  edges[1] = SWICS_PHA_CYCLEN;
  edges[2] = SWICS_PHA_CYCPERSR;

  if(SDreaddata(sds_id_s3_cpha4,start,NULL,edges, (VOIDP)(cpha_struc->time )) ==FAIL) {
    print_s3_cpha_error("read_s3_cpha -> SDreaddata: Couldn't read time");
    retval = -1;
  }
  if(VSread(vdata_id_s3_cpha, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_cpha_error("read_s3_cpha -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_cpha(odata, cpha_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_cpha()
{
  VSdetach(vdata_id_s3_cpha);
  SDendaccess(sds_id_s3_cpha1);
  SDendaccess(sds_id_s3_cpha2);
  SDendaccess(sds_id_s3_cpha3);
  SDendaccess(sds_id_s3_cpha4);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_cpha(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_cpha_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_cpha" )) ==FAIL)
    print_s3_cpha_error("rd_Vgrp_s3_cpha -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_cpha_error("rd_Vgrp_s3_cpha -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_cpha_error("rd_Vgrp_s3_cpha -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_cpha_error("rd_Vgrp_s3_cpha -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_cpha, HDstrlen(Vgrp_descrp_cpha)) ==FAIL)
    print_s3_cpha_error("rd_Vgrp_s3_cpha -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_cpha);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_cpha_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swics_cpha.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_cpha(uint8 *data, struct cpha *cpha_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &cpha_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &cpha_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &cpha_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &cpha_ptr->concat, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &cpha_ptr->elements, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_cpha(uint8 *data, struct cpha *cpha_ptr)
{
int32 ptr=0;

   memcpy(&cpha_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&cpha_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&cpha_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&cpha_ptr->concat, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&cpha_ptr->elements, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_s3_cpha() {return(vgrp_id_s3_cpha);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_cpha(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_cpha.h' is shown below, it was used to create the data in the Vgroup named 'VG_cpha'.\n\n");
  strcat(wr_strval,"/* Id: s3_cpha.h,v 1.2 1997/05/06 19:09:53 jeff Exp $           */\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SWICS_PHA_CYCLEN    194           \n");
  strcat(wr_strval,"#define SWICS_PHA_CYCPERSR  60      \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct cpha  {\n");
  strcat(wr_strval,"           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  QAC;         /* number of missing frames in this SR*/\n");
  strcat(wr_strval,"           uint8   concat;      /*  is the number of mpha structs     */\n");
  strcat(wr_strval,"           uint32  elements;    /*  number of pha events      */         \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"           uint8   range[SWICS_PHA_CYCLEN][SWICS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"           uint8   sector[SWICS_PHA_CYCLEN][SWICS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"           uint16  energy[SWICS_PHA_CYCLEN][SWICS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"           uint16  time[SWICS_PHA_CYCLEN][SWICS_PHA_CYCPERSR];\n");
  strcat(wr_strval,"     \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
