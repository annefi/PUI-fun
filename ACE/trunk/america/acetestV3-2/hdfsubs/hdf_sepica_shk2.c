/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_shk2.h,v 1.2 1998/12/07 18:12:39 ad Exp  */

#include "s3_shk2.h"
#include "df.h"

int32 vgrp_id_s3_shk2;
static int32 vdata_id_s3_shk2;

  /* 1952 is the size of s3_shk2.h + 1 added line */
char Vgrp_descrp_sshshk2[1952];

/****----  init create function  ----****/

int32 init_cr_s3_shk2(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_shk2();

  void print_s3_shk2_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_shk2 = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_shk2_error("init_cr_s3_shk2 -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_shk2, "VG_sshshk2"); 
  Vsetclass(vgrp_id_s3_shk2, "VG_S3_SHK2");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sshshk2" )) ==FAIL) {
    print_s3_shk2_error("init_cr_s3_shk2 -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_shk2(Vgrp_descrp_sshshk2);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_shk2_error("init_cr_s3_shk2 -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sshshk2, sizeof(Vgrp_descrp_sshshk2))) ==FAIL) {
    print_s3_shk2_error("init_cr_s3_shk2 -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_shk2 = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_shk2, "sshshk2");
  VSsetclass(vdata_id_s3_shk2, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_shk2, vdata_id_s3_shk2)) ==FAIL) {
    print_s3_shk2_error("init_cr_s3_shk2 -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_shk2, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "QAC", DFNT_UINT32, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "HKSECTOR", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define HKSECTOR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "FILL1", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define FILL1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "FILL2", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define FILL2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "FILL3", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define FILL3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "POWERS", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define POWERS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "RELAYS", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define RELAYS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "OVERI", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define OVERI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "P15LIM", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define P15LIM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "M15LIM", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define M15LIM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "P5LIM", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define P5LIM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "M5LIM", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define M5LIM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_30KSTATH", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _30KSTATH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_30KSET", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _30KSET");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_30KSTATL", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _30KSTATL");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KASTATH", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KASTATH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KASET", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KASET");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KASTATL", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KASTATL");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KBSTATH", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KBSTATH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KBSET", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KBSET");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KBSTATL", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KBSTATL");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KCSTATH", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KCSTATH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KCSET", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KCSET");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_2KCSTATL", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _2KCSTATL");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_75STATH", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _75STATH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_75SET", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _75SET");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "_75STATL", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define _75STATL");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "PC1P", DFNT_UINT16, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define PC1P");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "PC2P", DFNT_UINT16, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define PC2P");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "PC3P", DFNT_UINT16, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define PC3P");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "LINEP", DFNT_UINT16, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define LINEP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "PC1O", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define PC1O");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "PC2O", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define PC2O");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "PC3O", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define PC3O");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk2, "ALARMS", DFNT_UINT8, (1) )) {
    print_s3_shk2_error("init_cr_s3_shk2 -> VSfdefine: Couldn't define ALARMS");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_shk2,"sctime_readout, sctime_collection, QAC, HKSECTOR, FILL1, FILL2, FILL3, POWERS, RELAYS, OVERI, P15LIM, M15LIM, P5LIM, M5LIM, _30KSTATH, _30KSET, _30KSTATL, _2KASTATH, _2KASET, _2KASTATL, _2KBSTATH, _2KBSET, _2KBSTATL, _2KCSTATH, _2KCSET, _2KCSTATL, _75STATH, _75SET, _75STATL, PC1P, PC2P, PC3P, LINEP, PC1O, PC2O, PC3O, ALARMS")){
    print_s3_shk2_error("init_cr_s3_shk2 -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_shk2(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_shk2(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_shk2(struct sshshk2 sshshk2_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_shk2_error();
void pack_s3_shk2();

  odata = (uint8 *) malloc(sizeof(struct sshshk2));
  pack_s3_shk2(odata, &sshshk2_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_shk2, recnum)==-1) {
		print_s3_shk2_error("write_s3_shk2 -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_shk2, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_shk2_error("write_s3_shk2 -> VSwrite: Couldn't write data.");

  memset(&sshshk2_struc, 0, sizeof(struct sshshk2));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_shk2()
{
  VSdetach(vdata_id_s3_shk2);
  Vdetach(vgrp_id_s3_shk2);
}

/*----     init access function    ----*/

int32 init_acc_s3_shk2(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_shk2_error();


  if ((vdata_ref = VSfind(hdf_fp, "sshshk2")) <= 0 ) {
    print_s3_shk2_error("init_acc_s3_shk2 -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_shk2 = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_shk2_error("init_acc_s3_shk2 -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_shk2, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_shk2,"sctime_readout, sctime_collection, QAC, HKSECTOR, FILL1, FILL2, FILL3, POWERS, RELAYS, OVERI, P15LIM, M15LIM, P5LIM, M5LIM, _30KSTATH, _30KSET, _30KSTATL, _2KASTATH, _2KASET, _2KASTATL, _2KBSTATH, _2KBSET, _2KBSTATL, _2KCSTATH, _2KCSET, _2KCSTATL, _75STATH, _75SET, _75STATL, PC1P, PC2P, PC3P, LINEP, PC1O, PC2O, PC3O, ALARMS")) {
      print_s3_shk2_error("init_acc_s3_shk2 -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_shk2(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_shk2(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_shk2(struct sshshk2 *sshshk2_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_shk2_error();
void unpack_s3_shk2();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct sshshk2));
  VSinquire(vdata_id_s3_shk2, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_shk2, recnum_rd)==FAIL) {
          print_s3_shk2_error("read_s3_shk2 -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_shk2, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_shk2_error("read_s3_shk2 -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_shk2(odata, sshshk2_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_shk2()
{
  VSdetach(vdata_id_s3_shk2);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_shk2(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_shk2_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sshshk2" )) ==FAIL)
    print_s3_shk2_error("rd_Vgrp_s3_shk2 -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_shk2_error("rd_Vgrp_s3_shk2 -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_shk2_error("rd_Vgrp_s3_shk2 -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_shk2_error("rd_Vgrp_s3_shk2 -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sshshk2, HDstrlen(Vgrp_descrp_sshshk2)) ==FAIL)
    print_s3_shk2_error("rd_Vgrp_s3_shk2 -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sshshk2);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_shk2_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_shk2.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_shk2(uint8 *data, struct sshshk2 *sshshk2_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sshshk2_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk2_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &sshshk2_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk2_ptr->HKSECTOR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->FILL1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->FILL2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->FILL3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->POWERS, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->RELAYS, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->OVERI, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->P15LIM, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->M15LIM, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->P5LIM, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->M5LIM, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_30KSTATH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_30KSET, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_30KSTATL, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KASTATH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KASET, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KASTATL, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KBSTATH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KBSET, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KBSTATL, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KCSTATH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KCSET, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_2KCSTATL, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_75STATH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_75SET, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->_75STATL, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->PC1P, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshshk2_ptr->PC2P, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshshk2_ptr->PC3P, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshshk2_ptr->LINEP, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshshk2_ptr->PC1O, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->PC2O, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->PC3O, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk2_ptr->ALARMS, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_shk2(uint8 *data, struct sshshk2 *sshshk2_ptr)
{
int32 ptr=0;

   memcpy(&sshshk2_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk2_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&sshshk2_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk2_ptr->HKSECTOR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->FILL1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->FILL2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->FILL3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->POWERS, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->RELAYS, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->OVERI, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->P15LIM, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->M15LIM, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->P5LIM, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->M5LIM, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_30KSTATH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_30KSET, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_30KSTATL, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KASTATH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KASET, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KASTATL, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KBSTATH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KBSET, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KBSTATL, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KCSTATH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KCSET, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_2KCSTATL, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_75STATH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_75SET, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->_75STATL, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->PC1P, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshshk2_ptr->PC2P, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshshk2_ptr->PC3P, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshshk2_ptr->LINEP, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshshk2_ptr->PC1O, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->PC2O, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->PC3O, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk2_ptr->ALARMS, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3_shk2() {return(vgrp_id_s3_shk2);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_shk2(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_shk2.h' is shown below, it was used to create the data in the Vgroup named 'VG_sshshk2'.\n\n");
  strcat(wr_strval,"/* Id: s3_shk2.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sshshk2{\n");
  strcat(wr_strval,"	uint32 sctime_readout;	/* first minor frame of readout cycle, */\n");
  strcat(wr_strval,"	                        /* 32 bit spacecraft clock time */\n");
  strcat(wr_strval,"	float64 sctime_collection; /* time of the start of the first spin in the */\n");
  strcat(wr_strval,"	                           /* 5-spin cycle. sub-second resolution */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint8 HKSECTOR;	/* Housekeeping Sector    */\n");
  strcat(wr_strval,"	uint8 FILL1;	/* Fill Time PC 1  */\n");
  strcat(wr_strval,"	uint8 FILL2;	/* Fill Time PC 2  */\n");
  strcat(wr_strval,"	uint8 FILL3;	/* Fill Time PC 3  */\n");
  strcat(wr_strval,"	uint8 POWERS;	/* Power Status    */\n");
  strcat(wr_strval,"	uint8 RELAYS;	/* Relay Status    */\n");
  strcat(wr_strval,"	uint8 OVERI;	/* Over Currents    */\n");
  strcat(wr_strval,"	uint8 P15LIM;	/* +15V Current Limit   */\n");
  strcat(wr_strval,"	uint8 M15LIM;	/* -15V Current Limit   */\n");
  strcat(wr_strval,"	uint8 P5LIM;	/* +5V Current Limit   */\n");
  strcat(wr_strval,"	uint8 M5LIM;	/* -5V Current Limit   */\n");
  strcat(wr_strval,"	uint8 _30KSTATH;	/* 30kV Discharge    */\n");
  strcat(wr_strval,"	uint8 _30KSET;	/* 30kV Set Value   */\n");
  strcat(wr_strval,"	uint8 _30KSTATL;	/* 30kV Plug Status   */\n");
  strcat(wr_strval,"	uint8 _2KASTATH;	/* 2kV A Discharge   */\n");
  strcat(wr_strval,"	uint8 _2KASET;	/* 2kV A Set Value  */\n");
  strcat(wr_strval,"	uint8 _2KASTATL;	/* 2kV A Plug Status  */\n");
  strcat(wr_strval,"	uint8 _2KBSTATH;	/* 2kV B Discharge   */\n");
  strcat(wr_strval,"	uint8 _2KBSET;	/* 2kV B Set Value  */\n");
  strcat(wr_strval,"	uint8 _2KBSTATL;	/* 2kV B Plug Status  */\n");
  strcat(wr_strval,"	uint8 _2KCSTATH;	/* 2kV C Discharge   */\n");
  strcat(wr_strval,"	uint8 _2KCSET;	/* 2kV C Set Value  */\n");
  strcat(wr_strval,"	uint8 _2KCSTATL;	/* 2kV C Plug Status  */\n");
  strcat(wr_strval,"	uint8 _75STATH;	/* 75V Discharge    */\n");
  strcat(wr_strval,"	uint8 _75SET;	/* 75V Set Value   */\n");
  strcat(wr_strval,"	uint8 _75STATL;	/* 75V Plug Status   */\n");
  strcat(wr_strval,"	uint16 PC1P;	/* PC 1 Pres.   */\n");
  strcat(wr_strval,"	uint16 PC2P;	/* PC 2 Pres.   */\n");
  strcat(wr_strval,"	uint16 PC3P;	/* PC 3 Pres.   */\n");
  strcat(wr_strval,"	uint16 LINEP;	/* line Pres.    */\n");
  strcat(wr_strval,"	uint8 PC1O;	/* PC 1 On/Off   */\n");
  strcat(wr_strval,"	uint8 PC2O;	/* PC 2 On/Off   */\n");
  strcat(wr_strval,"	uint8 PC3O;	/* PC 3 On/Off   */\n");
  strcat(wr_strval,"	uint8 ALARMS;	/* Alarm Flags    */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
