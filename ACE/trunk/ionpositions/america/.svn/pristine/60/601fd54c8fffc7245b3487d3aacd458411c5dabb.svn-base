; Filename: axlv2_deliv_elem_corr.pro
;
; Description:
;   Plot correlations from axlv2_deliv_elem*.dat files.
;
; Author: Jim Raines (jmr)
;
; Method:
;;   
; Revision controlled by CVS:
; $Id: axlv2_deliv_elem_corr.pro,v 1.1 2005/05/11 21:01:32 jraines Exp $
;
; Major Modification History
;   11May2005   jmr   Adapted from axlv2_deliv_elem.pro
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        axlv2_deliv_elem*.dat data file
; O   data        axlv2_deliv_elem data structure
; [I] tag         optionally specify a text tag for the PS filename
; [I] doyfr_ranges optionally specify a set of day of year (fraction)
;                  range into which to devide the plots

pro axlv2_deliv_elem_corr, file=file, data=d, tag=tag,$
                     doyfr_ranges=doyfr_ranges

thisprog = 'axlv2_deliv_elem_corr'

;; --- extract elements from filename ---
;; proto. filename: axlv2_deliv_elem_2003326_2003350.dat
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
YLOG = 1

;; plotting symbol
PSYM = 4

;; defaults
; He, Mg, Fe, Si, C, Ne  (plot order: bottom to top)
ranges = [[1.e-2,1.e1],[1.e-2,1.e1],[1.e-2,1.e1],[1.e-2,1.e1], $
          [1.e-2,1.e1],[1.e-2,1.e1]]

main_title = 'ACE/SWICS Level II Deliv. Abundance Correlations'
main_title = main_title + '!C(v. 2, pre-release)'
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
!x.ticklen = 0.04
!x.charsize = 1.0
;; X axis label info for bottom plot only
!x.title='Day of Year '+year_str
!x.ticks=3                      ; 3 tailored for CR intervals
!x.minor=10                      ; 9 tailored for CR intervals
!x.tickname=[' ', strarr(!x.ticks) + ''] ; automatic is all ''
switch_x_labels, /save          ; save these for bottom plot
switch_x_labels, /on

;; force axis behavior to be specified
!y.style=1
!y.thick = !x.thick
!y.charsize = !x.charsize
!y.ticks = 3
!y.minor = 10
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

!p.multi = [0,2,2]

;; ----------------------------------------------------------------------
;; read, select and massage data
;; ----------------------------------------------------------------------
;;read swics data
restore, file='axlv2_deliv_elem_template.save'
d = read_ascii(file, template=template, comment='#')

;; ----------------------------------------------------------------------
;; loop over ranges and plot
;; ----------------------------------------------------------------------
num_doyfr_ranges= n_elements(doyfr_ranges[0,*])

for i_range = 0, num_doyfr_ranges-1 do begin

  range=doyfr_ranges[*, i_range]

  nrange = 6                   ; set to number of plots below
  plot, d.C_O, d.Ne_O, xtitle='C/O', ytitle= 'Ne/O', min=0., $
        ylog=YLOG, xlog=YLOG, yrange=ranges[*,--nrange],$
        xrange=ranges[*,nrange], psym=PSYM

  plot, d.Mg_O, d.Fe_O, xtitle='Mg/O',ytitle= 'Fe/O', min=0., $
        ylog=YLOG, xlog=YLOG, yrange=ranges[*,--nrange],$
        xrange=ranges[*,nrange], psym=PSYM

  plot, d.Si_O, d.Fe_O, xtitle='Si/O', ytitle= 'Fe/O', min=0., $
        ylog=YLOG, xlog=YLOG, yrange=ranges[*,--nrange], $
        xrange=ranges[*,nrange], psym=PSYM

  plot, d.Si_O, d.Mg_O, xtitle='Si/O', ytitle= 'Mg/O', min=0., $
        ylog=YLOG, xlog=YLOG, yrange=ranges[*,--nrange], $
        xrange=ranges[*,nrange], psym=PSYM

  ;; add notation of Carrington rotation
  range = [min(doyfr_ranges[*,*]),max(doyfr_ranges[*,*])]
  year = long(year_str)*1000L
  cr_str = string(format='(I4)',fix(ydoyfr2crfr(year+range[0]))) + ' - ' + $
           string(format='(I4)',fix(ydoyfr2crfr(year+range[1])))
  xyouts, 1.0, 0.5,$
          'Carrington rotation range: '+cr_str, $
          orien=270, align=0.5, /normal, size=0.9

  tagplot, /dir

  ;; add plot title
  xyouts, .5, 1.0, main_title, align=0.5, /normal, $
        size=!p.charsize

  ;; more plots
  plot, d.C_O, d.Fe_O, xtitle='C/O',ytitle= 'Fe/O', min=0., $
        ylog=YLOG, xlog=YLOG, yrange=ranges[*,--nrange],$
        xrange=ranges[*,nrange], psym=PSYM

  plot, d.Ne_O, d.Fe_O, xtitle='Ne/O',ytitle= 'Fe/O', min=0., $
        ylog=YLOG, xlog=YLOG, yrange=ranges[*,--nrange],$
        xrange=ranges[*,nrange], psym=PSYM

  ;; add notation of Carrington rotation
  range = [min(doyfr_ranges[*,*]),max(doyfr_ranges[*,*])]
  year = long(year_str)*1000L
  cr_str = string(format='(I4)',fix(ydoyfr2crfr(year+range[0]))) + ' - ' + $
           string(format='(I4)',fix(ydoyfr2crfr(year+range[1])))
  xyouts, 1.0, 0.5,$
          'Carrington rotation range: '+cr_str, $
          orien=270, align=0.5, /normal, size=0.9

  tagplot, /dir

  ;; add plot title
  xyouts, .5, 1.0, main_title, align=0.5, /normal, $
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
