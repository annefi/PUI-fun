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
; $Id: fmpick.pro,v 1.3 2004/10/19 13:47:29 jraines Exp $
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
; I     element          element to be picked
; I     mass             mass of element in amu
; I     pav              post-accel. voltage in kV, 
;                        must be 21.2998 or 24.8682.
; I     subsec           subsection of slice to plot; see plot_ets for
;                        details
; I     [tag]              text tag for plots
; I/O   [fmcdata]        data structure, read from fmcfile, returned
;                        to caller.  Data taken from here instead of
;                        fmcfile with '/noread' option.
; I/O   [ets]            data structure, read from etsfile, returned
;                        to caller.  Data taken from here instead of
;                        etsfile with '/noread' option.
; I     [noread]         take data from ets and fmc passed in.  Do not
;                        read from files.
; I     [zrange]           zrange for FM comparison E-T slice
; I/O   [peakdata]       structure of picked/read peaks (opt.)
; I     [nodef]          use previous ion/step pair definitions (from
;                        peakdata)
; I     [nopick]         do not do interactive peak picking
;
;                        *NOTE*:  If '/nopick' is given without
;                        '/nodef', user is prompted for full peak info
;                        in definition.  If both '/nodef' and '/nopick
;                        are given, previous def. and locations are
;                        taken from peakdata object.
;
; I     [noadj]          do not do manual TOF adjustment (default)
;                        Manual TOF adjustment DNW.
; I     [nofit]          do not do TOFCH and ESDCH fitting of peaks
pro fmpick, fmcfile=fmcfile, etsfile=etsfile, tag=tag, fmcdata=fmc, $
            etsdata=ets, noread=noread, zrange=zrange,  $
            peakdata=p, nopick=nopick, element=element, subsec=subsec, $
            nofit=nofit, mass=mass, pav=pav, noadj=noadj, nodef=nodef,$
            H=H

thisprog = 'fmpick'

;; ===========================> configuration <================================

;; default is no manual TOF adjusting
noadj = 1
;; ============================================================================

;; ----------------------------------------------------------------------------
;; ---------------------------- set up  --------------------------------------
;; ---------------------------------------------------------------------------
;; define step range if not specified on command line
if (not keyword_set(element) or not keyword_set(mass)) then begin
  message, /info, 'element, mass and pav keywords required; See code for syntax.'
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
  H[1] = 1000000.0
  H[3] = 0.00
  H[4] = 1.00
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
;; -------------------------- define peaks -----------------------------------
;; ---------------------------------------------------------------------------
if (not (keyword_set(nodef) ) ) then begin

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

  ;; enter info now for easier picking
  step = 0
  npick = 0 
  print, 'Begin interactive point definition for '+element+':'
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

    value = 0
    if (keyword_set(nopick)) then begin
      read, format='(I4)', prompt='Enter tofch (0..1023): ', value
      ptmp.tof = value
      read, format='(I3)', prompt='Enter esdch (0..255): ', value
      ptmp.esd = value

    endif

    ;; add to array of structures
    if (npick eq 0) then p = ptmp else p = [p,ptmp]
    npick += 1

    next_enter:
  endwhile

endif

;; ---------------------------------------------------------------------------
;; ---------------------------- pick peaks -----------------------------------
;; ---------------------------------------------------------------------------
if (not keyword_set(nopick) ) then begin
  ;; plot-pick loop
  print, thisprog + " -I- entering peak-picking loop for " + $
    string(format='(I3)', n_elements(p)) + " peaks"

  for npick=0,n_elements(p)-1 do begin

    ;; init graphics window
    window, title=thisprog, xsize=1000,ysize=800

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

;; ---------------------------------------------------------------------------
;; -------------------------- manually adjust TOF ----------------------------
;; ---------------------------------------------------------------------------
;; WARNING:  This section is out of date with the rest of the code.
;; It must be modified to loop over picked peaks.  It very well may be
;; un-necessary now anyway.
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
  tagplot, line1=thisprog+'.pro',/dir

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
    tagplot, line1=thisprog+'.pro', /dir

  endwhile 

  ficlose
endif
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

  weights = make_array(n_elements(p.charge), /float, value=1.0)
  fit_tof = curvefit(p.charge, p.tof, weights, a, $
                     function_name='xfmtof_fit', /noderivative)

  ;; update coef.
  H[1] = a[0]

  ;; plot results
  h1_str = string(format='("H1=",F12.2)',H[1])
  plot, p.charge, p.tof, title='Comparison of (q,TOF) picked to fit',color=0,$
        xtitle='charge',ytitle='TOF', psym=4, thick=3.0,$
        subtitle=h1_str+', symbols are picked points', xstyle=18,ystyle=18
  oplot, p.charge, fit_tof, color=254, thick=3.0
  tagplot, line1=thisprog+'.pro', /dir

  ;; move on
  print, 'fmpick -I- TOF fit finished'
  print, '+ '+h1_str

  ;; ---------- Fit ESD ----------
  print, 'fmpick -I- fitting ESD...'

  if (n_elements(p) lt 2) then begin
    print, 'fmpick -F- must have at least two points for linear fit'
    goto, exit
  endif

  ;; make Etilde array for indep. variable in H3/4 fit
  etil = make_array(n_elements(p.esd), /float, value=-1.0)
  for i=0,n_elements(p.esd)-1 do begin
    xfm_results = xfm(eoq=eoq_common[i], pav=pav_common, mas=mass_common,$
                      crg=p[i].charge, $
                      H3=H[3],H4=H[4],etil=etil_i)
    etil[i] = etil_i
  endfor

  ;; linear fit
  a = linfit(etil, p.esd, yfit=fit_esd, prob=model_prob, chisq=chisq)

  ;; update coef.
  H[3] = a[0]
  H[4] = a[1]

  ;; plot results
  h34_str = string(format='("H3=",F6.2," H4=",F6.2)',H[3],H[4])
  plot, etil, p.esd, title='Comparison of (Etilde,ESD) picked to fit', $
        psym=4, xtitle='Etilde',ytitle='ESD', thick=3.0,xstyle=18,ystyle=18,$
        subtitle=h34_str+', symbols are picked points'
  tagplot, line1=thisprog+'.pro', /dir
  if (model_prob gt .1) then oplot, etil, fit_esd, color=254 $
  else begin
    oplot, etil, p.esd
    xyouts, .5, .5, align=.5, "Etilde/ESD linear fit parameters are suspect",$
            /normal,size=2.0
  endelse

  print, 'fmpick -I- ESD fit finished'

endif
;; ----------------------------------------------------------------------------
;; ---------------------------- plot FM comparison ----------------------------
;; ----------------------------------------------------------------------------
for ip=0,n_elements(p)-1 do begin

  ;; ---------- Adj FM ----------
  fmc_adj = fmc

  ;; find fmc for this element at this step
;  i_elem = where( (strpos(fmc.ion, element) ge 0 and fmc.step eq p[ip].step), $
  i_elem = where( (stregex(fmc.ion, element+'[0-90-9\+]') ge 0 $
                   and fmc.step eq p[ip].step), $
                  ni_elem)
  if (ni_elem le 0) then begin
    print, format='(A," -E- no data for ",A," at step ",I2 )',$
           thisprog,element,p[ip].step
    goto, next_compare
  endif

  ;; shift centers not adjusted to an inconspicuous regin
  for i=0,n_elements(fmc_adj[*].tof)-1 do begin
    fmc_adj[i].tof    = 460.0
    fmc_adj[i].tofsig = 1.0
    fmc_adj[i].esd    = 15.0
    fmc_adj[i].esdsig = 1.0
  endfor

  ;; assign 
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
    print, format='(A," -E- no data at step ",I2 )',$
           thisprog,p[ip].step
    goto, next_compare
  endif

  ;; ---------- Plot old and new ----------
  ;; plot centers on slices from selected steps
  hstr = string(format='("H1 = ",F12.2," H3 = ",F6.2," H4 = ",F6.2)',$
                H[1],H[3],H[4])
  plot_ets, etslice=ets[p[ip].step-2], fmcstep=fmc[i_step], $
            pccstep=fmc_adj[i_step], $
             tag=hstr, zrange=zrange,$
            subsec=p[ip].subsec,plotCenters=[1,1];, $
            ;, xrange=[200,500],yrange=[0,300]
  tagplot, line1=thisprog+'.pro', /dir

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
