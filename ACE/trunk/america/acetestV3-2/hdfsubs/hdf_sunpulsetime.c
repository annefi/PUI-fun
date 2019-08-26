/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: sunpulsetime.h,v 1.2 1998/06/17 17:26:10 ad Exp  */

#include "sunpulsetime.h"
#include "df.h"

int32 vgrp_id_sunpulsetime;
static int32 vdata_id_sunpulsetime;

  /* 581 is the size of sunpulsetime.h + 1 added line */
char Vgrp_descrp_ACEsunpulsetime[581];

/****----  init create function  ----****/

int32 init_cr_sunpulsetime(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_sunpulsetime();

  void print_sunpulsetime_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_sunpulsetime = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_sunpulsetime_error("init_cr_sunpulsetime -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_sunpulsetime, "VG_ACEsunpulsetime"); 
  Vsetclass(vgrp_id_sunpulsetime, "VG_SUNPULSETIME");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_ACEsunpulsetime" )) ==FAIL) {
    print_sunpulsetime_error("init_cr_sunpulsetime -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_sunpulsetime(Vgrp_descrp_ACEsunpulsetime);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_sunpulsetime_error("init_cr_sunpulsetime -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_ACEsunpulsetime, sizeof(Vgrp_descrp_ACEsunpulsetime))) ==FAIL) {
    print_sunpulsetime_error("init_cr_sunpulsetime -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_sunpulsetime = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_sunpulsetime_error("init_cr_sunpulsetime -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_sunpulsetime, "ACEsunpulsetime");
  VSsetclass(vdata_id_sunpulsetime, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_sunpulsetime, vdata_id_sunpulsetime)) ==FAIL) {
    print_sunpulsetime_error("init_cr_sunpulsetime -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_sunpulsetime, "SPtime", DFNT_FLOAT64, (1) )) {
    print_sunpulsetime_error("init_cr_sunpulsetime -> VSfdefine: Couldn't define SPtime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sunpulsetime, "flag", DFNT_UINT8, (1) )) {
    print_sunpulsetime_error("init_cr_sunpulsetime -> VSfdefine: Couldn't define flag");
    retval = -1;
  }

  if (VSsetfields(vdata_id_sunpulsetime,"SPtime, flag")){
    print_sunpulsetime_error("init_cr_sunpulsetime -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_sunpulsetime(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_sunpulsetime(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_sunpulsetime(struct ACEsunpulsetime ACEsunpulsetime_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_sunpulsetime_error();
void pack_sunpulsetime();

  odata = (uint8 *) malloc(sizeof(struct ACEsunpulsetime));
  pack_sunpulsetime(odata, &ACEsunpulsetime_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_sunpulsetime, recnum)==-1) {
		print_sunpulsetime_error("write_sunpulsetime -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_sunpulsetime, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_sunpulsetime_error("write_sunpulsetime -> VSwrite: Couldn't write data.");

  memset(&ACEsunpulsetime_struc, 0, sizeof(struct ACEsunpulsetime));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_sunpulsetime()
{
  VSdetach(vdata_id_sunpulsetime);
  Vdetach(vgrp_id_sunpulsetime);
}

/*----     init access function    ----*/

int32 init_acc_sunpulsetime(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_sunpulsetime_error();


  if ((vdata_ref = VSfind(hdf_fp, "ACEsunpulsetime")) <= 0 ) {
    print_sunpulsetime_error("init_acc_sunpulsetime -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_sunpulsetime = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_sunpulsetime_error("init_acc_sunpulsetime -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_sunpulsetime, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_sunpulsetime,"SPtime, flag")) {
      print_sunpulsetime_error("init_acc_sunpulsetime -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_sunpulsetime(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_sunpulsetime(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_sunpulsetime(struct ACEsunpulsetime *ACEsunpulsetime_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_sunpulsetime_error();
void unpack_sunpulsetime();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct ACEsunpulsetime));
  VSinquire(vdata_id_sunpulsetime, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_sunpulsetime, recnum_rd)==FAIL) {
          print_sunpulsetime_error("read_sunpulsetime -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_sunpulsetime, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_sunpulsetime_error("read_sunpulsetime -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_sunpulsetime(odata, ACEsunpulsetime_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_sunpulsetime()
{
  VSdetach(vdata_id_sunpulsetime);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_sunpulsetime(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_sunpulsetime_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_ACEsunpulsetime" )) ==FAIL)
    print_sunpulsetime_error("rd_Vgrp_sunpulsetime -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_sunpulsetime_error("rd_Vgrp_sunpulsetime -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_sunpulsetime_error("rd_Vgrp_sunpulsetime -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_sunpulsetime_error("rd_Vgrp_sunpulsetime -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_ACEsunpulsetime, HDstrlen(Vgrp_descrp_ACEsunpulsetime)) ==FAIL)
    print_sunpulsetime_error("rd_Vgrp_sunpulsetime -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_ACEsunpulsetime);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_sunpulsetime_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sunpulsetime.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_sunpulsetime(uint8 *data, struct ACEsunpulsetime *ACEsunpulsetime_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &ACEsunpulsetime_ptr->SPtime, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &ACEsunpulsetime_ptr->flag, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_sunpulsetime(uint8 *data, struct ACEsunpulsetime *ACEsunpulsetime_ptr)
{
int32 ptr=0;

   memcpy(&ACEsunpulsetime_ptr->SPtime, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&ACEsunpulsetime_ptr->flag, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_sunpulsetime() {return(vgrp_id_sunpulsetime);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_sunpulsetime(char *wr_strval)
{
  strcpy(wr_strval, "The file 'sunpulsetime.h' is shown below, it was used to create the data in the Vgroup named 'VG_ACEsunpulsetime'.\n\n");
  strcat(wr_strval,"/* Id: sunpulsetime.h,v 1.2 1998/06/17 17:26:10 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct ACEsunpulsetime\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64  SPtime;  /* ACE sun pulse times in units of SC clock */\n");
  strcat(wr_strval,"  uint8    flag;    /* 0 if calculated from sunpulse time tags (normal) */\n");
  strcat(wr_strval,"                    /* 1 if calculated from spinphase clock values which */\n");
  strcat(wr_strval,"		    /* are latched every minor frame (not normal) */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
