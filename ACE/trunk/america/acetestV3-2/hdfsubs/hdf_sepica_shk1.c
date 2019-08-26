/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_shk1.h,v 1.2 1998/12/07 18:12:39 ad Exp  */

#include "s3_shk1.h"
#include "df.h"

int32 vgrp_id_s3_shk1;
static int32 vdata_id_s3_shk1;

  /* 1839 is the size of s3_shk1.h + 1 added line */
char Vgrp_descrp_sshshk1[1839];

/****----  init create function  ----****/

int32 init_cr_s3_shk1(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_shk1();

  void print_s3_shk1_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_shk1 = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_shk1_error("init_cr_s3_shk1 -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_shk1, "VG_sshshk1"); 
  Vsetclass(vgrp_id_s3_shk1, "VG_S3_SHK1");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sshshk1" )) ==FAIL) {
    print_s3_shk1_error("init_cr_s3_shk1 -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_shk1(Vgrp_descrp_sshshk1);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_shk1_error("init_cr_s3_shk1 -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sshshk1, sizeof(Vgrp_descrp_sshshk1))) ==FAIL) {
    print_s3_shk1_error("init_cr_s3_shk1 -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_shk1 = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_shk1, "sshshk1");
  VSsetclass(vdata_id_s3_shk1, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_shk1, vdata_id_s3_shk1)) ==FAIL) {
    print_s3_shk1_error("init_cr_s3_shk1 -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_shk1, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "QAC", DFNT_UINT32, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "HKSECTOR", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define HKSECTOR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "P5I", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define P5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "M5I", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define M5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "P15I", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define P15I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "M15I", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define M15I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "P5V", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define P5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "M5V", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define M5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "P15V", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define P15V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "M15V", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define M15V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_30KI", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _30KI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_30KV", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _30KV");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_2KI", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _2KI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_2KV", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _2KV");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_75I", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _75I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_75V", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _75V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "P5T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define P5T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "P15T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define P15T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_2KAV", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _2KAV");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_2KBV", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _2KBV");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "_2KCV", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define _2KCV");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "VAL1I", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define VAL1I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "VAL2I", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define VAL2I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "VAL3I", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define VAL3I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "VAL1V", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define VAL1V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "VAL2V", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define VAL2V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "VAL3V", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define VAL3V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "BASET", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define BASET");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "SSD1T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define SSD1T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "SSD2T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define SSD2T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "SSD3T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define SSD3T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "TANKT", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define TANKT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "EBOXT", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define EBOXT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "HV30T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define HV30T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "COLLT", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define COLLT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "PC1T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define PC1T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "PC2T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define PC2T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "PC3T", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define PC3T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk1, "GRMT", DFNT_UINT8, (1) )) {
    print_s3_shk1_error("init_cr_s3_shk1 -> VSfdefine: Couldn't define GRMT");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_shk1,"sctime_readout, sctime_collection, QAC, HKSECTOR, P5I, M5I, P15I, M15I, P5V, M5V, P15V, M15V, _30KI, _30KV, _2KI, _2KV, _75I, _75V, P5T, P15T, _2KAV, _2KBV, _2KCV, VAL1I, VAL2I, VAL3I, VAL1V, VAL2V, VAL3V, BASET, SSD1T, SSD2T, SSD3T, TANKT, EBOXT, HV30T, COLLT, PC1T, PC2T, PC3T, GRMT")){
    print_s3_shk1_error("init_cr_s3_shk1 -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_shk1(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_shk1(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_shk1(struct sshshk1 sshshk1_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_shk1_error();
void pack_s3_shk1();

  odata = (uint8 *) malloc(sizeof(struct sshshk1));
  pack_s3_shk1(odata, &sshshk1_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_shk1, recnum)==-1) {
		print_s3_shk1_error("write_s3_shk1 -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_shk1, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_shk1_error("write_s3_shk1 -> VSwrite: Couldn't write data.");

  memset(&sshshk1_struc, 0, sizeof(struct sshshk1));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_shk1()
{
  VSdetach(vdata_id_s3_shk1);
  Vdetach(vgrp_id_s3_shk1);
}

/*----     init access function    ----*/

int32 init_acc_s3_shk1(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_shk1_error();


  if ((vdata_ref = VSfind(hdf_fp, "sshshk1")) <= 0 ) {
    print_s3_shk1_error("init_acc_s3_shk1 -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_shk1 = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_shk1_error("init_acc_s3_shk1 -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_shk1, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_shk1,"sctime_readout, sctime_collection, QAC, HKSECTOR, P5I, M5I, P15I, M15I, P5V, M5V, P15V, M15V, _30KI, _30KV, _2KI, _2KV, _75I, _75V, P5T, P15T, _2KAV, _2KBV, _2KCV, VAL1I, VAL2I, VAL3I, VAL1V, VAL2V, VAL3V, BASET, SSD1T, SSD2T, SSD3T, TANKT, EBOXT, HV30T, COLLT, PC1T, PC2T, PC3T, GRMT")) {
      print_s3_shk1_error("init_acc_s3_shk1 -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_shk1(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_shk1(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_shk1(struct sshshk1 *sshshk1_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_shk1_error();
void unpack_s3_shk1();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct sshshk1));
  VSinquire(vdata_id_s3_shk1, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_shk1, recnum_rd)==FAIL) {
          print_s3_shk1_error("read_s3_shk1 -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_shk1, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_shk1_error("read_s3_shk1 -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_shk1(odata, sshshk1_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_shk1()
{
  VSdetach(vdata_id_s3_shk1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_shk1(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_shk1_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sshshk1" )) ==FAIL)
    print_s3_shk1_error("rd_Vgrp_s3_shk1 -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_shk1_error("rd_Vgrp_s3_shk1 -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_shk1_error("rd_Vgrp_s3_shk1 -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_shk1_error("rd_Vgrp_s3_shk1 -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sshshk1, HDstrlen(Vgrp_descrp_sshshk1)) ==FAIL)
    print_s3_shk1_error("rd_Vgrp_s3_shk1 -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sshshk1);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_shk1_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_shk1.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_shk1(uint8 *data, struct sshshk1 *sshshk1_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sshshk1_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk1_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &sshshk1_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk1_ptr->HKSECTOR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->P5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->M5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->P15I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->M15I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->P5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->M5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->P15V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->M15V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_30KI, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_30KV, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_2KI, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_2KV, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_75I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_75V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->P5T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->P15T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_2KAV, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_2KBV, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->_2KCV, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->VAL1I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->VAL2I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->VAL3I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->VAL1V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->VAL2V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->VAL3V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->BASET, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->SSD1T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->SSD2T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->SSD3T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->TANKT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->EBOXT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->HV30T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->COLLT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->PC1T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->PC2T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->PC3T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk1_ptr->GRMT, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_shk1(uint8 *data, struct sshshk1 *sshshk1_ptr)
{
int32 ptr=0;

   memcpy(&sshshk1_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk1_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&sshshk1_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk1_ptr->HKSECTOR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->P5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->M5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->P15I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->M15I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->P5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->M5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->P15V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->M15V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_30KI, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_30KV, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_2KI, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_2KV, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_75I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_75V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->P5T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->P15T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_2KAV, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_2KBV, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->_2KCV, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->VAL1I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->VAL2I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->VAL3I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->VAL1V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->VAL2V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->VAL3V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->BASET, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->SSD1T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->SSD2T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->SSD3T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->TANKT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->EBOXT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->HV30T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->COLLT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->PC1T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->PC2T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->PC3T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk1_ptr->GRMT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3_shk1() {return(vgrp_id_s3_shk1);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_shk1(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_shk1.h' is shown below, it was used to create the data in the Vgroup named 'VG_sshshk1'.\n\n");
  strcat(wr_strval,"/* Id: s3_shk1.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sshshk1{\n");
  strcat(wr_strval,"	uint32 sctime_readout;	/* first minor frame of readout cycle, */\n");
  strcat(wr_strval,"	                        /* 32 bit spacecraft clock time */\n");
  strcat(wr_strval,"	float64 sctime_collection; /* time of the start of the first spin in the */\n");
  strcat(wr_strval,"	                           /* 5-spin cycle. sub-second resolution */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint8 HKSECTOR;	/* Housekeeping Sector    */\n");
  strcat(wr_strval,"	uint8 P5I;	/* +5V I    */\n");
  strcat(wr_strval,"	uint8 M5I;	/* -5V I    */\n");
  strcat(wr_strval,"	uint8 P15I;	/* +15V I    */\n");
  strcat(wr_strval,"	uint8 M15I;	/* -15V I    */\n");
  strcat(wr_strval,"	uint8 P5V;	/* +5V     */\n");
  strcat(wr_strval,"	uint8 M5V;	/* -5V     */\n");
  strcat(wr_strval,"	uint8 P15V;	/* +15V     */\n");
  strcat(wr_strval,"	uint8 M15V;	/* -15V     */\n");
  strcat(wr_strval,"	uint8 _30KI;	/* 30kV I    */\n");
  strcat(wr_strval,"	uint8 _30KV;	/* 30kV     */\n");
  strcat(wr_strval,"	uint8 _2KI;	/* 2kV I    */\n");
  strcat(wr_strval,"	uint8 _2KV;	/* 2kV     */\n");
  strcat(wr_strval,"	uint8 _75I;	/* 75V I    */\n");
  strcat(wr_strval,"	uint8 _75V;	/* 75V     */\n");
  strcat(wr_strval,"	uint8 P5T;	/* +/-5V Temp.    */\n");
  strcat(wr_strval,"	uint8 P15T;	/* +/-15V Temp.    */\n");
  strcat(wr_strval,"	uint8 _2KAV;	/* 2kV A    */\n");
  strcat(wr_strval,"	uint8 _2KBV;	/* 2kV B    */\n");
  strcat(wr_strval,"	uint8 _2KCV;	/* 2kV C    */\n");
  strcat(wr_strval,"	uint8 VAL1I;	/* Valve PC 1 I  */\n");
  strcat(wr_strval,"	uint8 VAL2I;	/* Valve PC 2 I  */\n");
  strcat(wr_strval,"	uint8 VAL3I;	/* Valve PC 3 I  */\n");
  strcat(wr_strval,"	uint8 VAL1V;	/* Valve PC 1 V  */\n");
  strcat(wr_strval,"	uint8 VAL2V;	/* Valve PC 2 V  */\n");
  strcat(wr_strval,"	uint8 VAL3V;	/* Valve PC 3 V  */\n");
  strcat(wr_strval,"	uint8 BASET;	/* Base Temp.    */\n");
  strcat(wr_strval,"	uint8 SSD1T;	/* SSD 1 Temp.   */\n");
  strcat(wr_strval,"	uint8 SSD2T;	/* SSD 2 Temp.   */\n");
  strcat(wr_strval,"	uint8 SSD3T;	/* SSD 3 Temp.   */\n");
  strcat(wr_strval,"	uint8 TANKT;	/* Tank Temp.    */\n");
  strcat(wr_strval,"	uint8 EBOXT;	/* E-box Temp.    */\n");
  strcat(wr_strval,"	uint8 HV30T;	/* HV Temp.    */\n");
  strcat(wr_strval,"	uint8 COLLT;	/* Collimator Temp.    */\n");
  strcat(wr_strval,"	uint8 PC1T;	/* PC 1 Temp.   */\n");
  strcat(wr_strval,"	uint8 PC2T;	/* PC 2 Temp.   */\n");
  strcat(wr_strval,"	uint8 PC3T;	/* PC 3 Temp.   */\n");
  strcat(wr_strval,"	uint8 GRMT;	/* GRM Temp.    */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
