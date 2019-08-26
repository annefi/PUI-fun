/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1CrisCommandEcho.h,v 1.3 1997/09/11 00:39:43 jeff Exp  */

#include "L1CrisCommandEcho.h"
#include "df.h"

int32 vgrp_id_L1CrisCommandEcho;
static int32 vdata_id_L1CrisCommandEcho;

  /* 1012 is the size of L1CrisCommandEcho.h + 1 added line */
char Vgrp_descrp_L1CrisCommandEcho[1012];

/****----  init create function  ----****/

int32 init_cr_L1CrisCommandEcho(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1CrisCommandEcho();

  void print_L1CrisCommandEcho_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1CrisCommandEcho = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1CrisCommandEcho, "VG_L1CrisCommandEcho"); 
  Vsetclass(vgrp_id_L1CrisCommandEcho, "VG_L1CRISCOMMANDECHO");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1CrisCommandEcho" )) ==FAIL) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1CrisCommandEcho(Vgrp_descrp_L1CrisCommandEcho);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1CrisCommandEcho, sizeof(Vgrp_descrp_L1CrisCommandEcho))) ==FAIL) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1CrisCommandEcho = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1CrisCommandEcho, "L1CrisCommandEcho");
  VSsetclass(vdata_id_L1CrisCommandEcho, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1CrisCommandEcho, vdata_id_L1CrisCommandEcho)) ==FAIL) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1CrisCommandEcho, "ClockMinorFrame", DFNT_UINT32, (1) )) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> VSfdefine: Couldn't define ClockMinorFrame");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandEcho, "Second1996", DFNT_UINT32, (1) )) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandEcho, "microsecond", DFNT_UINT32, (1) )) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandEcho, "NumberChars", DFNT_UINT8, (1) )) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> VSfdefine: Couldn't define NumberChars");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisCommandEcho, "CommandEcho", DFNT_CHAR8, (MAX_NUM_CRIS_CMD_ECHO_CHARS) )) {
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> VSfdefine: Couldn't define CommandEcho");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1CrisCommandEcho,"ClockMinorFrame, Second1996, microsecond, NumberChars, CommandEcho")){
    print_L1CrisCommandEcho_error("init_cr_L1CrisCommandEcho -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1CrisCommandEcho(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1CrisCommandEcho(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1CrisCommandEcho(struct L1CrisCommandEcho L1CrisCommandEcho_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1CrisCommandEcho_error();
void pack_L1CrisCommandEcho();

  odata = (uint8 *) malloc(sizeof(struct L1CrisCommandEcho));
  pack_L1CrisCommandEcho(odata, &L1CrisCommandEcho_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1CrisCommandEcho, recnum)==-1) {
		print_L1CrisCommandEcho_error("write_L1CrisCommandEcho -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1CrisCommandEcho, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1CrisCommandEcho_error("write_L1CrisCommandEcho -> VSwrite: Couldn't write data.");

  memset(&L1CrisCommandEcho_struc, 0, sizeof(struct L1CrisCommandEcho));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1CrisCommandEcho()
{
  VSdetach(vdata_id_L1CrisCommandEcho);
  Vdetach(vgrp_id_L1CrisCommandEcho);
}

/*----     init access function    ----*/

int32 init_acc_L1CrisCommandEcho(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1CrisCommandEcho_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1CrisCommandEcho")) <= 0 ) {
    print_L1CrisCommandEcho_error("init_acc_L1CrisCommandEcho -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1CrisCommandEcho = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1CrisCommandEcho_error("init_acc_L1CrisCommandEcho -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1CrisCommandEcho, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1CrisCommandEcho,"ClockMinorFrame, Second1996, microsecond, NumberChars, CommandEcho")) {
      print_L1CrisCommandEcho_error("init_acc_L1CrisCommandEcho -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1CrisCommandEcho(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1CrisCommandEcho(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1CrisCommandEcho(struct L1CrisCommandEcho *L1CrisCommandEcho_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1CrisCommandEcho_error();
void unpack_L1CrisCommandEcho();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1CrisCommandEcho));
  VSinquire(vdata_id_L1CrisCommandEcho, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1CrisCommandEcho, recnum_rd)==FAIL) {
          print_L1CrisCommandEcho_error("read_L1CrisCommandEcho -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1CrisCommandEcho, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1CrisCommandEcho_error("read_L1CrisCommandEcho -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1CrisCommandEcho(odata, L1CrisCommandEcho_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1CrisCommandEcho()
{
  VSdetach(vdata_id_L1CrisCommandEcho);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1CrisCommandEcho(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1CrisCommandEcho_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1CrisCommandEcho" )) ==FAIL)
    print_L1CrisCommandEcho_error("rd_Vgrp_L1CrisCommandEcho -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1CrisCommandEcho_error("rd_Vgrp_L1CrisCommandEcho -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1CrisCommandEcho_error("rd_Vgrp_L1CrisCommandEcho -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1CrisCommandEcho_error("rd_Vgrp_L1CrisCommandEcho -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1CrisCommandEcho, HDstrlen(Vgrp_descrp_L1CrisCommandEcho)) ==FAIL)
    print_L1CrisCommandEcho_error("rd_Vgrp_L1CrisCommandEcho -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1CrisCommandEcho);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1CrisCommandEcho_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1CrisCommandEcho.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1CrisCommandEcho(uint8 *data, struct L1CrisCommandEcho *L1CrisCommandEcho_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1CrisCommandEcho_ptr->ClockMinorFrame, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandEcho_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandEcho_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisCommandEcho_ptr->NumberChars, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisCommandEcho_ptr->CommandEcho[0], ((1)*(MAX_NUM_CRIS_CMD_ECHO_CHARS)) );
   ptr+= ((1)*(MAX_NUM_CRIS_CMD_ECHO_CHARS));
}

/*----   unpack function    ----*/

void unpack_L1CrisCommandEcho(uint8 *data, struct L1CrisCommandEcho *L1CrisCommandEcho_ptr)
{
int32 ptr=0;

   memcpy(&L1CrisCommandEcho_ptr->ClockMinorFrame, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandEcho_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandEcho_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisCommandEcho_ptr->NumberChars, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisCommandEcho_ptr->CommandEcho[0], data+ptr,  ((1)*(MAX_NUM_CRIS_CMD_ECHO_CHARS)) );
   ptr+= ((1)*(MAX_NUM_CRIS_CMD_ECHO_CHARS));
}
int32 get_vgrp_id_L1CrisCommandEcho() {return(vgrp_id_L1CrisCommandEcho);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1CrisCommandEcho(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1CrisCommandEcho.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1CrisCommandEcho'.\n\n");
  strcat(wr_strval,"/* Id: L1CrisCommandEcho.h,v 1.3 1997/09/11 00:39:43 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisCommandEcho.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 00:39:43 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"CrisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1CrisCommandEcho\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint8  NumberChars;\n");
  strcat(wr_strval,"   char8  CommandEcho[MAX_NUM_CRIS_CMD_ECHO_CHARS];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockMinorFrame = S/C clock of the minor frame containing the  */\n");
  strcat(wr_strval,"/*                      command echo                                 */\n");
  strcat(wr_strval,"/*    NumberChars = Number of characters in the command echo         */\n");
  strcat(wr_strval,"/*    CommandEcho = Command echo characters                          */\n");
  return(0);
}
