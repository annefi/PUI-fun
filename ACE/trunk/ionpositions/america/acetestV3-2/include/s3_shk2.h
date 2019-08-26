/* $Id: s3_shk2.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */
#include "hdfi.h"

struct sshshk2{
	uint32 sctime_readout;	/* first minor frame of readout cycle, */
	                        /* 32 bit spacecraft clock time */
	float64 sctime_collection; /* time of the start of the first spin in the */
	                           /* 5-spin cycle. sub-second resolution */

	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */

	uint8 HKSECTOR;	/* Housekeeping Sector    */
	uint8 FILL1;	/* Fill Time PC 1  */
	uint8 FILL2;	/* Fill Time PC 2  */
	uint8 FILL3;	/* Fill Time PC 3  */
	uint8 POWERS;	/* Power Status    */
	uint8 RELAYS;	/* Relay Status    */
	uint8 OVERI;	/* Over Currents    */
	uint8 P15LIM;	/* +15V Current Limit   */
	uint8 M15LIM;	/* -15V Current Limit   */
	uint8 P5LIM;	/* +5V Current Limit   */
	uint8 M5LIM;	/* -5V Current Limit   */
	uint8 _30KSTATH;	/* 30kV Discharge    */
	uint8 _30KSET;	/* 30kV Set Value   */
	uint8 _30KSTATL;	/* 30kV Plug Status   */
	uint8 _2KASTATH;	/* 2kV A Discharge   */
	uint8 _2KASET;	/* 2kV A Set Value  */
	uint8 _2KASTATL;	/* 2kV A Plug Status  */
	uint8 _2KBSTATH;	/* 2kV B Discharge   */
	uint8 _2KBSET;	/* 2kV B Set Value  */
	uint8 _2KBSTATL;	/* 2kV B Plug Status  */
	uint8 _2KCSTATH;	/* 2kV C Discharge   */
	uint8 _2KCSET;	/* 2kV C Set Value  */
	uint8 _2KCSTATL;	/* 2kV C Plug Status  */
	uint8 _75STATH;	/* 75V Discharge    */
	uint8 _75SET;	/* 75V Set Value   */
	uint8 _75STATL;	/* 75V Plug Status   */
	uint16 PC1P;	/* PC 1 Pres.   */
	uint16 PC2P;	/* PC 2 Pres.   */
	uint16 PC3P;	/* PC 3 Pres.   */
	uint16 LINEP;	/* line Pres.    */
	uint8 PC1O;	/* PC 1 On/Off   */
	uint8 PC2O;	/* PC 2 On/Off   */
	uint8 PC3O;	/* PC 3 On/Off   */
	uint8 ALARMS;	/* Alarm Flags    */
};
