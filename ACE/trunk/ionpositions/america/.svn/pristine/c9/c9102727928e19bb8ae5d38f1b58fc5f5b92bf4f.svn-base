/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_mmonitor.h,v 1.3 1997/05/07 23:15:42 jeff Exp  */

#include "s3_mmonitor.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_mmonitor;
static int32 vdata_id_s3_mmonitor;

static int32 sds_id_s3_mmonitor1;

  /* 889 is the size of s3_mmonitor.h + 1 added line */
char Vgrp_descrp_mmonitor[889];

/****----  init create function  ----****/

int32 init_cr_s3_mmonitor(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_mmonitor();

  void print_s3_mmonitor_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_mmonitor = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_mmonitor, "VG_mmonitor"); 
  Vsetclass(vgrp_id_s3_mmonitor, "VG_S3_MMONITOR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_mmonitor" )) ==FAIL) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_mmonitor(Vgrp_descrp_mmonitor);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_mmonitor, sizeof(Vgrp_descrp_mmonitor))) ==FAIL) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_mmonitor = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_mmonitor, "mmonitor");
  VSsetclass(vdata_id_s3_mmonitor, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_mmonitor, vdata_id_s3_mmonitor)) ==FAIL) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_mmonitor, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mmonitor, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mmonitor, "QAC", DFNT_UINT32, (1) )) {
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_mmonitor,"sctime_readout, sctime_collection, QAC")){
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = MMON_CYC;
  dim_sizes[2] = MMON_CSZ;
  if((sds_id_s3_mmonitor1 = SDcreate(sd_id, "mmonitor_MONITOR", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> SDcreate: Couldn't create mmonitor_MONITOR");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_mmonitor1)) == FAIL)
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> SDidtoref: Couldn't get ref for mmonitor_MONITOR");

  if((Vaddtagref(vgrp_id_s3_mmonitor, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_mmonitor_error("init_cr_s3_mmonitor -> Vaddtagref: Couldn't add SDS mmonitor_MONITOR to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_mmonitor(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_mmonitor(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_mmonitor(struct mmonitor mmonitor_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_mmonitor_error();
void pack_s3_mmonitor();

  odata = (uint8 *) malloc(sizeof(struct mmonitor));
  pack_s3_mmonitor(odata, &mmonitor_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_mmonitor, recnum)==-1) {
		print_s3_mmonitor_error("write_s3_mmonitor -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_mmonitor, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_mmonitor_error("write_s3_mmonitor -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = MMON_CYC;
  edges[2] = MMON_CSZ;
  if (SDwritedata(sds_id_s3_mmonitor1,start,NULL,edges, (VOIDP)(mmonitor_struc.MONITOR)) ==FAIL)
    print_s3_mmonitor_error("write_s3_mmonitor -> SDwritedata: Problem writing MONITOR data.");

  memset(&mmonitor_struc, 0, sizeof(struct mmonitor));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_mmonitor()
{
  VSdetach(vdata_id_s3_mmonitor);
  Vdetach(vgrp_id_s3_mmonitor);
  SDendaccess(sds_id_s3_mmonitor1);
}

/*----     init access function    ----*/

int32 init_acc_s3_mmonitor(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_mmonitor_error();

  if((sds_index1=SDnametoindex(sd_id, "mmonitor_MONITOR" )) ==FAIL) {
      print_s3_mmonitor_error("init_acc_s3_mmonitor -> SDnametoindex: Couldn't find mmonitor_MONITOR");
      return(-1);
  }
  if((sds_id_s3_mmonitor1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_mmonitor_error("init_acc_s3_mmonitor -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "mmonitor")) <= 0 ) {
    print_s3_mmonitor_error("init_acc_s3_mmonitor -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_mmonitor = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_mmonitor_error("init_acc_s3_mmonitor -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_mmonitor, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_mmonitor,"sctime_readout, sctime_collection, QAC")) {
      print_s3_mmonitor_error("init_acc_s3_mmonitor -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_mmonitor(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_mmonitor(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_mmonitor(struct mmonitor *mmonitor_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_mmonitor_error();
void unpack_s3_mmonitor();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct mmonitor));
  VSinquire(vdata_id_s3_mmonitor, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_mmonitor, recnum_rd)==FAIL) {
          print_s3_mmonitor_error("read_s3_mmonitor -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = MMON_CYC;
  edges[2] = MMON_CSZ;

  if(SDreaddata(sds_id_s3_mmonitor1,start,NULL,edges, (VOIDP)(mmonitor_struc->MONITOR )) ==FAIL) {
    print_s3_mmonitor_error("read_s3_mmonitor -> SDreaddata: Couldn't read MONITOR");
    retval = -1;
  }
  if(VSread(vdata_id_s3_mmonitor, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_mmonitor_error("read_s3_mmonitor -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_mmonitor(odata, mmonitor_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_mmonitor()
{
  VSdetach(vdata_id_s3_mmonitor);
  SDendaccess(sds_id_s3_mmonitor1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_mmonitor(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_mmonitor_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_mmonitor" )) ==FAIL)
    print_s3_mmonitor_error("rd_Vgrp_s3_mmonitor -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_mmonitor_error("rd_Vgrp_s3_mmonitor -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_mmonitor_error("rd_Vgrp_s3_mmonitor -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_mmonitor_error("rd_Vgrp_s3_mmonitor -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_mmonitor, HDstrlen(Vgrp_descrp_mmonitor)) ==FAIL)
    print_s3_mmonitor_error("rd_Vgrp_s3_mmonitor -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_mmonitor);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_mmonitor_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swims_mmonitor.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_mmonitor(uint8 *data, struct mmonitor *mmonitor_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &mmonitor_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mmonitor_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mmonitor_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_mmonitor(uint8 *data, struct mmonitor *mmonitor_ptr)
{
int32 ptr=0;

   memcpy(&mmonitor_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mmonitor_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mmonitor_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_s3_mmonitor() {return(vgrp_id_s3_mmonitor);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_mmonitor(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_mmonitor.h' is shown below, it was used to create the data in the Vgroup named 'VG_mmonitor'.\n\n");
  strcat(wr_strval,"/* Id: s3_mmonitor.h,v 1.3 1997/05/07 23:15:42 jeff Exp $           */\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/*  #define swims_mon_cyclen   64            64*1.0          */\n");
  strcat(wr_strval,"/*  #define swims_mon_cycpersr 60                            */ \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define  MMON_CYC   60    /*  number of cycles per SR = 60/1   */\n");
  strcat(wr_strval,"#define  MMON_TSZ  3840   /*  total size in bytes              */\n");
  strcat(wr_strval,"#define  MMON_CSZ  MMON_TSZ/MMON_CYC\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct mmonitor  {\n");
  strcat(wr_strval,"           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  QAC;         /*  number of missing frames in this SR */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"           uint8  MONITOR[MMON_CYC][MMON_CSZ];   \n");
  strcat(wr_strval,"};\n");
  return(0);
}
