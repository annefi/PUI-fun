; Filename: axlv2_nvt_comp.pro
;
; Description:
;   Plot data from two ACE/SWICS level 2 nvt files for comparison.
;
; Author: Jim Raines (jmr)
;
; Method:
;
; ** This version is not the same as the CVS registered one! **
;   
; Major Modification History
;   10Dec2004   jmr   Adapted from axlv2_nvt.pro
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file1       data file 1, e.g. 
;                   file1='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; I   file2       data file 2, e.g. 
;                   file2='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data1       data structure, e.g., data=d001
; O   data1       data structure, e.g., data=d001
; [I] ions        array of ions to plot, e.g. ions=['He2+','Fe9+']
; [I] tag         string with which to tag output filename and plots
;                 (only alphanumeric and '_' work well)
; [I] noread      do not read data

pro axlv2_nvt_comp, file1=file1, file2=file2, data1=d1, data2=d2, $
               ions=ions, noread=noread, $
               tag=tag

;; init variables
thisprog = 'axlv2_nvt_comp'

;; ----------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------
psfile = 'axlv2_nvt_comp.ps'

!p.font = 1  ; True-type fonts
font = 'Times'
!p.charsize = 1.2
!p.charthick = 1.0
!p.thick = 2.0
!p.font = 0

!x.tickformat='doyfr2hms_tick'
;; X axis
!x.style = 1
!x.thick = 3.0
!x.ticklen = 0.04
;; X axis label info for bottom plot only
!x.title='Day of Year '+year_str
!x.tickname=['']                ; automatic
!x.ticks=0                      ; automatic
switch_x_labels, /save          ; save these for bottom plot

;; ----------------------------------------------------------------------
;; read data
;; ----------------------------------------------------------------------
if (not keyword_set(noread)) then begin
  tplatefile = 'axlv2_nvt_template.save'
  restore, file=tplatefile
  d1 = read_ascii(file1, template=template)
  d2 = read_ascii(file2, template=template)
endif

;; ----------------------------------------------------------------------
;; set defaults
;; ----------------------------------------------------------------------
if (not keyword_set(ions)) then begin
  ions=['He2+','He2+','O6+','O7+','Fe9+','Fe11+','Si7+']
endif

tagsep='_'
if (not keyword_set(tag)) then begin
  tag=''
  tagsep=''
endif

;; ----------------------------------------------------------------------
;; set up ancillary data
;; ----------------------------------------------------------------------
;; parse filename
file_parse, file=file1, base=base, split_base=sb

;; extract elements from filename
tmp = split_ydoy(sb[2], /strings)
year_str = tmp[0]

;; set up plot file
;psfile=base+'_'+tag+'.ps'
psplt, file=psfile, /color
loadct, 34
fix_ct_ends, black=0, white=255

;; figure out plot positions
PlotsPerPage = 2*n_elements(ions)
!p.multi = [0,1,PlotsPerPage]
Positions = plot_positions(lmargin=0.1,rmargin=0.1,tmargin=0.1,bmargin=0.1,$
                       nplots=PlotsPerPage)

;; plot text that does not change
title='ACE/SWICS Level II Data (version 2, pre-release)'

xtitle='Day of '+year

yticks = 0

;; ----------------------------------------------------------------------
;; loop over plots
;; ----------------------------------------------------------------------
nion = 0
nplot = 0
while (nplot le PlotsPerPage-1) do begin

  ;; select ion
  ion = ions[nion]
  i_ion1 = where(d1.ion eq ion, ni_ion)
  if (ni_ion le 0) then begin
    print, thisprog+' -F- no data for '+ion+' found in '+file2+'.  Exiting...'
    return
  endif
  i_ion2 = where(d2.ion eq ion, ni_ion)
  if (ni_ion le 0) then begin
    print, thisprog+' -F- no data for '+ion+' found in '+file2+'.  Exiting...'
    return
  endif


  ;; things to plot on first (bottom) plot only
  if (nplot eq 0) then begin
    orig_title = title
    title = ''

    y1 = d1.v[i_ion1]
    y2 = d2.v[i_ion2]
    ytitle=ion+' speed (km/s))'
    ytitle2='v ratio'
    ylog = 0

    switch_x_labels, /on
  endif else begin  ;; rest of the plots

    xtitle=''
    ;xticks = 1
    xticks = 1
    xtickname=[' ',' ']

    y1 = d1.n[i_ion1]
    y2 = d2.n[i_ion2]
    ytitle=ion ;+' density (cm^-3))'
    ytitle2='n ratio'
    ylog = 1

    switch_x_labels, /off
  endelse

  ;; things to plot on last (top) plot only
  if (nplot eq 0) then begin
  endif
  if (nplot eq PlotsPerPage-1) then begin
    title = orig_title
  endif

  ;; things common to all plots
  x1 = d1.doyfr[i_ion1]
  x2 = d1.doyfr[i_ion2]

  ;yticks = 4
  ytickname = make_array(yticks+1, value='', /string)
  ytickname[n_elements(ytickname)-1] = ' '


  plot, x1, y1, $
    title=title,$
    ytitle=ytitle,$
    xtitle=xtitle,$
    yticks=yticks,$
    ytickname=ytickname,$
    ylog=ylog,$
    position=positions[nplot++,*], $
    min = 0.0

  oplot,  x1, y1, psym=4

  oplot, x2, y2, color=254

  plot, x1, y1/y2, $
    title=title,$
    ytitle=ytitle2,$
    xtitle=xtitle,$
    xticks=xticks,$              ; ticks, 0 for default, n-1 ticks for >0
    xtickformat='doyfr2hms_tick',$
    yticks=yticks,$
    ytickname=ytickname,$
    ylog=ylog,$
    position=positions[nplot++,*], $
    min = 0.0,$
    charsize=charsize,$
    charthick=charthick,$
    font = font, $
    thick = thick

  nion = nion + 1
endwhile

;; put identifier on plot
tagplot, line1=psfile, line2='University of Michigan'

;; plot swepam stuff alone for comparision
if (keyword_set(swepam)) then begin
  !p.multi = [0,1,2]

  plot, dswepam.doyfr, dswepam.he_h * dswepam.nh, xtitle='DOY', $
        ytitle='He2+ density (cm^-3)!c(from nh * 4He/H)',$
        title='SWEPAM Data for Comparison', $
        nsum=100

  plot, dswepam.doyfr, dswepam.vh, xtitle='DOY', $
        ytitle='He2+ velocity (km/s)', $
        nsum=100, subtitle=swepam + ', 100 pt aves'
endif
;; clean up and get out
ficlose
!p.multi = 0
return
end

