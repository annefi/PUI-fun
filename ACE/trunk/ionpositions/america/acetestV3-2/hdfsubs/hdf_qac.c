/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: qac.h,v 1.1 1997/09/05 22:34:03 jeff Exp  */

#include "qac.h"
#include "df.h"

int32 vgrp_id_qac;
static int32 vdata_id_qac;

  /* 413 is the size of qac.h + 1 added line */
char Vgrp_descrp_QACarr[413];

/****----  init create function  ----****/

int32 init_cr_qac(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_qac();

  void print_qac_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_qac = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_qac_error("init_cr_qac -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_qac, "VG_QACarr"); 
  Vsetclass(vgrp_id_qac, "VG_QAC");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_QACarr" )) ==FAIL) {
    print_qac_error("init_cr_qac -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_qac(Vgrp_descrp_QACarr);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_qac_error("init_cr_qac -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_QACarr, sizeof(Vgrp_descrp_QACarr))) ==FAIL) {
    print_qac_error("init_cr_qac -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_qac = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_qac_error("init_cr_qac -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_qac, "QACarr");
  VSsetclass(vdata_id_qac, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_qac, vdata_id_qac)) ==FAIL) {
    print_qac_error("init_cr_qac -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_qac, "sctime", DFNT_UINT32, (1) )) {
    print_qac_error("init_cr_qac -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_qac, "val", DFNT_INT8, (128) )) {
    print_qac_error("init_cr_qac -> VSfdefine: Couldn't define val");
    retval = -1;
  }

  if (VSsetfields(vdata_id_qac,"sctime, val")){
    print_qac_error("init_cr_qac -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_qac(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_qac(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_qac(struct QACarr QACarr_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_qac_error();
void pack_qac();

  odata = (uint8 *) malloc(sizeof(struct QACarr));
  pack_qac(odata, &QACarr_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_qac, recnum)==-1) {
		print_qac_error("write_qac -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_qac, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_qac_error("write_qac -> VSwrite: Couldn't write data.");

  memset(&QACarr_struc, 0, sizeof(struct QACarr));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_qac()
{
  VSdetach(vdata_id_qac);
  Vdetach(vgrp_id_qac);
}

/*----     init access function    ----*/

int32 init_acc_qac(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_qac_error();


  if ((vdata_ref = VSfind(hdf_fp, "QACarr")) <= 0 ) {
    print_qac_error("init_acc_qac -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_qac = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_qac_error("init_acc_qac -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_qac, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_qac,"sctime, val")) {
      print_qac_error("init_acc_qac -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_qac(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_qac(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_qac(struct QACarr *QACarr_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_qac_error();
void unpack_qac();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct QACarr));
  VSinquire(vdata_id_qac, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_qac, recnum_rd)==FAIL) {
          print_qac_error("read_qac -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_qac, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_qac_error("read_qac -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_qac(odata, QACarr_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_qac()
{
  VSdetach(vdata_id_qac);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_qac(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_qac_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_QACarr" )) ==FAIL)
    print_qac_error("rd_Vgrp_qac -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_qac_error("rd_Vgrp_qac -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_qac_error("rd_Vgrp_qac -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_qac_error("rd_Vgrp_qac -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_QACarr, HDstrlen(Vgrp_descrp_QACarr)) ==FAIL)
    print_qac_error("rd_Vgrp_qac -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_QACarr);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_qac_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_qac.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_qac(uint8 *data, struct QACarr *QACarr_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &QACarr_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &QACarr_ptr->val[0], ((1)*(128)) );
   ptr+= ((1)*(128));
}

/*----   unpack function    ----*/

void unpack_qac(uint8 *data, struct QACarr *QACarr_ptr)
{
int32 ptr=0;

   memcpy(&QACarr_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&QACarr_ptr->val[0], data+ptr,  ((1)*(128)) );
   ptr+= ((1)*(128));
}
int32 get_vgrp_id_qac() {return(vgrp_id_qac);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_qac(char *wr_strval)
{
  strcpy(wr_strval, "The file 'qac.h' is shown below, it was used to create the data in the Vgroup named 'VG_QACarr'.\n\n");
  strcat(wr_strval,"/* Id: qac.h,v 1.1 1997/09/05 22:34:03 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct QACarr {\n");
  strcat(wr_strval,"    uint32 sctime;   /* sctime at beginning of array */\n");
  strcat(wr_strval,"    int8   val[128]; /* array of QAC values.  0=OK, 1=missing */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
