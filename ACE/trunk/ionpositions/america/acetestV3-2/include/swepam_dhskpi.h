/* $Id: swepam_dhskpi.h,v 1.1 1997/06/20 17:59:19 jeff Exp $ */
#include "hdfi.h"

struct DHSKPI               /* Swepam-I Housekeeping   */
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;              /* number of bad frames in this cycle */

  /* Major Frame Header */
  uint8  SCid[8];         /* SubCom ID */
  uint8  FmtFC[8];        /* Frame Format Count */
  uint8  FmtID[8];        /* Format ID */
  uint8  EF[8];           /* Event Flag */
  uint16 CS[8];           /* subcom Configuration Status */
  uint8  DB[8];           /* DataBase paramter */

  /* Subcom analog monitors - one complete cycle per 8 major frames in SCA normal mode. */
  uint8  HVMON1[8]; /* subcom analog high power supply monitor */
  uint8  HVMON2[8]; /* subcom analog high power supply monitor */
  uint8  PSMON[8];  /* subcom analog low power supply monitor */

  /* analog and telltale monitors - one sample per major frame */
  uint8  TMon[8];     /* Internal temp monitor */
  uint8  IMon[8];     /* 28v return Curr Mon */
  uint8  IFTMon[8];   /* Interface temp monitor */
  uint8  MainBusV[8];   /* Main bux voltage monitor */
};
