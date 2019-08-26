; Filename: fmcomp_allts.pro
;
; Description:
;   Run axlv2 Forward Model Comparison (fmcomp) on all timesteps in a
;   directory.
;
; Author: Jim Raines (jmr)
;
; Method:
;   Uses a pattern + wildcard to find all the
;   axlv2_et_slices_nnn_nn.dat and axlv2_pccomp_nnn_nn.dat files in a
;   directory. 
;   
; Revision controlled by CVS:
; $Id: fmcomp_allts.pro,v 1.3 2005/03/14 16:53:39 jraines Exp $
;
; Major Modification History
;   ddmmmyyyy   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   pattern     data file pattern, e.g. pattern='axlv2_' 
; O   sum         sum of data structures, e.g., data=d001
;pro fmcomp_allts

;; ----------------------------------------------------------------------------
;; set up
;; ----------------------------------------------------------------------------
thisprog = 'fmcomp_allts'

;; ----------------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------------
noplot = 0
subsec = 3
steps=indgen(15)+28
;; ----------------------------------------------------------------------------
;; find files
;; ----------------------------------------------------------------------------
spawn, '\ls axlv2_et_slices_*.dat', etsfiles
spawn, '\ls axlv2_pccomp_*.dat', pccfiles

num_etsfiles = n_elements(etsfiles)
num_pccfiles = n_elements(pccfiles)

if (num_etsfiles ne num_pccfiles) then begin
  print, thisprog + ' -W- number of files differ; exiting...'
  goto, clean_exit
endif

;; ----------------------------------------------------------------------------
;; do plots and sum
;; ----------------------------------------------------------------------------
for ifile = 0, num_etsfiles-1 do begin
  ;; --- construct filename ---
  ;; get rid of path and extension
  file_parse, file=etsfiles[ifile], base=base
  ;; find the underscores which delimit the doy and fraction
  us = strsplit(base, '_')
  nus = n_elements(us)
  ;; grab the doy and fraction from knowledge of underscore positions
  ;; note: doy is after second to last (hence -2) '_' and fraction is
  ;;       after the last underscore
  doyfr_str = strmid(base, us[nus-2], us[nus-1]-us[nus-2]) + $
              strmid(base, us[nus-1], strlen(base)-us[nus-1])
  ;; form actual filename
  psfile = 'axlv2_fmcomp_' + doyfr_str + '.ps'
  print, psfile

  ;; --- plot --- 
  if (not noplot) then $
    fmcomp, fmcfile='axlv2_fmcomp.dat', pccfile=pccfiles[ifile],$
      etsfile=etsfiles[ifile], etsdata=ets, fmcdata=fmc,$
      psfile=psfile, subsec=subsec, steps=steps

  ;; --- sum ---
  if (ifile eq 0) then begin
    sum_ets = ets
  endif else begin
    for n=0,n_elements(ets)-1 do begin
      sum_ets[n].mat += ets[n].mat
    endfor
  endelse

endfor

;; do plot of sum
;; note: pcc and ets filenames are dummy
if (not noplot) then $
  fmcomp, fmcfile='axlv2_fmcomp.dat', pccfile=pccfiles[0], steps=steps,$
  etsfile=etsfiles[0], etsdata=sum_ets, fmcdata=fmc, /noread

;; ----------------------------------------------------------------------------
;; clean up and get out
;; ----------------------------------------------------------------------------

clean_exit:

end
