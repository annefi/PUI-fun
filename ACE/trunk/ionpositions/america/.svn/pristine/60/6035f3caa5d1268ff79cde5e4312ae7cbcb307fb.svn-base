; Filename: get_ydoy.pro
;
; Description:
;   Get year-day-of-year (yyyydoy) from string.  Designed to be used
;   with filenames of the following form:
;
;                    some_name_here.yyyydoy.ext
;
; Author: Jim Raines (jmr)
;
; Method:
;   The yyyydoy string must be delimited by dots ('.'), the trailing
;   one being the last dot in the string.
;   
; Major Modification History
;   03Mar2003   jmr   initial coding
;

function get_ydoy, file

;; find location of all dots
;; note: location 0 is returned erroneously in element 0
dots = strsplit(file, '\.')

ndots = n_elements(dots)

;; extract string between last dot and previous dot (next to the last dot)
ydoy = strmid(file, dots[ndots-2], dots[ndots-1]-dots[ndots-2]-1)

return, ydoy
end
