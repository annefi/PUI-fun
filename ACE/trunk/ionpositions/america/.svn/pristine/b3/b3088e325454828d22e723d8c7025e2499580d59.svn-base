; Filename: doyfr2crfr.pro
;
; Description:
;   Convert day of year fraction (doyfr) to Carrington Rotation fraction.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: doyfr2crfr.pro,v 1.1 2005/04/23 06:36:46 jraines Exp $
;
; Major Modification History
;   22Apr2005   jmr   Initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   arg1        day of year fraction
; O   [returned]  Carrington rotation fraction
function doyfr2crfr, doyfr, cr_file=cr_file, cr_data=cr_data

if (not keyword_set(cr_file)) then cr_file='axlv2\cr_table.dat'

restore, file='axlv2\cr_table_template.save'
cr_data = read_ascii(cr_file, template=template)

return, crfr
end

