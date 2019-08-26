; Filename: s2doyfr.pro
;
; Description:
;   Convert seconds since 1970 to year and day of year fraction.
;
; Author: Jim Raines (jmr), Jessica Hovater Feeman (JAHF)
;
;   JAHF - 30Jul2003 - Adapted from s2doyfr.pro.
;
; CVS controlled:
; $Id: s2doyfr.pro,v 1.6 2003/11/19 21:20:57 jraines Exp $
;   
; Major Modification History
;   11Jun2003   jmr   initial coding
;   30Jul2003   JAHF  more coding
;   06Nov2003   jmr   changed output from string to float
;   18Nov2003   jmr   added formating in ss1970 string conv. formatting
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   ss1970      seconds since 1970
; O   [returned]  [year, day of year fraction]

function s2doyfr, ss1970

ss1970 = float(ss1970)

; Call 'tc' and pass ss1970
spawn, '$ACESW/bin/tc ' + string(format='(F16.0)',ss1970), result

; Split up array returned into individual elements
tcArr = STRSPLIT(result[0], /EXTRACT)

doy = fix(tcArr[3])
year = fix(tcArr[6])
hr = fix(tcArr[7])
min = fix(tcArr[8])
sec = fix(tcArr[9])

; Compute doy fraction
fr = ((hr * 3600L) + (min * 60) + sec) / float(86400)

; Build variable consisting of doy and doy fraction
doyfr = doy + fr

;ydoyfr = make_array(2,/float)
ydoyfr = [year, doyfr]

return, ydoyfr
end


