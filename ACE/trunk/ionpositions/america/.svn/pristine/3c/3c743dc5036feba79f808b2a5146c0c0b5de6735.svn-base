pro axlv2_nvt_ratios, file=file, year=year, ratios=ratios,data=d, tag=tag

thisprog = 'axlv2_nvt_ratios'

;; ===========> frequently changed configuration variables <===================
def_ratios = [['O7+','O6+'],['C6+','C5+'],['Fe11+','Fe9+']]
;;============================================================================

if (not keyword_set(year)) then begin
  print, thisprog + ' -F- must specify year'
  goto, exit
endif

if (not keyword_set(ratios)) then ratios = def_ratios

;; ----------------------------------------------------------------------
;; read data
;; ----------------------------------------------------------------------
;; read data
tplatefile = 'axlv2_nvt_template.save'
restore, file=tplatefile
d = read_ascii(file, template=template, comment='#')

;; ----------------------------------------------------------------------
;; PS file setup and plot formating
;; ----------------------------------------------------------------------
nratios = n_elements(ratios[0,*])

;; set up plot file and plot parameters
if (keyword_set(tag)) then begin
  tagsep='_' 
endif else begin
  tagsep=''
  tag = ''
endelse
psfile = thisprog + tagsep + tag + '.ps'
psplt, file=psfile, /color
;; empty, h, v, z, order
!p.multi = [0, 1, nratios+1, 1, 1]
positions = plot_positions(lmargin=0.1,rmargin=0.1,$
                           tmargin=0.1,bmargin=0.1,nplots=nratios+1)

device;, /portrait
!p.charsize = 2.0
!p.charthick = 3.0
!p.thick = 5.0

!x.style = 1
!x.thick = 3.0
!x.ticks = 1
!x.tickname = [' ', strarr(!x.ticks) + ' ']
!xtitle = ''
;; cannot set here since it must be different for all but bottom plot
;;!x.tickformat = 'doy2date_tick'

!y.style = 1
!y.thick = 3.0
!y.ticks = 3
!y.tickname = [' ', strarr(!y.ticks) + '']

;; ----------------------------------------------------------------------
;; Top panel -- velocity
;; ----------------------------------------------------------------------

ion = 'He2+'
i_ion = where(d.ion eq ion, ni_ion)

if (ni_ion le 0) then begin
  print, thisprog+' -F- no data for '+ion+' found.  Exiting...'
  return
endif

nplot = nratios + 1
;title='Average Charge States'
title = 'Ion Ratios from pre-release ACE/SWICS Level II ver. 2'
nplot = nplot - 1
plot, d.doyfr[i_ion], d.v[i_ion], $
  ytitle='v!IHe!N (km/s)', title=title, position=positions[nplot,*],$
  xtickname=[' ',' '],xticks=1, yticks=3, ytickname=[' ','','',''],$
  xtickformat=''
oplot,  d.doyfr[i_ion], d.v[i_ion], psym=4

;; ----------------------------------------------------------------------
;; Subsequent panels -- ratios
;; ----------------------------------------------------------------------
for iratio=0,nratios-1 do begin

  ion_num =  ratios[0,iratio]
  i_num = where(d.ion eq ion_num, nwhere)

  if (nwhere le 0) then begin
    print, thisprog+' -F- no data for '+ion_num+' found.  Skipping...'
    goto, next
  endif

  ion_den = ratios[1,iratio]
  i_den = where(d.ion eq ion_den, nwhere)

  if (nwhere le 0) then begin
    print, thisprog+' -F- no data for '+ion_den+' found.  Skipping...'
    goto, next
  endif

  if (iratio eq nratios-1) then begin ; last plot
    !x.ticks = 5
    !x.tickname = ['', strarr(!x.ticks) + '']
    !x.title = 'Day of ' + string(format='(I4)',year)
  endif

  nplot = nplot - 1
  plot, d.doyfr[i_num], d.n[i_num]/d.n[i_den], $
    position=positions[nplot,*],/ylog,$
    ytitle=ion_num+'/'+ion_den, yminor=10;, ytickv=[.01,.1,1,10]
  next:
endfor
;; ----------------------------------------------------------------------
;; Clean up and get out
;; ----------------------------------------------------------------------
tagplot, line1=tag, line2='University of Michigan', $
  line3='Raines/Lepri'
ficlose

exit:
return
end
