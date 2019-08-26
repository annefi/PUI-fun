/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_cmonitor.h,v 1.4 1999/09/01 21:22:19 ad Exp  */

#include "s3_cmonitor.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_cmonitor;
static int32 vdata_id_s3_cmonitor;

static int32 sds_id_s3_cmonitor1;

  /* 902 is the size of s3_cmonitor.h + 1 added line */
char Vgrp_descrp_cmonitor[902];

/****----  init create function  ----****/

int32 init_cr_s3_cmonitor(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_cmonitor();

  void print_s3_cmonitor_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_cmonitor = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_cmonitor, "VG_cmonitor"); 
  Vsetclass(vgrp_id_s3_cmonitor, "VG_S3_CMONITOR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_cmonitor" )) ==FAIL) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_cmonitor(Vgrp_descrp_cmonitor);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_cmonitor, sizeof(Vgrp_descrp_cmonitor))) ==FAIL) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_cmonitor = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_cmonitor, "cmonitor");
  VSsetclass(vdata_id_s3_cmonitor, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_cmonitor, vdata_id_s3_cmonitor)) ==FAIL) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_cmonitor, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_cmonitor, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_cmonitor, "QAC", DFNT_UINT32, (1) )) {
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_cmonitor,"sctime_readout, sctime_collection, QAC")){
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = CMON_CYC;
  dim_sizes[2] = CMON_CSZ;
  if((sds_id_s3_cmonitor1 = SDcreate(sd_id, "cmonitor_MONITOR", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> SDcreate: Couldn't create cmonitor_MONITOR");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_cmonitor1)) == FAIL)
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> SDidtoref: Couldn't get ref for cmonitor_MONITOR");

  if((Vaddtagref(vgrp_id_s3_cmonitor, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_cmonitor_error("init_cr_s3_cmonitor -> Vaddtagref: Couldn't add SDS cmonitor_MONITOR to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_cmonitor(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_cmonitor(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_cmonitor(struct cmonitor cmonitor_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_cmonitor_error();
void pack_s3_cmonitor();

  odata = (uint8 *) malloc(sizeof(struct cmonitor));
  pack_s3_cmonitor(odata, &cmonitor_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_cmonitor, recnum)==-1) {
		print_s3_cmonitor_error("write_s3_cmonitor -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_cmonitor, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_cmonitor_error("write_s3_cmonitor -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = CMON_CYC;
  edges[2] = CMON_CSZ;
  if (SDwritedata(sds_id_s3_cmonitor1,start,NULL,edges, (VOIDP)(cmonitor_struc.MONITOR)) ==FAIL)
    print_s3_cmonitor_error("write_s3_cmonitor -> SDwritedata: Problem writing MONITOR data.");

  memset(&cmonitor_struc, 0, sizeof(struct cmonitor));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_cmonitor()
{
  VSdetach(vdata_id_s3_cmonitor);
  Vdetach(vgrp_id_s3_cmonitor);
  SDendaccess(sds_id_s3_cmonitor1);
}

/*----     init access function    ----*/

int32 init_acc_s3_cmonitor(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_cmonitor_error();

  if((sds_index1=SDnametoindex(sd_id, "cmonitor_MONITOR" )) ==FAIL) {
      print_s3_cmonitor_error("init_acc_s3_cmonitor -> SDnametoindex: Couldn't find cmonitor_MONITOR");
      return(-1);
  }
  if((sds_id_s3_cmonitor1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_cmonitor_error("init_acc_s3_cmonitor -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "cmonitor")) <= 0 ) {
    print_s3_cmonitor_error("init_acc_s3_cmonitor -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_cmonitor = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_cmonitor_error("init_acc_s3_cmonitor -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_cmonitor, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_cmonitor,"sctime_readout, sctime_collection, QAC")) {
      print_s3_cmonitor_error("init_acc_s3_cmonitor -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_cmonitor(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_cmonitor(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_cmonitor(struct cmonitor *cmonitor_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_cmonitor_error();
void unpack_s3_cmonitor();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct cmonitor));
  VSinquire(vdata_id_s3_cmonitor, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_cmonitor, recnum_rd)==FAIL) {
          print_s3_cmonitor_error("read_s3_cmonitor -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = CMON_CYC;
  edges[2] = CMON_CSZ;

  if(SDreaddata(sds_id_s3_cmonitor1,start,NULL,edges, (VOIDP)(cmonitor_struc->MONITOR )) ==FAIL) {
    print_s3_cmonitor_error("read_s3_cmonitor -> SDreaddata: Couldn't read MONITOR");
    retval = -1;
  }
  if(VSread(vdata_id_s3_cmonitor, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_cmonitor_error("read_s3_cmonitor -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_cmonitor(odata, cmonitor_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_cmonitor()
{
  VSdetach(vdata_id_s3_cmonitor);
  SDendaccess(sds_id_s3_cmonitor1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_cmonitor(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_cmonitor_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_cmonitor" )) ==FAIL)
    print_s3_cmonitor_error("rd_Vgrp_s3_cmonitor -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_cmonitor_error("rd_Vgrp_s3_cmonitor -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_cmonitor_error("rd_Vgrp_s3_cmonitor -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_cmonitor_error("rd_Vgrp_s3_cmonitor -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_cmonitor, HDstrlen(Vgrp_descrp_cmonitor)) ==FAIL)
    print_s3_cmonitor_error("rd_Vgrp_s3_cmonitor -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_cmonitor);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_cmonitor_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swics_cmonitor.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_cmonitor(uint8 *data, struct cmonitor *cmonitor_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &cmonitor_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &cmonitor_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &cmonitor_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_cmonitor(uint8 *data, struct cmonitor *cmonitor_ptr)
{
int32 ptr=0;

   memcpy(&cmonitor_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&cmonitor_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&cmonitor_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_s3_cmonitor() {return(vgrp_id_s3_cmonitor);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_cmonitor(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_cmonitor.h' is shown below, it was used to create the data in the Vgroup named 'VG_cmonitor'.\n\n");
  strcat(wr_strval,"/* Id: s3_cmonitor.h,v 1.4 1999/09/01 21:22:19 ad Exp $           */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* SWICS monitor rates */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define  CMON_N     6    /*  number of monitor rates   */\n");
  strcat(wr_strval,"#define  CMON_S     8    /*  number of sectors   */\n");
  strcat(wr_strval,"#define  CMON_CYC  60    /*  number of cycles per SR = 60/1   */\n");
  strcat(wr_strval,"#define  CMON_TSZ  ( CMON_N*CMON_S*CMON_CYC )   /*  total size in bytes */\n");
  strcat(wr_strval,"#define  CMON_CSZ  ( CMON_N*CMON_S )\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct cmonitor  {\n");
  strcat(wr_strval,"           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  QAC;         /* number of missing frames in this SR */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"           uint8  MONITOR[CMON_CYC][CMON_CSZ];   \n");
  strcat(wr_strval,"};\n");
  return(0);
}
