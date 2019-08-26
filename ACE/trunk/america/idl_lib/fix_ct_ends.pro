; Filename: fix_ct_ends.pro
;
; Description:
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
; $Id: fix_ct_ends.pro,v 1.3 2003/11/21 17:08:51 jraines Exp $
;
; Major Modification History
;   25Apr2002   jmr   initial coding
;   
;
pro fix_ct_ends, black=black, white=white

  ;; IDL stores color tables in these arrays
  common colors, R_orig, G_orig, B_orig, R_curr, G_curr, B_curr

  ;; useful defaults
  if (not keyword_set(black)) then black = 0
  if (not keyword_set(white)) then white = 1

  ;; set black entry
  r_curr[black] = 0
  g_curr[black] = 0
  b_curr[black] = 0

  ;; set white entry  
  r_curr[white] = 255
  g_curr[white] = 255
  b_curr[white] = 255

  tvlct, r_curr, g_curr, b_curr

return
end
