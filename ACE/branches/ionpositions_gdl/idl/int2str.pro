PRO int2str, in, out

	tmp = STRING(in)
	IF (in LT 10) THEN BEGIN 
	tmp2 = STRMID(tmp,STRLEN(tmp)-1,1)
	tmp2 = '0' + tmp2
	ENDIF ELSE BEGIN
		tmp2 = STRMID(tmp,STRLEN(tmp)-2,2)
	ENDELSE
	out = tmp2

END 