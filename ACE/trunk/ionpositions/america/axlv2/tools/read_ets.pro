; Filename: read_ets.pro
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
; $Id: read_ets.pro,v 1.1 2003/09/05 17:40:35 jraines Exp $
;
; Major Modification History
;   15Nov2002   jmr   Adapted from fmfit.pro
;
; Arguments
; I/O   argument         description
; ---   --------         -----------
; I     etsfile          E-T slice file produced by axlv2
; O     ets              array of smread2 structures containing E-T
;                        slices and meta information. NOTE: Index into
;                        ets is deflection voltage step - 2, i.e., ets[0] is
;                        for step 2.
pro read_ets, file=file, ets=ets

;; set up E-T slice file
if (not keyword_set(file)) then file = 'axlv2_et_slices.dat'
get_lun, lun
openr, lun, file

;; read in E-T matrix
;; ------------------
for step= 2, 59 do begin
  print, "read_ets - reading tof-esd mat for step " + string(format=(I2),step)
  
  ;; nstep is position in arrays of data corresponding to E/q step, step
  ;; this is needed so arrays can start at zero 
  nstep = step - 2 

  ;; actually do read (note: smd is smd(tof,esd))
  smread2, lun=lun, data=smd
  
  ;; create array of structures the first time
  ;; 60 steps - 2 EDBs not analyzed (0 and 1) + 1 to get both ends
  if step eq 2 then ets = replicate( smd, 59-2+1)

  ;; insert recently read structure into array
  ets[nstep] = smd
  
endfor

close, lun
free_lun, lun

return
end
