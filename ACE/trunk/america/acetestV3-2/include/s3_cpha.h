/* $Id: s3_cpha.h,v 1.2 1997/05/06 19:09:53 jeff Exp $           */
#include  "hdfi.h"

#define SWICS_PHA_CYCLEN    194           
#define SWICS_PHA_CYCPERSR  60      

struct cpha  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */
           uint32  QAC;         /* number of missing frames in this SR*/
           uint8   concat;      /*  is the number of mpha structs     */
           uint32  elements;    /*  number of pha events      */         

           uint8   range[SWICS_PHA_CYCLEN][SWICS_PHA_CYCPERSR];
           uint8   sector[SWICS_PHA_CYCLEN][SWICS_PHA_CYCPERSR];
           uint16  energy[SWICS_PHA_CYCLEN][SWICS_PHA_CYCPERSR];
           uint16  time[SWICS_PHA_CYCLEN][SWICS_PHA_CYCPERSR];
     

};
