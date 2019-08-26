; Filename: axlv2_deliv_ctemp.pro
;
; Description:
;   Calculate and plot average charge from axlv2_deliv_*qdist*.dat files.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   This program overplots points in red which have the quality flag
;   set.  NOTE:  It relies on this flag only being 0 or 1.
;   
; Revision controlled by CVS:
; $Id: axlv2_deliv_ctemp.pro,v 1.2 2005/05/07 04:15:19 jraines Exp $
;
; Major Modification History
;   25Apr2005   jmr       generalized for production use
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
; [I] yranges           optionally specify yranges for all elements
; [I] doyfrs            optionally specify doyfs to plot from all
;                       files
; [I] atomic_numbers    optionally specify atomic number for each
;                       member of specified elements array 
; [O] ctemp             optionally return ctemp array to caller in
;                       this variable
; [I] noread            do not read/calc ctemp, use data passed in
; [I] save_ctemp        optionally specify that the ctemp array should
;                       be saved along with doyfrs array
; [I] itmax             optionally specify the max. number of
;                       iterations by curvefit (default is 20)
;


pro axlv2_deliv_ctemp, file_doyfr_range_str=file_doyfr_range_str,$
  tag=tag, doyfr_ranges=doyfr_ranges, elements=elements, doyfrs=doyfrs, $
  atomic_numbers=atomic_numbers, ctemp=ctemp, noread=noread, $
  save_ctemp=save_ctemp, itmax=itmax, yranges=yranges

thisprog = 'axlv2_deliv_ctemp'

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
YLOG = 1

;; error point color
ERR_COLOR = 254

;; minimum relative abundance to send to qdist_ctemp curve fitter
RA_FLOOR = 1.e-10

;; defaults
DEF_ELEMENTS = ['Mg', 'Fe', 'Si', 'C', 'O', 'Ne']
DEF_YRANGES = [[1.e5,1.e7],[1.e5,1.e7],[1.e5,1.e7],[1.e5,1.e7],$
               [1.e5,1.e7],[1.e5,1.e7]]
DEF_ATOMIC_NUMBERS = [12., 26., 14., 6., 8., 10.]

main_title = 'ACE/SWICS Level II Deliv. Est. Coronal Temp.!C(v. 2, pre-release)'
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
!y.ticks = 2
!y.minor = 10
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
endif

;; choose default elements
if (not keyword_set(elements)) then begin
  elements = DEF_ELEMENTS
  yranges = DEF_YRANGES
  atomic_numbers = DEF_ATOMIC_NUMBERS
endif else begin
  if (not keyword_set(yranges) or not keyword_set(atomic_numbers)) then begin
    print, thisprog+' -F- must also specify yranges and atomic numbers when specifying elements'
    goto, exit_now
  endif
endelse

;; choose default elements
if (not keyword_set(atomic_numbers)) then begin
endif

;; ----------------------------------------------------------------------
;; read from spec. element files and calculate average charge
;; ----------------------------------------------------------------------
if (not keyword_set(noread)) then begin
  restore, file='axlv2_deliv_qdist_template.save'
  for nelem=0, n_elements(elements)-1 do begin
    file = base + '_' + elements[nelem] + '_qdist_' + $
           file_doyfr_range_str + '.dat'
    print, thisprog+' -I- estimating coronal temp. for '+elements[nelem]

    d = read_ascii(file, template=template, comment='#')

    ;; choose all doyfr values in file by default
    if (not keyword_set(doyfrs)) then begin
      doyfrs = d.doyfr[uniq(d.doyfr, sort(d.doyfr))]
    endif

    ;; set up array on first element only
    if (nelem eq 0) then ctemp = $
      make_array(n_elements(elements), n_elements(doyfrs), /float, value=0.0)

    ;; -------------------------------------------
    ;; estimate coronal temperature for all doyfrs
    ;; -------------------------------------------
    for ndoyfr=0, n_elements(doyfrs)-1 do begin
      doyfr = doyfrs[ndoyfr]
      doyfr_str = string(format='(F6.2)',doyfrs[ndoyfr])

      ;; choose current doyfr
      i_doyfr = where(d.doyfr eq doyfr, num_ions)
      if (num_ions lt 1) then begin
        print, thisprog+' -W- no data at doyfr = '+doyfr_str
        goto, next_doyfr
      endif

      ;; fill in relative abundances not present in data
      ;; note: mazzotta code returns abundance for states 0..z+ so we
      ;; need to fill in the ones not returned in axlv2
      relab = make_array(atomic_numbers[nelem]+1, /float, value=RA_FLOOR)
      relab[fix(d.chg[i_doyfr])] = d.rel_abun[i_doyfr]

      ;; clean up relative abundances so fitter does not go crazy
      i_bad = where(relab le RA_FLOOR, nwhere)
      if (nwhere gt 0) then relab[i_bad] = RA_FLOOR

      ;; fit coronal temperature
      ctemp[nelem,ndoyfr] = qdist_ctemp(z=atomic_numbers[nelem],$
                                        relab=relab, itmax=itmax)

      next_doyfr:
    endfor

  endfor

  if (keyword_set(save_ctemp)) then $
    save, file=base+'_ctemp_'+file_doyfr_range_str+'.save', $
          ctemp, doyfrs

endif
;; ----------------------------------------------------------------------
;; set up plots
;; ----------------------------------------------------------------------
;; set up postscript plot
psfile = base+'_ctemp_'+file_doyfr_range_str+tagsep+tag+'.ps'
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
;; loop over ranges and plot
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
    
    plot, doyfrs, ctemp[nelem,*], ytitle= 'T!I'+element+'!N', min=0., $
          xrange=range, yrange=yranges[*,nelem],$
          position=positions[nelem,*], ylog=YLOG

  endfor

;  xyouts, positions[PlotsPerPage-1,2]+.01, positions[PlotsPerPage-1,3],$
;          'High FIP', $
;          orien=270, align=0.0, /normal, size=0.9

;  xyouts, positions[0,2]+.01, positions[0,1],$
;          'Low FIP', $
;          orien=270, align=1.0, /normal, size=0.9

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
