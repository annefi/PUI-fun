;; plot slices to identify peak in fmcomp plot

pin = !p
!p.charsize = 2.0
!p.multi = [0,3,3]

;; ===> configure <===
;; E/q steps for which to draw slices and ESD channel values at which
;; to draw lines for visual reference (both must be same length).
steps = [34,35,36,37,38,39]
lines = [66,63,63,60,47,43]

;steps = [34,35,36,37,38,39]
;lines = [66,63,63,60,60,59]

;; array of TOFCH at which to plot ESD curves
tofs = indgen(25) + 440

;; range of ESD channels to plot
esd_range = [1.,100.]

;; range for y axis; should be similar to zrange used in fmcomp
yrange = [1.e-7,1.e-5]          ; ~= zrange from fmcomp

;; number of plots per page
npp = 9

;; ===> end config. <===

;; get directory for tagplot label
spawn, 'pwd', dir
short_dir = strmid(dir,strlen(dir)-20,20)

psplt, file='fmpick_slices.ps', /color
loadct, 34
fix_ct_ends

for istep=0,n_elements(steps)-1 do begin
  !p.multi = [0,3,3]
  for itof=0,n_elements(tofs)-1 do begin
    tofch = tofs[itof]
    step  = steps[istep]
    label = string(format='("step = ",i2,", tofch = ", I3)',step,tofch)

    plot, ets[step].mat[tofch,*], xrange=esd_range,yrange=yrange,$
          subtitle=label, xtitle='ESD_CH', ytitle='counts'

    x = convert_coord( [lines[istep],0,0], /data,/to_normal)
    x = x[0]
    plots, [x,x] ,[0,1], /normal, color=254 

    if ( (itof mod npp) eq 0 ) then begin
      tagplot, line1='fmpick_slices.pro',line2=short_dir
    endif

  endfor
endfor

ficlose
!p = pin                        ; reset plotting structure
end
