/* $Id: schskp.h,v 1.10 1997/08/01 17:11:35 jeff Exp $ */
#include "hdfi.h"
/*--------------------------------------------------------------------*/


/* for Science format, 20 bytes per minor frame for 16 minor frames */
/*   Selectable telemetry byte and Phase angle values ,             */
/*   Format ID byte and Colletion format byte from every */
/*   minor frame will also be accumulated                           */
/* Total for science Format, 320 bytes + 16 bytes + 32 bytes        */
/*   +16 bytes +16 bytes = 400  */

/* for ADC format, 320 bytes + 51 "extra" bytes + 2 byte Sun Pulse  */
/*   phase angle + 22 bytes Sun Sensor data + 17 bytes spare +      */
/*   16 bytes Selectable telemetry byte + 32 bytes Phase angle      */
/*   +16 Format ID +16 Colletion format */
/* Total for ADC Format, 320 + 51 + 2 + 22 + 17 + 16 + 32 = 492 bytes */

/* in ADC mode */
/* Only the first Selectable telemtry byte, and the first Phase angle */
/* will be reported, the rest 15 Selectable telemtry bytes and Phase */
/* angle values will be zeroed                                       */
/* Same for Format ID and Colletion format bytes */

/* The values LastSPTT8, SunPulPhaAng{0/8}, will be zeroed for ADC format */
/* LastSPTT0 will be the sun pulse time tag value in ADC format */

/* Both formats will have the value of the S/C clock reported as well. */

struct SCHskpData
{
  uint32  sc_clk;

  /*--- following 20 bytes hskp items appear in mn_frm 0 in sci_fmt ---*/
  uint8 TankA1Temp;       /* Propellant Tank A1 Temperature */
  uint8 TankA2Temp;       /* Propellant Tank A2 Temperature */
  uint8 TankB1Temp;       /* Propellant Tank B1 Temperature */
  uint8 TankB2Temp;       /* Propellant Tank B2 Temperature */
  uint8 LinesATemp;       /* Internal Lines A Temperature   */
  uint8 LinesBTemp;       /* Internal Lines B Temperature   */
  uint8 LinesPosXTemp;    /* External Lines +X Temperature  */
  uint8 LinesNegXTemp;    /* External Lines -X Temperature  */
  uint8 StarTrkTemp;      /* Star Tracker Temperature       */
  uint8 InstDeckTemp1;    /* Instrument Deck Temperature #1 */
  uint8 InstDeckTemp2;    /* Instrument Deck Temperature #2 */
  uint8 InstDeckTemp3;    /* Instrument Deck Temperature #3 */
  uint8 InstDeckTemp4;    /* Instrument Deck Temperature #4 */
  uint8 InstDeckTemp5;    /* Instrument Deck Temperature #5 */
  uint8 InstDeckTemp6;    /* Instrument Deck Temperature #6 */
  uint8 InstDeckTemp7;    /* Instrument Deck Temperature #7 */
  uint8 InstDeckTemp8;    /* Instrument Deck Temperature #8 */
  uint8 LastSPTT0[3];     /* 24 bits, Last SP TT=4 Mnr Frm, ... */

  /*--- following 20 bytes hskp items appear in mn_frm 1 in sci_fmt ---*/
  uint8 ScIFHeaterCur;    /* Spacecraft Specific I/F Heater Current */
  uint8 SunSnsrTemp;      /* Sun Sensor (-X/-Y Side) Temperature */
  uint8 PosXSAPTemp;      /* +X Solar Array Panel Temperature */
  uint8 PosXSAPHTemp;     /* +X Solar Array Panel Hinge Temperature */
  uint8 NegXSAPTemp;      /* -X Solar Array Panel Temperature */
  uint8 NegXSAPHTemp;     /* -X Solar Array Panel Hinge Temperature */
  uint8 MagInTemp;        /* Magnetometer Inboard Temperature */
  uint8 MagOutTemp;       /* Magnetometer Outboard Temperature */
  uint8 MagInHtrPwrLvl;   /* Mag Inboard Heater Power Level */
  uint8 MagOutHtrPwrLvl;  /* Mag Outboard Heater Power Level */
  uint8 S3DPUPwrCvtVolt;  /* S3 DPU Power Conveter Voltage */
  uint8 PwrSubProACur;    /* Power Subsystem Processor A Current */
  uint8 PwrSubProBCur;    /* Power Subsystem Processor B Current */
  uint8 AxialThrstCur;    /* Axial Thruster Current */
  uint8 Channel25;        /* 0-50mV Channel #25 */
  uint8 Channel26;        /* 0-50mV Channel #26 */
  uint8 Channel20;        /* 0-5V Channel #20 */
  uint8 Channel30;        /* AD590 Channel #30 */
  uint8 DigTellLog0;      /* Digital Telltale logic byte 0 */
  uint8 DigTellLog1;      /* Digital Telltale logic byte 1 */

  /* --- next 20 bytes from min frame 2 -- */
  uint8 data_2_1[16];		    /* first 16 bytes of min frm 2 hskp */
  uint8 MagSenIntTempPosY;        /* Mag +Y Sensor interface temp */
  uint8 MagSenIntTempNegY;        /* Mag -Y Sensor interface temp */
  uint8 data_2_2[2];		    /* last 2 bytes of min frm 2 hskp */
  /* --- next 20 bytes from min frame 3 -- */
  uint8 data_3_1[10];		    /* 10 bytes of min frm 3 hskp */
  uint8 MainBusCur;                 /* Main bus curent */
  uint8 MainBusVolt;                /* Main bus voltage */
  uint8 data_3_2[8];		    /* last 8 bytes of min frm 3 hskp */
  /* --- next 20 bytes from min frame 4 -- */
  uint8 data_4_1[20];		    /* 20 bytes of min frm 4 hskp */
  /* --- next 20 bytes from min frame 5 -- */
  uint8 data_5_1[20];		    /* 20 bytes of min frm 5 hskp */
  /* --- next 20 bytes from min frame 6 -- */
  uint8 data_6_1[20];		    /* 20 bytes of min frm 6 hskp */
  /* --- next 20 bytes from min frame 7 -- */
  uint8 data_7_1[20];		    /* 20 bytes of min frm 7 hskp */
  /* --- next 20 bytes from min frame 8 -- */
  uint8 data_8_1[17];		    /* 17 bytes of min frm 8 hskp */
  uint8 LastSPTT8[3];              /* 24 bits, Last SP TT=4 Mnr Frm, ... */
  /* --- next 20 bytes from min frame 9 -- */
  uint8 SwepamE_8VPSMon;  /* SWEPAME +8 V Power Supply monitor */
  uint8 SwepamE_HVMon1;   /* SWEPAME HVMON1-subcommed over 8 mj frames */
  uint8 SwepamE_HVMon2;   /* SWEPAME HVMON2-subcommed over 8 mj frames */
  uint8 SwepamI_8VPSMon;  /* SWEPAMI +8 V Power Supply monitor */
  uint8 SwepamI_HVMon1;   /* SWEPAMI HVMON1-subcommed over 8 mj frames */
  uint8 SwepamI_HVMon2;   /* SWEPAMI HVMON2-subcommed over 8 mj frames */
  uint8 Epam_A1;          /* EPAM Analog A1, Int/Ext Cal Readout */
  uint8 Epam_A2;          /* EPAM Analog A2, subcommed over 8 mj frames */
  uint8 Epam_A3;          /* EPAM Analog A3, subcommed over 8 mj frames */
  uint8 Epam_A4;          /* EPAM Analog A4, Input Current Monitor */
  uint8 Epam_LAN1;        /* EPAM LAN 1, Electronics temp thermistor */
  uint8 Epam_LAN2A;       /* EPAM LAN 2A, Electronics temp thermistor */
  uint8 Epam_LAN2B;       /* EPAM LAN 2A, Sensor temp thermistor */
  uint8 Uleis_LVPSVolt;   /* ULEIS LVPS Voltage */
  uint8 Cris_IntTemp1;    /* CRIS Internal Temp #1 */
  uint8 Cris_IntTemp2;    /* CRIS Internal Temp #2 */
  uint8 Sis_IntTemp1;     /* SIS Internal Temp #1 */
  uint8 Sis_IntTemp2;     /* SIS Internal Temp #2 */
  uint16 SunPulPhaAng0;  /* Phase angle latched with Sun Pulse in mn frm 0 */
  /* --- next 20 bytes from min frame 10 -- */
  uint8 data_10_1[2];
  uint8 data_10_2;     

  /*  unsigned DigTelSwiCha15:1; Digital telltale switch #15 */
  /*  unsigned Sis_CovTell:1;    SIS Cover Telltale */
  /*  unsigned S3DPU_PowConSelTell:1;  S3DPU power converter select TT */
  /*  unsigned Swims_CovTell:1;  SWIMS cover Tell Tale */
  /*  unsigned data_10_2:4; */
  uint8 Cris_Cur;          /* CRIS current including detector bias */
  uint8 Sis_Cur;           /* SIS current including detector bias */
  uint8 Epam_Cur;          /* EPAM current */
  uint8 Epam_HtrCur;       /* EPAM heater current */
  uint8 Uleis_Cur;       /* ULEIS current */
  uint8 Uleis_AnaEleLVPSCur;  /* ULEIS current, Analog Electronics LVPS  */
  uint8 DCM1_Chan21;      /* DCM1 0-50mV channel 21 */
  uint8 Uleis_HtrCur;      /* ULEIS Heater current */
  uint8 SwepamE_Cur;      /* SWEPAM electron current */
  uint8 SwepamI_Cur;      /* SWEPAM ion current */
  uint8 Swims_Cur;      /* SWIMS current */
  uint8 Swics_Cur;      /* SWICS current */
  uint8 Sepica_Cur;      /* SEPICA current */
  uint8 Mag_Cur;      /* MAG current (DPU A, DPU B, Heater) */
  uint8 S3DPU_Cur;      /* S3DPU current  */
  uint8 data_10_3[2];
  /* --- next 20 bytes from min frame 11 -- */
  uint8 PowSwiOrdBit[14];  /* Power switching and ordinance bits - may */
			  /* decide to do all 112 items individually later */
      /* unsigned S3DPU_IntABSel:1;  S^3 DPU Interface A/B Select */
      /* data:7 */
  uint8 data_11_1[4];
  uint8 S3DPU_ConSecCur;  /* S3DPU Converter Secondary Current */
  uint8 PreTraCur;       /* Pressure Transducer Current */
  /* --- next 20 bytes from min frame 12 -- */
  uint8 Swims_IntTemp;   /* SWIMS Internal Temp */
  uint8 Swics_IntTemp;   /* SWICS Internal Temp */
  uint8 Uleis_TelTemp;   /* ULEIS Telescope Temp */
  uint8 Uleis_AnaEleTemp;   /* ULEIS Analog Electronics Temp */
  uint8 Uleis_DPUTemp;   /* ULEIS DPU Temp */
  uint8 Sepica_IsoTanTemp;   /* SEPICA Isobutane Tank temp */
  uint8 S3DPU_PowSupATemp;   /* S^3 DPU Power supply A temp */
  uint8 SwepamE_IntTemp;   /* SWEPAM Electron Internal Temp */
  uint8 SwepamI_IntTemp;   /* SWEPAM Ion Internal Temp */
  uint8 StarScan[8];      /* Star Scanner data */
  uint8 TermBoardFuse1Temp;  
  uint8 data_12_1;
  uint8 S3DPU_PowSupBTemp;   /* S^3 DPU Power supply B temp */
  /* --- next 48 bytes from min frame 13 14 & 15-- */
  uint8 CDH_HKdat[48];
  /* --- next 12 bytes from min frame 15-- */
  uint8 data_15_1[10];
  uint16 SunPulPhaAng8;  /* Phase angle latched with Sun Pulse in mn frm 8 */

  /* these total 80 bytes are Selectable Telemtry Byte, Format ID, */
  /* Collection format and Science format phase angle data. */
  /* ADC format will have only the first values, others are zeroed */
  uint8  SelTelByt[16];   /* Selectable Telemtry Byte */
  uint16 SCIPhaAng[16];   /* Science Format phase angle data */
  uint8  FormatID[16];    /* FormatID:4, SunSenTop:1,SunSenSide:1,C&DH ID:2*/
  uint8  CollForm[16];    /* CollFormat:1, mjfrm:3,mnfrm:4 */

  /* Found in ADC format only */
  uint16 ADCPhaAng;  /* ADC format phase angle value */
  uint16 SunSensor[11];  /* 11 sun sensor values */
  uint8 ADCXtrDat[51];   /* 51 bytes of data found only in ADC format */
  uint8 spare[17];       /* 17 bytes of unallocated data in ADC format */

};
