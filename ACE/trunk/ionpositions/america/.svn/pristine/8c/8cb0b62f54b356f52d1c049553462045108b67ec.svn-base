; Filename: xfmexp.pro
;
; Description:
;   ACE/SWICS Forward Model, IDL version
;
; Author: Simon Hefti (hef)
;         Jim Raines (jmr)
;
; Method:
; 
;   
; Revision controlled by CVS:
; $Id: xfmexp.pro,v 1.1 2004/10/04 16:25:42 jraines Exp $
;
; Major Modification History
;   13Jan2004   jmr   Adapted from libhef::swxtools::xfm and
;                     libhef::asxdpusim::adputof 
;
; Arguments for xfmexp:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   eoq         E/q for ion in question, in keV/e
; I   pav         post-accel. voltage, in kV
; I   mas         mass, in amu
; I   crg         charge, in units of e

; Routine: adputof
;
; Description:
;   Calculates  TOF(E/q,PAPS,m/q) according to DPU algorithm.
;
; Author(s): Simon Hefti (hef)
;            Jim Raines (jmr)
;
; Method:
; 
;   
; Arguments for xfmexp:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   eoq         E/q in keV/e
; I   paps        post-accel. voltage, in kV
; I   moq         mass/charge, in amu/e
function adputof, eoq, paps, moq

;; hardcoded in libhef::asdpusim.c
aducla_LUCLAC1 = 1.9159e-5
aducla_LUCLATC = 5.115          ; ch/ns

etrm = 0.0

etrm = eoq + paps - 1.5         

if( etrm le 0.0 ) then begin
  format = '("adputof --- bad energy: ",F6.2," ",F6.2)'
  print, format=format,eoq,paps
  dtof = -1.0
  goto, exit
endif

dtof = moq / aducla_LUCLAC1 / etrm 
  
dtof = sqrt(dtof) * aducla_LUCLATC ;/* in channels */

exit:
return, dtof
end

; Routine: xfmexp.pro
;
; Description:
;   ACE/SWICS Forward Model, IDL version
;
; Author: Jim Raines (jmr)
;
; Method:
;
; Arguments for xfmexp:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   eoq         E/q for ion in question, in keV/e
; I   pav         post-accel. voltage, in kV
; I   mas         mass, in amu
; I   crg         charge, in units of e
function xfm, eoq=eoq, pav=pav, mas=mas, crg=crg, H1=H1_in,UL=UL_in,$
              H3=H3_in,H4=H4_in, etil=etil
;  /* NOTE ON POST-ACCELERATION VOLTAGES:

;     The pav shifts the centers in both tof and esd dimenions.  For some,
;     reason the orginal set of coef. (for level 127) were fit assuming a pav
;     of 22.8kV, even though a3gxpavdpu(127) returns 21.2998.

;     When trying to determine new coef. for the new PAPS level, 171,
;     it was determined that pav = 25.8682 caused the centers to align
;     perfectly in tof, meaning that only the esd coef. (H3/4) needed to be
;     tuned (for existing ions).

;     So, a linear fit was made that converts values returned by
;     a3gxpavdpu for level 127 and 171 to these two values of 22.8 kV
;     and 25.8682.  And, a switch was implemented which switched
;     forward model coef. based on the two a3gxpavdpu-returned values.  
;   */
;  /* Post-accel. voltages (pav) for which forward model coef. were determined
;     paps level 127, corresponding to pav = 21.2998
;     paps level 171, corresponding to pav = 24.8682
;  */
KNOWN_PAV = [21.2998,24.8682]   ;

A1  =  5.81090
A2  = -1.50052
A3  = -3.01352
A4  =  0.471113
A5  =  0.0804588
A6  =  0.0731559
T2C =  5.115
E2C =  0.417498936

;; forward model constant arrays
H1 = make_array(57, /double, val=-1.0)
H2 = make_array(57, /double, val=-1.0)
H3 = make_array(57, /double, val=-1.0)
H4 = make_array(57, /double, val=-1.0)
H5 = make_array(57, /double, val=-1.0)
H6 = make_array(57, /double, val=-1.0)
UL = make_array(57, /double, val=-1.0)

;; forward model values: tof, stof, esd, sesd
adfm = make_array(4, /float, val=-1.0)


moq = mas / crg

found_pav = 0
if (pav ge .99*KNOWN_PAV[0] and pav le 1.01*KNOWN_PAV[0]) then begin 
  ;; level 127
  ;printf("xfm -I- using pav = %6.2f coef.\n",KNOWN_PAV[0])
  found_pav = 1

  H1[ 4] = 1423990.2
  H1[12] = 1410767.2
  H1[14] = 1395060.1
  H1[16] = 1379527.9
  H1[20] = 1401869.9
  H1[24] = 1383950.2
  H1[28] = 1383950.2
  H1[56] = 1358009.1

  UL[ 4] = 1.34
  UL[12] = 1.47
  UL[14] = 1.66
  UL[16] = 1.88
  UL[20] = 1.08
  UL[24] = 1.60
  UL[28] = 1.60
  UL[56] = 1.53

  H2[ 4] = 0.0124
  H2[12] = 0.0124
  H2[14] = 0.0124
  H2[16] = 0.0124
  H2[20] = 0.0124
  H2[24] = 0.0124
  H2[28] = 0.0124
  H2[56] = 0.0124

  H3[ 4] =   3.381
  H3[12] =   3.940
  H3[14] =   0.0  
  H3[16] =   6.243
  H3[20] =   0.0  
  H3[24] =  12.068
  H3[28] =  12.068
  H3[56] =   1.090

  H4[ 4] = 0.850
  H4[12] = 0.934
  H4[14] = 1.0  
  H4[16] = 0.852
  H4[20] = 1.0  
  H4[24] = 0.739
  H4[28] = 0.739
  H4[56] = 0.920

  H5[ 4] = 0.78
  H5[12] = 0.78
  H5[14] = 0.78
  H5[16] = 0.78
  H5[20] = 0.78
  H5[24] = 0.78
  H5[28] = 0.78
  H5[56] = 0.41

  H6[ 4] = -0.79
  H6[12] = -0.79
  H6[14] = -0.79
  H6[16] = -0.79
  H6[20] = -0.79
  H6[24] = -0.79
  H6[28] = -0.79
  H6[56] = -0.63
endif
if (pav ge .99*KNOWN_PAV[1] and pav le 1.01*KNOWN_PAV[1])then begin
  ;; level 171
  ;printf("xfm -I- using pav = %6.2f coef.\n",KNOWN_PAV[1])
  found_pav = 1

  ;; TOF correction
  ;; axfmtweak note: set to 1000000.0 to find coef.
  H1[ 1] = 1469383.9
  H1[ 3] = 1423990.2            ; copied from 4He
  H1[ 4] = 1423990.2
  H1[12] = 1410767.2
  H1[14] = 1395060.1
  H1[16] = 1379527.9
  H1[20] = 1401869.9
  H1[24] = 1401869.9
  H1[28] = 1383950.2
  H1[32] = 1383950.2
  H1[56] = 1358009.1

  ;; Energy lost in carbon foil (kV)
  UL[ 1] = 0.49
  UL[ 3] = 1.34                 ; copied from 4He
  UL[ 4] = 1.34
  UL[12] = 1.47
  UL[14] = 1.66
  UL[16] = 1.88
  UL[20] = 1.08
  UL[24] = 1.08
  UL[28] = 1.60
  UL[32] = 1.60
  UL[56] = 1.53

                                ; TOF sigma
  H2[ 1] = 0.0124               ; copied from 4He
  H2[ 3] = 0.0124               ; copied from 4He
  H2[ 4] = 0.0124
  H2[12] = 0.0124
  H2[14] = 0.0124
  H2[16] = 0.0124
  H2[20] = 0.0124
  H2[24] = 0.0124
  H2[28] = 0.0124
  H2[32] = 0.0124
  H2[56] = 0.0124

  ;; ESD correction offset, H3
  H3[ 1] =   -0.34
  H3[ 3] =   3.381              ; copied from 4He
  H3[ 4] = 0.67
  H3[12] =  5.05
  H3[14] =  1.01
  H3[16] =   -0.17
  H3[20] =   8.81
  H3[24] =   25.12
  H3[28] =  7.93
  H3[32] =  -3.38
  H3[56] =   6.15

                                ; ESD correction slope, H4
  H4[ 1] = 1.22
  H4[ 3] = 0.850                ; copied from 4He
  H4[ 4] = 0.84
  H4[12] = 0.81 
  H4[14] = 0.92
  H4[16] = 0.89  
  H4[20] = 0.81
  H4[24] = 0.59
  H4[28] = 0.79
  H4[32] = 1.01 
  H4[56] = 0.73

  ;; ESD sigma multiplier
  H5[ 1] = 0.78
  H5[ 3] = 0.78
  H5[ 4] = 0.78
  H5[12] = 0.78
  H5[14] = 0.78
  H5[16] = 0.78
  H5[20] = 0.78
  H5[24] = 0.78
  H5[28] = 0.78
  H5[32] = 0.78
  H5[56] = 0.41

  ;; ESD sigma exponent
  H6[ 1] = -0.79
  H6[ 3] = -0.79                ; copied from 4He
  H6[ 4] = -0.79
  H6[12] = -0.79
  H6[14] = -0.79
  H6[16] = -0.79
  H6[20] = -0.79
  H6[24] = -0.79
  H6[28] = -0.79
  H6[32] = -0.79
  H6[56] = -0.63
endif
if (not found_pav) then begin
  format = '("xfm -F- post-accel. voltage (",F6.2,' + $
  '") not one of known values (",F6.2," or ",F6.2)'
  print, format=format, pav, KNOWN_PAV[0], KNOWN_PAV[1]
  goto, exit
endif

if( (mas le 0.0) or (mas gt 56.0) ) then begin
  format = '("xfm -F- cannot deal with mass = ",F6.2)'
  print, format=format,mas
  goto, exit
endif

im = fix(mas)
if( H1[im] le 0.0 ) then begin
  format = '("xfm -F- mass ",F6.2," not in model.")'
  print, format=format,mas
  goto, exit
endif

;; ----------------------------------------------------------------------
;; Re-assign coeficients if specified
;;
;; ----------------------------------------------------------------------
if (keyword_set(H1_in)) then H1[im] = H1_in
if (keyword_set(UL_in)) then UL[im] = UL_in
if (keyword_set(H3_in)) then H3[im] = H3_in
if (keyword_set(H4_in)) then H4[im] = H4_in
;; ----------------------------------------------------------------------
;; TOF position
;; ----------------------------------------------------------------------

;; adjust pav to value used to determined forward model coef.
;; (see note at beginning of routine)
;; 21.2998 -> 22.8 
;; 24.8682 -> 25.8682
pav_adj = (0.8598)*pav + 4.4864

etoq = eoq + pav_adj

x    = etoq - UL[im]
if( x le 0.0 ) then begin
  format = '("xfm -F- problems with (E/q + PAPS - UL) = ",F6.2)'
  print, format=format,x
  goto, exit
endif

y    = H1[im] / x
TOF  = sqrt(y * moq)

;; ----------------------------------------------------------------------
;; TOF sigma
;; ----------------------------------------------------------------------

sTOF = H2[im] * TOF

;; ----------------------------------------------------------------------
;; ESSD position
;; ----------------------------------------------------------------------

TOFDPU = adputof(eoq,pav_adj,moq)

if( TOFDPU le 1.0 ) then begin
  format = '("xfm -F- running into troubles with TOF = ",F6.2)'
  print, format=format,TOF
  goto, exit
endif

y      = TOFDPU / T2C
y      = alog(y)

alf    = A5
bet    = A2 + A4 * y
gam    = A1 + y * (A3 + A6 * y * y) - alog(mas)

y      = (-bet + sqrt(bet * bet - 4.0 * alf * gam)) / 2.0 / alf
ESD    = exp(y) * E2C
etil   = ESD                      ; for curve fitting H3/4
ESD    = H3[im] + H4[im] * ESD

;; ----------------------------------------------------------------------
;; ESSD sigma
;; ----------------------------------------------------------------------

sESD = H5[im] * (crg * etoq / mas)^H6[im] * ESD

;; ----------------------------------------------------------------------
;; done
;; ----------------------------------------------------------------------

adfm[0] = TOF
adfm[1] = sTOF
adfm[2] = ESD
adfm[3] = sESD

exit:

return, adfm
end

; Routine: xfmtof_fit
;
; Description:
;   Interface between curvefit and xfmexp for TOF fitting.
;
; Author(s): Jim Raines (jmr)
;
; Method:
; 
;   
; Arguments for xfmexp:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   crg         charge in e
; I   A           vector of coeficients, only H1 in this case
; O   tof         tof in ns
; I   PDER        partial derivatives wrt the coeficients
PRO xfmtof_fit, crg, A, tof,PDER

;; must use common block to define other xfmexp params to keep curvefit happy
common xfmparam, eoq_common, pav_common, mass_common

;; handle array of crg passed in
ncrg = n_elements(crg)
tof = make_array(ncrg, /float, val=-1.0)
for i=0,ncrg-1 do begin

  xfm_results = xfm(eoq=eoq_common[i], pav=pav_common,  $
                    mas=mass_common, crg=crg[i], H1=a[0])

  tof[i] = xfm_results[0]
endfor

return
end

; Routine: xfmesd_fit
;
; Description:
;   Interface between curvefit and xfmexp for ESD fitting.
;
; Author(s): Jim Raines (jmr)
;
; Method:
; 
;   
; Arguments for xfmexp:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   crg         charge in e
; I   A           vector of coeficients, only H1 in this case
; O   esd         residual energy (SSD) in keV
; I   PDER        partial derivatives wrt the coeficients
PRO xfmesd_fit, crg, A, esd,PDER

;; must use common block to define other xfmexp params to keep curvefit happy
common xfmparam, eoq_common, pav_common, mass_common

;; handle array of crg passed in
ncrg = n_elements(crg)
esd = make_array(ncrg, /float, val=-1.0)
for i=0,ncrg-1 do begin

  xfm_results = xfm(eoq=eoq_common[i], pav=pav_common, mas=mass_common,$
                    crg=crg[i], $
                    H1=a[0],H3=a[1],H4=a[2])

  esd[i] = xfm_results[2]
endfor

return
end
