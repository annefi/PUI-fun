/* --------------------------------------------------------------- <Prolog> --
   Name:      expand.h
  -------------------------------------------------------------- </Prolog> -*/

/* $ProjectHeader$ */
/* $Id: expand.h,v 1.1.1.1 2000/06/02 13:37:21 jraines Exp $ */

#include "datatypes.h"

#ifndef EXPANDH
#define EXPANDH

typedef struct CPHA {
    int range;
    int sector;
    int ESSD;
    int TOF;
} CPHA;

typedef struct MPHA {
    int range;
    int sector;
    int amp;
    int k1;
    int k2;
    int tof;
} MPHA;

double ddpudbl      (int idx, BYTE abedb[NBINEDB], double dconv);
void   vxclassify   (SBCYC *pcyc);
int    expand       (BYTE abedb[NEDB][NBINEDB], double adtime[NEDB], 
		     BYTE abQAC[NEDB], SBCYC *cyc);
void   gedbpos      (BYTE abedb[NBINEDB],short aspos[NLOC][2]);
void   vxmascla     (BYTE abedb[NBINEDB], SBCYC *pcyc);
void   vxmoqcla     (BYTE abedb[NBINEDB], SBCYC *pcyc);
void   vxbrtab      (BYTE abedb[NBINEDB], SBCYC *pcyc);
void   vxmrtab      (BYTE abedb[NBINEDB], SBCYC *pcyc);
void   deccpha      (BYTE onepha[3], CPHA *stcpha);
void   decmpha      (BYTE onepha[6], MPHA *stmpha);
double convTmp      (BYTE bval);
double convTmp2     (BYTE bval);

#endif
