/* $Id: s3_mpha.h,v 1.2 1997/05/06 19:11:02 jeff Exp $           */
#include  "hdfi.h"

#define SWIMS_PHA_CYCLEN    99           
#define SWIMS_PHA_CYCPERSR  60      

struct mpha  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */
           uint32  QAC;         /*  number of missing frames in this SR */
           uint8   concat;      /*  is the number of mpha structs     */
           uint32  elements;    /*  number of pha events      */         

           uint8   range[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];
           uint8   sector[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];
           uint16  stamp[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];
           uint16  stopk1[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];
           uint16  stopk2[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];
           uint16  tof[SWIMS_PHA_CYCLEN][SWIMS_PHA_CYCPERSR];
     

};
