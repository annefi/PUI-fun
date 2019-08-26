; Filename: rp_axmr.pro
;
; Description:
;   Read and plot axmr.pl output.
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;   30May2002   jmr   adapted from rp_dbd.pro
;   15Feb2002   jmr   initial coding
;
; Usage note: no file keyword allows printing a number of days to one
; big file; nopercyc keyword set disables indiv. cycle plots, only
; daily aves.
pro rp_axmr, file=file, data=d, noread=noread

if (not keyword_set(noread)) then begin
  ; tag_names(d) = YEARDOY EDB EOQ FSR TCR MR0 MR1 MR2 MR3 MR4 MR5 MR6 MR7
  restore, file='axmr-template.save'
  d = read_ascii(file,template=template)
endif

; set up PS output
dot = strpos(file, '.', /reverse_search)
base = strmid(file, 0, dot)  ; name without extension
psfile = base + '.ps'
psplt, file=psfile, /color
!p.multi = [0,1,5]

; make list of days in this file
days = d.yeardoy(uniq(d.yeardoy))
ndays = n_elements(days)

; set up numerical output
get_lun, lun
datfile = 'rp_axmr'+ string(format='(I7,"-",I7)',days[0],days[ndays-1]) $
  + '.txt'
openw, lun, datfile

; set up common plot features
horiz0 = 0.05                   ; left margin
horiz1 = 0.95                   ; right margin
vert0  = 0.05                   ; bottom margin
vert1  = 0.95                   ; top margin
spacer = 0.02                   ; space between plots
nplots = 5                      ; number of plots per page
!p.multi = [0,1,nplots]         
ht = (vert1-vert0-(spacer*(nplots-1)))/nplots ; height of each plot as page fraction
xtickname = ['','','','','','','','']

for nydoy=0,ndays-1 do begin ; loop over days
  ydoy = days(nydoy)
  print, 'working on day ' , ydoy

  i = where( d.yeardoy eq days(nydoy) , ni)

  eoq = d.eoq(i)                ; used in daily average below, 
                                ; should all be same anyway

  plotno = 0
  plot, eoq, d.fsr(i), $
    xtickname=xtickname, xticks=1, $
    ytitle='FSR (counts)', $
    position=[horiz0, vert1-(plotno+1)*ht-(spacer*plotno), $
              horiz1, vert1- plotno*ht-(spacer*plotno)], $
    title='ACE/SWICS Daily Sum Rate Spectra'

  plotno = 1
  plot, eoq, d.tcr(i) , $
    xtickname=xtickname, xticks=1, $
    position=[horiz0, vert1-(plotno+1)*ht-(spacer*plotno), $
              horiz1, vert1- plotno*ht-(spacer*plotno)], $
    ytitle='TCR (counts)'

  plotno = 2
  plot, eoq, d.mr0(i), $
    xtickname=xtickname, xticks=1, $
    position=[horiz0, vert1-(plotno+1)*ht-(spacer*plotno), $
              horiz1, vert1- plotno*ht-(spacer*plotno)], $
    ytitle='MR0(H+) (counts)'

  plotno = 3
  plot, eoq, d.mr1(i), $
    xtickname=xtickname, xticks=1, $
    position=[horiz0, vert1-(plotno+1)*ht-(spacer*plotno), $
              horiz1, vert1- plotno*ht-(spacer*plotno)], $
    ytitle='MR1(He2+) (counts)'


  plotno = 4
  plot, eoq, d.mr7(i), $
    xtitle='E/q (keV/e)', $
    position=[horiz0, vert1-(plotno+1)*ht-(spacer*plotno), $
              horiz1, vert1- plotno*ht-(spacer*plotno)], $
    ytitle='MR7(Err) (counts)', $
    subtitle='day is ' + string(format='(I0)',ydoy)

  ; write some data to file
  ;printf, lun, format='(I7,x)', ydoy
  ;pntmat = fltarr(4,n_elements(eoq))
  ;pntmat(0,*) = eoq
  ;pntmat(1,*) = dcrda
  ;pntmat(2,*) = br03da
  ;pntmat(3,*) = br03diffda
  ;printf, lun, format='(4f10.2)',pntmat

endfor

hardcopy, printer='file', label='rp_axmr.pro', file=psfile

; tidy up output data file
close, lun
free_lun, lun

!p.multi = 0  ; resets it

return
end
