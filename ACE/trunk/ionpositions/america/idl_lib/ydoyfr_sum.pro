; Filename: ydoyfr_sum.pro
;
; Description:
;   Add two ydoyfr values, properly considering leap years and 365 days/year.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: ydoyfr_sum.pro,v 1.1 2005/04/23 06:36:46 jraines Exp $
;
; Major Modification History
;   22Apr2005   jmr   Initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   arg1        year/day-of-year fraction to which to add ndays
; I   arg2        ndays to add
; O   [returned]  returns sum
;
function ydoyfr_sum, ydoyfr, ndays


;; count it up
for i=1,ndays do begin
  year = fix(ydoyfr / 1000.)
  doyfr = ydoyfr - (year*1000.)
  days_this_year = 365. + float(is_leap(year))
  if (doyfr ge days_this_year ) then begin
    ;;                        fractional part of doyfr
    ydoyfr = (year+1)*1000. + doyfr/days_this_year
  endif else ydoyfr += 1.0D0
endfor

return, ydoyfr
end
