; matrixmmq.pro -- color contour plotting routine
; Arik Posner, 2Feb00
;
; Modification history
;   Adapted for my use.  J. Raines, 3Feb00

;-----------------------------------------------------
; ===> parameters -- user should probably alter these
;-----------------------------------------------------

; directory where input files reside
rootdir = '/home/jraines/wind/libsms/examples/Perl/'  

; data file 
datfile = 'mmq.19990909.tmqh-c'

; output file for matrix 
outfile = 'matrixmmq.dat'

; ps file
psfile = 'matrixmmq.ps'

; number of not data lines at beginning of file
nheader = 3
;-------------------------------
; plot set up and general init.
;-------------------------------

; set up plot stuff
a=0
set_plot,'ps'&erase
device,filename=rootdir + psfile,xoffset=2.,yoffset=25.,xsize=22.,ysize=16.,$
/color,bits=8,/landscape       ;customizing output
!p.multi=[0,1,1]
!p.font = 0
DEVICE,/TIMES
!p.thick=5.0
!p.charsize=0.9
!x.charsize=1.4
!y.charsize=1.4
!x.minor=10
loadct,39
xx=dblarr(2)&yy=dblarr(2)&zz=dblarr(2)
xx(0)=0.1&xx(1)=0.1&yy(0)=0.1&yy(1)=0.1
plot_oo,xx,yy,xrange=[0.3,50],yrange=[0.1,100],PSYM=3,xstyle=1,ystyle=1,$
xtitle='m/q [amu/e]',ytitle='m [amu]',xticklen=-0.005,/nodata,$ 
yticklen=-0.003,title='Wind/SMS/STICS m-m/q-Matrix'
headint=''                                 ;empty plot
date=''
s0dat=0.
sdat=dblarr(8)
pi=3.14159265358

; change to right dir
cd, rootdir

; restore template
restore, filename=rootdir + 'tmqh-c-template.save'

; init variables
sr=0&br=''&year=0&day=0&time=''&vs=0.&dvs=0.&h=0.&he2=0.&he1=0.&br0=0.&br1=0.
br2=0.&fsr12=0.&fsr34=0.&fsr56=0.&o1=0.&o6=0.&o7=0.
hour=0.&mi=0.&sec=0.&gtime=0.
bigar=lonarr(500,1000)   ;m-m/q-array m/q 0-50, m 0-100, 0.1 steps

;--------------
; data reading
;--------------
print, 'Reading in data...'

; read in data
d = read_ascii(datfile, template=template)

;-------------------------------------------
; classify and put into matrix for plotting
;-------------------------------------------
imax = size(d.mq, /dimensions)
for i=0,(imax(0) - 1) do BEGIN
  IF mass GT 0. AND mass LT 99.95 THEN BEGIN
    IF mq GT 0. AND mq LT 49.95 THEN BEGIN
      bigar(fix(10.*d.mq+0.5),fix(10.*d.m+0.5))=$
        bigar(fix(10.*d.mq+0.5),fix(10.*d.m+0.5))+1 ;sham's m/q
    ENDIF
  ENDIF
endfor

;===>
print, 'DEBUG exit...'
end
;********************end readsection************************************
name=rootdir + outfile
print,'Sending output matrix to ',name
openw,unit,name,/variable,/get_lun
   printf,unit,bigar                       ;save m-m/q-matrix in ascii-format
free_lun,unit                                                    
FOR a=0,499 DO BEGIN
 FOR b=0,999 DO BEGIN
  IF bigar(a,b) GT 255 THEN bigar(a,b)=255   ;colortable adjust
 ENDFOR
ENDFOR
xx=dblarr(4)&yy=dblarr(4)
FOR a=0.,499. DO BEGIN
 xx(0)=(a/10.)
 xx(1)=(a+1.)/10.
 xx(2)=xx(1)
 ;IF xx(0) LT 0.1 THEN xx(0)=0.1
 xx(3)=xx(0)
 FOR b=0,999 DO BEGIN
  yy(0)=b/10.
  yy(1)=b/10.
  yy(2)=(b+1)/10.
  yy(3)=(b+1)/10.
  IF a GT 2 AND b GT 0 THEN BEGIN
   polyfill,xx,yy,color=255-bigar(a,b)        ;plotting 
  ENDIF
 ENDFOR
ENDFOR


;print,halt
device,/close
end

