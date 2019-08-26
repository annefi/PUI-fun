; Filename: hms2fr.pro
;
; Description:
;   Convert 3 element hour, minute, second array to fraction of day.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: hms2fr.pro,v 1.1 2005/04/23 06:36:46 jraines Exp $
;
; Major Modification History
;   22Apr2005   jmr   Initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   arg1        [h, m, s]
; O   [returned]  fraction of the day
function hms2fr, hms

fr = ( float(hms[0])*3600. + float(hms[1])*60. + float(hms[2]) ) / 86400.

return, fr
end
