; Filename: savect.pro
;
; Description:
;   Saves current color table 
;   Sets black and white color table entries in an 8 bit (256 element)
;   color table.  If not specified in arguments, black is the first
;   entry and white is the second.  This configuration works well for
;   Dave Ortland's COLOR_PLOT routine.
;
; Author: Jim Raines (jmr)
;
; Method:
;   (R,G,B) for black is (0,0,0)
;   (R,G,B) for white is (255,255,255)
;   
; Arguments:
;   black -- location in color table in which to put black
;   white -- location in color table in which to put white
;
; Revision controlled by CVS:
; $Id: savect.pro,v 1.1 2004/03/29 20:01:05 jraines Exp $
;
; Sample usage:
;  Load color table, modify it then save it:
;  IDL> loadct, 33
;  IDL> xloadct  ;; modify color table here
;  IDL> savect, 41, 'MMQ', '~/idl/shrg_colors.tbl'
;
;  Entries 1-40 are the standard IDL pre-defined color tables.
;
; Major Modification History
;   25Mar2004   jmr   Adapted from fix_ct_ends
;   
;
pro savect, itab, name, file

  ;; IDL stores color tables in these arrays
  common colors, R_orig, G_orig, B_orig, R_curr, G_curr, B_curr

  modifyct, itab, name,  R_curr, G_curr, B_curr, file=file

return
end
