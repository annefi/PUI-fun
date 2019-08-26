function plot_positions, lmargin=lmargin, rmargin=rmargin, $
                    tmargin=tmargin, bmargin=bmargin, $
                    nplots=nplots

positions = make_array(nplots, 4)

;; change to x coordinate
rmargin = 1.0 - rmargin

parea = 1.0 - tmargin - bmargin
pheight = parea / nplots

for nplot=0,nplots-1 do begin
  ;; x0
  positions[nplot,0] = lmargin
  ;; y0
  positions[nplot,1] = bmargin + nplot*pheight
  ;; x1
  positions[nplot,2] = rmargin
  ;; y1
  positions[nplot,3] = bmargin + (nplot+1)*pheight
endfor

return, positions
end
