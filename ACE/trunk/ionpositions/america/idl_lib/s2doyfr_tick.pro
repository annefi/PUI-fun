; Filename: s2doyfr_tick.pro
;
; Description:
;   Produces doyfr string from seconds since 1970 suitable for use as
;   tick-producing function in plot, 
;   e.g., plot, ..., xtickformat='s2doyfr_tick'
;
; Author: Jim Raines (jmr)
;
; Method:
;   See description of user-defined tick function in IDL help on 
;   [xyz]tickformat.
;   
; Revision controlled by CVS:
; $Id: s2doyfr_tick.pro,v 1.2 2003/11/20 14:37:50 jraines Exp $
;
; Major Modification History
;   17Nov2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   axis        which axis (x, y, or z); unused
; I   index       ?, unused
; I   value       seconds since 1970
; O   [returned]  day of year fraction string

function s2doyfr_tick, axis, index, value, level
time = s2doyfr(value)
doyfr = string(format='(F6.2)',time[1])
return, doyfr
end

