/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisEventCycle.h,v 1.3 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisEventCycle.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_L1SisEventCycle;
static int32 vdata_id_L1SisEventCycle;

static int32 sds_id_L1SisEventCycle1;

  /* 1794 is the size of L1SisEventCycle.h + 1 added line */
char Vgrp_descrp_L1SisEventCycle[1794];

/****----  init create function  ----****/

int32 init_cr_L1SisEventCycle(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[2];
  int32 rank;

  int32 wr_Vgrp_desc_L1SisEventCycle();

  void print_L1SisEventCycle_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisEventCycle = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisEventCycle, "VG_L1SisEventCycle"); 
  Vsetclass(vgrp_id_L1SisEventCycle, "VG_L1SISEVENTCYCLE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisEventCycle" )) ==FAIL) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisEventCycle(Vgrp_descrp_L1SisEventCycle);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisEventCycle, sizeof(Vgrp_descrp_L1SisEventCycle))) ==FAIL) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisEventCycle = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisEventCycle, "L1SisEventCycle");
  VSsetclass(vdata_id_L1SisEventCycle, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisEventCycle, vdata_id_L1SisEventCycle)) ==FAIL) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisEventCycle, "ClockCycle", DFNT_UINT32, (1) )) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> VSfdefine: Couldn't define ClockCycle");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisEventCycle, "Second1996", DFNT_UINT32, (1) )) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisEventCycle, "microsecond", DFNT_UINT32, (1) )) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisEventCycle, "NumberNormalEventBytes", DFNT_UINT16, (MAX_SIS_EVT_AGE) )) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> VSfdefine: Couldn't define NumberNormalEventBytes");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisEventCycle, "NumberEvents", DFNT_UINT16, (1) )) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> VSfdefine: Couldn't define NumberEvents");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisEventCycle, "ContinuationFlag", DFNT_UINT8, (1) )) {
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> VSfdefine: Couldn't define ContinuationFlag");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisEventCycle,"ClockCycle, Second1996, microsecond, NumberNormalEventBytes, NumberEvents, ContinuationFlag")){
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 2;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SIZE_SIS_EVENT_BUFFER;
  if((sds_id_L1SisEventCycle1 = SDcreate(sd_id, "L1SisEventCycle_EventBuffer", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> SDcreate: Couldn't create L1SisEventCycle_EventBuffer");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_L1SisEventCycle1)) == FAIL)
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> SDidtoref: Couldn't get ref for L1SisEventCycle_EventBuffer");

  if((Vaddtagref(vgrp_id_L1SisEventCycle, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_L1SisEventCycle_error("init_cr_L1SisEventCycle -> Vaddtagref: Couldn't add SDS L1SisEventCycle_EventBuffer to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisEventCycle(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisEventCycle(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisEventCycle(struct L1SisEventCycle L1SisEventCycle_struc, int32 recnum)
{
  int32 start[2], edges[2];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_L1SisEventCycle_error();
void pack_L1SisEventCycle();

  odata = (uint8 *) malloc(sizeof(struct L1SisEventCycle));
  pack_L1SisEventCycle(odata, &L1SisEventCycle_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_L1SisEventCycle, recnum)==-1) {
		print_L1SisEventCycle_error("write_L1SisEventCycle -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisEventCycle, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisEventCycle_error("write_L1SisEventCycle -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  edges[0] = 1;

  edges[1] = SIZE_SIS_EVENT_BUFFER;
  if (SDwritedata(sds_id_L1SisEventCycle1,start,NULL,edges, (VOIDP)(L1SisEventCycle_struc.EventBuffer)) ==FAIL)
    print_L1SisEventCycle_error("write_L1SisEventCycle -> SDwritedata: Problem writing EventBuffer data.");

  memset(&L1SisEventCycle_struc, 0, sizeof(struct L1SisEventCycle));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisEventCycle()
{
  VSdetach(vdata_id_L1SisEventCycle);
  Vdetach(vgrp_id_L1SisEventCycle);
  SDendaccess(sds_id_L1SisEventCycle1);
}

/*----     init access function    ----*/

int32 init_acc_L1SisEventCycle(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisEventCycle_error();

  if((sds_index1=SDnametoindex(sd_id, "L1SisEventCycle_EventBuffer" )) ==FAIL) {
      print_L1SisEventCycle_error("init_acc_L1SisEventCycle -> SDnametoindex: Couldn't find L1SisEventCycle_EventBuffer");
      return(-1);
  }
  if((sds_id_L1SisEventCycle1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_L1SisEventCycle_error("init_acc_L1SisEventCycle -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "L1SisEventCycle")) <= 0 ) {
    print_L1SisEventCycle_error("init_acc_L1SisEventCycle -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisEventCycle = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisEventCycle_error("init_acc_L1SisEventCycle -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisEventCycle, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisEventCycle,"ClockCycle, Second1996, microsecond, NumberNormalEventBytes, NumberEvents, ContinuationFlag")) {
      print_L1SisEventCycle_error("init_acc_L1SisEventCycle -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisEventCycle(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisEventCycle(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisEventCycle(struct L1SisEventCycle *L1SisEventCycle_struc, int32 recnum_rd)
{
int32 start[2], edges[2];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisEventCycle_error();
void unpack_L1SisEventCycle();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct L1SisEventCycle));
  VSinquire(vdata_id_L1SisEventCycle, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisEventCycle, recnum_rd)==FAIL) {
          print_L1SisEventCycle_error("read_L1SisEventCycle -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SIZE_SIS_EVENT_BUFFER;

  if(SDreaddata(sds_id_L1SisEventCycle1,start,NULL,edges, (VOIDP)(L1SisEventCycle_struc->EventBuffer )) ==FAIL) {
    print_L1SisEventCycle_error("read_L1SisEventCycle -> SDreaddata: Couldn't read EventBuffer");
    retval = -1;
  }
  if(VSread(vdata_id_L1SisEventCycle, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisEventCycle_error("read_L1SisEventCycle -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisEventCycle(odata, L1SisEventCycle_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisEventCycle()
{
  VSdetach(vdata_id_L1SisEventCycle);
  SDendaccess(sds_id_L1SisEventCycle1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisEventCycle(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisEventCycle_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisEventCycle" )) ==FAIL)
    print_L1SisEventCycle_error("rd_Vgrp_L1SisEventCycle -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisEventCycle_error("rd_Vgrp_L1SisEventCycle -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisEventCycle_error("rd_Vgrp_L1SisEventCycle -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisEventCycle_error("rd_Vgrp_L1SisEventCycle -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisEventCycle, HDstrlen(Vgrp_descrp_L1SisEventCycle)) ==FAIL)
    print_L1SisEventCycle_error("rd_Vgrp_L1SisEventCycle -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisEventCycle);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisEventCycle_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisEventCycle.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisEventCycle(uint8 *data, struct L1SisEventCycle *L1SisEventCycle_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisEventCycle_ptr->ClockCycle, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisEventCycle_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisEventCycle_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisEventCycle_ptr->NumberNormalEventBytes[0], ((2)*(MAX_SIS_EVT_AGE)) );
   ptr+= ((2)*(MAX_SIS_EVT_AGE));
   memcpy(data+ptr, &L1SisEventCycle_ptr->NumberEvents, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1SisEventCycle_ptr->ContinuationFlag, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_L1SisEventCycle(uint8 *data, struct L1SisEventCycle *L1SisEventCycle_ptr)
{
int32 ptr=0;

   memcpy(&L1SisEventCycle_ptr->ClockCycle, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisEventCycle_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisEventCycle_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisEventCycle_ptr->NumberNormalEventBytes[0], data+ptr,  ((2)*(MAX_SIS_EVT_AGE)) );
   ptr+= ((2)*(MAX_SIS_EVT_AGE));
   memcpy(&L1SisEventCycle_ptr->NumberEvents, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1SisEventCycle_ptr->ContinuationFlag, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_L1SisEventCycle() {return(vgrp_id_L1SisEventCycle);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisEventCycle(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisEventCycle.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisEventCycle'.\n\n");
  strcat(wr_strval,"/* Id: L1SisEventCycle.h,v 1.3 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisEventCycle.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisEventCycle\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockCycle;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint16 NumberNormalEventBytes[MAX_SIS_EVT_AGE];\n");
  strcat(wr_strval,"   uint16 NumberEvents;\n");
  strcat(wr_strval,"   uint8  EventBuffer[SIZE_SIS_EVENT_BUFFER];\n");
  strcat(wr_strval,"   uint8  ContinuationFlag;\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockCycle = S/C clock of the first minor frame of the cycle   */\n");
  strcat(wr_strval,"/*                 in which SIS processed the events                 */\n");
  strcat(wr_strval,"/*    NumberNormalEventBytes = Number of bytes in each of the cycles */\n");
  strcat(wr_strval,"/*                             that is used for normal event         */\n");
  strcat(wr_strval,"/*                             transmision                           */\n");
  strcat(wr_strval,"/*    NumberEvents = Number of events stored in the event buffer     */\n");
  strcat(wr_strval,"/*    EventBuffer = Event buffer                                     */\n");
  strcat(wr_strval,"/*    ContinuationFlag = Flag indicating events from this cycle are  */\n");
  strcat(wr_strval,"/*                       continued in the next structure             */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Note: Each event in the event buffer is preceded by two bytes.    */\n");
  strcat(wr_strval,"/*       The first is the relative age of the event.  The second is  */\n");
  strcat(wr_strval,"/*       minor frame in which the first byte of the event was        */\n");
  strcat(wr_strval,"/*       transmitted.                                                */\n");
  return(0);
}
