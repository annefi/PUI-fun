/* $Id: s3_chk.h,v 1.2 1997/05/06 18:06:01 jeff Exp $ */
#include  "hdfi.h"

        struct csmhk {
             uint32  sctime_readout;     /* 32 bit spacecraft time  */
             uint32  sctime_collection;  /* 32 bit spacecraft time  */
             uint32  QAC;        /* number of missing frame in this SR*/

             uint8 GRP282V;       /*  GND  +28V Sec.     */
             uint8 GR20V;         /*  GND  20V  AC       */
             uint8 GRP10V;        /*  GND  +10V          */
             uint8 GRP5V;         /*  GND  +5V           */
             uint8 GRM5V;         /*  GND  -5V           */
             uint8 SPARE1;        /*  Spare              */
             uint8 GR1T;          /*  GND  Thermistor 1  */
             uint8 GR2T;          /*  GND  Thermister 2  */
             uint8 GRP281I;       /*  GND  +28V I Prim.  */
             uint8 GRP282I;       /*  GND  +28V I Sec.   */
             uint8 GRP5I;         /*  GND  +5V  I        */
             uint8 GR20I;         /*  GND  20V  AC I     */
             uint8 GRPAPS;        /*  GND  PAPS          */ 
             uint8 SPARE2;        /*  Spare              */
             uint8 GRDPPSL;       /*  GND  DPPS Low      */
             uint8 GRDPPSH;       /*  GND  DPPS High     */ 
             uint8 SPARE3;        /*  Spare              */
             uint8 PAC7;          /*  PAPS Synch C7      */
             uint8 PA1T;          /*  PAPS Thermistor 1  */
             uint8 PA2T;          /*  PAPS Thermistor 2  */
             uint8 PAP5V;         /*  PAPS +5V           */
             uint8 PAP5I;         /*  PAPS +5V I         */
             uint8 PAM5V;         /*  PAPS -5V           */
             uint8 PAM5I;         /*  PAPS -5V I         */
             uint8 PAMCP;         /*  PAPS MCP Bias      */
             uint8 FLAGS;         /*  Flags (DPPS Gain,..*/
}; 
