; Filename: plot_positions_bng.pro
;
; Description:
;   Calculate positions for multiple plots on page suitable for
;   positions keyword to plot.  This version produces positions for a
;   big and grid (bng) style plot, with one large plot on the top half
;   of the landscape page and lots of small plots (same type) in a
;   grid below.
;
; Author: Jim Raines (jmr)
;
; Method:
;
; Revision controlled by CVS:
; $Id: plot_positions_bng.pro,v 1.1 2005/03/14 16:53:40 jraines Exp $
;   
; Major Modification History
;   04Dec2003   jmr   adapted from plot_positions.pro
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   [lrtb]margin page margins in fraction of the page
; I   nplots       number of plots in grid
; O   [returned]   array of position arrays [x0,y0,x1,y1]
;                  where (x0,y0) is lower left corner
;                  and (x1,y1) is upper right corner
;                  Order in array is big plot first, then by row of
;                  small plots.
; I   [hv]space    horiz. and vertical spacing of grid plots

function plot_positions_bng, lmargin=lmargin, rmargin=rmargin, $
                    tmargin=tmargin, bmargin=bmargin, $
                    nplots=nplots, hspace=hspace, vspace=vspace,$
                         halfspace=halfspace, ncol=ncol, nrow=nrow

positions = make_array(nplots, 4)

vlen = 1.0 - tmargin - bmargin
hlen = 1.0 - lmargin - rmargin

;; dimensions of big plot on top
big_h = (vlen - halfspace)/2.0
big_w = hlen

;; dimensions for small plots
sm_h = (big_h - (nrow-1)*vspace)/nrow
sm_w = (big_w - (ncol-1)*hspace)/ncol

;; calculate positions for top plot
nplot = 0
;; x0
positions[nplot,0] = lmargin
;; y0
positions[nplot,1] = bmargin + big_h + halfspace
;; x1
positions[nplot,2] = lmargin + big_w
;; y1
positions[nplot,3] = bmargin + big_h + halfspace + big_h

;stop
for irow=0,nrow-1 do begin
  for icol=0,ncol-1 do begin
    nplot = nplot + 1

    ;; x0
    positions[nplot,0] = lmargin + icol*sm_w + icol*hspace
    ;; y0
    positions[nplot,1] = bmargin + (nrow-irow-1)*sm_h + (nrow-irow-1)*vspace
    ;; x1
    positions[nplot,2] = positions[nplot,0] + sm_w
    ;; y1
    positions[nplot,3] = positions[nplot,1] + sm_h
  endfor
endfor

return, positions
end
