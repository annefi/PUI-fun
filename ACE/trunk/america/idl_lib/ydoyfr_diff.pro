; Filename: crfr2ydoyfr.pro
;
; Description:
;   Convert day of year fraction (doyfr) to Carrington Rotation fraction.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: ydoyfr_diff.pro,v 1.1 2005/04/23 06:36:46 jraines Exp $
;
; Major Modification History
;   22Apr2005   jmr   Initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   ydoyfr1,2   year/day-of-year fractions to be subtracted
; O   [returned]  returns difference in absolute fractional days
;
function ydoyfr_diff, ydoyfr1, ydoyfr2

;; arrange so 2 > 1
if (ydoyfr1 gt ydoyfr2) then begin
  tmp = ydoyfr2
  ydoyfr2 = ydoyfr1
  ydoyfr1 = tmp
endif

;; strip out years
year2 = fix(ydoyfr2 / 1000.)
year1 = fix(ydoyfr1 / 1000.)

doyfr2 = ydoyfr2 - (year2*1000.)
doyfr1 = ydoyfr1 - (year1*1000.)

;; count up (damn!) leap days
leap_days = 0
for year=year1,year2-1 do begin
  leap_days += is_leap(year)
endfor

;; find number of days difference
;; () for clarity only
ndays = (doyfr2 + float(year2-year1)*365. + leap_days) - doyfr1

return, ndays
end
