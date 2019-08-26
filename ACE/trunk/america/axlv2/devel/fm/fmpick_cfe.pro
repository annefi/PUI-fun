; Filename: fmpick_cfe.pro
;
; Description:
;   Fit ACE/SWICS forward model parameter CORRECTION to data from
;   graphically-picked points.  This version written to correct Fe
;   (hence '_cfe') positions.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: fmpick_cfe.pro,v 1.1 2004/10/04 16:25:42 jraines Exp $
;
; Major Modification History
;   25Nov2003   jmr   Adapted from fmpick.pro, cvs rev 1.7
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
; I     zrange
; I     steps            array of steps from which to pick peaks
; I     [h1]             H1 const. in use for this run (opt.)
; I/O   [peakdata]       structure of picked/read peaks (opt.)
; I     [refit]          use previous pick data (from peakdata)
;                        instead of interactive picking
pro fmpick_cfe, fmcfile=fmcfile, etsfile=etsfile, tag=tag, fmcdata=fmc, $
            etsdata=ets, noread=noread, zrange=zrange, steps=steps, $
            peakdata=p, refit=refit, element=element, subsec=subsec

thisprog = 'fmpick_cfe'

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

if (not keyword_set(refit)) then begin
  ;; init graphics window
  window, title='fmpick_cfe', xsize=1000,ysize=800

  ;; Set up peak-pick structure
  npeaks = n_elements(steps)


  p_element = { p3,$
      tof:       0.0, $
      esd:       0.0, $
      step:        0, $
      label:      '', $
      element:    '', $
      subsec:      0  $
      }

  p = replicate(p_element, npeaks)

  ;; plot-pick loop
  print, "fmpick_cfe -I- entering peak-picking loop for " + $
    string(format='(I3)', npeaks) + " peaks"
  step = 0
  for npick=0,npeaks-1 do begin
    p[npick].element = element
    p[npick].subsec = subsec

    ;  read, "Enter step: ", step
    ;  if (step eq -1.0) then goto, next
    step = steps[npick]

    ;; select fmc data for this step
    tmp_index = where(fmc[*].step eq step, ntmp_index)
    if (ntmp_index gt 0) then fmcstep = fmc[tmp_index] else goto, next
  
    ;; plot (ets[0] is for step 2, etc.)
    plot_ets, etslice=ets[step-2], fmcstep=fmcstep, tag="?", zrange=zrange,$
      subsec=subsec, plotCenters=[1,0]

    ;; plot previously-picked peaks
    for i=0,npick-1 do begin
      xyouts,p[i].tof,p[i].esd,p[i].label,/data,color=black
    endfor

    ;; get peak pick
    print, "Click on desired location..."
    cursor,tofpick,esdpick,/data
 
    ;; store items in structure
    p[npick].tof = tofpick
    p[npick].esd = esdpick
    p[npick].step = step
    p[npick].label = string(format='("p",I1,"s",I2.2)',npick,step)

    ;; plot just-picked peak
    xyouts,p[npick].tof, p[npick].esd, p[npick].label, /data,color=black

    next:
  endfor
endif                           ; if not refit

;; ----------------------------------------------------------------------------
;; ---------------------------- do fitting ------------------------------------
;; ----------------------------------------------------------------------------
;; set up postscript file
psfile = 'fmpick_cfe.ps'
psplt, file=psfile, /color

xtitle = 'TOF_CH'
ytitle = 'ESD_CH'

;; ----------Fit picked points----------
title = 'Picked Peaks'

;; fit[] are coef.
degree = 3
a = make_array(degree)
;a = [1.0, exp(1.0), -1.0e-2, 250.0]
a = [1.0,1.0,1.0]
;y =  alog(p.esd)
y =  p.esd
fit_p = comfit( p.tof, y, a, $
                yfit=yfit_p, /logsquare, sigma=sigma)
;fit_p = svdfit( p.tof, p.esd, degree, $
;                 chisq=chisq,yfit=yfit_p, function_name='mod_exp')
;                 chisq=chisq,yfit=yfit_p, /legendre)

;; plot picked points
subtitle = tag + ', coef:'
;for i=0,degree do begin ; -1 for 0 start, +1 for degree+1 coef.
for i=0,degree-1 do begin ; -1 for 0 start, +1 for degree+1 coef.
  subtitle = subtitle + " " + string(format='(g8.2)',fit_p[i])
endfor
;subtitle = subtitle + ",  sigma = " + string(format='(g8.2)',sigma)
plot, p.tof, y, psym=5,$
  xtitle=xtitle,ytitle=xtitle,$
  title=title,$
  subtitle=subtitle

;; plot fit points
oplot, p.tof, yfit_p, color=254

;oplot, p.tof, logsquare(p.tof, fit_p), color=200

tagplot, line1='fmpick_cfe.pro', line2=psfile

;; plot labels
;; format is x,y,label
;; note:  +N.N offsets label from symbol for readability
xyouts, p.tof, p.esd+.4, p.label,$
  size=0.5,charthick=1.0

;x = p.tof
;plot, x, mod_exp(x, a), title='mod_exp(x,a)', psym=5

;; ----------Plot FM centers----------
title = 'Forward Model Centers'

i_elem = where( (strpos(fmc.ion, element) ge 0) and $
                (fmc.step eq p[0].step), ni_elem)
if (ni_elem le 0) then begin
  print, thisprog+' -E- no data for '+element
  goto, exit
endif

;oplot, fmc[i_elem].tof, fmc[i_elem].esd, psym=4
;fit = svdfit( fmc[i_elem].tof, fmc[i_elem].esd, degree, $
;                 chisq=chisq,yfit=yfit, /legendre)
degree = 3
a = [1.0, exp(1.0), -1.0e-2,250.0]
fit_fm = comfit( fmc[i_elem].tof, fmc[i_elem].esd, a, $
                yfit=yfit_fm, /gompertz, sigma=sigma)
;degree = 3
;a = [1.0,1.0,1.0]
;fit_fm = comfit( fmc[i_elem].tof, fmc[i_elem].esd, a, $
;                yfit=yfit_fm, /logsquare, sigma=sigma)

;; plot picked points
subtitle = tag + ', coef:'
;for i=0,degree do begin ; -1 for 0 start, +1 for degree+1 coef.
for i=0,degree-1 do begin ; -1 for 0 start, +1 for degree+1 coef.
  subtitle = subtitle + " " + string(format='(g8.2)',fit_fm[i])
endfor
;subtitle = subtitle + ",  sigma = " + string(format='(g8.2)',sigma)
plot, fmc[i_elem].tof, fmc[i_elem].esd, psym=5,$
  xtitle=xtitle,ytitle=ytitle,$
  title=title,$
  subtitle=subtitle

;; plot fit points
oplot, fmc[i_elem].tof, yfit_fm, color=254

;oplot, fmc[i_elem].tof, a[0]*a[1]^(a[2]*(fmc[i_elem].tof)-250.0)+a[3], psym=2
tagplot, line1='fmpick_cfe.pro', line2=psfile

;; plot labels
;; format is x,y,label
;; note:  +N.N offsets label from symbol for readability
xyouts, fmc[i_elem].tof, fmc[i_elem].esd+.4, fmc[i_elem].ion,$
  size=0.5,charthick=1.0

;; ----------Plot old and new----------
title = 'FM and New (red) Positions'

c_tof = make_array(n_elements(fmc[i_elem].tof), /float)
c_esd = make_array(n_elements(fmc[i_elem].tof), /float)
fmtof = fmc[i_elem].tof
ptof  = p[*].tof
j = 0
for i=0,n_elements(fmc[i_elem].tof)-1 do begin
  if (i+6 lt 16) then begin
    c_tof[i] = fmtof[i]
    c_esd[i] = yfit_fm[i]
  endif else begin
    c_tof[i] = ptof[j]
    c_esd[i] = yfit_p[j]
    j = j + 1
  endelse
endfor

plot, fmc[i_elem].tof, yfit_fm, title=title, xtitle=xtitle, ytitle=ytitle
oplot, c_tof, c_esd, color=254
oplot, c_tof, c_esd, color=254, psym=4

;; ----------Plot old E-T slices as reminder----------
step = steps[uniq(steps)]
subsec = 3
;; original fm
plot_ets, etslice=ets[step-2], fmcstep=fmc[i_elem], tag="?", zrange=zrange,$
  subsec=subsec, plotCenters=[1,0], xrange=[200,500],yrange=[0,300]

;; ----------Plot new data over E-T slice----------
;; this section just to verify that d_ arrays are working correctly

if (0) then begin
  c_fmc = fmc[i_elem]
  for i=0,n_elements(c_fmc)-1 do begin
    c_fmc[i].tof = c_tof[i]
    c_fmc[i].esd = c_esd[i]
  endfor

;; plot (ets[0] is for step 2, etc.)
  ;; corrected fm
  plot_ets, etslice=ets[step-2], fmcstep=c_fmc, tag="?", zrange=zrange,$
    subsec=subsec,plotCenters=[1,0], xrange=[200,500],yrange=[0,300]
  tagplot, line1='fmpick_cfe.pro', line2=psfile
endif 

;; ----------Determine correction to original FM----------
d_tof = make_array(n_elements(fmc[i_elem].tof), /float)
d_esd = make_array(n_elements(fmc[i_elem].tof), /float)

fmtof = fmc[i_elem].tof
fmesd = fmc[i_elem].esd
for i=0,n_elements(fmc[i_elem].tof)-1 do begin
    d_tof[i] = fmtof[i] - c_tof[i]
    d_esd[i] = fmesd[i] - c_esd[i]
endfor


c2_fmc = fmc[i_elem]
for i=0,n_elements(c2_fmc)-1 do begin
  c2_fmc[i].tof = fmtof[i] - d_tof[i]
  c2_fmc[i].esd = fmesd[i] - d_esd[i]
endfor

;; ----------Plot E-T slices with corrected fm----------
for step=2,11 do begin
  plot_ets, etslice=ets[step-2], fmcstep=fmc[i_elem], pccstep=c2_fmc, tag="?", zrange=zrange,$
    subsec=subsec,plotCenters=[1,1], xrange=[200,500],yrange=[0,300]
  tagplot, line1='fmpick_cfe.pro', line2=psfile
endfor

;; ----------write out correction for axlv2----------
get_lun, lun
openw, lun, 'fmpick_cfe.dat'

printf, lun,'# Forward Model corrections for Fe (subtract from FM)'
printf, lun,'# Produced by '+thisprog+'.pro on '+systime()

hformat = '("# ",A5,x,A6.6,x,A6.6)'
dformat = '("  ",A5,x,F6.2,x,F6.2)'

printf, lun, format=hformat, 'ion','tofcor','esdcor'
for i=0,n_elements(d_tof)-1 do begin
  printf, lun, format=dformat, $
    (fmc[i_elem].ion)[i], d_tof[i], d_esd[i]
endfor

close, lun
free_lun, lun
;; ----------Clean up and get out----------
exit:
ficlose

save, file='fmpick_cfe_peakdata.save', p

stop
return
end
