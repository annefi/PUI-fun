; Filename: axlv2.pro
;
; Description:
;   Plot ACE/SWICS Level II (ver. 2) data from axlv2_yyyyddd.dat files.
;   NOTE:  Right now, this only plots O7+/O6+ ratio very rudimentarily.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   06Nov2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
pro axlv2, file=file, data=d

read_lv2, file=file, data=d

;; set up plot file
file_parse, file=file, base=base
psfile=base+'.ps'
psplt, file=psfile, /color

!p.multi=[0,1,2]

title='ACE/SWICS Level II Data (version 2, pre-release)'
;; plot
plot, d.time, d.v_he, $
  ytitle='He2+ velocity (km/s)', title=title
oplot, d.time, d.v_he , psym=4

;; plot
plot, d.time, d.o7_o6, xtitle='Day of 2003', $
  ytitle='O7+/O6+'
oplot, d.time, d.o7_o6 , psym=4

tagplot, line1=psfile, line2='University of Michigan'

ficlose

return
end
