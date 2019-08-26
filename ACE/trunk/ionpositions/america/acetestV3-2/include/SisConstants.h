/* $Id: SisConstants.h,v 1.3 2000/12/11 23:09:54 rgr Exp $ */

/* $Source: /users/asc/aceprog/include/RCS/SisConstants.h,v $ */
/* $Author: rgr $ */
/* $Date: 2000/12/11 23:09:54 $ */
/* $Revision: 1.3 $ */

#define SIS_DIAG_BIT                           0x20
#define SIS_CMD_RESP_BIT                       0x40
#define SIS_SYNC_BIT                           0x80

#define SIS_QUALITY_FORMAT_ID_BIT              0x01
#define SIS_QUALITY_MNF_COUNTER_BIT            0x02
#define SIS_QUALITY_SC_CLOCK_BIT               0x04
#define SIS_QUALITY_SYNC_BIT                   0x08
#define SIS_QUALITY_CT_INDEX_BIT               0x10
#define SIS_QUALITY_CYCLE_NUMBER_BIT           0x20
#define SIS_QUALITY_FILL_LEVEL0_BIT            0x40
#define SIS_QUALITY_FILL_LEVEL1_BIT            0x80

#define SIS_UNDEFINED_8                        0xFF
#define SIS_UNDEFINED_16                     0xFFFF
#define SIS_UNDEFINED_32                 0xFFFFFFFF

#define SIS_END_OF_DATA                  0xFFFFFFFF

#define NUM_SIS_CMD_TAB_BYTES                  1180
#define NUM_SIS_CMD_TAB_BYTES_PER_CYCLE          80
#define NUM_SIS_EVT_BUFFERS                      96
#define NUM_SIS_EVT_CLASSES                       4
#define NUM_SIS_HSKP_BYTES                        6
#define NUM_SIS_HIGH_PRIORITY_RATES              18
#define NUM_SIS_HIGH_PRIORITY_SAMPLES             8
#define NUM_SIS_MATRIX_STRIPS                    64
#define NUM_SIS_MATRIX_PLANES                     4
#define NUM_SIS_MNFS_PER_CYCLE                  256
#define NUM_SIS_RAW_STACK_EVT_BYTES             540
#define NUM_SIS_STACK_DETECTORS                   8
#define NUM_SIS_TELEMETRY_BYTES                 249

#define MAX_NUM_SIS_DIAG_BYTES                  660
#define MAX_NUM_SIS_EVENT_BYTES                 109
#define MAX_NUM_SIS_EVENTS_PER_MNF               17
#define MAX_NUM_SIS_CMD_ECHO_CHARS               80
#define MAX_NUM_SIS_EVT_SUB_BLOCKS               32

#define MAX_SIS_EVT_AGE                           8

#define SIS_LIVETIME_UNIT_MICROSECOND             8
#define SIS_COINCIDENCE_WINDOW_UNIT_MICROSECOND   4

#define SIS_HSKP_OFFSET                           0
#define SIS_EVENT_THRESHOLD                       4
#define SIS_EVT_BUFFER_NUMBER_OFFSET             32

#define SIZE_SIS_SUBSET_FILTER                    3
#define SIZE_SIS_CYCLE_QUEUE                     16
#define SIZE_SIS_CMD_TAB_QUEUE                   24
#define SIZE_SIS_SUMMARY_QUEUE                   64
#define SIZE_SIS_CMD_ECHO_QUEUE                1000
#define SIZE_SIS_DIAG_EVENT_QUEUE                64
#define SIZE_SIS_EVENT_BUFFER                 75000


#define SIS_SC_HSKP_COVER_TELLTALE_LOC          202
#define SIS_SC_HSKP_CURRENT_LOC                 204
#define SIS_SC_HSKP_MAIN_BUS_VOLT_LOC            71
#define SIS_SC_HSKP_TEMPERATURE1_LOC            196
#define SIS_SC_HSKP_TEMPERATURE2_LOC            197
#define SIS_SC_HSKP_TEMPERATURE_INT_LOC          23

#define SIS_MNF_COVER_TELLTALE                   10
#define SIS_MNF_CURRENT                          10
#define SIS_MNF_MAIN_BUS_VOLT                     3
#define SIS_MNF_TEMPERATURE1                      9
#define SIS_MNF_TEMPERATURE2                      9

#define SIS_CONSISTENCY_CLOCK                     4
#define SIS_CONSISTENCY_CYCLE_NUMBER              1
#define SIS_CONSISTENCY_CTINDEX                   1
#define SIS_CONSISTENCY_TOTAL                     6

#define SIS_HIGH_PRIORITY_RTSW_0                 16
#define SIS_HIGH_PRIORITY_RTSW_1                 17
