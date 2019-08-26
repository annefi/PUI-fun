/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_dummy.h,v 1.3 1998/09/28 05:31:14 asc Exp  */

#include "s3_dummy.h"
#include "df.h"

int32 vgrp_id_s3_dummy;
static int32 vdata_id_s3_dummy;

  /* 427 is the size of s3_dummy.h + 1 added line */
char Vgrp_descrp_s3_dummy[427];

/****----  init create function  ----****/

int32 init_cr_s3_dummy(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_dummy();

  void print_s3_dummy_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_dummy = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_dummy_error("init_cr_s3_dummy -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_dummy, "VG_s3_dummy"); 
  Vsetclass(vgrp_id_s3_dummy, "VG_S3_DUMMY");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_s3_dummy" )) ==FAIL) {
    print_s3_dummy_error("init_cr_s3_dummy -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_dummy(Vgrp_descrp_s3_dummy);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_dummy_error("init_cr_s3_dummy -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_s3_dummy, sizeof(Vgrp_descrp_s3_dummy))) ==FAIL) {
    print_s3_dummy_error("init_cr_s3_dummy -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_dummy = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_dummy_error("init_cr_s3_dummy -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_dummy, "s3_dummy");
  VSsetclass(vdata_id_s3_dummy, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_dummy, vdata_id_s3_dummy)) ==FAIL) {
    print_s3_dummy_error("init_cr_s3_dummy -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_dummy, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_dummy_error("init_cr_s3_dummy -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dummy, "data", DFNT_UINT8, (203) )) {
    print_s3_dummy_error("init_cr_s3_dummy -> VSfdefine: Couldn't define data");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_dummy,"sctime_readout, data")){
    print_s3_dummy_error("init_cr_s3_dummy -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_dummy(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_dummy(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_dummy(struct s3_dummy s3_dummy_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_dummy_error();
void pack_s3_dummy();

  odata = (uint8 *) malloc(sizeof(struct s3_dummy));
  pack_s3_dummy(odata, &s3_dummy_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_dummy, recnum)==-1) {
		print_s3_dummy_error("write_s3_dummy -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_dummy, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_dummy_error("write_s3_dummy -> VSwrite: Couldn't write data.");

  memset(&s3_dummy_struc, 0, sizeof(struct s3_dummy));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_dummy()
{
  VSdetach(vdata_id_s3_dummy);
  Vdetach(vgrp_id_s3_dummy);
}

/*----     init access function    ----*/

int32 init_acc_s3_dummy(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_dummy_error();


  if ((vdata_ref = VSfind(hdf_fp, "s3_dummy")) <= 0 ) {
    print_s3_dummy_error("init_acc_s3_dummy -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_dummy = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_dummy_error("init_acc_s3_dummy -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_dummy, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_dummy,"sctime_readout, data")) {
      print_s3_dummy_error("init_acc_s3_dummy -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_dummy(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_dummy(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_dummy(struct s3_dummy *s3_dummy_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_dummy_error();
void unpack_s3_dummy();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct s3_dummy));
  VSinquire(vdata_id_s3_dummy, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_dummy, recnum_rd)==FAIL) {
          print_s3_dummy_error("read_s3_dummy -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_dummy, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_dummy_error("read_s3_dummy -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_dummy(odata, s3_dummy_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_dummy()
{
  VSdetach(vdata_id_s3_dummy);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_dummy(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_dummy_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_s3_dummy" )) ==FAIL)
    print_s3_dummy_error("rd_Vgrp_s3_dummy -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_dummy_error("rd_Vgrp_s3_dummy -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_dummy_error("rd_Vgrp_s3_dummy -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_dummy_error("rd_Vgrp_s3_dummy -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_s3_dummy, HDstrlen(Vgrp_descrp_s3_dummy)) ==FAIL)
    print_s3_dummy_error("rd_Vgrp_s3_dummy -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_s3_dummy);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_dummy_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3_dummy.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_dummy(uint8 *data, struct s3_dummy *s3_dummy_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &s3_dummy_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3_dummy_ptr->data[0], ((1)*(203)) );
   ptr+= ((1)*(203));
}

/*----   unpack function    ----*/

void unpack_s3_dummy(uint8 *data, struct s3_dummy *s3_dummy_ptr)
{
int32 ptr=0;

   memcpy(&s3_dummy_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3_dummy_ptr->data[0], data+ptr,  ((1)*(203)) );
   ptr+= ((1)*(203));
}
int32 get_vgrp_id_s3_dummy() {return(vgrp_id_s3_dummy);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_dummy(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_dummy.h' is shown below, it was used to create the data in the Vgroup named 'VG_s3_dummy'.\n\n");
  strcat(wr_strval,"/* Id: s3_dummy.h,v 1.3 1998/09/28 05:31:14 asc Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct s3_dummy\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 sctime_readout;         /* 32 bit spacecraft readout time    */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 data[203];    /* S3 dummy minor frame data */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
