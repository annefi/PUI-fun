; Filename: smread.pro
;
; Description:
;   Swindal Matrix Read -- read swindal matrix from open file (lun).
;   Also returns header info for plotting. 
;
; Author: Jim Raines (jmr)
;
; Method:
;   The matrices are produced by the C++ Template Numerical Toolkit
;   (TNT) so they have a nice output format.  In addition to the matrices, 
;   header lines are added to convey important information:
;
;        line 1:  plot title
;        line 2:  x_axis_label y_axis_label
;        line 3:  x_axis_range y_axis_range
;        (standard TNT stuff after this)
;        line 4:  #_rows #_columns
;        line 5:  row 1
;        line 6:  row 2
;        ...
;
;   Since, IDL matrices as transposed compared to TNT, the row and
;   column dimensions are reversed to IDL and the matrix is
;   transposed.
;   
; Arguments:
;   lun -- open logical unit number for swindal matrix file
;   mat -- matrix read from file (with proper transposition)
;   title, xtitle, ytitle -- titles from swindal
;   xrange, yrange -- ranges (tof, esd) relative to full tof,esd matrix.
;                     ((0,1023),(0,255)) is full tof, esd matrix
;
; Major Modification History
;   27Feb2002   jmr   initial coding for smread in fmcomp.pro
;   18Oct2002   jmr   split off into separate file, added header
;
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

