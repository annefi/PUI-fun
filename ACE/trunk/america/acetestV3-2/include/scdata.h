/* $Id: scdata.h,v 1.2 1996/11/06 23:15:23 jeff Exp $ */
#include "hdfi.h"

struct SCdata {
    uint8 fmt_id;
    uint8 mn_cnt;
    uint8 mj_cnt;
    uint32 sc_clk;
};
