; Filename: plotct.pro
;
; Description:
;   Plot color tables to facilitate easy determination of color/index pairs.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: plotct.pro,v 1.4 2004/11/11 15:11:21 jraines Exp $
;
; Major Modification History
;   ddmmmyyyy   jmr   initial coding
;
; Usage:
;   There is a main program at the end which plots all the built-in
;   IDL tables; simply '.run plotct.pro'.  Otherwise, this can be used
;   to plot individual color tables to an already open graphics device.
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   ct          array of color tables to plot
pro ct_plot, ct=ct

!p.multi = 0

if (not keyword_set(ct)) then ct = [33,34]

ca_size = sqrt(!d.table_size)
colors16 = indgen(ca_size)+1

colors = make_array(ca_size,ca_size, /int)
index = 0
for i=1,ca_size do begin
  for j=1,ca_size do begin
    colors(j-1,i-1) = index++
  endfor
endfor

for ict=0,n_elements(ct)-1 do begin
  loadct, ct[ict]
  ct_str = string(format='(I2)',ct[ict])
  fix_ct_ends, black=0,white=255
  color_plot, colors, colors16,colors16,xtitle='x',ytitle='y',$
    title = 'Color Table '+ct_str, $
    subtitle = '0/255 replaced with black/white for display'

  for i=1,ca_size do begin
    for j=1,ca_size do begin
      xyouts, i,j, string(format='(I3)',colors(i-1,j-1)), size=0.5, $
        alignment=.5, color = ca_size - 1 - colors(i-1,j-1), charthick=.7
    endfor
  endfor
  
  tagplot, line1='From plotct.pro', line2='University of Michigan',/notime

endfor

return
end

;; sample usage

psplt, file='plotct.ps', /color

cts = indgen(41)
;cts = [26]
ct_plot, ct=cts

ficlose

end
