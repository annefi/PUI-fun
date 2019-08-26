; Filename: plot_smmq.pro
;
; Description:
;   Plot one swindal mass-mass/charge matrix from input data and
;   centers.  Does not manipulate plot device, i.e. Postcript file
;   must be handled elsewhere.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: plot_smmq.pro,v 1.1 2004/06/14 19:38:36 jraines Exp $
;
; Major Modification History
;   19Mar2004   jmr   adapted from smmq.pro
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   smmq        smmq data structure, read by read_smmq.pro
; I   [centers]   ion center data, read by read_fmc.pro
; I   [ions]      list of unique ions in center data, also returned by
;                 read_fmc.pro
; I   [subtitle]  subtitle of plot
pro plot_smmq, smmq=smmq, centers=centers, ions=ions, subtitle=subtitle

;; color of cross-hairs and labels (if applicable)
xharecolor = 0
;; ----------------------------------------------------------------------
;; set up axis and labels
;; ----------------------------------------------------------------------

iq = [0, smmq.nrows-1]              ; nominally [0,123]
im = [0, smmq.ncols-1]              ; nominally [0,121]

;;; form axes
x = smmq.mqrange[0]*(smmq.mqrange[1]/smmq.mqrange[0])^(findgen(iq[1]+1)/iq[1])
x = reform(x[iq[0]:iq[1]])
y = smmq.mmrange[0]*(smmq.mmrange[1]/smmq.mmrange[0])^(findgen(im[1]+1)/im[1])
y = reform(y[im[0]:im[1]])

;;; set up tick marks

nx = n_elements(x) & ny = n_elements(y) 
nxtix = 6    & nytix = 6
 if (nx le nxtix) then begin 
   indx = indgen(nx)
endif else begin
   step = (nx-1)/(nxtix-1) & indx = indgen(nxtix)*step
endelse
xtickv = alog10(x[indx]) &  xtickname = string(x[indx],'(f4.1)')
if (ny le nytix) then begin 
   indy = indgen(ny)
endif else begin
   step = (ny-1)/(nytix-1) & indy = indgen(nytix)*step
endelse
ytickv = alog10(y[indy]) &  ytickname = string(y[indy],'(f4.1)')


;; ----------------------------------------------------------------------
;;; do plot
;; ----------------------------------------------------------------------

color_plot, smmq.mmq,  alog10(x), alog10(y), xtitle=smmq.mqtitle,$
  ytitle=smmq.mmtitle,  $  
  /fill, title=smmq.title , subtitle=subtitle, /logsc,  $
  xticks=nxtix-1,xminor=nxtix-1,xtickv=xtickv,xtickname=xtickname, $
  yticks=nytix-1,yminor=nytix-1,ytickv=ytickv,ytickname=ytickname, $
  zmin_color=1

;; ----------------------------------------------------------------------
;; plot and label ion centers
;; ----------------------------------------------------------------------
if (keyword_set(centers)) then begin
  nions = n_elements(ions)
  for nion=0,nions-1 do begin
    mq = 0.0
    mm = 0.0
    mqsig = 0.0
    mmsig = 0.0
    
    i_ion = where( centers.ion eq ions[nion], nwhere)
    if (nwhere le 0) then goto, next  ;; skip if none there
    centers_ion = centers[i_ion]

    ;; sum over step (since mmq matrix is summed over step)
    count = 0
    for nedb=min(centers_ion.step),max(centers_ion.step) do begin
      i_step = where( centers_ion.step eq nedb, nwhere)
      if (nwhere le 0) then goto, next

      mq = mq + centers_ion[i_step].(3)  ; m/q
      mqsig = mqsig + centers_ion[i_step].(4) ; m/q sigma (half-width)

      mm = mm + centers_ion[i_step].(5)  ; mass
      mmsig = mmsig + centers_ion[i_step].(6) ; mass sigma (half-width)

      count = count + 1
    endfor
    
    ;; turn sums into aves
    mq = mq / count
    mqsig = mqsig / count
    mm = mm / count
    mmsig = mmsig / count
    
    print, format='("ion = ", A," mq =",F6.2," mqsig =",F6.2," mm =",F6.2," mmsig =",F6.2)',$
      ions[nion],mq,mqsig,mm,mmsig

    ;; calculate +/- sigmas and take log to match plot
    mqlo = alog10(mq - mqsig)
    mqhi = alog10(mq + mqsig)
    mq = alog10(mq)
    mmlo = alog10(mm - mmsig)
    mmhi = alog10(mm + mmsig)
    mm = alog10(mm)

    if (mq ge alog10(smmq.mqrange[0]) and mq le alog10(smmq.mqrange[1])) $
      then inRange=1 else inRange=0
    if (mm ge alog10(smmq.mmrange[0]) and mm le alog10(smmq.mmrange[1])) $
      then inRange=1 else inRange=0
    if (inRange eq 1) then begin
      ;; draw cross-hairs on centers
      ;; ---------------------------
      ;; note: call is plots, [x0,x1], [y0,y1], color=somecolor,...
      ;;       where x is tof and y is esd

      ;; m/q
      plots, [mqlo, mqhi],$ ; x
        [mm,mm],$ ; y
        color=xharecolor, /data

      ;; mass
      plots,[mq,mq],$ ; x
        [mmlo, mmhi],$ ; y
        color=xharecolor, /data

      ;; label centers with ion names
      xyouts, mqhi, mm,$
        ions[nion], size=0.5,$
        charthick=1.5,color=xharecolor
    endif

    next:   ;; jump label for non-existant ion/step
  endfor
endif

return
end

