; Filename: fieldnames_from_header.pro
;
; Description:
;   Extract fieldnames from whitespace separated fieldnames located in
;   last header line (first character = '#').
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: fieldnames_from_header.pro,v 1.2 2005/03/18 21:53:37 jraines Exp $
;
; Major Modification History
;   18Mar2005   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file from which to get fieldnames
; O   [returns]   array of fieldname strings
function fieldnames_from_header, file

get_lun, lun
openr, lun, file

got_header = 1
line = ''
lp = ['']
while (got_header) do begin
  readf, lun, line

  llp = lp
  lp = strsplit(line, /extract) ; automatically splits on whitespace

  if (stregex(lp[0],'#', /bool)) then got_header = 1 $
  else got_header = 0
endwhile

fieldnames = llp[1:n_elements(llp)-1]

close, lun
free_lun, lun

return, fieldnames
end
