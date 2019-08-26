; Filename: axlv2_nvt.pro
;
; Description:
;   Plot ACE/SWICS level 2 density, velocity and thermal velocity data.
;
; Author: Jim Raines (jmr)
;
; Method:
;   
; Revision controlled with CVS:
; $Id: axlv2_nvt.pro,v 1.7 2005/03/14 15:31:09 jraines Exp $
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
; [I] ions        array of ions to plot, e.g. ions=['He2+','Fe9+']
; [I] tag         string with which to tag output filename and plots
;                 (only alphanumeric and '_' work well)
; [I] swepam      name of swepam data file (year, doyfr, nh, he/h, vh)
;                 to overplot
; [I] noread      do not read data, must have supplied data and
;                 second_data keywords (if applicable)
; [I] dswepam     name of variable in which to store swepam data
;                 structure, required for /noread
; [I] second_file optionally specify a second NVT file to overplot for
;                 comparison
; [I] second_data data structure for second_file
; [I] draw_points optionally request points be overplotted on primary
;                 data series
pro axlv2_nvt, file=file, data=d, ions=ions, noread=noread, $
               tag=tag, swepam=swepam, dswepam=dswepam, $
               second_file=second_file, second_data=d2, draw_points=draw_points

;; init variables
thisprog = 'axlv2_nvt'

;; save old !p structure to put it back at the end
orig_p = !p

;; extract elements from filename
file_parse, file=file, split_base=sb
tmp = split_ydoy(sb[2], /strings)
year_str = tmp[0]
                                                                               
;; ----------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------
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
  d = read_ascii(file, template=template)

  if (keyword_set(second_file)) then d2 = read_ascii(second_file, template=template)

  if (keyword_set(swepam)) then begin
    restore, file='swepam_he_template.save'
    dswepam = read_ascii(swepam, template=template)

    ;; get rid of lines with fill values
    ibad = where(dswepam.nh lt 0. or dswepam.he_h lt 0. or dswepam.vh lt 0.,$
                nwhere)
    if (nwhere gt 0.) then begin
      dswepam.he_h[ibad] = 0.
      dswepam.nh[ibad] = 0.
      dswepam.vh[ibad] = 0.
    endif
  endif

endif

;; set defaults
if (not keyword_set(ions)) then begin
  ions=['He2+','He2+','O6+','O7+','Fe9+','Fe11+','Si7+']
endif
tagsep='_'
if (not keyword_set(tag)) then begin 
  tag=''
  tagsep=''
endif

;; set up plot file
file_parse, file=file, base=base
psfile=base+tagsep+tag+'.ps'
psplt, file=psfile, /color
loadct, 34
fix_ct_ends, black=0, white=255

;; figure out plot positions
PlotsPerPage = n_elements(ions)
!p.multi = [0,1,PlotsPerPage]
Positions = plot_positions(lmargin=0.1,rmargin=0.1,tmargin=0.1,bmargin=0.1,$
                       nplots=PlotsPerPage)

;; plot text that does not change
title='ACE/SWICS Level II Densities (version 2, pre-release)'

yticks = 0

nion = 0
for nplot=0,PlotsPerPage-1 do begin

  ion = ions[nion]

  ;; select ion
  i_ion = where(d.ion eq ion, ni_ion)
  if (ni_ion le 0) then begin
    print, thisprog+' -F- no data for '+ion+' found.  Skipping...'
    goto, next_ion
  endif

  ;; select ion in second file if specified
  if (keyword_set(second_file)) then begin
    i2_ion = where(d.ion eq ion, ni_ion)
    if (ni_ion le 0) then begin
      print, thisprog+' -F- no data for '+ion+' found.  Skipping...'
      goto, next_ion
    endif
  endif


  ;; things to plot on first (bottom) plot only
  if (nplot eq 0) then begin
    orig_title = title
    title = ''

    y = d.v[i_ion]
    ytitle=ion+' speed (km/s)'
    ylog = 0
    if (keyword_set(second_file)) then y2 = d2.v[i2_ion]

    switch_x_labels, /on
  endif else begin  ;; rest of the plots
    y = d.n[i_ion]
    ytitle=ion ;+' density (cm^-3))'
    ylog = 1
    if (keyword_set(second_file)) then y2 = d2.n[i2_ion]

    switch_x_labels, /off
  endelse

  ;; top plot only
  if (nplot eq PlotsPerPage-1) then title = orig_title

  ;; things common to all plots
  x = d.doyfr[i_ion]
  if (keyword_set(second_file)) then x2 = d2.doyfr[i2_ion]

  ;yticks = 4
  ytickname = make_array(yticks+1, value='', /string)
  ytickname[n_elements(ytickname)-1] = ' '


  plot, x, y, $
    title=title,$
    ytitle=ytitle,$
    yticks=yticks,$
    ytickname=ytickname,$
    ylog=ylog, $
    position=positions[nplot,*], $
    min = 0.0

  if (keyword_set(second_file)) then oplot, x2, y2, color=254

  if (keyword_set(draw_points)) then oplot,  x, y, psym=4

  if (keyword_set(swepam) and ion eq 'He2+') then begin
    if (nplot eq 0) then begin
      oplot, dswepam.doyfr, dswepam.vh, color=254,$
             nsum=100
    endif else begin
      oplot, dswepam.doyfr, dswepam.he_h*dswepam.nh, color=254,$
             nsum=100
    endelse
  endif

  next_ion:
  nion = nion + 1
endfor

;; put identifier on plot
tagplot, line1='University of Michigan', /dir

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
!p = orig_p
return
end

