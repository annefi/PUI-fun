/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisDacOffset0.h,v 1.2 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisDacOffset0.h"
#include "df.h"

int32 vgrp_id_L1SisDacOffset0;
static int32 vdata_id_L1SisDacOffset0;

  /* 3037 is the size of L1SisDacOffset0.h + 1 added line */
char Vgrp_descrp_L1SisDacOffset0[3037];

/****----  init create function  ----****/

int32 init_cr_L1SisDacOffset0(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1SisDacOffset0();

  void print_L1SisDacOffset0_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisDacOffset0 = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisDacOffset0, "VG_L1SisDacOffset0"); 
  Vsetclass(vgrp_id_L1SisDacOffset0, "VG_L1SISDACOFFSET0");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisDacOffset0" )) ==FAIL) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisDacOffset0(Vgrp_descrp_L1SisDacOffset0);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisDacOffset0, sizeof(Vgrp_descrp_L1SisDacOffset0))) ==FAIL) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisDacOffset0 = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisDacOffset0, "L1SisDacOffset0");
  VSsetclass(vdata_id_L1SisDacOffset0, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisDacOffset0, vdata_id_L1SisDacOffset0)) ==FAIL) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisDacOffset0, "ClockCycle", DFNT_UINT32, (1) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define ClockCycle");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "Second1996", DFNT_UINT32, (1) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "microsecond", DFNT_UINT32, (1) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M1aGndCoarseDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M1aGndCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M1aHvCoarseDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M1aHvCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M2aGndCoarseDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M2aGndCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M2aHvCoarseDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M2aHvCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M1bGndCoarseDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M1bGndCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M1bHvCoarseDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M1bHvCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M2bGndCoarseDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M2bGndCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M2bHvCoarseDac", DFNT_UINT16, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M2bHvCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M1aGndOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M1aGndOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M1aHvOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M1aHvOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M2aGndOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M2aGndOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "M2aHvOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define M2aHvOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM1aGndCoarseDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM1aGndCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM1aHvCoarseDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM1aHvCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM2aGndCoarseDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM2aGndCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM2aHvCoarseDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM2aHvCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM1bGndCoarseDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM1bGndCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM1bHvCoarseDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM1bHvCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM2bGndCoarseDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM2bGndCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM2bHvCoarseDac", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM2bHvCoarseDac");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM1aGndOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM1aGndOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM1aHvOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM1aHvOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM2aGndOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM2aGndOffset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisDacOffset0, "QualityM2aHvOffset", DFNT_UINT8, (NUM_SIS_MATRIX_STRIPS) )) {
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSfdefine: Couldn't define QualityM2aHvOffset");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisDacOffset0,"ClockCycle, Second1996, microsecond, M1aGndCoarseDac, M1aHvCoarseDac, M2aGndCoarseDac, M2aHvCoarseDac, M1bGndCoarseDac, M1bHvCoarseDac, M2bGndCoarseDac, M2bHvCoarseDac, M1aGndOffset, M1aHvOffset, M2aGndOffset, M2aHvOffset, QualityM1aGndCoarseDac, QualityM1aHvCoarseDac, QualityM2aGndCoarseDac, QualityM2aHvCoarseDac, QualityM1bGndCoarseDac, QualityM1bHvCoarseDac, QualityM2bGndCoarseDac, QualityM2bHvCoarseDac, QualityM1aGndOffset, QualityM1aHvOffset, QualityM2aGndOffset, QualityM2aHvOffset")){
    print_L1SisDacOffset0_error("init_cr_L1SisDacOffset0 -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisDacOffset0(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisDacOffset0(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisDacOffset0(struct L1SisDacOffset0 L1SisDacOffset0_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1SisDacOffset0_error();
void pack_L1SisDacOffset0();

  odata = (uint8 *) malloc(sizeof(struct L1SisDacOffset0));
  pack_L1SisDacOffset0(odata, &L1SisDacOffset0_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1SisDacOffset0, recnum)==-1) {
		print_L1SisDacOffset0_error("write_L1SisDacOffset0 -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisDacOffset0, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisDacOffset0_error("write_L1SisDacOffset0 -> VSwrite: Couldn't write data.");

  memset(&L1SisDacOffset0_struc, 0, sizeof(struct L1SisDacOffset0));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisDacOffset0()
{
  VSdetach(vdata_id_L1SisDacOffset0);
  Vdetach(vgrp_id_L1SisDacOffset0);
}

/*----     init access function    ----*/

int32 init_acc_L1SisDacOffset0(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisDacOffset0_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1SisDacOffset0")) <= 0 ) {
    print_L1SisDacOffset0_error("init_acc_L1SisDacOffset0 -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisDacOffset0 = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisDacOffset0_error("init_acc_L1SisDacOffset0 -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisDacOffset0, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisDacOffset0,"ClockCycle, Second1996, microsecond, M1aGndCoarseDac, M1aHvCoarseDac, M2aGndCoarseDac, M2aHvCoarseDac, M1bGndCoarseDac, M1bHvCoarseDac, M2bGndCoarseDac, M2bHvCoarseDac, M1aGndOffset, M1aHvOffset, M2aGndOffset, M2aHvOffset, QualityM1aGndCoarseDac, QualityM1aHvCoarseDac, QualityM2aGndCoarseDac, QualityM2aHvCoarseDac, QualityM1bGndCoarseDac, QualityM1bHvCoarseDac, QualityM2bGndCoarseDac, QualityM2bHvCoarseDac, QualityM1aGndOffset, QualityM1aHvOffset, QualityM2aGndOffset, QualityM2aHvOffset")) {
      print_L1SisDacOffset0_error("init_acc_L1SisDacOffset0 -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisDacOffset0(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisDacOffset0(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisDacOffset0(struct L1SisDacOffset0 *L1SisDacOffset0_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisDacOffset0_error();
void unpack_L1SisDacOffset0();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1SisDacOffset0));
  VSinquire(vdata_id_L1SisDacOffset0, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisDacOffset0, recnum_rd)==FAIL) {
          print_L1SisDacOffset0_error("read_L1SisDacOffset0 -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1SisDacOffset0, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisDacOffset0_error("read_L1SisDacOffset0 -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisDacOffset0(odata, L1SisDacOffset0_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisDacOffset0()
{
  VSdetach(vdata_id_L1SisDacOffset0);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisDacOffset0(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisDacOffset0_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisDacOffset0" )) ==FAIL)
    print_L1SisDacOffset0_error("rd_Vgrp_L1SisDacOffset0 -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisDacOffset0_error("rd_Vgrp_L1SisDacOffset0 -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisDacOffset0_error("rd_Vgrp_L1SisDacOffset0 -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisDacOffset0_error("rd_Vgrp_L1SisDacOffset0 -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisDacOffset0, HDstrlen(Vgrp_descrp_L1SisDacOffset0)) ==FAIL)
    print_L1SisDacOffset0_error("rd_Vgrp_L1SisDacOffset0 -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisDacOffset0);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisDacOffset0_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisDacOffset0.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisDacOffset0(uint8 *data, struct L1SisDacOffset0 *L1SisDacOffset0_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisDacOffset0_ptr->ClockCycle, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M1aGndCoarseDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M1aHvCoarseDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M2aGndCoarseDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M2aHvCoarseDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M1bGndCoarseDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M1bHvCoarseDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M2bGndCoarseDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M2bHvCoarseDac[0], ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M1aGndOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M1aHvOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M2aGndOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->M2aHvOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM1aGndCoarseDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM1aHvCoarseDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM2aGndCoarseDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM2aHvCoarseDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM1bGndCoarseDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM1bHvCoarseDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM2bGndCoarseDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM2bHvCoarseDac[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM1aGndOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM1aHvOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM2aGndOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(data+ptr, &L1SisDacOffset0_ptr->QualityM2aHvOffset[0], ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
}

/*----   unpack function    ----*/

void unpack_L1SisDacOffset0(uint8 *data, struct L1SisDacOffset0 *L1SisDacOffset0_ptr)
{
int32 ptr=0;

   memcpy(&L1SisDacOffset0_ptr->ClockCycle, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDacOffset0_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDacOffset0_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisDacOffset0_ptr->M1aGndCoarseDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M1aHvCoarseDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M2aGndCoarseDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M2aHvCoarseDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M1bGndCoarseDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M1bHvCoarseDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M2bGndCoarseDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M2bHvCoarseDac[0], data+ptr,  ((2)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((2)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M1aGndOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M1aHvOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M2aGndOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->M2aHvOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM1aGndCoarseDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM1aHvCoarseDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM2aGndCoarseDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM2aHvCoarseDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM1bGndCoarseDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM1bHvCoarseDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM2bGndCoarseDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM2bHvCoarseDac[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM1aGndOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM1aHvOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM2aGndOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
   memcpy(&L1SisDacOffset0_ptr->QualityM2aHvOffset[0], data+ptr,  ((1)*(NUM_SIS_MATRIX_STRIPS)) );
   ptr+= ((1)*(NUM_SIS_MATRIX_STRIPS));
}
int32 get_vgrp_id_L1SisDacOffset0() {return(vgrp_id_L1SisDacOffset0);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisDacOffset0(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisDacOffset0.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisDacOffset0'.\n\n");
  strcat(wr_strval,"/* Id: L1SisDacOffset0.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDacOffset0.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisDacOffset0\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockCycle;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint16 M1aGndCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M1aHvCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M2aGndCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M2aHvCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M1bGndCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M1bHvCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M2bGndCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint16 M2bHvCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  M1aGndOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  M1aHvOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  M2aGndOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  M2aHvOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1aGndCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1aHvCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2aGndCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2aHvCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1bGndCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1bHvCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2bGndCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2bHvCoarseDac[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1aGndOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM1aHvOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2aGndOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"   uint8  QualityM2aHvOffset[NUM_SIS_MATRIX_STRIPS];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockCycle = S/C clock of the first minor frame of the cycle   */\n");
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
