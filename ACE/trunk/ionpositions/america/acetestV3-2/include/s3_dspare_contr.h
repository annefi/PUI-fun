/* $Id: s3_dspare_contr.h,v 1.3 1998/01/30 19:51:03 hemple Exp $ */

#include "hdfi.h"

struct s3s_dspare_contr{

uint32 sctime;             /* 32bit spacecraft time */

/* SEPICA control words, from EDB's 3,23,43 */
int16 Mode[3];		   /* mode */
int16 Delay[3];		   /* power off delay */
int16 Lim30k[3];	   /* 30 kV limit/delta */
int16 Lim30k_delta[3];
int16 Lim2k[3];		   /* 2 kV limit/delta */
int16 Lim2k_delta[3];
int16 Lim75[3];		   /* 75 V limit/delta */
int16 Lim75_delta[3];
int16 PhaThres_low[3];	   /* PHA threshold */
int16 PhaThres_hi[3];		
int16 PressCtrl_1[3];	   /* pressure control */
int16 PressCtrl_2[3];
int16 PressCmd_1[3];	   /* pressures */
int16 PressCmd_2[3];
int16 PressCmd_3[3];

int16 Mode_Cmd[3];
int16 Delay_Cmd[3];
int16 Lim30k_Cmd[3];
int16 Lim30k_delta_Cmd[3];
int16 Lim2k_Cmd[3];
int16 Lim2k_delta_Cmd[3];
int16 Lim75_Cmd[3];
int16 Lim75_delta_Cmd[3];
int16 PhaThres_low_Cmd[3];
int16 PhaThres_hi_Cmd[3];
int16 PressCtrl_1_Cmd[3];
int16 PressCtrl_2_Cmd[3];
int16 PressCmd_1_Cmd[3];
int16 PressCmd_2_Cmd[3];
int16 PressCmd_3_Cmd[3];
};






