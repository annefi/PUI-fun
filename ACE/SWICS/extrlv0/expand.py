#----------------------------------------------------------------------------
#   expand.c --- expand ACE EDB on-the-fly (in memory)
#   (c) 1998/1999 Simon Hefti (hefti@umich.edu)
#   $Id: expand.c,v 1.6 2004/05/20 14:58:18 jraines Exp $
#---------------------------------------------------------------------------- 

rcsid = "$Id: expand.c,v 1.6 2004/05/20 14:58:18 jraines Exp $"

from numpy import *
from decoded import *
from bittools import *
from asxdpusim import *
#include "acetools.h"

#  --------------------------------------------------------------------------
#    expand --- decode ACE EDB
#    Input:  array of bytes of 60 EDBs, corresponding time and QAC.
#    Output: Structure containing decoded data.
#  --------------------------------------------------------------------------
#int expand(BYTE abedb[NEDB][NBINEDB], double adtime[NEDB], 
#           BYTE abQAC[NEDB], SBCYC *pcyc)
def expand(abedb,adtime,abQAC,pcyc,debug=False,swics=True,swims=False,sepica=False,dpu=False):
  """  
  BYTE  *pabdum;
  CPHA  stcpha;
  MPHA  stmpha;

  long  ltmp;
  """
  if debug:
    print "DBG expand --- Starting.\n"

  # -------------------------------------------------------------------------
  # reset cyc
  # -------------------------------------------------------------------------

  # reset cyc wird nicht benoetigt da class SBCYC auf null initialisiert wird!
  # print ("DBG expand --- sizeof(cyc) = %d.\n",sizeof(*pcyc)); */
  # memset(pcyc,0,sizeof(*pcyc));

  # test whether data is resetted 

  for ie in range(NEDB):
      if (pcyc.asxNof[ie] != 0) or (pcyc.asxnr[ie][1][NSEC] != 0):
        if debug:
          print "expand --- cyc not properly resetted !\n"

  # -------------------------------------------------------------------------
  # copy information from L1 file
  # -------------------------------------------------------------------------

  for ie in range(NEDB):
      pcyc.abQAC[ie] = abQAC[ie]
      pcyc.adtime[ie] = adtime[ie]
      # copy first few bytes 
      for i in range(NEDBFRST):
          pcyc.abedbfrst[ie][i] = abedb[ie][i]

      #printf("DBG: first few bytes of EDB %2d: ",ie);
      #for(i = 0; i < NEDBFRST; i++) printf("%2.2x ",abedb[ie][i]);
      #printf("\n");
      #for(i = 0; i < NEDBFRST; i++) printf("%2.2x ",pcyc->abedbfrst[ie][i]);
      #printf("\n");
    

  # -------------------------------------------------------------------------
  # loop over EDBs
  # -----------------------------------------------------------------------*/

  for ie in range(NEDB):
    if debug:
      print "DBG expand --- EDB %d.\n"%(ie)

    # -----------------------------------------------------------------------
    # check sync word and EDB number
    # -----------------------------------------------------------------------

    if ((abQAC[ie]    == 0 ) and (hex(uint8(abedb[ie][0])) == "0xeb" ) and (hex(uint8(abedb[ie][1])) == "0x90") and (hex(uint8(abedb[ie][2])) == "0xda") and (abedb[ie][5] == ie)): # QAC/sync/number 
      # --- everything is fine --- */

      # printf("expand --- ie: %2d %2.2x %2.2x %2.2x\n",
      #       ie,abedb[ie][0],abedb[ie][1],abedb[ie][2]);
      
      
      # -------------------------------------------------------------------
      # for now we assume: usefull data
      # -------------------------------------------------------------------

      pcyc.abgood[ie] = 0

      # -------------------------------------------------------------------
      # get EDB structure
      # -------------------------------------------------------------------

      gedbpos(abedb[ie],pcyc.aspos[ie])

      # -------------------------------------------------------------------
      # get long EDB number
      # -------------------------------------------------------------------

      # printf("DBG expand --- get EDB number.\n");

      itmp         = 34
      pcyc.lrecNr = int32((abedb[ie,itmp+11] << 16) | (abedb[ie,itmp+12] <<  8) | (abedb[ie,itmp+13]))
      pcyc.alNr[ie] = pcyc.lrecNr * int32(60) + int32(ie);

      if debug:
        print "DBG expand --- recNr: %ld %ld\n"%(pcyc.lrecNr,pcyc.alNr[ie])

      # -------------------------------------------------------------------
      # get S3DPU HK block
      # -------------------------------------------------------------------
      
      if dpu:
        for i in range(NDHK):
          itmp = abedb[ie,pcyc.aspos[ie,LDHK,0] +  i]
          pcyc.abs3dpuhk[ie,i] = BYTE(itmp)
          

      # -------------------------------------------------------------------
      # get SEPICA HK block
      # -------------------------------------------------------------------
      # Block is commutated in NSHK (22) byte chunks over 5 EDBs.
      # -------------------------------------------------------------------

      if sepica:
        for i in range(NSHK):
          itmp = abedb[ie,pcyc.aspos[ie,LSHK,0] +  i]
          # pcyc->abshk[ie][i + (ie % 5)*NSHKPEREDB] = (BYTE)itmp;
          pcyc.abshk[ie,i] = BYTE(itmp)
      

      # -------------------------------------------------------------------
      # get SWICS/Eqtab (E/q CMD values from DPU spare block)
      # -------------------------------------------------------------------

      if ie==46 and swics:
          for i in range(NXEQ):
              itmp = abedb[ie,pcyc.aspos[ie,LDSPARE,0] +  i]
              # account for missing bits 
              if (itmp > 127):
                  itmp -= 103
              # reverse order 
              pcyc.abxeqtab[i] = BYTE(itmp)
          ### DEBUG FIXME    
          # pcyc.abxeqtab= array([10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48,50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88,90, 92, 94, 96, 98,100,102,104,108,112,116,120,124,128,132,136,140,144,148,152])

      # -------------------------------------------------------------------
      # get SWIMS/Eqtab (E/q CMD values from DPU spare block)
      # -------------------------------------------------------------------


      if ((ie == 35) or (ie == 36)) and swims:

        ipos = pcyc.aspos[ie,LDSPARE,LTLMPOS]

        for i in range(30):
          ltmp = 0
          ltmp = (abedb[ie,ipos +  i*2] << 8) | (abedb[ie,ipos +  i*2 + 1])
          pcyc.asmeqtab[i + (ie == 35) * 30] = int16(ltmp)


      # -------------------------------------------------------------------
      # get SWICS CMD block (PAPS command level)
      # -------------------------------------------------------------------
      if ((ie == 22) or (ie == 42)) and swics:
          for i in range(NXCMD):
            pcyc.abxcmd[i] = abedb[ie,pcyc.aspos[ie,LDSPARE,LTLMPOS] +  i]
              

      # -------------------------------------------------------------------
      # get SWIMS CMD block
      # -------------------------------------------------------------------
      if ((ie == 21) or (ie == 41)) and swims:
          for i in range(14):
              pcyc.asmcmd[i] = abedb[ie,pcyc.aspos[ie,LDSPARE,LTLMPOS] + i]
          for i in range(14,NMCMD):
              pcyc.asmcmd[i] = abedb[ie,pcyc.aspos[ie,LDSPARE,LTLMPOS] + i]


      # -------------------------------------------------------------------
      # get SWIMS Status bytes
      # -------------------------------------------------------------------
      if swims:
        for i in range(NMSTATUS):
          pcyc.abmstatus[i] = abedb[ie,pcyc.aspos[ie,LMSTATUS,LTLMPOS] + i]
          

      # -------------------------------------------------------------------
      # get SWICS CTRL block (limits and deltas)
      # -------------------------------------------------------------------
      if ((ie == 25) or (ie ==45)) and swics:
          for i in range(NXCTRL):
              pcyc.abxctrl[i] = abedb[ie,pcyc.aspos[ie,LDSPARE,LTLMPOS] +  i]


      # -------------------------------------------------------------------
      # get SWIMS CTRL block (limits and deltas)
      # -------------------------------------------------------------------

      if ((ie == 24) or (ie == 44)) and swims:
          for i in range(NMCTRL):
              pcyc.abmctrl[i] = abedb[ie,pcyc.aspos[ie,LDSPARE,LTLMPOS] +  i]

      # -------------------------------------------------------------------
      # SWICS HK
      # -------------------------------------------------------------------

      if swics:
        for i in range(NXHK):
          pcyc.afxhk[ie,i] = float32(abedb[ie,pcyc.aspos[ie,LCHK,0] +  i])

        # PAPS
        pcyc.afxhk[ie,LXGPAV] = float32(abedb[ie,pcyc.aspos[ie,LCHK,0] +  LXGPAV] * 0.150)

        # MCP 
        pcyc.afxhk[ie,LXPMCP] = -4.94370 + float32(abedb[ie,pcyc.aspos[ie,LCHK,0] +  LXPMCP] * 0.03905)

        # main current 
        pcyc.afxhk[ie,LXGPI1] = float32(abedb[ie,pcyc.aspos[ie,LCHK,0] +  LXGPI1] * 2.0)

        # Temp 
        pcyc.afxhk[ie,LXGTE1] = convTmp(abedb[ie,pcyc.aspos[ie,LCHK,0] +  LXGTE1])

        pcyc.afxhk[ie,LXGTE2] = convTmp(abedb[ie,pcyc.aspos[ie,LCHK,0] +  LXGTE2])

        pcyc.afxhk[ie,LXPTE1] = convTmp2(abedb[ie,pcyc.aspos[ie,LCHK,0] + LXPTE1])

        pcyc.afxhk[ie,LXPTE2] = convTmp2(abedb[ie,pcyc.aspos[ie,LCHK,0] + LXPTE2])


        # --- E/q --- 

        # gain bit 

        if (abedb[ie,pcyc.aspos[ie,LCHK,0]+24] & 0001):
          pcyc.afxhk[ie,LXGEOQ] *= 50.0
        else:
          pcyc.afxhk[ie,LXGEOQ] *=  6.25

      #  -------------------------------------------------------------------
      # SWICS Sensor Rates (FSR,DCR etc)
      # --------------------------------------------------------------------

      # --- get position of Sensor Rates in EDB --- 


      # according to a3dif and decoded the rates are as follows
      # Rate0 Alpha Rate from AUX Channel
      # Rate1 Proton Rate from AUX Channel
      # Rate2 SSD
      # Rate3 TCR
      # Rate4 DCR
      # Rate5 FSR
      # LB, 13.09.16
      
      if swics:
        ipos = pcyc.aspos[ie,LCMONITOR,LTLMPOS]

        for i in range(NXSR):
          pcyc.alxsr[ie,i,NSEC] = 0

          # sectors 

          for j in range(NSEC):
            ltmp = decmpa(abedb[ie,ipos + i*8 + j])
            # 26.10.16 Lars Berger
            # Looked at the 8Bit compressed values! (Found that 207 ~63488 is max value ! Looks like 16 Bit register is used on board for counters and overrun occurs (DCR > FSR)!
            # ltmp = abedb[ie,ipos + i*8 + j]
            if (ltmp < 0):
              ltmp = 0
              if debug:
                print "expand --- Decomp. Problem for SWICS SR %d, sec %d\n"%(i,j)
              pcyc.sdecomp_problem+=1

            pcyc.alxsr[ie,i,NSEC - 1 - j] = ltmp
            # sector inverted (by subtracting from 7) to align
            # max. sector from SR and PHA.  Also corresponds with 
            # info from Mark Popecki (UNH, Sepica) that the sun pulse
            # occurs at the end of sector 7, 135 deg after S/C +X
            # crosses Earth-Sun line.
            #
            #   J. Raines, 8Oct2002

            pcyc.alxsr[ie,i,NSEC] += pcyc.alxsr[ie,i,NSEC-1-j]


      # -------------------------------------------------------------------
      # SWIMS Sensor Rates (FSR etc)
      # -------------------------------------------------------------------

      if swims:
        ipos = pcyc.aspos[ie,LMMONITOR,LTLMPOS]

        for i in range(NMSR):
          if debug:
            print "DBG expand --- trying on SWIMS rate %d\n"%(i)

          pcyc.almsr[ie,i,NSEC] = 0

          for j in range(8):

            ltmp = decmpa(abedb[ie,ipos + i*8 + j])

            if ltmp<0:
              ltmp = 0
              pcyc.sdecomp_problem+=1
              if debug:
                  print "expand --- Decomp. Problem for SWIMS rate %d, sec %d\n"%(i,j)

            pcyc.almsr[ie,i,j] = ltmp
            # pcyc->almsr[ie][i][NSEC] += pcyc->almsr[ie][LMFSR][j];
            pcyc.almsr[ie,i,NSEC] += pcyc.almsr[ie,i,j]

      # -------------------------------------------------------------------
      # get DPU classification parameters: SWICS/mass
      # -------------------------------------------------------------------

      if (ie == 53) and swics:
        vxmascla(abedb[ie],pcyc)

      # -------------------------------------------------------------------
      # get DPU classification parameters: SWICS/m/q
      # -------------------------------------------------------------------

      if (ie == 54) and swics:
        vxmoqcla(abedb[ie],pcyc)

      # -------------------------------------------------------------------
      # get SWICS basic rates corners
      # -------------------------------------------------------------------

      if (ie == 47) and swics:
        vxbrtab(abedb[ie],pcyc)

      # -------------------------------------------------------------------
      # get SWICS matrix rates corners
      # -------------------------------------------------------------------

      if ((ie == 48) or (ie == 49)) and swics:
        vxmrtab(abedb[ie],pcyc)

      # -------------------------------------------------------------------
      # get SWICS PHA
      # -------------------------------------------------------------------

      if swics:
        itmp = int(pcyc.aspos[ie,LCPHA,LTLMLEN] / 3)
        pcyc.asxNof[ie] = int16(itmp)

        for i in range(pcyc.asxNof[ie]):
          ipos   = pcyc.aspos[ie,LCPHA,LTLMPOS] + pcyc.aspos[ie,LCPHA,LTLMLEN] - 3 - i*3

          # FIXME ?
          # pabdum = &(abedb[ie][ipos]);


          RANGE,SECTOR,ESSD,TOF=deccpha(abedb[ie][ipos:ipos+3])

          # RANGE is 3 Bit which most likely contain a mixture of priority range and dectector id
          # RANGE 6: Priority range 2
          # RANGE 1,3,5 : Priority range 1, Detector Id 0,1,2
          # RANGE 0,2 : Priority range 0, Detector Id 0,1
          # Range 4 : Priority range 0, Detector Id 2 if ESSD > 0, else Priority range 0, and dummy did val = 7 (not -1 because of uint) 
          # RANGE 7 -> Error Range Tof <70 or Tof =>1023, Most probably Priority range 3, and dymmy did val = 7

          pcyc.abxsec[ie,i] = BYTE(SECTOR)
          pcyc.abxdid[ie,i] = BYTE(RANGE)   # Dectetor ID oder Range???

          if (RANGE == 0) or (RANGE == 2) or (RANGE == 4): 
            pcyc.abxrng[ie,i] = BYTE(0)
          elif (RANGE == 1) or (RANGE == 3) or (RANGE == 5):
            pcyc.abxrng[ie,i] = BYTE(1)
          elif (RANGE == 6):
            pcyc.abxrng[ie,i] = BYTE(2)
          elif (RANGE == 7):
            pcyc.abxrng[ie,i] = BYTE(3)

          if (RANGE == 0) or (RANGE == 1):
            pcyc.abxdid[ie,i] = BYTE(0)
          elif (RANGE == 2) or (RANGE == 3):
            pcyc.abxdid[ie,i] = BYTE(1)
          elif ((RANGE == 4) and ESSD>0) or (RANGE == 5):
            pcyc.abxdid[ie,i] = BYTE(2)
          else:
            pcyc.abxdid[ie,i] = BYTE(7)
          pcyc.abxesd[ie,i] = BYTE(ESSD)
          pcyc.asxtof[ie,i] = int16(TOF)


      # -------------------------------------------------------------------
      # SWICS Matrix and Basic Rates
      # -------------------------------------------------------------------

      # Matrix Rates to a3dif.c
      # 0 H+
      # 1 He2+
      # 2 He+
      # 3 O7+
      # 4 O6+
      # 5 Fe ???
      # 6 Si ??? possible that Fe and Si are switched a3dif seems inconsistend here ???
      # 7 Err ??? Whatever Err means here
      # 26.10.16 Lars Berger

      
      if swics:
        ipos =  pcyc.aspos[ie,LCBASIC,LTLMPOS]

        if debug:
          print "expand -D- trying other decomp. codes for MR\n"
        for i in range(NXMR):  # loop rates 

          pcyc.alxmr[ie,NXMR-1-i,NSEC] = 0

          for j in range(NSEC):  # loop sectors 

            ltmp = decmpc(abedb[ie,ipos + i*NSEC + j])
            if (ltmp < 0):
              ltmp = 0
              if debug:
                print "expand --- Decomp. Problem for SWICS MR %d, sec %d\n"%(i,j)
              pcyc.sdecomp_problem+=1
            pcyc.alxmr[ie,NXMR-1-i,NSEC-1-j] = ltmp # back to
                                                    # orig. JR, 8Oct2002
            # sum 
            pcyc.alxmr[ie,NXMR-1-i,NSEC] += ltmp

        # basic rates 

        for i in range(NXBR):  # loop rates 

          # reset sum 
          pcyc.alxbr[ie,NXBR-1-i,NSEC] = 0

          for j in range(NSEC): # loop sectors 

            ltmp = decmpa(abedb[ie,ipos + (i+NXMR)*NSEC + j])

            # Note: NXMR is correct here -----^
            # SWICS has 4 * 8 Basic Rates and 8 * 8 Matrix Rates
                # ( = 96) in one block called "C_Basic" */
            if (ltmp < 0):
              ltmp = 0
              if debug:
                print "expand --- Decomp. Problem for SWICS BR %d, sec %d\n"%(i,j)
              pcyc.sdecomp_problem+=1
            pcyc.alxbr[ie,NXBR-1-i,NSEC-1-j] = ltmp #  back to
                                                    #  orig. JR, 8Oct2002

            # sum */
            pcyc.alxbr[ie,NXBR-1-i,NSEC] += ltmp

      # -------------------------------------------------------------------
      # get SWIMS TOF histograms
      # -------------------------------------------------------------------
      # SWIMS Histograms always produce decomp errors for certain ie(step) and i
        
      if ((ie > 0) and (ie < 30)) and swims:
        for i in range(NMTOFPEREDB):
            # Note: I just _assume_ that SWIMS uses Decompr. Code A. 
            ltmp = decmpa(abedb[ie,pcyc.aspos[ie,LMTOF,LTLMPOS] + i + ie * NMTOFPEREDB])
            pcyc.almtof1[i] = ltmp

      if ((ie >= 30) and (ie < 60)) and swims:
        for i in range(NMTOFPEREDB):
            # Note: I just _assume_ that SWIMS uses Decompr. Code A. 
            ltmp = decmpa(abedb[ie,pcyc.aspos[ie,LMTOF,LTLMPOS] + i + (ie-30) * NMTOFPEREDB])
            pcyc.almtof2[i] = ltmp

      # -------------------------------------------------------------------
      # SWIMS Basic Rates
      # -------------------------------------------------------------------

      # print "DBG expand --- Starting to access SWIMS BR.\n")

      if swims:
        ipos =  pcyc.aspos[ie,LMBASIC,LTLMPOS]


        for i in range(NMBR):  # loop rates 

          # reset sum 

          pcyc.almbr[ie,NMBR-1-i,NSEC] = 0L

          for j in range(NSEC):  # loop sectors 

            # print "DBG expand --- EDB %2d BR %1d SEC %1d ipos %3d pos %3d.\n"%(ie,i,j,ipos,ipos + i * NSEC + j)

            ltmp = decmpa(abedb[ie,ipos + i * NSEC + j])

            # Note: I just _assume_ that SWIMS uses Decompr. Code A. 

            if (ltmp < 0):
              ltmp = 0
              if debug:
                  print "expand --- Decomp. Problem for SWIMS BR %d, sec %d\n"%(i,j)
              pcyc.sdecomp_problem+=1

              pcyc.almbr[ie,NMBR-1-i,NSEC-1-j] = ltmp
              # sum 
              pcyc.almbr[ie,NMBR-1-i,NSEC]    += ltmp

      # -------------------------------------------------------------------
      # get SWIMS HK
      # -------------------------------------------------------------------

      if swims:
        # Hyperbola 
        pcyc.afmhk[ie,LMVHPS] = float32(abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMVHPS] * 0.150)

        # MCPs 
        pcyc.afmhk[ie,LMVMCA] = float32(abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMVMCA] * 15.0e-3)

        pcyc.afmhk[ie,LMVMCO] = float32(abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMVMCO] * 15.0e-3)


        # Vf  
        ltmp = 0
        ltmp = (abedb[ie,pcyc.aspos[ie,LMHK,0] + LMGV_F + 0] << 8) | (abedb[ie,pcyc.aspos[ie,LMHK,0] + LMGV_F + 1])

        ltmp = getbits(ltmp,0+16,12)

        pcyc.afmhk[ie,LMGV_F] = - 5.0 + float32(ltmp * 0.00244140625)

        # main current 
        pcyc.afmhk[ie,LMGPI1] = float32(abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMGPI1] * 2.0)

        # Temp 
        pcyc.afmhk[ie,LMGTE1] = convTmp(abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMGTE1])

        pcyc.afmhk[ie,LMGTE2] = convTmp(abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMGTE2])

        pcyc.afmhk[ie,LMVTE1] = convTmp(abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMVTE1])

        pcyc.afmhk[ie,LMVTE2] = convTmp(abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMVTE2])


      # -------------------------------------------------------------------
      # get SWIMS PHA
      # -------------------------------------------------------------------

      if swims:
        itmp = int(pcyc.aspos[ie,LMPHA,LTLMLEN] / 6)
        pcyc.asmNof[ie] = int16(itmp)

        for i in range(pcyc.asmNof[ie]):

          ipos   = pcyc.aspos[ie,LMPHA,LTLMPOS] + pcyc.aspos[ie,LMPHA,LTLMLEN] - 6 - i*6

          # === W R O N G ===
          #
          # ipos   = pcyc->aspos[ie][LMPHA][LTLMPOS] + i*6;
          #


          RANGE,SECTOR,AMP,K1,K2,TOF=decmpha(abedb[ie][ipos:ipos+6])

          pcyc.abmsec[ie,i] = BYTE(SECTOR)
          pcyc.abmdid[ie,i] = BYTE(RANGE)
          pcyc.asmsta[ie,i] = short(AMP)
          pcyc.asmak1[ie,i] = short(K1)
          pcyc.asmak2[ie,i] = short(K2)
          pcyc.asmtof[ie,i] = short(TOF)


  # -------------------------------------------------------------------------
  # SWICS E/q
  # -------------------------------------------------------------------------

  if swics:
    for ie in range(NXEQ):
      pcyc.afxeoqdpu[NXEQ-1-ie] = dswxeoq(ie,pcyc.abxeqtab,pcyc.adcnq)

    for ie in range(NXEQ):
      pcyc.afxeoqaux[NXEQ-1-ie] = pcyc.afxeoqdpu[NXEQ-1-ie] / 4.15

  # -------------------------------------------------------------------------
  # SWICS PAPS
  # -------------------------------------------------------------------------

  if swics:
    pcyc.fxpav = dswxpal(pcyc.abxcmd[LXPAPS],0,pcyc.adcnq)

  # -------------------------------------------------------------------------
  # SWIMS E/q
  # -------------------------------------------------------------------------

  if swims:
    for ie in range(NMEQ):
      # from HK 
      itmp =  abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMGEOQ + 0] * 16 + (abedb[ie,pcyc.aspos[ie,LMHK,0] +  LMGEOQ + 1]/16 and 15)
      pcyc.afmhk[ie,LMGEOQ] = 2.975 * itmp

      # from eqtab (DPU values) 
      pcyc.afmeoqdpu[ie] = 1.0e-3 * (69.8 + 0.119 * float64(pcyc.asmeqtab[ie] + 0.048 * sqrt(float64(pcyc.asmeqtab[ie]))))
                                                          
  # -------------------------------------------------------------------------
  # classify SWICS PHA
  # -------------------------------------------------------------------------

  if swics:
    vxclassify(pcyc)

  # -------------------------------------------------------------------------
  # weighting with Basic Rates (SWICS)
  # -------------------------------------------------------------------------
  if swics:
    for ie in range(NXEQ):
      for i in range(NXBR):
        for s in range(NSEC + 1):
          pcyc.afxwgt[ie,i,s] = 0.0

          if (pcyc.asxnr[ie,i,s] > 0):
            pcyc.afxwgt[ie,i,s] = float32(pcyc.alxbr[ie,i,s])/float32(pcyc.asxnr[ie,i,s])

  # -------------------------------------------------------------------------
  #  SWIMS: count PHA's in each range
  #  ------------------------------------------------------------------------ 

  # print "DBG expand --- Start SWIMS PHA counting.\n"

  if swims:
    for ie in range(NMEQ):

      # .......................................................................
      #  reset
      #  ......................................................................
      for i in range(NMBR):
        for j in range(NSEC):
          pcyc.asmnr[ie,i,j] = 0

      # .......................................................................
      #  count
      # .......................................................................


      for j in range(pcyc.asmNof[ie]):
        itmp = int(pcyc.abmdid[ie,j]) # BR range
        isec = int(pcyc.abmsec[ie,j]) # sector

        if ((itmp >= 0) and (itmp < 4)):
          if ((isec >= 0) and (isec < 8)):
            pcyc.asmnr[ie,itmp,isec]+=1
            pcyc.asmnr[ie,itmp,NSEC]+=1 # NSEC holds sum over sectors 
          else:
            if debug:
              print "expand --- Problem with SWIMS BR weight (sector OOR).\n"
              print "           sector %d.\n"%(itmp)


        else:
          if debug:
            print "expand --- Problem with SWIMS BR weight (range OOR).\n"
            print "           range %d.\n"%(itmp)


  # print "DBG expand --- Start SWIMS BR weight.\n"

  # -------------------------------------------------------------------------
  #  weighting with Basic Rates (SWIMS)
  # ------------------------------------------------------------------------- 

  if swims:
    for ie in range(NMEQ):
      for i in range(NMBR):
        pcyc.afmwgt[ie,i] = 0.0

        if (pcyc.asmnr[ie,i,NSEC] > 0):
          pcyc.afmwgt[ie,i] = float32(pcyc.almbr[ie,i,NSEC]) / float32(pcyc.asmnr[ie,i,NSEC])

  return 0

#  --------------------------------------------------------------------------
#    Function: ddpudbl
#    Synopsis: represent DPU variable as double
#  --------------------------------------------------------------------------


def ddpudbl(idx,abedb,dconv):

  ltmp = int32((abedb[idx + 0] << 24) | (abedb[idx + 1] << 16) | (abedb[idx + 2] <<  8) | (abedb[idx + 3]))

  dres = int32(ltmp) / float(int32(1) << 16) / dconv

  return float64(dres)

#  --------------------------------------------------------------------------
#    Function: vxclassify
#    Synopsis: classify SWICS PHA data using DPU simulator
#  --------------------------------------------------------------------------
def vxclassify(pcyc):
  ie = 0
  j  = 0
  k  = 0
  itmp = 0
  isec = 0
  bstp = BYTE(0)
  bmas = BYTE(0)
  bmoq = BYTE(0)

  dpav=float64(0.)
  deoq=float64(0.)
  dw=float64(0.)

  # -------------------------------------------------------------------
  # SWICS PHA classification
  # -------------------------------------------------------------------

  dpav = dswxpal(pcyc.abxcmd[LXPAPS],0,pcyc.adcnq)
  for ie in range(NXEQ): # loop EDBs (ie) 
    if (pcyc.asxNof[ie]): # there are PHAs
      bstp = 59 - BYTE((ie + NXEQ - 1) % NXEQ)

      deoq = dswxeoq(bstp,pcyc.abxeqtab, pcyc.adcnq)
      
      dw   = dpav + deoq

      if (dw > 0.0): # prevent ln(0) 
        dw = log(dw)
        for j in range(pcyc.asxNof[ie]): # loop words (j) 

          pcyc.afxmoq[ie,j] = dswxlnmq(dw,pcyc.asxtof[ie,j],pcyc.adcnq)

          pcyc.afxmas[ie,j] = dswxlnm(pcyc.asxtof[ie,j],pcyc.abxesd[ie,j],pcyc.adcnm)

          bmoq = BYTE(pcyc.afxmoq[ie,j])
          bmas = BYTE(pcyc.afxmas[ie,j])

          # --- Range --- 
          
          # according to Reiche ranges are always "inclusive".
          # --- Tel, 14-Apr-1998 


          """
          # Error Range 

          for k in range(NXBRBOX-1,-1,-1):
            itmp = pcyc.abxbrtab[k,LXBOX]
            if (itmp != 255):

              # 255 is "void" code 

              if ((bmas >= pcyc.abxbrtab[k,LXMN]) and (bmas <= pcyc.abxbrtab[k,LXMX]) and (bmoq >= pcyc.abxbrtab[k,LXQN]) and (bmoq <= pcyc.abxbrtab[k,LXQX]) ):
                fout.write("%i\t%i\tbmas = %i, bmoq = %i, itmp = %i\n"%(ie, j,bmas,bmoq,itmp))
                pcyc.abxrng[ie,j] = itmp
          """
        # -------------------------------------------------------------------
        # count PHA's in each range
        # -------------------------------------------------------------------

        for k in range(NXBR):
          for j in range(NSEC+1):
            pcyc.asxnr[ie,k,j] = 0

        for j in range(pcyc.asxNof[ie]):
          itmp = int(pcyc.abxrng[ie,j])
          isec = int(pcyc.abxsec[ie,j])
          pcyc.asxnr[ie,itmp,isec]+=1
          pcyc.asxnr[ie,itmp,NSEC]+=1 # NSEC holds sum over sectors 
  #print "expand.c --- classification done.\n"
  return

#  --------------------------------------------------------------------------
#    Function: g3edbpos
#    Synopsis: Get structure of ACE/S3 EDB
#  --------------------------------------------------------------------------

def gedbpos(abedb,aspos):

    # length 
    for i in range(18):
        aspos[i,1] = int16(abedb[i+6])
    for i in range(5):
        itmp=0
        itmp = (abedb[6+18+i*2] << 8) | abedb[6+18+i*2+1]
        aspos[i+18,1] = int16(itmp)
    # position 
    aspos[0,0] = 6
    for i in range(1,NLOC):
        aspos[i,0] = aspos[i-1,0] + aspos[i-1,1]

    # checksum 
    itmp = 6
    for i in range(NLOC):
        itmp += aspos[i,1]
    if (itmp != NBINEDB):
        print "W:gedbpos:EDB has unexpected length %d\n"%(itmp)
  
    return

#  --------------------------------------------------------------------------
#    Function: vxmascla
#    Synopsis: get DPU classification parameters: SWICS/mass
#    ------------------------------------------------------------------------*/
def vxmascla(abedb,pcyc):
  if (abedb[5] == 53):

    ipos = pcyc.aspos[abedb[5],LDSPARE,LTLMPOS]

    for i in range(6):
      itmp  = ipos + 4*i
      pcyc.adcnm[LCNMCLA5 - i] = ddpudbl(itmp,abedb,1.0)
      # used to be:  ddpudbl(itmp,abedb,S3DPULNM);
      # which results in "human readable" units, but
      # we need do remain in the DPU units domain */

    for i in range(6):
      itmp  = ipos + 4*i + 24
      pcyc.adcnm[LCNMEDAC - i] = ddpudbl(itmp,abedb,1.0)
    for i in range(4):
      itmp  =  ipos + 2*i + 48
      ltmp = 0L
      ltmp = (abedb[itmp] << 8) | abedb[itmp + 1]
      pcyc.adcnm[LCNMEMAX - i] = float64(ltmp)
  else: 
    print "W:vxmascla:Wrong EDB taken (%2d/%2d)\n"%(abedb[5],53)
  return


#  --------------------------------------------------------------------------
#    Function: vxmoqcla
#    Synopsis: get DPU classification parameters: SWICS/m/q
#  --------------------------------------------------------------------------
def vxmoqcla(abedb,pcyc):
  if (abedb[5] == 54):
    ipos = pcyc.aspos[abedb[5],LDSPARE,LTLMPOS]
    for i in range(3):
      itmp  = ipos + 4*i
      pcyc.adcnq[LCNQCLA2 - i] = ddpudbl(itmp,abedb,1.0)
      # used to be:  ddpudbl(itmp,abedb,S3DPULNQ)
      # which results in "human readable" units, but
      # we need do remain in the DPU units domain 
      ### I don't understand this comment ! The values as now from ddpudbl(itmp,abedb,1.0) are human readable???? - Lars Berger
    for i in range(10):
      itmp  = ipos + 4*i + 12
      pcyc.adcnq[LCNQEOQ1 - i] = ddpudbl(itmp,abedb,1.0)

    for i in range(2):
      itmp =  ipos + 2*i + 52
      ltmp = 0L
      ltmp = (abedb[itmp] << 8) | abedb[itmp + 1]
      pcyc.adcnq[LCNQTMAX - i] = float64(ltmp)
  else:
    print "W:vxmoqcla:Wrong EDB taken (%2d/%2d)\n"%(abedb[5],54)
  return

#  --------------------------------------------------------------------------
#    Function: vxbrtab
#    Synopsis: get SWICS basic rates corners
#  --------------------------------------------------------------------------
def vxbrtab(abedb,pcyc):
  if (abedb[5] == 47):

    # reset 

    for j in range(NXBRBOX):
      pcyc.abxbrtab[j,LXBOX] = 255
      pcyc.abxbrtab[j,LXMX]  = 255
      pcyc.abxbrtab[j,LXQX]  = 255
      pcyc.abxbrtab[j,LXMN]  = 255
      pcyc.abxbrtab[j,LXQN]  = 255

    itab = 0

    # loop over all bytes in DSpare, even though only 8 entries
    # are used 

    # 10 possible values in 60 bytes 
    for i in range(9):
      ipos =  pcyc.aspos[abedb[5],LDSPARE,LTLMPOS]

      itmp = 0
      itmp = (abedb[ipos + i*6 + 0] << 8) | (abedb[ipos + i*6 + 1])

      # itmp is the table entry. BR entries are located
      # in positins 8..15 

      if ((itmp>=8) and (itmp < (8+NXBRBOX))):
        itmp -= 8
        pcyc.abxbrtab[itab,LXBOX] = itmp
        pcyc.abxbrtab[itab,LXMX]  = abedb[ipos + i*6 + 2 + 0]
        pcyc.abxbrtab[itab,LXQX]  = abedb[ipos + i*6 + 2 + 1]
        pcyc.abxbrtab[itab,LXMN]  = abedb[ipos + i*6 + 2 + 2]
        pcyc.abxbrtab[itab,LXQN]  = abedb[ipos + i*6 + 2 + 3]

        itab+=1


      #
      # printf("DBG: ");
      # for(j = 0; j < 6; j++) printf("%3d ",abedb[ipos + i*6 + j]);
      # printf("\n");
      #
  else:
    print "W:vxbrtab:Wrong EDB taken (%2d/%2d)\n"&(abedb[5],47)
  return


#  --------------------------------------------------------------------------
#    vxmrtab --- get SWICS matrix rates corners
#  ------------------------------------------------------------------------
def vxmrtab(abedb,pcyc):
  if ((abedb[5] == 48) or (abedb[5] == 49)):

    if (abedb[5] == 48):
      ioff =  0
    else:
      ioff = 10

    # reset 

    for i in range(10):
      # Note: NXMRBOX is 20, but only 10 entries in one DSpare 

      pcyc.abxmrtab[i+ioff,LXBOX] = 255
      pcyc.abxmrtab[i+ioff,LXMX]  = 255
      pcyc.abxmrtab[i+ioff,LXQX]  = 255
      pcyc.abxmrtab[i+ioff,LXMN]  = 255
      pcyc.abxmrtab[i+ioff,LXQN]  = 255

    itab = 0

    # loop over all bytes in DSpare 

    for i in range(9,-1,-1):
      # loop DSpare 

      # correct entry 

      ipos = pcyc.aspos[abedb[5],LDSPARE,LTLMPOS]

      itmp = 0
      itmp = (abedb[ipos + i*6 + 0] << 8) | (abedb[ipos + i*6 + 1])

      # itmp is the table entry. MR entries are located
      # in positins 16..63 */
          
      if ((itmp >= 16) and (itmp < (16 + NXMRBOX))):

        itmp -= 16

        pcyc.abxmrtab[itab + ioff,LXBOX] = itmp
        pcyc.abxmrtab[itab + ioff,LXMX]  = abedb[ipos + i*6 + 2 + 0]
        pcyc.abxmrtab[itab + ioff,LXQX]  = abedb[ipos + i*6 + 2 + 1]
        pcyc.abxmrtab[itab + ioff,LXMN]  = abedb[ipos + i*6 + 2 + 2]
        pcyc.abxmrtab[itab + ioff,LXQN]  = abedb[ipos + i*6 + 2 + 3]

        itab+=1
  else: 
    print "W:vxmrtab:Wrong EDB taken (%2d/%2d %2d)\n"%(abedb[5],48,49)
  return

"""
#  --------------------------------------------------------------------------
#    deccpha --- Decipher SWICS PHA words.
#  --------------------------------------------------------------------------
def deccpha(onepha,stcpha):
  long ltmp = 0L

  # --- reset structure --- 

  stcpha.range  = 0
  stcpha.sector = 0
  stcpha.ESSD   = 0
  stcpha.TOF    = 0

  # -----------------------------------------------------------------------
  # 0123 4567   8901 2345   6789 0123
  #    v vv Sector =   vv   vvvv vvvv TOF =
  # 1110:1111 | 0100:0011 | 1011:1001
  #        ^^   ^^^^ ^^ Energy = 
  # ^^^ Range = 
  # -----------------------------------------------------------------------
    
  ltmp = 0L
  ltmp = (onepha[0] << 16) | (onepha[1] <<  8) | (onepha[2])

  stcpha.range  = getbits(ltmp, 0+8,3)
  stcpha.sector = getbits(ltmp, 3+8,3)
  stcpha.ESSD   = getbits(ltmp, 6+8,8)
  stcpha.TOF    = getbits(ltmp,14+8,10)
  return
"""
#  --------------------------------------------------------------------------
#    deccpha --- Decipher SWICS PHA words.
#  --------------------------------------------------------------------------
def deccpha(onepha):
  ltmp = int32(0)

  # --- reset structure --- 

  RANGE  = 0
  SECTOR = 0
  ESSD   = 0
  TOF    = 0

  # -----------------------------------------------------------------------
  # 0123 4567   8901 2345   6789 0123
  #    v vv Sector =   vv   vvvv vvvv TOF =
  # 1110:1111 | 0100:0011 | 1011:1001
  #        ^^   ^^^^ ^^ Energy = 
  # ^^^ Range = 
  # -----------------------------------------------------------------------
    
  ltmp = int32((onepha[0] << 16) | (onepha[1] <<  8) | (onepha[2]))

  RANGE  = getbits(ltmp, 0+8,3)
  SECTOR = getbits(ltmp, 3+8,3)
  ESSD   = getbits(ltmp, 6+8,8)
  TOF    = getbits(ltmp,14+8,10)
  return RANGE,SECTOR,ESSD,TOF


#  --------------------------------------------------------------------------
#    decmpha --- Decipher SWIMS MHA words.
#  --------------------------------------------------------------------------
def decmpha(onepha):
  ltmp = int32(0)

  # --- reset structure --- 

  RANGE  = 0 #/ 3  bits in PHA word 
  SECTOR = 0 #/ 3  " 
  AMP    = 0 #/ 10 " 
  K1     = 0 #/ 10 " 
  K2     = 0 #/ 10 " 
  TOF    = 0 #/ 12 " 

  # .........................................................................
  #   Note: even though there are 3 bits for the range, it looks like
  #         only 2 are actually used for Ranges 0,1, and 2.
  #   .......................................................................

  # --- fill structure --- 

  # --  take first 2 bytes: range,sector and amp -- 

  ltmp = int32((onepha[0] <<  8) | (onepha[1]))

  RANGE  = getbits(ltmp, 0+16, 3)
  SECTOR = getbits(ltmp, 3+16, 3)
  AMP    = getbits(ltmp, 6+16,10)

  # --  take other 4 bytes: k1,k2 and tof -- 

  ltmp = int32((onepha[2] << 24) | (onepha[3] << 16) | (onepha[4] <<  8) |(onepha[5]))

  K1     = getbits(ltmp, 0,10)
  K2     = getbits(ltmp,10,10)
  TOF    = getbits(ltmp,20,12)

  # --- that's it --- 

  return RANGE,SECTOR,AMP,K1,K2,TOF

"""
#  --------------------------------------------------------------------------
#    decmpha --- Decipher SWIMS MHA words.
#  --------------------------------------------------------------------------
def decmpha(onepha,stmpha):
  ltmp = long(0L)

  # --- reset structure --- 

  stmpha.range  = 0 #/ 3  bits in PHA word 
  stmpha.sector = 0 #/ 3  " 
  stmpha.amp    = 0 #/ 10 " 
  stmpha.k1     = 0 #/ 10 " 
  stmpha.k2     = 0 #/ 10 " 
  stmpha.tof    = 0 #/ 12 " 

  # .........................................................................
  #   Note: even though there are 3 bits for the range, it looks like
  #         only 2 are actually used for Ranges 0,1, and 2.
  #   .......................................................................

  # --- fill structure --- 

  # --  take first 2 bytes: range,sector and amp -- 

  ltmp = 0L
  ltmp = (onepha[0] <<  8) | (onepha[1])

  stmpha.range  = getbits(ltmp, 0+16, 3)
  stmpha.sector = getbits(ltmp, 3+16, 3)
  stmpha.amp    = getbits(ltmp, 6+16,10)

  # --  take other 4 bytes: k1,k2 and tof -- 

  ltmp = 0L
  ltmp = (onepha[2] << 24) | (onepha[3] << 16) | (onepha[4] <<  8) |(onepha[5])

  stmpha.k1     = getbits(ltmp, 0,10)
  stmpha.k2     = getbits(ltmp,10,10)
  stmpha.tof    = getbits(ltmp,20,12)

  # --- that's it --- 

  return
"""
# ---------------------------------------------------------------------------
#   convTmp --- convert byte to temperature
#   ------------------------------------------------------------------------- 

def convTmp(bval):
  adtemps = array([154.7, 154.7, 125.9, 110.6, 100.4,92.8, 86.7, 81.8, 77.5, 73.9, 70.6, 67.7, 65.1, 62.7, 60.6, 58.5, 56.7, 54.9, 53.3, 51.7, 50.3, 48.9, 47.6, 46.3, 45.1, 44.0, 42.9, 41.8, 40.8, 39.8, 38.9, 38.0, 37.1, 36.3, 35.4, 34.6, 33.8, 33.1, 32.4, 31.6, 30.9, 30.2, 29.6, 28.9, 28.3, 27.7, 27.1, 26.5, 25.9, 25.3, 24.7, 24.2, 23.6, 23.1, 22.6, 22.1, 21.6, 21.1, 20.6, 20.1, 19.6, 19.2, 18.7, 18.2, 17.8, 17.3, 16.9, 16.5, 16.0, 15.6, 15.2, 14.8, 14.4, 14.0, 13.6, 13.2, 12.8, 12.4, 12.0, 11.7, 11.3, 10.9, 10.5, 10.2, 9.8, 9.5, 9.1, 8.8, 8.4, 8.1, 7.7, 7.4, 7.0, 6.7, 6.4, 6.0, 5.7, 5.4, 5.1, 4.7, 4.4, 4.1, 3.8, 3.5, 3.2, 2.9, 2.5, 2.2, 1.9, 1.6, 1.3, 1.0, 0.7, 0.4, 0.1, -0.2, -0.5, -0.8, -1.0, -1.3, -1.6, -1.9, -2.2, -2.5, -2.8, -3.1, -3.4, -3.6, -3.9, -4.2, -4.5, -4.8, -5.0, -5.3, -5.6, -5.9, -6.2, -6.4, -6.7, -7.0, -7.3, -7.5, -7.8, -8.1, -8.4, -8.6, -8.9, -9.2, -9.5, -9.7, -10.0, -10.3, -10.6, -10.8, -11.1, -11.4, -11.7, -11.9, -12.2, -12.5, -12.8, -13.0, -13.3, -13.6, -13.9, -14.1, -14.4, -14.7, -15.0, -15.3, -15.5, -15.8, -16.1, -16.4, -16.7, -16.9, -17.2, -17.5, -17.8, -18.1, -18.4, -18.7, -19.0, -19.2, -19.5, -19.8, -20.1, -20.4, -20.7, -21.0, -21.3, -21.6, -21.9, -22.2, -22.5, -22.8, -23.1, -23.5, -23.8, -24.1, -24.4, -24.7, -25.0, -25.4, -25.7, -26.0, -26.4, -26.7, -27.0, -27.4, -27.7, -28.1, -28.4, -28.8, -29.1, -29.5, -29.9, -30.2, -30.6, -31.0, -31.4, -31.8, -32.1, -32.5, -32.9, -33.4, -33.8, -34.2, -34.6, -35.1, -35.5, -35.9, -36.4, -36.9, -37.3, -37.8, -38.3, -38.8, -39.3, -39.9, -40.4, -41.0, -41.5, -42.1, -42.7, -43.3, -44.0, -44.6, -45.3, -46.0, -46.7, -47.5, -48.2, -49.1, -49.9, -50.8])
  return adtemps[bval]

# ---------------------------------------------------------------------------
#   convTmp2 --- convert byte to temperature for SWICS/PAPS ref. temp.
# --------------------------------------------------------------------------- 

def convTmp2(bval):
  dres = -1.0

  if (bval < 235):
    dres = -128.0  + bval * 0.6714
  else:
    dres = -949.85 + bval * 4.117
  return(dres)


"""
   ---------------------------------------------------------------------------
   history

   date      | change
   ----------+----------------------------------------------------------------
   15-Jul-98 | SWICS/SWIMS CMD/CTL blocks: use both EDBs of one record
             | where the bytes can be found.
             | ...............................................................
             | SWICS PHA: store m, m/q.
   ----------+----------------------------------------------------------------

   ---------------------------------------------------------------------------
"""
