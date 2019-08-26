; Filename: smread.pro
;
; Description:
;   Swindal Matrix Read.  Reads swindal matrix into arrays for plotting.
;
; Author: Jim Raines, 7Jun2001
;
; Method:
;   The matrices are produced by the C++ Template Numerical Toolkit
;   (TNT) so they have a nice output format.  The first line contains
;   the row and column dimensions.  Subsequent lines are rows of the matrix.
;   
; Major Modification History
;   
;
pro smrp, file=file, data=mat

;;; init variables
get_lun, lun
openr, lun, file

;;; read yyyydoy
ydoy = 2000365
readf, lun, ydoy

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
;mat = fltarr(rowdim,coldim)
mat = fltarr(coldim,rowdim)

readf,lun, mat

mat = transpose(mat)

;;; do plot
title  = 'ACE/SWICS counts/second for day ' + string(format='(I7)',ydoy)

; warning: won't work for ps plots
;device, decompose = 0
;loadct, 9    -- instead use xloadct then green-white exp., reversed
color_plot, mat,  xrange, yrange, xtitle='TOF CH',ytitle='ESD CH',  $  
  /fill, title=title , /logsc  ;,$
;  zcolors = [50,100,150,200,250]; 
; ,max_value = 100
;  ,zrange =[50,2000]
; ,/smooth 
;  ,/logsc

; this zcolors makes a well colored scale but the plot is just red

;;; pack up and get out
close, lun
free_lun, lun

return
end

