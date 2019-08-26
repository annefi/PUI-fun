; Filename: doy2date_tick.pro
;
; Description:
;   Makes date dd-Mmm tick marks from day of year input.
;
; Author: Jim Raines (jmr)
;
; Method:
;
; Revision controlled by CVS:
; $Id: doy2date_tick.pro,v 1.2 2004/03/29 20:04:46 jraines Exp $
;   
; Major Modification History
;   05Jan2004   jmr   initial coding
;
; Arguments:
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   axis        which axis (x, y, or z); UNUSED
; I   index       ?, UNUSED
; I   value       day of year
; I   level       level of tick mark; UNUSED
; O   [returned]  dd-Mmm string

function doy2date_tick, axis, index, value, level

;; be sure value is a float or doy2date will get messed
value = value + 0.0

date = doy2date(value,/noyear)

return, date
end

