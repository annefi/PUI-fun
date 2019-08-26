; Filename: nvt_fig.pro
;
; Description: 
;   Compare ACE/SWICS level 2 density, velocity and thermal velocity.
;
; Author: Jim Raines (jmr)
;
; Method:
;   
; Revision controlled with CVS:
; $Id: nvt_fig.pro,v 1.1 2005/04/01 20:06:36 jraines Exp $
;
; Major Modification History
;   01Apr2005   jmr   Based on axlv2_n_fig.pro
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
; [I] noread      do not read data, must have supplied data and
;                 second_data keywords (if applicable)
; [I] draw_points optionally request points be overplotted on primary
;                 data series
; [I] error_level optionally set error acceptance level 
; [I] vth_level   optionally set error acceptance level for vth
; [I] yranges     optionally specify yranges for vth, v, and n (in
;                 that order)
pro nvt_fig, file=file, data=d, ions=ions, noread=noread, $
             tag=tag, draw_points=draw_points, colors=colors,$
             error_level=error_level, vth_level=vth_level,yranges=yranges

;; init variables
thisprog = 'nvt_fig'

;; save old !p structure to put it back at the end
orig_p = !p
orig_x = !x
orig_y = !y

;; extract elements from filename
file_parse, file=file, split_base=sb
ydoy_str = sb[2]
;; --- grab year
tmp = split_ydoy(sb[2], /strings)
year_str = tmp[0]
;; --- add second date if present (assumes same year)
if (n_elements(sb) eq 4) then ydoy_str = ydoy_str + '_' + sb[3]
                                                                               
;; ----------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------
DEFAULT_ERROR_LEVEL = 1.0
DEFAULT_YRANGES = [ [0.,0.], [0.,0.], [1.e-6,1]]

!p.title='ACE/SWICS Level II Plasma Parameters (version 2, pre-release)'
!p.font = 1  ; True-type fonts
font = 'Times'
!p.charsize = 2.8
!p.charthick = 6.0
!p.thick = 5.0
!p.font = 0

!x.tickformat='doyfr2hms_tick'
;; X axis
!x.style = 1
!x.thick = 5.0
!x.ticklen = 0.04
;; X axis label info for bottom plot only
!x.title='Day of Year '+year_str
!x.tickname=['']                ; automatic
!x.ticks=3                      ; automatic
switch_x_labels, /save          ; save these for bottom plot

!y.thick = !x.thick
!y.style = 1

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
if (not keyword_set(colors)) then begin
  colors = [0, 16, 50, 128,  192, 224, 254]
endif

if (not keyword_set(error_level)) then error_level = DEFAULT_ERROR_LEVEL

if (not keyword_set(yranges)) then yranges = DEFAULT_YRANGES
;; ----------------------------------------------------------------------
;; read data
;; ----------------------------------------------------------------------
if (not keyword_set(noread)) then begin
  tplatefile = 'axlv2_nvt_template.save'
  restore, file=tplatefile
  d = read_ascii(file, template=template)
endif
filter_nvt_by_qual, nvt=d, error_level=error_level
d.n = d.n*110.

;; ----------------------------------------------------------------------
;; set up plot file
;; ----------------------------------------------------------------------
file_parse, file=file, base=base
psfile=thisprog+'_'+ydoy_str+tagsep+tag+'.ps'
psplt, file=psfile, /color
loadct, 34
fix_ct_ends, black=0, white=255

;; figure out plot positions
PlotsPerPage = 3
!p.multi = [0,1,PlotsPerPage]
margin = .12
Positions = plot_positions(lmargin=margin,rmargin=margin,$
                           tmargin=margin,bmargin=margin,$
                           nplots=PlotsPerPage)

;; ----------------------------------------------------------------------
;; make nv, v, vth plots with specified ions overplotted
;; ----------------------------------------------------------------------
ytitles = ['v!Ith!N (km/s)', 'v (km/s)','n (cm!E-3!N)']
struc_indices = [4,3,2]
ylogs = [0,0,1]
ynozeros = [1,1,1]
mins = [1.0,1.0,0.]

for nplot=0,PlotsPerPage-1 do begin
  if (nplot eq 0) then switch_x_labels, /on else switch_x_labels, /off
  if (nplot eq PlotsPerPage-1) then title=!p.title else title=''

  for nion=0,n_elements(ions)-1 do begin ;; first ion is speed

    ion = ions[nion]
    color = colors[nion]

    ;; select ion
    i_ion = where(d.ion eq ion, ni_ion)
    if (ni_ion le 0) then begin
      print, thisprog+' -F- no data for '+ion+' found.  Skipping...'
      goto, next_ion
    endif

    ;; blank first y tick
    ytickname = make_array(!y.ticks+1, value='', /string)
    ytickname[n_elements(ytickname)-1] = ' '

    x = d.doyfr[i_ion]
    y = d.(struc_indices[nplot])[i_ion]
    if (nion eq 0) then begin
      plot, x, y, title=title,$
            yrange=[yranges[*,nplot]], $
            ytitle=ytitles[nplot],$
            ytickname=ytickname,$
            ylog=ylogs[nplot], ynozero=ynozeros[nplot], $
            position=Positions[nplot,*], $
            color=color, min=mins[nplot]
    endif else begin
      oplot, x, y, color=color, min=mins[nplot]
    endelse

    if (keyword_set(draw_points)) then oplot,  x, y, psym=4, color=color

    xyouts, positions[0,2]+.01, positions[PlotsPerPage-1,3]-(.05*(nion+1)),$
            ion, $
            color=color, /normal, size=1.5

    next_ion:
  endfor
endfor

;; put identifier on plot
tagplot, line1='University of Michigan', /dir

;; clean up and get out
ficlose
!p = orig_p
!x = orig_x
!y = orig_y
return
end

