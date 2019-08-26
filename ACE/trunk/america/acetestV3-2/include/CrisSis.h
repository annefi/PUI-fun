/* $Id: CrisSis.h,v 1.1 1997/08/11 02:33:59 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/CrisSis.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:33:59 $ */
/* $Revision: 1.1 $ */


#define SCIENCE_FORMAT       1
#define ADC_FORMAT           2

#define NUM_SC_MJFS          8
#define NUM_SC_MNFS         16



void AceEpochTime(uint32 clock,
                  uint32 *Second1996,
                  uint32 *microsecond);

void FrameCounterDecrement(uint8 *major, uint8 *minor);

void FrameCounterIncrement(uint8 *major, uint8 *minor);

void OrInt16(uint8 *byte, uint8 *flag, uint32 number);

void PackInt16(void *integer, void *byte, uint32 number);

void UnpackInt16(void *byte, void *integer, uint32 number);
