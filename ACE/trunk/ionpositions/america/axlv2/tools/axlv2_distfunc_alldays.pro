; Filename: axlv2_distfunc_allts.pro
;
; Description:
;
;   Run axlv2 distribution function analysis (axlv2_distfunc) on all
;   timesteps in a directory.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   Uses a pattern + wildcard to find all the
;   axlv2_distfunc_yyyydoy.dat files in a directory.
;   
; Revision controlled by CVS:
; $Id: axlv2_distfunc_alldays.pro,v 1.1 2005/01/05 15:23:33 jraines Exp $
;
; Major Modification History
;   29Nov2004   jmr   Adapted from fmcomp_allts.pro
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   pattern     data file pattern, e.g. pattern='axlv2_' 
;pro axlv2_distfunc_allts

;; ----------------------------------------------------------------------------
;; set up
;; ----------------------------------------------------------------------------
thisprog = 'axlv2_distfunc_allts'

;; ----------------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------------

;; ----------------------------------------------------------------------------
;; find files
;; ----------------------------------------------------------------------------
spawn, '\ls axlv2_distfunc_*.dat', dffiles
spawn, '\ls axlv2_nvt_*.dat', nvtfiles

num_dffiles = n_elements(dffiles)
num_nvtfiles = n_elements(nvtfiles)

if (num_dffiles ne num_nvtfiles) then begin
  print, thisprog + ' -W- number of files differ; exiting...'
  ; goto, done
endif

;; ----------------------------------------------------------------------------
;; do plots and sum
;; ----------------------------------------------------------------------------
for ifile = 0, num_dffiles-1 do begin

  ;; --- construct filename ---
  ;; get rid of path and extension
  file_parse, file=dffiles[ifile], base=base
  ;; find the underscores which delimit the doy and fraction
  us = strsplit(base, '_')
  nus = n_elements(us)
  ;; grab the ydoy from knowledge of underscore positions
  ;; note: ydoy is after last (hence -1) '_' 
  ydoy_str = strmid(base, us[nus-1], us[nus-1]-us[nus-2]) 
  ;; form actual filename
  psfile = 'axlv2_distfunc_' + ydoy_str + '.ps'
  print, psfile

  ;; --- run distfunc ---
  axlv2_distfunc, dffile=dffiles[ifile], dfdata=df, $
                  nvtfile=nvtfiles[ifile], nvtdata=nvt, $
                  tag=tag, ions=ions, relerr=relerr

endfor

;; ----------------------------------------------------------------------------
;; clean up and get out
;; ----------------------------------------------------------------------------
done:

end
