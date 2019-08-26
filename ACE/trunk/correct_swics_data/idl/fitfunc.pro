PRO fitfunc, x, A, value   

	temp = SIZE(A,/DIMENSIONS)
	NUMFIT = FIX(temp[0])
;	PRINT,'DIM : ',NUMFIT
	FOR i = 0,NUMFIT-1 DO BEGIN
;		PRINT,'fitfunc_param[',i,'] : ', A[i]
	ENDFOR
	NUMFIT = (NUMFIT/4)
;	PRINT,'NUMGAUSS : ',NUMFIT
	temp = SIZE(x,/DIMENSIONS)
	XDIM = FIX(temp[0])
	pos = fltarr(XDIM,NUMFIT)
	tmp = fltarr(XDIM)
	tmp[*] = 0.

	NUMFIT = NUMFIT - 1
	XDIM = XDIM - 1

;	PRINT,'Starting FITFUNC : x[',x[0],',',x[XDIM-1],']'	
		
	FOR i = 0,NUMFIT DO BEGIN
		pos[*,i] = x[*] - A[(i*4)]
	ENDFOR

;	PRINT,'pos = ',pos[22,1]

	FOR i = 0,XDIM DO BEGIN
		FOR j = 0,NUMFIT DO BEGIN
			IF (pos[i,j] LE 0.) THEN BEGIN
				pos[i,j] = pos[i,j] / A[(j*4)+1]	
			ENDIF ELSE BEGIN
				pos[i,j] = pos[i,j] / A[(j*4)+2]
			ENDELSE
		ENDFOR
	ENDFOR

	FOR i = 0,NUMFIT DO BEGIN
		pos[*,i] = pos[*,i] * pos[*,i]
		pos[*,i] = pos[*,i] / 2.
		pos[*,i] = -pos[*,i]
	ENDFOR

	FOR j = 0,XDIM DO BEGIN
		FOR i = 0,NUMFIT DO BEGIN
			IF (pos[j,i] GT -12.5) THEN  tmp[j] = tmp[j] + A[(i*4)+3] * EXP(pos[j,i])
		ENDFOR
	ENDFOR

;		FOR j = 0,XDIM DO BEGIN
;			IF (tmp[j] GT 0.1) THEN value[j] = value[j] + tmp[j]
;			PRINT,i,' value[',j,'] = ',value[j] 
;		ENDFOR

	value = tmp

;	PRINT,'Leaving FITFUNC'
;	FOR i = 0,XDIM DO BEGIN
;		PRINT,'value[',i,'] = ',value[i]
;	ENDFOR

END