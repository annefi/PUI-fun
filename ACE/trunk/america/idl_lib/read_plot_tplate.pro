; rp_tplate.pro -- read and plot tplate.pl data
; Jim Raines, 16Jan2002 (based on a long line of plot_*.pro files)
;
; Note: To use this template, replace 'tplate' with the name of the
; program that produced the data file.  
pro rp_tplate, datfile=datfile, data=d, mktp=mktp, noread=noread

; ===> parameters -- change these at will
tpfile = 'tplate_template.save'  ;name of template file for read_ascii

; ask for args if not present
if (keyword_set(noread)) then begin
  fRead = 0
endif else begin
  fRead = 1
endelse

if ((n_elements(datfile) le 0) and (fRead eq 1)) then begin
	datfile = ''
	read, 'Enter data file to plot: ', datfile
endif

; initialize


; read data
if fRead eq 1 then begin
  ;; template for read_ascii, made with ascii_template function
  if (keyword_set(mktp)) then begin
    ;;; make template file
    message, /info, 'making a new ascii template; plot may not work without code modification'
    template = ascii_template(datfile)
    save, filename=tpfile, template
  endif else begin
    ;;; restore template file
    restore, filename=tpfile
  endelse

  ;; read in file, which is a two column list of Nq and Nm  (mq and m classification)
  message, /info, 'reading data...'
  d = read_ascii(datfile, template=template)
endif

;---------
; do plot
;---------
message, /info, 'doing plot...'

; load color table (See IDL docs about color tables for a description)
;loadct, 0      ;;;loads ct but that doesn't do anything

; set up plot labels

xtitle = 'E/q'
ytitle = 'counts'
title = 'Test Plot'
subtitle = 'subtitle'

; ===> change what you are plotting!
plot, d.doy, xtitle=xtitle, ytitle=ytitle, title=title, $
  subtitle=subtitle, psym=3

exit:
end
