; Filename: filter_nvt_by_qual.pro
;
; Description:
;   Filter axlv2 NVT data by quality measures.  This is to be used in
;   conjunction with development of deliv. nvt filter and when
;   un-filtered nvt data is used for studies
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: filter_nvt_by_qual.pro,v 1.3 2005/04/01 20:06:36 jraines Exp $
;
; Major Modification History
;   ddmmmyyyy   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   nvtdata     nvt data structure
; [I] error_level optionally specify error level
; [I] vth         filter vth based on this factor when compared with fit_vth

pro filter_nvt_by_qual, nvtdata=nvt, error_level=error_level, $
  vth_level=vth_level

if (not keyword_set(error_level)) then error_level = .50

if (error_level eq -1.) then return

print, 'bing!'

;; filter out n/vth when density error exceeds maximum
;; (also filters out n FILL values)
i_bad = where((nvt.cnt_err gt error_level) or (nvt.n lt 0.), nwhere)
if (nwhere ge 1) then begin
  nvt.n[i_bad] = 0.0
  nvt.vth[i_bad] = -1.0
endif

;; filter out vth FILL values
i_bad = where(nvt.vth lt 0., nwhere)
if (nwhere ge 1) then begin
  nvt.vth[i_bad] = 0.0
endif

if (keyword_set(vth_level)) then begin
  ;; calculate number of channels by which vth and fit_vth differ
  comp_vth = 2*abs(nvt.vth - nvt.fit_vth)/(.064*nvt.v)
  i_bad = where((comp_vth gt vth_level), nwhere)

  if (nwhere ge 1) then begin
    nvt.vth[i_bad] = 0.0
  endif
endif

return
end

