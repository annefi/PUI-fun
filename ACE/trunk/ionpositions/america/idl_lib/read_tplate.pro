; Filename: read_xl2.pro
;
; Description:
;   Read ACE/SWICS level 2 data (version 0.2) into a structure.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   ddMmmyyyy   jmr   adapted from read_tplate.pro
;   24Jan2001   jmr   adapted from long line of  plot_*.pro files
;
; Note: To use this template, replace 'tplate' with the name of the
; program that produced the data file.  Then delete this comment

pro read_tplate, file=datfile, data=d, mktp=mktp

; ===> parameters -- change these at will
; name of template file for read_ascii
tpfile = 'read_tplate_template.save' 

; ask for args if not present
if ( n_elements(datfile) le 0 ) then begin
	datfile = ''
	read, 'Enter data file to plot: ', datfile
endif


;; restore or create template (for read_ascii)
if (keyword_set(mktp)) then begin
  ;; make template file
  message, /info, 'making a new ascii template'
  template = ascii_template(datfile)
  save, filename=tpfile, template
endif else begin
  ;; restore template file
  restore, filename=tpfile
endelse

; read data
message, /info, 'reading data...'
d = read_ascii(datfile, template=template)

exit:
end
