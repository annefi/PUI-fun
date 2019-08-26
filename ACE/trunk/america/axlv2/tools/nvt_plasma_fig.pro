;pro axlv2_plasma, hedata=dhe, tag=tag, eps=eps
;; build plasma parameter figure

thisprog = 'axlv2_plasma'

;; ==========> frequently changed configuration variables <====================
title='Plasma Parameters from ACE/SWICS and ACE/MAG'

;; number of plots per page
npp = 5

;; empty, h, v, z, order
!p.multi = [0, 1, npp, 1, 0]

;; start doy (in 2003), must be consistent with !x.range
START_DOY = 009

;; number of doys to process, must be consistent with !x.range
N_DOYS = 2

;; year of data (will not handle multiple years as written)
YEAR = 2005

;; name of nvt He data file
HFILE = './axlv2_nvt_2005009.dat'

;; base of MAG files
MAGBASE = 'ACE_MAG16_2005-'

;; directory for MAG files
MAG_DIR = '../mag'

;; version of MAG browse data
MAG_VER = '3-2'

;; toggle plotting of mag. data (0=> plot, 1=>no plot)
;; (turn off for tweaking plot formatting, it is slow to render)
NO_MAG_DATA=0

;; times of shocks, from Chuck Smith (Charles.Smith@unh.edu)
shock_times = [301.061944,302.248611,303.679861,308.249305,310.804861]

;; times of abrupt transitions in composition and assoc. colors
trans_times = [302.333333,303.666667,304.083333,306.75]
trans_colors = [40,40,40,40,40,40]

;; allowable error fraction in counts
ERROR_LEVEL = .2

;; ----- plot formatting -----
;; overall plot
;!p.charsize = 3.0
;!p.charthick = 3.0
;!p.thick = 5.0

;;; X axis
;!x.style = 1
;!x.thick = 3.0
;!x.ticklen = 0.04
;;; X axis label info for bottom plot only
;!x.title='Day of Year '+year_str
;!x.tickname=['']                ; automatic
;!x.ticks=0                      ; automatic
;!x.tickformat = 'doy2date_tick'
;!x.minor = 2
;!x.style = 9
;switch_x_labels, /save

;;; Y axis
;!y.style = 1
;!y.thick = 3.0
;!y.ticks = 3
;!y.tickname = [' ', strarr(!y.ticks) + '']
;; ============================================================================

;; set up plot file and plot parameters
if (keyword_set(tag)) then begin
  tagsep='_' 
endif else begin
  tagsep=''
  tag = ''
endelse
if (not keyword_set(eps)) then begin
  ext = '.ps'
  eps = 0
endif else ext = '.eps'
psfile = 'swics_plasma' + tagsep + tag + ext
psplt, file=psfile, /color
device, /portrait, encapsulated=eps
Positions = plot_positions(lmargin=0.07,rmargin=0.07,$
                           tmargin=0.07,bmargin=0.07,nplots=npp)

;; extract elements from filename
file_parse, file=file, split_base=sb
tmp = split_ydoy(sb[2], /strings)
year_str = tmp[0]

;; set global formatting attributes
!p.charsize = 3.0
!p.charthick = 3.0
!p.thick = 5.0

!x.style = 1
!x.thick = 3.0
;!x.ticks = 7
;!x.tickname = [' ', strarr(!x.ticks) + '']

!y.style = 1
!y.thick = 3.0
!y.ticks = 3
!y.tickname = [' ', strarr(!y.ticks) + '']


;; X axis label info for all but bottom plot
xtickname=[' ',' ']
xticks=1

nplot = npp
;; ----------------------------------------------------------------------
;; Read in MAG data
;; ----------------------------------------------------------------------
restore, file=MAG_DIR+'/ace_mag_browse_template.save'

doys = indgen(N_DOYS) + START_DOY
ndoys = n_elements(doys)        ; same as N_DOYS
for i=0,ndoys-1 do begin
  doy = string(format='(I3.3)',doys[i])
  file = MAG_DIR + '/' + MAGBASE +doy+'_V'+MAG_VER+'.DAT'
  d = read_ascii(file, template=template)
  if (i eq 0) then begin
    bdoyfr = d.scclock_start
    bmag  = d.bmag
    bz    = d.rtn_bn
  endif else begin
    bdoyfr = [bdoyfr,d.scclock_start]
    bmag  = [bmag,d.bmag]
    bz    = [bz,d.rtn_bn]
  endelse
endfor

;; crudely convert S/C clock to doyfr
start_scclock = bdoyfr[0]
bdoyfr = !x.range[0]*bdoyfr/start_scclock

;; ----------------------------------------------------------------------
;; Read in axlv2 data
;; ----------------------------------------------------------------------
restore, file='axlv2_nvt_template.save'
dnvt = read_ascii(HFILE, template=template)
filter_nvt_by_qual, nvtdata=dnvt, error_level=ERROR_LEVEL
i_he = where(dnvt.ion eq 'He2+', nwhere)
if (nwhere le 0) then begin
  print, thisprog+' -F- no He2+ data in file'
  goto, get_out
endif

dnvt.n = dnvt.n*439./2.
;; ----------------------------------------------------------------------
;; Top section -- He2+ data
;; ----------------------------------------------------------------------

plot,dnvt.doyfr[i_he], dnvt.v[i_he], title=title, ytitle='v', min=0.,$
  xtickname=xtickname,xticks=xticks,position=positions[--nplot,*],$
  yticks=3, ytickname=[' ','','',''];,yrange=[400.0,2000.0],$
  ;ytickv=[500.,1000.,1500.,2000.]

plot,dnvt.doyfr[i_he], dnvt.vth[i_he], ytitle='v!Dth!N', min=0.,$
  xtickname=xtickname,xticks=xticks,position=positions[--nplot,*],$
  yticks=2, ytickname=['','','',''];,ytickv=[150.,300.,450.]

plot,dnvt.doyfr[i_he], dnvt.n[i_he], ytitle='n', /ylog, min=0.,$
  xtickname=xtickname,xticks=xticks,position=positions[--nplot,*],$
  yticks=2, ytickname=[' ','','',''], $
  ytickformat=['','(F4.1)','(F4.1)','(F4.1)']          ;,ytickv=[0,.3,.6,.9]

;; ----------------------------------------------------------------------
;; Lower section -- magnetic field data
;; ----------------------------------------------------------------------
plot,bdoyfr, bmag, ytitle='|B|',/ylog, nodata=NO_MAG_DATA,$
  xtickname=xtickname,xticks=xticks,position=positions[--nplot,*],$
  ytickformat='(F3.1)',$
  yticks=2, ytickname=[' ','','',''];,ytickv=[.6,1.2,1.8],$
  ;yrange=[0.0,55.0]

;; set up x axis stuff for last plot by hand
xticks = fix(!x.range[1]) - fix(!x.range[0])
;; -- beware: must be a float array or doy2date_tick will be off by 1!
xtickv = findgen(fix(!x.range[1]) - fix(!x.range[0]) + 1) + fix(!x.range[0])
xtickname = make_array(xticks+1, /string, value=' ')
;!x.style = 9
toggle = 0
for itick=0,xticks do begin
  if (toggle eq 1) then begin
    xtickname[itick] = doy2date_tick(0,0,xtickv[itick],0)
    toggle = 0
  endif else begin
    xtickname[itick] = ' '
    toggle = 1
  endelse
  print, ' itick=',itick,' xtickv=',xtickv[itick],' xtickname=',xtickname[itick]
endfor

nplot = nplot - 1
plot,bdoyfr, bz, ytitle='B!Dz!N',  nodata=NO_MAG_DATA,$
  xtickname=xtickname,xticks=xticks,xtickformat='doy2date_tick',$
  xtickv=xtickv, xstyle=9,$
  position=positions[nplot,*],$
  xtitle='Day of Year '+year_str,yticks=2, $
  ytickformat='(F5.1)', $
  ytickv=[-20.0,0,20.0],yrange=[-40.0,40.0]

;; tag for credit
;xyouts, .945, .07, 'The ACE/SWICS Team',$
;  charsize=0.8,/normal, charthick=1.5, alignment=0.0, orientation=90.0

;; draw line at shocks
i_x_in_range = where(shock_times ge !x.range[0] and $
                                shock_times le !x.range[1], nwhere)
if (nwhere gt 0) then begin
  shock_times = shock_times[i_x_in_range]
  for ishock=0,n_elements(shock_times)-1 do begin
    shockx = convert_coord([shock_times[ishock],0.0] , /to_normal)
    plots,[shockx[0],shockx[0]],$
          ;; upper-most y value, lower-most y value
          [Positions[npp-1,3],Positions[0,1]],$
          /normal, color=255
  endfor
endif

;; draw line at transitions
for itrans=0,n_elements(trans_times)-1 do begin
;for itrans=0,0 do begin
  transx = convert_coord([trans_times[itrans],0.0] , /to_normal)
  plots,[transx[0],transx[0]],$
    ;; upper-most y value, lower-most y value
    [Positions[npp-1,3],Positions[0,1]],$
    /normal, color=trans_colors[itrans], linestyle=1
endfor


;xyouts, .995*Positions[0,2], Positions[0,1]-.025,$
;  '36 min averages', /normal, charsize=1.0, alignment=1.0

tagplot, line2='University of Michigan'

ficlose

file_parse, file=psfile, base=base
spawn, 'ps2pdf '+psfile+' '+base+'.pdf'

get_out:
end

