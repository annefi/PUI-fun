; Filename: axlv2_nvt_barq.pro
;
; Description:
;   Plot ACE/SWICS level 2 charge state relative abundances.  This is
;   a self-contained diagnostic figure not suitable for publication directly.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   10Nov2003   jmr   Adapted from axlv2_nvt.pro
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; I   element     element to plot, e.g., element='C'
; O   data        nvt data structure, e.g., data=d001
; [I] error_level specify error level below which data is thrown out
pro axlv2_nvt_barq, file=file, data=d, element=element, tag=tag,$
                    error_level=error_level

;; init variables
thisprog = 'axlv2_nvt_barq'

;; ----------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------
PlotsPerPage = !p.multi[1]*!p.multi[2]

;; values 
DEFAULT_ERROR_LEVEL = .5
;; ----------------------------------------------------------------------
;; set up
;; ----------------------------------------------------------------------
;; set defaults
if (not keyword_set(element)) then begin
  element='Fe'
endif
if (not keyword_set(tag)) then tag=''
if (not keyword_set(error_level)) then error_level = DEFAULT_ERROR_LEVEL

;; read and filter
tplatefile = 'axlv2_nvt_template.save'
restore, file=tplatefile
d = read_ascii(file, template=template, comment='#')
filter_nvt_by_qual, nvtdata=d, error_level=error_level

;; set up plot file
file_parse, file=file, base=base, split_base=sb
psfile=base+'_barq_'+element+'_'+tag+'.ps'
psplt, file=psfile, /color

;; extract year string from parts of filename
tmp = split_ydoy(sb[2], /strings)
year_str = tmp[0]

;; convert doy fraction to hms
hms = doyfr2hms(d.doyfr[0])  ; get one of the struct. ret'd by function
time = replicate(hms, n_elements(d.doyfr)) ; replicate
timestr = make_array(n_elements(d.doyfr), /string)
for i=0L,n_elements(d.doyfr)-1 do begin

  time[i] = doyfr2hms(d.doyfr[i])

  ;; build up time string for labels
  timestr[i] = time[i].dhms

  ;;print , 'timestr[',i,']=', timestr[i]
endfor

;; get short list of doyfr
doyfrs = d.doyfr(uniq(d.doyfr))

;; ----------------------------------------------------------------------
;; loop over time periods
;; ----------------------------------------------------------------------
for idoyfr=0,n_elements(doyfrs)-1 do begin
  doyfr_str = string(format='(F6.2)',doyfrs[idoyfr])
  title = 'DOY = '+year_str+' '+doyfr_str
  print, 'ion = ', element, ' title=',title

  ;; calculate He2+ speed for title
  i_he = where (d.ion eq 'He2+' and $
                d.doyfr eq doyfrs[idoyfr], ni_he)
  if (ni_he lt 0) then begin
    print, thisprog+' -E- no data for He2+ at doyfr = '+$
      doyfr_str
    goto, next
  endif
  i_he = i_he[0]                ; workaround for duplicate last timestep
  vhe = d.v[i_he]
  title = title + ', vHe2+ = ' + string(format='(F8.2)',vhe)
  
  ;; select ions of specified element
  i_elem = where( (strpos(d.ion, element) ge 0) and $
                d.doyfr eq doyfrs[idoyfr] , ni_elem)
  if (ni_elem le 0) then begin
    print, thisprog+' -E- no data for '+element+' at doyfr = '+$
      doyfr_str
    goto, next
  endif

  ;; create bar names
  ions = d.ion[i_elem]
  barnames = make_array(n_elements(ions) , /string)
  for nion=0,n_elements(ions)-1 do begin
    ion_parse, ion=ions[nion], state=state, /strings
    barnames[nion] = state
  endfor
  ;;barnames = string(format='(I2)',indgen(24-6+1)+6)

  ;; calculate relative abundances
  tot_ab = total( d.n[i_elem], /nan )
  if (tot_ab gt 0. and n_elements(i_elem) gt 1) then begin
      rel_ab = d.n[i_elem]/tot_ab 
  endif else begin
      print, thisprog+' -E- insufficient data for '+element+' at doyfr = '+$
             doyfr_str
      goto, next
  endelse

  ;; do plot
  bar_plot, rel_ab, title=title, barnames=barnames, $
    xtitle='Charge State of '+element, ytitle='Relative Abundance'

  error_level_str = string(format='(F6.2)',ERROR_LEVEL)
  ;; do tag only for first plot on every page
  if ( ((idoyfr+1) mod PlotsPerPage) eq 1 ) then $
    tagplot, line1='error_level='+error_level_str, /dir

  next:

endfor

;; ----------------------------------------------------------------------
;; done
;; ----------------------------------------------------------------------
ficlose
return
end

