/* --------------------------------------------------------------- <Prolog> --
   Name:      swxdpusim.h
   Title:     ACE/SWICS DPU simulator 
   $Id: asxdpusim.h,v 1.1.1.1 2000/06/02 13:37:21 jraines Exp $
   ------------------------------------------------------------- </Prolog> -*/

#include "decoded.h"

#ifndef SWXDPUSIMH
#define SWXDPUSIMH

#define S3DPULNQ 34.59577
#define S3DPULNM 25.50089

/* --- DPU software hard-coded values --- */

#define MUNDER     0                /* Output this code if M is too small   */
#define MOVER    123                /* Output this code if M is too big     */
#define EUNDER   124                /* Output this code if E is too small   */
#define EOVER    125                /* Output this code if E is too big     */


#define MQUNDER    0                /* Output this code if M/Q is too small */
#define MQOVER   125                /* Output this code if M/Q is too big   */
#define TOFUNDER 126                /* Output this code if TOF is too small */
#define TOFOVER  127                /* Output this code if TOF is too big   */

#define S3XNMMAX  122.0             /* min/max channel used */
#define S3XNMMIN    1.0
#define S3XM_MAX  115.0             /* min/max mass classified */
#define S3XM_MIN    1.0

#define S3XNQMAX  124.0             /* min/max channel used */
#define S3XNQMIN    1.0
#define S3XQ_MAX   35.0             /* min/max m/q classified */
#define S3XQ_MIN    1.0

double dswxu         (short stau, double dToff, double dTdac);
double dswxeoq       (BYTE bstp, BYTE abeqtab[60], double *adcnq);
double dswxpal       (BYTE bpaps, BYTE bred, double *adcnq);
double dswxlnmq      (double dw, short stau, double *adcnq);
double dswxlnm       (short stau, BYTE besd, double *adcnm);

double adputof       (double eoq, double paps, double moq);
double adpumoq_sig   (double sTOF, double TOF, double moq);
double adpuesd       (double tof, double mas);
double adpumoq       (double eoq, double paps, double tof);
double adpumas       (double esd, double tof);

double adpueoq       (int istep);



#endif
