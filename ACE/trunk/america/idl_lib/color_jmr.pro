; Filename: color_jmr.pro
;
; Description:
;   Set up 8 bit color table the way I like it and with useful
;   defaults.  This setup works very well with Dave Ortland's
;   COLOR_PLOT routine for contour plots.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   21Oct2002   jmr   adapted from parts of fmcomp.pro
;
pro, color_jmr, table=table, colors=c

if (n_elements(table) gt 0) then
  loadct, table
endif else begin
  loadct, 34
endelse

;; insert black and white
fix_ct_ends, black=0, white=1              

;; define colors that I like
c = { colors1,              $ ; name of structure
      black:    0,          $
      white:    1,          $
      purple:   2,          $
      blue:    40,          $
      green:  150,          $
      yellow: 230,          $
      orange: 240,          $
      red:    255,          $
    }      

return
end
