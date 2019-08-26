; Filename: axlv2_deliv_aveq.pro
;
; Description:
;   Calculate and plot average charge from axlv2_deliv_*qdist*.dat files.
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
; $Id: axlv2_deliv_aveq.pro,v 1.3 2005/05/11 21:01:32 jraines Exp $
;
; Major Modification History
;     Jan2005   lee/jmr   initial coding
;   24Apr2005   jmr       generalized for production use
;
; Arguments:
;
; I/O Arg               Explanation
; --- ----------        -----------
; I   file_doyfr_range_str  doyfr range string present in desired data files
;                       Filename format is axlv2_deliv_E_doyfr0_doyfr1.dat,
;                       where 'E' is the element name string, e.g. Fe
; [I] tag               optionally specify a text tag for the PS filename
; [I] doyfr_ranges      optionally specify a set of day of year (fraction)
;                       range into which to devide the plots
; [I] elements          optionally specify elements to plot on a page,
;                       default is all 
; [I] doyfrs            optionally specify doyfs to plot from all files
;
pro axlv2_deliv_aveq, file_doyfr_range_str=file_doyfr_range_str,$
  tag=tag, doyfr_ranges=doyfr_ranges, elements=elements, doyfrs=doyfrs

thisprog = 'axlv2_deliv_aveq'

;; --- extract elements from filename --- FIX: multiple filenames
;; proto: file_doyfr_range = 2003326_2003350.dat
fdrs_parts = strsplit(file_doyfr_range_str, '_', /extract)
ydoy_str = fdrs_parts[0]
;; --- grab year string
tmp = split_ydoy(ydoy_str, /strings)
year_str = tmp[0]
;; --- grab doy (float) and set doyfr range for plots
tmp = split_ydoy(ydoy_str)
doy = tmp[1]
file_doyfr_range = [doy,doy]
;; --- add second date if present (assumes same year)
if (n_elements(fdr) eq 2) then begin
  tmp = split_ydoy(fdrs_parts[1])
  doy2 = tmp[1]
  file_doyfr_range = [doy,doy2]
endif

;; ----------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------
;; filename base
base = 'axlv2_deliv'

;; plot y-axis on log scale
YLOG = 0

;; error point color
ERR_COLOR = 254

;; defaults
DEF_ELEMENTS = ['Mg','Fe','Si','C','O','Ne']
DEF_YRANGES = [[8.,12.],[8.,20.],[8.,12.],[4.,6.],[5.,8.],[6.,10.]]

;; correlations (specified by index of desired element in elements array)
corrs = [[0,1],[0,2],[1,2],[3,4],[1,4],[4,5]]

;; un-comment for ranges which are all the same
;YLOG = 0
;yr0 = 4.0
;yr1 = 18.0
;DEF_YRANGES = [[yr0,yr1],[yr0,yr1],[yr0,yr1],[yr0,yr1],[yr0,yr1],[yr0,yr1]]


main_title = 'ACE/SWICS Level II Deliv. <Q> from Q dist.!C(v. 2, pre-release)'
main_title_corr = 'ACE/SWICS Level II Deliv. <Q> correlations from Q dist.!C(v. 2, pre-release)'
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
!x.charsize = 1.2
;; X axis label info for bottom plot only
!x.title='Day of Year '+year_str
!x.ticks=3                      ; 3 tailored for CR intervals
!x.minor=9                      ; 9 tailored for CR intervals
!x.tickname=[strarr(!x.ticks) + ''] ; automatic is all ''
switch_x_labels, /save              ; save these for bottom plot

;; force axis behavior to be specified
!y.style=1
!y.thick = !x.thick
!y.charsize = !x.charsize
!y.ticks = 4
!y.tickname = [' ', strarr(!y.ticks) + '']

;; ----------------------------------------------------------------------
;; set some defaults
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

;; choose default elements
if (not keyword_set(elements)) then begin
  elements = DEF_ELEMENTS
  yranges = DEF_YRANGES
endif else begin
  if (not keyword_set(yranges)) then begin
    print, thisprog+' -F- must also specify yranges when specifying elements'
    goto, exit_now
  endif
endelse

;; ----------------------------------------------------------------------
;; read from spec. element files and calculate average charge
;; ----------------------------------------------------------------------
restore, file='axlv2_deliv_qdist_template.save'
for nelem=0, n_elements(elements)-1 do begin
  file = base + '_' + elements[nelem] + '_qdist_' + $
         file_doyfr_range_str + '.dat'

  d = read_ascii(file, template=template, comment='#')

  ;; choose all doyfr values in file by default
  if (not keyword_set(doyfrs)) then begin
    doyfrs = d.doyfr[uniq(d.doyfr, sort(d.doyfr))]
  endif

  ;; set up array on first element only
  if (nelem eq 0) then ave_q = $
    make_array(n_elements(elements), n_elements(doyfrs), /float, value=0.0)

  ;; ---------------------------------------
  ;; calculate average charge for all doyfrs
  ;; ---------------------------------------
  for ndoyfr=0, n_elements(doyfrs)-1 do begin
    doyfr = doyfrs[ndoyfr]
    doyfr_str = string(format='(F6.2)',doyfrs[ndoyfr])

    ;; choose current doyfr
    i_doyfr = where(d.doyfr eq doyfr, num_ions)
    if (num_ions lt 1) then begin
      print, thisprog+' -W- no data at doyfr = '+doyfr_str
      goto, next_doyfr
    endif

    ;; calculate average charge
    for nion=0, num_ions-1 do begin
      if (d.rel_abun[i_doyfr[nion]] gt 0.) then begin
        ave_q[nelem,ndoyfr] += d.chg[i_doyfr[nion]] * $
          d.rel_abun[i_doyfr[nion]]
      endif
    endfor

    next_doyfr:
  endfor

endfor

;; ----------------------------------------------------------------------
;; set up plots
;; ----------------------------------------------------------------------
;; set up postscript plot
psfile = base+'_aveq_'+file_doyfr_range_str+tagsep+tag+'.ps'
psplt, file=psfile, /color      ; open PS file
loadct, 34
fix_ct_ends

;; figure out plot positions
PlotsPerPage = n_elements(elements)
!p.multi = [0,1,PlotsPerPage]
margin = .12
positions = plot_positions(lmargin=margin,rmargin=margin,$
                           tmargin=margin,bmargin=margin,$
                           nplots=PlotsPerPage)
;; ----------------------------------------------------------------------
;; loop over ranges and plot <Q>
;; ----------------------------------------------------------------------
num_doyfr_ranges= n_elements(doyfr_ranges[0,*])

for nrange = 0, num_doyfr_ranges-1 do begin

  range=doyfr_ranges[*, nrange]
  nplot = PlotsPerPage - 1

  ;; ------------------------------------------------------------
  ;; loop over elements
  ;; ------------------------------------------------------------
  for nelem=0, n_elements(elements)-1 do begin
    element = elements[nelem]

    if (nelem eq 0) then switch_x_labels, /on else switch_x_labels, /off
    
    plot, doyfrs, ave_q[nelem,*], ytitle= '<Q!I'+element+'!N>', min=0., $
          xrange=range, yrange=yranges[*,nelem], $
          position=positions[nelem,*], ylog=YLOG
          
    ;oplot, d.doyfr, d.ave_q_C*d.qf_ave_q_C, color=ERR_COLOR, psym=4, min=.1

  endfor

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
;; ---------------------- second set of plots ---------------------------
;; ----------------------------------------------------------------------
;; loop over ranges and plot <Q> correlations
;; ----------------------------------------------------------------------
;; figure out plot positions
PlotsPerPage = n_elements(corrs[0,*])
!p.multi = [0,2,2]
margin = .12
positions = plot_positions(lmargin=margin,rmargin=margin,$
                           tmargin=margin,bmargin=margin,$
                           nplots=PlotsPerPage)
switch_x_labels, /on

main_title_corr = 'ACE/SWICS Level II Deliv. <Q> correlations from Q dist.!C(v. 2, pre-release)'
!p.title=''
!p.font = 1  ; True-type fonts
font = 'Times'
!p.charsize = 2.0
!p.charthick = 6.0
!p.thick = 5.0
!p.font = 0

;; X axis
!x.style = 1
!x.thick = 4.0
!x.ticklen = 0.04
!x.charsize = 1.0
;; X axis label info for bottom plot only
!x.title='Day of Year '+year_str
!x.ticks=3                      ; 3 tailored for CR intervals
!x.minor=0                      ; 9 tailored for CR intervals
;!x.tickname=[strarr(!x.ticks) + ''] ; automatic is all ''
switch_x_labels, /save              ; save these for bottom plot

;; force axis behavior to be specified
!y.style=1
!y.thick = !x.thick
!y.charsize = !x.charsize
!y.ticks = 3
;!y.tickname = [' ', strarr(!y.ticks) + '']


;; ------------------------------------------------------------
;; loop over correlations
;; ------------------------------------------------------------
for ncorr=0, n_elements(corrs[0,*])-1 do begin
  element0 = elements[corrs[0,ncorr]]
  element1 = elements[corrs[1,ncorr]]

                                ;if (ncorr eq 0) then switch_x_labels, /on else switch_x_labels, /off

;  xrange = [0.,20.]
  aqc = ave_q[corrs[0,ncorr],*]
  i_aqc = where(aqc gt 0.)
  xrange = [.9*min(aqc[i_aqc]),1.1*max(aqc[i_aqc])]
  aqc = ave_q[corrs[1,ncorr],*]
  i_aqc = where(aqc gt 0.)
  yrange = [.9*min(aqc[i_aqc]),1.1*max(aqc[i_aqc])]

  plot,ave_q[corrs[0,ncorr],*], ave_q[corrs[1,ncorr],*], $
       xtitle='<Q!I'+element0+'!N>', ytitle= '<Q!I'+element1+'!N>', $
       min=0., psym=4, xrange=xrange, yrange=yrange
                                ;xrange=range, yrange=yranges_corr[*,ncorr], $
                                ;position=positions[ncorr,*], $
  
  ;; overplot autocorrelation for reference
;  x = findgen(xrange[1])
;  mx = x
;  oplot, x, mx, color=40

  ;; --- doing these everytime is not required but is a quick fix ---
  ;; add notation of Carrington rotation
  range = [min(doyfr_ranges[*,*]),max(doyfr_ranges[*,*])]
  year = long(year_str)*1000L
  cr_str = string(format='(I4)',fix(ydoyfr2crfr(year+range[0]))) + ' - ' + $
           string(format='(I4)',fix(ydoyfr2crfr(year+range[1])))
  xyouts, 1.0, .5,$
          'Carrington rotation range: '+cr_str, $
          orien=270, align=0.5, /normal, size=0.9

  tagplot, /dir

  ;; add plot title
  xyouts, .5, 1.0, main_title_corr, align=0.5, /normal, $
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
