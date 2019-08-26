;; This is an example of how to use Dave Ortland's color plot routine,
;; with some of my modifications.  J. Raines, 18Mar2003
pro color_plot_example

loadct, 34                      ;34 is Rainbow
fix_ct_ends                     ;make 0 - black and 1 - white
black = 0                       ;define color mnemonic for black
white = 1                       ;define color mnemonic for black

psfile = 'color_plot_example.ps'
psplt, file=psfile, /color      ; does the set_plot with some niceties

submat = make_array(5,5, /int)
submat = [[0,5,10,5,0],$
          [5,100,100,100,5],$
          [10,100,10000,100,10],$
          [5,100,100,100,5],$
          [0,5,10,5,0]]

;; color plot accepts most graphics keywords
title = "color_plot.pro example plot"
xtitle = 'channels'
x      = indgen(6)              ; for axis labeling
y      = indgen(6)              ; for axis labeling
ytitle = 'channels'
color_plot, submat, x, y, xtitle=xtitle,$
  ytitle=ytitle, title=title , $  
  zmin_color=white, $
  /fill
tagplot, line1='color_plot_example', line2=psfile  ; puts some info in lower 
                                           ; right corner of plot

ficlose                         ; does the ps file closing and set_plot back 
                                ; to X, with some niceties
return
end
