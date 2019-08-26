/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisDiagnosticEvent.h,v 1.2 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisDiagnosticEvent.h"
#include "df.h"

int32 vgrp_id_L1SisDiagnosticEvent;
static int32 vdata_id_L1SisDiagnosticEvent;

  /* 1306 is the size of L1SisDiagnosticEvent.h + 1 added line */
char Vgrp_descrp_L1SisDiagnosticEvent[1306];

/****----  init create function  ----****/

int32 init_cr_L1SisDiagnosticEvent(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1SisDiagnosticEvent();

  void print_L1SisDiagnosticEvent_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisDiagnosticEvent = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisDiagnosticEvent, "VG_L1SisDiagnosticEvent"); 
  Vsetclass(vgrp_id_L1SisDiagnosticEvent, "VG_L1SISDIAGNOSTICEVENT");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisDiagnosticEvent" )) ==FAIL) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisDiagnosticEvent(Vgrp_descrp_L1SisDiagnosticEvent);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisDiagnosticEvent, sizeof(Vgrp_descrp_L1SisDiagnosticEvent))) ==FAIL) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisDiagnosticEvent = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisDiagnosticEvent, "L1SisDiagnosticEvent");
  VSsetclass(vdata_id_L1SisDiagnosticEvent, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisDiagnosticEvent, vdata_id_L1SisDiagnosticEvent)) ==FAIL) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisDiagnosticEvent, "ClockMinorFrame0", DFNT_UINT32, (1) )) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSfdefine: Couldn't define ClockMinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDiagnosticEvent, "ClockMinorFrame1", DFNT_UINT32, (1) )) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSfdefine: Couldn't define ClockMinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDiagnosticEvent, "Second1996MinorFrame0", DFNT_UINT32, (1) )) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSfdefine: Couldn't define Second1996MinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDiagnosticEvent, "MicrosecondMinorFrame0", DFNT_UINT32, (1) )) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSfdefine: Couldn't define MicrosecondMinorFrame0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDiagnosticEvent, "Second1996MinorFrame1", DFNT_UINT32, (1) )) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSfdefine: Couldn't define Second1996MinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDiagnosticEvent, "MicrosecondMinorFrame1", DFNT_UINT32, (1) )) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSfdefine: Couldn't define MicrosecondMinorFrame1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDiagnosticEvent, "RawStack", DFNT_UINT16, (NUM_SIS_RAW_STACK_EVT_BYTES/2) )) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSfdefine: Couldn't define RawStack");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDiagnosticEvent, "NormalEvent", DFNT_UINT8, (MAX_NUM_SIS_EVENT_BYTES) )) {
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSfdefine: Couldn't define NormalEvent");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisDiagnosticEvent,"ClockMinorFrame0, ClockMinorFrame1, Second1996MinorFrame0, MicrosecondMinorFrame0, Second1996MinorFrame1, MicrosecondMinorFrame1, RawStack, NormalEvent")){
    print_L1SisDiagnosticEvent_error("init_cr_L1SisDiagnosticEvent -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisDiagnosticEvent(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisDiagnosticEvent(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisDiagnosticEvent(struct L1SisDiagnosticEvent L1SisDiagnosticEvent_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1SisDiagnosticEvent_error();
void pack_L1SisDiagnosticEvent();

  odata = (uint8 *) malloc(sizeof(struct L1SisDiagnosticEvent));
  pack_L1SisDiagnosticEvent(odata, &L1SisDiagnosticEvent_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1SisDiagnosticEvent, recnum)==-1) {
		print_L1SisDiagnosticEvent_error("write_L1SisDiagnosticEvent -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisDiagnosticEvent, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisDiagnosticEvent_error("write_L1SisDiagnosticEvent -> VSwrite: Couldn't write data.");

  memset(&L1SisDiagnosticEvent_struc, 0, sizeof(struct L1SisDiagnosticEvent));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisDiagnosticEvent()
{
  VSdetach(vdata_id_L1SisDiagnosticEvent);
  Vdetach(vgrp_id_L1SisDiagnosticEvent);
}

/*----     init access function    ----*/

int32 init_acc_L1SisDiagnosticEvent(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisDiagnosticEvent_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1SisDiagnosticEvent")) <= 0 ) {
    print_L1SisDiagnosticEvent_error("init_acc_L1SisDiagnosticEvent -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisDiagnosticEvent = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisDiagnosticEvent_error("init_acc_L1SisDiagnosticEvent -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisDiagnosticEvent, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisDiagnosticEvent,"ClockMinorFrame0, ClockMinorFrame1, Second1996MinorFrame0, MicrosecondMinorFrame0, Second1996MinorFrame1, MicrosecondMinorFrame1, RawStack, NormalEvent")) {
      print_L1SisDiagnosticEvent_error("init_acc_L1SisDiagnosticEvent -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisDiagnosticEvent(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisDiagnosticEvent(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisDiagnosticEvent(struct L1SisDiagnosticEvent *L1SisDiagnosticEvent_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisDiagnosticEvent_error();
void unpack_L1SisDiagnosticEvent();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1SisDiagnosticEvent));
  VSinquire(vdata_id_L1SisDiagnosticEvent, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisDiagnosticEvent, recnum_rd)==FAIL) {
          print_L1SisDiagnosticEvent_error("read_L1SisDiagnosticEvent -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1SisDiagnosticEvent, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisDiagnosticEvent_error("read_L1SisDiagnosticEvent -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisDiagnosticEvent(odata, L1SisDiagnosticEvent_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisDiagnosticEvent()
{
  VSdetach(vdata_id_L1SisDiagnosticEvent);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisDiagnosticEvent(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisDiagnosticEvent_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisDiagnosticEvent" )) ==FAIL)
    print_L1SisDiagnosticEvent_error("rd_Vgrp_L1SisDiagnosticEvent -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisDiagnosticEvent_error("rd_Vgrp_L1SisDiagnosticEvent -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisDiagnosticEvent_error("rd_Vgrp_L1SisDiagnosticEvent -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisDiagnosticEvent_error("rd_Vgrp_L1SisDiagnosticEvent -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisDiagnosticEvent, HDstrlen(Vgrp_descrp_L1SisDiagnosticEvent)) ==FAIL)
    print_L1SisDiagnosticEvent_error("rd_Vgrp_L1SisDiagnosticEvent -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisDiagnosticEvent);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisDiagnosticEvent_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisDiagnosticEvent.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisDiagnosticEvent(uint8 *data, struct L1SisDiagnosticEvent *L1SisDiagnosticEvent_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisDiagnosticEvent_ptr->ClockMinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDiagnosticEvent_ptr->ClockMinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDiagnosticEvent_ptr->Second1996MinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDiagnosticEvent_ptr->MicrosecondMinorFrame0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDiagnosticEvent_ptr->Second1996MinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDiagnosticEvent_ptr->MicrosecondMinorFrame1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDiagnosticEvent_ptr->RawStack[0], ((2)*(NUM_SIS_RAW_STACK_EVT_BYTES/2)) );
   ptr+= ((2)*(NUM_SIS_RAW_STACK_EVT_BYTES/2));
   memcpy(data+ptr, &L1SisDiagnosticEvent_ptr->NormalEvent[0], ((1)*(MAX_NUM_SIS_EVENT_BYTES)) );
   ptr+= ((1)*(MAX_NUM_SIS_EVENT_BYTES));
}

/*----   unpack function    ----*/

void unpack_L1SisDiagnosticEvent(uint8 *data, struct L1SisDiagnosticEvent *L1SisDiagnosticEvent_ptr)
{
int32 ptr=0;

   memcpy(&L1SisDiagnosticEvent_ptr->ClockMinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDiagnosticEvent_ptr->ClockMinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDiagnosticEvent_ptr->Second1996MinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDiagnosticEvent_ptr->MicrosecondMinorFrame0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDiagnosticEvent_ptr->Second1996MinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDiagnosticEvent_ptr->MicrosecondMinorFrame1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDiagnosticEvent_ptr->RawStack[0], data+ptr,  ((2)*(NUM_SIS_RAW_STACK_EVT_BYTES/2)) );
   ptr+= ((2)*(NUM_SIS_RAW_STACK_EVT_BYTES/2));
   memcpy(&L1SisDiagnosticEvent_ptr->NormalEvent[0], data+ptr,  ((1)*(MAX_NUM_SIS_EVENT_BYTES)) );
   ptr+= ((1)*(MAX_NUM_SIS_EVENT_BYTES));
}
int32 get_vgrp_id_L1SisDiagnosticEvent() {return(vgrp_id_L1SisDiagnosticEvent);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisDiagnosticEvent(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisDiagnosticEvent.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisDiagnosticEvent'.\n\n");
  strcat(wr_strval,"/* Id: L1SisDiagnosticEvent.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDiagnosticEvent.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisDiagnosticEvent\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame0;\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame1;\n");
  strcat(wr_strval,"   uint32 Second1996MinorFrame0;\n");
  strcat(wr_strval,"   uint32 MicrosecondMinorFrame0;\n");
  strcat(wr_strval,"   uint32 Second1996MinorFrame1;\n");
  strcat(wr_strval,"   uint32 MicrosecondMinorFrame1;\n");
  strcat(wr_strval,"   uint16 RawStack[NUM_SIS_RAW_STACK_EVT_BYTES/2];\n");
  strcat(wr_strval,"   uint8  NormalEvent[MAX_NUM_SIS_EVENT_BYTES];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockMinorFrame0 = S/C clock of the minor frame containing     */\n");
  strcat(wr_strval,"/*                       the start of the diagnostic event           */\n");
  strcat(wr_strval,"/*    ClockMinorFrame1 = S/C clock of the minor frame containing     */\n");
  strcat(wr_strval,"/*                       the end of the diagnostic event             */\n");
  strcat(wr_strval,"/*    RawStack = Raw stack event portion of the diagnostic event     */\n");
  strcat(wr_strval,"/*    NormalEvent = Normal event portion of the diagnostic event     */\n");
  return(0);
}
