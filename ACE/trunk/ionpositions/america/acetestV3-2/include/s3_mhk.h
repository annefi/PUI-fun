/* $Id: s3_mhk.h,v 1.2 1997/05/06 19:11:02 jeff Exp $ */
#include  "hdfi.h"

        struct ssmhk {
             uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
             uint32  sctime_collection;      /*  32 bit  spacecraft  time  */
             uint32  QAC;         /*  number of missing frames in this SR */

             uint8 GRP282V;       /*  GND  +28V Sec.     */
             uint8 GRP9V;         /*  GND  +9V           */
             uint8 GRP5V;         /*  GND  +5V           */
             uint8 GRM5V;         /*  GND  -5V           */
             uint8 GRM12V;        /*  GND  -12V          */
             uint8 GR1T;          /*  GND  Thermistor 1  */
             uint8 GR2T;          /*  GND  Thermistor 2  */
             uint8 SPARE1;        /*  Spare              */
             uint8 GRP281I;       /*  GND  +28V Prim.    */
             uint8 GRP282I;       /*  GND  +28V Sec.     */
             uint8 GRP5I;         /*  GND  +5V  I        */
             uint8 SPARE2;        /*  Spare              */
             uint8 SPARE3;        /*  Spare              */
             uint8 SPARE4;        /*  Spare              */
            uint16 GRWAVEEQ;      /*  GND  Wave  E/q     */
            uint16 GRVF;          /*  GND  VF            */
             uint8 VFP28V;        /*  VF  +28V           */
             uint8 VFP9V;         /*  VF  +9V            */
             uint8 VFP6V;         /*  VF  +6V            */
             uint8 VFP5V;         /*  VF  +5V            */
             uint8 VFM5V;         /*  VF  -5V            */
             uint8 VFM12V;        /*  VF  -12V           */
             uint8 VF1T;          /*  VF  Thermistor 1   */
             uint8 VF2T;          /*  VF  Thermistor 2   */  
             uint8 VFP28I;        /*  VF  +28V I         */
             uint8 VFP6I;         /*  VF  +6V  I         */
             uint8 VFP5I;         /*  VF  +5V  I         */
             uint8 VFM5I;         /*  VF  -5V  I         */
             uint8 VFSTART;       /*  VF  Start MCP      */
             uint8 SPARE5;        /*  Spare              */
             uint8 VFSTOP;        /*  VF  Stop MCP       */
             uint8 VFHPS;         /*  VF  HVPS           */
             uint8 STATE;          /*  Digital Status     */
}; 
