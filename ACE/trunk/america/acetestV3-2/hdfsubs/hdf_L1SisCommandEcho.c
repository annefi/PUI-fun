/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisCommandEcho.h,v 1.2 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisCommandEcho.h"
#include "df.h"

int32 vgrp_id_L1SisCommandEcho;
static int32 vdata_id_L1SisCommandEcho;

  /* 1007 is the size of L1SisCommandEcho.h + 1 added line */
char Vgrp_descrp_L1SisCommandEcho[1007];

/****----  init create function  ----****/

int32 init_cr_L1SisCommandEcho(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1SisCommandEcho();

  void print_L1SisCommandEcho_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisCommandEcho = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisCommandEcho, "VG_L1SisCommandEcho"); 
  Vsetclass(vgrp_id_L1SisCommandEcho, "VG_L1SISCOMMANDECHO");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisCommandEcho" )) ==FAIL) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisCommandEcho(Vgrp_descrp_L1SisCommandEcho);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisCommandEcho, sizeof(Vgrp_descrp_L1SisCommandEcho))) ==FAIL) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisCommandEcho = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisCommandEcho, "L1SisCommandEcho");
  VSsetclass(vdata_id_L1SisCommandEcho, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisCommandEcho, vdata_id_L1SisCommandEcho)) ==FAIL) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisCommandEcho, "ClockMinorFrame", DFNT_UINT32, (1) )) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> VSfdefine: Couldn't define ClockMinorFrame");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandEcho, "Second1996", DFNT_UINT32, (1) )) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandEcho, "microsecond", DFNT_UINT32, (1) )) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandEcho, "NumberChars", DFNT_UINT8, (1) )) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> VSfdefine: Couldn't define NumberChars");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisCommandEcho, "CommandEcho", DFNT_CHAR8, (MAX_NUM_SIS_CMD_ECHO_CHARS) )) {
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> VSfdefine: Couldn't define CommandEcho");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisCommandEcho,"ClockMinorFrame, Second1996, microsecond, NumberChars, CommandEcho")){
    print_L1SisCommandEcho_error("init_cr_L1SisCommandEcho -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisCommandEcho(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisCommandEcho(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisCommandEcho(struct L1SisCommandEcho L1SisCommandEcho_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1SisCommandEcho_error();
void pack_L1SisCommandEcho();

  odata = (uint8 *) malloc(sizeof(struct L1SisCommandEcho));
  pack_L1SisCommandEcho(odata, &L1SisCommandEcho_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1SisCommandEcho, recnum)==-1) {
		print_L1SisCommandEcho_error("write_L1SisCommandEcho -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisCommandEcho, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisCommandEcho_error("write_L1SisCommandEcho -> VSwrite: Couldn't write data.");

  memset(&L1SisCommandEcho_struc, 0, sizeof(struct L1SisCommandEcho));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisCommandEcho()
{
  VSdetach(vdata_id_L1SisCommandEcho);
  Vdetach(vgrp_id_L1SisCommandEcho);
}

/*----     init access function    ----*/

int32 init_acc_L1SisCommandEcho(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisCommandEcho_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1SisCommandEcho")) <= 0 ) {
    print_L1SisCommandEcho_error("init_acc_L1SisCommandEcho -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisCommandEcho = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisCommandEcho_error("init_acc_L1SisCommandEcho -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisCommandEcho, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisCommandEcho,"ClockMinorFrame, Second1996, microsecond, NumberChars, CommandEcho")) {
      print_L1SisCommandEcho_error("init_acc_L1SisCommandEcho -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisCommandEcho(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisCommandEcho(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisCommandEcho(struct L1SisCommandEcho *L1SisCommandEcho_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisCommandEcho_error();
void unpack_L1SisCommandEcho();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1SisCommandEcho));
  VSinquire(vdata_id_L1SisCommandEcho, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisCommandEcho, recnum_rd)==FAIL) {
          print_L1SisCommandEcho_error("read_L1SisCommandEcho -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1SisCommandEcho, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisCommandEcho_error("read_L1SisCommandEcho -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisCommandEcho(odata, L1SisCommandEcho_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisCommandEcho()
{
  VSdetach(vdata_id_L1SisCommandEcho);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisCommandEcho(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisCommandEcho_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisCommandEcho" )) ==FAIL)
    print_L1SisCommandEcho_error("rd_Vgrp_L1SisCommandEcho -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisCommandEcho_error("rd_Vgrp_L1SisCommandEcho -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisCommandEcho_error("rd_Vgrp_L1SisCommandEcho -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisCommandEcho_error("rd_Vgrp_L1SisCommandEcho -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisCommandEcho, HDstrlen(Vgrp_descrp_L1SisCommandEcho)) ==FAIL)
    print_L1SisCommandEcho_error("rd_Vgrp_L1SisCommandEcho -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisCommandEcho);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisCommandEcho_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisCommandEcho.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisCommandEcho(uint8 *data, struct L1SisCommandEcho *L1SisCommandEcho_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisCommandEcho_ptr->ClockMinorFrame, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandEcho_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandEcho_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisCommandEcho_ptr->NumberChars, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisCommandEcho_ptr->CommandEcho[0], ((1)*(MAX_NUM_SIS_CMD_ECHO_CHARS)) );
   ptr+= ((1)*(MAX_NUM_SIS_CMD_ECHO_CHARS));
}

/*----   unpack function    ----*/

void unpack_L1SisCommandEcho(uint8 *data, struct L1SisCommandEcho *L1SisCommandEcho_ptr)
{
int32 ptr=0;

   memcpy(&L1SisCommandEcho_ptr->ClockMinorFrame, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandEcho_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandEcho_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisCommandEcho_ptr->NumberChars, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisCommandEcho_ptr->CommandEcho[0], data+ptr,  ((1)*(MAX_NUM_SIS_CMD_ECHO_CHARS)) );
   ptr+= ((1)*(MAX_NUM_SIS_CMD_ECHO_CHARS));
}
int32 get_vgrp_id_L1SisCommandEcho() {return(vgrp_id_L1SisCommandEcho);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisCommandEcho(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisCommandEcho.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisCommandEcho'.\n\n");
  strcat(wr_strval,"/* Id: L1SisCommandEcho.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisCommandEcho.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisCommandEcho\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint8  NumberChars;\n");
  strcat(wr_strval,"   char8  CommandEcho[MAX_NUM_SIS_CMD_ECHO_CHARS];\n");
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
