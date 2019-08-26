/* $Id: swepam_bri.h,v 1.1 1997/08/15 00:51:02 jeff Exp $ */
#include "hdfi.h"

struct SwepamI_br
{
  float64 bin_start;      /* beginning of bin. ACE epoch */
  float64 bin_end;        /* end of bin. ACE epoch */

    int32 flag3d;          /* =0 data OK. */
			    /* & 0x01 - proton density < 0 */
			    /* & 0x02 - alpha density < 0 */
			    /* & 0x04 - proton T < 0 */
			    /* & 0x08 - speed < 0 */
			    /* & 0x10 - lmx=255, not SWI mode */

    float32 np;            /* proton number density, cm^-3 */
    float32 he_ratio;      /* nHe++/np */
    float32 speed;         /* SW (bulk) speed */
    float32 Trr;           /* (1,1) component of temp tensor along radial dir*/
};
