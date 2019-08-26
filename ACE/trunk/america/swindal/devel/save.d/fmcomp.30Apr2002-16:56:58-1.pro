; Filename: fmcomp.pro
;
; Description:
;   Swindal forward model comparison.  Makes contour plot in E-T space
;   of MA slice and overplots forward model centers and widths.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   27Feb2002   jmr   initial coding
;
; Usage:
;   fmcomp, date='2001056'
pro fmcomp, fmcfile=fmcfile, etsfile=etsfile, date=date, fmcdata=fmc

;; ----------------------------------------------------------------------------
;; ---------------------------- set up  --------------------------------------
;; ---------------------------------------------------------------------------
;; set up E-T slice file
if (not keyword_set(etsfile)) then etsfile = 'axlv2_et_slices.dat'
get_lun, lun
openr, lun, etsfile

;; set up postscript file
psfile = 'fmcomp.' + date + '.ps'
psplt, file=psfile, /color

;; read center data 
if (not keyword_set(fmcfile)) then fmcfile = 'axlv2_' + date + '_fmcomp.dat'
restore, file='fmcomp_template.save'
fmc = read_ascii(fmcfile,template=template)

;; set up color table and colors
;loadct, 33                      ;33 is Blue-Red 2
;loadct, 27                      ;27 is Eos B
loadct, 34                      ;34 is Rainbow
fix_ct_ends                     ;make ends of color table black and white, resp
black = 0                       ;define color mnemonic
white = 1
xharecolor = black              ; set color for crosshares and rel. text

;; define subsections -- DEFAULT VALUES ONLY; REDEFINED LATER
xranges = intarr(2,3)
yranges = intarr(2,3)

;; build unique list of ions
ions = fmc.ion(sort(fmc.ion))   ; sort ions
ions = ions(uniq(ions))         ; remove duplicates
nions = n_elements(ions)        ; store number of ions

;; build a uniqe list of eoq
eoqtable = fmc.eoq(sort(fmc.eoq))
eoqtable = eoqtable(uniq(eoqtable))
eoqtable = reverse(eoqtable)

;; ----------------------------------------------------------------------------
;;                           get to work
;; ----------------------------------------------------------------------------
for step=2,59 do begin ; loop over charge steps, 2-59 is the full range

  ;; **** jump to a step for debugging ****
  if (0) then begin
    jumptostep = 28
    if (step eq 2) then begin
      for jumpstep=2,jumptostep-1 do begin
        print, 'fmcomp -I- SKIPPING step ' + string(format='(I)',jumpstep)
        ;; read ET matrix, returned in mat
        smread, lun=lun, mat=mat,title=title, xtitle=xtitle, xrange=xrange, $
          ytitle=ytitle, yrange=yrange
      endfor
      step = jumpstep
    endif
  endif

  ;; read ET matrix, returned in mat
  smread, lun=lun, mat=mat,title=title, xtitle=xtitle, xrange=xrange, $
    ytitle=ytitle, yrange=yrange


  nstep = step - 2              ; loops start at zero even though element zero 
                                ; represents EDB 2 -- step is deflection
                                ; voltage step while nstep is position in array

  print, 'fmcomp -I- working on step ' + string(format='(I)',step)

  ;; select values for this step
  i = where(fmc.eoq eq eoqtable(nstep))
  eoq = fmc.eoq(i)
  tof = fmc.tof(i)
  tofsig = fmc.tofsig(i)
  esd = fmc.esd(i)
  esdsig = fmc.esdsig(i)
  ion  = fmc.ion(i)
  
  ;; define bounds for subsections
  ;; -----------------------------
  ;; whole thing
  xranges[*,0] = [0,1023]
  yranges[*,0] = [0,255]

  ;; non-iron (nfe)
  nfeidx = where(stregex( ion, 'Fe', /boolean) ne 1)
  xranges[*,1] = [min(tof(nfeidx) - tofsig(nfeidx)),$
                max(tof(nfeidx) + tofsig(nfeidx))]
  yranges[*,1] = [min(esd(nfeidx) - esdsig(nfeidx)),$
                max(esd(nfeidx) + esdsig(nfeidx))]

  ;; iron (fe)
  feidx = where(stregex( ion, 'Fe', /boolean) eq 1)
  xranges[*,2] = [min(tof(feidx) - tofsig(feidx)),$
                max(tof(feidx) + tofsig(feidx))]
  yranges[*,2] = [min(esd(feidx) - esdsig(feidx)),$
                 max(esd(feidx) + esdsig(feidx))]

  ;; HACK!!!
  iyover = where(yranges gt 255,niyover)
  if (niyover gt 0) then yranges[iyover] = 255
  ;xranges = [[0,1023],[300,425],[400,700]]
  ;yranges = [[0,255],[20,100],[20,80]] 

  ;; loop over subsections
  for nsub=0,2 do begin         ; FIX: figure out number of subsections
    ;; make subsection matrices
    xrange = xranges[*,nsub]
    yrange = yranges[*,nsub]
    zrange=[.5e-5,.5e-3]

    submat = mat[xrange(0):xrange(1),yrange(0):yrange(1)]

    ;; plot ET matrix
    subtitle = psfile + ', step = ' + string(format='(I2)',step) + $
      ', E/q(keV/e) = ' + string(format='(F6.2)',eoqtable(nstep))

    color_plot, submat,  xrange, xtitle=xtitle,subtitle=subtitle,$
      yrange, ytitle=ytitle, title=title , $  
      zrange=zrange, /logsc, zmin_color=white, $
      /fill

    ;; --- Plot Forward Model Centers/Ranges ---
    ;; -----------------------------------------

    for nion=0,nions-1 do begin

      ;print,$
      ;  format='("Ion ", A0," is centered at (tof,esd)=(",F6.2,",",f6.2,")" )',$
       ; ions(nion), tof(nion), esd(nion)

      ;; decide if center is in plot range
      if ( ( ((tof(nion) - tofsig(nion)) ge xrange(0)) and $
             ((tof(nion) + tofsig(nion)) le xrange(1)) ) and $
           ( ((esd(nion) - esdsig(nion)) ge yrange(0)) and $
             ((esd(nion) + esdsig(nion)) le yrange(1)) ) ) $
        then doPlot = 1 else doPlot = 0
     
      if (doPlot eq 1) then begin
        ;; label centers with ion names
        xyouts, tof(nion) + tofsig(nion), esd(nion), ions(nion), size=0.5,$
          charthick=1.5,color=xharecolor

        ;; draw cross-hairs on centers
        ;; tof
        plots, [[tof(nion) - tofsig(nion), esd(nion)], $
                [tof(nion) + tofsig(nion),esd(nion)]], color=xharecolor

        ;; esd
        plots,[[tof(nion),esd(nion) - esdsig(nion)],$
               [tof(nion),esd(nion) + esdsig(nion)]], color=xharecolor
      endif
      
    endfor                      ;loop over ions
  endfor                        ;loop over subsections

endfor                          ; loop over steps

;; close and label PS plot file
hardcopy, label='from fmcomp.pro', file=psfile, printer='file'

close, lun
free_lun, lun
return
end

;; smread -- read swindal matrix from open file (lun)
;;           Also returns header info for plotting; See smrp.pro for
;;           file format details.
;; Jim Raines, 27Feb2002 (based on smrp.pro)
pro smread, lun=lun, mat=mat, title=title, xtitle=xtitle, xrange=xrange, $
            ytitle=ytitle, yrange=yrange


;; read title
title = ''
readf, lun, title

;;; read x and y titles
tmpstr = ''
readf, lun, tmpstr
xytitle = strcompress(tmpstr)
xytitle = strsplit(tmpstr,/extract)

xtitle = xytitle[0]
ytitle = xytitle[1]

;;; read x and y ranges
xrange = [0,0]
yrange = xrange
readf, lun, xrange, yrange

;;; find dimensions of matrix
rowdim = 0
coldim = 0

readf, lun, rowdim, coldim

;msg = string(format='("Matrix is ",I4," rows by ",I4," columns" )',$
;                 rowdim,coldim)
;message, /info, msg

;;; set up array and read data
mat = fltarr(coldim,rowdim)

readf,lun, mat

mat = transpose(mat)

return
end

; Filename: fix_ct_ends.pro
;
; Description:
;   Sets the first color table entry to black and the last to white,
;   for 8 bit (256 element) color tables only.  Keyword 'reverse'
;   flips this around to the opposite.  THIS IS A SPECIALLY MODIFIED
;   VERSION FOR FMCOMP.PRO.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   25Apr2002   jmr   initial coding
;   26Apr2002   jmr   modified for fmcomp.pro, 0 is black, 1 is white
;
pro fix_ct_ends

  ;; IDL stores color tables in these arrays
  common colors, R_orig, G_orig, B_orig, R_curr, G_curr, B_curr

  ;; make first entry black
  r_curr(0) = 0
  g_curr(0) = 0
  b_curr(0) = 0

  ;; make second entry white
  r_curr(1) = 255
  g_curr(1) = 255
  b_curr(1) = 255

  tvlct, r_curr, g_curr, b_curr

return
end
