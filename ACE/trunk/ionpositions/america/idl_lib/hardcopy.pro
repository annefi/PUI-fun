; hardcopy.pro -- produce hardcopy output of current graphics device
; Jim Raines, 22Sep99
;
; Usage: harcopy, /help		(gives usage statement)
; NOTE:  You must execute 'psplt' and your plotting routines first
;
; Uses HRDI idl_lib routines: ficlose (which uses psplt)
;
; Modification history
;   adapted for use on ionstream, J. Raines, 1Feb00
;
pro hardcopy, label=label, file=psfile, num_series_labels=nsl, $
	series_labels=sl, _extra=size, printer=printer, help=help

; usage statement
if (keyword_set(help)) then begin
  lmax = 10                      ; number of usage statement lines
  l = 0                         ; element number of usage array  
  usage = strarr(lmax,80)
  usage(0)='usage: hardcopy [, optional argument1, ...]'
  usage(1)='  NOTE: Use psplt, file=filename then your plot command first.'
  usage(2)='  optional arguments:  (remember single quotes around strings!)'
  usage(3)='  label=              text label for lower right hand corner of plot'
  usage(4)='  file=               filename of Postscript plot'
  usage(5)='  size=<0.0-1.0>      font size passed to xyout'
  usage(6)='  num_series_labels=  number of series labels in series_labels'
  usage(7)='  series_labels=      structure containing series labels'
  usage(8)='  printer=            name of printer, file causes no hardcopy'
  usage(9)='  /help               prints this usage message'

  for j=0,lmax do print, usage(j)
  return
endif

; handle args
if (n_elements(label) le 0) then begin
  label = ''
  read, 'Enter label for plot (32 char max): ', label
endif
if (n_elements(psfile) le 0) then begin
  psfile = ''
  read, 'Enter postscript filename: ', psfile
endif

if (n_elements(printer) le 0) then begin
  fPrint = 1                    ; no printing
  printer = 'swicsco'
endif else begin
  if (printer eq 'file') then begin
    fPrint = 0
  endif else begin
    fPrint = 1
  endelse
endelse

; write series label(s) to graphics device
if (n_elements(nsl) gt 0 and n_elements(sl) gt 0) then begin
  for i=0,nsl-1 do begin
    ;print, sl(i).x, sl(i).y, sl(i).label
    xyouts, sl(i).x, sl(i).y, sl(i).label, /data, _extra=size
  endfor
endif

; write label to graphics device
out = STRARR(4)
out(0) = 'Plot:  ' + label
out(1) = 'Created:  '+STRMID(!stime,0,11)
out(2) = 'By:  J. Raines'
out(3) = 'From file:  ' + psfile

for k = 0,3 do XYOUTS, 0.95, -0.015*k, out(k), /normal, size=0.5

;close device
ficlose

;actually print file
if (fPrint) then begin
  cmd='lpr -P ' + printer + ' ' + psfile
  spawn, cmd
  print, 'File printed with: ' + cmd
endif


EXIT:
return
end
