/* $Id: L1_1SisEvent.h,v 1.1 2000/11/03 04:02:55 rgr Exp $ */

/* $RCSfile: L1_1SisEvent.h,v $ */
/* $Author: rgr $ */
/* $Date: 2000/11/03 04:02:55 $ */
/* $Revision: 1.1 $ */
/* $State: Exp $ */
/* $Locker:  $ */


#ifndef L1_1_SIS_EVENT_H

   #define L1_1_SIS_EVENT_H
   #include "SisConstants.h"

   #define  NMDS   NUM_SIS_MATRIX_STRIPS
   #define  NSSD   NUM_SIS_STACK_DETECTORS
   
   struct SisFlag
   {
      u_char stimulated;          /* Stimulated event flag               */
      u_char maybe;               /* Maybe flag                          */
      u_char hazard;              /* Hazard flag                         */
      u_char PeakTime;            /* Transmission flag for relative      */
                                  /* times to peak                       */
   };
   
   struct SisStimulated
   {
      u_short stmask;
      u_short CalSequence;
      u_char  gain_f1;
      u_char  gain_f2;
      u_char  vref;
      u_char  vref1;
      u_char  vref2;
      u_char  MatrixGndSide;
      u_char  AMatrixHvSide;
      u_char  BMatrixHvSide;
   };
      
    struct L1_1SisEvent
   {
      u_long  EventNumber;        /* Event number                        */
      u_long  Second1996;         /* Seconds of 1996                     */
      u_long  microsecond;        /* Microsecond                         */
   
      struct SisFlag flag;               /* Flags for the SIS event      */
      struct SisStimulated stimulated;   /* Stimulated event parameters  */
   
      short   M1GndPha[NMDS];     /* M1 grounded side strip pulse hgts   */
      short   M1FloatPha[NMDS];   /* M1 floating side strip pulse hgts   */
      short   M2GndPha[NMDS];     /* M2 grounded side strip pulse hgts   */
      short   M2FloatPha[NMDS];   /* M2 floating side strip pulse hgts   */
      short   StackA[NSSD];       /* Stack A detector pulse heights      */
      short   StackB[NSSD];       /* Stack B detector pulse heights      */
      u_char  RangeA;             /* Range of event in detector A        */
      u_char  RangeB;             /* Range of event in detector B        */
      u_char  StackAStatus;       /* 0=Not Hit, 1=Primary, 2=Sec. Hit    */
      u_char  StackBStatus;       /* 0=Not Hit, 1=Primary, 2=Sec. Hit    */
      u_char  NumberMatrixStrips; /* Number of matrix strips transmitted */
      u_char  OtherMatrixGroups;  /* Encoded pattern for of the matrix   */
                                  /* groups not transmitted              */
      u_char  TimeTag;            /* Event time tag in units of 256 sec  */
      u_char  phase;              /* Event phase information             */
      u_char  PeakTimeM1;         /* M1 peak time (0.25 musec.)          */
      u_char  PeakTimeM2;         /* M2 peak time (0.25 musec.)          */
      u_char  PeakTimeT1;         /* T1 peak time (0.25 musec.)          */
      char    M1GndSideOffset;    /* M1 ground side offset               */
      char    M1HvSideOffset;     /* M1 high voltage offset              */
      char    M2GndSideOffset;    /* M2 ground side offset               */
      char    M2HvSideOffset;     /* M2 high voltage offset              */
      u_char  BufferId;           /* Event buffer identification         */
      u_char  EventOffset;        /* Offset of event from minor frame    */
      u_char  NumberBytes;        /* Number of bytes in compressed event */
   };
   
   #undef NMDS
   #undef NSSD

#endif
