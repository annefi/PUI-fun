PRO stat;

;**************************
;***** Initialisation *****
;**************************

real = intarr(2)
erg = intarr(1000,6)
tmp1 = ''
tmp2 = 0
tmp3 = 0
tmp4 = 0
tmp5 = 0
tmp6 = 0
tmp7 = 0

nsvd1 = intarr(1000)
nsvd2 = intarr(1000)
nvst1 = intarr(1000)
nvst2 = intarr(1000)
nmax1 = intarr(1000)
nmax2 = intarr(1000)	
hsvd1 = intarr(1000)
hsvd2 = intarr(1000)
hvst1 = intarr(1000)
hsvd2 = intarr(1000)
hmax1 = intarr(1000)
hmax2 = intarr(1000)

i = 0
namew = 'stat.ps'

;*************************************
;***** stat1000.dat wird geladen *****
;*************************************

PRINT, 'stat1000.dat'
OPENR,1,'./stat1000_1000_50.dat'

READF,1,tmp1
READF,1,real
READF,1,tmp1

FOR i = 0,999 DO BEGIN
	READF,1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7
	nsvd1[i] = tmp2
	nsvd2[i] = tmp3
	nvst1[i] = tmp4
	nvst2[i] = tmp5
	nmax1[i] = tmp6
	nmax2[i] = tmp7
ENDFOR

CLOSE,1

;***********************************
;***** Histogramm wird erzeugt *****
;***********************************

;FOR i = 0, 999 DO BEGIN
;	nsvd1[i] = erg[i,0]
;	nsvd2[i] = erg[i,1]
;	nvst1[i] = erg[i,2]
;	nvst2[i] = erg[i,3]
;	nmax1[i] = erg[i,4]
;	nmax2[i] = erg[i,5]
;ENDFOR
;FOR i = 0, 999 DO BEGIN
;	PRINT,nsvd1[i],nsvd2[i],nvst1[i],nvst2[i],nmax1[i],nmax2[i]
;ENDFOR


hsvd2 = HISTOGRAM(nsvd2,LOCATION = x)
hmax2 = HISTOGRAM(nmax2,LOCATION = y)
;WINDOW,1
;x = x - real[1]
;y = y - real[1]
;plot,y,hsvd2,COLOR = !P.BACKGROUND,BACKGROUND = !P.COLOR
;oplot,x,hmax2,COLOR = 50000
;READ,tmp1
;WDELETE,1


;****************************
;***** Output : ps-file *****
;****************************

	SET_PLOT,'ps',/copy,/interpolate
	
	DEVICE,FILE=namew,/LANDSCAPE, /COLOR $ 
;BITS_PER_PIXEL=8 
	,YSIZE=19.,XSIZE=29.$
	,YOFFSET=0.,XOFFSET=0.
	;,/ENCAPSUL
	;!P.MULTI=[0,1,3]
	;indgen, z,100
	;indgen, z2,100

	PLOT,y,hsvd2,XTITLE='Results',YTITLE='Number of Fits',COLOR=150
	;,XRANGE=[0,40]
	OPLOT,x,hmax2
	;,COLOR=100

	DEVICE,/CLOSE
END
