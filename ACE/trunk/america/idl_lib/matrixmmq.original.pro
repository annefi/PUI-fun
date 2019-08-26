a=0
set_plot,'ps'&erase
device,filename='matrixmmq.ps',xoffset=2.,yoffset=25.,xsize=22.,ysize=16.,$
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
filelists=findfile('hrd$tscr:[ap.l1]pha9*.dat',count=fcts)
print,filelists                     ;input PHA-files
sr=0&br=''&year=0&day=0&time=''&vs=0.&dvs=0.&h=0.&he2=0.&he1=0.&br0=0.&br1=0.
br2=0.&fsr12=0.&fsr34=0.&fsr56=0.&o1=0.&o6=0.&o7=0.
hour=0.&mi=0.&sec=0.&gtime=0.
bigar=lonarr(500,1000)   ;m-m/q-array m/q 0-50, m 0-100, 0.1 steps
;******************readsection********************************************
FOR opener=0,fcts-1 DO BEGIN
 openr,3,filelists(opener)
 print,filelists(opener)
 ;fi=strmid(filelists(opener),29,10)
 FOR header=0,21 DO BEGIN
  readf,3,headint
 ENDFOR
 WHILE a EQ 0 DO BEGIN
  ON_IOERROR,sbad
  readf,3,$
  FORMAT='(I9,A3,I6,I5,A10,I4,F9.2,I7,I13,I14,I10,I8,I10,I8,I8,F11.2,F8.1,I5,I5,I5)',$
sr,br,year,day,time,vs,epq,stopid,startid,ed,sector,ssdid,tof,start,range,$
mq,mass,nm,nq,nrg
  hour=FLOAT(STRMID(time,2,2))
  mi=FLOAT(STRMID(time,5,2))
  sec=FLOAT(STRMID(time,8,2))
  ;print,time,hour,mi,sec
  gtime=day+hour/24.+mi/1440.+sec/86400.
  ;print,gtime
  ;xx(0)=(1.*tof-44.)*1.0e-09/2.372530695&xx(1)=xx(0)
  ;yy(0)=epq&yy(1)=epq
  ;zz(0)=10.*(xx(0)/(0.1/sqrt(2.*epq*1000.*1.602e-19/1.661e-27)))^2.
  ;zz(1)=zz(0)       ;alternate m/q determination
  ;print,zz(0)
  ;oplot,zz,yy,psym=3
  IF mass GT 0. AND mass LT 99.95 THEN BEGIN
   IF mq GT 0. AND mq LT 49.95 THEN BEGIN
    ;bigar(fix(zz(0)+0.5),fix(10.*mass+0.5))=bigar(fix(zz(0)+0.5),vs)+1
    bigar(fix(10.*mq+0.5),fix(10.*mass+0.5))=$
    bigar(fix(10.*mq+0.5),fix(10.*mass+0.5))+1   ;sham's m/q
    ;IF bigar(fix(zz(0)+0.5),vs) GT 255 THEN bigar(fix(zz(0)+0.5),vs)=255
   ENDIF
  ENDIF
 ENDWHILE
 sbad:print,a
 close,3
ENDFOR
;********************end readsection************************************
name='hrdia$dkb0:[hrdusr.ap.stics]matrixmmql1.dat'
print,name
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

