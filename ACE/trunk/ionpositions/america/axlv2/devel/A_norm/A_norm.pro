;; figure out how to normalize A
;; Jim Raines, 20Aug2004

;; ===> configure <===
READ_DATA = 0


;; ===> end config <===

if (READ_DATA) then begin
  !p.multi=[0,3,3]
  spawn, 'ln -fs ~/ace/axlv2/tools/axlv2_rates_template.save .'

  file = '/home/jraines/ace/axlv2/runs/17Aug2004-switched-around-duty/8-print-sum-A'
  axlv2_distfunc, file=file, data=dnorm, tag='Norm', ions=['He2+']

  file = '/home/jraines/ace/axlv2/runs/17Aug2004-switched-around-duty/7-sue-n'
  axlv2_distfunc, file=file, data=d, tag='NOT_norm', ions=['He2+']

end

doyfr = 10.00
ion = 'He2+'

i = where(d.doyfr eq doyfr and d.ion eq ion, nwhere)

aq = dnorm.rate[i]/d.rate[i]

end 

