; Filename: smmq_pub.pro
;
; Description:
;   Swindal mass-mass/charge plotter.  THIS VERSION MODIFIED FOR PUBLICATION.
;
; Author: Jim Raines (jmr) 
;
; Method:
;   The matrices are produced by the C++ Template Numerical Toolkit
;   (TNT) so they have a nice output format.  The first line contains
;   the row and column dimensions.  Subsequent lines are rows of the matrix.
;
;   Centers are read from a forward model centers, axlv2_fmc
;   
; Revision controlled by CVS:
; $Id: smmq_pub.pro,v 1.1 2005/03/14 16:53:40 jraines Exp $
;
; Major Modification History
;   08Jan2003   jmr   Adapted from smmq.pro.
;
; Arguments (optional in [])
;
; I/O Arg           Explanation
; --- ----------    -----------
; I   file          MMQ data file from axlv2.
; O   data          MMQ matrix
; I   [center_file] filename for fmc data file, e.g. axlv2_fmcomp.dat.
; I   [tag]         text tag for plot label
; I   [title]       title for plot
pro smmq_pub, file=file, data=mat, center_file=center_file, tag=tag, $
              title=title,position=position

;; ----------------------------------------------------------------------
;;; ===> adjustable parameters <===
;; ----------------------------------------------------------------------

;; color of cross-hairs and labels (if applicable)
xharecolor = 0

;; names of ions for which to plot centers
ions_to_plot = ['H+','He2+',$
                'C4+','C5+','C6+',$
                'O6+','O7+','O8+',$
                'Fe8+','Fe16+','Fe22+']
mass_to_plot = [1.,4.,$
                12.,12.,12.,$
                16.,16.,16.,$
                56.,56.,56.]
labels = ['H!E+!N','He!E2+!N',$
          'C!E4-6+!N', ' ', ' ',$
          'O!E6-8+!N', ' ', ' ',$
          'Fe!E22+,16+,8+!N',' ', ' ']

;ions_to_plot = ['O3+','O4+','O5+','O6+','O7+','O8+']

;mass_to_plot = [16.,16.,16.,16.,16.,16.]

;labels = ['O!E3-8+!N', ' ', ' ', ' ', ' ', ' ']

xraw_tickv = [1.0,5.0,20.0]
;yraw_tickv = [1.0, 4.0,12.0,56.0]
yraw_tickv = [1.0, 10.0,50.0,100.0]
;; ----------------------------------------------------------------------
;; init variables
;; ----------------------------------------------------------------------

;; ----------------------------------------------------------------------
;;; read data and meta data from file
;; ----------------------------------------------------------------------
;; note: This code was take from smread2.  The generic variable names
;; were kept and those variables assigned to other, more discriptively
;; named variables later in this program.
get_lun, lun
openr, lun, file

file_parse, file=file, base=base
psfile = base + '.ps'

;;; read title
tmptitle = ''
readf, lun, tmptitle
if (not keyword_set(title)) then title=tmptitle

;;; read x and y titles
tmpstr = ''
readf, lun, tmpstr
xytitle = strcompress(tmpstr)
xytitle = strsplit(tmpstr,/extract)

xtitle = xytitle[0]
ytitle = xytitle[1]

;;; read x and y ranges
xrange = [0.0,0.0]
yrange = xrange
readf, lun, xrange, yrange

;;; find dimensions of matrix
rowdim = 0
coldim = 0

readf, lun, rowdim, coldim

msg = string(format='("Matrix is ",I4," rows by ",I4," columns" )',$
                 rowdim,coldim)
message, /info, msg

;;; set up array and read data
mat = fltarr(coldim,rowdim)

readf,lun, mat

mat = transpose(mat)

;mmq = reform(mat[iq[0]:iq[1],im[0]:im[1]])
;mmq = mat
;mmq = alog10(mmq > 1.0)

;; ----------------------------------------------------------------------
;; set up axis and labels
;; ----------------------------------------------------------------------

qrange = xrange
mrange = yrange
iq = [0, rowdim-1]              ; nominally [0,123]
im = [0, coldim-1]              ; nominally [0,121]

;;; form axes
x = qrange[0]*(qrange[1]/qrange[0])^(findgen(iq[1]+1)/iq[1])
x = reform(x[iq[0]:iq[1]])
y = mrange[0]*(mrange[1]/mrange[0])^(findgen(im[1]+1)/im[1])
y = reform(y[im[0]:im[1]])

;;; set up tick marks
nx = n_elements(x)
ny = n_elements(y) 
nxtix = n_elements(xraw_tickv)
nytix = n_elements(yraw_tickv)

if (nx le nxtix) then begin 
  indx = indgen(nx)
endif else begin
  step = (nx-1)/(nxtix-1)
  indx = indgen(nxtix)*step
endelse
;xtickv = alog10(x[indx])
;xtickname = string(x[indx],'(f4.1)')
xtickv = alog10(xraw_tickv)
xtickname = string(xraw_tickv, '(F5.1)')

if (ny le nytix) then begin 
  indy = indgen(ny)
endif else begin
  step = (ny-1)/(nytix-1)
  indy = indgen(nytix)*step
endelse
;ytickv = alog10(y[indy])
;ytickname = string(y[indy],'(f4.1)')
ytickv = alog10(yraw_tickv)
ytickname = string(yraw_tickv, '(F5.1)')

;stop
;; ===> hardcode axis labels for publication
xtitle = 'm/q'
ytitle = 'mass'
;; ----------------------------------------------------------------------
;;; do plot
;; ----------------------------------------------------------------------

;psplt, file=psfile, /color
if (not keyword_set(tag)) then tag=''

;erase  ;; from nathan, I don't know why
;loadct, 33
fix_ct_ends
; 33 -- blue background
; 27 -- white background

color_plot, mat,  alog10(x), alog10(y), xtitle=xtitle,ytitle=ytitle,  $  
  /fill, title=title , /logsc,  $
  xticks=nxtix-1,xminor=nxtix-1,xtickv=xtickv,xtickname=xtickname, $
  yticks=nytix-1,yminor=nytix-1,ytickv=ytickv,ytickname=ytickname, $
  zmin_color=1, position=position, /noscale

;tagplot, line1=tag, line2=psfile

;; ----------------------------------------------------------------------
;; plot and label ion centers
;; ----------------------------------------------------------------------
if (keyword_set(center_file)) then begin
  ;; read FM center data
  ;; note: read_fmc returns an array of FMC structures labeled in
  ;; tof/esd space.  As such, structure element numbers are used
  ;; instead of names to ease confusion.  (An alternative would have
  ;; been to write a variant of read_fmc for the mmq version, but that
  ;; was deemed too repetetive.)
  read_fmc, file=center_file, fmc=fmc, ions=ions, eqtab=eoqtable
  
  ;; only plot a subset of ions
  ions = ions_to_plot
  nions = n_elements(ions)
  for nion=0,nions-1 do begin
    mq = 0.0
    mm = 0.0
    mqsig = 0.0
    mmsig = 0.0
    
    i_ion = where( fmc.ion eq ions[nion], nwhere)
    if (nwhere le 0) then goto, next  ;; skip if none there
    fmc_ion = fmc[i_ion]

    ;; sum over step (since mmq matrix is summed over step)
    count = 0
    for nedb=min(fmc_ion.step),max(fmc_ion.step) do begin
      i_step = where( fmc_ion.step eq nedb, nwhere)
      if (nwhere le 0) then goto, next

      mq = mq + fmc_ion[i_step].(3)  ; m/q
      mqsig = mqsig + fmc_ion[i_step].(4) ; m/q sigma (half-width)

      mm = mm + fmc_ion[i_step].(5)  ; mass
      mmsig = mmsig + fmc_ion[i_step].(6) ; mass sigma (half-width)

      count = count + 1
    endfor
    
    ;; turn sums into aves
    mq = mq / count
    mqsig = mqsig / count
    mm = mm / count
    mmsig = mmsig / count

    print, format='("ion = ", A," mq =",F6.2," mqsig =",F6.2," mm =",F6.2," mmsig =",F6.2)',$
      ions[nion],mq,mqsig,mm,mmsig

    ;; adjust Fe to make up for bad FM
    ion_parse, ion=ions[nion], elem=elem, state=state
    if (elem eq 'Fe') then begin
      mm = mm + 8.0
  
      ;; HACK(!) some state-dep positioning
      if ( state eq 8) then mm = .9*mm
      if ( state eq 22) then mm = 1.05*mm
    endif

    ;; draw small x's instead of sigmas
    mqdim = alog10(qrange[1]-qrange[0])
    size_mq = .020
    mqlo = alog10(mq) - size_mq
    mqhi = alog10(mq) + size_mq
    mq = alog10(mq)

    mmdim = alog10(mrange[1]-mrange[0])
    size_mm = size_mq*mmdim/mqdim ; scale up by ratio for same size in each dim
    mmlo = alog10(mm) - size_mm
    mmhi = alog10(mm) + size_mm
    mm = alog10(mm)

    if (mq ge alog10(qrange[0]) and mq le alog10(qrange[1])) $
      then inRange=1 else inRange=0
    if (mm ge alog10(mrange[0]) and mm le alog10(mrange[1])) $
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
;      mqhi = .9+mq_offset[nion]
;      ion_parse, ion=ions[nion], elem=elem, state=state, /strings
;      if (mq_offset[nion] eq 0.0) then begin
;        label = elem + ': ' + state
;      endif else begin
;        label = state
;      endelse
      mqhi = .9
      xyouts, mqhi, alog10(mass_to_plot[nion]),$
        labels[nion], size=1.0,$
        charthick=2.1,color=xharecolor
    endif

    next:   ;; jump label for non-existant ion/step
  endfor
endif

;; ----------------------------------------------------------------------
;;; pack up and get out
;; ----------------------------------------------------------------------
close, lun
free_lun, lun

;ficlose

return
end

