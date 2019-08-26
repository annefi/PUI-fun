; Filename: smread2.pro
;
; Description:
;   Swindal Matrix Read -- read swindal matrix from open file (lun).
;   Also returns header info for plotting.  Returns data in structure. 
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
;   data -- structure containing items below:
;     mat(tof,energy) -- matrix read from file (with proper transposition)
;       e.g. the element at tof=380 and energy=50 is mat(380,50)
;     title, xtitle, ytitle -- titles from swindal
;     xrange, yrange -- ranges (tof, esd) relative to full tof,esd matrix.
;       ((0,1023),(0,255)) is full tof, esd matrix
;
; Major Modification History
;   18Oct2002   jmr   adapted from smread.pro
;
pro smread2, lun=lun, data=d

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

;; set up structure
d = { smread2,                     $ ; name of structure
      mat: fltarr(rowdim,coldim),  $ ; E-T matrix, (tof, energy) to idl
      title: '',                   $ ; plot title
      xtitle: '',                  $ ; x axis title
      ytitle: '',                  $ ; y axis title
      xrange: intarr(2),           $ ; x range
      yrange: intarr(2)            $ ; y range
    }

;; assign members
d.mat = mat
d.title = title
d.xtitle = xtitle
d.ytitle = ytitle
d.xrange = xrange
d.yrange = yrange

return
end

