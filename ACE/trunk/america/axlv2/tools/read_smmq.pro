; Filename: read_smmq.pro
;
; Description:
;   Read a swindal mass-mass/charge matrix.
;
; Author: Jim Raines (jmr)
;
; Method:
;   MMQ matrices have the following format:
;       line 1:    title
;       line 2:    x_label y_label
;       line 3:    mq0 mq1 mm0 mm1
;       line 4:    num_lines(N) num_elem_per_line(M)
;       line 5:    mat(0,0) mat(1,0) ... mat(M-1,0)
;       line 6:    mat(0,0) mat(1,0) ... mat(M-1,0)
;     ...
;     line N+4:    mat(0,N-1) mat(1,N-1) ... mat(M-1,N-1)
;
;   Lines after 3 represent a built-in matrix output format from the 
;   Template Numerical Toolkit(TNT).
;   
;   The data structure returned adds descriptive info. to the data and
;   is described in the code.
;     
;   
; Revision controlled by CVS:
; $Id: read_smmq.pro,v 1.1 2004/06/14 19:38:36 jraines Exp $
;
; Major Modification History
;   19Mar2004   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   smmq        returned data structure, e.g., smmq=d001
pro read_smmq, file=file, smmq=d


;; ----------------------------------------------------------------------
;;; read data and meta data from file
;; ----------------------------------------------------------------------
;; note: This code was take from smread2.  The generic variable names
;; were kept and those variables assigned to other, more discriptively
;; named variables later in this program.
get_lun, lun
openr, lun, file

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

;; ----------------------------------------------------------------------
;; return data
;; ----------------------------------------------------------------------

file_parse, file=file, base=base, dir=dir

;; set up data structure
d = {                      $; anonymous struct, required in case dim. vary
      dir: dir,            $; data directory
      file: file,          $; data file
      title: title,        $; title of data, read from file
      mqtitle: xtitle,     $; title for m/q dimension
      mmtitle: ytitle,     $; title for mass dimension
      mqrange: xrange,     $; range of m/q dimension (amu/e)
      mmrange: yrange,     $; range of mass dimension (amu)
      nrows: rowdim,       $; number of rows in mmq
      ncols: coldim,       $; number of columns in mmq
      mmq: mat             $; mmq matrix, (mq,mm)
}

close, lun
free_lun, lun

return
end

      
