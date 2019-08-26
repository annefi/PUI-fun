; label_series -- label particular series, selecting location with mouse
; Jim Raines, 23Sep99

pro label_series, nlabels, sl, _extra=size, use_existing=use_existing,help=help

; ===> parameters
MAXLABELS = 10		; maximum number of labels, arbitrary limit

; usage statement
if (keyword_set(help)) then begin
  usage = strarr(7,128)
  usage(0)='usage: label_series [, optional argument1, ...]'
  usage(1)='  optional arguments:  (order important for non-keyword args)'
  usage(2)='  integer          # of labels'
  usage(3)='  name             structure of labels for output (for hardcopy) '
  usage(4)='  size=<0.0-1.0>   font size passed to xyout'
  usage(5)='  /use_existing    prints labels on plot using existing structure'
  usage(6)='  /help            prints this usage message'

  for j=0,6 do print, usage(j)
  return
endif

on_error, 1

; parse args
if (n_elements(nlabels) le 0) then begin
  nlabels = 1
endif

if (keyword_set(use_existing)) then begin

  for i=0,nlabels-1 do begin
    xyouts, sl(i).x, sl(i).y, sl(i).label, /data, _extra=size
  endfor

endif else begin

  ; init. variables
  label = ''
  sl = replicate( $
	{ series_labels, $	; name of structure
	x: 0.0, $			; x value
	y: 0.0, $			; y value
	label: ''}, $		; label
	MAXLABELS)		; number of structures in array

  ; get locations, labels and write on plot
  for i=0,nlabels-1 do begin
    print, "Click on plot at location of label..."
    cursor,x,y, /data
    sl(i).x = x
    sl(i).y = y
    read, "Enter label text: ",label
    sl(i).label = label
    xyouts, sl(i).x, sl(i).y, sl(i).label, /data, _extra=size
  endfor
endelse

return
end
