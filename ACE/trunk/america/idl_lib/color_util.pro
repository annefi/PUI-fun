; Filename: color_util.pro
;
; Description:
;   rgb2idx:
;   --------
;   Translates an RGB triplet of three 1-byte values into a long
;   integer in a manner appropriate for color specification in IDL.
;   The allows the specification of colors in terms of RGB values
;   which is much more intuitive than one single long integer.
;
;   decompose:
;   ----------
;   Reverse of rgb2idx.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   24Apr2002   jmr   Typed in from _Introduction to IDL, Training
;                     Course Manual_, Research Systems, 2000
;
function rgb2idx, rgb
  return, rgb[0] + (rgb[1]*2L^8) + (rgb[2]*2L^16)
end

function decompose, idx
  return, [decode(idx,0,7),decode(idx,8,15),decode(idx,16,23)]
end

FUNCTION decode,word,begbit,endbit

;+
; RSI TRAINING FILE HEADER
; FILE: decode.pro
; ROUTINE: decode
; PURPOSE: decode bits from a short or long word
; TOPICS: decoding
; CLASS: Intro/Intermediate
; REFERENCE:
; LAST MODIFIED: 09/30/99 - BL
; USAGE: decode
;-;
; decode - given word,beginning bit and number of bit, returns the value

compile_opt idl2
compile_opt hidden

retval=0l
j=0
for i=begbit,endbit do begin

	; if bit is on then add the value of the bit (wrt to bit offset) else set it
	; to zero
    if ((word mod 2l^(i+1))/(2l^i) eq 1) then begin
       addval=2l^j
    endif else begin
       addval=0
    endelse

    retval=retval+addval
    j=j+1

endfor
return,retval
end

