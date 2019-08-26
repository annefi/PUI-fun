;Filename: axlv2_deliv_qdist.pro
;
;Author: Laura Emig
;
;Purpose: plot average charge distribution
;
;Must choose doy range and ion (correct file)
;something wrong w/ average charge----pry [doyfr] and total_n

file='axlv2_deliv_O_qdist_2003326_2003350.dat'
psfile= 'axlv2_deliv_qdist_2003326_200335.ps'

;;read data
restore, file='axlv2_deliv_qdist_template.save'
d = read_ascii(file, template=template, comment='#')

;; set up postscript plot
psplt, file=psfile, /color      ; open PS file
loadct, 34
fix_ct_ends

doyfrs = d.doyfr
ndoyfrs = n_elements(doyfrs)
ave_q = make_array(ndoyfrs, /float, value=-1.0)

for idoyfr=0,ndoyfrs-1 do begin
  doyfr_str = string(format='(F6.2)',doyfrs[idoyfr])
;  print, 'working on '+doyfr_str

  ;; choose current doyfr
  i_doyfr = where (d.doyfr eq doyfrs[idoyfr], nions)
  if (nions lt 0) then begin
    print, thisprog+' -E- no data at doyfr = '+doyfr_str
    goto, next_doyfr
  endif

  ;; calculate average charge
  ave_q[idoyfr] = 0.0
  for nion=0,nions-1 do begin
    if (d.rel_abun[i_doyfr[nion]] gt 0.) then begin
      ave_q[idoyfr] = ave_q[idoyfr] + d.chg[i_doyfr[nion]]*d.rel_abun[i_doyfr[nion]]
    endif
  endfor

 next_doyfr:
endfor

;;plot data
!p.multi=[0,1,1]
plot, doyfrs, ave_q, xtitle='Day of Year',ytitle='Average Charge', $
      title='Average Charge of O'
tagplot, /dir

;;end
ficlose
!p.multi=0
end
