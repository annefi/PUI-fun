; Filename: smmq_fig.pro
;
; Description:
;   Make MMQ figure for publication.
;
; Author: Jim Raines (jmr) 
;
; Method:
;
; Revision controlled by CVS:
; $Id: smmq_fig.pro,v 1.1 2005/03/14 16:53:40 jraines Exp $
;
; Major Modification History
;   08Jan2003   jmr  initial coding
;
; Arguments (optional in [])
;
; I/O Arg           Explanation
; --- ----------    -----------
; I   file          Name of postscript output file
pro smmq_fig, file=psfile

thisprog = 'smmq_fig'

;; set up plot format and arrangement
npp = 2
!p.multi = [npp, npp, 1]

psplt, file=psfile, /color
Positions = plot_positions_cols(lmargin=0.03,rmargin=0.03,$
                           tmargin=0.03,bmargin=0.42,sep=-.07, nplots=npp)


print, format='("plot 0 x: ",F6.2," - ",F6.2)',Positions[0,0],Positions[0,2]
print, format='("plot 1 x: ",F6.2," - ",F6.2)',Positions[1,0],Positions[1,2]

device, /landscape , encapsulated=0
!p.charsize = 1.3
!p.charthick = 2.5
!p.thick = 3.0

!x.style = 1
!x.thick = 2.0
!x.ticks = 3

!y.style = 1
!y.thick = 2.0
!y.ticks = 4

;; do plots

;smmq_pub, file='../a-2003298/axlv2_mmq.dat', $
;  center_file='../a-2003298/axlv2_mmq_fmc.dat', $
;  tag='Adding labels', title='25-Oct-2003', position=Positions[nplot,*]

;; plot raw data
nplot = 0
smmq_pub, file='axlv2_mmq_010_96.dat', $
  center_file='axlv2_mmq_fmc.dat', $
  tag='Adding labels', title='Raw counts', position=Positions[nplot,*]


;ficlose
;return

;; sum assigned counts (plots also but we don't care here)
pattern='axlv2_acmmq_elem_[0-9]*.dat'

;; get list of files
spawn, 'ls -1 '+pattern, files
nfiles = n_elements(files)

for ifile = 0, nfiles-1 do begin

  print, thisprog+' -I- reading from file '+files[ifile]
  read_smmq, file=files[ifile], smmq=smmq_ts

  if (ifile eq 0) then begin
    smmq = smmq_ts
  endif else begin
    
    smmq.mmq = smmq.mmq + smmq_ts.mmq

    if (ifile eq nfiles-1) then $
      smmq.file = smmq.file+' - '+smmq_ts.file
  
  endelse

endfor

;; hard code labels
smmq.title = 'Counts assigned to carbon'
smmq.mqtitle = 'm/q'
smmq.mmtitle = 'mass'

;; do actual assigned counts plot
nplot = nplot + 1
read_fmc, file='axlv2_mmq_fmc.dat', fmc=centers, ions=ions,$
  eqtab=eoqtable
plot_smmq_pub, smmq=smmq, centers=centers, $
  tag='2005009', position=Positions[nplot,*]

ficlose

;return
end

