/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_smonitor.h,v 1.6 1998/12/07 18:12:39 ad Exp  */

#include "s3_smonitor.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_smonitor;
static int32 vdata_id_s3_smonitor;

static int32 sds_id_s3_smonitor1;

  /* 1517 is the size of s3_smonitor.h + 1 added line */
char Vgrp_descrp_smonitor[1517];

/****----  init create function  ----****/

int32 init_cr_s3_smonitor(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_smonitor();

  void print_s3_smonitor_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_smonitor = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_smonitor, "VG_smonitor"); 
  Vsetclass(vgrp_id_s3_smonitor, "VG_S3_SMONITOR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_smonitor" )) ==FAIL) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_smonitor(Vgrp_descrp_smonitor);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_smonitor, sizeof(Vgrp_descrp_smonitor))) ==FAIL) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_smonitor = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_smonitor, "smonitor");
  VSsetclass(vdata_id_s3_smonitor, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_smonitor, vdata_id_s3_smonitor)) ==FAIL) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_smonitor, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_smonitor, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_smonitor, "QAC", DFNT_UINT32, (1) )) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_smonitor, "FILL", DFNT_UINT16, (SMON_NFILL) )) {
    print_s3_smonitor_error("init_cr_s3_smonitor -> VSfdefine: Couldn't define FILL");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_smonitor,"sctime_readout, sctime_collection, QAC, FILL")){
    print_s3_smonitor_error("init_cr_s3_smonitor -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SMON_N;
  dim_sizes[2] = SMON_S;
  if((sds_id_s3_smonitor1 = SDcreate(sd_id, "smonitor_MONITOR", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_smonitor_error("init_cr_s3_smonitor -> SDcreate: Couldn't create smonitor_MONITOR");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_smonitor1)) == FAIL)
    print_s3_smonitor_error("init_cr_s3_smonitor -> SDidtoref: Couldn't get ref for smonitor_MONITOR");

  if((Vaddtagref(vgrp_id_s3_smonitor, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_smonitor_error("init_cr_s3_smonitor -> Vaddtagref: Couldn't add SDS smonitor_MONITOR to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_smonitor(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_smonitor(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_smonitor(struct smonitor smonitor_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_smonitor_error();
void pack_s3_smonitor();

  odata = (uint8 *) malloc(sizeof(struct smonitor));
  pack_s3_smonitor(odata, &smonitor_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_smonitor, recnum)==-1) {
		print_s3_smonitor_error("write_s3_smonitor -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_smonitor, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_smonitor_error("write_s3_smonitor -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = SMON_N;
  edges[2] = SMON_S;
  if (SDwritedata(sds_id_s3_smonitor1,start,NULL,edges, (VOIDP)(smonitor_struc.MONITOR)) ==FAIL)
    print_s3_smonitor_error("write_s3_smonitor -> SDwritedata: Problem writing MONITOR data.");

  memset(&smonitor_struc, 0, sizeof(struct smonitor));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_smonitor()
{
  VSdetach(vdata_id_s3_smonitor);
  Vdetach(vgrp_id_s3_smonitor);
  SDendaccess(sds_id_s3_smonitor1);
}

/*----     init access function    ----*/

int32 init_acc_s3_smonitor(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_smonitor_error();

  if((sds_index1=SDnametoindex(sd_id, "smonitor_MONITOR" )) ==FAIL) {
      print_s3_smonitor_error("init_acc_s3_smonitor -> SDnametoindex: Couldn't find smonitor_MONITOR");
      return(-1);
  }
  if((sds_id_s3_smonitor1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_smonitor_error("init_acc_s3_smonitor -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "smonitor")) <= 0 ) {
    print_s3_smonitor_error("init_acc_s3_smonitor -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_smonitor = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_smonitor_error("init_acc_s3_smonitor -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_smonitor, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_smonitor,"sctime_readout, sctime_collection, QAC, FILL")) {
      print_s3_smonitor_error("init_acc_s3_smonitor -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_smonitor(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_smonitor(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_smonitor(struct smonitor *smonitor_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_smonitor_error();
void unpack_s3_smonitor();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct smonitor));
  VSinquire(vdata_id_s3_smonitor, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_smonitor, recnum_rd)==FAIL) {
          print_s3_smonitor_error("read_s3_smonitor -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SMON_N;
  edges[2] = SMON_S;

  if(SDreaddata(sds_id_s3_smonitor1,start,NULL,edges, (VOIDP)(smonitor_struc->MONITOR )) ==FAIL) {
    print_s3_smonitor_error("read_s3_smonitor -> SDreaddata: Couldn't read MONITOR");
    retval = -1;
  }
  if(VSread(vdata_id_s3_smonitor, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_smonitor_error("read_s3_smonitor -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_smonitor(odata, smonitor_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_smonitor()
{
  VSdetach(vdata_id_s3_smonitor);
  SDendaccess(sds_id_s3_smonitor1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_smonitor(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_smonitor_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_smonitor" )) ==FAIL)
    print_s3_smonitor_error("rd_Vgrp_s3_smonitor -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_smonitor_error("rd_Vgrp_s3_smonitor -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_smonitor_error("rd_Vgrp_s3_smonitor -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_smonitor_error("rd_Vgrp_s3_smonitor -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_smonitor, HDstrlen(Vgrp_descrp_smonitor)) ==FAIL)
    print_s3_smonitor_error("rd_Vgrp_s3_smonitor -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_smonitor);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_smonitor_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_smonitor.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_smonitor(uint8 *data, struct smonitor *smonitor_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &smonitor_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &smonitor_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &smonitor_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &smonitor_ptr->FILL[0], ((2)*(SMON_NFILL)) );
   ptr+= ((2)*(SMON_NFILL));
}

/*----   unpack function    ----*/

void unpack_s3_smonitor(uint8 *data, struct smonitor *smonitor_ptr)
{
int32 ptr=0;

   memcpy(&smonitor_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&smonitor_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&smonitor_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&smonitor_ptr->FILL[0], data+ptr,  ((2)*(SMON_NFILL)) );
   ptr+= ((2)*(SMON_NFILL));
}
int32 get_vgrp_id_s3_smonitor() {return(vgrp_id_s3_smonitor);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_smonitor(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_smonitor.h' is shown below, it was used to create the data in the Vgroup named 'VG_smonitor'.\n\n");
  strcat(wr_strval,"/* Id: s3_smonitor.h,v 1.6 1998/12/07 18:12:39 ad Exp $	     */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SMON_N     12  /* number of monitor rates */\n");
  strcat(wr_strval,"#define SMON_S     8  /* number of sectors */\n");
  strcat(wr_strval,"#define SMON_CYC   12  /* number of cycles per SR = 60 / 5 */\n");
  strcat(wr_strval,"#define SMON_NFILL 4  /* amount of fill data elements */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval," /* total size (in bytes) of SMON data (including slack) in a full SR */\n");
  strcat(wr_strval,"#define SMON_TSZ   1800 \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval," /* size (in bytes) of SMON cycle (including slack) */\n");
  strcat(wr_strval,"#define SMON_CSZ   SMON_TSZ/SMON_CYC \n");
  strcat(wr_strval,"#define SMON_ESZ   SMON_TSZ/60  /* size (in bytes) of SMON in EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* monitor rates are collected over 5 spins and output during the next */\n");
  strcat(wr_strval,"/* 5 spins(or edb's). There are 12 matrix rate collection cycles per */\n");
  strcat(wr_strval,"/* Science Record */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_readout: spacecraft clock of first minor frame of the */\n");
  strcat(wr_strval,"/* first edb of the monitor rate output cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_collection:  time of the start of the first spin in the */\n");
  strcat(wr_strval,"/* collection cycle, in spacecraft clock time units */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct smonitor{\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   uint32 sctime_readout;     /* 32 bit spacecraft time  */\n");
  strcat(wr_strval,"   float64 sctime_collection; /* spacecraft time, sub-second resolution */\n");
  strcat(wr_strval,"   uint32 QAC;	/* number of missing frames in this 5-spin cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   uint16 MONITOR[SMON_N][SMON_S];/* 12 Monitor rates, 8 sectors */\n");
  strcat(wr_strval,"   uint16 FILL[SMON_NFILL];    /* Fill  data   */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
