; Filename: axlv2_nvt_abun.pro
;
; Description:
;   Returns ACE/SWICS Level 2 elemental abundance versus time from 
;   n, v, vth data.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: axlv2_nvt_abun.pro,v 1.1 2005/03/14 16:53:39 jraines Exp $
;
; Major Modification History
;     Dec2003  jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   data        data structure containing nvt data
; I   element     element 
function axlv2_nvt_abun, data=d, element=element

doyfrs = d.doyfr(uniq(d.doyfr))
ndoyfrs = n_elements(doyfrs)

elem_pattern = element + '[0-9]{1,2}\+'

abun = make_array(ndoyfrs, /float)
for idoyfr=0,ndoyfrs-1 do begin
  doyfr_str = string(format='(F6.2)', doyfrs[idoyfr])

  ;; select ions of specified element
  i_elem = where( (stregex(d.ion, elem_pattern) ge 0) and $
                  d.doyfr eq doyfrs[idoyfr], ni_elem)
  if (ni_elem le 0) then begin
    print, thisprog+' -E- no data for '+element+' at doyfr = '+$
      doyfr_str
    goto, next
  endif

  ;; sum over ions
  abun[idoyfr] = total(d.n[i_elem], /nan)

  next:
endfor

return, abun
end
  
