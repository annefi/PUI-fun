; Filename: axlv2_rates.pro
;
; Description:
;   Read and Plot ACE/SWICS rates for each time period from
;   text file generated by axlv2.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: axlv2_rates.pro,v 1.13 2005/03/17 19:14:19 jraines Exp $
;
; Major Modification History
;   10Jul2003   jmr   Adapted from rp_axlv2_br.pro
;   22Aug2003   jmr   Added rate_type option
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
; I   [doyfrs]    specify particular day of year fractions
;                   read, e.g. doyfrs=[100.55, 100.75]
; I   [/noread]    use data passed in via data keyword rather than
; I   [ytitle]    specify ytitle for color_plot
; O   [eqfile]     save E/q table array (eqtab) in specified file.
; I   [/counts]    plot counts column instead of rates
; I   [rate_type]  specify rate type for plot title, e.g. 'Prob.'
; I   [tag]        specify an additional string for subtitle

pro axlv2_rates, file=datfile, data=d, noread=noread, doyfrs=doyfrs, $
                 ytitle=ytitle, eqfile=eqfile, counts=counts, $
                 rate_type=rate_type, tag=tag, zrange=zrange

;; set up
thisprog = 'axlv2_rates'
old_p = !p  ; save incoming plot settings for restore at end

;; ----------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------
;; define pattern for elements which should appear on a separate plot
;; note: there are too many elements to have all on one (y axis label limits)
SUBSEC_PATTERN = 'Fe[0-9]{1,2}'

!p.charsize = 0.7
!p.charthick = 3.0
!p.thick = 5.0

!x.style = 1
!x.thick = 3.0

!y.style = 1
!y.thick = 3.0

;; ----------------------------------------------------------------------
;; Read data, setup uniq. arrays and setup PS file
;; ----------------------------------------------------------------------


;; read data
if (not keyword_set(noread)) then begin
  restore, file='axlv2_rates_template.save'
  d = read_ascii(datfile, template=template, header=h)
endif
;; put in quality?

;; set up matrix rate array

;; make uniq arrays
if (not keyword_set(doyfrs)) then begin
  doyfrs = d.doyfr[uniq(d.doyfr, sort(d.doyfr))]
endif
ndoyfrs = n_elements(doyfrs)

eqtab = d.eoq[uniq(d.eoq, sort(d.eoq))]
eqtab = reverse(eqtab)          ; max(step) should be min(eqtab)
nsteps = n_elements(eqtab)

if (keyword_set(eqfile)) then save, file=eqfile, eqtab

;; set up PS file
file_parse, file=datfile, dir=dir, base=base, ext=ext
;psfile = dir + '/' + base + '.ps'
psfile = base + '.ps'
psplt, file=psfile, /color

;; removed !p.multi stuff; set outside of program
;; Some useful settings:
;; 9 plots per page: !p.multi = [0,3,3]
;; 4 plots per page: !p.multi = [0,1,2]
;; 1 plot per page:  !p.multi = 0

;; set up color table
loadct, 33
;; 33 -- blue background
;; 27 -- white background

black = 0
white = 1
fix_ct_ends, black=black, white=white

;; ----------------------------------------------------------------------
;; do rate plots for each doyfr
;; ----------------------------------------------------------------------
for ndoyfr=0,ndoyfrs-1 do begin
  doyfr = doyfrs[ndoyfr]
  print, thisprog + ' -I- working on doyfr = ' + string(format='(F11.2)',doyfr)

  for nsubsec=0,1 do begin
    
    ;; ------------------------------------------------------------
    ;; select subsection (all ions will not fit on one page)
    ;; ------------------------------------------------------------
    if (nsubsec eq 0) then begin
      i_subsec = where( stregex(d.ion, SUBSEC_PATTERN, /bool) and $
                        d.doyfr eq doyfrs[ndoyfr], ni_subsec)
    endif else begin
      i_subsec = where( (not stregex(d.ion, SUBSEC_PATTERN, /bool)) and $
                        d.doyfr eq doyfrs[ndoyfr], ni_subsec)
    endelse

    if (ni_subsec le 0) then begin
      print, thisprog+' -E- no data for subsec '+$
             string(format='(I1)',nsubsec)+$
             ' at doyfr = '+doyfr_str
      goto, next_subsec
    endif
 
    ;; grab list from first edb and first  beginning to keep in file order
    i_uniq_ions = where(d.edb[i_subsec] eq 2 and $
                        d.doyfr[i_subsec] eq doyfrs[ndoyfr], nwhere)
    ;; workaround duplicate last timestep problem (skip duplicate)
    if (nwhere gt nsteps) then i_uniq_ions = i_uniq_ions[0:nsteps-1]
    subsec_ions = d.ion[i_subsec]
    ions = subsec_ions[i_uniq_ions]
    nions = n_elements(ions)
 
    ;; ------------------------------------------------------------
    ;; form matrix
    ;; ------------------------------------------------------------

    ;; dimension main rate array 
    data = fltarr(nsteps,nions)

    ;; loop over ions
    for nion=0,nions-1 do begin
      ;;;print, thisprog + ' -I- working on ion = ' + ions[nion]

      ;; put data into 2D array for plotting by color plot
      i_rate = where( (d.doyfr[i_subsec] eq doyfr) and $
                      (d.ion[i_subsec] eq ions[nion]), ni_rate)

      ;; workaround duplicate last timestep problem (skip duplicate)
      if (ni_rate gt nsteps) then i_rate = i_rate[0:nsteps-1]

      if (ni_rate gt 0) then begin
        if (keyword_set(counts)) then begin
          subsec_data = d.counts[i_subsec]
        endif else begin
          subsec_data = d.rate[i_subsec]
        endelse
        data[*, nion] = subsec_data[i_rate]
      endif

    endfor

    ;; ------------------------------------------------------------
    ;; plot data
    ;; ------------------------------------------------------------
    if (not keyword_set(rate_type)) then rate_type=''

    if (keyword_set(counts)) then begin
      title = 'ACE/SWICS Level II ' + rate_type + ' Counts'
    endif else begin
      title = 'ACE/SWICS Level II ' + rate_type + ' Rates'
    endelse
    subtitle = 'doyfr = ' + string(format='(F11.2)',doyfr)
    if (keyword_set(tag)) then subtitle = subtitle + ', ' + tag

    ;;x = eqtab
    ;;xtitle = 'E/q (keV/e)'
    x = indgen(nsteps) + 2
    xtitle = 'Deflection Voltage Step'
    y = indgen(nions)
    if (not keyword_set(ytitle)) then ytitle = 'Ion'
    ytickname = ions
    ytickv    = indgen(nions)
    yticks    = nions
                     ;vvvv +1E-5 because 0s do not work for log scaled plots
    color_plot, data+1.0e-5,  x, y, xtitle=xtitle,ytitle=ytitle,  $  
                /fill, title=title , /logsc, subtitle=subtitle, $
                zmin_color=white,$
                ytickname=ytickname, ytickv=ytickv, yticks=yticks, $
                zrange=zrange

    tagplot, line1=thisprog, /dir

    next_subsec:
  endfor
endfor

;; ----------------------------------------------------------------------
;; write out EDB of maximum counts for each ion IN ONE SUBSECTION ONLY
;; ----------------------------------------------------------------------
ratefile = base + '_maxedb.dat'
print, thisprog + $
  ' -I- Writing out EDB of maximum counts for each ion to '+ratefile
get_lun, lun
openw, lun, ratefile
printf, lun, '# EDB of maximum counts for each ion produced by axlv2_rates.pro'
printf, lun, '# Data file: ' + datfile
printf, lun, '# nion ion maxedb maxeoq'

for nion=0,nions-1 do begin
  i_nion = where(d.ion eq ions[nion], ni_nion)
  if (ni_nion gt 0) then begin
    maxval = max(d.rate[i_nion], imaxval)
    maxedb = d.edb[imaxval]
    eoqmax  = d.eoq[imaxval]

    printf, lun, format='(I2.2,3x,A7,3x,I2.2,3x,E9.2)', $
      nion, ions[nion], maxedb, eoqmax
  endif
endfor 
close, lun
free_lun, lun

;; ----------------------------------------------------------------------
;; clean up and get out
;; ----------------------------------------------------------------------
!p = old_p                      ; restore incoming plot settings
ficlose
return
end

