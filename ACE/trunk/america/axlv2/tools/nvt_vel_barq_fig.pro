; Filename: nvt_vel_barq_fig.pro
;
; Description:
;   Create multi-panel plot with velocity on top and selected charge
;   distribution bar plot on bottom.  This was designed for
;   publication and is not very general.  It is best used by copying
;   to working directory and modifying to suit.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: nvt_vel_barq_fig.pro,v 1.2 2005/03/24 05:03:24 jraines Exp $
;
; Major Modification History
;     Nov2004   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
; I   doyfrs      day of year fractions to call out in bar plots
; [I] tag         optional text tag for filename
; [I] error_level specify error level above which data is discarded
pro nvt_vel_barq_fig, file=file, data=d, doyfrs=doyfrs, tag=tag, $
  error_level=error_level
;;; make velocity and Q bar graph figure

thisprog='nvt_vel_barq_fig'
;; ==========> frequently changed configuration variables <====================

;; define parameters for velocity plot
;IONS = ['O2+','C5+', 'O6+']     ; over-plotted on vhe
;COLORS = [50, 125, 254]
IONS = ['He2+','C5+','O6+']
COLORS = [0,50, 254]
VEL_YRANGE = [400.0,500.0]

TITLE = 'ACE/SWICS Level II (prelim) -- Charge Distributions'

;; nvt data with cnt_error higher than this fraction discarded
;; can be over-ridden by keyword
DEFAULT_ERROR_LEVEL = .7

;; set up elements for which to plot q bar graphs
elements = ['C','O','Fe']
yranges =[[0.,1.0],[0.,1.0],[0.0,1.0]]

;; ============================================================================

if (not keyword_set(error_level)) then error_level=DEFAULT_ERROR_LEVEL

;; read data
tplatefile = 'axlv2_nvt_template.save'
restore, file=tplatefile
d = read_ascii(file, template=template, comment='#')
filter_nvt_by_qual, nvtdata=d, error_level=error_level

;; change -1.0 (fill) to 0.0 for this calculation
i_zero = where(d.n lt 0., nwhere)
if (nwhere gt 0) then d.n[i_zero] = 0.

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

;device, xsize=11, ysize=8.5
device, /portrait
!p.charsize = 1.3
!p.charthick = 3.0
!p.thick = 5.0

!x.style = 1
!x.thick = 3.0
!x.minor = 2
!x.ticks = 0
!x.tickformat = '(F6.2)'

!y.style = 1
!y.thick = 3.0

;; turns off use of position keyword when set to zero
no_position=0

title = 'Relative Abundances'
title = ' '

nelements = n_elements(elements)
ndoyfrs=n_elements(doyfrs)

num_ions = n_elements(IONS)
;; ----------------------------------------------------------------------
;; Set up and calculate plot positions
;; ----------------------------------------------------------------------
;; number of plots per page
npp = ndoyfrs*nelements + 1

positions = plot_positions_bng(lmargin=0.05,rmargin=0.05,$
                               tmargin=0.05,bmargin=0.05,$
                               nplots=npp, hspace=0.01, vspace=0.0,$
                               halfspace=0.16, ncol=ndoyfrs, nrow=nelements)
;; ----------------------------------------------------------------------
;; Top panel -- velocity
;; ----------------------------------------------------------------------
!p.multi = [0, 1, 2, 1, 1]
!y.range = VEL_YRANGE
ion = 'He2+'

nplot = 0

for nion=0, num_ions-1 do begin
  ion = IONS[nion]

  i_elem = where( d.ion eq ion, nwhere)

  if (nwhere le 0) then begin
    print, thisprog+' -E- vel. data for '+element
    goto, next_v_elem
  endif

  if (nion eq 0) then begin
    axlv2_nvt_vel, data=d, ion=ion, doyfr_lines=doyfrs,title=TITLE,$
                   position=positions[nplot,*], no_position=no_position
  endif else begin
    oplot, d.doyfr[i_elem], d.v[i_elem], color=COLORS[nion]
  endelse

  xyouts, positions[nplot,2]+.01, positions[nplot,3]-.05-(.05*nion), ion, $ 
          color=COLORS[nion], /normal , size=1.0
 

  next_v_elem:
endfor
;; ----------------------------------------------------------------------
;; Bottom panel -- selected Q bar graphs
;; ----------------------------------------------------------------------
!x.tickformat = ''
!p.multi = [ndoyfrs*nelements, ndoyfrs, 2*nelements, 1, 0]

for ielem = 0, nelements-1 do begin

  if (ielem ne 0) then no_title=1 else no_title=0

  nvt_barq_plot, data=d, element=elements[ielem], doyfrs=doyfrs, $
    no_title=no_title, positions=positions, nplot=nplot,yrange=yranges[*,ielem],$
    no_position=no_position

endfor

err_str = string(format='(F4.2)',error_level)
tagplot, line1=tag, line2='err = '+err_str

xyouts, Positions[0,2]-.015, Positions[0,3]-.040,$
  'Day of '+year_str, /normal, charsize=1.0, alignment=1.0

ficlose

return
end

