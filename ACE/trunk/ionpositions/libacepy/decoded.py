"""
   ---------------------------------------------------------------------------
   adapted from decoded.h b< Lars Berger (berger@physik.uni-kiel.de)
   decoded.h --- define "expanded" SWICS/ACE and SWIMS/ACE data structure
   (c) 1998/1999 Simon Hefti (hefti@umich.edu)
   $Id: decoded.h,v 1.2 2003/11/09 12:50:32 jraines Exp $
   ------------------------------------------------------------------------ 

   ---------------------------------------------------------------------------
   conventions
   -----------
   X --> SWICS
   M --> SWIMS
   ...........
   N --> number of
   L --> Location (Position in array)
   ...........
   a --> array
   l --> long --> int32 in Python
   i --> int  
   s --> short --> int16 in Python
   b --> byte  --> uint8 in Python 

   TBC   --> to be checked
   Y2K   --> year 2000 bug (year encoded with two digits)
   FIXME --> expect a problem here
   -------------------------------------------------------------------------
"""


from datatypes import *
import datetime

DSTRUCTVER = 31                   # structure VERSION 

NBINEDB = 2436                    # bytes in EDB 
NBINDDB =  203                    # bytes in dummy EDB 
NSEC    =    8                    # number of sectors 
NEDB    =   60

# --- SWICS ---                      # number of ... 
NXEQ    =   60                    # .. SWICS E/q steps 
NXBR    =    4                    # .. basic rates 
NXPH    =  800                    # .. PHA words (maximal) 
NXMR    =    8                    # .. matrix rates 

NXBRBOX  =   8                    #  8 boxes are possible for 
					#    basic rates 
NXMRBOX  =  20                    # 20 for the matrix rates 

NEDBFRST =   7                    # first few bytes of EDB 

# --- SWIMS ---                      # number of ... 
NMPH        =  400                  # .. PHA words (maximal) 
NMEQ        =   60                  # .. E/q steps 
NMBR        =    4                  # .. basic rates (TBC) 
NMTOFHIST   = 1024                  # length of ToF histogram 
NMSTATUS    =    5                  # status bytes. No idea 
NMTOFPEREDB =   35                  # ToF bytes per EDB (2100/60) 

# ---------------------------------------------------------------------------
# find (L)ocations in array: sensor rates
# ------------------------------------------------------------------------ 
LXFSR = 5
LXDCR = 4
LXTCR = 3
LXSSR = 2
LXPR  = 1
LXAR  = 0

NXSR  = 6

# ---------------------------------------------------------------------------
# find (L)ocations in array: SWIMS sensor rates
# ------------------------------------------------------------------------ 
LMFSR   = 7 # start rate 
LMFSRA  = 6 # Stop Rate 
LMFSRB  = 5 # Stop Rate 
LMFSRAB = 4 # Stop Rate 
LMRSR   = 3 # start rate 
LMDCR   = 2 # double coincidence 
LMMFSR  = 1 # multiple start, one stop 
LMMDCR  = 0 # multiple stops, one start 

NMSR    = 8

# ---------------------------------------------------------------------------
# find (L)ocations in array: Telemetry allocation
# ------------------------------------------------------------------------ 
LDTLM     =  0
LDHK      =  1
LSHK      =  2
LMHK      =  3
LCHK      =  4
LSSTATUS  =  5
LSMATRIX  =  6
LSSECTOR  =  7
LSBASIC   =  8
LSMONITOR =  9
LMSTATUS  = 10
LMTOF     = 11
LMBASIC   = 12
LMMONITOR = 13
LCSTATUS  = 14
LCELEMENT = 15
LCBASIC   = 16
LCMONITOR = 17
LDSPARE   = 18
LSPHA     = 19
LMPHA     = 20
LCPHA     = 21
LSDIAG    = 22

NLOC      = 23 # locations 

LTLMPOS   =  0 # position (aspos[NXEQ][NLOC][ LTLMPOS ]) 
LTLMLEN   =  1 # length 

# ---------------------------------------------------------------------------
# find (L)ocations in array: S3DPU HK block
# Details from 'ACE S3DPU Command and Data Document'.
# ------------------------------------------------------------------------ 
LSSDVERSION      =   0
LSSDFLAGS        =   1
LSSDSPINART      =   1
LSSDSPINABSENT   =   1
LSSDSUNABSENT    =   1
LSSDMEMSCRUB     =   1
LSSDAUTOTLM      =   1
LSSDMPBIDENT     =   1
LSSDLUCNT        =   2
LSSDIDLECTR      =   3
LSSDJOB          =   4
LSSDSMODENEXT    =   5
LSSDSMODE        =   5
LSSDMMODENEXT    =   6
LSSDMMODE        =   6
LSSDCMODENEXT    =   7
LSSDCMODE        =   7
LSSDSPINCTR      =   8
LSSDRECORDCTR    =  11
LSSDMPOWER       =  14 
LSSDCPOWER       =  14
LSSDSPOWER       =  14
LSSDSUNSECTOR    =  14
LSSDSECTOR7LEN   =  15
LSSDSECTOR0LEN   =  17
LSSDSPINCLOCKS   =  19
LSSDTTMUX        =  21
LSSDTTSTATUS     =  23
LSSDLUSTROBE     =  24
LSSDLUMASK       =  26
LSSDOSCSTATE     =  28
LSSDLUSTATE      =  28
LSSDCLASSMUX3    =  30
LSSDCLASSMUX2    =  30
LSSDCLASSMUX1    =  30
LSSDCLASSMUX0    =  30
LSSDCMDOK        =  31
LSSDCMDERR       =  32
LSSDCMDHIST1     =  33
LSSDCMDHIST1ID   =  33
LSSDCMDHIST1TYPE =  34
LSSDCMDHIST1LEN  =  34
LSSDCMDHIST2     =  35
LSSDCMDHIST2ID   =  35
LSSDCMDHIST2TYPE =  36
LSSDCMDHIST2LEN  =  36
LSSDCMDHIST3     =  37
LSSDCMDHIST3ID   =  37
LSSDCMDHIST3TYPE =  38
LSSDCMDHIST3LEN  =  38
LSSDPARITYERR    =  39
LSSDSCMDERR      =  40
LSSDMCMDERR      =  41
LSSDCCMDERR      =  42
LSSDEEFILL       =  43
LSSDMEM0A        =  44
LSSDMEM0B        =  44
LSSDMEM1A        =  45
LSSDMEM1B        =  45
LSSDMEM2A        =  46
LSSDMEM2B        =  46
LSSDMEM3A        =  47
LSSDMEM3B        =  47

NDHK             =  48 # number of S3DPU HK block items 

# ---------------------------------------------------------------------------
# find (M)asks for each item: S3DPU HK block
# usage:  cyc.abs3dpuhk[ie][LSSDLUSTATE] & MSSDLUSTATE
# ------------------------------------------------------------------------ 
MSSDVERSION          = hex(0xff)
MSSDFLAGS            = hex(0x80)
MSSDSPINART          = hex(0x80)
MSSDSPINABSENT       = hex(0x40)
MSSDSUNABSENT        = hex(0x20)
MSSDMEMSCRUB         = hex(0x04)
MSSDAUTOTLM          = hex(0x02)
MSSDMPBIDENT         = hex(0x01)
MSSDLUCNT            = hex(0xff)
MSSDIDLECTR          = hex(0xff)
MSSDJOB              = hex(0xff)
MSSDSMODENEXT        = hex(0xf0)
MSSDSMODE            = hex(0x0f)
MSSDMMODENEXT        = hex(0xf0)
MSSDMMODE            = hex(0x0f)
MSSDCMODENEXT        = hex(0xf0)
MSSDCMODE            = hex(0x0f)
MSSDSPINCTR      = hex(0xffffff)
MSSDRECORDCTR    = hex(0xffffff)
MSSDMPOWER           = hex(0x80)
MSSDCPOWER           = hex(0x40)
MSSDSPOWER           = hex(0x20)
MSSDSUNSECTOR        = hex(0x1f)
MSSDSECTOR7LEN     = hex(0xffff)
MSSDSECTOR0LEN     = hex(0xffff)
MSSDSPINCLOCKS     = hex(0xffff)
MSSDTTMUX          = hex(0xffff)
MSSDTTSTATUS         = hex(0xff)
MSSDLUSTROBE       = hex(0x01ff)
MSSDLUMASK         = hex(0x01ff)
MSSDOSCSTATE         = hex(0x02)
MSSDLUSTATE        = hex(0x01ff)
MSSDCLASSMUX3        = hex(0xc0)
MSSDCLASSMUX2        = hex(0x30)
MSSDCLASSMUX1        = hex(0x0c)
MSSDCLASSMUX0        = hex(0x03)
MSSDCMDOK            = hex(0xff)
MSSDCMDERR           = hex(0xff)
MSSDCMDHIST1       = hex(0xffff)
MSSDCMDHIST1ID       = hex(0xff)
MSSDCMDHIST1TYPE     = hex(0xe0)
MSSDCMDHIST1LEN      = hex(0x1f)
MSSDCMDHIST2       = hex(0xffff)
MSSDCMDHIST2ID       = hex(0xff)
MSSDCMDHIST2TYPE     = hex(0xe0)
MSSDCMDHIST2LEN      = hex(0x1f)
MSSDCMDHIST3       = hex(0xffff)
MSSDCMDHIST3ID       = hex(0xff)
MSSDCMDHIST3TYPE     = hex(0xe0)
MSSDCMDHIST3LEN      = hex(0x1f)
MSSDPARITYERR        = hex(0xff)
MSSDSCMDERR          = hex(0xff)
MSSDMCMDERR          = hex(0xff)
MSSDCCMDERR          = hex(0xff)
MSSDEEFILL           = hex(0xff)
MSSDMEM0A            = hex(0xf0)
MSSDMEM0B            = hex(0x0f)
MSSDMEM1A            = hex(0xf0)
MSSDMEM1B            = hex(0x0f)
MSSDMEM2A            = hex(0xf0)
MSSDMEM2B            = hex(0x0f)
MSSDMEM3A            = hex(0xf0)
MSSDMEM3B            = hex(0x0f)

# ---------------------------------------------------------------------------
# find (L)ocations in array: SEPICA HK block
# Details from 'ACE S3DPU Command and Data Document'.
# The SHK block is commutated in 22 byte units over 5 EDBs.  See
# ------------------------------------------------------------------------ 
LSSSFAN1MODE  =  6  # 0 ->science 1->engineering 
LSSSFAN2MODE  =  8  # 0 ->science 1->engineering 
LSSSFAN3MODE  = 10  # 0 ->science 1->engineering 

NSHK          = 22
# ---------------------------------------------------------------------------
# find (M)asks for each item: S3DPU HK block
# usage:  cyc.abs3shk[ie][LSSDLUSTATE] & MSSDLUSTATE
# Many items are not identified here
# ------------------------------------------------------------------------ 
MSSSFAN1MODE  = hex(0x20)
MSSSFAN2MODE  = hex(0x20)
MSSSFAN3MODE  = hex(0x20)

# ---------------------------------------------------------------------------
# find (L)ocations in array: Corner Table
# ------------------------------------------------------------------------ 
LXQN     =  0 # minimal m/q 
LXQX     =  1 # maximal m/q 
LXMN     =  2 # minimal m 
LXMX     =  3 # maximal m 
LXBOX    =  4 # which range is defined by this box 

NCORN    =  5

# ---------------------------------------------------------------------------
# find (L)ocations in array: SWICS houbsekeeping
# ------------------------------------------------------------------------ 
LXGV28   =   0 # ground-referenced primary 28 V 
LXGV20   =   1 # 
LXGV10   =   2 # 
LXGV5P   =   3 # 
LXGV5M   =   4 # 
LXSPR1   =   5 # unused 
LXGTE1   =   6 # temperature 
LXGTE2   =   7 # 
LXGPI1   =   8 # ground ref. +28V current primary 
LXGPI2   =   9 # ground ref. +28V current secondary 
LXGI5P   =  10 # 
LXGI20   =  11 # 
LXGPAV   =  12 # post-acceleration 
LXSPR2   =  13 # unused 
LXGEOQ   =  14 # E/q of entrance system 
LXSPR3   =  15 # unused 
# PAPS-referenced 
LXPAC7   =  16 # 
LXPTE1   =  17 # temperature 
LXPTE2   =  18 # 
LXPV5P   =  19 # 
LXPI5P   =  20 # 
LXPV5M   =  21 # 
LXPI5M   =  22 # 
LXPMCP   =  23 # MCP voltage 
LXPGAI   =  24 # E/q GAIN 

NXHK     =  25  # number of SWICS HK entries 


# ---------------------------------------------------------------------------
# find (L)ocations in array: SWICS command
# ------------------------------------------------------------------------ 
LXTRIG   =   0 # Trigger mode 
LXMCPL   =   1 # MCP level 
LXTCAL   =   2 # T Cal, USS threshold 
LXECA1   =   3 # E cal 
LXECA2   =   4 # E cal 
LXETAC   =   5 # TAC slope 
LXSSDE   =   6 # SSD enables 
LXDPPS   =   7 # DPPS Level 
LXPAPS   =   8 # PAPS Level 
LXHVEN   =   9 # HV enables 

NXCMD    =  10  # ............... "command" bytes 

# ---------------------------------------------------------------------------
# find (L)ocations in array: SWIMS command
# ------------------------------------------------------------------------ 

LMAHYP   =  12 # Hyperbola Level (A for commAnd, not control) 
LMAMCO   =  13 # Stop  MCP Level (actually may be Start MCP) 
LMAMCA   =  14 # Start MCP Level 

NMCMD    =  20  # ............... "command" bytes 

# ---------------------------------------------------------------------------
# find (L)ocations in array: SWICS control
# ------------------------------------------------------------------------ 
LXLDPP   =   0 # DPPS Limit 
LXDDPP   =   1 # DPPS Delta 
LXLMCP   =   2 # MCP  Limit 
LXDMCP   =   3 # MCP  Delta 
LXLPAV   =   4 # PAPS Limit 
LXDPAV   =   5 # PAPS Delta 

NXCTRL   =  16  # ............... "control" bytes 

  # Note: 2 items in the CTRL block are currently not identified.
  # There are 2 x 8 bytes there, one block for the commanded control
  # bytes and one block for the active control bytes.
  # Add 8 to those indices to access the block with the currently
  # active bytes 

# find (L)ocations in array: SWIMS control 

NMCTRL   =  32  # ............... "control" bytes 

# ---------------------------------------------------------------------------
# find (L)ocations in array: SWIMS housekeeping
# ------------------------------------------------------------------------ 
LMGV28   =   0 # ground-referenced primary 28 V 
LMGV09   =   1 # 
LMGV5P   =   2 # 
LMGV5M   =   3 # 
LMGV12   =   4 # 
LMGTE1   =   5 # temperature 
LMGTE2   =   6 # temperature 
LMSPR1   =   7 # unused 
LMGPI1   =   8 # ground ref. +28V current primary 
LMGPI2   =   9 # ground ref. +28V current secondary 
LMGI5P   =  10 # 
LMSPR2   =  11 # unused 
LMSPR3   =  12 # unused 
LMSPR4   =  13 # unused 
LMGEOQ   =  14 # E/q of entrance system 
LMGV_F   =  16 # Vf (E/q is 16 bits)
# Vf-referenced 
LMVV28   =  18 # (Vf is 16 bits) 
LMVV09   =  19 # 
LMVV06   =  20 # 
LMVV5P   =  21 # 
LMVV5M   =  22 # 
LMVV12   =  23 # 
LMVTE1   =  24 # temperature 
LMVTE2   =  25 # "           
LMVI28   =  26 # 
LMVPI6   =  27 # 
LMVPI5   =  28 # 
LMVMI5   =  29 # 
LMVMCA   =  30 # start MCP 
LMSPR5   =  31 # unused 
LMVMCO   =  32 # stop MCP 
LMVHPS   =  33 # Hyperbola 
LMVSTA   =  34 # status 

NMHK     =  35  # number of SWIMS HK entries 

# ---------------------------------------------------------------------------
# DPU/Classification Parameters/CNQ
# ------------------------------------------------------------------------ 

LCNQTMIN = 0
LCNQTMAX = 1
LCNQCMIN = 2                     # Classification 
LCNQCMAX = 3
LCNQTOFF = 4                     # offset 
LCNQTDAC = 5
LCNQPOF1 = 6                     # PAPS conversion 1 
LCNQPOF2 = 7                      
LCNQPSL1 = 8                     # slope
LCNQPSL2 = 9
LCNQEOQ0 =10                     # E/q 
LCNQEOQ1 =11
LCNQCLA0 =12                     # Classification const 
LCNQCLA1 =13
LCNQCLA2 =14

NCNQ     =15

# ---------------------------------------------------------------------------
# DPU/Classification Parameters/CNM
# ------------------------------------------------------------------------ 

LCNMTMIN = 0
LCNMTMAX = 1
LCNMEMIN = 2
LCNMEMAX = 3
LCNMCMIN = 4                     # Classification 
LCNMCMAX = 5
LCNMTOFF = 6                     # offset 
LCNMEOFF = 7 
LCNMTDAC = 8
LCNMEDAC = 9
LCNMCLA0 =10                     # Classification const 
LCNMCLA1 =11
LCNMCLA2 =12
LCNMCLA3 =13
LCNMCLA4 =14
LCNMCLA5 =15

NCNM     =16

# ---------------------------------------------------------------------------
# Cycle
# ------------------------------------------------------------------------ 
class SBCYC(object):
    def __init__(self):
        # decoding HK 
        self.sver = int16(0)                        # data structure version 
        self.sdecomp_problem = int16(0)             # flag is if decompression caused problems 
        # information on EDB 
        self.abQAC=zeros(NEDB,BYTE)                 # QAC from L1 file 
        self.alNr=zeros(NEDB,int32)                  # long EDB number 
        self.adtime=zeros(NEDB,float64)           # so-called s/c readout time 
        self.adepoch=zeros(NEDB,float64)          # so-called epoch 
        self.abedbfrst=zeros((NEDB,NEDBFRST),BYTE)  # first few bytes of EDB 
        self.abgood=zeros(NEDB,BYTE)                # my QAC (use EDB only if 0) 
        # TOC 
        self.aspos=zeros((NXEQ,NLOC,2),int16)        # EDB,item,pos and length  

        # S3DPU HK block 
        self.abs3dpuhk=zeros((NEDB,NDHK),BYTE)

        # SEPICA HK block 
        self.abshk=zeros((NEDB,NSHK),BYTE)

        # SWICS rates 
        self.alxsr=zeros((NXEQ,NXSR,NSEC + 1),int32) # sensor rate 
                                               # EDB,rate,sector and sum  
        self.alxmr=zeros((NXEQ,NXMR,NSEC + 1),int32) # matrix rate  
        self.alxbr=zeros((NXEQ,NXBR,NSEC + 1),int32) # basic rate  
        # SWIMS rates 
        self.almsr=zeros((NMEQ,NMSR,NSEC + 1),int32) # sensor rate 
        self.almbr=zeros((NMEQ,NMBR,NSEC + 1),int32) # basic rate 
        # long     *almbr;
        # 
        self.lrecNr=int32(0)                      # record number 
        self.adcnm=zeros(NCNM,float64)           # SWICS classification 
        self.adcnq=zeros(NCNQ,float64)
        self.abxbrtab=zeros((NXBRBOX,NCORN),BYTE)# corner table of basic rates 
        self.abxmrtab=zeros((NXMRBOX,NCORN),BYTE)# ... matrix rates 
        self.abxeqtab=zeros(NXEQ,BYTE)           # SWICS E/q values of cycle 
        self.asmeqtab=zeros(NMEQ,int16)         # SWIMS E/q values of cycle 
        # SWICS PHA words 
        self.abxsec=zeros((NXEQ,NXPH),BYTE)      # sector 
        self.abxdid=zeros((NXEQ,NXPH),BYTE)      # ID as found in telemetry 
        self.abxesd=zeros((NXEQ,NXPH),BYTE)      # E_SSD 
        self.asxtof=zeros((NXEQ,NXPH),int16)     # TOF 
        self.abxrng=zeros((NXEQ,NXPH),BYTE)      # range as calculated off-line 
        self.asxNof=zeros(NXEQ,int16)            # number of PHAs in each EDB 
        self.asxnr=zeros((NXEQ,NXBR,NSEC + 1),int16) # PHA per range and sector 
        self.afxmas=zeros((NXEQ,NXPH),float32)   # classsified 
        self.afxmoq=zeros((NXEQ,NXPH),float32)   # classsified 
        self.afxwgt=zeros((NXEQ,NXBR,NSEC +1),float32)   # weights 
        # SWICS HK 
        self.afxhk=zeros((NXEQ,NXHK),float32)
        self.abxcmd=zeros(NXCMD,BYTE)
        self.abxctrl=zeros(NXCTRL,BYTE)
        self.fxpav=float32(0)             # DPU-value of PA voltage [kV] 
        self.afxeoqdpu=zeros(NXEQ,float32)# E/q from eqtab (DPU values) 
        self.afxeoqaux=zeros(NXEQ,float32)# AUX: E/q from eqtab (DPU values) 
        # SWIMS PHA words 
        self.abmsec=zeros((NMEQ,NMPH),BYTE)# sector 
        self.abmdid=zeros((NMEQ,NMPH),BYTE)# DPU-calculated range 
        self.asmsta=zeros((NMEQ,NMPH),int16)# Start Amplitude 
        self.asmak1=zeros((NMEQ,NMPH),int16)# Stop Amplitude K1 
        self.asmak2=zeros((NMEQ,NMPH),int16)# Stop Amplitude K2 
        self.asmtof=zeros((NMEQ,NMPH),int16)# TOF 
        self.asmNof=zeros(NMEQ,int16)       # number of PHAs in each EDB 
        self.asmnr=zeros((NMEQ,NMBR,NSEC + 1),int16)# PHA per range and sector 
        self.afmwgt=zeros((NMEQ,NMBR),float32)# weights 
        # histograms 
        self.almtof1=zeros(NMTOFHIST,int32)# time-of-fligh histogram of SWIMS 
        self.almtof2=zeros(NMTOFHIST,int32)
        # SWIMS HK 
        self.abmstatus=zeros(NMSTATUS,BYTE)# status bytes 
        self.afmhk=zeros((NMEQ,NMHK),float32)
        self.asmcmd=zeros(NMCMD,int16)
        self.abmctrl=zeros(NMCTRL,BYTE)
        self.afmeoqdpu=zeros(NMEQ,float32)# E/q from eqtab (DPU values) 


    def get_time(self):
        time = datetime.datetime.fromtimestamp(self.adtime[0])
        self.doy = time.day+time.hour/24.+time.minute/(24.*60.)+time.second/(24.*60.*60.)
        
    
    #def write_rates()
# ---------------------------------------------------------------------------
#
#  history
#  ---------------------------------------------------------------------------
#  struct version|changes
#     date       |
#  11 15-Jul-98  |added m and m/q to SWICS PHA arrays
#  ---------------------------------------------------------------------------
#
#  -------------------------------------------------------------------------
