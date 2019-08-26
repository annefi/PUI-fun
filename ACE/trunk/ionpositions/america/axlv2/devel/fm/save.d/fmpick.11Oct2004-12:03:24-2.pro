; Filename: fmpick.pro
;
; Description:
;   Fit ACE/SWICS forward model parameter to data from
;   graphically-picked points.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: fmpick.pro,v 1.1 2004/10/04 16:25:42 jraines Exp $
;
; Major Modification History
;   13Jan2003   jmr   Adapted from fmpick_cfe.pro, cvs rev 1.1
;
; Arguments
; I/O   argument         description
; ---   --------         -----------
; I     fmcfile          forward model comparison (fmcomp) file
;                        produced by axlv2 or axfmtweak
; I     etsfile          E-T slice file produced by axlv2
; I     tag              text tag for plots
; I/O   fmcdata          data structure, read from fmcfile, returned
;                        to caller.  Data taken from here instead of
;                        fmcfile with '/noread' option.
; I/O   ets              data structure, read from etsfile, returned
;                        to caller.  Data taken from here instead of
;                        etsfile with '/noread' option.
; I     noread           take data from ets and fmc passed in.  Do not
;                        read from files.
; I     zrange           zrange for FM comparison E-T slice
; I     steps            array of steps from which to pick peaks
; I/O   [peakdata]       structure of picked/read peaks (opt.)
; I     [nodef]          use previous ion/step pair definitions (from peakdata)
; I     [nopick]         use previous pick data (from peakdata)
;                        instead of interactive picking
; I     [nofit]          pick peaks only, no fitting
; I     element          element to be picked
; I     mass             mass of element in amu
; I     pav              post-accel. voltage in kV, 
;                        must be 21.2998 or 24.8682.
pro fmpick, fmcfile=fmcfile, etsfile=etsfile, tag=tag, fmcdata=fmc, $
            etsdata=ets, noread=noread, zrange=zrange, steps=steps, $
            peakdata=p, nopick=nopick, element=element, subsec=subsec, $
            nofit=nofit, mass=mass, pav=pav, noadj=noadj, nodef=nodef,$
            H=H

thisprog = 'fmpick'

;; ===========================> configuration <================================
tof_window = 2     ; number of channels on either side of center to include

;; ============================================================================

;; ----------------------------------------------------------------------------
;; ---------------------------- set up  --------------------------------------
;; ---------------------------------------------------------------------------
;; define step range if not specified on command line
if (not keyword_set(steps) or not keyword_set(element)) then begin
  message, /info, 'steps and element keywords required; See code for syntax.'
endif
if (not keyword_set(fmcfile)) then begin
  fmcfile='axlv2_fmcomp.dat'
endif
if (not keyword_set(etsfile)) then begin
  etsfile='axlv2_et_slices.dat'
endif
if (not keyword_set(H)) then begin
;; ===> initial values
H = make_array(6+1,/float,value=-1.0)
H[1] = 1520000.0
H[3] = 6.15
H[4] = 0.73
endif

;; set up color table and colors
loadct, 34                        ;34 is Rainbow
fix_ct_ends, black=0, white=255   ;insert bw
black = 0                         ;define color mnemonic
white = 1

;; read FM center data
;; note: must read or alter to pass fmc_ions and eoqtable in/out of
;; this routine
read_fmc, file=fmcfile, fmc=fmc, ions=fmc_ions, eqtab=eoqtable

if (not keyword_set(noread)) then begin
  ;; read in ET array
  read_ets, file=etsfile, ets=ets
endif

; store number of fmc_ions
nfmc_ions = n_elements(fmc_ions)

;; define an array of fmc structures to use with individual steps
fmcstep = replicate( fmc[0], nfmc_ions)

;; ---------------------------------------------------------------------------
;; -------------------------- manually adjust TOF ----------------------------
;; ---------------------------------------------------------------------------
if (not keyword_set(noadj)) then begin
  ;; set up postscript file
  psfile = thisprog + '_tofadj.ps'
  psplt, file=psfile, /color

  xtitle = 'TOF_CH'
  ytitle = 'ESD_CH'

  ;; ----------manually adjust TOF----------
  h1 = 1358009.1
  step = 12
  format = '("Manually adjusting TOF via H1 parameter for ",A," (",F6.2,")")'
  print, format=format, element, mass
  h1str = string(format='("H1 = ",F12.2)',H[1])
  print, 'Current values: ' + h1str

  ;; find fmc for this element
  i_elem = where( (strpos(fmc.ion, element) ge 0 and fmc.step eq step), $
                  ni_elem)
  if (ni_elem le 0) then begin
    print, thisprog+' -E- no data for '+element
    goto, exit
  endif


  ;; plot centers on slices from selected steps
  plot_ets, etslice=ets[step-2], fmcstep=fmc[i_elem], $
    tag=h1str, zrange=zrange,$
    subsec=subsec,plotCenters=[1,0], xrange=[200,500],yrange=[0,300]
  tagplot, line1=thisprog+'.pro', line2=psfile

  fmc_adj = fmc
  while (h1 gt 0.0) do begin
    read, "Enter new H1 value (-1.0 to quit): ", H[1]
    h1str = string(format='("H1 = ",F12.2)',H[1])

    ;; adjust
    for i=0,n_elements(i_elem)-1 do begin
      ion_parse, ion=fmc[i_elem[i]].ion, state=q
      fm = xfm(eoq=fmc[i_elem[i]].eoq,pav=pav,mas=mass,crg=q,H1=H[1])
      fmc_adj[i_elem[i]].tof    = fm[0]
      fmc_adj[i_elem[i]].tofsig = fm[1]
      fmc_adj[i_elem[i]].esd    = fm[2]
      fmc_adj[i_elem[i]].esdsig = fm[3]
    endfor 

    ;; plot centers on slices from selected steps
    plot_ets, etslice=ets[step-2], fmcstep=fmc[i_elem], $
      pccstep=fmc_adj[i_elem], $
      tag=h1str, zrange=zrange,$
      subsec=subsec,plotCenters=[1,1], xrange=[200,500],yrange=[0,300]
    tagplot, line1=thisprog+'.pro', line2=psfile

  endwhile 

  ficlose
endif

;; ---------------------------------------------------------------------------
;; -------------------------- define peaks -----------------------------------
;; ---------------------------------------------------------------------------
if (not (keyword_set(nodef) or keyword_set(nopick)) ) then begin
  ;; init graphics window
  window, title=thisprog, xsize=1000,ysize=800

  ;; Set up peak-pick structure
  ;npeaks = n_elements(steps)


  p_element = { fmpick_picked_peak,$
      tof:       0.0, $
      esd:       0.0, $
      step:        0, $
      ion_name:   '', $
      element:    '', $
      charge:    0.0, $          
      label:      '', $
      subsec:      0  $
      }

  ;p = replicate(p_element, 1)

  ;; enter info now for easier picking
  step = 0
  npick = 0 
  while (step ne -1) do begin
    ptmp = p_element

    ptmp.element = element
    ptmp.subsec = subsec

    read, "Enter step (-1 to quit): ", step
    if (step eq -1) then goto, next_enter
    ptmp.step = step 

    ;; get ion name
    ion_name = ''
    i_elem_fmc_ions = where(strpos(fmc_ions, element) ge 0, nwhere)
    print, 'Choose among the following ions:', fmc_ions[i_elem_fmc_ions]
    prompt = 'Enter ion name: '
    read, format='(A)', prompt=prompt, ion_name
    ptmp.ion_name = ion_name
    ptmp.step = step
    ptmp.label = string(format='(A5,I2)',ptmp.ion_name,step)
    ion_parse, ion=ion_name, elem=elem, state=state
    ptmp.element = elem
    ptmp.charge = state

    ;; add to array of structures
    if (npick eq 0) then p = ptmp else p = [p,ptmp]

    npick += 1

    next_enter:
  endwhile

  ;; plot-pick loop
  print, thisprog + " -I- entering peak-picking loop for " + $
    string(format='(I3)', n_elements(p)) + " peaks"

endif

;; ---------------------------------------------------------------------------
;; ---------------------------- pick peaks -----------------------------------
;; ---------------------------------------------------------------------------
if (not keyword_set(nopick) ) then begin
  for npick=0,n_elements(p)-1 do begin

    ;; select fmc data for this step
    tmp_index = where(fmc[*].step eq p[npick].step, ntmp_index)
    if (ntmp_index gt 0) then fmcstep = fmc[tmp_index] else goto, next
  
    ;; plot (ets[0] is for step 2, etc.)
    plot_ets, etslice=ets[p[npick].step-2], fmcstep=fmcstep, tag="?", $
              zrange=zrange,$
              subsec=subsec, plotCenters=[1,0]

    ;; plot previously-picked peaks
    for i=0,npick-1 do begin
      xyouts,p[i].tof,p[i].esd,p[i].label,/data,color=black
    endfor


    ;; get peak pick
    print, format='("Click on desired location for ",A," at step ",I2)',$
           p[npick].ion_name,p[npick].step
    cursor,tofpick,esdpick,/data
 
    ;; store pick
    p[npick].tof = tofpick
    p[npick].esd = esdpick

    ;; plot just-picked peak
    xyouts,p[npick].tof, p[npick].esd, p[npick].label, /data,color=black

    next:
  endfor
endif                           ; if not nopick

;; ----------------------------------------------------------------------------
;; ---------------------------- do fitting ------------------------------------
;; ----------------------------------------------------------------------------
;; set up postscript file for results output
psfile = thisprog + '_fit.ps'
psplt, file=psfile, /color


if (not keyword_set(nofit)) then begin
  ;; ----------Fit TOF----------
  print, 'fmpick -I- fitting TOF...'

  ;; set up additional (fixed) parameters required by xfm that curvefit will not
  ;; allow to be passed
  common xfmparam, eoq_common, pav_common, mass_common
  eoq_common = eoqtable[p[*].step]
  pav_common = pav 
  mass_common = mass

  ;; initial value for fit parameter
  a = H[1]

; what was this?
;xfmtof_fit, p.charge, a, tof
;print, tof

  weights = make_array(n_elements(p.charge), /float, value=1.0)
  fit_tof = curvefit(p.charge, p.tof, weights, a, $
                     function_name='xfmtof_fit', /noderivative)

  ;; plot results
  plot, p.charge, p.tof, title='Compare TOF picked to fit',color=0,$
        xtitle='charge',ytitle='TOF', psym=4, subtitle='line is fit', thick=3.0
  oplot, p.charge, fit_tof, color=254, thick=3.0

  ;; update coef.
  H[1] = a[0]
  print, 'fmpick -I- TOF fit finished'
  print, format='("+ H1=",F12.2)',H[1]

  ;; ---------- Fit ESD ----------
  print, 'fmpick -I- fitting ESD...'
  ;; initialize to current values
  a = [H[1],H[3],H[4]]

  if (n_elements(p) le n_elements(a)) then begin
    print, 'fmpick -F- must have more points than parameters for curve fit'
    print, format='("+ num. points =",I2,", num. params =", I2)',$
           n_elements(p), n_elements(a)
    goto, exit
  endif

  ;; make Etilde array for indep. variable in H3/4 fit
  etil = make_array(n_elements(p.esd), /float, value=-1.0)
  for i=0,n_elements(p.esd)-1 do begin
    xfm_results = xfm(eoq=eoq_common[i], pav=pav_common, mas=mass_common,$
                      crg=p[i].charge, $
                      H3=a[0],H4=a[1],etil=etil_i)
    etil[i] = etil_i
  endfor

  ;; calculate ESD for points before fitting
  xfmesd_fit, p.charge, a, esd
  ;; linear fit
;  weights = make_array(n_elements(etil), /float, value=1.0)
  a = linfit(etil, p.esd, yfit=fit_esd)


  ;; fit using xfm -- UN-NEEDED AND DNW
;;  weights = make_array(n_elements(etil), /float, value=1.0)
;;  fit_esd = curvefit(etil, p.esd, weights, a, status=status, $
;;                     function_name='xfmesd_fit', /noderivative)

  ;; plot results
  status = 0
  plot, etil, p.esd, psym=4, xtitle='Etilde',ytitle='ESD', thick=3.0,$
        subtitle='fit is line'
  if (status eq 0) then oplot, etil, fit_esd, color=254 $
  else begin
    oplot, etil, p.esd
    xyouts, .5, .5, align=.5, "Etilde/ESD curve fit failed",/normal,$
            size=2.0
  endelse



  ;; update coef.
  print, format='("H1 before ESD fit:",F12.2)', H[1]
  ;H[1] = a[0]
  ;H[3] = a[1]
  ;H[4] = a[2]
  H[3] = a[0]
  H[4] = a[1]
  print, format='("H1 after ESD fit:",F12.2)', H[1]

  ;; what is this?
  ;xfmesd_fit, p.charge, a, esd
  ;oplot, etil, esd, psym=4, color=127, thick=5.0

  print, 'fmpick -I- ESD fit finished'

endif
;; ----------------------------------------------------------------------------
;; ---------------------------- plot FM comparison ----------------------------
;; ----------------------------------------------------------------------------
for ip=0,n_elements(p)-1 do begin

  ;; ---------- Adj FM ----------
  fmc_adj = fmc

  ;; find fmc for this element at this step
  i_elem = where( (strpos(fmc.ion, element) ge 0 and fmc.step eq p[ip].step), $
                  ni_elem)
  if (ni_elem le 0) then begin
    print, format='(A," -E- no data for ",A," at step",I2 )',$
           thisprog,element,p[ip].step
    goto, next_compare
  endif

  for i=0,n_elements(i_elem)-1 do begin
    ion_parse, ion=fmc[i_elem[i]].ion, state=q
    fm = xfm(eoq=fmc[i_elem[i]].eoq,pav=pav,mas=mass,crg=q,H1=H[1],H3=H[3],H4=H[4])
    fmc_adj[i_elem[i]].tof    = fm[0]
    fmc_adj[i_elem[i]].tofsig = fm[1]
    fmc_adj[i_elem[i]].esd    = fm[2]
    fmc_adj[i_elem[i]].esdsig = fm[3]
  endfor 

  ;; find fmc for ALL elements at this step
  i_step = where( fmc.step eq p[ip].step, nwhere)
  if (nwhere le 0) then begin
    print, format='(A," -E- no data at step",I2 )',$
           thisprog,p[ip].step
    goto, next_compare
  endif

  ;; ---------- Plot old and new ----------
  ;; plot centers on slices from selected steps
  hstr = string(format='("H1 = ",F12.2," H3 = ",F6.2," H4 = ",F6.2)',$
                H[1],H[3],H[4])
;  plot_ets, etslice=ets[p[ip].step-2], fmcstep=fmc[i_elem], $
;            pccstep=fmc_adj[i_elem], $
  plot_ets, etslice=ets[p[ip].step-2], fmcstep=fmc[i_step], $
            pccstep=fmc_adj[i_step], $
             tag=hstr, zrange=zrange,$
            subsec=p[ip].subsec,plotCenters=[1,1];, $
            ;, xrange=[200,500],yrange=[0,300]
  tagplot, line1=thisprog+'.pro', line2=psfile

  next_compare:
endfor
;; ----------------------------------------------------------------------------
;; --------------------------- Clean up and get out ---------------------------
;; ----------------------------------------------------------------------------
exit:
ficlose

print, 'fmpick -I- dumping H parameters:'
for ih=0,n_elements(H)-1 do begin
  print, format='("+ H[",I1,"]=",F12.2)',ih,H[ih]
endfor
print, '+ see ',psfile,' for more details'

save, file=thisprog+'_peakdata.save', p

stop
return
end
