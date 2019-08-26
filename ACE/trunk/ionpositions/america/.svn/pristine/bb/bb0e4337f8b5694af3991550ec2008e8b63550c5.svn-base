/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_shk5.h,v 1.2 1998/12/07 18:12:39 ad Exp  */

#include "s3_shk5.h"
#include "df.h"

int32 vgrp_id_s3_shk5;
static int32 vdata_id_s3_shk5;

  /* 1636 is the size of s3_shk5.h + 1 added line */
char Vgrp_descrp_sshshk5[1636];

/****----  init create function  ----****/

int32 init_cr_s3_shk5(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_shk5();

  void print_s3_shk5_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_shk5 = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_shk5_error("init_cr_s3_shk5 -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_shk5, "VG_sshshk5"); 
  Vsetclass(vgrp_id_s3_shk5, "VG_S3_SHK5");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sshshk5" )) ==FAIL) {
    print_s3_shk5_error("init_cr_s3_shk5 -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_shk5(Vgrp_descrp_sshshk5);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_shk5_error("init_cr_s3_shk5 -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sshshk5, sizeof(Vgrp_descrp_sshshk5))) ==FAIL) {
    print_s3_shk5_error("init_cr_s3_shk5 -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_shk5 = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_shk5, "sshshk5");
  VSsetclass(vdata_id_s3_shk5, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_shk5, vdata_id_s3_shk5)) ==FAIL) {
    print_s3_shk5_error("init_cr_s3_shk5 -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_shk5, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "QAC", DFNT_UINT32, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "HKSECTOR", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define HKSECTOR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMOP3", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMOP3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMOP2", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMOP2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMOP1", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMOP1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMUP3", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMUP3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMUP2", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMUP2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMUP1", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMUP1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMDISCHG", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMDISCHG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM30KI", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM30KI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM30KV", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM30KV");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM2KVC", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM2KVC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM2KVB", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM2KVB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM2KVA", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM2KVA");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM2KI", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM2KI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM2KV", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM2KV");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM75I", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM75I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARM75V", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARM75V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMM15I", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMM15I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMM15V", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMM15V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMP15I", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMP15I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMP15V", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMP15V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMM5I", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMM5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMM5V", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMM5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMP5I", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMP5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk5, "ALARMP5V", DFNT_UINT8, (1) )) {
    print_s3_shk5_error("init_cr_s3_shk5 -> VSfdefine: Couldn't define ALARMP5V");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_shk5,"sctime_readout, sctime_collection, QAC, HKSECTOR, ALARMOP3, ALARMOP2, ALARMOP1, ALARMUP3, ALARMUP2, ALARMUP1, ALARMDISCHG, ALARM30KI, ALARM30KV, ALARM2KVC, ALARM2KVB, ALARM2KVA, ALARM2KI, ALARM2KV, ALARM75I, ALARM75V, ALARMM15I, ALARMM15V, ALARMP15I, ALARMP15V, ALARMM5I, ALARMM5V, ALARMP5I, ALARMP5V")){
    print_s3_shk5_error("init_cr_s3_shk5 -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_shk5(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_shk5(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_shk5(struct sshshk5 sshshk5_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_shk5_error();
void pack_s3_shk5();

  odata = (uint8 *) malloc(sizeof(struct sshshk5));
  pack_s3_shk5(odata, &sshshk5_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_shk5, recnum)==-1) {
		print_s3_shk5_error("write_s3_shk5 -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_shk5, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_shk5_error("write_s3_shk5 -> VSwrite: Couldn't write data.");

  memset(&sshshk5_struc, 0, sizeof(struct sshshk5));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_shk5()
{
  VSdetach(vdata_id_s3_shk5);
  Vdetach(vgrp_id_s3_shk5);
}

/*----     init access function    ----*/

int32 init_acc_s3_shk5(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_shk5_error();


  if ((vdata_ref = VSfind(hdf_fp, "sshshk5")) <= 0 ) {
    print_s3_shk5_error("init_acc_s3_shk5 -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_shk5 = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_shk5_error("init_acc_s3_shk5 -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_shk5, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_shk5,"sctime_readout, sctime_collection, QAC, HKSECTOR, ALARMOP3, ALARMOP2, ALARMOP1, ALARMUP3, ALARMUP2, ALARMUP1, ALARMDISCHG, ALARM30KI, ALARM30KV, ALARM2KVC, ALARM2KVB, ALARM2KVA, ALARM2KI, ALARM2KV, ALARM75I, ALARM75V, ALARMM15I, ALARMM15V, ALARMP15I, ALARMP15V, ALARMM5I, ALARMM5V, ALARMP5I, ALARMP5V")) {
      print_s3_shk5_error("init_acc_s3_shk5 -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_shk5(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_shk5(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_shk5(struct sshshk5 *sshshk5_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_shk5_error();
void unpack_s3_shk5();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct sshshk5));
  VSinquire(vdata_id_s3_shk5, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_shk5, recnum_rd)==FAIL) {
          print_s3_shk5_error("read_s3_shk5 -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_shk5, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_shk5_error("read_s3_shk5 -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_shk5(odata, sshshk5_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_shk5()
{
  VSdetach(vdata_id_s3_shk5);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_shk5(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_shk5_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sshshk5" )) ==FAIL)
    print_s3_shk5_error("rd_Vgrp_s3_shk5 -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_shk5_error("rd_Vgrp_s3_shk5 -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_shk5_error("rd_Vgrp_s3_shk5 -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_shk5_error("rd_Vgrp_s3_shk5 -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sshshk5, HDstrlen(Vgrp_descrp_sshshk5)) ==FAIL)
    print_s3_shk5_error("rd_Vgrp_s3_shk5 -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sshshk5);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_shk5_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_shk5.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_shk5(uint8 *data, struct sshshk5 *sshshk5_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sshshk5_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk5_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &sshshk5_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk5_ptr->HKSECTOR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMOP3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMOP2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMOP1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMUP3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMUP2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMUP1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMDISCHG, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM30KI, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM30KV, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM2KVC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM2KVB, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM2KVA, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM2KI, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM2KV, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM75I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARM75V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMM15I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMM15V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMP15I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMP15V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMM5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMM5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMP5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk5_ptr->ALARMP5V, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_shk5(uint8 *data, struct sshshk5 *sshshk5_ptr)
{
int32 ptr=0;

   memcpy(&sshshk5_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk5_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&sshshk5_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk5_ptr->HKSECTOR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMOP3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMOP2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMOP1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMUP3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMUP2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMUP1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMDISCHG, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM30KI, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM30KV, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM2KVC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM2KVB, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM2KVA, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM2KI, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM2KV, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM75I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARM75V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMM15I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMM15V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMP15I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMP15V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMM5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMM5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMP5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk5_ptr->ALARMP5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3_shk5() {return(vgrp_id_s3_shk5);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_shk5(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_shk5.h' is shown below, it was used to create the data in the Vgroup named 'VG_sshshk5'.\n\n");
  strcat(wr_strval,"/* Id: s3_shk5.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sshshk5{\n");
  strcat(wr_strval,"	uint32 sctime_readout;	/* first minor frame of readout cycle, */\n");
  strcat(wr_strval,"	                        /* 32 bit spacecraft clock time */\n");
  strcat(wr_strval,"	float64 sctime_collection; /* time of the start of the first spin in the */\n");
  strcat(wr_strval,"	                           /* 5-spin cycle. sub-second resolution */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint8 HKSECTOR;	/* Housekeeping Sector    */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint8 ALARMOP3;	/* Overpressure Fan 3   */\n");
  strcat(wr_strval,"	uint8 ALARMOP2;	/* Overpressure Fan 2   */\n");
  strcat(wr_strval,"	uint8 ALARMOP1;	/* Overpressure Fan 1   */\n");
  strcat(wr_strval,"	uint8 ALARMUP3;	/* Underpressure Fan 3   */\n");
  strcat(wr_strval,"	uint8 ALARMUP2;	/* Underpressure Fan 2   */\n");
  strcat(wr_strval,"	uint8 ALARMUP1;	/* Underpressure Fan 1   */\n");
  strcat(wr_strval,"	uint8 ALARMDISCHG;	/* Discharge Alarm    */\n");
  strcat(wr_strval,"	uint8 ALARM30KI;	/* 30kV I Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARM30KV;	/* 30kV Alarm    */\n");
  strcat(wr_strval,"	uint8 ALARM2KVC;	/* 2kV C Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARM2KVB;	/* 2kV B Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARM2KVA;	/* 2kV A Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARM2KI;	/* 2kV I Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARM2KV;	/* 2kV Alarm    */\n");
  strcat(wr_strval,"	uint8 ALARM75I;	/* 75V I Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARM75V;	/* 75V Alarm    */\n");
  strcat(wr_strval,"	uint8 ALARMM15I;	/* -15V I Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARMM15V;	/* -15V Alarm    */\n");
  strcat(wr_strval,"	uint8 ALARMP15I;	/* +15V I Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARMP15V;	/* +15V Alarm    */\n");
  strcat(wr_strval,"	uint8 ALARMM5I;	/* -5V I Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARMM5V;	/* -5V Alarm    */\n");
  strcat(wr_strval,"	uint8 ALARMP5I;	/* +5V I Alarm   */\n");
  strcat(wr_strval,"	uint8 ALARMP5V;	/* +5V Alarm    */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
