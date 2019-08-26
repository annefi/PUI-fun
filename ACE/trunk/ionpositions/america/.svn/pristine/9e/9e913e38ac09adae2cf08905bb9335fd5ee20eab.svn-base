/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_shk4.h,v 1.2 1998/12/07 18:12:39 ad Exp  */

#include "s3_shk4.h"
#include "df.h"

int32 vgrp_id_s3_shk4;
static int32 vdata_id_s3_shk4;

  /* 1949 is the size of s3_shk4.h + 1 added line */
char Vgrp_descrp_sshshk4[1949];

/****----  init create function  ----****/

int32 init_cr_s3_shk4(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_shk4();

  void print_s3_shk4_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_shk4 = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_shk4_error("init_cr_s3_shk4 -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_shk4, "VG_sshshk4"); 
  Vsetclass(vgrp_id_s3_shk4, "VG_S3_SHK4");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sshshk4" )) ==FAIL) {
    print_s3_shk4_error("init_cr_s3_shk4 -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_shk4(Vgrp_descrp_sshshk4);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_shk4_error("init_cr_s3_shk4 -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sshshk4, sizeof(Vgrp_descrp_sshshk4))) ==FAIL) {
    print_s3_shk4_error("init_cr_s3_shk4 -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_shk4 = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_shk4, "sshshk4");
  VSsetclass(vdata_id_s3_shk4, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_shk4, vdata_id_s3_shk4)) ==FAIL) {
    print_s3_shk4_error("init_cr_s3_shk4 -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_shk4, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "QAC", DFNT_UINT32, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "HKSECTOR", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define HKSECTOR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "PC1YTH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define PC1YTH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "PC1ZTH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define PC1ZTH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "PC2YTH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define PC2YTH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "PC2ZTH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define PC2ZTH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "PC3YTH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define PC3YTH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "PC3ZTH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define PC3ZTH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "SSD1TH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define SSD1TH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "BIT1PERIOD", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define BIT1PERIOD");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "SSD2TH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define SSD2TH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "BIT2PERIOD", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define BIT2PERIOD");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "SSD3TH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define SSD3TH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "BIT3PERIOD", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define BIT3PERIOD");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DEDX1TH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DEDX1TH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DEDX2TH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DEDX2TH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DEDX3TH", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DEDX3TH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET1TRIG", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET1TRIG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET1EVENT", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET1EVENT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET1GAIN", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET1GAIN");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET1CHANNELS", DFNT_UINT16, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET1CHANNELS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET2TRIG", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET2TRIG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET2EVENT", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET2EVENT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET2GAIN", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET2GAIN");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET2CHANNELS", DFNT_UINT16, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET2CHANNELS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET3TRIG", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET3TRIG");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET3EVENT", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET3EVENT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET3GAIN", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET3GAIN");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "DET3CHANNELS", DFNT_UINT16, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define DET3CHANNELS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "ACTRCTRL", DFNT_UINT16, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define ACTRCTRL");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "FANPRIOR", DFNT_UINT8, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define FANPRIOR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk4, "ACTRSAMPLE", DFNT_UINT16, (1) )) {
    print_s3_shk4_error("init_cr_s3_shk4 -> VSfdefine: Couldn't define ACTRSAMPLE");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_shk4,"sctime_readout, sctime_collection, QAC, HKSECTOR, PC1YTH, PC1ZTH, PC2YTH, PC2ZTH, PC3YTH, PC3ZTH, SSD1TH, BIT1PERIOD, SSD2TH, BIT2PERIOD, SSD3TH, BIT3PERIOD, DEDX1TH, DEDX2TH, DEDX3TH, DET1TRIG, DET1EVENT, DET1GAIN, DET1CHANNELS, DET2TRIG, DET2EVENT, DET2GAIN, DET2CHANNELS, DET3TRIG, DET3EVENT, DET3GAIN, DET3CHANNELS, ACTRCTRL, FANPRIOR, ACTRSAMPLE")){
    print_s3_shk4_error("init_cr_s3_shk4 -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_shk4(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_shk4(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_shk4(struct sshshk4 sshshk4_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_shk4_error();
void pack_s3_shk4();

  odata = (uint8 *) malloc(sizeof(struct sshshk4));
  pack_s3_shk4(odata, &sshshk4_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_shk4, recnum)==-1) {
		print_s3_shk4_error("write_s3_shk4 -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_shk4, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_shk4_error("write_s3_shk4 -> VSwrite: Couldn't write data.");

  memset(&sshshk4_struc, 0, sizeof(struct sshshk4));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_shk4()
{
  VSdetach(vdata_id_s3_shk4);
  Vdetach(vgrp_id_s3_shk4);
}

/*----     init access function    ----*/

int32 init_acc_s3_shk4(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_shk4_error();


  if ((vdata_ref = VSfind(hdf_fp, "sshshk4")) <= 0 ) {
    print_s3_shk4_error("init_acc_s3_shk4 -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_shk4 = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_shk4_error("init_acc_s3_shk4 -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_shk4, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_shk4,"sctime_readout, sctime_collection, QAC, HKSECTOR, PC1YTH, PC1ZTH, PC2YTH, PC2ZTH, PC3YTH, PC3ZTH, SSD1TH, BIT1PERIOD, SSD2TH, BIT2PERIOD, SSD3TH, BIT3PERIOD, DEDX1TH, DEDX2TH, DEDX3TH, DET1TRIG, DET1EVENT, DET1GAIN, DET1CHANNELS, DET2TRIG, DET2EVENT, DET2GAIN, DET2CHANNELS, DET3TRIG, DET3EVENT, DET3GAIN, DET3CHANNELS, ACTRCTRL, FANPRIOR, ACTRSAMPLE")) {
      print_s3_shk4_error("init_acc_s3_shk4 -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_shk4(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_shk4(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_shk4(struct sshshk4 *sshshk4_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_shk4_error();
void unpack_s3_shk4();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct sshshk4));
  VSinquire(vdata_id_s3_shk4, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_shk4, recnum_rd)==FAIL) {
          print_s3_shk4_error("read_s3_shk4 -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_shk4, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_shk4_error("read_s3_shk4 -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_shk4(odata, sshshk4_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_shk4()
{
  VSdetach(vdata_id_s3_shk4);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_shk4(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_shk4_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sshshk4" )) ==FAIL)
    print_s3_shk4_error("rd_Vgrp_s3_shk4 -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_shk4_error("rd_Vgrp_s3_shk4 -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_shk4_error("rd_Vgrp_s3_shk4 -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_shk4_error("rd_Vgrp_s3_shk4 -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sshshk4, HDstrlen(Vgrp_descrp_sshshk4)) ==FAIL)
    print_s3_shk4_error("rd_Vgrp_s3_shk4 -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sshshk4);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_shk4_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_shk4.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_shk4(uint8 *data, struct sshshk4 *sshshk4_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sshshk4_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk4_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &sshshk4_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk4_ptr->HKSECTOR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->PC1YTH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->PC1ZTH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->PC2YTH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->PC2ZTH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->PC3YTH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->PC3ZTH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->SSD1TH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->BIT1PERIOD, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->SSD2TH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->BIT2PERIOD, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->SSD3TH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->BIT3PERIOD, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DEDX1TH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DEDX2TH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DEDX3TH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET1TRIG, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET1EVENT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET1GAIN, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET1CHANNELS, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET2TRIG, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET2EVENT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET2GAIN, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET2CHANNELS, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET3TRIG, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET3EVENT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET3GAIN, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->DET3CHANNELS, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshshk4_ptr->ACTRCTRL, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshshk4_ptr->FANPRIOR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk4_ptr->ACTRSAMPLE, ((2)*(1)) );
   ptr+= ((2)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_shk4(uint8 *data, struct sshshk4 *sshshk4_ptr)
{
int32 ptr=0;

   memcpy(&sshshk4_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk4_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&sshshk4_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk4_ptr->HKSECTOR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->PC1YTH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->PC1ZTH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->PC2YTH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->PC2ZTH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->PC3YTH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->PC3ZTH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->SSD1TH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->BIT1PERIOD, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->SSD2TH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->BIT2PERIOD, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->SSD3TH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->BIT3PERIOD, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DEDX1TH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DEDX2TH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DEDX3TH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET1TRIG, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET1EVENT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET1GAIN, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET1CHANNELS, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshshk4_ptr->DET2TRIG, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET2EVENT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET2GAIN, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET2CHANNELS, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshshk4_ptr->DET3TRIG, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET3EVENT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET3GAIN, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->DET3CHANNELS, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshshk4_ptr->ACTRCTRL, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshshk4_ptr->FANPRIOR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk4_ptr->ACTRSAMPLE, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
}
int32 get_vgrp_id_s3_shk4() {return(vgrp_id_s3_shk4);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_shk4(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_shk4.h' is shown below, it was used to create the data in the Vgroup named 'VG_sshshk4'.\n\n");
  strcat(wr_strval,"/* Id: s3_shk4.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sshshk4{\n");
  strcat(wr_strval,"	uint32 sctime_readout;	/* first minor frame of readout cycle, */\n");
  strcat(wr_strval,"	                        /* 32 bit spacecraft clock time */\n");
  strcat(wr_strval,"	float64 sctime_collection; /* time of the start of the first spin in the */\n");
  strcat(wr_strval,"	                           /* 5-spin cycle. sub-second resolution */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint8 HKSECTOR;	/* Housekeeping Sector    */\n");
  strcat(wr_strval,"	uint8 PC1YTH;	/* PC 1 Y Threshold  */\n");
  strcat(wr_strval,"	uint8 PC1ZTH;	/* PC 1 Z Threshold  */\n");
  strcat(wr_strval,"	uint8 PC2YTH;	/* PC 2 Y Threshold  */\n");
  strcat(wr_strval,"	uint8 PC2ZTH;	/* PC 2 Z Threshold  */\n");
  strcat(wr_strval,"	uint8 PC3YTH;	/* PC 3 Y Threshold  */\n");
  strcat(wr_strval,"	uint8 PC3ZTH;	/* PC 3 Z Threshold  */\n");
  strcat(wr_strval,"	uint8 SSD1TH;	/* SSD 1 Threshold   */\n");
  strcat(wr_strval,"	uint8 BIT1PERIOD;	/* BIT 1 Period   */\n");
  strcat(wr_strval,"	uint8 SSD2TH;	/* SSD 2 Threshold   */\n");
  strcat(wr_strval,"	uint8 BIT2PERIOD;	/* BIT 2 Period   */\n");
  strcat(wr_strval,"	uint8 SSD3TH;	/* SSD 3 Threshold   */\n");
  strcat(wr_strval,"	uint8 BIT3PERIOD;	/* BIT 3 Period   */\n");
  strcat(wr_strval,"	uint8 DEDX1TH;	/* dEdX 1 Threshold   */\n");
  strcat(wr_strval,"	uint8 DEDX2TH;	/* dEdX 2 Threshold   */\n");
  strcat(wr_strval,"	uint8 DEDX3TH;	/* dEdX 3 Threshold   */\n");
  strcat(wr_strval,"	uint8 DET1TRIG;	/* CAMEX 1 Trigger   */\n");
  strcat(wr_strval,"	uint8 DET1EVENT;	/* Valid Event 1 Condition  */\n");
  strcat(wr_strval,"	uint8 DET1GAIN;	/* SSD 1 CAMEX Gain  */\n");
  strcat(wr_strval,"	uint16 DET1CHANNELS;	/* BIT 1 Channels   */\n");
  strcat(wr_strval,"	uint8 DET2TRIG;	/* CAMEX 2 Trigger   */\n");
  strcat(wr_strval,"	uint8 DET2EVENT;	/* Valid Event 2 Condition  */\n");
  strcat(wr_strval,"	uint8 DET2GAIN;	/* SSD 2 CAMEX Gain  */\n");
  strcat(wr_strval,"	uint16 DET2CHANNELS;	/* BIT 2 Channels   */\n");
  strcat(wr_strval,"	uint8 DET3TRIG;	/* CAMEX 3 Trigger   */\n");
  strcat(wr_strval,"	uint8 DET3EVENT;	/* Valid Event 3 Condition  */\n");
  strcat(wr_strval,"	uint8 DET3GAIN;	/* SSD 3 CAMEX Gain  */\n");
  strcat(wr_strval,"	uint16 DET3CHANNELS;	/* BIT 3 Channels   */\n");
  strcat(wr_strval,"	uint16 ACTRCTRL;	/* ACTR Control Register   */\n");
  strcat(wr_strval,"	uint8 FANPRIOR; /* Fan Priority    */\n");
  strcat(wr_strval,"	uint16 ACTRSAMPLE;      /* ACTR Sample Register   */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
