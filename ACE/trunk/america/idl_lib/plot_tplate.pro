; plot_tplate.pro -- plot tplate.pl data (after reading with
;                         read_tplate.pro)
; Jim Raines, 24Jan2001
;
; To use this template, replace 'tplate' with the name of the program
; that generated the data and config. items marked with '===>'

pro plot_tplate, data=d

; load color table (See IDL docs about color tables for a description)
;loadct, 0   

; read plot title out of first line of data file
; ----------------------------------------------
get_lun, lun
openr, lun, datfile
title = ''
datdate = ''
readf, lun, format='(a128)',title
readf, lun, format='(a128)',datdate

; clean up title strings
title = strmid(title,2)         ; chop off characters 0 and 1
title = strtrim(title)          ; chop off trailing blanks
datdate = strmid(datdate,2)
datdate = strtrim(datdate)

; tidy up file stuff
close, lun
free_lun, lun

; do plot
; -------

; set up plot labels

xtitle = 'X'
ytitle = 'Y'
title = 'Test Plot'
subtitle = 'subtitle'

; ===> set what you are plotting!
plot, d.(0), xtitle=xtitle, ytitle=ytitle, title=title, $
  subtitle=subtitle, psym=3

exit:
end
