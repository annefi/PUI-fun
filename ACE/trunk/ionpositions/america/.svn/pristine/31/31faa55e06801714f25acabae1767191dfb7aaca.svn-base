; Filename: prob_range.pro
;
; Description:
;   Plot distributions of random numbers and assignment to simulated
;   ions from prob_range.cc
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   12Aug2003   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001

datfile = "prob_range_data.dat"
psfile  = "prob_range_data.ps"
NSPECIES = 3

restore, file='prob_range_data_template.save'
d = read_ascii(datfile, template=template)
niter = n_elements(d.iter)

title="Simulations for swindal::ProbRates"
subtitle="Iterations: "+string(niter)
psplt, file=psfile, /color
loadct, 34
fix_ct_ends

;; plot random number distribution
binsize = 0.01
x = findgen(1.0/binsize)*binsize
h = histogram(d.dice_roll, binsize=binsize)
h = float(h)/niter

plot, x, h, ytitle='Distribution of dice_roll', title=title, psym=10,$
  subtitle=subtitle
tagplot, line1='prob_range.pro', line2=psfile

;; plot assignment distribution
x = indgen(NSPECIES)
h = histogram(d.s, min=0)
h = float(h)/niter

plot, x, h, ytitle='Distribution of species assignment',xtitle='species',$
  title=title, psym=10, subtitle=subtitle
tagplot, line1='prob_range.pro', line2=psfile

;; plot probabilities
p = [.12, .65, .23] ;; taken from prob_range.cc
plot, x, p, ytitle='Probability of species', xtitle='species',$
  color=255,psym=10, title=title, subtitle=subtitle
tagplot, line1='prob_range.pro', line2=psfile

ficlose
end
