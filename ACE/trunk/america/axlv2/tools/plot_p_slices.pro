; Filename: read_slices.pro
;
; Description:
;   Read set of energy-tof slice matrices and return in structure.
;   Matrices are as formated by axlv2, which is TNT library style with
;   additional headers.  See smread2 for details.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: plot_p_slices.pro,v 1.3 2005/01/19 01:12:25 jraines Exp $
;
; Major Modification History
;   25Aug2003   jmr   Adapted from read_ets.pro
;
; Arguments
; I/O   argument         description
; ---   --------         -----------
; I     file             E-T slice file produced by axlv2
; O     slices           array of smread2 structures containing E-T
;                        slices and meta information.
; I     [/noread]         Optionally turn off reading of slice data
;                        (use struct. passed in)
; I     [/fullrange]      Optionally include plot of slice over full E-T
; I     [tag]             Optional text tag for subtitle
pro plot_p_slices, file=slicefile, slices=slices, noread=noread, $
                   fullrange=fullrange, tag=tag

thisprog = 'plot_p_slices'

;; set to > zero to turn on debugging output
debug = 0

;; read in E-T matrix
;; ------------------
if (not keyword_set(slicefile)) then slicefile = 'axlv2_p_slices.dat'
if (not keyword_set(noread)) then begin
  read_slices, file=slicefile, slices=slices
endif 

if (not keyword_set(tag)) then tag=''

;; ----------------------------------------------------------------------------
;; plot here for now
;; ----------------------------------------------------------------------------
;; --- read FM center data ---
;; note: must read or alter to pass fmc_ions and eoqtable in/out of
;; this routine
fmcfile='axlv2_fmcomp.dat'
read_fmc, file=fmcfile, fmc=fmc, ions=fmc_ions, eqtab=eoqtable

;; store number of fmc_ions
nfmc_ions = n_elements(fmc_ions)

;; define an array of fmc structures to use with individual steps
fmcstep = replicate( fmc[0], nfmc_ions)

;; set up PS file
file_parse, file=slicefile, dir=dir, base=base, ext=ext
psfile = base + '.ps'
psplt, file=psfile, /color

for nslice=0,n_elements(slices)-1 do begin
  ;; Get step from end of TOF axis label, e.g. TOF_CH_STEP_43
  l = slices[nslice].xtitle
  sl = strsplit(l, '_')
  step = fix(strmid(l, sl[n_elements(sl)-1], strlen(l) - sl[n_elements(sl)-1]))

  ;; select fmc data for this step
  tmp_index = where(fmc[*].step eq step, ntmp_index)
  if (ntmp_index gt 0) then fmcstep = fmc[tmp_index] else goto, next
  
  ;; add a small number to make color_plot happy to do log z scale
  slices[nslice].mat = slices[nslice].mat + 1.0e-5

  ;; plot a larger range 
  ;; FIX: this only makes sense for subsec=1 or if proper subsec is determined
  if (keyword_set(fullrange)) then begin
    plot_ets, etslice=slices[nslice], fmcstep=fmcstep, tag=tag, $
      zrange=zrange, plotFM=[1,0], subsec=3
  endif

  ;; find x/yranges for this slice
  ;; -----------------------------
  peak_cutoff = 0.5
  window = 5
  ;xrange = intarr(2)
  xrange = [0,1023]
  ;yrange = intarr(2)
  yrange = [0,255]
  in_peak = 0
  ;; xrange
  for tofch=0,1023 do begin
    tot = total(slices[nslice].mat(tofch,*))
    if (debug) then print, tofch, tot
    if (tot gt peak_cutoff and in_peak eq 0) then begin
      if (debug) then print, '----ENTER PEAK----'
      in_peak = 1
      xrange[0] = tofch - window
    endif
    if (tot le peak_cutoff and in_peak eq 1) then begin
      if (debug) then print, '----EXIT PEAK----'
      in_peak = 0
      xrange[1] = tofch + window
      break
    endif
  endfor
  ;; yrange
  for esdch=0,255 do begin
    tot = total(slices[nslice].mat(*,esdch))
    if (debug) then print, tot
    if (tot gt peak_cutoff and in_peak eq 0) then begin
      if (debug) then print, '----ENTER PEAK----'
      in_peak = 1
      yrange[0] = esdch - window
    endif
    if (tot le peak_cutoff and in_peak eq 1) then begin
      if (debug) then print, '----EXIT PEAK----'
      in_peak = 0
      yrange[1] = esdch + window
      break
    endif
  endfor

  ;; -- plot (ets[0] is for step 2, etc.) ---
  ;;slices[nslice].mat = slices[nslice].mat + 1.0e-5
  plot_ets, etslice=slices[nslice], fmcstep=fmcstep, tag=tag, $
    zrange=zrange, plotCenters=[1,0], xrange=xrange,yrange=yrange

  tagplot, line1=thisprog, line2=psfile

  next:
endfor

ficlose
return
end
