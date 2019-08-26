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

;; read center data -- fix: change to formated read?
if (not keyword_set(fmcfile)) then fmcfile = 'axlv2_' + date + '_fmcomp.dat'
restore, file='fmcomp_template.save'
fmc_bycol = read_ascii(fmcfile,template=template)

;; build unique list of ions -- needed to figure out number of ions
ions = fmc_bycol.ion(sort(fmc_bycol.ion ))   ; sort ions
ions = ions(uniq(ions))         ; remove duplicates
nions = n_elements(ions)        ; store number of ions

;; build a uniqe list of eoq -- needed?
eoqtable = fmc_bycol.eoq(sort(fmc_bycol.eoq))
eoqtable = eoqtable(uniq(eoqtable))
eoqtable = reverse(eoqtable)
eoqtable = [-1,-1,eoqtable[*]]  ; add -1 for first two steps, 0 and 1, 
                                ; since they are not used

;; re-organize forward model data into array of structures
;; -------------------------------------------------------
;; This organization, rather than the structure of arrays as read in
;; by read_ascii, makes misalignments (e.g. pairing ion with wrong
;; tof, esd, etc.) more much difficult

;; define structure
fmc_element = $
                 { fmc1,       $ ;name of structure
                   step: 0,    $ ;deflection voltage step (DVS)
                   eoq: 0.0,   $ ;E/q
                   ion: '',    $ ;name of ion (e.g. He1+, Fe15+)
                   prate: 0.0, $ ;probabilistic rate
                   tof: 0.0,   $ ;forward model (fm) time of flight
                   tofsig: 0.0,$ ;fm tof sigma (1/2 width of gaussian)
                   pctof: 0.0, $ ;tof center from prob. rate (prob center tof)
                   deltof: 0.0,$ ;difference between fm and prob center
                   esd: 0.0,   $ ;forward model (fm) time of flight
                   esdsig: 0.0,$ ;fm esd sigma (1/2 width of gaussian)
                   pcesd: 0.0, $ ;esd center from prob. rate (prob center esd)
                   delesd: 0.0 $ ;difference between fm and prob center
                 }

;; build array of structures
fmc = replicate( fmc_element, n_elements(fmc_bycol.ion))

;; fill structures in fmc array
for i=0,n_elements(fmc_bycol.ion)-1 do begin
  fmc[i].step = where(eoqtable eq fmc_bycol.eoq[i])
  fmc[i].eoq  = fmc_bycol.eoq[i]
  fmc[i].ion  = fmc_bycol.ion[i]
  fmc[i].prate  = fmc_bycol.prate[i]
  fmc[i].tof  = fmc_bycol.tof[i]
  fmc[i].tofsig  = fmc_bycol.tofsig[i]
  fmc[i].pctof  = fmc_bycol.pctof[i]
  fmc[i].deltof  = fmc_bycol.deltof[i]
  fmc[i].esd  = fmc_bycol.esd[i]
  fmc[i].esdsig  = fmc_bycol.esdsig[i]
  fmc[i].pcesd  = fmc_bycol.pcesd[i]
  fmc[i].delesd  = fmc_bycol.delesd[i]
endfor

;; define an array of fmc structures to use with individual steps
fmcstep = replicate( fmc_element, nions)

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

;; ----------------------------------------------------------------------------
;;                           get to work
;; ----------------------------------------------------------------------------
for step=2,47 do begin ; loop over charge steps, 2-59 is the full range

  ;; **** jump to a step for debugging ****
  if (1) then begin
    jumptostep = 28             ; step 28 is where counts get significant
    if (step eq 2) then begin
      for jumpstep=2,jumptostep-1 do begin
        print, 'fmcomp -I- SKIPPING step ' + string(format='(I)',jumpstep)
        if (0) then begin
          ;; read ET matrix, returned in mat
          smread, lun=lun, mat=mat,title=title, xtitle=xtitle, xrange=xrange, $
          ytitle=ytitle, yrange=yrange
        endif else begin
          print, 'fmcomp -D- not reading ET matrix from disk...'
        endelse
      endfor
      step = jumpstep
    endif
  endif

  ;; read ET matrix, returned in mat
  smread, lun=lun, mat=mat,title=title, xtitle=xtitle, xrange=xrange, $
    ytitle=ytitle, yrange=yrange

  if (1) then begin
    if (step ge 39 and step le 41) then begin
      fmcdbgfile = 'fmcdbg'+string(format='(I2)',step)+'.save'
      if (0) then begin
        print, '****** saving mats for debugging ******'
        save, file=fmcdbgfile, mat, xrange, yrange,xtitle,ytitle,title
      endif else begin
        print, '****** using restored mats for debugging ******'
        restore, file=fmcdbgfile
      endelse
    endif else begin
      print, 'fmcomp -D- DBG SKIPPING step ' + string(format='(I)',step)
      goto, next
    endelse
  endif

  nstep = step - 2              ; loops start at zero even though element zero 
                                ; represents EDB 2 -- step is deflection
                                ; voltage step while nstep is position in array

  print, 'fmcomp -I- working on step ' + string(format='(I)',step)

  ;; select data for this step
  tmp_index = where(fmc[*].step eq step, ntmp_index)
  if (ntmp_index gt 0) then fmcstep = fmc[tmp_index] else goto, next

  ;; define bounds for subsections
  ;; -----------------------------
  ;; for reference sake, these ranges work ok
  ;; full, non-iron, iron, respectively
  ;; xranges = [[0,1023],[300,425],[400,700]]
  ;; yranges = [[0,255],[20,100],[20,80]] 

  ;; whole thing
  xranges[*,0] = [0,1023]
  yranges[*,0] = [0,255]

  ;; non-iron (nfe)
  nfeidx = where(stregex( fmcstep[*].ion, 'Fe', /boolean) ne 1)
  xranges[*,1] = [min(fmcstep[nfeidx].tof - fmcstep[nfeidx].tofsig),$
                max(fmcstep[nfeidx].tof + fmcstep[nfeidx].tofsig)]
  yranges[*,1] = [min(fmcstep[nfeidx].esd - fmcstep[nfeidx].esdsig),$
                max(fmcstep[nfeidx].esd + fmcstep[nfeidx].esdsig)]

  ;; iron (fe)
  feidx = where(stregex( fmcstep[*].ion, 'Fe', /boolean) eq 1)
  xranges[*,2] = [min(fmcstep[feidx].tof - fmcstep[feidx].tofsig),$
                max(fmcstep[feidx].tof + fmcstep[feidx].tofsig)]
  yranges[*,2] = [min(fmcstep[feidx].esd - fmcstep[feidx].esdsig),$
                 max(fmcstep[feidx].esd + fmcstep[feidx].esdsig)]

  ;; HACK!!!
  iyover = where(yranges gt 255,niyover)
  if (niyover gt 0) then yranges[iyover] = 255

  ;; loop over subsections
  for nsub=0,2 do begin         ; FIX: figure out number of subsections
    ;; make subsection matrices
    xrange = xranges[*,nsub]
    yrange = yranges[*,nsub]
    zrange=[.5e-5,.5e-3]

    submat = mat[xrange(0):xrange(1),yrange(0):yrange(1)]

    ;; plot ET matrix
    subtitle = psfile + ', step = ' + string(format='(I2)',step) + $
;      ', E/q(keV/e) = ' + string(format='(F6.2)',eoqtable(nstep))
      ', E/q(keV/e) = ' + string(format='(F6.2)',fmcstep[0].eoq)

    color_plot, submat,  xrange, xtitle=xtitle,subtitle=subtitle,$
      yrange, ytitle=ytitle, title=title , $  
      zrange=zrange, /logsc, zmin_color=white, $
      /fill

    ;; --- Plot Forward Model Centers/Ranges ---
    ;; -----------------------------------------

    for nion=0,nions-1 do begin

      format = '("At E/q=",F6.2,", ion ",A0," is centered at ' $
       + '(tof,esd)=(",F6.2,",",f6.2,")")'
      print,format=format,fmcstep[nion].eoq,$
        fmcstep[nion].ion, fmcstep[nion].tof, fmcstep[nion].esd

      ;; decide if center is in plot range
      if ( ( ((fmcstep[nion].tof - fmcstep[nion].tofsig) ge xrange(0)) and $
             ((fmcstep[nion].tof + fmcstep[nion].tofsig) le xrange(1)) ) and $
           ( ((fmcstep[nion].esd - fmcstep[nion].esdsig) ge yrange(0)) and $
             ((fmcstep[nion].esd + fmcstep[nion].esdsig) le yrange(1)) ) ) $
        then doPlot = 1 else doPlot = 0
     
      if (doPlot eq 1) then begin
        ;; label centers with ion names
        xyouts, fmcstep[nion].tof + fmcstep[nion].tofsig, fmcstep[nion].esd,$
          fmcstep[nion].ion, size=0.5,$
          charthick=1.5,color=xharecolor

        ;; draw cross-hairs on centers
        ;; tof
;        plots, [[fmcstep[nion].tof - fmcstep[nion].tofsig, fmcstep[nion].esd],$
;                [fmcstep[nion].tof + fmcstep[nion].tofsig,fmcstep[nion].esd]],$
;          color=xharecolor
        plots, [fmcstep[nion].tof - fmcstep[nion].tofsig,fmcstep[nion].tof + fmcstep[nion].tofsig ],$
                [fmcstep[nion].esd,fmcstep[nion].esd],$
          color=xharecolor

        ;; esd
;        plots,[[fmcstep[nion].tof,fmcstep[nion].esd - fmcstep[nion].esdsig],$
;               [fmcstep[nion].tof,fmcstep[nion].esd + fmcstep[nion].esdsig]],$
;          color=xharecolor
        plots,[fmcstep[nion].tof,fmcstep[nion].tof],$
               [fmcstep[nion].esd - fmcstep[nion].esdsig,fmcstep[nion].esd + fmcstep[nion].esdsig],$
          color=xharecolor
      endif
      
    endfor                      ;loop over ions
  endfor                        ;loop over subsections

  next:                         ; used w/goto to move to next loop iter. immed.
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
