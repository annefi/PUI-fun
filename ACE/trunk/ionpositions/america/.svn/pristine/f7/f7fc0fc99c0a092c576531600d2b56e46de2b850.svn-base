/* $Id: L1CrisPrototype.h,v 1.5 1998/05/31 23:25:23 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisPrototype.h,v $ */
/* $Author: rgr $ */
/* $Date: 1998/05/31 23:25:23 $ */
/* $Revision: 1.5 $ */

void accum_cris_level1(uint8  *cris_data,
               struct SCdata  sc_params,
           struct SCHskpData  schskp,
                       uint8  qac);




uint8 CrisQueryCmpEvtAge(uint8 *event);

uint8 CrisQueryCmpEvtId(uint8 *event);

uint8 CrisQueryCmpEvtLengthComponents(uint8 *event);

uint8 CrisQueryCmpEvtLengthTotal(uint8 *event);

uint8 CrisQueryMnfCmdResp(uint8 *mnf);

uint8 CrisQueryMnfDiag(uint8 *mnf);




void L1CrisAccumCommandEchoes(struct L1CrisSubsetState  *sub,
                         struct L1CrisCommandEchoState  *cmd);

void L1CrisAccumCommandTable( struct L1CrisCycleState  *CycleState,
                       struct L1CrisCommandTableState  *cts);

void L1CrisAccumCycle(struct L1CrisSubsetState  *sub,
                       struct L1CrisCycleState  *cycle);

void L1CrisAccumDiagEvent(struct L1CrisSubsetState  *sub,
                       struct L1CrisDiagEventState  *diag);

void L1CrisAccumEventBlock(struct L1CrisCycleState  *CycleState,
                      struct L1CrisEventBlockState  *BlockState);




void L1CrisBuildEventCycle(   uint32  BlockNumber0,
                              uint32  BlockNumber1,
        struct L1CrisEventBlockState  *blk,
   struct L1CrisLowPriorityRateState  *rate);

void L1CrisBuildCommandTable(uint32  clock0,
                             uint32  clock1,
                              uint8  *ct,
                              uint8  *qual,
                             struct  L1CrisCommandTable *CmdTab);

void L1CrisBuildCycle(struct L1CrisCycleState  *state);

void L1CrisBuildEventBlock(uint32  ClockCycle0,
                           uint32  ResetNumber0,
                           uint32  CycleNumber,
                            uint8  *cycle0,
                            uint8  *QualityCycle0,
                           uint32  ClockCycle1,
                           uint32  ResetNumber1,
                            uint8  *cycle1,
                            uint8  *QualityCycle1,
     struct L1CrisEventBlockState  *evt);

void L1CrisBuildEventSubblocks(uint16 NumberBorrowed,
                                uint8 *cycle0,
                                uint8 *QualityCycle0,
                                uint8 *cycle1,
                                uint8 *QualityCycle1,
                                uint8 *EventArray,
                               uint16 *MnfArray,
                                uint8 *LocationArray,
                                uint8 *NumberSubblocks,
                                int32 *boundary);

void L1CrisBuildLowPriorityRate(
                       struct L1CrisCycleState  *CycleState,
             struct L1CrisLowPriorityRateState  *LowPriorityRateState);

void L1CrisBuildHighPriorityRate(
                      struct L1CrisCycleState  *CycleState,
           struct L1CrisHighPriorityRateState  *HighPriorityRateState);

void L1CrisBuildHskp(struct L1CrisCycleState  *CycleState,
                      struct L1CrisHskpState  *HskpState);

void L1CrisBuildSubset(uint8  *cris_data,
               struct SCdata  *sc_params,
           struct SCHskpData  *schskp,
                       uint8  qac,
    struct L1CrisSubsetState  *sub);

void L1CrisBuildSummary(struct L1CrisSubsetState  *SubsetState,
                       struct L1CrisSummaryState  *SummaryState);




uint8 L1CrisCheckEventLength(uint8 *event);

void L1CrisCheckEventNulls(uint8 *EvtArray,
                           uint32 EvtArraySize,
                           uint32 EventIndex);

void L1CrisCmdTabByteInit(uint8 *ct);

uint32 L1CrisCycleConsistency(uint32  index0,
                              uint32  index1,
             struct L1CrisCycleState  *state);

void L1CrisCycleFix(uint32  index0,
                    uint32  index1,
   struct L1CrisCycleState  *state);




void L1CrisExtractAdc(uint8  *cycle,
                      uint8  *QualityCycle,
          struct L1CrisHskp  *hskp);

void L1CrisExtractCommandTableSegment(uint8 *cycle,
                                      uint8 *QualityCycle,
                                      uint8 *CommandTableSegment,
                                      uint8 *QualitySegment);

void L1CrisExtractDac(uint8  *cycle,
                      uint8  *QualityCycle,
          struct L1CrisHskp  *hskp);

void L1CrisExtractDiagEvent(struct L1CrisDiagEventState *diag);

void L1CrisExtractHighPriorityRate(uint32  ClockCycle,
                                    uint8  *cycle,
                                    uint8  *QualityCycle,
            struct L1CrisHighPriorityRate  *rate);

void L1CrisExtractHskp(uint32  ClockCycle,
                        uint8  *cycle,
                        uint8  *QualityCycle,
            struct L1CrisHskp  *hskp);

void L1CrisExtractLowPriorityRate(uint32  ClockCycle,
                                   uint8  *cycle,
                                   uint8  *QualityCycle,
            struct L1CrisLowPriorityRate  *rate);

void L1CrisExtractStatus(uint8  *cycle,
                         uint8  *QualityCycle,
             struct L1CrisHskp  *hskp);




void L1CrisFillNumberEvents(  uint32  ClockCycle,
                              uint16  *nevents,
   struct L1CrisLowPriorityRateState  *rate);

void L1CrisFilterSubsets(struct L1CrisSubsetState  *sub);

void L1CrisFilterCycles(struct L1CrisCycleState  *cycle);

void L1CrisFindCycleNumbers(uint32  BlockNumber0,
                            uint32  BlockNumber1,
      struct L1CrisEventBlockState  *blk);

void L1CrisFindEvents(uint32 SyncThreshold,
                      uint32 NumberSyncEvents,
                       uint8 *EvtArray,
                      uint32 EvtArraySize,
                      uint32 *index,
                      uint32 *NumberEvents);

void L1CrisMakeCommandTable(uint32  MinorFrameClock0,
                            uint32  MinorFrameClock1,
                             uint8  *CurrentCommandTable,
                             uint8  *PreviousCommandTable,
                             uint8  *quality,
         struct L1CrisCommandTable  *CommandTable);

void L1CrisSetHskpRateDefaults(uint8 *cycle,
                               uint8 *quality,
                               uint8 *DefaultValue);

uint32 L1CrisTestCycle(struct L1CrisCycleState  *cycle);

int L1CrisTestDiagEvent(uint8 *DiagEvent, uint32 NumberBytes);




void output_cris_level1(void);

void L1CrisOutputCommandEchoes(struct L1CrisCommandEchoState *cmd);

void L1CrisOutputCommandTables(struct L1CrisCommandTableState  *cmd,
                                struct L1CrisCommandEchoState  *echo);

void L1CrisOutputDiagEvents(struct L1CrisDiagEventState *diag);

void L1CrisOutputDiagMode(struct L1CrisDiagModeState *mode,
                            struct L1CrisSubsetState *sub);

void L1CrisOutputEvents(struct L1CrisEventBlockState  *blk,
                   struct L1CrisLowPriorityRateState  *rate);

void L1CrisOutputHighPriorityRates(
                             struct L1CrisHighPriorityRateState *rate);

void L1CrisOutputHskp(struct L1CrisHskpState *hskp);

void L1CrisOutputLowPriorityRates(
                              struct L1CrisLowPriorityRateState *rate);

void L1CrisOutputSummaries(struct L1CrisSummaryState *sum);




void BrowseCrisExtract(struct L1CrisLowPriorityRate  *lp,
                                  struct BrowseCris  *browse);

void ComputeCrisBufferRates(struct L1CrisLowPriorityRate  *lp,
                                                 float32  *rate);

void output_cris_browse(void);





void read_cris_status(int fd);
void write_cris_status(int fd);





int32 write_BrowseCris(struct BrowseCris BrowseCris_struc,
                       int32 recnum);

int32 write_L1CrisCommandEcho(
                      struct L1CrisCommandEcho L1CrisCommandEcho_struc,
                      int32 recnum);

int32 write_L1CrisCommandTable(
                    struct L1CrisCommandTable L1CrisCommandTable_struc,
                    int32 recnum);

int32 write_L1CrisDiagnosticEvent(
              struct L1CrisDiagnosticEvent L1CrisDiagnosticEvent_struc,
              int32 recnum);
int32 write_L1CrisEventCycle(
                        struct L1CrisEventCycle L1CrisEventCycle_struc,
                        int32 recnum);

int32 write_L1CrisHighPriorityRate(
            struct L1CrisHighPriorityRate L1CrisHighPriorityRate_struc,
            int32 recnum);

int32 write_L1CrisHskp(struct L1CrisHskp L1CrisHskp_struc,
             int32 recnum);

int32 write_L1CrisLowPriorityRate(
              struct L1CrisLowPriorityRate L1CrisLowPriorityRate_struc,
              int32 recnum);

int32 write_L1CrisSubset(struct L1CrisSubset L1CrisSubset_struc,
                         int32 recnum);

int32 write_L1CrisSummary(struct L1CrisSummary L1CrisSummary_struc,
                          int32 recnum);
