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

; set up E-T slice file
if (not keyword_set(etsfile)) then etsfile = 'axlv2_et_slices.dat'
get_lun, lun
openr, lun, etsfile

; read center data
if (not keyword_set(fmcfile)) then fmcfile = 'axlv2_' + date + '_fmcomp.dat'
restore, file='fmcomp_template.save'
fmc = read_ascii(fmcfile,template=template)

; set up postscript file
psfile = 'fmcomp.' + date + '.ps'
psplt, file=psfile, /color
loadct, 33


for step=2,59 do begin ; loop over charge steps

  ;; read ET matrix, returned in mat
  smread, lun=lun, mat=mat,title=title, xtitle=xtitle, xrange=xrange, $
            ytitle=ytitle, yrange=yrange

  ;; plot ET matrix
  color_plot, mat,  xrange, yrange, xtitle=xtitle,ytitle=ytitle,  $  
    /fill, title=title , subtitle=psfile ; , /logsc

  ;; select fm items for this step

  ;; plot symbols for fm

  ;; for using fmcexp (for debugging)
  if (step eq 41) then save, file='fmcexp.save', fmc, mat, xrange, yrange, $
    xtitle,ytitle, title
endfor

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
