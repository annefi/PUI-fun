; Filename: file_exists.pro
;
; Description:
;   Test to see if argument file exists.
;
; Author: Jim Raines (jmr)
;
; Method:
;   Uses bash from spawn.  Note:  This starts a shell for each
;   invocation and may not be most efficient method for checking many
;   files repeatedly.
;   
; Revision controlled by CVS:
; $Id: file_exists.pro,v 1.1 2003/11/03 15:40:30 jraines Exp $
;
; Major Modification History
;   03Nov2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   (returned)  1=>file exists, 0=>otherwise
; I   [/verbose]  print existence message
function file_exists, file, verbose=verbose

;; build command
cmd = 'f='+file+'; if [ -e $f ]; then echo 1; fi'

;; check file
spawn, cmd, result

;; test and return
if (result[0] eq 1) then begin
  retval=1 
  if (keyword_set(verbose)) then print, file, ' exists'
endif else begin
  retval=0
  if (keyword_set(verbose)) then print, file, ' DOES NOT exist'
endelse

return, retval
end

