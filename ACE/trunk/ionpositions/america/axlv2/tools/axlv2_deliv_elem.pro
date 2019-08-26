; Filename: axlv2_deliv_elem.pro
;
; Description:
;   Plot data from axlv2_deliv_elem*.dat files, including SWEPAM overplot
;
; Author: Laura Emig (lee)
;         Jim Raines (jmr)
;
; Method:
;
;   SWEPAM data is Level 2, downloaded from the ACE Science Center.
; Care must be taken to select the right columns to keep from having
; to make a new template.  The current template expects columns in the
; following order:
;
; year fp_doy proton_density proton_temp He4toprotons proton_speed
;   
; Revision controlled by CVS:
; $Id: axlv2_deliv_elem.pro,v 1.3 2005/05/11 21:01:32 jraines Exp $
;
; Major Modification History
;     Jan2005   lee   initial coding
;   20Apr2005   jmr   generalized for production use
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

pro axlv2_deliv_elem, file=file, data=d, tag=tag,$
                     doyfr_ranges=doyfr_ranges

thisprog = 'axlv2_deliv_elem'

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

;; defaults
; He, Mg, Fe, Si, C, Ne  (plot order: bottom to top)
yranges = [[1.e1,1.e3],[1.e-2,1.e1],[1.e-2,1.e1],$
           [1.e-2,1.e1],[1.e-1,1.e1],[1.e-1,1.e1]]

main_title = 'ACE/SWICS Level II Deliv. Elemental Abundances'
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
;; X axis label info for bottom plot only
!x.title='Day of Year '+year_str
!x.ticks=3                      ; 3 tailored for CR intervals
!x.minor=9                      ; 9 tailored for CR intervals
!x.tickname=[strarr(!x.ticks) + ''] ; automatic is all ''
switch_x_labels, /save          ; save these for bottom plot

;; force axis behavior to be specified
!y.style=1
!y.thick = !x.thick
!y.style = 0
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
restore, file='axlv2_deliv_elem_template.save'
d = read_ascii(file, template=template, comment='#')

;; ----------------------------------------------------------------------
;; loop over ranges and plot
;; ----------------------------------------------------------------------
num_doyfr_ranges= n_elements(doyfr_ranges[0,*])

for i_range = 0, num_doyfr_ranges-1 do begin

  range=doyfr_ranges[*, i_range]
  nplot = PlotsPerPage - 1

  switch_x_labels, /off
  nyrange = 6
  plot, d.doyfr, d.Ne_O, ytitle= 'Ne/O', min=0., xrange=range,  $
        position=positions[nplot--,*], ylog=YLOG, yrange=yranges[*,--nyrange],$
        yticks=2

  plot, d.doyfr, d.C_O, ytitle= 'C/O', min=0., xrange=range,  $
        position=positions[nplot--,*], ylog=YLOG, yrange=yranges[*,--nyrange],$
        yticks=2

  plot, d.doyfr, d.Si_O, ytitle= 'Si/O', min=0., xrange=range, $
        position=positions[nplot--,*], ylog=YLOG, yrange=yranges[*,--nyrange]

  plot, d.doyfr, d.Fe_O, ytitle= 'Fe/O', min=0., xrange=range,  $
        position=positions[nplot--,*], ylog=YLOG, yrange=yranges[*,--nyrange]

  plot, d.doyfr, d.Mg_O, ytitle= 'Mg/O', min=0., xrange=range,  $
        position=positions[nplot--,*], ylog=YLOG, yrange=yranges[*,--nyrange]

  switch_x_labels, /on
  plot, d.doyfr, d.He_O, ytitle= 'He/O', min=0., xrange=range, $
        position=positions[nplot--,*], ylog=YLOG, yrange=yranges[*,--nyrange],$
        yticks=2

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

  ;; add plot subtitle
  if (keyword_set(swepam_file)) then $
    xyouts, .5, margin-.1, 'SWEPAM data over-plotted in red', $
            align=0.5, /normal, $
            size=!p.charsize*.6
endfor
;; ----------------------------------------------------------------------
;; clean up and get out
;; ----------------------------------------------------------------------
exit_now:

ficlose
!p.multi = 0

return
end
