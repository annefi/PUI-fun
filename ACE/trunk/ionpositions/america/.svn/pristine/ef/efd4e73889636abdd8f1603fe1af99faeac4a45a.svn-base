; Filename: 
;
; Description:
;   
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: sys_var.pro,v 1.1 2005/03/21 14:30:50 jraines Exp $
;
; Major Modification History
;   ddmmmyyyy   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
pro sys_var, save=save, restore=restore

common sys_var, p, x, y, z

if (keyword_set(save)) then begin
  p = !p
  x = !x
  y = !y
  z = !z
endif

if (keyword_set(restore)) then begin
  !p = p
  !x = x
  !y = y
  !z = z
endif

return
end
