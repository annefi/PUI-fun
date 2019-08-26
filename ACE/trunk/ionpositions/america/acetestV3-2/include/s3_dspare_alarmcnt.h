/* $Id: s3_dspare_alarmcnt.h,v 1.3 1998/01/30 19:50:07 hemple Exp $ */

#include "hdfi.h"

struct s3s_dspare_alarmcnt {

uint32 sctime; /* 32bit spacecraft time */

/* SEPICA counters for alarm violations, from EDB 7 */

uint8 AlarmDelay_set_Cnt;	/* delay 10 min. */
uint8 AlarmDis_Cnt;		/* 30kV discharge check */
uint8 AlarmPres_Cnt;		/* pressure check */
uint8 AlarmLV_Cnt;		/* LV status bit check */
uint8 AlarmV1Open_set_Cnt;	/* valve 1 open */
uint8 AlarmV2Open_set_Cnt;	/* valve 2 open */
uint8 AlarmV3Open_set_Cnt;	/* valve 3 open */
uint8 AlarmPC1P_min_Cnt;	/* PC1 pressure */
uint8 AlarmPC1P_max_Cnt;	/* PC1 pressure */
uint8 AlarmPC2P_min_Cnt;	/* PC2 pressure */
uint8 AlarmPC2P_max_Cnt;	/* PC2 pressure */
uint8 AlarmPC3P_min_Cnt;	/* PC3 pressure */
uint8 AlarmPC3P_max_Cnt;	/* PC3 pressure */
uint8 AlarmP5V_min_Cnt;	        /* +5V */
uint8 AlarmP5V_max_Cnt;   	/* +5V */
uint8 AlarmP5I_min_Cnt;	        /* +5V (I) */
uint8 AlarmP5I_max_Cnt;	        /* +5V (I) */
uint8 AlarmM5V_min_Cnt;	        /* -5V */
uint8 AlarmM5V_max_Cnt;	        /* -5V */
uint8 AlarmM5I_min_Cnt;    	/* -5V (I) */
uint8 AlarmM5I_max_Cnt;	        /* -5V (I) */
uint8 AlarmP15V_min_Cnt;	/* +15V */
uint8 AlarmP15V_max_Cnt;	/* +15V */
uint8 AlarmP15I_min_Cnt;	/* +15V (I) */
uint8 AlarmP15I_max_Cnt;	/* +15V (I) */
uint8 AlarmM15V_min_Cnt;	/* -15V */
uint8 AlarmM15V_max_Cnt;	/* -15V */
uint8 AlarmM15I_min_Cnt;	/* -15V (I) */
uint8 AlarmM15I_max_Cnt;	/* -15V (I) */
uint8 Alarm75V_min_Cnt;		/* 75V */
uint8 Alarm75V_max_Cnt;		/* 75V */
uint8 Alarm75I_min_Cnt;		/* 75V (I) */
uint8 Alarm75I_max_Cnt;		/* 75V (I) */
uint8 Alarm2kV_min_Cnt;		/* 2kV */
uint8 Alarm2kV_max_Cnt;		/* 2kV */
uint8 Alarm2kI_min_Cnt;		/* 2kV (I) */
uint8 Alarm2kI_max_Cnt;		/* 2kV (I) */
uint8 Alarm2kAV_min_Cnt;	/* 2kV A */
uint8 Alarm2kAV_max_Cnt;	/* 2kV A */
uint8 Alarm2kBV_min_Cnt;	/* 2kV B */
uint8 Alarm2kBV_max_Cnt;	/* 2kV B */
uint8 Alarm2kCV_min_Cnt;	/* 2kV C */
uint8 Alarm2kCV_max_Cnt;	/* 2kV C */
uint8 Alarm30kV_min_Cnt;	/* 30kV */
uint8 Alarm30kV_max_Cnt;	/* 30kV */
uint8 Alarm30kI_min_Cnt;	/* 30kV (I) */
uint8 Alarm30kI_max_Cnt;	/* 30kV (I) */
uint8 AlarmDisV_min_Cnt;	/* 30kV discharge */
uint8 AlarmDisV_max_Cnt;	/* 30kV discharge */
uint8 AlarmDisI_min_Cnt;	/* 30kV discharge (I) */
uint8 AlarmDisI_max_Cnt;	/* 30kV discharge (I) */
};













