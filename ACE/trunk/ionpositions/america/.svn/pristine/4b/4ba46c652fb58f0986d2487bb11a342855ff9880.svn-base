; Filename: date2doy.pro
;
; Description:
;   Convert date string of type 'dd-Mmm-yy' to 2-element array, [year,doy].
;
; Author: Jim Raines (jmr)
;
; Method:
;   Function date2doy calls date2doy_uars and then splits up the
;   output and converts to actual year.
;   
; Revision controlled by CVS:
; $Id: date2doy.pro,v 1.2 2004/02/27 21:15:15 jraines Exp $
;
; Major Modification History
;   27Feb2004   jmr   Adapted from HRDI's date2doy.pro by Dave Gell
;
; Usage:
; IDL> print, date2doy('27-Feb-2004')
;        2004          58

function	date2doy_uars, date
	; 
	; convert date dd-mon-year to
	; year and day-of-year (yyyddd, where yyy is years since 1900)
	
	common doy2date, firstday, leapdays, monthnames

	if n_elements(firstday) le 0 then begin		; is firstday initialized?
		;d;print, 'initializing doy2date block'
		;no, fill array with day of year for the first of each month
		;		 jan, feb, mar, apr, may, jun
		firstday = 	[  1,  32,  60,  91, 121, 152, $
				 182, 213, 244, 274, 305, 335  ]
		;		 jul, aug, sep, oct, nov, dec

		;		 jan, feb, mar, apr, may, jun
		leapdays = 	[  1,  32,  61,  92, 122, 153, $
				 183, 214, 245, 275, 306, 336  ]
		;		 jul, aug, sep, oct, nov, dec

		monthnames = [	'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', $
				'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec' ]
	endif

;
;  The variable RESULT must be of the same length as the input DATE, 
;  either a single variable or an array.
;
	n_dates = n_elements(date)
	result  = long(date)

	months = strupcase(monthnames)

	for i = 0, n_dates-1 do begin
		; parse date into day-of-month, month_name, & year
		; date dd-mon-19yy

		loc = strpos(date(i), '-' )
		dom = fix ( strmid(date(i), 0, loc) )
		month = strupcase( strmid(date(i), loc+1, 3) )
		year  = long ( strmid(date(i), loc+5, 4) )

		;d;print, 'loc, dom, month, year:', loc, dom, ' ',month, year
		;
		; if not a leap year then
		;	find start-of-month in firstday
		; else
		;	find start-of-month in leapdays
		; endif

		idx = where ( months eq month)
		if year mod 4 ne 0			$
		then	start = firstday(idx(0))	$
		else	start = leapdays(idx(0))

		;
		; form day-of-year = day-of-month + start-of-month-1

		doy = dom + start - 1

		;d;print, "dom, start, doy: ", dom, start, doy
		
		result(i) = 1000 * (year-1900) + doy

	endfor
	return, result
end

function date2doy, date

;; change years since 1900 to real year  
ydoy = date2doy_uars(date)+1900000

;; split off year
year = ydoy/1000

;; split off doy
doy = ydoy - year*1000

return, [year, doy]
end

