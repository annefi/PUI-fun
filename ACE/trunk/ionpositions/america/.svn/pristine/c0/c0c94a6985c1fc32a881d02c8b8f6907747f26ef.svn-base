/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: uleis_stat_tlm.h,v 1.5 1998/03/24 19:06:51 asc Exp  */

#include "uleis_stat_tlm.h"
#include "df.h"

int32 vgrp_id_uleis_stat_tlm;
static int32 vdata_id_uleis_stat_tlm;

  /* 720 is the size of uleis_stat_tlm.h + 1 added line */
char Vgrp_descrp_UStatTLMSet[720];

/****----  init create function  ----****/

int32 init_cr_uleis_stat_tlm(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_uleis_stat_tlm();

  void print_uleis_stat_tlm_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_uleis_stat_tlm = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_uleis_stat_tlm, "VG_UStatTLMSet"); 
  Vsetclass(vgrp_id_uleis_stat_tlm, "VG_ULEIS_STAT_TLM");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_UStatTLMSet" )) ==FAIL) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_uleis_stat_tlm(Vgrp_descrp_UStatTLMSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_UStatTLMSet, sizeof(Vgrp_descrp_UStatTLMSet))) ==FAIL) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_uleis_stat_tlm = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_uleis_stat_tlm, "UStatTLMSet");
  VSsetclass(vdata_id_uleis_stat_tlm, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_uleis_stat_tlm, vdata_id_uleis_stat_tlm)) ==FAIL) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_uleis_stat_tlm, "output_sctime", DFNT_UINT32, (1) )) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_stat_tlm, "collect_sctime", DFNT_UINT32, (1) )) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_stat_tlm, "QAC", DFNT_UINT32, (1) )) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_stat_tlm, "stattlmtime_offset", DFNT_UINT16, (1) )) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> VSfdefine: Couldn't define stattlmtime_offset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_stat_tlm, "StatusTLM", DFNT_UINT8, (U_STAT_TLM_SIZE) )) {
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> VSfdefine: Couldn't define StatusTLM");
    retval = -1;
  }

  if (VSsetfields(vdata_id_uleis_stat_tlm,"output_sctime, collect_sctime, QAC, stattlmtime_offset, StatusTLM")){
    print_uleis_stat_tlm_error("init_cr_uleis_stat_tlm -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_uleis_stat_tlm(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_uleis_stat_tlm(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_uleis_stat_tlm(struct UStatTLMSet UStatTLMSet_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_uleis_stat_tlm_error();
void pack_uleis_stat_tlm();

  odata = (uint8 *) malloc(sizeof(struct UStatTLMSet));
  pack_uleis_stat_tlm(odata, &UStatTLMSet_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_uleis_stat_tlm, recnum)==-1) {
		print_uleis_stat_tlm_error("write_uleis_stat_tlm -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_uleis_stat_tlm, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_uleis_stat_tlm_error("write_uleis_stat_tlm -> VSwrite: Couldn't write data.");

  memset(&UStatTLMSet_struc, 0, sizeof(struct UStatTLMSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_uleis_stat_tlm()
{
  VSdetach(vdata_id_uleis_stat_tlm);
  Vdetach(vgrp_id_uleis_stat_tlm);
}

/*----     init access function    ----*/

int32 init_acc_uleis_stat_tlm(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_uleis_stat_tlm_error();


  if ((vdata_ref = VSfind(hdf_fp, "UStatTLMSet")) <= 0 ) {
    print_uleis_stat_tlm_error("init_acc_uleis_stat_tlm -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_uleis_stat_tlm = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_uleis_stat_tlm_error("init_acc_uleis_stat_tlm -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_uleis_stat_tlm, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_uleis_stat_tlm,"output_sctime, collect_sctime, QAC, stattlmtime_offset, StatusTLM")) {
      print_uleis_stat_tlm_error("init_acc_uleis_stat_tlm -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_uleis_stat_tlm(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_uleis_stat_tlm(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_uleis_stat_tlm(struct UStatTLMSet *UStatTLMSet_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_uleis_stat_tlm_error();
void unpack_uleis_stat_tlm();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct UStatTLMSet));
  VSinquire(vdata_id_uleis_stat_tlm, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_uleis_stat_tlm, recnum_rd)==FAIL) {
          print_uleis_stat_tlm_error("read_uleis_stat_tlm -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_uleis_stat_tlm, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_uleis_stat_tlm_error("read_uleis_stat_tlm -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_uleis_stat_tlm(odata, UStatTLMSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_uleis_stat_tlm()
{
  VSdetach(vdata_id_uleis_stat_tlm);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_uleis_stat_tlm(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_uleis_stat_tlm_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_UStatTLMSet" )) ==FAIL)
    print_uleis_stat_tlm_error("rd_Vgrp_uleis_stat_tlm -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_uleis_stat_tlm_error("rd_Vgrp_uleis_stat_tlm -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_uleis_stat_tlm_error("rd_Vgrp_uleis_stat_tlm -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_uleis_stat_tlm_error("rd_Vgrp_uleis_stat_tlm -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_UStatTLMSet, HDstrlen(Vgrp_descrp_UStatTLMSet)) ==FAIL)
    print_uleis_stat_tlm_error("rd_Vgrp_uleis_stat_tlm -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_UStatTLMSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_uleis_stat_tlm_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_uleis_stat_tlm.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_uleis_stat_tlm(uint8 *data, struct UStatTLMSet *UStatTLMSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &UStatTLMSet_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UStatTLMSet_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UStatTLMSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UStatTLMSet_ptr->stattlmtime_offset, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatTLMSet_ptr->StatusTLM[0], ((1)*(U_STAT_TLM_SIZE)) );
   ptr+= ((1)*(U_STAT_TLM_SIZE));
}

/*----   unpack function    ----*/

void unpack_uleis_stat_tlm(uint8 *data, struct UStatTLMSet *UStatTLMSet_ptr)
{
int32 ptr=0;

   memcpy(&UStatTLMSet_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UStatTLMSet_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UStatTLMSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UStatTLMSet_ptr->stattlmtime_offset, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatTLMSet_ptr->StatusTLM[0], data+ptr,  ((1)*(U_STAT_TLM_SIZE)) );
   ptr+= ((1)*(U_STAT_TLM_SIZE));
}
int32 get_vgrp_id_uleis_stat_tlm() {return(vgrp_id_uleis_stat_tlm);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_uleis_stat_tlm(char *wr_strval)
{
  strcpy(wr_strval, "The file 'uleis_stat_tlm.h' is shown below, it was used to create the data in the Vgroup named 'VG_UStatTLMSet'.\n\n");
  strcat(wr_strval,"/* Id: uleis_stat_tlm.h,v 1.5 1998/03/24 19:06:51 asc Exp $*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define U_STAT_TLM_SIZE    125		/* Status TLM length 125 bytes */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct UStatTLMSet\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 output_sctime;		/* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;	/* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint32 QAC;			/* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint16 stattlmtime_offset;	/* offset for output_sctime for Status TLM */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"     /* Status TLM: 125 bytes */\n");
  strcat(wr_strval,"  uint8  StatusTLM[U_STAT_TLM_SIZE];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
