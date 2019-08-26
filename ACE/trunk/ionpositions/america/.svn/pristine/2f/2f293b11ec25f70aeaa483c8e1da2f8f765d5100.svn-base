pro heavy_vel, file=file, data=d, tag=tag, ions=ions
;; build elemental abundance figure

thisprog = 'heavy_vel'

;; ==========> frequently changed configuration variables <====================
;; default ions
default_ions=['He2+','Fe9+','Fe9+','O6+','C5+']
;ions=['He2+']
;; colors (same order as ions), color table dependent
colors=[0, 2,  32, 224, 255, 145, 208]

;; nvt data with cnt_error higher than this fraction discarded
;; note:  this is not the error in NVT values, though related
ERROR_LEVEL = .2

;; ============================================================================

;; add related functions to path
path = !path + ":~/ace/Oct-Nov2003-CMEs"

;; read data
tplatefile = 'axlv2_nvt_template.save'
restore, file=tplatefile
d = read_ascii(file, template=template, comment='#')
filter_nvt_by_qual, nvtdata=d, error_level=ERROR_LEVEL

;; change -1.0 (fill) to 0.0 for this calculation
i_zero = where(d.n lt 0., nwhere)
if (nwhere gt 0) then d.n[i_zero] = 0.


;; set up plot file and plot parameters
if (keyword_set(tag)) then begin
  tagsep='_' 
endif else begin
  tagsep=''
  tag = ''
endelse
psfile = thisprog + tagsep + tag + '.ps'
psplt, file=psfile, /color
!p.multi = [0,1,2]

;; set default ions if not specified
if (not keyword_set(ions)) then ions=default_ions

doyfrs = d.doyfr(uniq(d.doyfr))
ndoyfrs = n_elements(doyfrs)
;; ----------------------------------------------------------------------
;; Do plots
;; ----------------------------------------------------------------------
title='ACE/SWICS Heavy Ion Velocities'
nions = n_elements(ions)

loadct, 34
fix_ct_ends

y = [[d.v],[d.vth]]
ytitle = ['v (km/s)','vth (km/s)']
for iy=0,1 do begin
  ix = 0
  for nion=0,nions-1 do begin
    ion = ions[nion]

    ;; select ion
    i_ion = where(d.ion eq ion, ni_ion)

    if (ni_ion le 0) then begin
      print, thisprog+' -F- no data for '+ion+' found.  Exiting...'
      return
    endif

    if (nion eq 0) then begin
      plot,doyfrs, y[i_ion,iy], title=title, ytitle=ytitle[iy],  $
;        xtickformat='dhms_tick',color=colors[nion]
        xtickformat='(F6.2)',color=colors[nion]
    endif else begin
      oplot,doyfrs,  y[i_ion,iy],color=colors[nion]
    endelse

    if (iy eq 0) then begin
      xspacing = 0.1
      xoffset = .1
      legend = [(xspacing*float(ix))+xoffset,0.01] ; positioning
;  legend = [(.1*nion)+.1,0.01] ; positioning
      if (nion eq 0) then begin
        ion='Legend: '+ion
        ix = ix + 1             ; add one more for extra spacing
      endif
    
      xyouts,legend[0],legend[1],ion, color=colors[nion], /normal

      ix = ix + 1               ; add one to set up next plot
    endif

    next:
  endfor
endfor

tagplot, line1=tag, line2='University of Michigan'

ficlose

return
end

