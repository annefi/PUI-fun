; Filename: ydoyfr2crfr.pro
;
; Description:
;   Convert day of year fraction (doyfr) to Carrington Rotation fraction.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: ydoyfr2crfr.pro,v 1.2 2005/05/05 18:09:49 jraines Exp $
;
; Major Modification History
;   22Apr2005   jmr   Initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   arg1        day of year fraction
; O   [returned]  Carrington rotation fraction
; [I] save_file   optionally specify a save file from which to read
;                 the CR data structure
; [O] data        optionally specify a variable for returning the CR
;                 data structure
function ydoyfr2crfr, ydoyfr, file=file, data=crd

thisprog = 'ydoyfr2crfr'

;;----------------------------------------------------------------------
;; restore CR data structure
;;----------------------------------------------------------------------
if (keyword_set(save_file)) then restore, file=save_file $
else restore, file='cr_table.save'

;; ----------------------------------------------------------------------
;; look for nearest CR
;; ----------------------------------------------------------------------
index = -1
for ndat=0, n_elements(crd)-1 do begin
  if (crd[ndat].ydoyfr ge ydoyfr) then begin
    index = ndat-1
    break
  endif
endfor

if (index lt 0) then begin
  print, thisprog+' -F- could not find a carrington rotation for ydoyfr =' + $
  string(format='(F10.2)', ydoyfr)
  crfr = -1
  goto, exit_now
endif

;; ----------------------------------------------------------------------
;; determine CR and fraction
;; ----------------------------------------------------------------------
cr_frac = ydoyfr_diff(ydoyfr, crd[index].ydoyfr) / $
          ydoyfr_diff(crd[index].ydoyfr,crd[index+1].ydoyfr)

crfr = double(crd[index].cr) + cr_frac

exit_now:

return, crfr
end

