; fmcexp.pro -- experimenting with plotting foward model data on E-T
;               contour plot
; JR, 27Feb2002
pro fmcexp, mat=mat, fmc=fmc

; restore EDB 41 data saved by fmcomp
restore, file='fmcexp.save'

psfile = 'fmcexp.ps'
psplt, file=psfile, /color
loadct, 33
;loadct, 27

;; plot ET matrix
color_plot, mat,  xrange, yrange, xtitle=xtitle,ytitle=ytitle,  $  
  /fill, title=title , subtitle=psfile, /logsc, zrange=[.5e-5,.5e-3]

;; --- FM stuff ---
;; ----------------

;; build unique list of ions
ions = fmc.ion(sort(fmc.ion))   ; sort ions
ions = ions(uniq(ions))         ; remove duplicates
nions = n_elements(ions)        ; store number of ions

for ion=0,nions-1 do begin
    i = where(fmc.ion eq ions(ion))
    eoq = fmc.eoq(i)
    tof = fmc.tof(i)
    tofsig = fmc.tofsig(i)
    esd = fmc.esd(i)
    esdsig = fmc.esdsig(i)

;  for nstep=2,59 do begin
  for nstep=41,41 do begin
    step = nstep - 2

    ;; select values for this iteration

    print,$
      format='("Ion ", A0," is centered at (tof,esd)=(",F6.2,",",f6.2,")" )',$
      ions(ion), tof(nstep), esd(nstep)

    ;; label centers with ion names
    xyouts, tof(nstep) + tofsig(nstep), esd(nstep), ions(ion), size=0.5,$
      charthick=1.0,color=2

    ;; draw cross-hairs on centers
    ;; tof
    plots, [[tof(nstep) - tofsig(nstep), esd(nstep)], $
      [tof(nstep) + tofsig(nstep),esd(nstep)]]

    ;; esd
    plots,[[tof(nstep),esd(nstep) - esdsig(nstep)],$
      [tof(nstep),esd(nstep) + esdsig(nstep)]]
 
  endfor
endfor

;; close and label PS plot file
hardcopy, label='from fmcexp.pro', file=psfile, printer='file'

return
end
