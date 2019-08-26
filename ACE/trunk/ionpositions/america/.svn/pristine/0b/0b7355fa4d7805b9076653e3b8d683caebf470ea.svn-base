; Filename: smrp.pro
;
; Description:
;   Swindal Matrix Read and Plot.  
;   Reads swindal matrix into arrays for plotting.
;
; Author: Jim Raines, 7Jun2001
;
; Method:
;   The matrices are produced by the C++ Template Numerical Toolkit
;   (TNT) so they have a nice output format.  The first line contains
;   the row and column dimensions.  Subsequent lines are rows of the
;   matrix.  IDL see matrices as transposed compared to TNT so the row
;   and column dimensions are reversed to IDL and the matrix is transposed.
;
; Usage:
;   smrp, file='matrix.dat', data=mat, [/nolog]
;   
;   file is a TNT-style matrix file with additional header lines
;        line 1:  plot title
;        line 2:  x_axis_label y_axis_label
;        line 3:  x_axis_range y_axis_range
;        (standard TNT stuff after this)
;        line 4:  #_rows #_columns
;        line 5:  row 1
;        line 6:  row 2
;        ...
;   data the name in which to store the returned matrix
;   /nolog causes the contour plot to be done on a standard scale
;
; Major Modification History
;   27Feb2002   jmr  Made plotting optional.
;   07May2003   jmr  Fixed syntax problem in /noplot option
;   
;
pro smrp, file=file, data=mat, nolog=nolog, noplot=noplot

;;; init variables
get_lun, lun
openr, lun, file

tmpstr = strsplit(file, '.',/extract)
psfile = tmpstr[0] + '.ps'

;;; read title
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

msg = string(format='("Matrix is ",I4," rows by ",I4," columns" )',$
                 rowdim,coldim)
message, /info, msg

;;; set up array and read data
mat = fltarr(coldim,rowdim)

readf,lun, mat

mat = transpose(mat)

;;; do plot

if (not keyword_set(noplot) ) then begin

  psplt, file=psfile, /color
  loadct, 33
  ;; 33 -- blue background
  ;; 27 -- white background

  ;; plot (with or without log scale
  if (keyword_set(nolog)) then begin
    color_plot, mat,  xrange, yrange, xtitle=xtitle,ytitle=ytitle,  $  
      /fill, title=titlec, subtitle=psfile
  endif else begin
    color_plot, mat,  xrange, yrange, xtitle=xtitle,ytitle=ytitle,  $  
      /fill, title=title , /logsc, subtitle=psfile
  endelse

;;; other possibly useful options to color_plot
;  zcolors = [50,100,150,200,250]; 
; ,max_value = 100
;  ,zrange =[50,2000]
; ,/smooth 
;  ,/logsc


  ;; close and label PS plot file
  hardcopy, label='from smmq.pro', file=psfile, printer='file'

endif
;; pack up and get out
close, lun
free_lun, lun

return
end

