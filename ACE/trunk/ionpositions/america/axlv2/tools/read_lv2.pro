; Filename: read_lv2.pro
;
; Description:
;   Read ACE/SWICS Level II (version 2+) data file produced by axlv2.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   09Sep2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        array of structures where each structure has all of
;                 the data items for that time point
; I   [bycol]     return structure of arrays (by column organization) instead
pro read_lv2, file=file, data=lv2, bycol=bycol

;; restore template
tplatefile = 'axlv2_lv2_template.save'
restore, file=tplatefile

;; read data organized in arrays by column
lv2_bycol = read_ascii(file, template=template, header=h)

if (keyword_set(bycol)) then begin
  lv2 = lv2_bycol
endif else begin
  ;; re-organize data into array of structures
  ;; -------------------------------------------------------
  ;; This organization, rather than the structure of arrays as read in
  ;; by read_ascii, makes misalignments (e.g. pairing ion with wrong
  ;; tof, esd, etc.) more much difficult

  ;; define by row structure
  lv2_element = $
    { axlv2,                    $ ; name of structure
      time: 0.0,                $ ; time in year day of year fraction
      v_h: 0.0,                 $ ; velocity of H+ in km/s
      vth_h: 0.0,               $ ; thermal velocity of H+ in km/s
      v_he: 0.0,                $ ; velocity of He2+ in km/s
      vth_he: 0.0,              $ ; thermal velocity of He2+ in km/s
      v_o6: 0.0,                $ ; velocity of He2+ in km/s
      vth_o6: 0.0,              $ ; thermal velocity of He2+ in km/s
      v_mg: 0.0,                $ ; velocity of Mg10+ in km/s
      vth_mg: 0.0,              $ ; thermal velocity of Mg10+ in km/s
      v_fe: 0.0,                $ ; velocity of Fe11+ in km/s
      vth_fe: 0.0,              $ ; thermal velocity of Fe11+ in km/s
      he_o: 0.0,                $ ; He/O ratio
      ne_o: 0.0,                $ ; Ne/O ratio
      mg_o: 0.0,                $ ; Mg/O ratio
      fe_o: 0.0,                $ ; Fe/O ratio
      ir_3he_4he: 0.0,          $ ; 3He/4He isotopic ratio
      ir_22ne_20ne: 0.0,        $ ; 22Ne/20Ne isotopic ratio
      ir_24mg_26mg: 0.0,        $ ; 24Mg/26Mg isotopic ratio
      c5_c6: 0.0,               $ ; C5+/C6+
      o7_o6: 0.0,               $ ; O7+/O6+
      fe11_fe9: 0.0             $ ; Fe11+/Fe9+
    }
     
  ;; build array of structures
  lv2 = replicate(lv2_element, n_elements(lv2_bycol.time))
 
  ;; fill structures in fmc array
  for i=0,n_elements(lv2_bycol.time)-1 do begin
    lv2[i].time = lv2_bycol.time[i] 
    lv2[i].v_h = lv2_bycol.v_h[i]
    lv2[i].vth_h = lv2_bycol.vth_h[i]
    lv2[i].v_he = lv2_bycol.v_he[i]
    lv2[i].vth_he = lv2_bycol.vth_he[i]
    lv2[i].v_o6 = lv2_bycol.v_o6[i]
    lv2[i].vth_o6 = lv2_bycol.vth_o6[i]
    lv2[i].v_mg = lv2_bycol.v_mg[i]
    lv2[i].vth_mg = lv2_bycol.vth_mg[i]
    lv2[i].v_fe = lv2_bycol.v_fe[i]
    lv2[i].vth_fe = lv2_bycol.vth_fe[i]
    lv2[i].he_o = lv2_bycol.he_o[i]
    lv2[i].ne_o = lv2_bycol.ne_o[i]
    lv2[i].mg_o = lv2_bycol.mg_o[i]
    lv2[i].fe_o = lv2_bycol.fe_o[i]
    lv2[i].ir_3he_4he = lv2_bycol.ir_3he_4he[i]
    lv2[i].ir_22ne_20ne = lv2_bycol.ir_22ne_20ne[i]
    lv2[i].ir_24mg_26mg = lv2_bycol.ir_24mg_26mg[i]
    lv2[i].c5_c6 = lv2_bycol.c5_c6[i]
    lv2[i].o7_o6 = lv2_bycol.o7_o6[i]
    lv2[i].fe11_fe9 = lv2_bycol.fe11_fe9[i]
  endfor
endelse

return
end
