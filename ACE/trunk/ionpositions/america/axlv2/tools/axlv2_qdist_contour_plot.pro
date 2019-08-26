; Filename: axlv2_qdist_contour_plot.pro
;
; Description:
;   Creates a charge distribution versus time contour plot.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: axlv2_qdist_contour_plot.pro,v 1.1 2005/03/14 15:28:18 jraines Exp $
;
; Major Modification History
;   14Jan2005   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   data        nvt data structure
; [I] position    position for plot
; [I] logsc       make z-axis log scaled (note: this is rarely an improvement)
;                 viewing
; [I] tag         text tag for output filename (no spaces!)
; I   year        year of data (string; for plot labels)

pro axlv2_qdist_contour_plot, data=d, element=element, tag=tag,$
  position=position, logsc=logsc, year=year, title=title

;; init variables
thisprog = 'axlv2_nvt_qdist_contour'

;; ===> configure <===

;; set defaults
if (not keyword_set(element)) then begin
  element='Fe'
endif
if (not keyword_set(tag)) then tag=''

;; get short list of doyfr
doyfrs = d.doyfr(uniq(d.doyfr))

;; determine number of ions for this element
elem_pattern = element + '[0-9]{1,2}\+'
i_elem = where( (stregex(d.ion, elem_pattern) ge 0) and $
                d.doyfr eq doyfrs[0], nwhere)
if (nwhere lt 0) then begin
  print, thisprog+' -E- no data for '+element+' at doyfr = '+$
         doyfr_str
  goto, next
endif
ions = d.ion[i_elem]
num_ions = n_elements(ions)

;; set up charge/time matrix
qt_matrix = make_array(n_elements(doyfrs), num_ions, /float)

;; loop over time periods
for idoyfr=0,n_elements(doyfrs)-1 do begin
  doyfr_str = string(format='(F6.2)',doyfrs[idoyfr])
  print, 'working on element = ', element, ' doyfr =',doyfr_str

  ;; select ions of specified element
  i_elem = where( (stregex(d.ion, elem_pattern ) ge 0) and $
                  d.doyfr eq doyfrs[idoyfr], nwhere)


;  i_elem = where( (strpos(d.ion, element) ge 0) and $
;                  d.doyfr eq doyfrs[idoyfr], nwhere)
  if (nwhere lt 0) then begin
    print, thisprog+' -E- no data for '+element+' at doyfr = '+$
           doyfr_str
    goto, next
  endif

  ;; work around for weird duplicate timestep at end
  i_elem = i_elem[0:num_ions-1]

  ;; create state labels
  ions = d.ion[i_elem]

  ;; calculate relative abundances
  tot_ab = total( d.n[i_elem] , /nan)
  if (tot_ab > 0.) then rel_ab = d.n[i_elem]/tot_ab else rel_ab = 0.

  print, 'ions = ', ions
  print, 'total = ', tot_ab
  print, 'rel_ab=',rel_ab

  ;qt_matrix[*, idoyfr] = rel_ab[*]
  qt_matrix[idoyfr,*] = rel_ab[*]

  next:

endfor

;; zero small values
i_small = where(qt_matrix le 0.01, nwhere)
;if (nwhere ge 1) then qt_matrix[i_small] = 0.0

x = doyfrs
y = indgen(num_ions)
if (not keyword_set(ytitle)) then ytitle = 'Ion'
ytickname = ions
ytickv    = indgen(num_ions)
yticks    = num_ions

color_plot, qt_matrix,  x, y, xtitle=xtitle,ytitle=ytitle,  $  
            /fill, title=title , subtitle=subtitle, zmin_color=1,$
            ytickname=ytickname, ytickv=ytickv, yticks=yticks, zrange=zrange,$
            position=position, logsc=logsc

tagplot, line1='University of Michigan', /dir

return
end
