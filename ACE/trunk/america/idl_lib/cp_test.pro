;; This is a little routine to test color_plot under different
;; circumstances.  JMR, 24Mar2003
pro cp_test

loadct, 34                      ;34 is Rainbow
fix_ct_ends                     ;make 0 - black and 1 - white
black = 0                       ;define color mnemonic for black
white = 1                       ;define color mnemonic for black

psfile = 'cp_test.ps'
psplt, file=psfile, /color      ; does the set_plot with some niceties

submat = make_array(5,5, /int)
submat = [[0,5,10,5,0],$
          [5,100,100,100,5],$
          [10,100,10000,100,10],$
          [5,100,100,100,5],$
          [0,5,10,5,0]]

x = indgen(64)
y = indgen(64)
;; color plot accepts most graphics keywords
title = "color_plot.pro test plot"
xtitle = 'channels'
ytitle = 'channels'
color_plot, submat, x,y,  xtitle=xtitle,$
  ytitle=ytitle, title=title , $  
  zmin_color=white, $
  /fill
tagplot, line1='cp_test', line2=psfile  ; puts some info in lower 
                                           ; right corner of plot

ficlose                         ; does the ps file closing and set_plot back 
                                ; to X, with some niceties
return
end
