/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisDacOffset1.h,v 1.2 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisDacOffset1.h"
#include "df.h"

int32 vgrp_id_L1SisDacOffset1;
static int32 vdata_id_L1SisDacOffset1;

  /* 3221 is the size of L1SisDacOffset1.h + 1 added line */
char Vgrp_descrp_L1SisDacOffset1[3221];

/****----  init create function  ----****/

int32 init_cr_L1SisDacOffset1(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1SisDacOffset1();

  void print_L1SisDacOffset1_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisDacOffset1 = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisDacOffset1, "VG_L1SisDacOffset1"); 
  Vsetclass(vgrp_id_L1SisDacOffset1, "VG_L1SISDACOFFSET1");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisDacOffset1" )) ==FAIL) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisDacOffset1(Vgrp_descrp_L1SisDacOffset1);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisDacOffset1, sizeof(Vgrp_descrp_L1SisDacOffset1))) ==FAIL) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisDacOffset1 = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisDacOffset1, "L1SisDacOffset1");
  VSsetclass(vdata_id_L1SisDacOffset1, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisDacOffset1, vdata_id_L1SisDacOffset1)) ==FAIL) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisDacOffset1, "ClockCycle", DFNT_UINT32, (1) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define ClockCycle");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "Second1996", DFNT_UINT32, (1) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "microsecond", DFNT_UINT32, (1) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M1aGndFineDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M1aGndFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M1aHvFineDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M1aHvFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M2aGndFineDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M2aGndFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M2aHvFineDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M2aHvFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M1bGndFineDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M1bGndFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M1bHvFineDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M1bHvFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M2bGndFineDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M2bGndFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M2bHvFineDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M2bHvFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M1bGndOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M1bGndOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M1bHvOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M1bHvOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M2bGndOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M2bGndOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "M2bHvOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define M2bHvOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM1aGndFineDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM1aGndFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM1aHvFineDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM1aHvFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM2aGndFineDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM2aGndFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM2aHvFineDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM2aHvFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM1bGndFineDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM1bGndFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM1bHvFineDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM1bHvFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM2bGndFineDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM2bGndFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM2bHvFineDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM2bHvFineDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM1bGndOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM1bGndOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM1bHvOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM1bHvOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM2bGndOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM2bGndOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset1, "QualityM2bHvOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSfdefine: Couldn't define QualityM2bHvOffset");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisDacOffset1,"ClockCycle, Second1996, microsecond, M1aGndFineDac, M1aHvFineDac, M2aGndFineDac, M2aHvFineDac, M1bGndFineDac, M1bHvFineDac, M2bGndFineDac, M2bHvFineDac, M1bGndOffset, M1bHvOffset, M2bGndOffset, M2bHvOffset, QualityM1aGndFineDac, QualityM1aHvFineDac, QualityM2aGndFineDac, QualityM2aHvFineDac, QualityM1bGndFineDac, QualityM1bHvFineDac, QualityM2bGndFineDac, QualityM2bHvFineDac, QualityM1bGndOffset, QualityM1bHvOffset, QualityM2bGndOffset, QualityM2bHvOffset")){
    print_L1SisDacOffset1_error("init_cr_L1SisDacOffset1 -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisDacOffset1(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisDacOffset1(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisDacOffset1(struct L1SisDacOffset1 L1SisDacOffset1_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1SisDacOffset1_error();
void pack_L1SisDacOffset1();

  odata = (uint8 *) malloc(sizeof(struct L1SisDacOffset1));
  pack_L1SisDacOffset1(odata, &L1SisDacOffset1_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1SisDacOffset1, recnum)==-1) {
		print_L1SisDacOffset1_error("write_L1SisDacOffset1 -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisDacOffset1, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisDacOffset1_error("write_L1SisDacOffset1 -> VSwrite: Couldn't write data.");

  memset(&L1SisDacOffset1_struc, 0, sizeof(struct L1SisDacOffset1));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisDacOffset1()
{
  VSdetach(vdata_id_L1SisDacOffset1);
  Vdetach(vgrp_id_L1SisDacOffset1);
}

/*----     init access function    ----*/

int32 init_acc_L1SisDacOffset1(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisDacOffset1_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1SisDacOffset1")) <= 0 ) {
    print_L1SisDacOffset1_error("init_acc_L1SisDacOffset1 -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisDacOffset1 = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisDacOffset1_error("init_acc_L1SisDacOffset1 -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisDacOffset1, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisDacOffset1,"ClockCycle, Second1996, microsecond, M1aGndFineDac, M1aHvFineDac, M2aGndFineDac, M2aHvFineDac, M1bGndFineDac, M1bHvFineDac, M2bGndFineDac, M2bHvFineDac, M1bGndOffset, M1bHvOffset, M2bGndOffset, M2bHvOffset, QualityM1aGndFineDac, QualityM1aHvFineDac, QualityM2aGndFineDac, QualityM2aHvFineDac, QualityM1bGndFineDac, QualityM1bHvFineDac, QualityM2bGndFineDac, QualityM2bHvFineDac, QualityM1bGndOffset, QualityM1bHvOffset, QualityM2bGndOffset, QualityM2bHvOffset")) {
      print_L1SisDacOffset1_error("init_acc_L1SisDacOffset1 -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisDacOffset1(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisDacOffset1(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisDacOffset1(struct L1SisDacOffset1 *L1SisDacOffset1_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisDacOffset1_error();
void unpack_L1SisDacOffset1();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1SisDacOffset1));
  VSinquire(vdata_id_L1SisDacOffset1, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisDacOffset1, recnum_rd)==FAIL) {
          print_L1SisDacOffset1_error("read_L1SisDacOffset1 -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1SisDacOffset1, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisDacOffset1_error("read_L1SisDacOffset1 -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisDacOffset1(odata, L1SisDacOffset1_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisDacOffset1()
{
  VSdetach(vdata_id_L1SisDacOffset1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisDacOffset1(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisDacOffset1_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisDacOffset1" )) ==FAIL)
    print_L1SisDacOffset1_error("rd_Vgrp_L1SisDacOffset1 -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisDacOffset1_error("rd_Vgrp_L1SisDacOffset1 -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisDacOffset1_error("rd_Vgrp_L1SisDacOffset1 -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisDacOffset1_error("rd_Vgrp_L1SisDacOffset1 -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisDacOffset1, HDstrlen(Vgrp_descrp_L1SisDacOffset1)) ==FAIL)
    print_L1SisDacOffset1_error("rd_Vgrp_L1SisDacOffset1 -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisDacOffset1);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisDacOffset1_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisDacOffset1.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisDacOffset1(uint8 *data, struct L1SisDacOffset1 *L1SisDacOffset1_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisDacOffset1_ptr->ClockCycle, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M1aGndFineDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M1aHvFineDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M2aGndFineDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M2aHvFineDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M1bGndFineDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M1bHvFineDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M2bGndFineDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M2bHvFineDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M1bGndOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M1bHvOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M2bGndOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->M2bHvOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM1aGndFineDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM1aHvFineDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM2aGndFineDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM2aHvFineDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM1bGndFineDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM1bHvFineDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM2bGndFineDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM2bHvFineDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM1bGndOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM1bHvOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM2bGndOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset1_ptr->QualityM2bHvOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
}

/*----   unpack function    ----*/

void unpack_L1SisDacOffset1(uint8 *data, struct L1SisDacOffset1 *L1SisDacOffset1_ptr)
{
int32 ptr=0;

   memcpy(&L1SisDacOffset1_ptr->ClockCycle, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDacOffset1_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDacOffset1_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDacOffset1_ptr->M1aGndFineDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M1aHvFineDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M2aGndFineDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M2aHvFineDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M1bGndFineDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M1bHvFineDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M2bGndFineDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M2bHvFineDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M1bGndOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M1bHvOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M2bGndOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->M2bHvOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM1aGndFineDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM1aHvFineDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM2aGndFineDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM2aHvFineDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM1bGndFineDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM1bHvFineDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM2bGndFineDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM2bHvFineDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM1bGndOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM1bHvOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM2bGndOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset1_ptr->QualityM2bHvOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
}
int32 get_vgrp_id_L1SisDacOffset1() {return(vgrp_id_L1SisDacOffset1);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisDacOffset1(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisDacOffset1.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisDacOffset1'.\n\n");
  strcat(wr_strval,"/* Id: L1SisDacOffset1.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDacOffset1.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisDacOffset1\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockCycle;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint16 M1aGndFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M1aHvFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M2aGndFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M2aHvFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M1bGndFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M1bHvFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M2bGndFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M2bHvFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  M1bGndOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  M1bHvOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  M2bGndOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  M2bHvOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1aGndFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1aHvFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2aGndFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2aHvFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1bGndFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1bHvFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2bGndFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2bHvFineDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1bGndOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1bHvOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2bGndOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2bHvOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockCycle = Adjusted S/C clock.  The value 256 has been       */\n");
  strcat(wr_strval,"/*                 subtracted from the S/C clock of the first minor  */\n");
  strcat(wr_strval,"/*                 frame of the cycle in which the DAC and offsets   */\n");
  strcat(wr_strval,"/*                 were readout.                                     */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Note: Quality bits are defined in the table below.  If the field  */\n");
  strcat(wr_strval,"/*       which the quality byte is trying to characterize contains   */\n");
  strcat(wr_strval,"/*       multiple bytes, the quality byte associated with the field  */\n");
  strcat(wr_strval,"/*       is the logical \"or\" of the individual quality bytes.        */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Quality bits:                                                     */\n");
  strcat(wr_strval,"/*    0x01 = Format ID error                                         */\n");
  strcat(wr_strval,"/*    0x02 = Minor/major counter error                               */\n");
  strcat(wr_strval,"/*    0x04 = S/C clock error                                         */\n");
  strcat(wr_strval,"/*    0x08 = Sync bit error                                          */\n");
  strcat(wr_strval,"/*    0x10 = Command table index error                               */\n");
  strcat(wr_strval,"/*    0x20 = Cycle number error                                      */\n");
  strcat(wr_strval,"/*    0x40 = Level 0 quality bit                                     */\n");
  strcat(wr_strval,"/*    0x80 = Level 1 quality bit                                     */\n");
  return(0);
}
