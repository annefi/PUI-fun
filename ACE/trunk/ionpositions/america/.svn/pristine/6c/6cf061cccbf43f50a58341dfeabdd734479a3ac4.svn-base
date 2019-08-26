/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_drawe.h,v 1.1 1997/06/20 18:02:10 jeff Exp  */

#include "swepam_drawe.h"
#include "df.h"

int32 vgrp_id_swepam_drawe;
static int32 vdata_id_swepam_drawe;

  /* 565 is the size of swepam_drawe.h + 1 added line */
char Vgrp_descrp_DRAWE[565];

/****----  init create function  ----****/

int32 init_cr_swepam_drawe(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_swepam_drawe();

  void print_swepam_drawe_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_drawe = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_drawe, "VG_DRAWE"); 
  Vsetclass(vgrp_id_swepam_drawe, "VG_SWEPAM_DRAWE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_DRAWE" )) ==FAIL) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_drawe(Vgrp_descrp_DRAWE);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_DRAWE, sizeof(Vgrp_descrp_DRAWE))) ==FAIL) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_drawe = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_drawe, "DRAWE");
  VSsetclass(vdata_id_swepam_drawe, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_drawe, vdata_id_swepam_drawe)) ==FAIL) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_drawe, "output_sctime", DFNT_UINT32, (1) )) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_drawe, "collect_sctime", DFNT_UINT32, (1) )) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_drawe, "QAC", DFNT_UINT8, (1) )) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_drawe, "rawdat", DFNT_UINT8, (16*57) )) {
    print_swepam_drawe_error("init_cr_swepam_drawe -> VSfdefine: Couldn't define rawdat");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_drawe,"output_sctime, collect_sctime, QAC, rawdat")){
    print_swepam_drawe_error("init_cr_swepam_drawe -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_drawe(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_drawe(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_drawe(struct DRAWE DRAWE_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_swepam_drawe_error();
void pack_swepam_drawe();

  odata = (uint8 *) malloc(sizeof(struct DRAWE));
  pack_swepam_drawe(odata, &DRAWE_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_swepam_drawe, recnum)==-1) {
		print_swepam_drawe_error("write_swepam_drawe -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_drawe, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_drawe_error("write_swepam_drawe -> VSwrite: Couldn't write data.");

  memset(&DRAWE_struc, 0, sizeof(struct DRAWE));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_drawe()
{
  VSdetach(vdata_id_swepam_drawe);
  Vdetach(vgrp_id_swepam_drawe);
}

/*----     init access function    ----*/

int32 init_acc_swepam_drawe(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_drawe_error();


  if ((vdata_ref = VSfind(hdf_fp, "DRAWE")) <= 0 ) {
    print_swepam_drawe_error("init_acc_swepam_drawe -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_drawe = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_drawe_error("init_acc_swepam_drawe -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_drawe, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_drawe,"output_sctime, collect_sctime, QAC, rawdat")) {
      print_swepam_drawe_error("init_acc_swepam_drawe -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_drawe(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_drawe(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_drawe(struct DRAWE *DRAWE_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_drawe_error();
void unpack_swepam_drawe();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct DRAWE));
  VSinquire(vdata_id_swepam_drawe, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_drawe, recnum_rd)==FAIL) {
          print_swepam_drawe_error("read_swepam_drawe -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_swepam_drawe, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_drawe_error("read_swepam_drawe -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_drawe(odata, DRAWE_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_drawe()
{
  VSdetach(vdata_id_swepam_drawe);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_drawe(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_drawe_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_DRAWE" )) ==FAIL)
    print_swepam_drawe_error("rd_Vgrp_swepam_drawe -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_drawe_error("rd_Vgrp_swepam_drawe -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_drawe_error("rd_Vgrp_swepam_drawe -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_drawe_error("rd_Vgrp_swepam_drawe -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_DRAWE, HDstrlen(Vgrp_descrp_DRAWE)) ==FAIL)
    print_swepam_drawe_error("rd_Vgrp_swepam_drawe -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_DRAWE);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_drawe_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_drawe.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_drawe(uint8 *data, struct DRAWE *DRAWE_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &DRAWE_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DRAWE_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DRAWE_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DRAWE_ptr->rawdat[0], ((1)*(16*57)) );
   ptr+= ((1)*(16*57));
}

/*----   unpack function    ----*/

void unpack_swepam_drawe(uint8 *data, struct DRAWE *DRAWE_ptr)
{
int32 ptr=0;

   memcpy(&DRAWE_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DRAWE_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DRAWE_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DRAWE_ptr->rawdat[0], data+ptr,  ((1)*(16*57)) );
   ptr+= ((1)*(16*57));
}
int32 get_vgrp_id_swepam_drawe() {return(vgrp_id_swepam_drawe);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_drawe(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_drawe.h' is shown below, it was used to create the data in the Vgroup named 'VG_DRAWE'.\n\n");
  strcat(wr_strval,"/* Id: swepam_drawe.h,v 1.1 1997/06/20 18:02:10 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct DRAWE\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;   /* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;  /* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint8  QAC;             /* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 rawdat[16*57];  /* One SWEPAM-E minor frame */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
