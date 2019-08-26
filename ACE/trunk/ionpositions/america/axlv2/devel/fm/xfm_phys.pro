; Filename: xfm_phys.pro
;
; Description:
;   ACE/SWICS Physics-Based Forward Model.  Predicts (TOF,ESD) for
;   particular ion from a set of related values, physical constants
;   and parameters.
;
; Author: Jim Raines (jmr)
;
; Method:
;   Calculates energy losses by interpolation from Univ. of Maryland's
;   CFOIL and DFECT tables.
;   
; Revision controlled by CVS:
; $Id: xfm_phys.pro,v 1.1 2004/10/04 16:25:42 jraines Exp $
;
; Major Modification History
;   ddmmmyyyy   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   eoq         E/q for ion in question, in keV/e
; I   pav         post-accel. voltage, in kV
; I   mas         mass, in amu
; I   crg         charge, in units of e
; I   [H4]        Adjustable parameter which models departure of
;                 measured ESD from predicted, likely due to
;                 efficiency issues.
; O   [cfoil_data] optionally return CFOIL data array
; O   [dfect_data] optionally return DFECT data array
function xfm_phys, eoq=eoq, pav=pav, mas=mas, crg=crg, H3=H3_in, $
                   cfoil_data=CFOIL, dfect_data=DFECT

;; ----------------------------------------------------------------------
;; Initialize variables
;; ----------------------------------------------------------------------
;; name of this routine
thisprog = 'xfm_phys'

;; integer mass, for indexing
imas = fix(mas)

;; forward model position for this ion (returned)
fm_pos = make_array(4, /float, value=-1.0)

;; Based on CFOIL.FOR, 4/21/1989
;; -------------------------------------------------
;; energy/nucleon
CFOIL_EON = [    1.00,    1.50,    2.50,    4.00,    6.00,    8.00,   10.00,$
                 15.00,   25.00,   40.00,   60.00,   80.00,  100.00,  150.00,$
                 250.00,  400.00,  600.00,  800.00, 1000.00,10000.00]
;; Energy loss (cm^2 / nucleon ug ) in a carbon foil
;; 1st index is mass (integer), 2nd index goes with CFOIL_EON, above
;; This wastes memory, but only about 6kb.
CFOIL = make_array(85, n_elements(CFOIL_EON), /float, val=-1.0)
;; H
CFOIL[1,*] = [0.16,    0.18,    0.23,    0.28,    0.34,    0.38,    0.42,$
              0.50,    0.60,    0.70,    0.75,    0.75,    0.73,    0.64,$
              0.51,    0.40,    0.32,    0.27,    0.23,    0.04]
;; He
CFOIL[4,*] = [0.43,    0.48,    0.57,    0.66,    0.75,    0.84,    0.91,$
              1.05,    1.25,    1.47,    1.65,    1.82,    1.86,    1.93,$
              1.81,    1.53,    1.24,    1.04,    0.89,    0.16]
;; C
CFOIL[12,*] = [1.28,    1.38,    1.52,    1.72,    1.91,    2.10,    2.28,$
               2.60,    3.25,    4.10,    4.95,    5.58,    6.05,    6.75,$
               7.20,    7.10,    6.80,    6.25,    5.80,    1.45]
;; N
CFOIL[14,*] = [1.41,    1.51,    1.71,    1.91,    2.18,    2.39,    2.58,$
               2.97,    3.67,    4.55,    5.50,    6.25,    6.80,    7.95,$
               8.70,    8.80,    8.30,    7.75,    7.20,    1.95]
;; O
CFOIL[16,*] = [1.42,    1.52,    1.72,    1.99,    2.29,    2.51,    2.73,$
               3.22,    4.05,    5.00,    6.02,    7.00,    7.62,    8.90,$
               10.10,   10.20,    9.80,    9.35,    8.85,    2.50]
;; Ne
CFOIL[20,*] = [1.30,    1.37,    1.54,    1.80,    2.10,    2.35,    2.60,$
               3.13,    4.15,    5.27,    6.50,    7.58,    8.56,   10.70,$
               13.60,   15.20,   15.20,   14.40,   13.40,    3.90]
;; Ar
CFOIL[40,*] = [3.08,    3.08,    3.18,    3.45,    3.80,    4.15,    4.45,$
               5.20,    6.30,    7.77,    9.60,   11.30,   12.80,   16.30,$
               21.00,   24.50,   26.60,   26.80,   26.30,   10.40]
;; Fe
CFOIL[56,*] = [3.25,    3.25,    3.25,    3.40,    3.72,    4.13,    4.60,$
               5.65,    7.40,    9.48,   11.80,   13.90,   15.90,   20.90,$
               27.30,   33.10,   36.90,   38.00,   37.90,   18.30]
;; Kr
CFOIL[84,*] = [4.10,    4.10,    4.10,    4.20,    4.43,    4.78,    5.19,$
               6.30,    8.38,   10.80,   13.60,   16.10,   18.50,   24.80,$
               33.70,   42.40,   48.60,   51.00,   51.50,   29.30]

;; Based on DFECT.FOR, 4/21/1989
;; -------------------------------------------------
;; energy/nucleon
DFECT_EON = [0.40,     0.70,     1.00,     1.50,     2.50,     4.00,     6.00,$
             8.00,    10.00,    15.00,    25.00,    40.00,    60.00,    80.00,$
             100.00,   150.00,   250.00,   400.00,   600.00,   800.00,$
             1000.00, 10000.00]
;; Energy loss (cm^2 / nucleon ug ) in a carbon foil
;; 1st index is mass (integer), 2nd index goes with DFECT_EON, above
;; This wastes memory, but only about 6kb.
DFECT = make_array(85, n_elements(DFECT_EON), /float, val=-1.0)
;; H
DFECT[1,*] = [35.50,    45.50,    51.90,    58.40,    65.70,    71.80,$
              77.00,    80.50,    82.90,    86.40,    90.20,    92.80,$
              94.60,    95.60,    96.40,    97.50,    98.50,    99.20,$
              99.50,    99.60,    99.70,    100.00]
;; He
DFECT[4,*] = [32.80,    43.40,    50.00,    57.20,    65.50,    72.30,$
              77.50,    80.70,    83.10,    87.00,    90.90,    93.40,$
              95.20,    96.00,    96.60,    97.50,    98.40,    99.00,$
              99.40,    99.50,    99.60,    100.00]
;; C
DFECT[12,*] = [18.20,    26.20,    31.60,    38.30,    47.30,    56.20,$
               64.10,    69.10,    72.50,    78.20,    84.20,    88.30,$
               91.30,    93.10,    94.00,    95.70,    97.20,    98.20,$
               98.70,    99.00,    99.20,    99.80]
;; N
DFECT[14,*] = [17.30,    24.80,    29.90,    36.40,    45.70,    54.60,$
               62.20,    67.20,    70.70,    76.60,    82.80,    87.40,$
               90.70,    92.60,    93.70,    95.30,    97.00,    98.00,$
               98.60,    98.90,    99.10,    99.80]
;; O
DFECT[16,*] = [17.20,    23.20,    27.10,    32.90,    41.50,    50.40,$
               59.10,    64.60,    68.40,    74.50,    80.80,    85.80,$
               88.70,    90.40,    91.50,    93.60,    95.70,    97.10,$
               97.90,    98.40,    98.70,    99.70]
;; Ne
DFECT[20,*] = [17.10,    22.50,    25.80,    30.20,    37.10,    45.10,$
               52.70,    58.10,    62.20,    69.50,    77.60,    82.70,$
               86.40,    88.60,    90.00,    92.00,    94.30,    95.80,$
               96.80,    97.40,    97.70,    99.50]
;; Ar
DFECT[40,*] = [15.20,    20.50,    23.90,    28.20,    35.00,    42.10,$
               48.80,    53.40,    57.00,    63.30,    71.20,    77.20,$
               81.90,    84.60,    86.60,    89.90,    93.10,    94.90,$
               96.10,    96.60,    97.00,    99.30]
;; Fe
DFECT[56,*] = [14.50,    18.80,    22.40,    26.20,    31.00,    35.60,$
               40.30,    43.70,    46.60,    52.80,    62.00,    70.90,$
               77.50,    81.20,    83.30,    86.60,    90.30,    92.90,$
               94.60,    95.40,    95.90,    99.00]
;; Kr
DFECT[84,*] = [14.00,    17.40,    21.20,    25.20,    29.80,    34.20,$
               38.60,    42.20,    45.10,    50.40,    58.20,    66.00,$
               72.40,    76.50,    78.90,    82.90,    87.80,    91.30,$
               93.30,    94.40,    95.10,    98.80]

;; carbon foil thickness in ug/cm^2
FOIL_THICK = 2.0

;; Length of TOF region (cm)
TOF_DISTANCE = 10.0 

;; ESD (keV) -> ESD (ch)
ESD_kev_per_ch = 2.395

;; TOF (ns) -> TOF (ch)
TOF_ns_per_ch = 0.1955
;; ----------------------------------------------------------------------
;; ===> Configuration <===
;; ----------------------------------------------------------------------
;; ----------------------------------------------------------------------
;; Find energy lost in foil
;; ----------------------------------------------------------------------
;; total energy
etot = (eoq + pav)*crg

;; energy/nucleon
eon = etot/mas

if (CFOIL[imas, 0] eq -1.0) then begin
  format = '(A," -F- mass ",F6.2," not in foil loss table.  Exiting.")'
  print, format=format, thisprog, mas
  return, fm_pos
endif

;; get interpolated value for foil loss rate and calculate foil loss
loss_rate = interpol(CFOIL[imas,*], CFOIL_EON, eon, /spline)
ul = loss_rate*FOIL_THICK

;; reduce total energy accordingly
etot = etot - ul

;; ----------------------------------------------------------------------
;; Calculate TOF
;; ----------------------------------------------------------------------
;; tof
;; conv. factor: 520.0 ns^2 keV / cm^2 amu
tof = TOF_DISTANCE*sqrt(mas*520.0/etot)

;; ----------------------------------------------------------------------
;; Find energy lost (and not measured) in solid state detector
;; ----------------------------------------------------------------------
;; recalculate energy/nucleon
eon = etot/mas

if (DFECT[imas, 0] eq -1.0) then begin
  format = '(A," -F- mass ",F6.2," not in foil loss table.  Exiting.")'
  print, format=format, thisprog, mas
  return, fm_pos
endif

;; get interpolated value for ESD measurement fraction and calculate measured
meas_frac = interpol(DFECT[imas,*], DFECT_EON, eon, /spline)
emeas = etot*(meas_frac/100.0)

;; ----------------------------------------------------------------------
;; Convert to channels and store in returned array
;; ----------------------------------------------------------------------


;; convert tof to channels
fm_pos[0] = tof / TOF_ns_per_ch

;; TBD
fm_pos[1] = 0.1*fm_pos[0]

;; convert esd to channels
fm_pos[2] = emeas / ESD_kev_per_ch

;; TBD
fm_pos[3] = 0.1*fm_pos[2]

;; debug only
print, "fm_pos: ", fm_pos
return, fm_pos
end


