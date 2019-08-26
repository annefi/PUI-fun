; Filename: axlv2_deliv_nvt.pro
;
; Description:
;   Plot data from axlv2_deliv_nvt*.dat files, including SWEPAM overplot
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
; $Id: axlv2_deliv_nvt.pro,v 1.4 2005/06/06 20:43:50 jraines Exp $
;
; Major Modification History
;     Jan2005   lee   initial coding
;   20Apr2005   jmr   generalized for production use
;   09May2005   jmr   added WIND/SWE data overplot
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        axlv2_deliv_nvt*.dat data file
; O   data        axlv2_deliv_nvt data structure
; [I] swepam_file optionally specify SWEPAM data to be overplotted.
;                 Data described in 'Method' section above
; [O] swepam_data swepam data returned in this structure if specified
; [I] he_scalar   optionally specify scalar for AXLV2 He2+ density to 
;                 to better match SWEPAM
; [I] tag         optionally specify a text tag for the PS filename
; [I] doyfr_ranges optionally specify a set of day of year (fraction)
;                  range into which to devide the plots
; [I] swe_file    optionally specify WIND/SWE data to be overplotted.
;                 Data described in 'Method' section above
; [I] swe_data    SWE data returned in this structure if specified
pro axlv2_deliv_nvt, file=file, data=dswics, swepam_file=swepam_file, $
                     swepam_data=swepam_data, he_scalar=he_scalar, tag=tag,$
                     doyfr_ranges=doyfr_ranges, swe_file=swe_file, $
                     swe_data=swe_data, n_pnts=n_pnts

thisprog = 'axlv2_deliv_nvt'

;; --- extract elements from filename ---
;; proto. filename: axlv2_deliv_nvt_2003326_2003350.dat
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

;; Set default He2+ scalar.  Axlv2 He2+ density is multiplied by this
;; number to try to match SWEPAM.
DEF_HE_SCALAR = 4.0

;; Colors, from color table 34
;; --- SWEPAM data
SWEPAM_COLOR = 254
;; --- SWE data
SWE_COLOR = 40

main_title = 'ACE/SWICS Level II Deliv. NVT (v. 2, pre-release)'
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
!y.style=0
!y.thick = !x.thick
!y.style = 1
!y.ticks = 3
!y.tickname = [' ', strarr(!y.ticks) + '']

;; ----------------------------------------------------------------------
;; set defaults and misc
;; ----------------------------------------------------------------------
if (not keyword_set(he_scalar)) then he_scalar = DEF_HE_SCALAR
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
PlotsPerPage = 3
!p.multi = [0,1,PlotsPerPage]
margin = .12
positions = plot_positions(lmargin=margin,rmargin=margin,$
                           tmargin=margin,bmargin=margin,$
                           nplots=PlotsPerPage)
;; ----------------------------------------------------------------------
;; read, select and massage data
;; ----------------------------------------------------------------------
;;read swics data
restore, file='axlv2_deliv_nvt_template.save'
dswics = read_ascii(file, template=template, comment='#')

;;find swics temp & density
swics_temp = ((((dswics.vthHe2*1000.)^2)*4./6.02e26)/(2.*(1.38e-23)))/3
dswics.nHe2 = dswics.nHe2*he_scalar
he_scalar_str = string(format='("SWICS n scaled by ",F6.2)', he_scalar)

if (keyword_set(swepam_file)) then begin
  ;;read swepam data
  restore, file='axlv2_deliv_nvt_swepam_template.save'
  swepam_data = read_ascii(swepam_file, template=template)

  ;; select data of correct year and not fill for each of n, v and t
  year = fix(year_str)
  ;; --- n
  i_use_n = where(swepam_data.year eq year and $
                swepam_data.proton_density gt 0. and $
                swepam_data.He4toprotons gt 0., nwhere)
  if (nwhere le 0) then begin
    print, thisprog+'-F- no good SWEPAM He2+ density data for year '+year_str
    goto, exit_now
  endif
  ;; --- v
  i_use_v = where(swepam_data.year eq year and $
                  swepam_data.proton_speed gt 0., nwhere)
  if (nwhere le 0) then begin
    print, thisprog+'-F- no good SWEPAM speed data for year '+year_str
    goto, exit_now
  endif
  ;; --- t
  i_use_t = where(swepam_data.year eq year and $
                  swepam_data.proton_temp gt 0., nwhere)
  if (nwhere le 0) then begin
    print, thisprog+'-F- no good SWEPAM temperature data for year '+year_str
    goto, exit_now
  endif

endif

if (keyword_set(swe_file)) then begin
  ;;read swe data
  restore, file='axlv2_deliv_nvt_swe_template.save'
  swe_data = read_ascii(swe_file, template=template)

  ;; calculate swe He2+ temperature from vth
  swe_temp = ((((swe_data.vthHe2*1000.)^2)*4./6.02e26)/(2.*(1.38e-23)))/3
endif

;; ----------------------------------------------------------------------
;; loop over ranges and plot
;; ----------------------------------------------------------------------
num_doyfr_ranges= n_elements(doyfr_ranges[0,*])
for i_range = 0, num_doyfr_ranges-1 do begin
  range=doyfr_ranges[*, i_range]
  nplot = PlotsPerPage - 1

  switch_x_labels, /off
  ;; --- density
  plot, dswics.doyfr, dswics.nHe2,  /ylog, ystyle=0, $
        ytitle='Density (cm!E3!N)',xrange=range, min=0., $
        position=positions[nplot--,*], yrange = [1.e-3,1.]
  if (keyword_set(n_pnts)) then $
    oplot, dswics.doyfr, dswics.nHe2, min=0., psym=4, max=5.e3
  if (keyword_set(swepam_file)) then $
    oplot, swepam_data.fp_doy[i_use_n], $
           swepam_data.proton_density[i_use_n] * $
           swepam_data.He4toprotons[i_use_n], $
           min=0., color=SWEPAM_COLOR
  if (keyword_set(swe_file)) then $
    oplot, swe_data.doyfr, swe_data.nHe2, min=0., color=SWE_COLOR, max=5.e3

  ;; --- velocity
  plot, dswics.doyfr, dswics.vHe2, ytitle='Velocity (km/s)',$
        xrange=range, min=0., $
        position=positions[nplot--,*]
  if (keyword_set(swepam_file)) then $
    oplot, swepam_data.fp_doy[i_use_v], swepam_data.proton_speed[i_use_v],$
           color=SWEPAM_COLOR, min=0.
  if (keyword_set(swe_file)) then $
    oplot, swe_data.doyfr, swe_data.vHe2, min=0., color=SWE_COLOR, max=5.e3

  ;; --- temperature
  switch_x_labels, /on
  plot, dswics.doyfr, swics_temp,ytitle='Temperature(K)', $
        xrange=range, min=0.,$
        position=positions[nplot--,*]
  if (keyword_set(swepam_file)) then $
    oplot, swepam_data.fp_doy[i_use_t], swepam_data.proton_temp[i_use_t], $
           min=0., color=SWEPAM_COLOR
  if (keyword_set(swe_file)) then $
    oplot, swe_data.doyfr, swe_temp, min=0., color=SWE_COLOR,max=5.e7 

  ;; add notation of Carrington rotation
  year = long(year_str)*1000L
  cr_str = string(format='(I4)',fix(ydoyfr2crfr(year+range[0]))) + ' - ' + $
           string(format='(I4)',fix(ydoyfr2crfr(year+range[1])))
  xyouts, positions[PlotsPerPage-1,2]+.01, positions[PlotsPerPage-1,3],$
          'Carrington rotation range: '+cr_str, $
          orien=270, align=0.0, /normal, size=0.9

  ;; add He scalar
  xyouts, positions[0,2]+.01, positions[0,1],$
          he_scalar_str, $
          orien=270, align=1.0, /normal, size=0.9

  tagplot, /dir

  ;; add plot title
  xyouts, .5, 1.0-margin+0.04, main_title, align=0.5, /normal, $
        size=!p.charsize

  ;; add plot subtitle
  if (keyword_set(swepam_file)) then $
    xyouts, .5, margin-.1, 'SWEPAM data over-plotted in red', $
            align=0.5, /normal, $
            size=!p.charsize*.6, color=SWEPAM_COLOR
  if (keyword_set(swe_file)) then $
    xyouts, .5, margin-.1, 'WIND/SWE data over-plotted in blue', $
            align=0.5, /normal, $
            size=!p.charsize*.6, color=SWE_COLOR
endfor

;; ----------------------------------------------------------------------
;; clean up and get out
;; ----------------------------------------------------------------------
exit_now:

ficlose
!p.multi = 0

return
end
