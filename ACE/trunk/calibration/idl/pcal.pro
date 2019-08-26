PRO pcal

namer = "/home/ivar/berger/projects/SWICS/calibration/idl/tofcal.dat"

tmp = ""
tmp1 = 0
tmp2 = 0
sum = 0LL
range = 0

OPENR,1,namer

WHILE (~ EOF(1)) DO BEGIN
	READF,1,tmp
	range = range + 1
ENDWHILE

CLOSE,1

range = range -1

xval = intarr(range)
yval = intarr(range)
ynorm = fltarr(range)

OPENR,1,namer

FOR i = 0,range-1 DO BEGIN
	READF,1,tmp1,tmp2
	xval[i]=tmp1
	yval[i]=tmp2
	sum = sum + yval[i]
	IF (yval[i] LE 0) THEN PRINT,"WARNING!!!",yval[i]
ENDFOR

norm = 0.
norm = float(range)/float(sum)
PRINT,"norm = ",norm
FOR i = 0,range-1 DO BEGIN
	ynorm[i]= yval[i]*norm
ENDFOR

CLOSE,1

plot,xval,ynorm,COLOR=!P.BACKGROUND,BACKGROUND=!P.COLOR,XRANGE=[480,530]
;,YRANGE=[0,5000]

END