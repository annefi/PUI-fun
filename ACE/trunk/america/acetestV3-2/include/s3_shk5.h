/* $Id: s3_shk5.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */
#include "hdfi.h"

struct sshshk5{
	uint32 sctime_readout;	/* first minor frame of readout cycle, */
	                        /* 32 bit spacecraft clock time */
	float64 sctime_collection; /* time of the start of the first spin in the */
	                           /* 5-spin cycle. sub-second resolution */

	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */

	uint8 HKSECTOR;	/* Housekeeping Sector    */

	uint8 ALARMOP3;	/* Overpressure Fan 3   */
	uint8 ALARMOP2;	/* Overpressure Fan 2   */
	uint8 ALARMOP1;	/* Overpressure Fan 1   */
	uint8 ALARMUP3;	/* Underpressure Fan 3   */
	uint8 ALARMUP2;	/* Underpressure Fan 2   */
	uint8 ALARMUP1;	/* Underpressure Fan 1   */
	uint8 ALARMDISCHG;	/* Discharge Alarm    */
	uint8 ALARM30KI;	/* 30kV I Alarm   */
	uint8 ALARM30KV;	/* 30kV Alarm    */
	uint8 ALARM2KVC;	/* 2kV C Alarm   */
	uint8 ALARM2KVB;	/* 2kV B Alarm   */
	uint8 ALARM2KVA;	/* 2kV A Alarm   */
	uint8 ALARM2KI;	/* 2kV I Alarm   */
	uint8 ALARM2KV;	/* 2kV Alarm    */
	uint8 ALARM75I;	/* 75V I Alarm   */
	uint8 ALARM75V;	/* 75V Alarm    */
	uint8 ALARMM15I;	/* -15V I Alarm   */
	uint8 ALARMM15V;	/* -15V Alarm    */
	uint8 ALARMP15I;	/* +15V I Alarm   */
	uint8 ALARMP15V;	/* +15V Alarm    */
	uint8 ALARMM5I;	/* -5V I Alarm   */
	uint8 ALARMM5V;	/* -5V Alarm    */
	uint8 ALARMP5I;	/* +5V I Alarm   */
	uint8 ALARMP5V;	/* +5V Alarm    */
};
