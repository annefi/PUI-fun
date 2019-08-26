; Filename: 
;
; Description:
;   
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;     Nov2003   jmr   initial coding
;   08Nov2004   jmr   Added fit function display
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
pro axlv2_distfunc, file=datfile, data=d, noread=noread, tag=tag, ions=ions

;; set up
thisprog = 'axlv2_distfunc'

;; read data
if (not keyword_set(noread)) then begin
  restore, file='axlv2_distfunc_template.save'
  d = read_ascii(datfile, template=template, header=h)
endif

;; set up matrix rate array

;; ----------------------------------------------------------------------
;; make uniq arrays
;; ----------------------------------------------------------------------
if (not keyword_set(doyfrs)) then begin
  doyfrs = d.doyfr[uniq(d.doyfr, sort(d.doyfr))]
endif
ndoyfrs = n_elements(doyfrs)

if (not keyword_set(ions)) then begin
  ;; grab list from first edb and first  beginning to keep in file order
  ions = d.ion[where(d.edb eq 2 and d.doyfr eq doyfrs[0])]
endif
nions = n_elements(ions)

eqtab = d.eoq[uniq(d.eoq, sort(d.eoq))]
eqtab = reverse(eqtab)          ; max(step) should be min(eqtab)
nsteps = n_elements(eqtab)

;;----------------------------------------------------------------------
;; set up plotting stuff
;;----------------------------------------------------------------------
;; set up PS file
file_parse, file=datfile, dir=dir, base=base, ext=ext
;psfile = dir + '/' + base + '.ps'
if (keyword_set(tag)) then begin
    sep='_' 
endif else begin 
    sep=''
    tag=''
endelse
psfile = base + sep + tag + '.ps'
psplt, file=psfile, /color
npp = !p.multi[1]*!p.multi[2]   ; number of plots per page

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

nplot = 1

;;----------------------------------------------------------------------
;; 
;;----------------------------------------------------------------------

;; load generic ions for mass and charge values later
sw_ions = loadIons_sw()


;;----------------------------------------------------------------------
;; Plot DF versus EDB and velocity
;;----------------------------------------------------------------------
for nion=0,nions-1 do begin
  ;; force a new page at start of ion
  !p.multi[0] = 0

  print, thisprog + ' -I- working on ion = ' + ions[nion]

  ;; convert E/q scale to velocity for this ion
  ion_parse, ion=ions[nion], elem=elem, state=charge, iso=iso
  this_ion = where(sw_ions.element eq elem, nwhere)
  mass = sw_ions[this_ion[0]].mass
  if (iso ne -1.0) then mass = iso  ;; fixes problem in elem. matching above
  v_edb=438.*sqrt(d.eoq*charge/mass)

  ;; loop over days
  for ndoyfr=0,ndoyfrs-1 do begin

    doyfr = doyfrs[ndoyfr]
    doyfr_str = string(format='(F11.2)',doyfr)
    ;print, thisprog + ' -I- working on doyfr = ' + doyfr_str

    ;; find ion
    i_df = where( (d.doyfr eq doyfr) and (d.ion eq ions[nion]), ni_df)
    if (ni_df le 0) then begin
      print, thisprog+' -I- no data for '+ions[nion]+' at '+doyfr_str
      goto,next
    endif
    
    if (0) then begin
      ;; plot df vs. edb
      plot, d.edb[i_df], d.df[i_df],$
            xtitle = 'Deflection Voltage Step',ytitle='A[edb] for '+ions[nion],$
            subtitle='doy = '+doyfr_str
      nplot = nplot + 1
      
      if (fix(nplot)/fix(npp) eq float(nplot)/float(npp)) then begin
        tagplot, line1=tag ,line2='University of Michigan'
        nplot = 1               ; reset
      endif
    endif

    ;; plot versus velocity
    plot, v_edb[i_df], d.df[i_df],$
      xtitle = 'Velocity (km/s)',ytitle='A[edb] for '+ions[nion],$
      subtitle='doy = '+doyfr_str
    nplot = nplot + 1

    oplot, v_edb[i_df], d.fit_df[i_df], color=254
;    plot, v_edb[i_df], d.fit_df[i_df], color=254, $
;      xtitle = 'Velocity (km/s)',ytitle='FIT A[edb] for '+ions[nion],$
;      subtitle='doy = '+doyfr_str
;    nplot = nplot + 1

    if (fix(nplot)/fix(npp) eq float(nplot)/float(npp)) then begin
      tagplot, line1=tag ,line2='University of Michigan'
      nplot = 1                 ; reset
    endif

    next:
  endfor
endfor

ficlose
return
end
