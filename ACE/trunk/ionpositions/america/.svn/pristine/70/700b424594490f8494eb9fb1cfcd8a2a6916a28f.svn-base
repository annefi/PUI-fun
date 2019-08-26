; Filename: fmcomp.pro
;
; Description:
;   Swindal forward model comparison.  Makes contour plot in E-T space
;   of MA slice and overplots forward model centers and widths.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   This program uses two input files:  
;     1)  E-T slice file where it reads esd - tof slices (at one
;         charge step)
;     2)  FM center file where it reads the FM centers and
;     probabilistic centers.
;
;   It then plots 3 regions of each slice, Fe, non-Fe and the whole
;   thing with a fixed (needs improvment) Z scaling.  Over that it
;   plots cross hairs for the FM centers and the probabilistic centers.
;   
; This file controlled by CVS:
; $Id: fmcomp.pro,v 1.18 2005/01/19 01:12:25 jraines Exp $
;
; Major Modification History
;   27Feb2002   jmr   initial coding
;   24Sep2002   jmr   added range checking for prob center plotting
;                     and improved same for FM
;   29Oct2002   jmr   added consideration of FM *and* prob. crosshairs
;                     for range setting
;   1Nov2002    jmr   added zrange option
;   15Nov2002   jmr   major re-working -- split parts into subroutines
;   06Feb2003   jmr   added tagplot to annotate plots
;   21Aug2003   jmr   added full bounds checking of subsections
;   05Sep2003   jmr   reworked to use modular code pieces (based on fmpick.pro)
;   21Nov2003   jmr   split fmcomp stuff into fmc and pcc
;
; Arguments
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   fmcfile     forward model comparision file,
;                 e.g. axlv2_fmcomp.dat
; I   pccfile     prob. center comparison file, e.g. axlv2_pccomp.dat
; I   etsfile     E-T slice file, e.g. axlv2_et_slices.dat
; I   [tag]       Optional text tag for subtitle
; I   [steps]     Optional specify array of steps to plot
; I   [zrange]    Optionally specify fixed zrange (same for all plots)
;                 instead of letting color_plot determine it for each plot.
; I   [/noread]   Optionally disable reading of etsfile; uses
;                 structure passed in on command line instead.
; I/O [etsdata]       Optionally specify variable into which E-T slice
;                 structure is returned
; I   [psfile]    specify a Postscript output filename explicitly
; I   [subsec]    plot only one subsection.  See plot_ets.pro for def.
pro fmcomp, fmcfile=fmcfile, pccfile=pccfile, etsfile=etsfile, tag=tag, $
            fmcdata=fmc, pccdata=pcc, $
            steps=steps, zrange=zrange, noread=noread, etsdata=ets,$
            psfile=psfile, subsec=subsec

;; ===========================> configuration <================================
;; none
;; ============================================================================

;; ----------------------------------------------------------------------------
;; ---------------------------- set up  --------------------------------------
;; ---------------------------------------------------------------------------
if (not keyword_set(fmcfile)) then begin
  fmcfile='axlv2_fmcomp.dat'
endif
if (not keyword_set(pccfile)) then begin
  pccfile='axlv2_pccomp.dat'
endif
if (not keyword_set(etsfile)) then begin
  etsfile='axlv2_et_slices.dat'
endif

;; define step range if not specified on command line
if (not keyword_set(steps)) then begin
  steps = indgen(58) + 2
endif

if (not keyword_set(tag)) then tag=''

;; set up postscript file
if (not keyword_set(psfile)) then begin
  file_parse, file=fmcfile, base=base
  psfile = base + '.ps'
endif
psplt, file=psfile, /color

;; set up color table and colors
loadct, 34                        ;34 is Rainbow
fix_ct_ends, black=0, white=255   ;insert bw
black = 0                         ;define color mnemonic
white = 1

;; read FM center data
;; note: must read or alter to pass fmc_ions and eoqtable in/out of
;; this routine
read_fmc, file=fmcfile, fmc=fmc, ions=fmc_ions, eqtab=eoqtable

;; define an array of fmc structures to use with individual steps
nfmc_ions = n_elements(fmc_ions)
fmcstep = replicate( fmc[0], nfmc_ions)

if (file_exists(pccfile)) then begin
  pcc_present = 1

  read_pcc, file=pccfile, pcc=pcc, ions=pcc_ions

  ;; define an array of fmc structures to use with individual steps
  npcc_ions = n_elements(pcc_ions)
  pccstep = replicate( pcc[0], npcc_ions)
endif else pcc_present = 0

if (not keyword_set(noread)) then begin
  ;; read in ET array
  read_ets, file=etsfile, ets=ets
endif


;; loop over steps to actually do plots
;; -----------------------------------
for istep=0,n_elements(steps)-1 do begin
  ;; re-init
  plotCenters = [1,pcc_present]

  step = steps[istep]

  ;; select fmc data for this step
  tmp_index = where(fmc[*].step eq step, ntmp_index)
  if (ntmp_index gt 0) then begin
    fmcstep = fmc[tmp_index] 

    if (pcc_present) then begin
      tmp_index = where(pcc[*].step eq step, ntmp_index)
      if (ntmp_index gt 0) then pccstep = pcc[tmp_index] $
      else plotCenters[1] = 0   ; turn off pcc on this step
    endif
  endif else goto, next
  
  ;; plot (ets[0] is for step 2, etc.)
  plot_ets, etslice=ets[step-2], fmcstep=fmcstep, pccstep=pccstep, $
    tag=tag, zrange=zrange, plotCenters=plotCenters, subsec=subsec
  tagplot, line1=thisprog, line2=psfile

  next:
endfor

;; ----------Clean up and get out----------
ficlose
return
end
