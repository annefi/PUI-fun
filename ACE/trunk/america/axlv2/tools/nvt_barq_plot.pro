; Filename: nvt_barq_plot.pro
;
; Description:
;   Plot ACE/SWICS level 2 charge state distributions from data in
;   memory and to open device (psfile).
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
;   $Id: nvt_barq_plot.pro,v 1.1 2005/03/14 16:53:40 jraines Exp $
;
; Major Modification History
;   10Nov2003   jmr   Adapted from axlv2_nvt.pro
;   14Mar2005   jmr   Renamed from axlv2_nvt_barq.pro when merging
;                     some publication routines (from Halloween storm)
;                     into axlv2/tools
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; O   data        structure containing data
; I   element     element to select for plotting
; I   [tag]       text tag for plot
; I   [doyfrs]    array of selected doy fractions to plot
; I   [hespeed]   add He2+ speed to title
; I   [no_title]  do not print plot title
pro nvt_barq_plot, data=d, element=element, tag=tag, $
                    doyfrs=doyfrs, hespeed=hespeed,$
                    bar_name_freq=bar_name_freq, no_title=no_title,$
                    positions=positions, nplot=nplot, yrange=yrange,$
                    no_position=no_position

;; init variables
thisprog = 'nvt_barq_plot'

;; ===> configure <===

if (not keyword_set(tag)) then tag='' else tag = '_'+tag

if (not keyword_set(bar_name_freq)) then bar_name_freq=0

;; get short list of doyfr if not specifiec
if (not keyword_set(doyfrs)) then begin
  doyfrs = d.doyfr(uniq(d.doyfr))
endif
ndoyfrs = n_elements(doyfrs)

;; convert doy fraction to hms
hms = doyfr2hms(doyfrs[0])  ; get one of the struct. ret'd by function
time = replicate(hms, ndoyfrs) ; replicate
timestr = make_array(ndoyfrs, /string)
for i=0,ndoyfrs-1 do begin

  time[i] = doyfr2hms(doyfrs[i])

  ;; build up time string for labels
  timestr[i] = time[i].dhms
endfor

;; define proper pattern for matching element
elem_pattern = element + '[0-9]{1,2}\+'

;; loop over time periods
for idoyfr=0,ndoyfrs-1 do begin
  doyfr_str = timestr[idoyfr]
  ;title = doyfr_str
  if (not keyword_set(no_title)) then begin
    title = string(format='(F6.2)',doyfrs[idoyfr])
  endif else title = ''

  ;; calculate He2+ speed for title
  i_he = where (d.ion eq 'He2+' and $
                d.doyfr eq doyfrs[idoyfr], ni_he)
  if (ni_he le 0) then begin
    print, thisprog+' -E- no data for He2+ at doyfr = '+$
      doyfr_str
    vhe = -1.0
  endif else begin
    vhe = d.v[i_he]
  endelse
 
  if (keyword_set(hespeed)) then begin
    title = title + ', vHe2+ = ' + string(format='(F8.2)',vhe)
  endif
  
  ;; select ions of specified element
  i_elem = where( (stregex(d.ion, elem_pattern ) ge 0) and $
; right qdists but floating number of states
;                d.doyfr eq doyfrs[idoyfr] and $
;                  d.n gt 0., ni_elem)
                d.doyfr eq doyfrs[idoyfr], ni_elem)
 if (ni_elem le 0) then begin
    print, thisprog+' -E- no data for '+element+' at doyfr = '+$
      doyfr_str
    goto, next
  endif

  ;; create bar names
  ions = d.ion[i_elem]
  barnames = make_array(n_elements(ions) , /string)
  bar_name_freq=2
  if (n_elements(ions) ge 4) then bar_name_freq=2
  if (n_elements(ions) ge 5) then bar_name_freq=3
  if (n_elements(ions) gt 15) then bar_name_freq=5
  for nion=0,n_elements(ions)-1 do begin
    ion_parse, ion=ions[nion], state=state, /strings

    barnames[nion] = state

    ;; null some of the bar names for readability
    if (bar_name_freq gt 0) then begin
      if (fix(state)/fix(bar_name_freq) ne $
          float(state)/float(bar_name_freq)) then begin
        barnames[nion] = ' '
      endif
    endif

  endfor
  ;;barnames = string(format='(I2)',indgen(24-6+1)+6)

  ;; calculate relative abundances
  tot_ab = total( d.n[i_elem] )
  rel_ab = d.n[i_elem]/tot_ab

  ;; set ytitle
  if (idoyfr eq 0) then begin
    ytitle=element
    !y.ticks=3
    !y.tickname=[' ',strarr(3)]
  endif else begin 
    ytitle=''
    !y.ticks=1
    !y.tickname=strarr(3) + ' '
  endelse

  ;!y.tickformat='(F4.2)'
  !y.range=yrange
  !p.charsize=1.7

  ;; do plot
  nplot = nplot + 1

  if (not keyword_set(no_position)) then begin
    bar_plot_pos, rel_ab, title=title, barnames=barnames, $
      ytitle=ytitle, position=positions[nplot,*]
  endif else begin
    bar_plot_pos, rel_ab, title=title, barnames=barnames,ytitle=ytitle
  endelse

  next:

endfor

;; put things back
!y.tickname=''
!y.ticks=0

return
end

