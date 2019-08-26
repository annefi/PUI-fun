; Filename: plot_ets.pro
;
; Description:
;   Plot and Energy-Tof slice matrix with forward model parameters.
;
; Author: Jim Raines (jmr)
;
; Method:
;
; Arguments:
;   etslice -- one smread2 structure which contains et slice matrix and
;              titles.
;   fmcstep -- an array of fmc structures at one particular E/q step
;   pcccstep -- an array of fmc structures at one particular E/q step
;   tag -- text tag for plot subtitle
;   zrange -- range to plot in Z; IDL does this automatically if
;             omitted
;   plotCenters -- 2 element array, [forward_model, prob_center], which serves
;             as a flag for plotting respective centers:  zero => do not plot
;             corresponding center data.
;   subsec -- subsection to plot; 1 -> all, 2 -> non-iron, 3 -> iron
;             Note: internally these subsections are 0-2.  But,
;             subsec=0 passed in causes keyword_set(subsec) to be
;             false -- even though it was set (to zero) in the call
;   [xrange] -- (opt) specifies xrange and skips auto-ranging based on
;               subsection.  MUST SPECIFY YRANGE AS WELL.
;   [yrange] --  (opt) specifies yrange and skips auto-ranging based on
;               subsection.  MUST SPECIFY XRANGE AS WELL.
;
; Revision controlled by CVS:
; $Id: plot_ets.pro,v 1.3 2004/01/02 19:42:15 jraines Exp $
;
; Major Modification History
;   15Nov2002   jmr   Adapted from fmcomp.pro
;   21Nov2003   jmr   Split off pcc from fmc; removed pcc from
;                     sub-section calc.
;   25Nov2003   jmr   protected where statements against 0 found with if blocks
;

pro plot_ets, etslice=etslice, fmcstep=fmcstep, pccstep=pccstep, tag=tag, $
              zrange=zrange, subsec=subsec, plotCenters=plotCenters, $
              xrange=xrange, yrange=yrange

;; ----------------------------------------------------------------------------
;; --------------------------------- setup ------------------------------------
;; ----------------------------------------------------------------------------
if (not keyword_set(plotCenters)) then plotCenters = [1,1]

; set up color table and colors
;loadct, 33                      ;33 is Blue-Red 2
;loadct, 27                      ;27 is Eos B
loadct, 34                      ;34 is Rainbow
;fix_ct_ends, white=255
fix_ct_ends                     ;make ends of color table black and white, resp
black = 0                       ;define color mnemonic
white = 1
xharecolor = black              ; set color for crosshares and rel. text
;window, title='fmpick', xsize=1000,ysize=800

;; define subsections -- DEFAULT VALUES ONLY; REDEFINED LATER
if (not keyword_set(xrange) and not keyword_set(yrange)) then begin
  xranges = intarr(2,3)
  yranges = intarr(2,3)

  ;; --------------------------------------------------------------------------
  ;; ------------------- define bounds for subsections ------------------------
  ;; --------------------------------------------------------------------------
  ;; for reference sake, these ranges work ok
  ;; full, non-iron, iron, respectively
  ;; xranges = [[0,1023],[300,425],[400,700]]
  ;; yranges = [[0,255],[20,100],[20,80]] 

  ;; whole thing
  ;; -----------
  xranges[*,0] = [0,1023]
  yranges[*,0] = [0,255]

  ;; non-iron heavies (nfeh) (bo H/He either)
  ;; ----------------------------------------
  ;; find non-Fe indices
  nfehidx = where((stregex( fmcstep[*].ion, 'Fe', /boolean) ne 1) and $
                  (stregex( fmcstep[*].ion, 'H', /boolean) ne 1) , count)
  if (count gt 0) then begin
    ;; find min tof of FM
    ;; note: sigmas are not needed here now, but left for future
    ;; expansion to separate sigmas for FM and prob. centers
    ;;
    ;; note2:  Prob. centers removed from subsection range calculations
    ;; because they were problematic.  To put them back in, follow the
    ;; example below:
    ;;
    ;;  min_tof = min([min(fmcstep[nfehidx].tof    - fmcstep[nfehidx].tofsig), $
    ;;               min(pcccstep[nfehidx].tof - pccstep[nfehidx].tofsig)])
    min_tof = min(fmcstep[nfehidx].tof - fmcstep[nfehidx].tofsig)

    ;; find max tof of FM and prob. centers
    max_tof = max(fmcstep[nfehidx].tof + fmcstep[nfehidx].tofsig)

    ;; set xrange
    xranges[*,1] = [min_tof, max_tof]

    ;; repeat for yrange (esd)
    min_esd = min(fmcstep[nfehidx].esd - fmcstep[nfehidx].esdsig)
    max_esd = max(fmcstep[nfehidx].esd + fmcstep[nfehidx].esdsig)
    yranges[*,1] = [min_esd, max_esd]
  endif else begin
    ;; no indices found set to full range 
    xranges[*,1] = xranges[*,0]
    yranges[*,1] = yranges[*,0]
  endelse

  ;; iron (fe)
  ;; ---------
  ;; find Fe indices
  feidx = where(stregex( fmcstep[*].ion, 'Fe', /boolean) eq 1, count)
  if (count gt 0) then begin
    ;; find min tof of FM and prob. centers
    min_tof = min(fmcstep[feidx].tof - fmcstep[feidx].tofsig)
    ;; find max tof of FM and prob. centers
    max_tof = max(fmcstep[feidx].tof + fmcstep[feidx].tofsig)
    ;; set xrange
    xranges[*,2] = [min_tof, max_tof]

    ;; repeat for yrange (esd)
    min_esd = min(fmcstep[feidx].esd - fmcstep[feidx].esdsig)
    max_esd = max(fmcstep[feidx].esd + fmcstep[feidx].esdsig)
    yranges[*,2] = [min_esd, max_esd]

  endif else begin
    ;; no indices found set to full range 
    xranges[*,2] = xranges[*,0]
    yranges[*,2] = yranges[*,0]
  endelse

  ;; set up number of subsections
  ;; ----------------------------
  if (keyword_set(subsec)) then begin
    nsub_min = subsec-1
    nsub_max = subsec-1 
  endif else begin
    nsub_min = 0
    nsub_max = n_elements(xranges[0,*])-1
  endelse

endif else begin
  xranges = intarr(2,1)
  yranges = intarr(2,1)

  xranges[0] = xrange
  yranges[0] = yrange

  nsub_min = 0
  nsub_max = 0
endelse

;; bounds checking/correction
;; --------------------------------------------------
;; sets range that are out of bounds to min/max in bounds
;; --- min
iout = where(xranges lt 0,niout)
if (niout gt 0) then xranges[iout] = 0
iout = where(yranges lt 0,niout)
if (niout gt 0) then yranges[iout] = 0
;; --- max
iout = where(xranges gt 1023,niout)
if (niout gt 0) then xranges[iout] = 1023
iout = where(yranges gt 255,niout)
if (niout gt 0) then yranges[iout] = 255

;; ----------------------------------------------------------------------------
;; ---------------------- plot each subsection --------------------------------
;; ----------------------------------------------------------------------------
for nsub=nsub_min,nsub_max do begin

  ;; make subsection matrices
  xrange = xranges[*,nsub]
  yrange = yranges[*,nsub]

  submat = etslice.mat[xrange(0):xrange(1),yrange(0):yrange(1)]

  ;; plot ET matrix
  subtitle = tag + ' step = ' + string(format='(I2)',fmcstep[0].step)$
    + ', E/q(keV/e) = ' + string(format='(F6.2)',fmcstep[0].eoq)

  if (not keyword_set(zrange)) then begin
    ;; allow IDL to find best z-scale for each step and subsection
    color_plot, submat,  xrange, xtitle=etslice.xtitle,subtitle=subtitle,$
      yrange, ytitle=etslice.ytitle, title=etslice.title , $
      /logsc, $  
      zmin_color=white, $
;      zcolors=zcolors, $
      /fill
  endif else begin
    ;; force and specify common z-scale for all steps and subsections
    ;; zrange=[.5e-5,.1e-3] works in general
    color_plot, submat,  xrange, xtitle=etslice.xtitle,subtitle=subtitle,$
      yrange, ytitle=etslice.ytitle, title=etslice.title , /logsc, $  
      zrange=zrange,  $
      zmin_color=white, $;zcolors=8, $
      /fill
  endelse

  ;; -------------------------------
  ;; --- Plot Centers and Ranges ---
  ;; -------------------------------

  for nion=0,n_elements(fmcstep)-1 do begin

;    format = '("At E/q=",F6.2,", ion ",A0," is centered at ' $
;      + '(tof,esd)=(",F6.2,",",f6.2,")")'
;    print,format=format,fmcstep[nion].eoq,$
;      fmcstep[nion].ion, fmcstep[nion].tof, fmcstep[nion].esd

    ;; -----------------------------
    ;; Plot forward model parameters
    ;; -----------------------------
    ;; decide if FM center is in plot range
    if (plotCenters[0] eq 1) then begin
      if ( ( (fmcstep[nion].tof ge xrange(0)) and $
             (fmcstep[nion].tof le xrange(1)) ) and $
           ( (fmcstep[nion].esd ge yrange(0)) and $
             (fmcstep[nion].esd le yrange(1)) ) ) $
        then inRange = 1 else inRange = 0
    
      if (inRange eq 1) then begin
        ;; draw cross-hairs on centers
        ;; ---------------------------
        ;; note: call is plots, [x0,x1], [y0,y1], color=somecolor,...
        ;;       where x is tof and y is esd

        ;; tof
        plots, [fmcstep[nion].tof - fmcstep[nion].tofsig,$ ; x
                fmcstep[nion].tof + fmcstep[nion].tofsig ],$
          [fmcstep[nion].esd,fmcstep[nion].esd],$ ; y
          color=xharecolor

        ;; esd
        plots,[fmcstep[nion].tof,fmcstep[nion].tof],$ ; x
          [fmcstep[nion].esd - fmcstep[nion].esdsig,$ ; y
           fmcstep[nion].esd + fmcstep[nion].esdsig],$
          color=xharecolor

        ;; label centers with ion names
        xyouts, fmcstep[nion].tof + fmcstep[nion].tofsig, fmcstep[nion].esd,$
          fmcstep[nion].ion, size=0.5,$
          charthick=1.5,color=xharecolor
      endif
    endif

    ;; -------------------------
    ;; Plot probabilitic centers
    ;; -------------------------
    ;; decide if probabilistic center is in plot range (if so directed)
    if (plotCenters[1] eq 1) then begin
      if ( ( (pccstep[nion].tof ge xrange(0)) and $
             (pccstep[nion].tof le xrange(1)) ) and $
           ( (pccstep[nion].esd ge yrange(0)) and $
             (pccstep[nion].esd le yrange(1)) ) ) $
        then inRange = 1 else inRange = 0
    
      if (inRange eq 1 and plotCenters[1] eq 1) then begin
        ;; draw cross-hairs on probabilistic centers
        ;; -----------------------------------------
        ;; tof
        plots, [pccstep[nion].tof - pccstep[nion].tofsig,$ ; x
                pccstep[nion].tof + pccstep[nion].tofsig ],$
          [pccstep[nion].esd,pccstep[nion].esd],$ ; y
          color=xharecolor, linestyle=1

        ;; esd
        plots,[pccstep[nion].tof,pccstep[nion].tof],$ ; x
          [pccstep[nion].esd - pccstep[nion].esdsig,$ ; y
           pccstep[nion].esd + pccstep[nion].esdsig],$
          color=xharecolor, linestyle=1

        ;; label probabilistic centers with ion name
        xyouts, pccstep[nion].tof + pccstep[nion].tofsig,$
          pccstep[nion].esd,"p"+pccstep[nion].ion, size=0.5,$
          charthick=1.5,color=xharecolor

      endif
    endif
    
  endfor                        ;loop over ions
endfor                          ;loop over subsections

return
end
