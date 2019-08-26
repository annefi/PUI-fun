; Filename: plot_positions_cols.pro
;
; Description:
;   Calculate positions for multiple plots on page suitable for
;   positions keyword to plot.  This version arranges plots in columns
;   across the page (a single row).
;
; Author: Jim Raines (jmr)
;         Dustin Doud (dd)
;
; Method:
;
; Revision controlled by CVS:
; $Id: plot_positions_cols.pro,v 1.1 2004/03/29 20:00:01 jraines Exp $
;   
; Major Modification History
;   08Jan2003   jmr    adapted from plot_positions.pro
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   [lrtb]margin page margins in fraction of the page
; I   nplots       number of plots per page
; O   [returned]   array of position arrays [x0,y0,x1,y1]
;                  where (x0,y0) is lower left corner
;                  and (x1,y1) is upper right corner

function plot_positions_cols, lmargin=lmargin, rmargin=rmargin, $
                    tmargin=tmargin, bmargin=bmargin, sep=sep, $
                    nplots=nplots

positions = make_array(nplots, 4)

;; change from margin sizes to position in normal coordinates
lbound = lmargin
rbound = 1.0 - rmargin          ; unused
bbound = bmargin
tbound = 1.0 - tmargin

parea = 1.0 - lmargin - rmargin
pwidth = (parea - sep*(nplots-1)) / nplots

for nplot=0,nplots-1 do begin
  ;; x0
  positions[nplot,0] = lbound + nplot*pwidth + nplot*sep
  ;; y0
  positions[nplot,1] = bbound
  ;; x1
  positions[nplot,2] = lbound + nplot*sep + (nplot+1)*pwidth
  ;; y1
  positions[nplot,3] = tbound
endfor

return, positions
end
