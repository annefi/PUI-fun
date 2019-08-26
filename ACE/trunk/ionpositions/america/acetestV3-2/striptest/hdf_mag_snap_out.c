/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.40 1997/10/08 01:13:48 jeff Exp $ */

/* The include file used to create this file is: */
/* $Id: mag_snapshot.h,v 1.6 1997/05/07 18:44:38 jeff Exp $ */

#include "mag_snapshot.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_mag_snap_out;
static int32 vdata_id_mag_snap_out;

static int32 sds_id_mag_snap_out1;

  /* 784 is the size of mag_snapshot.h + 1 added line */
char Vgrp_descrp_MagSnapSet[784];

/****----  init create function  ----****/

int32 init_cr_mag_snap_out(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_mag_snap_out();

  void print_mag_snap_out_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_mag_snap_out = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_mag_snap_out, "VG_MagSnapSet"); 
  Vsetclass(vgrp_id_mag_snap_out, "VG_mag_snap_outSHOT");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_MagSnapSet" )) ==FAIL) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_mag_snap_out(Vgrp_descrp_MagSnapSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_MagSnapSet, sizeof(Vgrp_descrp_MagSnapSet))) ==FAIL) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_mag_snap_out = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_mag_snap_out, "MagSnapSet");
  VSsetclass(vdata_id_mag_snap_out, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_mag_snap_out, vdata_id_mag_snap_out)) ==FAIL) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_mag_snap_out, "sctime_readout", DFNT_UINT32, (1) )) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_snap_out, "sctime_collection", DFNT_UINT32, (1) )) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_snap_out, "QAC", DFNT_UINT32, (1) )) {
    print_mag_snap_out_error("init_cr_mag_snap_out -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }

  if (VSsetfields(vdata_id_mag_snap_out,"sctime_readout, sctime_collection, QAC")){
    print_mag_snap_out_error("init_cr_mag_snap_out -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 3;
  dim_sizes[2] = SNPVAL*SNAPCYCLELEN;
  if((sds_id_mag_snap_out1 = SDcreate(sd_id, "MagSnapSet_hxyz", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_mag_snap_out_error("init_cr_mag_snap_out -> SDcreate: Couldn't create MagSnapSet_hxyz");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_mag_snap_out1)) == FAIL)
    print_mag_snap_out_error("init_cr_mag_snap_out -> SDidtoref: Couldn't get ref for MagSnapSet_hxyz");

  if((Vaddtagref(vgrp_id_mag_snap_out, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_mag_snap_out_error("init_cr_mag_snap_out -> Vaddtagref: Couldn't add SDS MagSnapSet_hxyz to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_mag_snap_out(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_mag_snap_out(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_mag_snap_out(struct MagSnapSet MagSnapSet_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_mag_snap_out_error();
void pack_mag_snap_out();

  odata = (uint8 *) malloc(sizeof(struct MagSnapSet));
  pack_mag_snap_out(odata, &MagSnapSet_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_mag_snap_out, recnum)==-1) {
		print_mag_snap_out_error("write_mag_snap_out -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_mag_snap_out, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_mag_snap_out_error("write_mag_snap_out -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 3;
  edges[2] = SNPVAL*SNAPCYCLELEN;
  if (SDwritedata(sds_id_mag_snap_out1,start,NULL,edges, (VOIDP)(MagSnapSet_struc.hxyz)) ==FAIL)
    print_mag_snap_out_error("write_mag_snap_out -> SDwritedata: Problem writing hxyz data.");

  memset(&MagSnapSet_struc, 0, sizeof(struct MagSnapSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_mag_snap_out()
{
  VSdetach(vdata_id_mag_snap_out);
  Vdetach(vgrp_id_mag_snap_out);
  SDendaccess(sds_id_mag_snap_out1);
}

/*----     init access function    ----*/

int32 init_acc_mag_snap_out(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_mag_snap_out_error();

   if((sds_index1=SDnametoindex(sd_id, "MagSnapSet_hxyz" )) ==FAIL) {
      print_mag_snap_out_error("init_acc_mag_snap_out -> SDnametoindex: Couldn't find MagSnapSet_hxyz");
      return(-1);
  }
  if((sds_id_mag_snap_out1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_mag_snap_out_error("init_acc_mag_snap_out -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "MagSnapSet")) <= 0) {
    print_mag_snap_out_error("init_acc_mag_snap_out -> VSfind: Found no vdata of specified type");
    return(0);
  }
  if ((vdata_id_mag_snap_out = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_mag_snap_out_error("init_acc_mag_snap_out -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_mag_snap_out, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_mag_snap_out,"sctime_readout, sctime_collection, QAC")) {
      print_mag_snap_out_error("init_acc_mag_snap_out -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_mag_snap_out(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_mag_snap_out(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_mag_snap_out(struct MagSnapSet *MagSnapSet_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
static int32 last_recnum = -1;
int32 maxrec;
int32 retval = 0;
uint8 *odata;

void print_mag_snap_out_error();
void unpack_mag_snap_out();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct MagSnapSet));
  VSinquire(vdata_id_mag_snap_out, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_mag_snap_out, recnum_rd)==FAIL) {
          print_mag_snap_out_error("read_mag_snap_out -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 3;
  edges[2] = SNPVAL*SNAPCYCLELEN;

  if(SDreaddata(sds_id_mag_snap_out1,start,NULL,edges, (VOIDP)(MagSnapSet_struc->hxyz )) ==FAIL) {
    print_mag_snap_out_error("read_mag_snap_out -> SDreaddata: Couldn't read hxyz");
    retval = -1;
  }
  if(VSread(vdata_id_mag_snap_out, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_mag_snap_out_error("read_mag_snap_out -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_mag_snap_out(odata, MagSnapSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_mag_snap_out()
{
  VSdetach(vdata_id_mag_snap_out);
  SDendaccess(sds_id_mag_snap_out1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_mag_snap_out(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_mag_snap_out_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_MagSnapSet" )) ==FAIL)
    print_mag_snap_out_error("rd_Vgrp_mag_snap_out -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_mag_snap_out_error("rd_Vgrp_mag_snap_out -> ANnumann: Couldn't get number of annotations.");

printf("1numann= %d \n", num_ann);
    ann_list = HDmalloc(num_ann * sizeof(int32));
printf("1ann_list= %d \n", ann_list);
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_mag_snap_out_error("rd_Vgrp_mag_snap_out -> ANannlist: Couldn't");

printf("2numann= %d \n", num_ann);
printf("2ann_list= %d \n", ann_list);
  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_mag_snap_out_error("rd_Vgrp_mag_snap_out -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_MagSnapSet, HDstrlen(Vgrp_descrp_MagSnapSet)) ==FAIL)
    print_mag_snap_out_error("rd_Vgrp_mag_snap_out -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_MagSnapSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_mag_snap_out_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_mag_snap_out.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_mag_snap_out(uint8 *data, struct MagSnapSet *MagSnapSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &MagSnapSet_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagSnapSet_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagSnapSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_mag_snap_out(uint8 *data, struct MagSnapSet *MagSnapSet_ptr)
{
int32 ptr=0;

   memcpy(&MagSnapSet_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagSnapSet_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagSnapSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_mag_snap_out() {return(vgrp_id_mag_snap_out);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_mag_snap_out(char *wr_strval)
{
  strcat(wr_strval, "The file 'mag_snapshot.h' is shown below, it was used to create the data in the Vgroup named 'VG_MagSnapSet'.\n\n");
  strcat(wr_strval,"/* $Id: mag_snapshot.h,v 1.6 1997/05/07 18:44:38 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SNPVAL 21\n");
  strcat(wr_strval,"#define SNAPCYCLELEN 340  /* The snapshot buffer is 340 major frames long */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct MagSnapSet                   /* setkey=sG                     */\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 sctime_readout;            /* 32 bit spacecraft readout time  */\n");
  strcat(wr_strval,"  uint32 sctime_collection;            /* 32 bit spacecraft collection time  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 QAC;                       /* number of missing frames in this cycle*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"         /* 21 x, y and z values per major frame  */\n");
  strcat(wr_strval,"  uint16 hxyz[3][SNPVAL*SNAPCYCLELEN];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
