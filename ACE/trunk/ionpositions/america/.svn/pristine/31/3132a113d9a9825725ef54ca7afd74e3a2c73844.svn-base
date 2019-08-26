; Filename: axlv2_deliv_qratio.pro
;
; Description:
;   Plot data from axlv2_deliv_qratio*.dat files, including SWEPAM overplot
;
; Author: Laura Emig (lee)
;         Jim Raines (jmr)
;
; Method:
;
;   This program overplots points in red which have the quality flag
;   set.  NOTE:  It relies on this flag only being 0 or 1.
;   
; Revision controlled by CVS:
; $Id: axlv2_deliv_qratio.pro,v 1.3 2005/06/06 20:43:50 jraines Exp $
;
; Major Modification History
;     Jan2005   lee   initial coding
;   20Apr2005   jmr   generalized for production use
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        axlv2_deliv_qratio*.dat data file
; O   data        axlv2_deliv_qratio data structure
; [I] tag         optionally specify a text tag for the PS filename
; [I] doyfr_ranges optionally specify a set of day of year (fraction)
;                  range into which to devide the plots

pro axlv2_deliv_qratio, file=file, data=d, tag=tag,$
                     doyfr_ranges=doyfr_ranges, oplot_points=oplot_points

thisprog = 'axlv2_deliv_qratio'

;; --- extract elements from filename ---
;; proto. filename: axlv2_deliv_qratio_2003326_2003350.dat
file_parse, file=file, base=base, split_base=sb
ydoy_str = sb[3]
;; --- grab year string
tmp = split_ydoy(sb[3], /strings)
year_str = tmp[0]
;; --- grab doy (float) and set doyfr range for pltos
tmp = split_ydoy(sb[3])
doy = tmp[1]
file_doyfr_range = [doy,doy]
;; --- add second date if present (assumes same year)
if (n_elements(sb) eq 5) then begin
  tmp = split_ydoy(sb[4])
  doy2 = tmp[1]
  file_doyfr_range = [doy,doy2]
endif

;; ----------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------
;; plot y-axis on log scale
YLOG = 0

;; error point color
ERR_COLOR = 254

;; symbol for optional symbol overplotting
DATA_PSYM = 4
DATA_SYMSIZE = 0.5

main_title = 'ACE/SWICS Level II Deliv. QRATIOs!C(v. 2, pre-release)'
!p.title=''
!p.font = 1  ; True-type fonts
font = 'Times'
!p.charsize = 2.0
!p.charthick = 6.0
!p.thick = 5.0
!p.font = 0

;; X axis
!x.style = 1
!x.thick = 5.0
!x.charsize = 1.2
!x.ticklen = 0.04
;; X axis label info for bottom plot only
!x.title='Day of Year '+year_str
!x.ticks=3                      ; 3 tailored for CR intervals
!x.minor=9                      ; 9 tailored for CR intervals
!x.tickname=[strarr(!x.ticks) + ''] ; automatic is all ''
switch_x_labels, /save          ; save these for bottom plot

;; force axis behavior to be specified
!y.style=1
!y.thick = !x.thick
!y.charsize = !x.charsize
!y.ticks = 4
!y.minor = 0
!y.tickname = [' ', strarr(!y.ticks) + '']

;; ----------------------------------------------------------------------
;; set defaults and misc
;; ----------------------------------------------------------------------
tagsep='_'
if (not keyword_set(tag)) then begin 
  tag=''
  tagsep=''
endif

;; set up doyfr range(s)
if (not keyword_set(doyfr_ranges)) then begin
  doyfr_ranges = [file_doyfr_range]
endif
;; ----------------------------------------------------------------------
;; set up plots
;; ----------------------------------------------------------------------
;; set up postscript plot
psfile = base+tagsep+tag+'.ps'
psplt, file=psfile, /color      ; open PS file
loadct, 34
fix_ct_ends

;; figure out plot positions
PlotsPerPage = 6
!p.multi = [0,1,PlotsPerPage]
margin = .12
positions = plot_positions(lmargin=margin,rmargin=margin,$
                           tmargin=margin,bmargin=margin,$
                           nplots=PlotsPerPage)
;; ----------------------------------------------------------------------
;; read, select and massage data
;; ----------------------------------------------------------------------
;;read swics data
restore, file='axlv2_deliv_qratio_template.save'
d = read_ascii(file, template=template, comment='#')

;; ----------------------------------------------------------------------
;; loop over ranges and plot
;; ----------------------------------------------------------------------
num_doyfr_ranges= n_elements(doyfr_ranges[0,*])

for i_range = 0, num_doyfr_ranges-1 do begin

  range=doyfr_ranges[*, i_range]
  nplot = PlotsPerPage - 1

  switch_x_labels, /off
  plot, d.doyfr, d.ave_q_Fe, ytitle= '<Q!IFe!N>', min=0., xrange=range,$
        position=positions[nplot--,*], $
        yrange=[8.,20.]
  oplot, d.doyfr, d.ave_q_Fe*d.qf_ave_q_fe, color=ERR_COLOR, psym=DATA_PSYM, symsize=DATA_SYMSIZE, min=.1
  if (keyword_set(oplot_points)) then oplot, d.doyfr, d.ave_q_Fe, psym=DATA_PSYM, symsize=DATA_SYMSIZE
  
  plot, d.doyfr, d.ave_q_O, ytitle= '<Q!IO!N>', min=0., xrange=range,$
        position=positions[nplot--,*], $
        yrange=[5.,8.]
  oplot, d.doyfr, d.ave_q_O*d.qf_ave_q_O, color=ERR_COLOR, psym=DATA_PSYM, symsize=DATA_SYMSIZE, min=.1
  if (keyword_set(oplot_points)) then oplot, d.doyfr, d.ave_q_O, psym=DATA_PSYM, symsize=DATA_SYMSIZE

  plot, d.doyfr, d.ave_q_C, ytitle= '<Q!IC!N>', min=0., xrange=range,$
        position=positions[nplot--,*], $
        yrange=[4.,6.]
  oplot, d.doyfr, d.ave_q_C*d.qf_ave_q_C, color=ERR_COLOR, psym=DATA_PSYM, symsize=DATA_SYMSIZE, min=.1
  if (keyword_set(oplot_points)) then oplot, d.doyfr, d.ave_q_C, psym=DATA_PSYM, symsize=DATA_SYMSIZE

  plot, d.doyfr, d.no7_no6, ytitle= 'O!e7+!N/O!E6+!N', min=0., xrange=range,$
        position=positions[nplot--,*], ylog=1, $
        yrange=[1.e-2,1.e1], yticks=3, yminor=10
  oplot, d.doyfr, d.no7_no6*d.qf_no7_no6, color=ERR_COLOR, psym=DATA_PSYM, symsize=DATA_SYMSIZE, min=.1
  if (keyword_set(oplot_points)) then oplot, d.doyfr, d.no7_no6, psym=DATA_PSYM, symsize=DATA_SYMSIZE

  plot, d.doyfr, d.nc6_nc5, ytitle= 'C!e6+!N/C!E5+!N', min=0., xrange=range,$
        position=positions[nplot--,*], ylog=1, $
        yrange=[1.e-1,1.e1], yticks=2, yminor=10
  oplot, d.doyfr, d.nc6_nc5*d.qf_nc6_nc5, color=ERR_COLOR, psym=DATA_PSYM, symsize=DATA_SYMSIZE, min=.1
  if (keyword_set(oplot_points)) then oplot, d.doyfr, d.nc6_nc5, psym=DATA_PSYM, symsize=DATA_SYMSIZE

  switch_x_labels, /on
  plot, d.doyfr, d.no7_no6/d.nc6_nc5, $
        ytitle= 'O!e7+!N/O!E6+!N/C!e6+!N/C!E5+!N', min=0.,$
        xrange=range,  yrange=[1.e-2,1.e2], $
        position=positions[nplot--,*], ylog=1, yticks=4, yminor=10
  if (keyword_set(oplot_points)) then oplot, d.doyfr, d.no7_no6/d.nc6_nc5, psym=DATA_PSYM, symsize=DATA_SYMSIZE

  ;; add notation of Carrington rotation
  year = long(year_str)*1000L
  cr_str = string(format='(I4)',fix(ydoyfr2crfr(year+range[0]))) + ' - ' + $
           string(format='(I4)',fix(ydoyfr2crfr(year+range[1])))
  xyouts, positions[PlotsPerPage-1,2]+.01, positions[PlotsPerPage-1,3],$
          'Carrington rotation range: '+cr_str, $
          orien=270, align=0.0, /normal, size=0.9

  tagplot, /dir

  ;; add plot title
  xyouts, .5, 1.0-margin+0.06, main_title, align=0.5, /normal, $
        size=!p.charsize

endfor

;; ----------------------------------------------------------------------
;; clean up and get out
;; ----------------------------------------------------------------------
exit_now:

ficlose
!p.multi = 0

return
end
