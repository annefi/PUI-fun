/* --------------------------------------------------------------- <Prolog> --
   expand_tools.h --- utilities connected to "expanding" of cycles
   Simon Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: expand_tools.h,v 1.1.1.1 2000/06/02 13:37:21 jraines Exp $
   ------------------------------------------------------------- </Prolog> -*/

#include <stdio.h>

#include "libhef.h"
#include "../../netcdf-3.6.0-p1/include/netcdf.h"

#ifndef EXPAND_TOOLSH
#define EXPAND_TOOLSH

#define XNEQNOMTAB 2                    /* number of accepted E/q tables */
#define XEQTABNOM  0                    /* nominal table */
#define XEQTABJAN  1                    /* table used in Jan 1998 */

#define MNEQNOMTAB 4                    /* number of accepted E/q tables */
#define MEQTABNOM  2                    /* nominal table */

int    ccycg           (SBCYC *pcyc);
int    ccycg_recnrinc  (SBCYC *pcyc);
int    ccycg_timeinc   (SBCYC *pcyc);

int    ccycx           (SBCYC *pcyc);
int    ccycx_mcplev    (SBCYC *pcyc, int iexplev);
int    ccycx_pavlev    (SBCYC *pcyc, int iexplev);
int    ccycx_eqhk      (SBCYC *pcyc);
int    ccycx_eqtabnom  (SBCYC *pcyc, int itab);
int    ccycx_rates     (SBCYC *pcyc);
                                        
int    ccycm           (SBCYC *pcyc);
int    ccycm_mcalev    (SBCYC *pcyc, int iexplev);
int    ccycm_mcolev    (SBCYC *pcyc, int iexplev);
int    ccycm_hyplev    (SBCYC *pcyc, int iexplev);
int    ccycm_eqhk      (SBCYC *pcyc);
int    ccycm_eqtabnom  (SBCYC *pcyc, int itab);

int    cycok           (BYTE abedb[NEDB][NBINEDB], 
			BYTE abQAC[NEDB], SBCYC *pcyc);
void   nc_readcyc      (int edbid,int ic,BYTE abedb[NEDB][NBINEDB],
			double adtime[NEDB],BYTE abQAC[NEDB]);
void   nc_handle_error (int itmp, int line);
char   *zrecid(SBCYC *pcyc);

#endif
