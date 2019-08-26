; Filename: switch_x_labels.pro
;
; Description:
;   Turn on and off for easy strip plot printing, where x labels are
;   off except on bottom plot.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: switch_x_labels.pro,v 1.3 2005/06/29 20:02:48 jraines Exp $
; 
; Usage:
;
;   Set up all formatting and such on the !x object then issue
;   'switch_x_labels, /save'.  Issue 'switch_x_labels, /off' for all
;   plots until the bottom one.  Then, issue 'switch_x_labels, /on' to
;   turn on your formatting.
;
; Major Modification History
;   31Jan2005   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; [I] save        save !x structure for 'on' later
; [I] on          turn on x labels according to formatting in !x object
; [I] off         turn off x labels
pro switch_x_labels, save=save, on=on, off=off

common switch_x_labels, bang_x

if (keyword_set(save)) then bang_x = !x

if (keyword_set(on) and keyword_set(bang_x)) then !x = bang_x

if (keyword_set(off)) then begin
  !p.subtitle = ''

  !x.title='' 
  !x.tickname=[' ',' ']
  !x.ticks=1
  !x.tickformat = ''
  !x.minor = 0
endif  

return
end


