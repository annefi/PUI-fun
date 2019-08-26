/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.40 1997/10/08 01:13:48 jeff Exp $ */

/* The include file used to create this file is: */
/* $Id: sunpulsetime.h,v 1.1 1997/11/17 19:31:17 jeff Exp $ */

#include "sunpulsetime.h"
#include "df.h"

int32 vgrp_id_sunpulsetime_in;
static int32 vdata_id_sunpulsetime_in;

  /* 377 is the size of sunpulsetime.h + 1 added line */
char Vgrp_descrp_ACEsunpulsetime[377];

/****----  init create function  ----****/

int32 init_cr_sunpulsetime_in(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_sunpulsetime_in();

  void print_sunpulsetime_in_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_sunpulsetime_in = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_sunpulsetime_in_error("init_cr_sunpulsetime_in -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_sunpulsetime_in, "VG_ACEsunpulsetime"); 
  Vsetclass(vgrp_id_sunpulsetime_in, "VG_sunpulsetime_in");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_ACEsunpulsetime" )) ==FAIL) {
    print_sunpulsetime_in_error("init_cr_sunpulsetime_in -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_sunpulsetime_in(Vgrp_descrp_ACEsunpulsetime);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_sunpulsetime_in_error("init_cr_sunpulsetime_in -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_ACEsunpulsetime, sizeof(Vgrp_descrp_ACEsunpulsetime))) ==FAIL) {
    print_sunpulsetime_in_error("init_cr_sunpulsetime_in -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_sunpulsetime_in = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_sunpulsetime_in_error("init_cr_sunpulsetime_in -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_sunpulsetime_in, "ACEsunpulsetime");
  VSsetclass(vdata_id_sunpulsetime_in, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_sunpulsetime_in, vdata_id_sunpulsetime_in)) ==FAIL) {
    print_sunpulsetime_in_error("init_cr_sunpulsetime_in -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_sunpulsetime_in, "SPtime", DFNT_FLOAT64, (1) )) {
    print_sunpulsetime_in_error("init_cr_sunpulsetime_in -> VSfdefine: Couldn't define SPtime");
    retval = -1;
  }

  if (VSsetfields(vdata_id_sunpulsetime_in,"SPtime")){
    print_sunpulsetime_in_error("init_cr_sunpulsetime_in -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_sunpulsetime_in(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_sunpulsetime_in(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_sunpulsetime_in(struct ACEsunpulsetime ACEsunpulsetime_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_sunpulsetime_in_error();
void pack_sunpulsetime_in();

  odata = (uint8 *) malloc(sizeof(struct ACEsunpulsetime));
  pack_sunpulsetime_in(odata, &ACEsunpulsetime_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_sunpulsetime_in, recnum)==-1) {
		print_sunpulsetime_in_error("write_sunpulsetime_in -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_sunpulsetime_in, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_sunpulsetime_in_error("write_sunpulsetime_in -> VSwrite: Couldn't write data.");

  memset(&ACEsunpulsetime_struc, 0, sizeof(struct ACEsunpulsetime));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_sunpulsetime_in()
{
  VSdetach(vdata_id_sunpulsetime_in);
  Vdetach(vgrp_id_sunpulsetime_in);
}

/*----     init access function    ----*/

int32 init_acc_sunpulsetime_in(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_sunpulsetime_in_error();


  if ((vdata_ref = VSfind(hdf_fp, "ACEsunpulsetime")) <= 0) {
    print_sunpulsetime_in_error("init_acc_sunpulsetime_in -> VSfind: Found no vdata of specified type");
    return(0);
  }
  if ((vdata_id_sunpulsetime_in = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_sunpulsetime_in_error("init_acc_sunpulsetime_in -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_sunpulsetime_in, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_sunpulsetime_in,"SPtime")) {
      print_sunpulsetime_in_error("init_acc_sunpulsetime_in -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_sunpulsetime_in(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_sunpulsetime_in(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_sunpulsetime_in(struct ACEsunpulsetime *ACEsunpulsetime_struc, int32 recnum_rd)
{
static int32 last_recnum = -1;
int32 maxrec;
int32 retval = 0;
uint8 *odata;

void print_sunpulsetime_in_error();
void unpack_sunpulsetime_in();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct ACEsunpulsetime));
  VSinquire(vdata_id_sunpulsetime_in, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_sunpulsetime_in, recnum_rd)==FAIL) {
          print_sunpulsetime_in_error("read_sunpulsetime_in -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_sunpulsetime_in, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_sunpulsetime_in_error("read_sunpulsetime_in -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_sunpulsetime_in(odata, ACEsunpulsetime_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_sunpulsetime_in()
{
  VSdetach(vdata_id_sunpulsetime_in);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_sunpulsetime_in(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_sunpulsetime_in_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_ACEsunpulsetime" )) ==FAIL)
    print_sunpulsetime_in_error("rd_Vgrp_sunpulsetime_in -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_sunpulsetime_in_error("rd_Vgrp_sunpulsetime_in -> ANnumann: Couldn't get number of annotations.");

printf("1numann= %d \n", num_ann);
    ann_list = HDmalloc(num_ann * sizeof(int32));
printf("1ann_list= %d \n", ann_list);
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_sunpulsetime_in_error("rd_Vgrp_sunpulsetime_in -> ANannlist: Couldn't");

printf("2numann= %d \n", num_ann);
printf("2ann_list= %d \n", ann_list);
  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_sunpulsetime_in_error("rd_Vgrp_sunpulsetime_in -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_ACEsunpulsetime, HDstrlen(Vgrp_descrp_ACEsunpulsetime)) ==FAIL)
    print_sunpulsetime_in_error("rd_Vgrp_sunpulsetime_in -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_ACEsunpulsetime);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_sunpulsetime_in_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sunpulsetime_in.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_sunpulsetime_in(uint8 *data, struct ACEsunpulsetime *ACEsunpulsetime_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &ACEsunpulsetime_ptr->SPtime, ((8)*(1)) );
   ptr+= ((8)*(1));
}

/*----   unpack function    ----*/

void unpack_sunpulsetime_in(uint8 *data, struct ACEsunpulsetime *ACEsunpulsetime_ptr)
{
int32 ptr=0;

   memcpy(&ACEsunpulsetime_ptr->SPtime, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
}
int32 get_vgrp_id_sunpulsetime_in() {return(vgrp_id_sunpulsetime_in);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_sunpulsetime_in(char *wr_strval)
{
  strcat(wr_strval, "The file 'sunpulsetime.h' is shown below, it was used to create the data in the Vgroup named 'VG_ACEsunpulsetime'.\n\n");
  strcat(wr_strval,"/* $Id: sunpulsetime.h,v 1.1 1997/11/17 19:31:17 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct ACEsunpulsetime\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64  SPtime;  /* ACE sun pulse times in units of SC clock */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
