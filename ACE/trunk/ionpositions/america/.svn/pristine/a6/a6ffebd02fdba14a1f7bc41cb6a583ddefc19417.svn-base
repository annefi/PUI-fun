/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_dspare_cmd.h,v 1.3 1998/01/30 19:50:50 hemple Exp  */

#include "s3_dspare_cmd.h"
#include "df.h"

int32 vgrp_id_s3_dspare_cmd;
static int32 vdata_id_s3_dspare_cmd;

  /* 1151 is the size of s3_dspare_cmd.h + 1 added line */
char Vgrp_descrp_s3s_dspare_cmd[1151];

/****----  init create function  ----****/

int32 init_cr_s3_dspare_cmd(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_dspare_cmd();

  void print_s3_dspare_cmd_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_dspare_cmd = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_dspare_cmd, "VG_s3s_dspare_cmd"); 
  Vsetclass(vgrp_id_s3_dspare_cmd, "VG_S3_DSPARE_CMD");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_s3s_dspare_cmd" )) ==FAIL) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_dspare_cmd(Vgrp_descrp_s3s_dspare_cmd);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_s3s_dspare_cmd, sizeof(Vgrp_descrp_s3s_dspare_cmd))) ==FAIL) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_dspare_cmd = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_dspare_cmd, "s3s_dspare_cmd");
  VSsetclass(vdata_id_s3_dspare_cmd, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_dspare_cmd, vdata_id_s3_dspare_cmd)) ==FAIL) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_dspare_cmd, "sctime", DFNT_UINT32, (1) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "SCommand1", DFNT_INT16, (SCOMMANDITEMS) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define SCommand1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "SCommand2", DFNT_INT16, (SCOMMANDITEMS) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define SCommand2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "SCommand3", DFNT_INT16, (SCOMMANDITEMS) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define SCommand3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "Pressure_set_1", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define Pressure_set_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "Pressure_set_2", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define Pressure_set_2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "Pressure_set_3", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define Pressure_set_3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "HvEnable", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define HvEnable");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "BITChannel_1", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define BITChannel_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "BITChannel_2", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define BITChannel_2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "BITChannel_3", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define BITChannel_3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "DAC0Channel_1", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define DAC0Channel_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "DAC0Channel_2", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define DAC0Channel_2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "DAC0Channel_3", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define DAC0Channel_3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "DAC1Channel_1", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define DAC1Channel_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_cmd, "DAC1Channel_2", DFNT_INT16, (3) )) {
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSfdefine: Couldn't define DAC1Channel_2");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_dspare_cmd,"sctime, SCommand1, SCommand2, SCommand3, Pressure_set_1, Pressure_set_2, Pressure_set_3, HvEnable, BITChannel_1, BITChannel_2, BITChannel_3, DAC0Channel_1, DAC0Channel_2, DAC0Channel_3, DAC1Channel_1, DAC1Channel_2")){
    print_s3_dspare_cmd_error("init_cr_s3_dspare_cmd -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_dspare_cmd(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_dspare_cmd(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_dspare_cmd(struct s3s_dspare_cmd s3s_dspare_cmd_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_dspare_cmd_error();
void pack_s3_dspare_cmd();

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_cmd));
  pack_s3_dspare_cmd(odata, &s3s_dspare_cmd_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_dspare_cmd, recnum)==-1) {
		print_s3_dspare_cmd_error("write_s3_dspare_cmd -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_dspare_cmd, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_dspare_cmd_error("write_s3_dspare_cmd -> VSwrite: Couldn't write data.");

  memset(&s3s_dspare_cmd_struc, 0, sizeof(struct s3s_dspare_cmd));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_dspare_cmd()
{
  VSdetach(vdata_id_s3_dspare_cmd);
  Vdetach(vgrp_id_s3_dspare_cmd);
}

/*----     init access function    ----*/

int32 init_acc_s3_dspare_cmd(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_dspare_cmd_error();


  if ((vdata_ref = VSfind(hdf_fp, "s3s_dspare_cmd")) <= 0 ) {
    print_s3_dspare_cmd_error("init_acc_s3_dspare_cmd -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_dspare_cmd = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_dspare_cmd_error("init_acc_s3_dspare_cmd -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_dspare_cmd, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_dspare_cmd,"sctime, SCommand1, SCommand2, SCommand3, Pressure_set_1, Pressure_set_2, Pressure_set_3, HvEnable, BITChannel_1, BITChannel_2, BITChannel_3, DAC0Channel_1, DAC0Channel_2, DAC0Channel_3, DAC1Channel_1, DAC1Channel_2")) {
      print_s3_dspare_cmd_error("init_acc_s3_dspare_cmd -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_dspare_cmd(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_dspare_cmd(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_dspare_cmd(struct s3s_dspare_cmd *s3s_dspare_cmd_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_dspare_cmd_error();
void unpack_s3_dspare_cmd();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_cmd));
  VSinquire(vdata_id_s3_dspare_cmd, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_dspare_cmd, recnum_rd)==FAIL) {
          print_s3_dspare_cmd_error("read_s3_dspare_cmd -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_dspare_cmd, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_dspare_cmd_error("read_s3_dspare_cmd -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_dspare_cmd(odata, s3s_dspare_cmd_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_dspare_cmd()
{
  VSdetach(vdata_id_s3_dspare_cmd);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_dspare_cmd(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_dspare_cmd_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_s3s_dspare_cmd" )) ==FAIL)
    print_s3_dspare_cmd_error("rd_Vgrp_s3_dspare_cmd -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_dspare_cmd_error("rd_Vgrp_s3_dspare_cmd -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_dspare_cmd_error("rd_Vgrp_s3_dspare_cmd -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_dspare_cmd_error("rd_Vgrp_s3_dspare_cmd -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_s3s_dspare_cmd, HDstrlen(Vgrp_descrp_s3s_dspare_cmd)) ==FAIL)
    print_s3_dspare_cmd_error("rd_Vgrp_s3_dspare_cmd -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_s3s_dspare_cmd);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_dspare_cmd_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3dspare_cmd.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_dspare_cmd(uint8 *data, struct s3s_dspare_cmd *s3s_dspare_cmd_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &s3s_dspare_cmd_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->SCommand1[0], ((2)*(SCOMMANDITEMS)) );
   ptr+= ((2)*(SCOMMANDITEMS));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->SCommand2[0], ((2)*(SCOMMANDITEMS)) );
   ptr+= ((2)*(SCOMMANDITEMS));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->SCommand3[0], ((2)*(SCOMMANDITEMS)) );
   ptr+= ((2)*(SCOMMANDITEMS));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->Pressure_set_1[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->Pressure_set_2[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->Pressure_set_3[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->HvEnable[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->BITChannel_1[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->BITChannel_2[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->BITChannel_3[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->DAC0Channel_1[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->DAC0Channel_2[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->DAC0Channel_3[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->DAC1Channel_1[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_cmd_ptr->DAC1Channel_2[0], ((2)*(3)) );
   ptr+= ((2)*(3));
}

/*----   unpack function    ----*/

void unpack_s3_dspare_cmd(uint8 *data, struct s3s_dspare_cmd *s3s_dspare_cmd_ptr)
{
int32 ptr=0;

   memcpy(&s3s_dspare_cmd_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_cmd_ptr->SCommand1[0], data+ptr,  ((2)*(SCOMMANDITEMS)) );
   ptr+= ((2)*(SCOMMANDITEMS));
   memcpy(&s3s_dspare_cmd_ptr->SCommand2[0], data+ptr,  ((2)*(SCOMMANDITEMS)) );
   ptr+= ((2)*(SCOMMANDITEMS));
   memcpy(&s3s_dspare_cmd_ptr->SCommand3[0], data+ptr,  ((2)*(SCOMMANDITEMS)) );
   ptr+= ((2)*(SCOMMANDITEMS));
   memcpy(&s3s_dspare_cmd_ptr->Pressure_set_1[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->Pressure_set_2[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->Pressure_set_3[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->HvEnable[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->BITChannel_1[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->BITChannel_2[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->BITChannel_3[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->DAC0Channel_1[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->DAC0Channel_2[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->DAC0Channel_3[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->DAC1Channel_1[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_cmd_ptr->DAC1Channel_2[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
}
int32 get_vgrp_id_s3_dspare_cmd() {return(vgrp_id_s3_dspare_cmd);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_dspare_cmd(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_dspare_cmd.h' is shown below, it was used to create the data in the Vgroup named 'VG_s3s_dspare_cmd'.\n\n");
  strcat(wr_strval,"/* Id: s3_dspare_cmd.h,v 1.3 1998/01/30 19:50:50 hemple Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SCOMMANDITEMS 55\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct s3s_dspare_cmd {\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"uint32 sctime; /* 32bit spacecraft time */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* SEPICA Command parameters, from EDB's 0,20,40 */\n");
  strcat(wr_strval,"int16 SCommand1[SCOMMANDITEMS];\n");
  strcat(wr_strval,"int16 SCommand2[SCOMMANDITEMS];\n");
  strcat(wr_strval,"int16 SCommand3[SCOMMANDITEMS];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* some unique SEPICA command parameters pulled from the above arrays */\n");
  strcat(wr_strval,"int16 Pressure_set_1[3];    /* pressure */\n");
  strcat(wr_strval,"int16 Pressure_set_2[3];    /* pressure */\n");
  strcat(wr_strval,"int16 Pressure_set_3[3];    /* pressure */\n");
  strcat(wr_strval,"int16 HvEnable[3];	    /* HV enables */\n");
  strcat(wr_strval,"int16 BITChannel_1[3];	    /* BIT channel */\n");
  strcat(wr_strval,"int16 BITChannel_2[3];	    /* BIT channel */\n");
  strcat(wr_strval,"int16 BITChannel_3[3];	    /* BIT channel */\n");
  strcat(wr_strval,"int16 DAC0Channel_1[3];     /* DAC 0 channel */\n");
  strcat(wr_strval,"int16 DAC0Channel_2[3];     /* DAC 0 channel */\n");
  strcat(wr_strval,"int16 DAC0Channel_3[3];     /* DAC 0 channel */\n");
  strcat(wr_strval,"int16 DAC1Channel_1[3];     /* DAC 1 channel */\n");
  strcat(wr_strval,"int16 DAC1Channel_2[3];     /* DAC 1 channel */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
