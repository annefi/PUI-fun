; Filename: plot_smmq_sum.pro
;
; Description: 
;   Plot summation MMQ of all plots which match input pattern.
;
; Author: Jim Raines (jmr)
;
; Method:
;   
;   
; Revision controlled by CVS:
; $Id: smmq.pro,v 1.5 2004/06/14 19:38:36 jraines Exp $
;
; Major Modification History
;   19Mar2004   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   pattern     filename pattern, e.g., base='axlv2_mmq_*.dat' 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   [data]      data structure returned for further use, e.g., data=d001
; I   [/sum]      sum over timesteps
pro smmq, pattern=pattern, data=smmq_array, center_file=center_file,$
                   sum=sum

;; init variables
thisprog = 'plot_smmq_sum'

;; get list of files
spawn, 'ls -1 '+pattern, files
nfiles = n_elements(files)

for ifile = 0, nfiles-1 do begin

  print, thisprog+' -I- reading from file '+files[ifile]
  read_smmq, file=files[ifile], smmq=smmq_ts

  if (ifile eq 0) then begin
    smmq_array = smmq_ts
  endif else begin

    if (keyword_set(sum)) then begin
      smmq_array.mmq = smmq_array.mmq + smmq_ts.mmq
      if (ifile eq nfiles-1) then $
        smmq_array.file = smmq_array.file+' - '+smmq_ts.file
    endif else begin
      smmq_array = [smmq_array,smmq_ts]
    endelse

    ;; FIX: handle other structure members
  endelse
  
endfor

;; --- setup PS file

;; split off doy and fraction
;; note: assumes file names only differ by doy and fraction and have
;; format:  base_ddd_ff.dat, base can contain '_'
file_parse, file=files[0], base=base
s = strsplit(base,'_')
ns = n_elements(s)

base = strmid(base,0,s[ns-2])

doy0 = strmid(files[0],s[ns-2],3)           ;; first file
fr0  = strmid(files[0],s[ns-1],2)

doy1 = strmid(files[nfiles-1],s[ns-2],3)    ;; last file
fr1  = strmid(files[nfiles-1],s[ns-1],2)

psfile = base + doy0 + '_' + fr0 + '_' + doy1 + '_' + fr1 + '.ps'
psplt, file=psfile, /color
;loadct, 33
fix_ct_ends

;; read ion centers
;; ----------------
;; note: read_fmc returns an array of FMC structures labeled in
;; tof/esd space.  As such, structure element numbers are used
;; instead of names to ease confusion.  (An alternative would have
;; been to write a variant of read_fmc for the mmq version, but that
;; was deemed too repetetive.)
if (keyword_set(center_file)) then begin
  read_fmc, file=center_file, fmc=centers, ions=ions, eqtab=eoqtable
endif else centers=0

nsmmq = n_elements(smmq_array)
for ismmq=0,nsmmq-1 do begin

  plot_smmq, smmq=smmq_array[ismmq], centers=centers, ions=ions, $
    subtitle=smmq_array[ismmq].file
  tagplot, line1=tag, line2=psfile

endfor

;; ----------------------------------------------------------------------
;;; pack up and get out
;; ----------------------------------------------------------------------

ficlose
return
end
