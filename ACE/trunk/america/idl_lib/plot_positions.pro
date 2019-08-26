; Filename: plot_positions.pro
;
; Description:
;   Calculate positions for multiple plots on page suitable for
;   positions keyword to plot.
;
; Author: Jim Raines (jmr)
;         Dustin Doud (dd)
;
; Method:
;
; Revision controlled by CVS:
; $Id: plot_positions.pro,v 1.4 2004/07/21 21:04:58 jraines Exp $
;   
; Major Modification History
;   18Sep2003   jmr/dd   initial coding
;   21Apr2004   jmr   used local variables to avoid changing arguments
;                     after remembering that IDL is call-by-reference
;   21Jul2004   jmr   added 'separation' keyword
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   [lrtb]margin page margins in fraction of the page
; I   nplots       number of plots per page
; I   [separation] separation between plots, defaults to 0
; O   [returned]   array of position arrays [x0,y0,x1,y1]
;                  where (x0,y0) is lower left corner
;                  and (x1,y1) is upper right corner
;

function plot_positions, lmargin=lmargin, rmargin=rmargin, $
                    tmargin=tmargin, bmargin=bmargin, $
                    nplots=nplots, separation=sep

if (not keyword_set(sep)) then sep = 0.

positions = make_array(nplots, 4)

;; change to x coordinate
local_rmargin = 1.0 - rmargin

parea = 1.0 - tmargin - bmargin - (nplots-1)*sep
pheight = parea / nplots

for nplot=0,nplots-1 do begin
  ;; x0
  positions[nplot,0] = lmargin
  ;; y0
  positions[nplot,1] = bmargin + nplot*(pheight+sep)
  ;; x1
  positions[nplot,2] = local_rmargin
  ;; y1
  positions[nplot,3] = bmargin + (nplot+1)*pheight + nplot*sep
endfor

return, positions
end
