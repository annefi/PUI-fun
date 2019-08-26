/* $Id: L1SisPrototype.h,v 1.8 2001/11/14 00:38:22 rgr Exp $ */

/* $Author: rgr $ */
/* $Source: /users/asc/aceprog/include/RCS/L1SisPrototype.h,v $ */
/* $Date: 2001/11/14 00:38:22 $ */
/* $Revision: 1.8 $ */

void BrowseSisAddRtsw(struct L1SisHighPriorityRateState  *state,
                                     struct BrowseSis_1  *browse);

void BrowseSisExtract(struct L1SisLowPriorityRateExtended  *lp,
                                    struct BrowseSisState  *state,
                                       struct BrowseSis_1  *browse);

void ComputeSisBufferRates(struct L1SisLowPriorityRateExtended  *lp,
                                         struct BrowseSisState  *state,
                                                       float32  *rate,
                                                         uint8  flag);

float32 ComputeSisCoinRate1(struct L1SisLowPriorityRateExtended *lp);

float32 ComputeSisT4Rate(struct L1SisLowPriorityRateExtended *lp);

void L1SisAccumCommandEchoes(struct L1SisSubsetState  *sub,
                        struct L1SisCommandEchoState  *cmd);

void L1SisAccumCommandTable( struct L1SisCycleState  *CycleState,
                      struct L1SisCommandTableState  *cts);

void L1SisAccumCycle(struct L1SisSubsetState  *sub,
                      struct L1SisCycleState  *cycle);

void L1SisAccumDiagEvent(struct L1SisSubsetState  *sub,
                      struct L1SisDiagEventState  *diag);

void L1SisAccumEventBlock(struct L1SisCycleState  *CycleState,
                     struct L1SisEventBlockState  *BlockState);

void L1SisBuildCommandTable(uint32  clock0,
                            uint32  clock1,
                             uint8  *ct,
                             uint8  *qual,
          struct L1SisCommandTable  *CmdTab);

void L1SisBuildCycle(struct L1SisCycleState  *state);

void L1SisBuildDacOffset0( struct L1SisCycleState  *CycleState,
                      struct L1SisDacOffset0State  *DacOffset0State);

void L1SisBuildDacOffset1( struct L1SisCycleState  *CycleState,
                      struct L1SisDacOffset1State  *DacOffset1State);

void L1SisBuildEventBlock(uint32  ClockCycle0,
                          uint32  ResetNumber0,
                          uint32  CycleNumber,
                           uint8  *cycle0,
                           uint8  *QualityCycle0,
                          uint32  ClockCycle1,
                          uint32  ResetNumber1,
                           uint8  *cycle1,
                           uint8  *QualityCycle1,
     struct L1SisEventBlockState  *evt);

void L1SisBuildEventCycle(   uint32  BlockNumber0,
                             uint32  BlockNumber1,
        struct L1SisEventBlockState  *blk,
   struct L1SisLowPriorityRateState  *rate);

void L1SisBuildEventSubblocks(uint16 NumberBorrowed,
                               uint8 *cycle0,
                               uint8 *QualityCycle0,
                               uint8 *cycle1,
                               uint8 *QualityCycle1,
                               uint8 *EventArray,
                              uint16 *MnfArray,
                               uint8 *LocationArray,
                               uint8 *NumberSubblocks,
                               int32 *boundary);

void L1SisBuildHighPriorityRate(
                       struct L1SisCycleState  *CycleState,
            struct L1SisHighPriorityRateState  *HighPriorityRateState);

void L1SisBuildHskp(struct L1SisCycleState  *CycleState,
                     struct L1SisHskpState  *HskpState);

void L1SisBuildLowPriorityRate(
                        struct L1SisCycleState  *CycleState,
              struct L1SisLowPriorityRateState  *LowPriorityRateState);

void L1SisBuildSubset(uint8  *sis_data,
              struct SCdata  *sc_params,
          struct SCHskpData  *schskp,
                      uint8  qac,
    struct L1SisSubsetState  *sub);

void L1SisBuildSummary(struct L1SisSubsetState  *SubsetState,
                      struct L1SisSummaryState  *SummaryState);

uint8 L1SisCheckEventLength(uint8 *event);

void L1SisCmdTabByteInit(uint8 *ct);

uint32 L1SisCycleConsistency(uint32  index0,
                             uint32  index1,
             struct L1SisCycleState  *state);

void L1SisCycleFix(uint32  index0,
                   uint32  index1,
   struct L1SisCycleState  *state);

void L1SisExtractAdc(uint8  *cycle,
                     uint8  *QualityCycle,
          struct L1SisHskp  *hskp);

void L1SisExtractCommandTableSegment(uint8 *cycle,
                                     uint8 *QualityCycle,
                                     uint8 *CommandTableSegment,
                                     uint8 *QualitySegment);

void L1SisExtractDacOffset0(uint32  ClockCycle,
                             uint8  *cycle,
                             uint8  *QualityCycle,
            struct L1SisDacOffset0  *matrix);

void L1SisExtractDacOffset1(uint32  ClockCycle,
                             uint8 *cycle,
                             uint8  *QualityCycle,
            struct L1SisDacOffset1  *matrix);

void L1SisExtractDiagEvent(struct L1SisDiagEventState *diag);

void L1SisExtractHighPriorityRate(uint32  ClockCycle,
                                   uint8  *cycle,
                                   uint8  *QualityCycle,
            struct L1SisHighPriorityRate  *rate);

void L1SisExtractHskp(uint32  ClockCycle,
                       uint8  *cycle,
                       uint8  *QualityCycle,
            struct L1SisHskp  *hskp);

void L1SisExtractLowPriorityRate(uint32  ClockCycle,
                                  uint8  *cycle,
                                  uint8  *QualityCycle,
    struct L1SisLowPriorityRateExtended  *rate);

void L1SisExtractMatrixDacCoarse(uint8  *cycle,
                                 uint8  *QualityCycle,
                struct L1SisDacOffset0  *matrix);

void L1SisExtractMatrixDacFine(uint8  *cycle,
                               uint8  *QualityCycle,
              struct L1SisDacOffset1  *matrix);

void L1SisExtractMatrixOffsetA(uint8  *cycle,
                               uint8  *QualityCycle,
              struct L1SisDacOffset0  *matrix);

void L1SisExtractMatrixOffsetB(uint8  *cycle,
                               uint8  *QualityCycle,
              struct L1SisDacOffset1  *matrix);

void L1SisExtractStatus(uint8  *cycle,
                        uint8  *QualityCycle,
             struct L1SisHskp  *hskp);

void L1SisFillNumberEvents(  uint32  ClockCycle,
                             uint16  *nevents,
                             uint16  *neventsCno,
                             uint16  *neventsHiz,
   struct L1SisLowPriorityRateState  *rate);

void L1SisFilterCycles(struct L1SisCycleState  *cycle);

void L1SisFilterSubsets(struct L1SisSubsetState  *sub);

void L1SisFindEvents(uint32 SyncThreshold,
                     uint32 NumberSyncEvents,
                      uint8 *EvtArray,
                     uint32 EvtArraySize,
                     uint32 *index,
                     uint32 *NumberEvents);

void L1SisHpCmdInit(uint16 *hiprcmd);

void L1SisMakeCommandTable(uint32  MinorFrameClock0,
                           uint32  MinorFrameClock1,
                            uint8  *CurrentCommandTable,
                            uint8  *PreviousCommandTable,
                            uint8  *quality,
         struct L1SisCommandTable  *CommandTable);

void L1SisSetHskpRateDefaults(uint8 *cycle,
                              uint8 *quality,
                              uint8 *DefaultValue);

uint32 L1SisTestCycle(struct L1SisCycleState  *cycle);

int L1SisTestDiagEvent(uint8 *DiagEvent, uint32 NumberBytes);

void L1SisOutputCommandEchoes(struct L1SisCommandEchoState *cmd);

void L1SisOutputCommandTables(struct L1SisCommandTableState *cmd,
                               struct L1SisCommandEchoState *echo);

void L1SisOutputDacOffsets0(struct L1SisDacOffset0State *matrix);

void L1SisOutputDacOffsets1(struct L1SisDacOffset1State *matrix);

void L1SisOutputDiagEvents(struct L1SisDiagEventState *diag);

void L1SisOutputDiagMode(struct L1SisDiagModeState *mode,
                           struct L1SisSubsetState *sub);

void L1SisOutputEvents(struct L1SisEventBlockState  *blk,
                  struct L1SisLowPriorityRateState  *rate);

void L1SisOutputHighPriorityRates(
                              struct L1SisHighPriorityRateState *rate);

void L1SisOutputHskp(struct L1SisHskpState *hskp);

void L1SisOutputLowPriorityRates(
                               struct L1SisLowPriorityRateState *rate);

void L1SisOutputSummaries(struct L1SisSummaryState *sum);

uint8 SisQueryCmpEvtAge(uint8 *event);

uint8 SisQueryCmpEvtClass(uint8 *event);

uint8 SisQueryCmpEvtCno(uint8 *event);

uint8 SisQueryCmpEvtHiZ(uint8 *event);

uint8 SisQueryCmpEvtId(uint8 *event);

uint8 SisQueryCmpEvtLengthComponents(uint8 *event);

uint8 SisQueryCmpEvtLengthTotal(uint8 *event);

uint8 SisQueryMnfDiag(uint8 *mnf);

uint8 SisQueryMnfCmdResp(uint8 *mnf);

float32 UncompressSisValue(uint16 value);





void accum_sis_level1(uint8  *sis_data,
              struct SCdata  sc_params,
          struct SCHskpData  schskp,
                      uint8  qac);

int checkCompressedEvent_s(uint8  *telemetry,
                          uint32  index);

int16 findMaxMatrixValue(const int16 *pha);

void output_sis_browse(void);

void output_sis_level1(void);

void read_sis_status(int fd);

void unpackEventHeader_s(uint8  *telemetry,
                        uint32  *index,
           struct L1_1SisEvent  *event);

void unpackEvent_s(uint8 *telemetry, struct L1_1SisEvent *event);

void unpackMatrixStrips_s(uint8  *telemetry,
                         uint32  *index,
            struct L1_1SisEvent  *event);

void unpackPeakAndOffsetData_s(uint8  *telemetry,
                              uint32  *index,
                 struct L1_1SisEvent  *event);

void unpackStackPhas_s(uint8  *telemetry,
                       uint32  *index,
          struct L1_1SisEvent  *event);

void unpackStimData_s(uint8  *telemetry,
                     uint32  *index,
        struct L1_1SisEvent  *event);

void write_sis_status(int fd);





int32 write_BrowseSis(struct BrowseSis_1 BrowseSis_struc,
                      int32 recnum);

int32 write_L1SisCommandEcho(
                        struct L1SisCommandEcho L1SisCommandEcho_struc,
                        int32 recnum);

int32 write_L1SisCommandTable(
                      struct L1SisCommandTable L1SisCommandTable_struc,
                      int32 recnum);

int32 write_L1SisDacOffset0(
                          struct L1SisDacOffset0 L1SisDacOffset0_struc,
                          int32 recnum);

int32 write_L1SisDacOffset1(
                          struct L1SisDacOffset1 L1SisDacOffset1_struc,
                          int32 recnum);

int32 write_L1SisDiagnosticEvent(
                struct L1SisDiagnosticEvent L1SisDiagnosticEvent_struc,
                int32 recnum);

int32 write_L1SisEventCycle(
                          struct L1SisEventCycle L1SisEventCycle_struc,
                          int32 recnum);

int32 write_L1SisHighPriorityRate(
              struct L1SisHighPriorityRate L1SisHighPriorityRate_struc,
              int32 recnum);

int32 write_L1SisHskp(struct L1SisHskp L1SisHskp_struc,
                      int32 recnum);

int32 write_L1SisLowPriorityRate(
                struct L1SisLowPriorityRate L1SisLowPriorityRate_struc,
                int32 recnum);

int32 write_L1SisSubset(struct L1SisSubset L1SisSubset_struc,
                        int32 recnum);

int32 write_L1SisSummary(struct L1SisSummary L1SisSummary_struc,
                        int32 recnum);
