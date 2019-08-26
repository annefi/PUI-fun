/* $Id: CrisConstants.h,v 1.1 1997/09/10 18:26:21 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/CrisConstants.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/09/10 18:26:21 $ */
/* $Revision: 1.1 $ */

#define CRIS_DIAG_BIT                           0x20
#define CRIS_CMD_RESP_BIT                       0x40
#define CRIS_SYNC_BIT                           0x80

#define CRIS_QUALITY_FORMAT_ID_BIT              0x01
#define CRIS_QUALITY_MNF_COUNTER_BIT            0x02
#define CRIS_QUALITY_SC_CLOCK_BIT               0x04
#define CRIS_QUALITY_SYNC_BIT                   0x08
#define CRIS_QUALITY_CT_INDEX_BIT               0x10
#define CRIS_QUALITY_CYCLE_NUMBER_BIT           0x20
#define CRIS_QUALITY_FILL_LEVEL0_BIT            0x40
#define CRIS_QUALITY_FILL_LEVEL1_BIT            0x80

#define CRIS_UNDEFINED_8                        0xFF
#define CRIS_UNDEFINED_16                     0xFFFF
#define CRIS_UNDEFINED_32                 0xFFFFFFFF

#define CRIS_END_OF_DATA                  0xFFFFFFFF

#define CRIS_LIVETIME_UNIT_MICROSECOND           128

#define CRIS_EVENT_THRESHOLD                       3
#define CRIS_HSKP_OFFSET                           4

#define NUM_CRIS_CMD_TAB_BYTES                   844
#define NUM_CRIS_CMD_TAB_BYTES_PER_CYCLE          66
#define NUM_CRIS_EVT_BUFFERS                      64
#define NUM_CRIS_HIGH_PRIORITY_RATES               2
#define NUM_CRIS_HIGH_PRIORITY_SAMPLES            16
#define NUM_CRIS_HSKP_BYTES                        3
#define NUM_CRIS_MNFS_PER_CYCLE                  256
#define NUM_CRIS_RAW_SOFT_EVT_BYTES             2000
#define NUM_CRIS_RAW_STACK_EVT_BYTES              72
#define NUM_CRIS_TELEMETRY_BYTES                  58

#define MAX_CRIS_EVT_AGE                          64
#define MAX_NUM_CRIS_CMD_ECHO_CHARS               40
#define MAX_NUM_CRIS_DIAG_BYTES                33002
#define MAX_NUM_CRIS_EVENT_BYTES                 162
#define MAX_NUM_CRIS_EVENTS_PER_MNF                5
#define MAX_NUM_CRIS_EVT_SUB_BLOCKS               32

#define SIZE_CRIS_CMD_ECHO_QUEUE                1000
#define SIZE_CRIS_CMD_TAB_QUEUE                   24
#define SIZE_CRIS_CYCLE_QUEUE                     16
#define SIZE_CRIS_DIAG_EVENT_QUEUE                32
#define SIZE_CRIS_SUBSET_FILTER                    3
#define SIZE_CRIS_SUMMARY_QUEUE                   64
#define SIZE_CRIS_EVENT_BUFFER                 17000

#define CRIS_SC_HSKP_CURRENT_LOC                 203
#define CRIS_SC_HSKP_MAIN_BUS_VOLT_LOC            71
#define CRIS_SC_HSKP_TEMPERATURE1_LOC            194
#define CRIS_SC_HSKP_TEMPERATURE2_LOC            195
#define CRIS_SC_HSKP_TEMPERATURE_INT_LOC          22

#define CRIS_MNF_CURRENT                          10
#define CRIS_MNF_MAIN_BUS_VOLT                     3
#define CRIS_MNF_TEMPERATURE1                      9
#define CRIS_MNF_TEMPERATURE2                      9

#define CRIS_CONSISTENCY_CLOCK                     4
#define CRIS_CONSISTENCY_CYCLE_NUMBER              0
#define CRIS_CONSISTENCY_CTINDEX                   1
#define CRIS_CONSISTENCY_TOTAL                     5
