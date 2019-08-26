/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3schk.h,v 1.3 1997/09/05 22:33:24 jeff Exp  */

#include "s3schk.h"
#include "df.h"

int32 vgrp_id_s3schk;
static int32 vdata_id_s3schk;

  /* 3289 is the size of s3schk.h + 1 added line */
char Vgrp_descrp_s3schk[3289];

/****----  init create function  ----****/

int32 init_cr_s3schk(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3schk();

  void print_s3schk_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3schk = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3schk_error("init_cr_s3schk -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3schk, "VG_s3schk"); 
  Vsetclass(vgrp_id_s3schk, "VG_S3SCHK");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_s3schk" )) ==FAIL) {
    print_s3schk_error("init_cr_s3schk -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3schk(Vgrp_descrp_s3schk);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3schk_error("init_cr_s3schk -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_s3schk, sizeof(Vgrp_descrp_s3schk))) ==FAIL) {
    print_s3schk_error("init_cr_s3schk -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3schk = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3schk_error("init_cr_s3schk -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3schk, "s3schk");
  VSsetclass(vdata_id_s3schk, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3schk, vdata_id_s3schk)) ==FAIL) {
    print_s3schk_error("init_cr_s3schk -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3schk, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "CDHId", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define CDHId");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SunPulDat", DFNT_UINT32, (2) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SunPulDat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "S3PwrCvtVol", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define S3PwrCvtVol");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "S3Cur", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define S3Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "S3ConSecCur", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define S3ConSecCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "S3PowSupATmp", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define S3PowSupATmp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "S3PowSupBTmp", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define S3PowSupBTmp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "S3DckTmp", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define S3DckTmp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "S3Log", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define S3Log");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SepDecTmp", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SepDecTmp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SepCur", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SepCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SepIsoButTmp", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SepIsoButTmp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SepLog", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SepLog");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SwcCur", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SwcCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SwcIntTmp", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SwcIntTmp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SwcDckTmp", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SwcDckTmp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SwcLog", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SwcLog");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SwmCur", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SwmCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SwmIntTmp", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SwmIntTmp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3schk, "SwmLog", DFNT_UINT8, (1) )) {
    print_s3schk_error("init_cr_s3schk -> VSfdefine: Couldn't define SwmLog");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3schk,"sctime_readout, CDHId, SunPulDat, S3PwrCvtVol, S3Cur, S3ConSecCur, S3PowSupATmp, S3PowSupBTmp, S3DckTmp, S3Log, SepDecTmp, SepCur, SepIsoButTmp, SepLog, SwcCur, SwcIntTmp, SwcDckTmp, SwcLog, SwmCur, SwmIntTmp, SwmLog")){
    print_s3schk_error("init_cr_s3schk -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3schk(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3schk(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3schk(struct s3schk s3schk_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3schk_error();
void pack_s3schk();

  odata = (uint8 *) malloc(sizeof(struct s3schk));
  pack_s3schk(odata, &s3schk_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3schk, recnum)==-1) {
		print_s3schk_error("write_s3schk -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3schk, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3schk_error("write_s3schk -> VSwrite: Couldn't write data.");

  memset(&s3schk_struc, 0, sizeof(struct s3schk));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3schk()
{
  VSdetach(vdata_id_s3schk);
  Vdetach(vgrp_id_s3schk);
}

/*----     init access function    ----*/

int32 init_acc_s3schk(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3schk_error();


  if ((vdata_ref = VSfind(hdf_fp, "s3schk")) <= 0 ) {
    print_s3schk_error("init_acc_s3schk -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3schk = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3schk_error("init_acc_s3schk -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3schk, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3schk,"sctime_readout, CDHId, SunPulDat, S3PwrCvtVol, S3Cur, S3ConSecCur, S3PowSupATmp, S3PowSupBTmp, S3DckTmp, S3Log, SepDecTmp, SepCur, SepIsoButTmp, SepLog, SwcCur, SwcIntTmp, SwcDckTmp, SwcLog, SwmCur, SwmIntTmp, SwmLog")) {
      print_s3schk_error("init_acc_s3schk -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3schk(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3schk(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3schk(struct s3schk *s3schk_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3schk_error();
void unpack_s3schk();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct s3schk));
  VSinquire(vdata_id_s3schk, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3schk, recnum_rd)==FAIL) {
          print_s3schk_error("read_s3schk -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3schk, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3schk_error("read_s3schk -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3schk(odata, s3schk_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3schk()
{
  VSdetach(vdata_id_s3schk);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3schk(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3schk_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_s3schk" )) ==FAIL)
    print_s3schk_error("rd_Vgrp_s3schk -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3schk_error("rd_Vgrp_s3schk -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3schk_error("rd_Vgrp_s3schk -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3schk_error("rd_Vgrp_s3schk -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_s3schk, HDstrlen(Vgrp_descrp_s3schk)) ==FAIL)
    print_s3schk_error("rd_Vgrp_s3schk -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_s3schk);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3schk_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3schk.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3schk(uint8 *data, struct s3schk *s3schk_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &s3schk_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3schk_ptr->CDHId, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SunPulDat[0], ((4)*(2)) );
   ptr+= ((4)*(2));
   memcpy(data+ptr, &s3schk_ptr->S3PwrCvtVol, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->S3Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->S3ConSecCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->S3PowSupATmp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->S3PowSupBTmp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->S3DckTmp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->S3Log, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SepDecTmp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SepCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SepIsoButTmp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SepLog, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SwcCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SwcIntTmp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SwcDckTmp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SwcLog, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SwmCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SwmIntTmp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &s3schk_ptr->SwmLog, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3schk(uint8 *data, struct s3schk *s3schk_ptr)
{
int32 ptr=0;

   memcpy(&s3schk_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3schk_ptr->CDHId, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SunPulDat[0], data+ptr,  ((4)*(2)) );
   ptr+= ((4)*(2));
   memcpy(&s3schk_ptr->S3PwrCvtVol, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->S3Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->S3ConSecCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->S3PowSupATmp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->S3PowSupBTmp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->S3DckTmp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->S3Log, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SepDecTmp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SepCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SepIsoButTmp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SepLog, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SwcCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SwcIntTmp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SwcDckTmp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SwcLog, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SwmCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SwmIntTmp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&s3schk_ptr->SwmLog, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3schk() {return(vgrp_id_s3schk);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3schk(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3schk.h' is shown below, it was used to create the data in the Vgroup named 'VG_s3schk'.\n\n");
  strcat(wr_strval,"/* Id: s3schk.h,v 1.3 1997/09/05 22:33:24 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct s3schk    /* Spacecraft housekeeping data for S3 instruments */\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    uint32 sctime_readout;   /* Readout time */\n");
  strcat(wr_strval,"    uint8 CDHId;             /* C&DH A = 01, C&DH B = 10, error otherwise */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 SunPulDat[2];    /* Sun sensor data */\n");
  strcat(wr_strval,"		/* bits 31-24 : unused */\n");
  strcat(wr_strval,"		/* bits 23-20 : Mnr frame */\n");
  strcat(wr_strval,"		/* bits 19-10 : sub secont count (684.75 cnts=1 sec)*/\n");
  strcat(wr_strval,"		/* bits  9- 8 : ID bits, 00=err,01=top,10=side,11=neither */\n");
  strcat(wr_strval,"		/* bits  7- 0 : Y angle measurment (Grey code) */\n");
  strcat(wr_strval,"		/* */\n");
  strcat(wr_strval,"		/*   From C&DH Specification (mf0:index=0, mf8:index=1) */\n");
  strcat(wr_strval,"		/* For the time tag in Science minor frame 0: for a minor */\n");
  strcat(wr_strval,"		/* frame ID of 0, the sun pulse would have occured in the */\n");
  strcat(wr_strval,"		/* current major frame.  For a minor frame ID of 1 to 15, */\n");
  strcat(wr_strval,"		/* the sun pulse would have occured in the previous major */\n");
  strcat(wr_strval,"		/* frame */\n");
  strcat(wr_strval,"		/* For the time tag in Science minor frame 8: for a minor */\n");
  strcat(wr_strval,"		/* frame ID of 0-8, the sun pulse would have occured in the */\n");
  strcat(wr_strval,"		/* current major frame.  For a minor frame ID of 9 to 15, */\n");
  strcat(wr_strval,"		/* the sun pulse would have occured in the previous major */\n");
  strcat(wr_strval,"		/* frame */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* S3DPU SCHK values */\n");
  strcat(wr_strval,"    uint8 S3PwrCvtVol;       /* S3DPU power converter voltage */\n");
  strcat(wr_strval,"    uint8 S3Cur;             /* S3DPU current */\n");
  strcat(wr_strval,"    uint8 S3ConSecCur;       /* S3DPU converter secondary curent */\n");
  strcat(wr_strval,"    uint8 S3PowSupATmp;      /* S3DPU Power Supply A temp */\n");
  strcat(wr_strval,"    uint8 S3PowSupBTmp;      /* S3DPU Power Supply B temp */\n");
  strcat(wr_strval,"    uint8 S3DckTmp;          /* S3DPU Deck Temp */\n");
  strcat(wr_strval,"    uint8 S3Log;             /* S3DPU Logic and telltale bits */\n");
  strcat(wr_strval,"				/* bit 7: Power conv sel telltale */\n");
  strcat(wr_strval,"				/* bit 6: Interface A/B select */\n");
  strcat(wr_strval,"				/* bit 5: Converter A power */\n");
  strcat(wr_strval,"				/* bit 4: Converter B power */\n");
  strcat(wr_strval,"				/* bits 3-0: not used */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* Sepica SCHK values */\n");
  strcat(wr_strval,"    uint8 SepDecTmp;        /* Deck temperature near Sepica */\n");
  strcat(wr_strval,"    uint8 SepCur;           /* Sepica current */\n");
  strcat(wr_strval,"    uint8 SepIsoButTmp;     /* Sepica Iso-butane tank temp */\n");
  strcat(wr_strval,"    uint8 SepLog;           /* Sepica logic and telltales */\n");
  strcat(wr_strval,"				/* bit 7: Sepica Gas Valve */\n");
  strcat(wr_strval,"				/* bit 6: Sepica Main Power */\n");
  strcat(wr_strval,"				/* bit 5: Sepica Internal Heater (1&2)*/\n");
  strcat(wr_strval,"				/* bit 4: Sepica Interface Heater */\n");
  strcat(wr_strval,"				/* bits 3-0: Unused */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* Swics SCHK values */\n");
  strcat(wr_strval,"    uint8 SwcCur;              /* SWICS current */\n");
  strcat(wr_strval,"    uint8 SwcIntTmp;           /* SWICS internal temp */\n");
  strcat(wr_strval,"    uint8 SwcDckTmp;           /* SWICS Deck temp */\n");
  strcat(wr_strval,"    uint8 SwcLog;              /* SWICS logic and telltales */\n");
  strcat(wr_strval,"				/* bit 7: SWICS Main Power */\n");
  strcat(wr_strval,"				/* bit 6: SWICS Internal heaters */\n");
  strcat(wr_strval,"				/* bit 5: SWICS Interface heaters */\n");
  strcat(wr_strval,"				/* bit 4: SWICS Pyro Main/Backup */\n");
  strcat(wr_strval,"				/* bits 3-0: Unused */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* Swims SCHK values */\n");
  strcat(wr_strval,"    uint8 SwmCur;              /* SWIMS current */\n");
  strcat(wr_strval,"    uint8 SwmIntTmp;           /* SWIMS Internal Temp */\n");
  strcat(wr_strval,"    uint8 SwmLog;              /* SWICS logic and telltales */\n");
  strcat(wr_strval,"				/* bit 7: SWIMS Cover Telltale */\n");
  strcat(wr_strval,"				/* bit 6: SWIMS Main Power */\n");
  strcat(wr_strval,"				/* bit 5: SWIMS Internal Heater */\n");
  strcat(wr_strval,"				/* bit 4: SWIMS Interface Heater */\n");
  strcat(wr_strval,"				/* bit 3: SWIMS Pyro Main/Backup */\n");
  strcat(wr_strval,"				/* bits 2-0: Unused */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
