; Filename: build_cr_data.pro
;
; Description:
;   Build Carrington rotation data structure (crd) that is used by
;   ydoyfr2crfr and crfr2ydoyfr.  NOTE:  This only needs to be run
;   when the CR data source file changes.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: build_cr_data.pro,v 1.2 2005/05/05 18:11:23 jraines Exp $
;
; Major Modification History
;   22Apr2005   jmr   Initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; [I] file        ascii file to process into the structure used by
;                 ydoyfr2crfr and crfr2ydoyfr.
; [O] data        optionally specify a variable for returning the CR
;                 data structure
;
; Sample usage:
;
; IDL> build_cr_data, file=file, data=crd
;
pro build_cr_data, file=file, data=crd

;; read data
restore, file='/shrg1/local/idl_lib/cr_table_template.save'
crdo = read_ascii(file, template=template)
num_cr_data = n_elements(crdo.cr)

;; set up CR data structure
crd_element = $
  { carr_rot_data1    , $       ; structure name
    cr: 0L            , $       ; Carrington rotation
    ydoyfr: 0.0D0       $       ; year, day of year (fraction) at start of cr
  }

crd = replicate(crd_element, num_cr_data) 

for ndat=0,num_cr_data-1 do begin
  ;; store Carrington rotation
  crd[ndat].cr = crdo.cr[ndat]

  ;; change month number into string
  months = ['','Jan','Feb','Mar','Apr','May','Jun','Jul','Aug',$
            'Sep','Oct','Nov','Dec']
  mon_str = months[crdo.month[ndat]]

  ;; convert dd-Mmm-yy to doy
  day_str = string(format='(I2.2)',crdo.day[ndat])
  year_str = string(format='(I4.4)',crdo.year[ndat])
  tmp = date2doy(day_str+'-'+mon_str+'-'+year_str)
  doy = tmp[1]
  
  ;; split the hh:mm:ss into three, separate, integer columns then
  ;; convert to fraction of day
  hms_str = strsplit(crdo.hms[ndat], ':', /extract)
  hms_int = make_array(3, /int, value=0)
  for j=0,2 do begin
    hms_int[j] = fix(hms_str[j])
  endfor
  frac = hms2fr(hms_int)

  ;; finally, form ydoyfr
  crd[ndat].ydoyfr = float(year_str)*1000. + float(doy) + frac

endfor

;; save file for later
file_parse, file=file, base=base
save_file = base + '.save'
save, file=save_file, crd

return
end
