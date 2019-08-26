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
pro fmcomp, fmcfile=fmcfile, etsfile=etsfile, date=date

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

;; define subsections
xrs = [[0,1023],[300,425],[400,700]]
yrs = [[0,255],[20,100],[20,80]] 

;; ----------------------------------------------------------------------------
;;                           get to work
;; ----------------------------------------------------------------------------
for step=2,44 do begin ; loop over charge steps, 2-59 is the full range

  ;; **** jump to the 37 for debugging ****
  jumptostep = 41
  if (step eq 2) then begin
    for jumpstep=2,jumptostep do begin
      print, 'fmcomp -I- SKIPPING step ' + string(format='(I)',jumpstep)
      ;; read ET matrix, returned in mat
      smread, lun=lun, mat=mat,title=title, xtitle=xtitle, xrange=xrange, $
        ytitle=ytitle, yrange=yrange
    endfor
    step = jumpstep
  endif

  nstep = step - 2      ; loops start at zero even though element zero 
                        ; represents EDB 2 

  print, 'fmcomp -I- working on step ' + string(format='(I)',step)
  
  ;; loop over subsections
  for isub=0,2 do begin         ; FIX: figure out number of subsections
    ;; make subsection matrices
    xrange = xrs[*,isub]
    yrange = yrs[*,isub]
    zrange=[.5e-5,.5e-3]

    submat = mat[xrange(0):xrange(1),yrange(0):yrange(1)]

    ;; plot ET matrix
    subtitle = psfile + ', step = ' + string(format='(I)',step)
    color_plot, submat,  xrange, xtitle=xtitle,subtitle=subtitle,$
      yrange, ytitle=ytitle, title=title , $  
      zrange=zrange, /logsc, zmin_color=white, $
      /fill

    ;; --- FM stuff ---
    ;; ----------------

    ;; build unique list of ions
    ions = fmc.ion(sort(fmc.ion)) ; sort ions
    ions = ions(uniq(ions))     ; remove duplicates
    nions = n_elements(ions)    ; store number of ions

    for ion=0,nions-1 do begin
      ;; select values for this ion
      i = where(fmc.ion eq ions(ion))
      eoq = fmc.eoq(i)
      tof = fmc.tof(i)
      tofsig = fmc.tofsig(i)
      esd = fmc.esd(i)
      esdsig = fmc.esdsig(i)

      ;print,$
      ;  format='("Ion ", A0," is centered at (tof,esd)=(",F6.2,",",f6.2,")" )',$
       ; ions(ion), tof(nstep), esd(nstep)

      ;; decide if center is in plot range
      if ( ( ((tof(nstep) - tofsig(nstep)) ge xrange(0)) and $
             ((tof(nstep) + tofsig(nstep)) le xrange(1)) ) and $
           ( ((esd(nstep) - esdsig(nstep)) ge yrange(0)) and $
             ((esd(nstep) + esdsig(nstep)) le yrange(1)) ) ) $
        then doPlot = 1 else doPlot = 0
     
      if (doPlot eq 1) then begin
        ;; label centers with ion names
        xyouts, tof(nstep) + tofsig(nstep), esd(nstep), ions(ion), size=0.5,$
          charthick=1.5,color=xharecolor

        ;; draw cross-hairs on centers
        ;; tof
        plots, [[tof(nstep) - tofsig(nstep), esd(nstep)], $
                [tof(nstep) + tofsig(nstep),esd(nstep)]], color=xharecolor

        ;; esd
        plots,[[tof(nstep),esd(nstep) - esdsig(nstep)],$
               [tof(nstep),esd(nstep) + esdsig(nstep)]], color=xharecolor
      endif
      
    endfor                      ;loop over ions
  endfor                        ;loop over subsections

endfor                          ; loop over steps

;; close and label PS plot file
hardcopy, label='from fmcomp.pro', file=psfile, printer='file'

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
