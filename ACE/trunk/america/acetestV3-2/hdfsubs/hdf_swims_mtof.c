/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_mtof.h,v 1.3 1997/05/07 23:15:42 jeff Exp  */

#include "s3_mtof.h"
#include "df.h"

int32 vgrp_id_s3_mtof;
static int32 vdata_id_s3_mtof;

  /* 730 is the size of s3_mtof.h + 1 added line */
char Vgrp_descrp_mtof[730];

/****----  init create function  ----****/

int32 init_cr_s3_mtof(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_mtof();

  void print_s3_mtof_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_mtof = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_mtof_error("init_cr_s3_mtof -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_mtof, "VG_mtof"); 
  Vsetclass(vgrp_id_s3_mtof, "VG_S3_MTOF");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_mtof" )) ==FAIL) {
    print_s3_mtof_error("init_cr_s3_mtof -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_mtof(Vgrp_descrp_mtof);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_mtof_error("init_cr_s3_mtof -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_mtof, sizeof(Vgrp_descrp_mtof))) ==FAIL) {
    print_s3_mtof_error("init_cr_s3_mtof -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_mtof = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_mtof_error("init_cr_s3_mtof -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_mtof, "mtof");
  VSsetclass(vdata_id_s3_mtof, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_mtof, vdata_id_s3_mtof)) ==FAIL) {
    print_s3_mtof_error("init_cr_s3_mtof -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_mtof, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_mtof_error("init_cr_s3_mtof -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mtof, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_mtof_error("init_cr_s3_mtof -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mtof, "QAC", DFNT_UINT32, (1) )) {
    print_s3_mtof_error("init_cr_s3_mtof -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mtof, "MTOF", DFNT_UINT8, (MTIME_TSZ) )) {
    print_s3_mtof_error("init_cr_s3_mtof -> VSfdefine: Couldn't define MTOF");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_mtof,"sctime_readout, sctime_collection, QAC, MTOF")){
    print_s3_mtof_error("init_cr_s3_mtof -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_mtof(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_mtof(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_mtof(struct mtof mtof_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_mtof_error();
void pack_s3_mtof();

  odata = (uint8 *) malloc(sizeof(struct mtof));
  pack_s3_mtof(odata, &mtof_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_mtof, recnum)==-1) {
		print_s3_mtof_error("write_s3_mtof -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_mtof, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_mtof_error("write_s3_mtof -> VSwrite: Couldn't write data.");

  memset(&mtof_struc, 0, sizeof(struct mtof));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_mtof()
{
  VSdetach(vdata_id_s3_mtof);
  Vdetach(vgrp_id_s3_mtof);
}

/*----     init access function    ----*/

int32 init_acc_s3_mtof(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_mtof_error();


  if ((vdata_ref = VSfind(hdf_fp, "mtof")) <= 0 ) {
    print_s3_mtof_error("init_acc_s3_mtof -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_mtof = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_mtof_error("init_acc_s3_mtof -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_mtof, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_mtof,"sctime_readout, sctime_collection, QAC, MTOF")) {
      print_s3_mtof_error("init_acc_s3_mtof -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_mtof(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_mtof(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_mtof(struct mtof *mtof_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_mtof_error();
void unpack_s3_mtof();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct mtof));
  VSinquire(vdata_id_s3_mtof, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_mtof, recnum_rd)==FAIL) {
          print_s3_mtof_error("read_s3_mtof -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_mtof, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_mtof_error("read_s3_mtof -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_mtof(odata, mtof_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_mtof()
{
  VSdetach(vdata_id_s3_mtof);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_mtof(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_mtof_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_mtof" )) ==FAIL)
    print_s3_mtof_error("rd_Vgrp_s3_mtof -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_mtof_error("rd_Vgrp_s3_mtof -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_mtof_error("rd_Vgrp_s3_mtof -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_mtof_error("rd_Vgrp_s3_mtof -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_mtof, HDstrlen(Vgrp_descrp_mtof)) ==FAIL)
    print_s3_mtof_error("rd_Vgrp_s3_mtof -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_mtof);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_mtof_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swims_mtof.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_mtof(uint8 *data, struct mtof *mtof_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &mtof_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mtof_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mtof_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mtof_ptr->MTOF[0], ((1)*(MTIME_TSZ)) );
   ptr+= ((1)*(MTIME_TSZ));
}

/*----   unpack function    ----*/

void unpack_s3_mtof(uint8 *data, struct mtof *mtof_ptr)
{
int32 ptr=0;

   memcpy(&mtof_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mtof_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mtof_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mtof_ptr->MTOF[0], data+ptr,  ((1)*(MTIME_TSZ)) );
   ptr+= ((1)*(MTIME_TSZ));
}
int32 get_vgrp_id_s3_mtof() {return(vgrp_id_s3_mtof);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_mtof(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_mtof.h' is shown below, it was used to create the data in the Vgroup named 'VG_mtof'.\n\n");
  strcat(wr_strval,"/* Id: s3_mtof.h,v 1.3 1997/05/07 23:15:42 jeff Exp $           */\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define  MTIME_CYC   1    /* number of cycle per SR=  60/60   */\n");
  strcat(wr_strval,"#define  MTIME_TSZ  2100  /* total size in bytes  */\n");
  strcat(wr_strval,"#define  MTIME_CSZ  MTIME_TSZ/MTIME_CYC\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct mtof  {\n");
  strcat(wr_strval,"           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  QAC;         /*  number of missing frames in this SR */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"           uint8  MTOF[MTIME_TSZ];     \n");
  strcat(wr_strval,"};\n");
  return(0);
}
