; Filename: splitYdoy.pro
;
; Description:
;   Split yyyydoy string into year (yyyy) and day of year (doy)
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: split_ydoy.pro,v 1.2 2005/05/05 21:11:29 jraines Exp $
;
; Major Modification History
;   27Jan2005   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   ydoy        year-doy as int, long, float or string
; O   [returned]  [year, doy]
; [I] strings     optionally return year and doy as strings
function split_ydoy, ydoy, strings=strings

thisprog = 'split_ydoy'

;; default value
result = [-1,-1]

;; determine type
s = size(ydoy)
type = s[n_elements(s)-2]

;; exit if not a scalar
if (s[0] ne 0) then begin
  print, thisprog+' -F- only scalar expressions accepted'
  goto, exit
endif

case type of
  ;; long int
  ;; ------------------------------------------------------------
  3: begin
    year = long(ydoy/1000)
    doy = ydoy - year*1000
    result = [year, doy]
    if (keyword_set(strings)) then begin
      year_str = string(format='(I4.4)',year)
      doy_str = string(format='(I3.3)',doy)
      result = [year_str, doy_str]
    endif
  end

  ;; double
  ;; ------------------------------------------------------------
  5: begin
    year = double(fix(ydoy/1000.))
    doy = ydoy - year*1000.D
    result = [year, doy]

    if (keyword_set(strings)) then begin
      year_str = string(format='(I4.4)',fix(year))
      doy_str = string(format='(F7.3)',doy)
      result = [year_str, doy_str]
    endif
  end

  ;; string
  ;; ------------------------------------------------------------
  7: begin

    year_str = strmid(ydoy, 0, 4)

    if (stregex(ydoy, '\.', /bool)) then  begin
      doy_str = strmid(ydoy, 4, strlen(ydoy)-4)
      doy = float(doy_str)
      year = float(year_str)
    endif else begin
      doy_str = strmid(ydoy, 4, 3)
      doy  = fix(doy_str)
      year = fix(year_str)
    endelse


    result=[year,doy]

    if (keyword_set(strings)) then result=[year_str,doy_str]
  end
  
  ;; none of the above
  ;; ------------------------------------------------------------
  else: begin
    print, thisprog+' -F- type ('+string(format='(I1)',type)+') not supported'
    print, '+ ydoy must be long(3), double(5) or string'
    print, '+ ydoy cannot be represented accurately as int or float'
    goto, exit
  end
endcase

exit:
return, result
end
