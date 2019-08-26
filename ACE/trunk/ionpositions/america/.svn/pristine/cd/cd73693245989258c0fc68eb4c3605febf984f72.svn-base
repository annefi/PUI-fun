; Filename: axlv2_nvt.pro
;
; Description:
;   Plot ACE/SWICS level 2 density, velocity and thermal velocity data.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   05Nov2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
; I   ion         ion to plot
; I   [doyfrs]    draw vertical lines at these doy fractions
; I   [title]     title of plot
pro axlv2_nvt_vel, data=d, ion=ion, doyfr_lines=doyfr_lines,title=title,$
                   position=position, no_position=no_position

;; init variables
thisprog = 'axlv2_nvt_vel'

;; select ion
i_ion = where(d.ion eq ion, ni_ion)

if (ni_ion le 0) then begin
  print, thisprog+' -F- no data for '+ion+' found.  Exiting...'
  return
endif

doyfr = d.doyfr[i_ion]
v = d.v[i_ion]

;; plot
if (not keyword_set(title)) then $
  title='ACE/SWICS Level II Data (version 2, pre-release)'

ion_parse, ion=ion, iso=iso, elem=elem, state=state, /strings
;if (iso eq '-1') then iso = ''
;ion_name = iso+elem+'!E'+state+'+!N'
if (not keyword_set(no_position)) then begin
  plot, doyfr, v,  $
    ytitle='v!D'+elem+'!N (km/s)', title=title, subtitle=file , $
    position=position
endif else begin
  plot, doyfr, v,   $
    ytitle='v!D'+elem+'!N (km/s)', title=title, subtitle=file 
    
endelse
; xtickformat='(F6.2)'
;  
oplot,  doyfr, v, psym=4

if (keyword_set(doyfr_lines)) then begin
  ndoyfr_lines = n_elements(doyfr_lines)

  for idoyfr=0,ndoyfr_lines-1 do begin
    x = [doyfr_lines[idoyfr], doyfr_lines[idoyfr]]

    i_y = where(doyfr eq doyfr_lines[idoyfr], ni_y)
    if (ni_y le 0) then begin
      print, thisprog+' -E- no speed for '+ion+' at '+$
        string(format='(F6.2)',doyfr_lines[idoyfr])
      goto, next
    endif
    ymax_array = v[i_y]
    ymax = ymax_array[0]
    if (ymax le 0) then ymax = v[i_y-1] 
    y = [!y.range[0],ymax]

    plots, x, y, /data 

    next:
  endfor
endif

return
end

