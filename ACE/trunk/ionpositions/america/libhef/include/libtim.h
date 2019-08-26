/* --------------------------------------------------------------- <Prolog> --
   libtim.h --- header file for time handling
   (c) Simon Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: libtim.h,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   ------------------------------------------------------------- </Prolog> -*/

#include <stdio.h>

#ifndef LIBTIMH
#define LIBTIMH

#define LTIGREG2 2299161L
#define LTIGREG1 (15L + 31L*(10L + 12L * 1582L))


#define SEC70POS 0
#define JULDYPOS 1
#define SECDYPOS 2
#define DOY__POS 3
#define DAY__POS 4
#define MONTHPOS 5
#define YEAR_POS 6
#define HOUR_POS 7
#define MIN__POS 8
#define SEC__POS 9
#define WDAY_POS 10
#define DUM1_POS 11
#define DUM2_POS 12
#define DUM3_POS 13

#define SECOFDAY 86400L

/* long g_alltime[14]; */

void sec70_time (long alltime[14], long *sec70);
void ltcaldat   (long *julian, long *mm, long *id, long *iyyy);
void ltjulday   (long *mm, long *id, long *iyyy,long *julday);
void doy_time   (long alltime[14], long *doy, long *year);
void date_time  (long alltime[14], long *mday, long *mon, long *year);
int  is_leap    (int iyear);
char *timstr    (long sec70);

#endif
