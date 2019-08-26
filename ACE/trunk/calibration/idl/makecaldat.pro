PRO makecaldat

close,1
close,2

tmp = ""
tmp1 = 0
tmp2 = 0
tmp3 = 0.
npha1 = 0LL
npha2 = 0LL
npha = 0LL

path = "/home/ivar/berger/projects/SWICS/trunk/calibration/"

namer = path + "ramp1_cut.pha"
namer2 = path + "ramp1ii.pha"
namew = path + "tofcal.dat"
namew2 = path + "rampg.pha"

OPENR,1,namer

READF,1,tmp
READF,1,tmp
READF,1,tmp

WHILE (~ EOF(1)) DO BEGIN

	READF,1,tmp
	npha1 = npha1 + 1
	
ENDWHILE

CLOSE,1

PRINT,"npha1 = ",npha1
pha1 = intarr(npha1)

OPENR,1,namer

READF,1,tmp
READF,1,tmp
READF,1,tmp

FOR i = 0LL,npha1-1 DO BEGIN

	READF,1,tmp3,tmp3,tmp3,tmp3,tmp3,tmp3,tmp1,tmp2,tmp1
	;PRINT,"tmp2 = ",tmp2
	pha1[i] = tmp2	

ENDFOR
CLOSE,1

;***********

OPENR,1,namer2

READF,1,tmp
READF,1,tmp
READF,1,tmp

WHILE (~ EOF(1)) DO BEGIN

	READF,1,tmp
	npha2 = npha2 + 1
	
ENDWHILE

CLOSE,1

pha2 = intarr(npha2)

OPENR,1,namer2

READF,1,tmp
READF,1,tmp
READF,1,tmp

FOR i = 0LL,npha2-1 DO BEGIN

	READF,1,tmp1,tmp2,tmp1
	pha2[i] = tmp2	

ENDFOR
CLOSE,1

;*****

npha = npha1 + npha2

PRINT,"npha = ",npha
pha = intarr(npha)

FOR i = 0LL,npha1-1 DO BEGIN
	pha[i]=pha1[i]
ENDFOR
FOR i = npha1,npha1+npha2-1 DO BEGIN
	pha[i]=pha2[i-npha1]
ENDFOR


OPENW,2,namew2
FOR i = 0,npha-1 DO BEGIN
	PRINTF,2,i,"  ",pha[i]
ENDFOR


xrange = 1002 - 105 + 1
PRINT,"xrange = ",xrange

xpha = intarr(xrange)
ypha = intarr(xrange)
ypha[*] = 0 

FOR i = 0, xrange -1 DO BEGIN
	xpha[i] = 105 + i
ENDFOR

FOR j = 0, xrange-1 DO BEGIN
	FOR i = 0LL, npha-1 DO BEGIN
		IF (pha[i] EQ xpha[j]) THEN ypha[j] = ypha[j]+1
	ENDFOR
ENDFOR

OPENW,2,namew
FOR i = 0,xrange-1 DO BEGIN
	PRINTF,2,xpha[i],"  ",ypha[i]
ENDFOR

close,2
plot,xpha,ypha


END		


 

