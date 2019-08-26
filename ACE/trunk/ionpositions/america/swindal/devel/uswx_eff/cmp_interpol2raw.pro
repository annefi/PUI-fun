;; Compare interpolated efficiencies to raw efficiencies to test
;; interpolation.
;; JR, 24Jun2004

;; ---------------------------------------------------------------------------
;; Set up
;; ---------------------------------------------------------------------------
thisprog = 'cmp_interpol2raw'

;; ---------------------------------------------------------------------------
;; ===> configure <===
;; ---------------------------------------------------------------------------
;; ULYSSES efficiency directory
UXDIR = '/shrg1/ulysses/calib/effic'

;; interpolated eff. file
IEFF_FILE = "uswx_eff.dat"

;; set up plot layout
npp = 12

;; postscript file
PSFILE = 'cmp_interpol2eff.ps'
;; ---------------------------------------------------------------------------
;; Read in interpolated efficiencies and set up
;; ---------------------------------------------------------------------------
restore, file='uswx_eff_template.save'
ieffd = read_ascii(IEFF_FILE, template=template)

;; build unique ion list
ions = ieffd.ion[uniq(ieffd.ion)]
num_ions = n_elements(ions)

;; build unique element list
for i_ion=0,num_ions-1 do begin
  ion_parse, ion=ions[i_ion], elem=elem
  if (i_ion eq 0) then elements = [elem] $
    else elements = [elements,elem]
endfor 
elements = elements[uniq(elements)]
num_elements = n_elements(elements)

;; restore raw eff. template
restore, file='plot_uswx_eff_template.save'
;; ---------------------------------------------------------------------------
;; set up postscript file
;; ---------------------------------------------------------------------------
psplt, file=PSFILE, /color
loadct, 34
fix_ct_ends

;; ---------------------------------------------------------------------------
;; Over plot raw and interpolated eff. for each ion
;; ---------------------------------------------------------------------------

;for i_elem=0,0 do begin
for i_elem=0,num_elements-1 do begin
  !p.multi = [0,3,3]
  
  ;; Read in UX data for ion
  if (strlen(elements[i_elem]) eq 1) then spacer = '_' else spacer = ''
  uxfile = strupcase(elements[i_elem]) + spacer + '_MOD.DAT'
  uxd = read_ascii(UXDIR + '/' + uxfile, template=template)

  ;; select matching ions
;  i_ions_of_elem = where( (strpos(ions, elements[i_elem]) ge 0),$
  i_ions_of_elem = $
    where( stregex(ions,'[0-9]{0,2}'+elements[i_elem]+'[0-9]{0,2}\+',$
                   /fold) ge 0, num_ions_of_elem)
  if (num_ions_of_elem le 0) then goto, next_elem
  ions_of_elem = ions[i_ions_of_elem]

  for i_ioe=0,num_ions_of_elem-1 do begin
    i_ion = where(ieffd.ion eq ions_of_elem[i_ioe], nwhere)
    if (num_ions_of_elem le 0) then goto, next_ion

    print, 'plotting '+ions_of_elem[i_ioe]

    subtitle = uxfile + ' ' + ions_of_elem[i_ioe]
    eff = uxd.prob1*uxd.prob2*uxd.prob3
    plot, uxd.etot, eff, xtitle='Etot (keV)',ytitle='Effic.',$
      subtitle=subtitle, xrange=[0.,1000.]
    
    oplot, ieffd.etot[i_ion], ieffd.eff[i_ion],color=254
    ; linestyle=2

    str = 'Comparision of raw (black) to interpolated (red) eff. from USWX'
    xyouts, .01,.99, str, /normal

    tagplot, line1=PSFILE

    next_ion:
  endfor

  next_elem:
endfor

;; ---------------------------------------------------------------------------
;; clean up and get out
;; ---------------------------------------------------------------------------
done:

ficlose

end
