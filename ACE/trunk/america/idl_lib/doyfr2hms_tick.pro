; Filename: doyfr2hms_tick.pro
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
; $Id: doyfr2hms_tick.pro,v 1.3 2004/08/25 17:50:54 jraines Exp $
;
; Major Modification History
;   17Nov2003   jmr   initial coding
;   25Aug2004   jmr   changed name of function from dhms_tick to match
;                     filename and be more descriptive
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   axis        which axis (x, y, or z); unused
; I   index       ?, unused
; I   value       seconds since 1970
; I   level       level of tick mark; unused
; O   [returned]  doy:hh:mm:ss string

function doyfr2hms_tick, axis, index, value, level

hms = doyfr2hms(value)
dhms = hms.dhms

;print, 'dhms_tick: ', dhms

return, dhms
end

