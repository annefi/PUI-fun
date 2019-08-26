/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_celement.h,v 1.3 1997/05/07 22:58:29 jeff Exp  */

#include "s3_celement.h"
#include "df.h"

int32 vgrp_id_s3_celement;
static int32 vdata_id_s3_celement;

  /* 740 is the size of s3_celement.h + 1 added line */
char Vgrp_descrp_celement[740];

/****----  init create function  ----****/

int32 init_cr_s3_celement(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_celement();

  void print_s3_celement_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_celement = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_celement_error("init_cr_s3_celement -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_celement, "VG_celement"); 
  Vsetclass(vgrp_id_s3_celement, "VG_S3_CELEMENT");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_celement" )) ==FAIL) {
    print_s3_celement_error("init_cr_s3_celement -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_celement(Vgrp_descrp_celement);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_celement_error("init_cr_s3_celement -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_celement, sizeof(Vgrp_descrp_celement))) ==FAIL) {
    print_s3_celement_error("init_cr_s3_celement -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_celement = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_celement_error("init_cr_s3_celement -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_celement, "celement");
  VSsetclass(vdata_id_s3_celement, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_celement, vdata_id_s3_celement)) ==FAIL) {
    print_s3_celement_error("init_cr_s3_celement -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_celement, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_celement_error("init_cr_s3_celement -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_celement, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_celement_error("init_cr_s3_celement -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_celement, "QAC", DFNT_UINT32, (1) )) {
    print_s3_celement_error("init_cr_s3_celement -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_celement, "ELEMENT", DFNT_UINT8, (CTIME_TSZ) )) {
    print_s3_celement_error("init_cr_s3_celement -> VSfdefine: Couldn't define ELEMENT");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_celement,"sctime_readout, sctime_collection, QAC, ELEMENT")){
    print_s3_celement_error("init_cr_s3_celement -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_celement(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_celement(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_celement(struct celement celement_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_celement_error();
void pack_s3_celement();

  odata = (uint8 *) malloc(sizeof(struct celement));
  pack_s3_celement(odata, &celement_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_celement, recnum)==-1) {
		print_s3_celement_error("write_s3_celement -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_celement, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_celement_error("write_s3_celement -> VSwrite: Couldn't write data.");

  memset(&celement_struc, 0, sizeof(struct celement));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_celement()
{
  VSdetach(vdata_id_s3_celement);
  Vdetach(vgrp_id_s3_celement);
}

/*----     init access function    ----*/

int32 init_acc_s3_celement(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_celement_error();


  if ((vdata_ref = VSfind(hdf_fp, "celement")) <= 0 ) {
    print_s3_celement_error("init_acc_s3_celement -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_celement = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_celement_error("init_acc_s3_celement -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_celement, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_celement,"sctime_readout, sctime_collection, QAC, ELEMENT")) {
      print_s3_celement_error("init_acc_s3_celement -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_celement(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_celement(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_celement(struct celement *celement_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_celement_error();
void unpack_s3_celement();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct celement));
  VSinquire(vdata_id_s3_celement, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_celement, recnum_rd)==FAIL) {
          print_s3_celement_error("read_s3_celement -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_celement, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_celement_error("read_s3_celement -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_celement(odata, celement_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_celement()
{
  VSdetach(vdata_id_s3_celement);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_celement(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_celement_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_celement" )) ==FAIL)
    print_s3_celement_error("rd_Vgrp_s3_celement -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_celement_error("rd_Vgrp_s3_celement -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_celement_error("rd_Vgrp_s3_celement -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_celement_error("rd_Vgrp_s3_celement -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_celement, HDstrlen(Vgrp_descrp_celement)) ==FAIL)
    print_s3_celement_error("rd_Vgrp_s3_celement -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_celement);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_celement_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swics_celement.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_celement(uint8 *data, struct celement *celement_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &celement_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &celement_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &celement_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &celement_ptr->ELEMENT[0], ((1)*(CTIME_TSZ)) );
   ptr+= ((1)*(CTIME_TSZ));
}

/*----   unpack function    ----*/

void unpack_s3_celement(uint8 *data, struct celement *celement_ptr)
{
int32 ptr=0;

   memcpy(&celement_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&celement_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&celement_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&celement_ptr->ELEMENT[0], data+ptr,  ((1)*(CTIME_TSZ)) );
   ptr+= ((1)*(CTIME_TSZ));
}
int32 get_vgrp_id_s3_celement() {return(vgrp_id_s3_celement);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_celement(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_celement.h' is shown below, it was used to create the data in the Vgroup named 'VG_celement'.\n\n");
  strcat(wr_strval,"/* Id: s3_celement.h,v 1.3 1997/05/07 22:58:29 jeff Exp $           */\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define  CTIME_CYC   1    /* number of cycle per SR=  60/60   */\n");
  strcat(wr_strval,"#define  CTIME_TSZ  120  /* total size in bytes  */\n");
  strcat(wr_strval,"#define  CTIME_CSZ  CTIME_TSZ/CTIME_CYC\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct celement  {\n");
  strcat(wr_strval,"           uint32  sctime_readout;   /*  readout : 32 bit S/C  time  */\n");
  strcat(wr_strval,"           uint32  sctime_collection;   /*  collection : 32 bit  S/C  time  */\n");
  strcat(wr_strval,"           uint32  QAC;         /* number of missing frams in this SR */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"           uint8  ELEMENT[CTIME_TSZ];     \n");
  strcat(wr_strval,"};\n");
  return(0);
}
