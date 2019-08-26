; Filename: doyfr2hms.pro
;
; Description:
;   Convert day-of-year fraction to hours, minutes and seconds.
;
; Author: Jim Raines (jmr)
;
; Method:
;
; Revision controlled by CVS:
; $Id: doyfr2hms.pro,v 1.3 2003/11/07 22:21:49 jraines Exp $
;   
; Major Modification History
;   07Nov2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   doyfr       day of year fraction
;
; O   [returned]  hms time structure, below.
;
function doyfr2hms, doyfr

;; set up structure
hms = $
  { hms3,                      $ ; name of structure
    hr: 0,                    $ ; hours
    min: 0,                   $ ; minutes
    sec: 0,                   $ ; seconds
    doy: 0.0,                 $ ; day of year
    fr:  0.0,                 $ ; fraction of day
    dhms: ''                  $ ; doy:hh:mm:ss as a string
  }

hms.doy = fix(doyfr)
hms.fr  = doyfr - float(hms.doy)
totsec  = hms.fr*24.0*60.0*60.0
hms.hr  = fix(totsec/60.0/60.0)
totsec  = totsec - float(hms.hr*60.0*60.0)
hms.min = fix(totsec/60.0)
totsec  = totsec - float(hms.min*60.0)
hms.sec = totsec

hms.dhms =  string(format='(I3.3)',hms.doy) + ':' + $
    string(format='(I2.2)',hms.hr) + ':' + $
    string(format='(I2.2)',hms.min) + ':' + $
    string(format='(I2.2)',hms.sec)

return, hms
end
