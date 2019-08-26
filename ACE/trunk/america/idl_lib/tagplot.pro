; Filename: tagplot.pro
;
; Description:
;   Put a 4 line tag on the lower right corner of a plot.  Lines 1-3 are 
;   arguments, defaulting to null.  Line 4 is the date and time that the
;   plot was created.  (Time may be optionally excluded.)
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: tagplot.pro,v 1.9 2005/02/01 14:54:36 jraines Exp $
;
; Major Modification History
;   10Jul2003   jmr   made line3 default to contents of IDL_USER_INFO var.
;   19May2003   jmr   changed hardcoded name to 'line3' argument
;   13Dec2002   jmr   adapted from hardcopy.pro
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; [I]   line1,2,3   Text of the first three lines of the tag, 30 char. max 
; [I]   notime      date only (no time) on last line 
; [I]   time        No operation; provided for backward compatibility
; [I] [dir]       set line2 as last MAXLEN characters of current
;                 working dir.
; [I] /off        turn off tag plotting for this IDL session (useful
;                 for final draft on publication work)
; [I] /on         turn on routine for this IDL session
pro tagplot, line1=line1, line2=line2, line3=line3, notime=notime, $
             time=time, dir=dir, on=on, off=off

;; maximum characters per line
MAXLEN = 30

;; ----------------------------------------------------------------------
;; toggle printing of tag 
;; ----------------------------------------------------------------------
common tagplot, run_already, state

if (not keyword_set(run_already)) then  begin
  run_already = 1
  state = 1                     ; default to 'on'
endif

if (keyword_set(on)) then begin 
  state=1
  message, /info, ' -I- tag plotting enabled in this IDL session'
  return
endif

if (keyword_set(off) or not keyword_set(state)) then begin 
  state=0
  message, /info, ' -I- tag plotting *DISABLED* in this IDL session'
  return
endif

;; ----------------------------------------------------------------------
;; determine line content
;; ----------------------------------------------------------------------

if (not keyword_set(line1)) then line1 = ''
if (not keyword_set(line2)) then begin
  if (keyword_set(dir)) then begin
    spawn, 'pwd', dir
    line2 = strmid(dir,strlen(dir)-MAXLEN,MAXLEN)
  endif else line2 = ''
endif
if (not keyword_set(line3)) then begin
  ;; get user info
  spawn, 'echo $IDL_USER_INFO', USER_INFO
  line3 = USER_INFO
endif

if ((strlen(line1) gt MAXLEN) or (strlen(line2) gt MAXLEN)) then begin
  print, 'tagplot -W- line too long, max = ' + string(format='(I2)',MAXLEN)
endif

;; ----------------------------------------------------------------------
;; write label to graphics device
;; ----------------------------------------------------------------------
out = STRARR(4)
out(0) = line1
out(1) = line2
out(2) = line3
if (keyword_set(notime)) then begin
  out(3) = STRMID(!stime,0,11)  ; date only
endif else begin
  out(3) = !stime               ; date and time
endelse

for k = 0,3 do XYOUTS, 0.95, -0.015*k, out(k), /normal, size=0.5

return
end


