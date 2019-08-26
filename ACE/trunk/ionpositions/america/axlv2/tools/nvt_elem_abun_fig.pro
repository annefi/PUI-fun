; Filename: elem_abun_fig.pro
;
; Description:
;   Build elemental abundance figure out of ACE/SWICS Level II NVT data.
;
; Author: Jim Raines (jmr)
;
; Method:
;   First panel is He2+ velocity.  Second panel is average charge
;   state of oxygen.  Subsequent panels are ratios specified below.
;   
; Revision controlled by CVS:
; $Id: nvt_elem_abun_fig.pro,v 1.1 2005/03/14 16:53:40 jraines Exp $
;
; Major Modification History
;   ddmmmyyyy   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; [O] data        optionally return nvt data structure in this variable
; [I] oplot_pnts  optionally over plot points
; [I] tag         optionally tag filename with this string
;                 (alpha-numeric and _ or - only)
pro elem_abun_fig, file=file, data=d, tag=tag, oplot_pnts=oplot_pnts

thisprog = 'elem_abun'

;; extract elements from filename
file_parse, file=file, split_base=sb
tmp = split_ydoy(sb[2], /strings)
year_str = tmp[0]

;; ==========> frequently changed configuration variables <====================
;; plot title
TITLE='ACE/SWICS Level II (prelim) -- Elemental Abundances'

ACCUM_TIME_STR = '1 hour averages'

;; element ratios
;; Note: 4He must be specified at ^He; 3He as 3He
;; He will include 3He and 4He
ELEM_RATIOS = [['C','O'],['Fe','O']]

;; yranges
YRANGES = [[.2,2.],[.01,1.]]

;; nvt data with F0 error above this level are thrown out
ERROR_LEVEL = .5

shock_times = [301.061944,302.248611,303.679861,308.249305,310.804861]

;; times of abrupt transitions in composition and assoc. line colors
trans_times = [301.104167,301.354167,302.333333,303.666667,$
              304.083333,306.75]
trans_colors = [40,40,40,40,40,40]

;; ----- plot formatting -----
;; overall plot
!p.charsize = 3.0
!p.charthick = 3.0
!p.thick = 5.0

;; X axis
!x.style = 1
!x.thick = 3.0
!x.ticklen = 0.04
;; X axis label info for bottom plot only
!x.title='Day of Year '+year_str
!x.tickname=['']                ; automatic
!x.ticks=0                      ; automatic
!x.tickformat = 'doy2date_tick'
!x.minor = 2
!x.style = 9
switch_x_labels, /save

;; Y axis
!y.style = 1
!y.thick = 3.0
!y.ticks = 3
!y.tickname = [' ', strarr(!y.ticks) + '']

;; ============================================================================
;; number of plots per page
npp = n_elements(ELEM_RATIOS[0,*]) + 2
nplot = npp
!p.multi=[0,1,npp,1,1]

;; read data
tplatefile = 'axlv2_nvt_template.save'
restore, file=tplatefile
d = read_ascii(file, template=template, comment='#')
filter_nvt_by_qual, nvtdata=d, error_level=ERROR_LEVEL

doyfrs = d.doyfr(uniq(d.doyfr))
ndoyfrs = n_elements(doyfrs)

num_ratios = n_elements(ELEM_RATIOS[0,*])

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
Positions = plot_positions(lmargin=0.07,rmargin=0.07,$
                           tmargin=0.07,bmargin=0.07,nplots=npp)

device, /landscape
;; ----------------------------------------------------------------------
;; Top panel -- He2+ speed
;; ----------------------------------------------------------------------
ion = 'He2+'
i_ion = where(d.ion eq ion, ni_ion)

if (ni_ion le 0) then begin
  print, thisprog+' -F- no data for '+ion+' found.  Exiting...'
  return
endif

switch_x_labels, /off

plot, d.doyfr[i_ion], d.v[i_ion], $
  ytitle='v!DHe!N (km/s)', title=TITLE, position=positions[--nplot,*],$
  yrange=[400.0,500.0], ystyle=0,xtickname=xtickname,xticks=xticks

if (keyword_set(oplot_pnts)) then oplot,doyfrs, ratio, psym=4

;; ----------------------------------------------------------------------
;; Second panel -- Ave Q for O
;; ----------------------------------------------------------------------
switch_x_labels, /off
ave_q_plot, data=d, element='O', position=positions[--nplot,*],$
            yrange=[2,8],ytitle='<Q!IO!N>'

;; ----------------------------------------------------------------------
;; Plot element ratios
;; ----------------------------------------------------------------------
for nratio=0,num_ratios-1 do begin
  elem1 = ELEM_RATIOS[0,nratio]
  elem2 = ELEM_RATIOS[1,nratio]

  print, thisprog+' -I- working on '+elem1+'/'+elem2

  ratio = axlv2_nvt_abun(data=d,element=elem1) / $
    axlv2_nvt_abun(data=d,element=elem2)
          
  ;; last plot
  if (nratio eq num_ratios-1) then begin
    switch_x_labels, /on
  endif else begin
    switch_x_labels, /off
  endelse

  plot, doyfrs, ratio,  /ylog, ytitle=elem1+'/'+elem2, $
        position=positions[--nplot,*], yrange=YRANGES[*,nratio]
        
  if (keyword_set(oplot_pnts)) then oplot,  doyfrs,  alog10(ratio), psym=4
endfor

;; ----------------------------------------------------------------------
;; Pack up and get out
;; ----------------------------------------------------------------------

tagplot, line1=tag, line2='University of Michigan'

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

xyouts, .995*Positions[0,2], Positions[npp-1,3]-.025,$
  ACCUM_TIME_STR, /normal, charsize=1.0, alignment=1.0

ficlose

return
end

