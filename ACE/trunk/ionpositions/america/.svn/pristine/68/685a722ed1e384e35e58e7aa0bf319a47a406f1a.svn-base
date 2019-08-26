/* $Id: L1CrisState.h,v 1.1 1997/08/11 02:46:49 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:46:49 $ */
/* $Revision: 1.1 $ */

#include "L1CrisSubsetState.h"
#include "L1CrisCycleState.h"
#include "L1CrisEventBlockState.h"
#include "L1CrisHskpState.h"
#include "L1CrisLowPriorityRateState.h"
#include "L1CrisHighPriorityRateState.h"
#include "L1CrisCommandTableState.h"
#include "L1CrisSummaryState.h"
#include "L1CrisCommandEchoState.h"
#include "L1CrisDiagEventState.h"
#include "L1CrisDiagModeState.h"
#include "L1CrisFlags.h"

struct L1CrisState {
             struct L1CrisSubsetState  SubsetState;
           struct L1CrisDiagModeState  DiagModeState;
        struct L1CrisCommandEchoState  CommandEchoState;
          struct L1CrisDiagEventState  DiagEventState;
            struct L1CrisSummaryState  SummaryState;
              struct L1CrisCycleState  CycleState;
         struct L1CrisEventBlockState  EventBlockState;
               struct L1CrisHskpState  HskpState;
    struct L1CrisLowPriorityRateState  LowPriorityRateState;
   struct L1CrisHighPriorityRateState  HighPriorityRateState;
       struct L1CrisCommandTableState  CommandTableState;
                   struct L1CrisFlags  flag;
};
