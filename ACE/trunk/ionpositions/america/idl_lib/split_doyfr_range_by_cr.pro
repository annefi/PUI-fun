; Filename: split_doyfr_range_by_cr.pro
;
; Description:
;   Split a give day of year fraction range into complete Carrington rotations.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: split_doyfr_range_by_cr.pro,v 1.6 2005/05/06 21:16:28 jraines Exp $
;
; Major Modification History
;   22Apr2005   jmr   Initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   arg1        doyfr range array, [start_ydoyfr, end_ydoyfr]
; O   [returned]  array of pairs of doyfr ranges, suitable for using
;                 as xrange in a timeseries plot
; [I] exact_range first and last range returned start and end with
;                 exact doyfr specified  in arg1.  This can make them
;                 less than a full CR wide.
; [I] omit_year   omit year, user must apply common sense near end of year
function split_doyfr_range_by_cr, doyfr_range, exact_range=exact_range,$
                                  omit_year=omit_year

;; find CRs for ends
;; note: double(long()) syntax used to remove (truncate, not round) cr fraction
start_cr = double(long(ydoyfr2crfr(doyfr_range[0])))
stop_cr  = double(long(ydoyfr2crfr(doyfr_range[1])))

;;print, 'start_cr = ', start_cr
;;print, 'stop_cr = ', stop_cr

;; note: +1 extends range beyond last ydoyfr, which is typically
;; desired to encompass all data within ydoyfr range
num_cr = fix(abs(stop_cr - start_cr)) + 1

cr_ranges = make_array(2,num_cr, /double)

for ncr=0, num_cr-1 do begin

  cr_ranges[0,ncr] = crfr2ydoyfr(start_cr+double(ncr))

  if (keyword_set(exact_range) and ncr eq 0) then $
    cr_ranges[0,ncr] = doyfr_range[0]
  
  cr_ranges[1,ncr] = crfr2ydoyfr(start_cr+double(ncr)+1)

  if (keyword_set(exact_range) and ncr eq num_cr-1) then $
    cr_ranges[1,ncr] = doyfr_range[1]

  if (keyword_set(omit_year)) then begin
    ;; split_ydoy returns a 2 element array, [year, doy].  We want doy
    ;; only here hence the weird ()[1] syntax
    cr_ranges[0,ncr] = (split_ydoy(cr_ranges[0,ncr]))[1]
    cr_ranges[1,ncr] = (split_ydoy(cr_ranges[1,ncr]))[1]

    ;; fix ends
    if (ncr eq 1 and cr_ranges[0,0] gt cr_ranges[0,1]) then begin
      cr_ranges[0,0] = -(365. + is_leap((split_ydoy(cr_ranges[0,0]))[0]) - $
        cr_ranges[0,0])
    endif
    if (ncr eq num_cr-1 and $
        cr_ranges[1,num_cr-1] lt cr_ranges[1,num_cr-2]) then $
      cr_ranges[1,ncr] += 365. + is_leap((split_ydoy(cr_ranges[1,ncr]))[0])

  endif

endfor

return, cr_ranges
end

