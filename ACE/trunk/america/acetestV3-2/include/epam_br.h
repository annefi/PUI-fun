/* $Id: epam_br.h,v 1.6 1998/07/24 17:01:41 ad Exp $ */
#include "hdfi.h"

struct Epam_br
{
  float64 bin_start;            /* beginning of bin. ACE epoch */
  float64 bin_end;            /* end of bin. ACE epoch */

  float32 P1;              /* Flux of .047 - .065 Mev ions EPAM */
  float32 P3;              /* Flux of .112 - .187 Mev ions EPAM */
  float32 P5;              /* Flux of .310 - .580 Mev ions EPAM */
  float32 P7;              /* Flux of 1.06 - 1.91 MeV ions EPAM */
  float32 DE1;             /* Flux of .038 - .053 Mev electrons EPAM */
  float32 DE4;             /* Flux of .175 - .315 Mev electrons EPAM */
  float32 W1;              /* Flux of .480 - .966 Mev protons EPAM */
  float32 fp6p;            /* Flux of .761 - 1.22 Mev protons EPAM */

  float32 EPAM_livetime;   /* livetime (seconds) for these measurements. */
};
