; Filename: doy2date.pro
;
; Description:
;   Converts year-doy to dd-Mmm-yyyy.  Input year can be is years
;   since 1900 (UARS convention).
;
; Author:  HRDI Team
;          Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: doy2date.pro,v 1.2 2004/01/05 21:38:33 jraines Exp $
;
; Major Modification History
;   19May2003   jmr   initial retrieval from HRDI system.
;   05Jan2004   jmr   added noyear argument
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   doy         [yy]yydoy, year day of year where year is years
;                 since 1900 or four digit year, e.g. for 2003 302,
;                 doy could be 103302 or 2003302 (long or float).
; I   [noyear]    do not put year on output string
; O   [returned]  date in format dd-Mmm[-yyyy]
function doy2date,doy, noyear=noyear

common doy2date, firstday, leapdays, monthnames

if n_elements(firstday) le 0 then begin ; is firstday initialized?
;d;		print, 'initializing doy2date block'
   ;no, fill array with day of year for the first of each month
  ;;		 jan, feb, mar, apr, may, jun
  firstday = 	[  1,  32,  60,  91, 121, 152, $
                   182, 213, 244, 274, 305, 335  ]
  ;;		 jul, aug, sep, oct, nov, dec

  ;;		 jan, feb, mar, apr, may, jun
  leapdays = 	[  1,  32,  61,  92, 122, 153, $
                   183, 214, 245, 275, 306, 336  ]
  ;;		 jul, aug, sep, oct, nov, dec

  monthnames = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', $
                'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec' ]
endif

n_doy  = n_elements(doy)
result = strarr(n_doy)

for i = 0, n_doy-1 do begin
  ;; handle both 4 digit years and years since 1900
  if (doy(i) ge 1900000) then offset = 0 else offset = 1900
  year = doy(i) / 1000 + offset
  day  = doy(i) mod 1000
;d;		print, i, doy(i), year, day

  if day gt 0 and day le 366 then begin
    if year mod 4 ne 0 then begin
      ;; not a leap year
      ind   = where (day ge firstday,nd)
;d;   print, 'norm year, nd: ', nd, ' ind: ', ind
      month = monthnames(ind(nd-1))
      dom   = day - firstday(ind(nd-1)) + 1
    endif else begin
      ind   = where (day ge leapdays,nd)
;d;   print, 'leap year, nd: ', nd, ' ind: ', ind
      month = monthnames(ind(nd-1))
      dom   = day - leapdays(ind(nd-1)) + 1
    endelse

;d; print, 'dom, mon, yr', dom, month, year
    if (keyword_set(noyear)) then begin ; do not include year
      result(i) = $
        string(dom, month,format="(I2, '-', A3)",/print)
    endif else begin
      result(i) = $
        string(dom, month, year,format="(I2, '-', A3, '-', I4)",/print)
    endelse

    if ( day eq 366 ) and ( year mod 4 ne 0 ) then $
      result(i) = '00-bad-date'
  endif else begin
    result(i) = '00-bad-date'
  endelse
;d; print, result(i)
endfor

if n_doy eq 1	$
  then	return, result(0) $
else	return, result

end
