; Filename: nvt_ave_q_fig.pro
;
; Description:
;   Make average charge comparison plot from ACE/SWICS level II nvt data.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: nvt_ave_q_fig.pro,v 1.2 2005/03/23 21:26:17 jraines Exp $
;
; Major Modification History
;   14Mar2005   jmr   Merged into tools from publication routine
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
; [I] slfe        overplot Sue Lepri's Fe data (may be obsolete or not
;                 general)
pro nvt_ave_q_fig, file=file, data=d, tag=tag, slfe=slfe

thisprog = 'nvt_ave_q_fig'

;; ===========> frequently changed configuration variables <===================
;; description of accumulation time
ACCUM_TIME_STR = '2 hour averages'

ELEMENTS = ['C','O','Fe']
;yranges  = [[3.,6.1],[3.,9.1],[5.,20.]] ; div. 3 makes integer
yranges = [[0.,0.],[0.,0.],[0.,0.]]

;; error level to accept 
ERROR_LEVEL = .5

;; minimum y value to plot, used to get rid of zeros
MIN_VALUE = .1

;; yrange for velocity plot
v_yrange = [400.,500.]

;; title for whole plot
TITLE='ACE/SWICS Level II data (prelim) -- Average Charge States'

;; times of shocks, from Chuck Smith (Charles.Smith@unh.edu)
;301.063356
;shock_times = [301.063356,302.248910,303.679648,308.249641,310.805563]
shock_times = [301.061944,302.248611,303.679861,308.249305,310.804861]
;; times of abrupt transitions in composition
;trans_times = [300.9,302.51,304.08,306.95]
;trans_colors = [40,40,40,40]
trans_times = [301.104167,301.354167,302.333333,303.666667,$
              304.083333,306.75]
trans_colors = [40,40,40,40,40,40]
;;============================================================================

;; ----------------------------------------------------------------------
;; read data
;; ----------------------------------------------------------------------
nelements = n_elements(ELEMENTS)

;; read data
tplatefile = 'axlv2_nvt_template.save'
restore, file=tplatefile
d = read_ascii(file, template=template, comment='#')
filter_nvt_by_qual, nvtdata=d, error_level=ERROR_LEVEL

;; change -1.0 (fill) to 0.0 for this calculation
i_zero = where(d.n lt 0., nwhere)
if (nwhere gt 0) then d.n[i_zero] = 0.

;; ----------------------------------------------------------------------
;; PS file setup and plot formating
;; ----------------------------------------------------------------------
;; extract elements from filename
file_parse, file=file, split_base=sb
tmp = split_ydoy(sb[2], /strings)
year_str = tmp[0]

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
!p.multi = [0, 1, nelements+1, 1, 1]
positions = plot_positions(lmargin=0.07,rmargin=0.07,$
                           tmargin=0.07,bmargin=0.07,nplots=nelements+1)

device, /landscape;/portrait
!p.charsize = 3.0
!p.charthick = 3.0
!p.thick = 5.0

!x.style = 1
!x.thick = 3.0
;!x.ticks = 1
;!x.tickname = [' ', strarr(!x.ticks) + '']
!x.title='Day of Year '+year_str
!x.tickname=['']              ; automatic
!x.ticks=0                    ; automatic
!x.tickformat = '(F6.2)'
!x.minor = 2
!x.style = 9
switch_x_labels, /save

!y.style = 1
!y.thick = 3.0
!y.ticks = 3
!y.tickname = [' ', strarr(!y.ticks) + '']

;; colors
loadct, 34
fix_ct_ends
;; ----------------------------------------------------------------------
;; Top panel -- velocity
;; ----------------------------------------------------------------------
ion = 'He2+'
i_ion = where(d.ion eq ion, ni_ion)

if (ni_ion le 0) then begin
  print, thisprog+' -F- no data for '+ion+' found.  Exiting...'
  return
endif

nplot = nelements
;title = ''
switch_x_labels, /off
plot, d.doyfr[i_ion], d.v[i_ion], $
  ytitle='v!IHe!N (km/s)', title=TITLE, position=positions[nplot,*],$
  yticks=3, ytickname=[' ','','',''],$
  yrange=v_yrange
oplot,  d.doyfr[i_ion], d.v[i_ion], psym=4
nplot = nplot - 1  ;; 

;; ----------------------------------------------------------------------
;; Average charge panels
;; ----------------------------------------------------------------------
for ielem = 0, nelements-1 do begin

  ;; x axis label/ticks only for bottom plot
  if (nplot eq 0) then begin
    switch_x_labels, /on
  endif else begin
    switch_x_labels, /off
  endelse

  ave_q_plot, data=d, element=ELEMENTS[ielem], position=positions[nplot,*],$
    yrange=yranges[*,ielem], min_value=MIN_VALUE
  nplot = nplot - 1  ;; 

  ;; over plot Sue's data
  if (ELEMENTS[ielem] eq 'Fe' and keyword_set(slfe)) then begin
    slfile = 'slepri_FE2hr03300_312.dat'
    restore, file='slfe_template.save'
    dsl = read_ascii(slfile, template=slfe_template)
    oplot, dsl.doyfr, dsl.aveq, color=255
  endif

endfor

xyouts, .995*Positions[nelements,2], Positions[nelements,3]-.025,$
  ACCUM_TIME_STR, /normal, charsize=1.0, alignment=1.0

;; draw line at shocks
i_x_in_range = where(shock_times ge !x.range[0] and $
                                shock_times le !x.range[1], nwhere)
if (nwhere gt 0) then begin
  shock_times = shock_times[i_x_in_range]
  for ishock=0,n_elements(shock_times)-1 do begin
    shockx = convert_coord([shock_times[ishock],0.0] , /to_normal)
    plots,[shockx[0],shockx[0]],$
          ;; upper-most y value, lower-most y value
          [Positions[nelements,3],Positions[0,1]],$
          /normal, color=255
  endfor
endif

;; draw line at transitions
for itrans=0,n_elements(trans_times)-1 do begin
;for itrans=0,0 do begin
  transx = convert_coord([trans_times[itrans],0.0] , /to_normal)
  plots,[transx[0],transx[0]],$
    ;; upper-most y value, lower-most y value
    [Positions[nelements,3],Positions[0,1]],$
    /normal, color=trans_colors[itrans], linestyle=1
endfor

tagplot, line1=tag, line2='University of Michigan', /dir
ficlose

return
end

