; Filename: file_parse.pro
;
; Description:
;   Parse a unix-style filename (file) into directory (dir), base name
;   (base) and extension (ext).
;
; Author: Jim Raines (jmr)
;
; Method:
;   Note: extension is string after last dot.
;   
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   [dir]       variable in which to return directory
; O   [base]       variable in which to return base filename
; O   [ext]       variable in which to return extension
; O   [split_base] variable in which to return parts of base, split by
;                  sb_str
; I   [sb_str]    string on which to split base, default: '_'

; Major Modification History
;   12Dec2002   jmr   initial coding
;   24Jan2003   jmr   formalized and added extension removal
;

pro file_parse, file=file, dir=dir, base=base, ext=ext, debug=debug,$
                split_base=split_base, sb_str=sb_str

s = strsplit(file, '\/')
ns = n_elements(s)
base   = strmid(file,s[ns-1], strlen(file)-s[ns-1])
dir    = strmid(file,0, s[ns-1]-1) ; string before last /

if (keyword_set(debug)) then begin
  print, 'file_parse -I- printing debugging output:'
  print, 'fully-qualified file =', file
  print, 'dir = ', dir
  print, 'file without path = ', base
endif

s = strsplit(base, '.')
ns = n_elements(s)
ext  = strmid(base, s[ns-1], strlen(base)-s[ns-1])
base = strmid(base, 0, s[ns-1]-1)
if (keyword_set(debug)) then begin
  print, 'base = ', base
  print, 'ext = ', ext
endif

;; split base by string
if (not keyword_set(sb_str)) then sb_str = '_'
split_base = strsplit(base, sb_str, /extract)
if (keyword_set(debug)) then begin
  print, format='("base parts, split by ",A,", are: ")',sb_str
  for i=0,n_elements(split_base)-1 do begin
    print, split_base[i]
  endfor
endif


;return
end
