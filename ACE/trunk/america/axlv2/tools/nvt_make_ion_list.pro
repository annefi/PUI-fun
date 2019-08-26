; Filename: nvt_make_ion_list.pro
;
; Description:
;   Make an ASCII ion list from an NVT file
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: nvt_make_ion_list.pro,v 1.1 2005/04/26 18:41:41 jraines Exp $
;
; Major Modification History
;   26Apr2005   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   nvt_file    nvt data file
; I   list_file   name of file into which to write list
;
pro nvt_make_ion_list, nvt_file=nvt_file, list_file=list_file

restore,file='axlv2_nvt_template.save'
d = read_ascii(nvt_file,template=template)

i_doyfr = where(d.doyfr eq d.doyfr[0])

spawn, 'date', date_str

get_lun, lun
openw, lun, list_file

printf, lun, "# Ions used in ACE/SWICS Lv2 v2.0 inversion"
printf, lun, "# Created: "+date_str
printf, lun, d.ion[i_doyfr]

close, lun
free_lun, lun
return
end
