; Filename: crfr2ydoyfr.pro
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
; $Id: crfr2ydoyfr.pro,v 1.3 2005/05/05 19:08:19 jraines Exp $
;
; Major Modification History
;   22Apr2005   jmr   Initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   arg1        Carrinton rotation fraction
; O   [returned]  corresponding day of year fraction
; [I] save_file   optionally specify an IDL save file into which to
;                 save (if cr_file is specified) or from which to load (if not)
; [O] data        optionally specify a variable for returning the CR
;                 data structure
function crfr2ydoyfr, crfr, file=file, save_file=save_file, data=crd

thisprog = 'crfr2ydoyfr'

;; 
;;----------------------------------------------------------------------
;; read CR data structure
;;----------------------------------------------------------------------
if (keyword_set(save_file)) then restore, file=save_file $
else restore, file='cr_table.save'

;;----------------------------------------------------------------------
;; look for nearest CR
;;----------------------------------------------------------------------
index = -1
for ndat=0, n_elements(crd)-1 do begin
  if (crd[ndat].cr ge crfr) then begin
    index = ndat-1
    break
  endif
endfor

if (index lt 0) then begin
  print, thisprog+' -F- could not find a ydoyfr for crfr =' + $
  string(format='(F10.2)', crfr)
  crfr = -1
  goto, exit_now
endif

;;----------------------------------------------------------------------
;; determine fraction and assemble
;;----------------------------------------------------------------------
ndays =  float(abs(crfr - crd[index].cr)) * $
        ydoyfr_diff(crd[index].ydoyfr,crd[index+1].ydoyfr)
;;print, 'ndays = ', ndays
ydoyfr = double( ydoyfr_sum(crd[index].ydoyfr, ndays) )

;;----------------------------------------------------------------------
;; done!
;;----------------------------------------------------------------------
exit_now:

return, ydoyfr
end

