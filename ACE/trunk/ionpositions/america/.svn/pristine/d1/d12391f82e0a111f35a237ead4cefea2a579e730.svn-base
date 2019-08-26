; Filename: ion_parse.pro
;
; Description:
;   Parse an ion name string, e.g. O6+, Fe16+, or 20Ne8+, into its
;   component parts of isotope (if present), element name and charge.
;
; Author: Jim Raines (jmr)
;
; Method:
;   
; Revision controlled by CVS:
; $Id: ion_parse.pro,v 1.2 2004/10/18 19:31:31 jraines Exp $
;
; Major Modification History
;   11Nov2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   ion         String ion name, e.g. O6+, Fe16+, or 20Ne8+
; O   iso         isotope mass (integer) if present, -1 otherwise
; O   elem        element name (string)
; O   state       oxidation state (integer)
; I   [/verbose]  turn on verbose output
; I   [/strings]  return all parts as strings instead

pro ion_parse, ion=ion, iso=iso, elem=element,state=state,verbose=verbose,$
               strings=strings

;; isotope mass
pattern_start = stregex(ion, '^[0-9]{1,2}', /fold_case, length=pattern_len)
if (pattern_start ge 0) then begin
  iso = strmid(ion,pattern_start,pattern_len) ;; -1 gets rid
endif else begin
  iso = '-1'
endelse
if (not keyword_set(strings)) then iso = fix(iso)

;; element
element = ''
pattern_start = stregex(ion, '[a-z]{1,2}', /fold_case, length=pattern_len)
element = strmid(ion,pattern_start,pattern_len)

;; state
pattern_start = stregex(ion, '[0-9]*\+', length=pattern_len)
state = strmid(ion,pattern_start,pattern_len-1) ;; -1 removes + sign
if (element eq 'H') then state = 1 ; work-around H+ notation (no charge number)
if (not keyword_set(strings)) then state = fix(state)

if (keyword_set(verbose)) then $
  print, 'ion = ',ion,', iso = ',iso,', element = ', element,$
  ', state = ', state

return
end


;; un-comment for debugging
;ions = ['O6+','Fe16+','20Ne8+', '3He1+']
;for nion=0,n_elements(ions)-1 do begin
;  ion = ions[nion]
;  ion_parse, ion=ion, /verbose, /strings

;endfor

;end

