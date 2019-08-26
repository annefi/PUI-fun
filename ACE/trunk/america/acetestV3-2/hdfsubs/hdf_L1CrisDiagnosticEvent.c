/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1CrisDiagnosticEvent.h,v 1.2 1997/09/11 16:50:59 jeff Exp  */

#include "L1CrisDiagnosticEvent.h"
#include "df.h"

int32 vgrp_id_L1CrisDiagnosticEvent;
static int32 vdata_id_L1CrisDiagnosticEvent;

  /* 1464 is the size of L1CrisDiagnosticEvent.h + 1 added line */
char Vgrp_descrp_L1CrisDiagnosticEvent[1464];

/****----  init create function  ----****/

int32 init_cr_L1CrisDiagnosticEvent(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1CrisDiagnosticEvent();

  void print_L1CrisDiagnosticEvent_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1CrisDiagnosticEvent = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1CrisDiagnosticEvent, "VG_L1CrisDiagnosticEvent"); 
  Vsetclass(vgrp_id_L1CrisDiagnosticEvent, "VG_L1CRISDIAGNOSTICEVENT");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1CrisDiagnosticEvent" )) ==FAIL) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1CrisDiagnosticEvent(Vgrp_descrp_L1CrisDiagnosticEvent);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1CrisDiagnosticEvent, sizeof(Vgrp_descrp_L1CrisDiagnosticEvent))) ==FAIL) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1CrisDiagnosticEvent = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1CrisDiagnosticEvent, "L1CrisDiagnosticEvent");
  VSsetclass(vdata_id_L1CrisDiagnosticEvent, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1CrisDiagnosticEvent, vdata_id_L1CrisDiagnosticEvent)) ==FAIL) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "ClockMinorFrame0", DFNT_UINT32, (1) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define ClockMinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "ClockMinorFrame1", DFNT_UINT32, (1) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define ClockMinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "Second1996MinorFrame0", DFNT_UINT32, (1) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define Second1996MinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "MicrosecondMinorFrame0", DFNT_UINT32, (1) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define MicrosecondMinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "Second1996MinorFrame1", DFNT_UINT32, (1) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define Second1996MinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "MicrosecondMinorFrame1", DFNT_UINT32, (1) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define MicrosecondMinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "RawStack", DFNT_UINT16, (NUM_CRIS_RAW_STACK_EVT_BYTES/2) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define RawStack");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "SoftEvent", DFNT_UINT16, (NUM_CRIS_RAW_SOFT_EVT_BYTES/2) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define SoftEvent");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "NormalEvent", DFNT_UINT8, (MAX_NUM_CRIS_EVENT_BYTES) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define NormalEvent");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisDiagnosticEvent, "ContinuationFlag", DFNT_UINT8, (1) )) {
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSfdefine: Couldn't define ContinuationFlag");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1CrisDiagnosticEvent,"ClockMinorFrame0, ClockMinorFrame1, Second1996MinorFrame0, MicrosecondMinorFrame0, Second1996MinorFrame1, MicrosecondMinorFrame1, RawStack, SoftEvent, NormalEvent, ContinuationFlag")){
    print_L1CrisDiagnosticEvent_error("init_cr_L1CrisDiagnosticEvent -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1CrisDiagnosticEvent(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1CrisDiagnosticEvent(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1CrisDiagnosticEvent(struct L1CrisDiagnosticEvent L1CrisDiagnosticEvent_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1CrisDiagnosticEvent_error();
void pack_L1CrisDiagnosticEvent();

  odata = (uint8 *) malloc(sizeof(struct L1CrisDiagnosticEvent));
  pack_L1CrisDiagnosticEvent(odata, &L1CrisDiagnosticEvent_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1CrisDiagnosticEvent, recnum)==-1) {
		print_L1CrisDiagnosticEvent_error("write_L1CrisDiagnosticEvent -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1CrisDiagnosticEvent, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1CrisDiagnosticEvent_error("write_L1CrisDiagnosticEvent -> VSwrite: Couldn't write data.");

  memset(&L1CrisDiagnosticEvent_struc, 0, sizeof(struct L1CrisDiagnosticEvent));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1CrisDiagnosticEvent()
{
  VSdetach(vdata_id_L1CrisDiagnosticEvent);
  Vdetach(vgrp_id_L1CrisDiagnosticEvent);
}

/*----     init access function    ----*/

int32 init_acc_L1CrisDiagnosticEvent(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1CrisDiagnosticEvent_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1CrisDiagnosticEvent")) <= 0 ) {
    print_L1CrisDiagnosticEvent_error("init_acc_L1CrisDiagnosticEvent -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1CrisDiagnosticEvent = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1CrisDiagnosticEvent_error("init_acc_L1CrisDiagnosticEvent -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1CrisDiagnosticEvent, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1CrisDiagnosticEvent,"ClockMinorFrame0, ClockMinorFrame1, Second1996MinorFrame0, MicrosecondMinorFrame0, Second1996MinorFrame1, MicrosecondMinorFrame1, RawStack, SoftEvent, NormalEvent, ContinuationFlag")) {
      print_L1CrisDiagnosticEvent_error("init_acc_L1CrisDiagnosticEvent -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1CrisDiagnosticEvent(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1CrisDiagnosticEvent(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1CrisDiagnosticEvent(struct L1CrisDiagnosticEvent *L1CrisDiagnosticEvent_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1CrisDiagnosticEvent_error();
void unpack_L1CrisDiagnosticEvent();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1CrisDiagnosticEvent));
  VSinquire(vdata_id_L1CrisDiagnosticEvent, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1CrisDiagnosticEvent, recnum_rd)==FAIL) {
          print_L1CrisDiagnosticEvent_error("read_L1CrisDiagnosticEvent -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1CrisDiagnosticEvent, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1CrisDiagnosticEvent_error("read_L1CrisDiagnosticEvent -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1CrisDiagnosticEvent(odata, L1CrisDiagnosticEvent_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1CrisDiagnosticEvent()
{
  VSdetach(vdata_id_L1CrisDiagnosticEvent);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1CrisDiagnosticEvent(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1CrisDiagnosticEvent_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1CrisDiagnosticEvent" )) ==FAIL)
    print_L1CrisDiagnosticEvent_error("rd_Vgrp_L1CrisDiagnosticEvent -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1CrisDiagnosticEvent_error("rd_Vgrp_L1CrisDiagnosticEvent -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1CrisDiagnosticEvent_error("rd_Vgrp_L1CrisDiagnosticEvent -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1CrisDiagnosticEvent_error("rd_Vgrp_L1CrisDiagnosticEvent -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1CrisDiagnosticEvent, HDstrlen(Vgrp_descrp_L1CrisDiagnosticEvent)) ==FAIL)
    print_L1CrisDiagnosticEvent_error("rd_Vgrp_L1CrisDiagnosticEvent -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1CrisDiagnosticEvent);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1CrisDiagnosticEvent_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1CrisDiagnosticEvent.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1CrisDiagnosticEvent(uint8 *data, struct L1CrisDiagnosticEvent *L1CrisDiagnosticEvent_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->ClockMinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->ClockMinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->Second1996MinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->MicrosecondMinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->Second1996MinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->MicrosecondMinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->RawStack[0], ((2)*(NUM_CRIS_RAW_STACK_EVT_BYTES/2)) );
   ptr+= ((2)*(NUM_CRIS_RAW_STACK_EVT_BYTES/2));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->SoftEvent[0], ((2)*(NUM_CRIS_RAW_SOFT_EVT_BYTES/2)) );
   ptr+= ((2)*(NUM_CRIS_RAW_SOFT_EVT_BYTES/2));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->NormalEvent[0], ((1)*(MAX_NUM_CRIS_EVENT_BYTES)) );
   ptr+= ((1)*(MAX_NUM_CRIS_EVENT_BYTES));
   memcpy(data+ptr, &L1CrisDiagnosticEvent_ptr->ContinuationFlag, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_L1CrisDiagnosticEvent(uint8 *data, struct L1CrisDiagnosticEvent *L1CrisDiagnosticEvent_ptr)
{
int32 ptr=0;

   memcpy(&L1CrisDiagnosticEvent_ptr->ClockMinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisDiagnosticEvent_ptr->ClockMinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisDiagnosticEvent_ptr->Second1996MinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisDiagnosticEvent_ptr->MicrosecondMinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisDiagnosticEvent_ptr->Second1996MinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisDiagnosticEvent_ptr->MicrosecondMinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisDiagnosticEvent_ptr->RawStack[0], data+ptr,  ((2)*(NUM_CRIS_RAW_STACK_EVT_BYTES/2)) );
   ptr+= ((2)*(NUM_CRIS_RAW_STACK_EVT_BYTES/2));
   memcpy(&L1CrisDiagnosticEvent_ptr->SoftEvent[0], data+ptr,  ((2)*(NUM_CRIS_RAW_SOFT_EVT_BYTES/2)) );
   ptr+= ((2)*(NUM_CRIS_RAW_SOFT_EVT_BYTES/2));
   memcpy(&L1CrisDiagnosticEvent_ptr->NormalEvent[0], data+ptr,  ((1)*(MAX_NUM_CRIS_EVENT_BYTES)) );
   ptr+= ((1)*(MAX_NUM_CRIS_EVENT_BYTES));
   memcpy(&L1CrisDiagnosticEvent_ptr->ContinuationFlag, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_L1CrisDiagnosticEvent() {return(vgrp_id_L1CrisDiagnosticEvent);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1CrisDiagnosticEvent(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1CrisDiagnosticEvent.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1CrisDiagnosticEvent'.\n\n");
  strcat(wr_strval,"/* Id: L1CrisDiagnosticEvent.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisDiagnosticEvent.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"CrisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1CrisDiagnosticEvent\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame0;\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame1;\n");
  strcat(wr_strval,"   uint32 Second1996MinorFrame0;\n");
  strcat(wr_strval,"   uint32 MicrosecondMinorFrame0;\n");
  strcat(wr_strval,"   uint32 Second1996MinorFrame1;\n");
  strcat(wr_strval,"   uint32 MicrosecondMinorFrame1;\n");
  strcat(wr_strval,"   uint16 RawStack[NUM_CRIS_RAW_STACK_EVT_BYTES/2];\n");
  strcat(wr_strval,"   uint16 SoftEvent[NUM_CRIS_RAW_SOFT_EVT_BYTES/2];\n");
  strcat(wr_strval,"   uint8  NormalEvent[MAX_NUM_CRIS_EVENT_BYTES];\n");
  strcat(wr_strval,"   uint8  ContinuationFlag;\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockMinorFrame = S/C clock of the minor frame containing the  */\n");
  strcat(wr_strval,"/*                      start of the diagnostic event                */\n");
  strcat(wr_strval,"/*    RawStack = Raw stack event portion of the diagnostic event     */\n");
  strcat(wr_strval,"/*    SoftEvent = Raw SOFT event portion of the diagnostic event     */\n");
  strcat(wr_strval,"/*    NormalEvent = Normal event portion of the diagnostic event     */\n");
  strcat(wr_strval,"/*    ContinuationFlag = Flag indicating the SOFT portion of the     */\n");
  strcat(wr_strval,"/*                       event is continued in the next cycle        */\n");
  return(0);
}
