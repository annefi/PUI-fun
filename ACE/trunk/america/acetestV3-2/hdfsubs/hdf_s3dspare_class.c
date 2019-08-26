/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_dspare_class.h,v 1.2 1998/01/28 17:41:29 hemple Exp  */

#include "s3_dspare_class.h"
#include "df.h"

int32 vgrp_id_s3_dspare_class;
static int32 vdata_id_s3_dspare_class;

  /* 1247 is the size of s3_dspare_class.h + 1 added line */
char Vgrp_descrp_s3s_dspare_class[1247];

/****----  init create function  ----****/

int32 init_cr_s3_dspare_class(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_dspare_class();

  void print_s3_dspare_class_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_dspare_class = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_dspare_class, "VG_s3s_dspare_class"); 
  Vsetclass(vgrp_id_s3_dspare_class, "VG_S3_DSPARE_CLASS");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_s3s_dspare_class" )) ==FAIL) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_dspare_class(Vgrp_descrp_s3s_dspare_class);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_s3s_dspare_class, sizeof(Vgrp_descrp_s3s_dspare_class))) ==FAIL) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_dspare_class = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_dspare_class, "s3s_dspare_class");
  VSsetclass(vdata_id_s3_dspare_class, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_dspare_class, vdata_id_s3_dspare_class)) ==FAIL) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_dspare_class, "sctime", DFNT_UINT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "sbitable", DFNT_UINT8, (SBITABLEITEMS) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define sbitable");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "srctable", DFNT_UINT8, (SRCTABLEITEMS) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define srctable");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "sdetable", DFNT_UINT8, (SDETABLEITEMS) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define sdetable");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "scos", DFNT_UINT8, (SCOSITEMS) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define scos");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "scos2", DFNT_UINT8, (SCOS2ITEMS) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define scos2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_Emin0", DFNT_INT16, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_Emin0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_Emin1", DFNT_INT16, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_Emin1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_MinClass", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_MinClass");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_MaxClass", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_MaxClass");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_Eoffset0", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_Eoffset0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_Eoffset1", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_Eoffset1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_E00", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_E00");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_E01", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_E01");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_E1", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_E1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlndE_Cosine", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlndE_Cosine");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_Emin0", DFNT_INT16, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_Emin0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_Emin1", DFNT_INT16, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_Emin1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_MinClass", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_MinClass");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_MaxClass", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_MaxClass");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_Eoffset0", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_Eoffset0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_Eoffset1", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_Eoffset1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_E00", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_E00");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_E01", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_E01");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SlnE_E1", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SlnE_E1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SY_focal", DFNT_INT16, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SY_focal");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SY_Cosine", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SY_Cosine");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SY_Y1", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SY_Y1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SQ_MaxQ", DFNT_INT16, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SQ_MaxQ");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SQ_Q10", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SQ_Q10");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "SQ_Q11", DFNT_FLOAT32, (1) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define SQ_Q11");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_class, "spseq", DFNT_UINT8, (SPSEQITEMS) )) {
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSfdefine: Couldn't define spseq");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_dspare_class,"sctime, sbitable, srctable, sdetable, scos, scos2, SlndE_Emin0, SlndE_Emin1, SlndE_MinClass, SlndE_MaxClass, SlndE_Eoffset0, SlndE_Eoffset1, SlndE_E00, SlndE_E01, SlndE_E1, SlndE_Cosine, SlnE_Emin0, SlnE_Emin1, SlnE_MinClass, SlnE_MaxClass, SlnE_Eoffset0, SlnE_Eoffset1, SlnE_E00, SlnE_E01, SlnE_E1, SY_focal, SY_Cosine, SY_Y1, SQ_MaxQ, SQ_Q10, SQ_Q11, spseq")){
    print_s3_dspare_class_error("init_cr_s3_dspare_class -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_dspare_class(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_dspare_class(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_dspare_class(struct s3s_dspare_class s3s_dspare_class_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_dspare_class_error();
void pack_s3_dspare_class();

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_class));
  pack_s3_dspare_class(odata, &s3s_dspare_class_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_dspare_class, recnum)==-1) {
		print_s3_dspare_class_error("write_s3_dspare_class -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_dspare_class, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_dspare_class_error("write_s3_dspare_class -> VSwrite: Couldn't write data.");

  memset(&s3s_dspare_class_struc, 0, sizeof(struct s3s_dspare_class));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_dspare_class()
{
  VSdetach(vdata_id_s3_dspare_class);
  Vdetach(vgrp_id_s3_dspare_class);
}

/*----     init access function    ----*/

int32 init_acc_s3_dspare_class(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_dspare_class_error();


  if ((vdata_ref = VSfind(hdf_fp, "s3s_dspare_class")) <= 0 ) {
    print_s3_dspare_class_error("init_acc_s3_dspare_class -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_dspare_class = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_dspare_class_error("init_acc_s3_dspare_class -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_dspare_class, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_dspare_class,"sctime, sbitable, srctable, sdetable, scos, scos2, SlndE_Emin0, SlndE_Emin1, SlndE_MinClass, SlndE_MaxClass, SlndE_Eoffset0, SlndE_Eoffset1, SlndE_E00, SlndE_E01, SlndE_E1, SlndE_Cosine, SlnE_Emin0, SlnE_Emin1, SlnE_MinClass, SlnE_MaxClass, SlnE_Eoffset0, SlnE_Eoffset1, SlnE_E00, SlnE_E01, SlnE_E1, SY_focal, SY_Cosine, SY_Y1, SQ_MaxQ, SQ_Q10, SQ_Q11, spseq")) {
      print_s3_dspare_class_error("init_acc_s3_dspare_class -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_dspare_class(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_dspare_class(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_dspare_class(struct s3s_dspare_class *s3s_dspare_class_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_dspare_class_error();
void unpack_s3_dspare_class();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_class));
  VSinquire(vdata_id_s3_dspare_class, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_dspare_class, recnum_rd)==FAIL) {
          print_s3_dspare_class_error("read_s3_dspare_class -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_dspare_class, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_dspare_class_error("read_s3_dspare_class -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_dspare_class(odata, s3s_dspare_class_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_dspare_class()
{
  VSdetach(vdata_id_s3_dspare_class);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_dspare_class(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_dspare_class_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_s3s_dspare_class" )) ==FAIL)
    print_s3_dspare_class_error("rd_Vgrp_s3_dspare_class -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_dspare_class_error("rd_Vgrp_s3_dspare_class -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_dspare_class_error("rd_Vgrp_s3_dspare_class -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_dspare_class_error("rd_Vgrp_s3_dspare_class -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_s3s_dspare_class, HDstrlen(Vgrp_descrp_s3s_dspare_class)) ==FAIL)
    print_s3_dspare_class_error("rd_Vgrp_s3_dspare_class -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_s3s_dspare_class);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_dspare_class_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3dspare_class.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_dspare_class(uint8 *data, struct s3s_dspare_class *s3s_dspare_class_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &s3s_dspare_class_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->sbitable[0], ((1)*(SBITABLEITEMS)) );
   ptr+= ((1)*(SBITABLEITEMS));
   memcpy(data+ptr, &s3s_dspare_class_ptr->srctable[0], ((1)*(SRCTABLEITEMS)) );
   ptr+= ((1)*(SRCTABLEITEMS));
   memcpy(data+ptr, &s3s_dspare_class_ptr->sdetable[0], ((1)*(SDETABLEITEMS)) );
   ptr+= ((1)*(SDETABLEITEMS));
   memcpy(data+ptr, &s3s_dspare_class_ptr->scos[0], ((1)*(SCOSITEMS)) );
   ptr+= ((1)*(SCOSITEMS));
   memcpy(data+ptr, &s3s_dspare_class_ptr->scos2[0], ((1)*(SCOS2ITEMS)) );
   ptr+= ((1)*(SCOS2ITEMS));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_Emin0, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_Emin1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_MinClass, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_MaxClass, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_Eoffset0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_Eoffset1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_E00, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_E01, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_E1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlndE_Cosine, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_Emin0, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_Emin1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_MinClass, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_MaxClass, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_Eoffset0, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_Eoffset1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_E00, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_E01, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SlnE_E1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SY_focal, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SY_Cosine, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SY_Y1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SQ_MaxQ, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SQ_Q10, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->SQ_Q11, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_class_ptr->spseq[0], ((1)*(SPSEQITEMS)) );
   ptr+= ((1)*(SPSEQITEMS));
}

/*----   unpack function    ----*/

void unpack_s3_dspare_class(uint8 *data, struct s3s_dspare_class *s3s_dspare_class_ptr)
{
int32 ptr=0;

   memcpy(&s3s_dspare_class_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->sbitable[0], data+ptr,  ((1)*(SBITABLEITEMS)) );
   ptr+= ((1)*(SBITABLEITEMS));
   memcpy(&s3s_dspare_class_ptr->srctable[0], data+ptr,  ((1)*(SRCTABLEITEMS)) );
   ptr+= ((1)*(SRCTABLEITEMS));
   memcpy(&s3s_dspare_class_ptr->sdetable[0], data+ptr,  ((1)*(SDETABLEITEMS)) );
   ptr+= ((1)*(SDETABLEITEMS));
   memcpy(&s3s_dspare_class_ptr->scos[0], data+ptr,  ((1)*(SCOSITEMS)) );
   ptr+= ((1)*(SCOSITEMS));
   memcpy(&s3s_dspare_class_ptr->scos2[0], data+ptr,  ((1)*(SCOS2ITEMS)) );
   ptr+= ((1)*(SCOS2ITEMS));
   memcpy(&s3s_dspare_class_ptr->SlndE_Emin0, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_Emin1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_MinClass, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_MaxClass, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_Eoffset0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_Eoffset1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_E00, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_E01, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_E1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlndE_Cosine, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_Emin0, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_Emin1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_MinClass, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_MaxClass, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_Eoffset0, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_Eoffset1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_E00, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_E01, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SlnE_E1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SY_focal, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_class_ptr->SY_Cosine, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SY_Y1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SQ_MaxQ, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&s3s_dspare_class_ptr->SQ_Q10, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->SQ_Q11, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_class_ptr->spseq[0], data+ptr,  ((1)*(SPSEQITEMS)) );
   ptr+= ((1)*(SPSEQITEMS));
}
int32 get_vgrp_id_s3_dspare_class() {return(vgrp_id_s3_dspare_class);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_dspare_class(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_dspare_class.h' is shown below, it was used to create the data in the Vgroup named 'VG_s3s_dspare_class'.\n\n");
  strcat(wr_strval,"/* Id: s3_dspare_class.h,v 1.2 1998/01/28 17:41:29 hemple Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SBITABLEITEMS 256\n");
  strcat(wr_strval,"#define SRCTABLEITEMS 256\n");
  strcat(wr_strval,"#define SDETABLEITEMS 480\n");
  strcat(wr_strval,"#define SCOSITEMS 16\n");
  strcat(wr_strval,"#define SCOS2ITEMS 32\n");
  strcat(wr_strval,"#define SLNDEITEMS 36\n");
  strcat(wr_strval,"#define SLNEITEMS 32\n");
  strcat(wr_strval,"#define SYITEMS 20\n");
  strcat(wr_strval,"#define SPSEQITEMS 31\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct s3s_dspare_class {\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"uint32 sctime; /* 32bit spacecraft time */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"uint8 sbitable[SBITABLEITEMS];\n");
  strcat(wr_strval,"uint8 srctable[SRCTABLEITEMS];\n");
  strcat(wr_strval,"uint8 sdetable[SDETABLEITEMS];\n");
  strcat(wr_strval,"uint8 scos[SCOSITEMS];\n");
  strcat(wr_strval,"uint8 scos2[SCOS2ITEMS];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"int16 SlndE_Emin0;\n");
  strcat(wr_strval,"int16 SlndE_Emin1;\n");
  strcat(wr_strval,"float32 SlndE_MinClass;\n");
  strcat(wr_strval,"float32 SlndE_MaxClass;\n");
  strcat(wr_strval,"float32 SlndE_Eoffset0;\n");
  strcat(wr_strval,"float32 SlndE_Eoffset1;\n");
  strcat(wr_strval,"float32 SlndE_E00;\n");
  strcat(wr_strval,"float32 SlndE_E01;\n");
  strcat(wr_strval,"float32 SlndE_E1;\n");
  strcat(wr_strval,"float32 SlndE_Cosine;\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"int16 SlnE_Emin0;\n");
  strcat(wr_strval,"int16 SlnE_Emin1;\n");
  strcat(wr_strval,"float32 SlnE_MinClass;\n");
  strcat(wr_strval,"float32 SlnE_MaxClass;\n");
  strcat(wr_strval,"float32 SlnE_Eoffset0;\n");
  strcat(wr_strval,"float32 SlnE_Eoffset1;\n");
  strcat(wr_strval,"float32 SlnE_E00;\n");
  strcat(wr_strval,"float32 SlnE_E01;\n");
  strcat(wr_strval,"float32 SlnE_E1;\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"int16 SY_focal;\n");
  strcat(wr_strval,"float32 SY_Cosine;\n");
  strcat(wr_strval,"float32 SY_Y1;\n");
  strcat(wr_strval,"int16 SQ_MaxQ;\n");
  strcat(wr_strval,"float32 SQ_Q10;\n");
  strcat(wr_strval,"float32 SQ_Q11;\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"uint8 spseq[SPSEQITEMS];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  return(0);
}
