; Filename: ave_q_plot.pro
;
; Description:
;   Plot average charge for selected element from ACE/SWICS Level II
;   nvt read_ascii structure.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   19Nov2003   jmr   initial coding for Oct-Nov2003 CME analysis
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
pro ave_q_plot, file=file, data=d, element=element, position=position,$
                yrange=yrange, ytitle=ytitle, _EXTRA=extra_keywords

thisprog = 'ave_q_plot'

;; find all doyfrs in data
doyfrs = d.doyfr(uniq(d.doyfr))
;; limit doyfrs to !x.range if specified
if (!x.range[0] gt 0. and !x.range[1] gt 0.) then begin
  i_x_range = where(doyfrs ge !x.range[0] and doyfrs le !x.range[1],$
                    nwhere)
  if (nwhere le 1) then begin
    print, thisprog+' -W- no data for element '+element+$
      ' in xrange = ', !x.range
    goto, exit
  endif

  doyfrs = doyfrs[i_x_range]
endif
ndoyfrs = n_elements(doyfrs)

ave_q = make_array(ndoyfrs, /float, value=-1.0)
bad_fe_df = make_array(ndoyfrs,2, /float, value=-1.0)

elem_pattern = element + '[0-9]{1,2}\+'

for idoyfr=0,ndoyfrs-1 do begin
  doyfr_str = string(format='(F6.2)', doyfrs[idoyfr])

  ;; select ions of specified element
;  i_elem = where( (strpos(d.ion, element) ge 0) and $
  i_elem = where( (stregex(d.ion, elem_pattern) ge 0) and $
                  d.doyfr eq doyfrs[idoyfr], ni_elem)
  if (ni_elem le 0) then begin
    print, thisprog+' -E- no data for '+element+' at doyfr = '+$
      doyfr_str
    goto, next
  endif

  ;; calculate average charge
  sum_q = 0.0
  total_n = 0.0
  nions = n_elements(i_elem)
  for nion=0,nions-1 do begin
    ion_parse, ion=d.ion[i_elem[nion]], state=state
    if (d.n[i_elem[nion]] gt 0.) then begin
      sum_q = sum_q + state*d.n[i_elem[nion]]
      total_n = total_n + d.n[i_elem[nion]]
    endif
  endfor

  if (total_n gt 0.) then ave_q[idoyfr] = sum_q/total_n

  print, thisprog+' -I- ave_q = '+string(format='(F6.2)',ave_q[idoyfr])$
    +' for '+element+ ' at doyfr = '+doyfr_str

  next:  ;; tag to goto when there is no data

endfor

if (not keyword_set(ytitle)) then ytitle='<Q!I'+element+'!N>'

;; plot -- assuming psfile/device stuff done by caller
plot, doyfrs, ave_q, ytitle=ytitle, position=position,$
  yrange=yrange, yticks=3, ytickname=[' ','','',''], _EXTRA=extra_keywords
;stop
exit:
return
end

