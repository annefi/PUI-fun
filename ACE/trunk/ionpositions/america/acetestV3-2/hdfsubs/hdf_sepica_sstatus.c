/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_sstatus.h,v 1.3 1998/12/07 18:12:39 ad Exp  */

#include "s3_sstatus.h"
#include "df.h"

int32 vgrp_id_s3_sstatus;
static int32 vdata_id_s3_sstatus;

  /* 702 is the size of s3_sstatus.h + 1 added line */
char Vgrp_descrp_sstatus[702];

/****----  init create function  ----****/

int32 init_cr_s3_sstatus(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_sstatus();

  void print_s3_sstatus_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_sstatus = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_sstatus, "VG_sstatus"); 
  Vsetclass(vgrp_id_s3_sstatus, "VG_S3_SSTATUS");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sstatus" )) ==FAIL) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_sstatus(Vgrp_descrp_sstatus);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sstatus, sizeof(Vgrp_descrp_sstatus))) ==FAIL) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_sstatus = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_sstatus, "sstatus");
  VSsetclass(vdata_id_s3_sstatus, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_sstatus, vdata_id_s3_sstatus)) ==FAIL) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_sstatus, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sstatus, "QAC", DFNT_UINT32, (1) )) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sstatus, "QACarr", DFNT_UINT8, (720) )) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> VSfdefine: Couldn't define QACarr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sstatus, "STACMD", DFNT_UINT16, (60) )) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> VSfdefine: Couldn't define STACMD");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sstatus, "STARET", DFNT_UINT32, (60) )) {
    print_s3_sstatus_error("init_cr_s3_sstatus -> VSfdefine: Couldn't define STARET");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_sstatus,"sctime_readout, QAC, QACarr, STACMD, STARET")){
    print_s3_sstatus_error("init_cr_s3_sstatus -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_sstatus(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_sstatus(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_sstatus(struct sstatus sstatus_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_sstatus_error();
void pack_s3_sstatus();

  odata = (uint8 *) malloc(sizeof(struct sstatus));
  pack_s3_sstatus(odata, &sstatus_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_sstatus, recnum)==-1) {
		print_s3_sstatus_error("write_s3_sstatus -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_sstatus, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_sstatus_error("write_s3_sstatus -> VSwrite: Couldn't write data.");

  memset(&sstatus_struc, 0, sizeof(struct sstatus));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_sstatus()
{
  VSdetach(vdata_id_s3_sstatus);
  Vdetach(vgrp_id_s3_sstatus);
}

/*----     init access function    ----*/

int32 init_acc_s3_sstatus(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_sstatus_error();


  if ((vdata_ref = VSfind(hdf_fp, "sstatus")) <= 0 ) {
    print_s3_sstatus_error("init_acc_s3_sstatus -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_sstatus = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_sstatus_error("init_acc_s3_sstatus -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_sstatus, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_sstatus,"sctime_readout, QAC, QACarr, STACMD, STARET")) {
      print_s3_sstatus_error("init_acc_s3_sstatus -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_sstatus(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_sstatus(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_sstatus(struct sstatus *sstatus_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_sstatus_error();
void unpack_s3_sstatus();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct sstatus));
  VSinquire(vdata_id_s3_sstatus, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_sstatus, recnum_rd)==FAIL) {
          print_s3_sstatus_error("read_s3_sstatus -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_sstatus, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_sstatus_error("read_s3_sstatus -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_sstatus(odata, sstatus_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_sstatus()
{
  VSdetach(vdata_id_s3_sstatus);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_sstatus(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_sstatus_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sstatus" )) ==FAIL)
    print_s3_sstatus_error("rd_Vgrp_s3_sstatus -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_sstatus_error("rd_Vgrp_s3_sstatus -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_sstatus_error("rd_Vgrp_s3_sstatus -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_sstatus_error("rd_Vgrp_s3_sstatus -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sstatus, HDstrlen(Vgrp_descrp_sstatus)) ==FAIL)
    print_s3_sstatus_error("rd_Vgrp_s3_sstatus -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sstatus);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_sstatus_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_sstatus.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_sstatus(uint8 *data, struct sstatus *sstatus_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sstatus_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sstatus_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sstatus_ptr->QACarr[0], ((1)*(720)) );
   ptr+= ((1)*(720));
   memcpy(data+ptr, &sstatus_ptr->STACMD[0], ((2)*(60)) );
   ptr+= ((2)*(60));
   memcpy(data+ptr, &sstatus_ptr->STARET[0], ((4)*(60)) );
   ptr+= ((4)*(60));
}

/*----   unpack function    ----*/

void unpack_s3_sstatus(uint8 *data, struct sstatus *sstatus_ptr)
{
int32 ptr=0;

   memcpy(&sstatus_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sstatus_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sstatus_ptr->QACarr[0], data+ptr,  ((1)*(720)) );
   ptr+= ((1)*(720));
   memcpy(&sstatus_ptr->STACMD[0], data+ptr,  ((2)*(60)) );
   ptr+= ((2)*(60));
   memcpy(&sstatus_ptr->STARET[0], data+ptr,  ((4)*(60)) );
   ptr+= ((4)*(60));
}
int32 get_vgrp_id_s3_sstatus() {return(vgrp_id_s3_sstatus);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_sstatus(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_sstatus.h' is shown below, it was used to create the data in the Vgroup named 'VG_sstatus'.\n\n");
  strcat(wr_strval,"/* Id: s3_sstatus.h,v 1.3 1998/12/07 18:12:39 ad Exp $	     */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_readout: scclock of first minor frame of Science Record */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sstatus{\n");
  strcat(wr_strval,"	uint32 sctime_readout;	/* 32 bit spacecraft time  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint32 QAC;	/* number of missing frames in this SR */\n");
  strcat(wr_strval,"	uint8  QACarr[720]; /* array of flags indicating which minor frames */\n");
  strcat(wr_strval,"	                    /* in the SR are missing. 0=OK, 1=missing */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16 STACMD[60];  /* Command bytes */\n");
  strcat(wr_strval,"	uint32 STARET[60];  /* Return bytes */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
