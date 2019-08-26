; Filename: isLeap.pro
;
; Description:
;   Determines whether argument year is leap year or not.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; CVS controlled:
; $Id: is_leap.pro,v 1.2 2003/06/11 21:02:19 jraines Exp $
;
; Major Modification History
;   11Jun2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   year        year
; O   [returned]  1 => leap year, 0 => not leap year
function is_leap, year

isLeap = 0

if ((year mod 100) eq 0) then begin ;; year is a century
  if ((year mod 400) eq 0) then isLeap = 1
endif else begin
  if ((year mod 4) eq 0) then isLeap = 1
endelse

return, isLeap
end
