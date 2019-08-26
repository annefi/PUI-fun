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
; $Id: read_slices.pro,v 1.1 2003/09/05 17:40:35 jraines Exp $
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
; I     [noread]         Optionally turn off reading of slice data
;                        (use struct. passed in)
pro read_slices, file=file, slices=slices

thisprog = 'read_slices'

;; set up E-T slice file
if (not keyword_set(file)) then file = 'axlv2_p_slices.dat'
get_lun, lun
openr, lun, file

;; read in E-T matrix
;; ------------------
spawn , 'grep -c AXLV2 '+file, nslicemax
nslicemax = fix(nslicemax[0])
for nslice= 0,nslicemax-1 do begin
  print, "read_slices - reading tof-esd mat for nslice " + $
    string(format=(I2),nslice)
  
  ;; actually do read
  smread2, lun=lun, data=smd
  
  ;; create array of structures the first time
  if nslice eq 0 then slices = replicate( smd, nslicemax)

  ;; insert recently read structure into array
  slices[nslice] = smd
  
endfor

close, lun
free_lun, lun

return
end
