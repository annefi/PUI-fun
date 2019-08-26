/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1CrisSubset.h,v 1.2 1997/09/11 00:37:38 jeff Exp  */

#include "L1CrisSubset.h"
#include "df.h"

int32 vgrp_id_L1CrisSubset;
static int32 vdata_id_L1CrisSubset;

  /* 2875 is the size of L1CrisSubset.h + 1 added line */
char Vgrp_descrp_L1CrisSubset[2875];

/****----  init create function  ----****/

int32 init_cr_L1CrisSubset(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1CrisSubset();

  void print_L1CrisSubset_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1CrisSubset = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1CrisSubset, "VG_L1CrisSubset"); 
  Vsetclass(vgrp_id_L1CrisSubset, "VG_L1CRISSUBSET");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1CrisSubset" )) ==FAIL) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1CrisSubset(Vgrp_descrp_L1CrisSubset);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1CrisSubset, sizeof(Vgrp_descrp_L1CrisSubset))) ==FAIL) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1CrisSubset = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1CrisSubset, "L1CrisSubset");
  VSsetclass(vdata_id_L1CrisSubset, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1CrisSubset, vdata_id_L1CrisSubset)) ==FAIL) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1CrisSubset, "ClockMinorFrame", DFNT_UINT32, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define ClockMinorFrame");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "Second1996", DFNT_UINT32, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "microsecond", DFNT_UINT32, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "FormatId", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define FormatId");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "MajorFrameCount", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define MajorFrameCount");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "MinorFrameCount", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define MinorFrameCount");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "quality", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define quality");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "MainBusVoltage", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define MainBusVoltage");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "CrisCurrent", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define CrisCurrent");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "CrisInternalTemperature1", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define CrisInternalTemperature1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "CrisInternalTemperature2", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define CrisInternalTemperature2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "CrisInterfaceTemperature", DFNT_UINT8, (1) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define CrisInterfaceTemperature");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSubset, "CrisData", DFNT_UINT8, (NUM_CRIS_TELEMETRY_BYTES) )) {
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSfdefine: Couldn't define CrisData");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1CrisSubset,"ClockMinorFrame, Second1996, microsecond, FormatId, MajorFrameCount, MinorFrameCount, quality, MainBusVoltage, CrisCurrent, CrisInternalTemperature1, CrisInternalTemperature2, CrisInterfaceTemperature, CrisData")){
    print_L1CrisSubset_error("init_cr_L1CrisSubset -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1CrisSubset(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1CrisSubset(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1CrisSubset(struct L1CrisSubset L1CrisSubset_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1CrisSubset_error();
void pack_L1CrisSubset();

  odata = (uint8 *) malloc(sizeof(struct L1CrisSubset));
  pack_L1CrisSubset(odata, &L1CrisSubset_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1CrisSubset, recnum)==-1) {
		print_L1CrisSubset_error("write_L1CrisSubset -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1CrisSubset, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1CrisSubset_error("write_L1CrisSubset -> VSwrite: Couldn't write data.");

  memset(&L1CrisSubset_struc, 0, sizeof(struct L1CrisSubset));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1CrisSubset()
{
  VSdetach(vdata_id_L1CrisSubset);
  Vdetach(vgrp_id_L1CrisSubset);
}

/*----     init access function    ----*/

int32 init_acc_L1CrisSubset(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1CrisSubset_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1CrisSubset")) <= 0 ) {
    print_L1CrisSubset_error("init_acc_L1CrisSubset -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1CrisSubset = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1CrisSubset_error("init_acc_L1CrisSubset -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1CrisSubset, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1CrisSubset,"ClockMinorFrame, Second1996, microsecond, FormatId, MajorFrameCount, MinorFrameCount, quality, MainBusVoltage, CrisCurrent, CrisInternalTemperature1, CrisInternalTemperature2, CrisInterfaceTemperature, CrisData")) {
      print_L1CrisSubset_error("init_acc_L1CrisSubset -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1CrisSubset(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1CrisSubset(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1CrisSubset(struct L1CrisSubset *L1CrisSubset_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1CrisSubset_error();
void unpack_L1CrisSubset();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1CrisSubset));
  VSinquire(vdata_id_L1CrisSubset, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1CrisSubset, recnum_rd)==FAIL) {
          print_L1CrisSubset_error("read_L1CrisSubset -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1CrisSubset, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1CrisSubset_error("read_L1CrisSubset -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1CrisSubset(odata, L1CrisSubset_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1CrisSubset()
{
  VSdetach(vdata_id_L1CrisSubset);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1CrisSubset(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1CrisSubset_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1CrisSubset" )) ==FAIL)
    print_L1CrisSubset_error("rd_Vgrp_L1CrisSubset -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1CrisSubset_error("rd_Vgrp_L1CrisSubset -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1CrisSubset_error("rd_Vgrp_L1CrisSubset -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1CrisSubset_error("rd_Vgrp_L1CrisSubset -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1CrisSubset, HDstrlen(Vgrp_descrp_L1CrisSubset)) ==FAIL)
    print_L1CrisSubset_error("rd_Vgrp_L1CrisSubset -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1CrisSubset);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1CrisSubset_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1CrisSubset.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1CrisSubset(uint8 *data, struct L1CrisSubset *L1CrisSubset_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1CrisSubset_ptr->ClockMinorFrame, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->FormatId, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->MajorFrameCount, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->MinorFrameCount, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->quality, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->MainBusVoltage, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->CrisCurrent, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->CrisInternalTemperature1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->CrisInternalTemperature2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->CrisInterfaceTemperature, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSubset_ptr->CrisData[0], ((1)*(NUM_CRIS_TELEMETRY_BYTES)) );
   ptr+= ((1)*(NUM_CRIS_TELEMETRY_BYTES));
}

/*----   unpack function    ----*/

void unpack_L1CrisSubset(uint8 *data, struct L1CrisSubset *L1CrisSubset_ptr)
{
int32 ptr=0;

   memcpy(&L1CrisSubset_ptr->ClockMinorFrame, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisSubset_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisSubset_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisSubset_ptr->FormatId, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->MajorFrameCount, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->MinorFrameCount, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->quality, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->MainBusVoltage, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->CrisCurrent, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->CrisInternalTemperature1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->CrisInternalTemperature2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->CrisInterfaceTemperature, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSubset_ptr->CrisData[0], data+ptr,  ((1)*(NUM_CRIS_TELEMETRY_BYTES)) );
   ptr+= ((1)*(NUM_CRIS_TELEMETRY_BYTES));
}
int32 get_vgrp_id_L1CrisSubset() {return(vgrp_id_L1CrisSubset);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1CrisSubset(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1CrisSubset.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1CrisSubset'.\n\n");
  strcat(wr_strval,"/* Id: L1CrisSubset.h,v 1.2 1997/09/11 00:37:38 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisSubset.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 00:37:38 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"CrisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1CrisSubset\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint8  FormatId;\n");
  strcat(wr_strval,"   uint8  MajorFrameCount;\n");
  strcat(wr_strval,"   uint8  MinorFrameCount;\n");
  strcat(wr_strval,"   uint8  quality;\n");
  strcat(wr_strval,"   uint8  MainBusVoltage;\n");
  strcat(wr_strval,"   uint8  CrisCurrent;\n");
  strcat(wr_strval,"   uint8  CrisInternalTemperature1;\n");
  strcat(wr_strval,"   uint8  CrisInternalTemperature2;\n");
  strcat(wr_strval,"   uint8  CrisInterfaceTemperature;\n");
  strcat(wr_strval,"   uint8  CrisData[NUM_CRIS_TELEMETRY_BYTES];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockMinorFrame = S/C clock of the minor frame                 */\n");
  strcat(wr_strval,"/*    Second1996 = Time of the minor frame in seconds since 00:00:00 */\n");
  strcat(wr_strval,"/*                 of January 1, 1996                                */\n");
  strcat(wr_strval,"/*    microsecond = Microseconds of the time of the minor frame      */\n");
  strcat(wr_strval,"/*    FormatId = Format of the minor frame                           */\n");
  strcat(wr_strval,"/*    MajorFrameCount = Major frame count of the minor frame         */\n");
  strcat(wr_strval,"/*    MinorFrameCount = Minor frame count of the minor frame         */\n");
  strcat(wr_strval,"/*    quality = Quality flag associated with the minor frame         */\n");
  strcat(wr_strval,"/*              0x01 = Format ID error                               */\n");
  strcat(wr_strval,"/*              0x02 = Minor/major counter error                     */\n");
  strcat(wr_strval,"/*              0x04 = S/C clock error                               */\n");
  strcat(wr_strval,"/*              0x08 = Sync bit error                                */\n");
  strcat(wr_strval,"/*              0x10 = Command table index error                     */\n");
  strcat(wr_strval,"/*              0x20 = Cycle number error                            */\n");
  strcat(wr_strval,"/*              0x40 = Level 0 quality bit                           */\n");
  strcat(wr_strval,"/*              0x80 = Level 1 quality bit                           */\n");
  strcat(wr_strval,"/*    MainBusVoltage = Main bus voltage value (255=no data)          */\n");
  strcat(wr_strval,"/*    CrisCurrent = CRIS I/F & survial heater current (255=no data)  */\n");
  strcat(wr_strval,"/*    CrisInternalTemperature1 =                                     */\n");
  strcat(wr_strval,"/*                         CRIS internal temperature 1 (255=no data) */\n");
  strcat(wr_strval,"/*    CrisInternalTemperature2 =                                     */\n");
  strcat(wr_strval,"/*                         CRIS internal temperature 2 (255=no data) */\n");
  strcat(wr_strval,"/*    CrisInterfaceTemperature =                                     */\n");
  strcat(wr_strval,"/*                         CRIS interface temperature (255=no data)  */\n");
  strcat(wr_strval,"/*    CrisData = CRIS data                                           */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Note: This structure is only written when the instrument is in    */\n");
  strcat(wr_strval,"/*       diagnostic mode and/or command response mode.               */\n");
  return(0);
}
