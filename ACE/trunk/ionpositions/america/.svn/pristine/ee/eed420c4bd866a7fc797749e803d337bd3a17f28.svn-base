/* $Id: L1SisState.h,v 1.1 1997/08/11 03:11:24 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:11:24 $ */
/* $Revision: 1.1 $ */

#include "L1SisSubsetState.h"
#include "L1SisSummaryState.h"
#include "L1SisCycleState.h"
#include "L1SisEventBlockState.h"
#include "L1SisHskpState.h"
#include "L1SisDacOffset0State.h"
#include "L1SisDacOffset1State.h"
#include "L1SisLowPriorityRateState.h"
#include "L1SisHighPriorityRateState.h"
#include "L1SisCommandTableState.h"
#include "L1SisCommandEchoState.h"
#include "L1SisDiagEventState.h"
#include "L1SisDiagModeState.h"
#include "L1SisFlags.h"

struct L1SisState {
             struct L1SisSubsetState  SubsetState;
           struct L1SisDiagModeState  DiagModeState;
        struct L1SisCommandEchoState  CommandEchoState;
          struct L1SisDiagEventState  DiagEventState;
            struct L1SisSummaryState  SummaryState;
              struct L1SisCycleState  CycleState;
         struct L1SisEventBlockState  EventBlockState;
         struct L1SisDacOffset0State  DacOffset0State;
         struct L1SisDacOffset1State  DacOffset1State;
               struct L1SisHskpState  HskpState;
    struct L1SisLowPriorityRateState  LowPriorityRateState;
   struct L1SisHighPriorityRateState  HighPriorityRateState;
       struct L1SisCommandTableState  CommandTableState;
                   struct L1SisFlags  flag; 
};
