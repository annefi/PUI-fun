
;  ************************************************
;  *                                              *
;  * file:      correct_swics_data.pro            *
;  *                                              *
;  * author:                                      *
;  *            Lars Berger                       *
;  *            <berger@physik.uni-kiel.de>       *
;  *                                              *
;  * version:   1.00                              *
;  *                                              *
;  * rev. date: 19.09.2005                        *
;  *                                              *
;  * Program to determine corretion-functions to  *
;  * fix 5th bit problem in ToF for ACE/SWICS.    *
;  *                                              *
;  *                                              *
;  *                                              *
;  *                                              *
;  ************************************************

PRO corr_swics;

;**************************
;***** Initialisation *****
;**************************

XDIM_DATA = 1024
YDIM_DATA = 256
XBIN = 1
YBIN = 1
XDIM = XDIM_DATA / XBIN
YDIM = YDIM_DATA / YBIN
X_RANGE = intarr(2)
Y_RANGE = intarr(2)

status = 0
MINEDB = 1
MAXEDB = 1
MINASPANG = 7
MAXASPANG = 7
peak_sum = 0.
peak_soll_sum = 0.
whole_sum = fltarr(XDIM,YDIM)
whole_sum[*] = 0.
whole_sum2 = fltarr(XDIM,YDIM)
whole_sum2[*] = 0.
read_et_mat = intarr(YDIM,(XDIM_DATA))
et_mat = intarr(((MAXASPANG-MINASPANG)+1),(XDIM_DATA),YDIM)
numberions = 0
xachs = intarr(XDIM)
yachs = intarr(XDIM)
plot_sum = fltarr(XDIM)
plot_sum_ech = fltarr(YDIM)
plot_sum_ech_bin = fltarr(YDIM/2)
FOR i = 0,(XDIM-1) DO BEGIN
	xachs[i] = i
	yachs[i] = 0
ENDFOR

;******************************************
;***** Start loop over EDBs	      *****
;******************************************

FOR step = MINEDB,MAXEDB DO BEGIN

;******************************************
;***** Start loop over Aspect-Angle   *****
;******************************************

	FOR aspint = MINASPANG,MAXASPANG DO BEGIN
 
		temp1 = ''
		temp2 = 0 
		temp3 = 0
		temp4 = 0.
		temp5 = 0.

;************************************************
;***** Names for in- and output are created *****
;************************************************
;***** namer and namew must contain path    *****
;***** and base for filenames + ending      *****
;***** complete Format e.g. for namer :     *****
;***** /home/ivar/berger/ = path            *****
;***** axlv2_sumwhol_asp_ = base            *****
;***** 00.0-01.0.dat      = ending          *****
;************************************************

		;***** path and base are set 
		;***** namew is created later, see Output : ps-file

		namer = '/home/ivar/berger/work/subversion/amerika/runs/2000138-2005198_accum_aspang/axlv2_sumwhol_asp_'	
		;***** ending is created and added.

		PRINT,'aspint = ',aspint
		
		call_procedure,'int2str',aspint-1,tmp2
		call_procedure,'int2str',aspint,tmp4

		namer = namer + tmp2 + '.0-' + tmp4 + '.0.dat'

;************************
;***** Data is read *****
;************************

		;***** idl reads x = colums, y = rows 
		;***** therefor plot_mat is used to switch x and y around
		;***** if necessary for plotting; Plotting for ACE/SWICS should
		;***** have format x = 1024 ToFch and y = 256 Ech

		PRINT, 'loading', namer
		OPENR,1,namer

;************************************************
;***** E-T-Matrix wird geladen              *****
;************************************************ 

		FOR k = 0,step DO BEGIN
			READF,1,tmp10,tmp11
			READF,1,read_et_mat	
		ENDFOR

		FOR l = 0,(YDIM-1) DO BEGIN
			FOR m = 0,(XDIM_DATA-1) DO BEGIN
				et_mat[(aspint-MINASPANG),m,l] = read_et_mat[l,m]
			ENDFOR
		ENDFOR
		
		CLOSE,1

	ENDFOR  

;************************************************
;***** Binning E-T-Matrix                   *****
;************************************************ 

	et_mat_bin = intarr(((MAXASPANG-MINASPANG)+1),XDIM,YDIM)

	FOR k = MINASPANG,MAXASPANG DO BEGIN
		FOR i = 1,(XDIM-1) DO BEGIN
			FOR j = 0,(YDIM-1) DO BEGIN
				et_mat_bin[(k-MINASPANG),i,j] = 0
				FOR l = 0,(XBIN-1) DO BEGIN
					et_mat_bin[(k-MINASPANG),i,j]+= et_mat[(k-MINASPANG),((i*XBIN)-l),j]
				ENDFOR
			ENDFOR
		ENDFOR
	ENDFOR

; Loop over aspint for data input ends here

	nameplot='test.ps'
	X_RANGE [0] = 200/XBIN
	X_RANGE [1] = 700/XBIN
	Y_RANGE [0] = 0/YBIN
	Y_RANGE [1] = 100/YBIN
	OUTPUTMAT = intarr(XDIM,YDIM)
	OUTPUTMAT[*,*] = et_mat_bin[0,*,*]

	call_procedure,'plot_et_mat',X_RANGE,Y_RANGE,OUTPUTMAT,nameplot

	nameplot='test2.ps'
	X_RANGE [0] = 200
	X_RANGE [1] = 700
	Y_RANGE [0] = 0
	Y_RANGE [1] = 100
	OUTPUTMAT = intarr(XDIM_DATA,YDIM_DATA)
	OUTPUTMAT[*,*] = et_mat[0,*,*]

	call_procedure,'plot_et_mat',X_RANGE,Y_RANGE,OUTPUTMAT,nameplot
		

;***************************
;***** Output : Screen *****
;***************************
	
	plot_sum[*] = 0.
		
	FOR l = 0,(XDIM-1) DO BEGIN

		tmp = 0.

		FOR m = 1,(YDIM-1) DO BEGIN
			tmp = tmp + FLOAT(et_mat_bin[0,l,m])
		ENDFOR

		IF (tmp GE 1.) THEN BEGIN
			plot_sum[l] = tmp
		ENDIF ELSE BEGIN
			plot_sum[l] = 1.
		ENDELSE

	ENDFOR
	
	plot_sum_ech[*] = 0.
	plot_sum_ech_bin[*] = 0.

	FOR l = 0,(YDIM-1) DO BEGIN
		
		tmp = 0.

		FOR m = 140,180 DO BEGIN
			tmp = tmp + FLOAT(et_mat_bin[0,m,l])
		ENDFOR

		IF (tmp GE 1.) THEN BEGIN
			plot_sum_ech[l] = tmp
		ENDIF ELSE BEGIN
			plot_sum_ech[l] = 1.
		ENDELSE

	ENDFOR
		
	FOR l = 0,((YDIM/2)-2) DO BEGIN
		FOR i = 0,1 DO BEGIN
			plot_sum_ech_bin[l] += plot_sum_ech[(l*2)+i]
		ENDFOR
	ENDFOR

;------ Plot des E-Spektrums wird erzeugt


	stat=1
	SET_PLOT,'X'
	loadct,0
	WHILE (stat EQ 1) DO BEGIN

;		DEVICE,DECOMPOSED=0
		ERASE,(YDIM-1)
		PLOT,xachs,plot_sum_ech_bin,XRANGE=[30,40],XSTYLE=1,YSTYLE=1,$
			XTITLE='ECH channel',$
			YTITLE='Counts',$
			POS=[0.1,0.1,0.9,0.9],$			
			CHARSIZE=1.5,$
			BACKGROUND=(YDIM-1),$;!P.Color,$
			COLOR=0;!P.Background
	
		CURSOR, temp4, temp5, /DOWN	
			
		IF (!MOUSE.BUTTON EQ 1) THEN BEGIN
			stat = 0
		ENDIF
	ENDWHILE	

	stat=1
	SET_PLOT,'X'
	loadct,0

	WHILE (stat EQ 1) DO BEGIN

;		DEVICE,DECOMPOSED=0
		ERASE,(YDIM-1)
		PLOT,xachs,plot_sum_ech,XRANGE=[60,80],XSTYLE=1,YSTYLE=1,$
			XTITLE='ECH channel',$
			YTITLE='Counts',$
			POS=[0.1,0.1,0.9,0.9],$			
			CHARSIZE=1.5,$
			BACKGROUND=(YDIM-1),$;!P.Color,$
			COLOR=0;!P.Background
	
		CURSOR, temp4, temp5, /DOWN	
			
		IF (!MOUSE.BUTTON EQ 1) THEN BEGIN
			stat = 0
		ENDIF
	ENDWHILE	

;------ Plot des T-Spektrums wird erzeugt

	intervall = 30

	stat = 1
	i = -1
	tmpparam = fltarr(120)
	tmpparam[*] = 0.

	SET_PLOT,'X'
	loadct,0
	WHILE (stat EQ 1) DO BEGIN

;		DEVICE,DECOMPOSED=0
		ERASE,(YDIM-1)
		PLOT,xachs,plot_sum,XRANGE=[intervall-30,intervall],XSTYLE=1,YSTYLE=1,$
			XTITLE='ToF channel',$
			YTITLE='Counts',$
			POS=[0.1,0.1,0.9,0.9],$			
			CHARSIZE=1.5,$
			BACKGROUND=(YDIM-1),$;!P.Color,$
			COLOR=0;!P.Background

		!MOUSE.BUTTON = 0

		i = i + 1

		IF (i LT 30) THEN BEGIN 		
			PRINT,i+1,' Click Peak position and Peak high'  
			CURSOR, temp4, temp5, /DOWN
			PRINT,'x : ',temp4
			PRINT,'y : ',temp5
		ENDIF ELSE BEGIN
			i = i - 1
			stat = 0
		ENDELSE

;----- Linke Maustaste -> x-wert = peak position, y-wert = peak high 

		IF (!MOUSE.BUTTON EQ 1) THEN BEGIN
			call_procedure,'fitfunc',xachs,tmpparam,tmpfit_sum
			temp6 = FIX(temp4)
			tmpparam[(i*4)] = FLOAT(temp6)
			tmpparam[(I*4)+3] = FLOAT(temp5) - tmpfit_sum[(i*4)]
			PRINT,i+1,' Left sigma '

			CURSOR, temp4, temp5, /DOWN
			PRINT,'x : ',temp4
			PRINT,'y : ',temp5

			IF (!MOUSE.BUTTON EQ 1) THEN BEGIN
				tmpparam[(i*4)+1] = tmpparam[(i*4)] - FLOAT(temp4)
			ENDIF
			IF ((!MOUSE.BUTTON EQ 2) OR (!MOUSE.BUTTON EQ 4)) THEN BEGIN
				tmpparam[(i*4)+1] = 3.
			ENDIF
		
			PRINT,i+1,' Right sigma '

			CURSOR, temp4, temp5, /DOWN
			PRINT,'x : ',temp4
			PRINT,'y : ',temp5

			IF (!MOUSE.BUTTON EQ 1) THEN BEGIN
				tmpparam[(i*4)+2] = FLOAT(temp4) - tmpparam[(i*4)]
			ENDIF
			IF ((!MOUSE.BUTTON EQ 2) OR (!MOUSE.BUTTON EQ 4)) THEN BEGIN
				tmpparam[(i*4)+2] = 4.
			ENDIF
			
  			PRINT,i+1,' Peak position : ', tmpparam[(i*4)]
			PRINT,i+1,' Peak high     : ', tmpparam[(i*4)+3]
			PRINT,i+1,' Left sigma    : ', tmpparam[(i*4)+1]
			PRINT,i+1,' Right sigma   : ', tmpparam[(i*4)+2]

			!MOUSE.BUTTON = 0 
		ENDIF

;----- Mittlere Maustaste -> Intervall wird nach rechts verschoben.

		
		IF (!MOUSE.BUTTON EQ 2) THEN BEGIN
			intervall = intervall + 15
			i = i - 1
			PRINT,'Nächstes Intervall!'  
		ENDIF

;----- Rechte Maustaste -> Positionsbestimmung beendet!						

		IF (!MOUSE.BUTTON EQ 4) THEN BEGIN
			stat = 0
			PRINT,'Positionsbestimmung beendet, ',i,' Peaks gefunden.'  
			i = i - 1
		ENDIF

	ENDWHILE
	
	WDELETE,0

	IF (i EQ -1) THEN BEGIN
		GOTO,ende	
	ENDIF

	param = fltarr((i+1)*4)

	NUMFIT = i+1
	
	FOR k = 0,((NUMFIT*4)-1) DO BEGIN
		param[k] = tmpparam[k]	
	ENDFOR

	fit_sum = fltarr(XDIM)
	fit_sum[*] = 0.
	t_sum = fltarr(XDIM)
	t_sum[*] = 0.
	fitted_sum = fltarr(XDIM)
	fitted_sum[*] = 0.		
	diff_sum = fltarr(XDIM)
	diff_sum[*] = 0.

;****************************************************
;***** Start loop over Aspect-Angle for fitting *****
;****************************************************

	FOR aspint = MINASPANG,MAXASPANG DO BEGIN

		FOR l = 0,(XDIM-1) DO BEGIN

			tmp = 0.

			FOR m = 1,(YDIM-1) DO BEGIN
				tmp = tmp + FLOAT(et_mat_bin[(aspint-MINASPANG),l,m])
			ENDFOR

			IF (tmp GE 1.) THEN BEGIN
				t_sum[l] = tmp
			ENDIF ELSE BEGIN
				t_sum[l] = 0.
			ENDELSE

		ENDFOR

		fit_sum = t_sum

;		FOR i = 1,31 DO BEGIN
;			fit_sum[i*32] = t_sum[(i*32)+1]
;			fit_sum[(i*32)-1] = t_sum[(i*32)-2]
;			fit_sum[(i*32)+16] = t_sum[(i*32)+17]
;			fit_sum[(i*32)+15] = t_sum[(i*32)+14]
;		ENDFOR

;		FOR i = 500,511 DO BEGIN
;			fit_sum[i] = ((2.*t_sum[1029-i])+t_sum[1030-i]) / 3.
;		ENDFOR	
		
;		FOR i = 700,(XDIM-1) DO BEGIN
;			fit_sum[i] = 0
;		ENDFOR
	
		weights = fltarr(XDIM)

		FOR i = 0,(XDIM-1) DO BEGIN
			weights[i] = 1.
		ENDFOR
		
		fit_param = param
		FOR i = 0, NUMFIT-1 DO BEGIN
			fit_param[(i*4)+3] = 0.
		ENDFOR

		FOR i = 0, NUMFIT-1 DO BEGIN
			call_procedure,'fitfunc',xachs,fit_param,startfit_sum
			pos0 = FIX(fit_param[(i*4)])
;			PRINT,i*4,' :',pos0
			fit_param[(i*4)+3] = fit_sum[pos0] - startfit_sum[pos0]
			FOR K = 0,3 DO BEGIN
;				PRINT,((i*4)+k),' : ',fit_param[(i*4)+k]
			ENDFOR 
		ENDFOR
		bla =''
		READ,bla	
;		call_procedure,'fitfunc',xachs,fit_param,startfit_sum
		
		use_param = intarr(NUMFIT*4)
		FOR i = 0,NUMFIT-1 DO BEGIN
			use_param[*] = 0
			FOR k = 0,3 DO BEGIN
				use_param[(i*4)+k] = 1
			ENDFOR

;			FOR j = 0,NUMFIT-1 DO BEGIN
;				IF (fit_param[(i*4)] LE fit_param[(j*4)]) THEN BEGIN
;					IF ((fit_param[(i*4)]+(fit_param[(i*4)+2]*4.)) GE fit_param[(j*4)]) THEN BEGIN
;						FOR k = 0,3 DO BEGIN
;							use_param[(j*4)+k] = 1
;						ENDFOR
;					ENDIF
;				ENDIF
;			ENDFOR

			FOR j = 0,((NUMFIT*4)-1) DO BEGIN
				IF (use_param[j] NE 0) THEN BEGIN
;					PRINT,'use_param[',j,'] : ',use_param[j],'  ; fit_param[',j,'] : ',fit_param[j]
				ENDIF					
			ENDFOR

			IF ((fit_param[(i*4)]+(fit_param[(i*4)+2]*5.)) GT FLOAT(XDIM-1)) THEN BEGIN
				rightb = (XDIM-1)
			ENDIF ELSE BEGIN
				rightb =FIX(fit_param[(i*4)]+(fit_param[(i*4)+2]*5.))
			ENDELSE

			IF ((fit_param[(i*4)]-(fit_param[(i*4)+1]*5.)) LT 0.) THEN BEGIN
				leftb = 0
			ENDIF ELSE BEGIN
				leftb =FIX(fit_param[(i*4)]-(fit_param[(i*4)+1]*5.))
			ENDELSE
 			IF (rightb LE 0) THEN rightb = 0
			IF (leftb LE 0) THEN leftb = 0
			IF (rightb LE leftb) THEN rightb = leftb 
			xfitdim = rightb - leftb + 1
			IF (xfitdim LE 0) THEN xfitdim = 1
			PRINT,'main : xfitdim = ',xfitdim
			xfit = fltarr(xfitdim)
			yfit = fltarr(xfitdim)
			tmp_fit = fltarr(xfitdim)
			weights = fltarr(xfitdim)
			tmp_index = 0
			FOR j = leftb,rightb DO BEGIN
				xfit[tmp_index] = FLOAT(j)
;				PRINT,'xfit[',tmp_index,'] : ',xfit[tmp_index]				
				yfit[tmp_index] = fit_sum[j]
;				PRINT,'yfit[',tmp_index,'] : ',yfit[tmp_index]
				IF (yfit[tmp_index] NE 0) THEN BEGIN
					weights[tmp_index] = 1. / yfit[tmp_index]
				ENDIF ELSE BEGIN
					weights[tmp_index] = 1.
				ENDELSE	
			tmp_index = tmp_index + 1
			ENDFOR
			chisqu = 0.
			status = 0
			tmp_fit = CURVEFIT2(xfit,yfit,weights,fit_param,FITA=use_param,FUNCTION_NAME='fitfunc',ITMAX=30,/NODERIVATIVE,TOL=0.1,CHISQ=chisqu,STATUS=status)
			PRINT,'CHISQ = ',chisqu
		ENDFOR

		call_procedure,'fitfunc',xachs,fit_param,fitted_sum

		PRINT,'Aspect Angle intervall : ',aspint

		FOR i = 0,((NUMFIT*4)-1) DO BEGIN
;			PRINT,'Parameter,',i,' : ',param[i]
;			PRINT,'Parameter ',i,' : ',fit_param[i]
		ENDFOR	

		FOR i = 0,(XDIM-1) DO BEGIN
			diff_sum[i] = t_sum[i] - fit_sum[i]
		ENDFOR
		
;		tmpsum = 0
;		FOR i = 0,10 DO BEGIN
;			tmpsum = tmpsum + diff_sum[i+501]
;		ENDFOR

;		peak_sum = peak_sum + t_sum[512]
;		peak_soll_sum = peak_soll_sum + fitted_sum[512]
;		PRINT,'PEAK = ', diff_sum[512]
;		PRINT,'SUM  = ', tmpsum 

		whole_sum = whole_sum + diff_sum
		whole_sum2 = whole_sum2 + t_sum 


;****************************
;***** Output : PS-File *****
;****************************
	
		SET_PLOT,'ps',/copy,/interpolate
	
;------ Plot des T-Spektrums wird erzeugt

		call_procedure,'int2str',aspint-1,tmp2
		call_procedure,'int2str',aspint,tmp4

		nameplot ='Gaussfit400-600_' + tmp2 + '-'+ tmp4 + '.ps' 
		X_RANGE[0] = 500/XBIN
		X_RANGE[1] = 520/XBIN
				
		call_procedure,'plot_t_spec',X_RANGE,fit_sum,fitted_sum,nameplot

	ENDFOR

	SET_PLOT,'ps',/copy,/interpolate

;------ Plot des T-Spektrums wird erzeugt
	
	namew ='16Gaussfit400-600_whole.ps' 
	DEVICE,FILE=namew, YSIZE=21.,XSIZE=29.,YOFFSET=29.,XOFFSET=0.,/LANDSCAPE
	PLOT,whole_sum,XRANGE=[0,50],$
	TITLE=namew,LINESTYLE = 0,THICK = 3,POS=[0.1,.1,0.9,0.9]

	whole_sum3 = fltarr(XDIM)
	whole_sum3[*] = SQRT(whole_sum2[*]) * 3.

	OPLOTERR,yachs,whole_sum3		

	OPLOT,yachs,THICK=3,LINESTYLE=2

;	xlin = fltarr(12)
;	xlin = [500.,501.,502.,503.,504.,505.,506.,507.,508.,509.,510.,511.]
;	ylin = fltarr(12)
;	FOR i = 500,511 DO BEGIN
;		ylin[i-500] = whole_sum[i]
;	ENDFOR
;	xpara = fltarr(12)
;	xpara =[0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.]
;	paramparafit = [0.,1.,1.,0.,0.,-100.]
;	ylinfit = fltarr(12)
;	linparam = LINFIT(xlin,ylin,YFIT=ylinfit)
	
;	OPLOT,xlin,ylinfit,THICK=3,LINESTYLE=2
;	yparafit = GAUSSFIT(xpara, ylin , paramparafit, NTERMS=6) 
	
;	OPLOT,xlin,yparafit,THICK=3,LINESTYLE=3

;	FOR i = 0,11 DO BEGIN
;		PRINT,i+500,' : ',yparafit[i]
;	ENDFOR
;	PRINT,'512 soll: ',peak_soll_sum
;	PRINT,'512 ist : ',peak_sum
;	tmpsum = 0.
;	FOR i = 1,11 DO BEGIN
;		PRINT,i+500,' : ',(-yparafit[i] / peak_sum)
;		tmpsum = tmpsum + yparafit[i]
;	ENDFOR
;	PRINT,(tmpsum - peak_soll_sum)
	
	DEVICE,/CLOSE	


;*******************************************************
;***** Starting loop for correction of channel 512 *****
;*******************************************************

	FOR step = 31,31 DO BEGIN

		aspint = 8
;		step = 31

		;***** path and base are set 
		;***** namew is created later, see Output : ps-file

		namer = '/home/ivar/berger/work/subversion/amerika/runs/2000138-2005198_accum_aspang/axlv2_sumwhol_asp_'	
		;***** ending is created and added.
		PRINT,'aspint = ',aspint

		call_procedure,'int2str',aspint-1,tmp2
		call_procedure,'int2str',aspint,tmp4

		namer = namer + tmp2 + '.0-' + tmp4 + '.0.dat'


;************************
;***** Data is read *****
;************************

		;***** idl reads x = colums, y = rows 
		;***** plot_mat is used to switch x and y around
		;***** if necessary for plotting; Plotting for ACE/SWICS should
		;***** have format x = 1024 ToFch and y = 256 Ech

		et_mat = intarr(YDIM_DATA,XDIM_DATA)
		plot_mat = intarr(XDIM_DATA,YDIM_DATA)

		PRINT, 'loading', namer
		OPENR,1,namer


;************************************************
;***** E-T-Matrix wird geladen              *****
;************************************************ 

		FOR k = 0,step DO BEGIN
			READF,1,tmp10,tmp11
			READF,1,et_mat	
		ENDFOR

;		step = 'E/q-Step '+ step

		FOR l = 0,(YDIM-1) DO BEGIN
			FOR m = 0,(XDIM-1) DO BEGIN
				plot_mat[m,l] = et_mat[l,m]
			ENDFOR
		ENDFOR
		close,1
		
		plot_mat_bak = plot_mat


;************************************************
;***** Kanal 512 wird korrigiert            *****
;************************************************

		
;		randomnumbers = fltarr(YDIM,10000)
		time = SYSTIME(/SECONDS)
;		randomnumbers = RANDOMU(time,[YDIM,10000])

		NUMFIT = (11)

		wahrsch = fltarr(NUMFIT)
		wahrsch = [0.220,0.203,0.160,0.124,0.094,0.069,0.051,0.036,0.024,0.014,0.005]
;		wahrsch = [0.134,0.130,0.120,0.110,0.1,0.09,0.08,0.07,0.06,0.05,0.04,0.03,0.02,0.01,0.01]
	
		wahrsch2 = fltarr(512,2)
		wahrsch2[*,*] = 0.
		wahrsch2[0,0] = 1.
		FOR l = 1,511 DO BEGIN
			mittel = (whole_sum[(l*2)] + whole_sum[(l*2)-1]) / 2.
			tmp0   = whole_sum[(l*2)] - mittel
			wahrsch2[l,0] = (whole_sum2[(l*2)] - tmp0) / whole_sum2[(l*2)]
			wahrsch2[l,1] = tmp0 / whole_sum2[(l*2)]
;			PRINT,'p',l*2,' = ',wahrsch2[l,0],'p',(l*2)-1,' = ',wahrsch2[l,1]
		ENDFOR
			mittel = (whole_sum[(480)] + whole_sum[(479)]) / 2.
			tmp0   = whole_sum[(480)] - mittel
;			PRINT,'mittel = ',mittel
;			PRINT,'tmp0   = ',tmp0
;			PRINT,'480    = ',whole_sum2[480]
;			PRINT,'479    = ',whole_sum2[479]
				
		
		plot_sum2 = fltarr(XDIM)
	
		FOR l = 0,(XDIM-1) DO BEGIN
			xachs[l] = l
			yachs[l] = 1
			tmp = 0.
			FOR m = 1,(YDIM-1) DO BEGIN
				tmp = tmp + FLOAT(plot_mat[l,m])
			ENDFOR

			IF (tmp GE 1) THEN BEGIN
				plot_sum2[l] = tmp
			ENDIF ELSE BEGIN
				plot_sum2[l] = 1.
			ENDELSE

		ENDFOR

		totassignedcounts = 0.
		totcounts = 0.

		
		FOR m = 1,511 DO BEGIN

			FOR i = 0,(YDIM-1) DO BEGIN

				assignedcounts = 0.
				tmpcounts = plot_mat[m*2,i]
				plot_mat[m*2,i] = 0
				time = SYSTIME(/SECONDS)
				IF (tmpcounts GT 0) THEN randomnumbers = RANDOMU(time,[1,tmpcounts])

				FOR j = 0,tmpcounts-1 DO BEGIN

					tmprand = randomnumbers[0,j]

					IF (tmprand LE wahrsch2[m,0]) THEN BEGIN
						plot_mat[(m*2),i] = plot_mat[(m*2),i] + 1
						assignedcounts = assignedcounts + 1.
					ENDIF ELSE BEGIN
						IF (tmprand GT wahrsch2[m,0]) THEN BEGIN
							plot_mat[(m*2)-1,i] = plot_mat[(m*2)-1,i] + 1
							assignedcounts = assignedcounts +1.
						ENDIF
					ENDELSE


;				FOR k = 0,(NUMFIT-1) DO BEGIN
;					IF (tmprand LE wahrsch[k]) THEN BEGIN
;						plot_mat[512-k,i] = plot_mat[512-k,i] + 1
;						assignedcounts = assignedcounts + 1.
;;						PRINT,k,' : ',tmprand,' wahrsch : ',wahrsch[k]	
;						PRINT, 'Count ',j,' assigned to ',(512-k)
;						k = NUMFIT
;					ENDIF ELSE BEGIN
;						IF ((tmprand GT wahrsch[k]) AND (k LT NUMFIT)) THEN BEGIN
;;							PRINT,k,' : ',tmprand,' wahrsch : ',wahrsch[k]
;							tmprand = tmprand - wahrsch[k]
;						ENDIF
;					ENDELSE
;					
;				ENDFOR
;;				IF (tmpcounts GT 0) THEN BEGIN
;;					PRINT,'tmpcounts = ', tmpcounts
;;					PRINT,'assigned counts = ', assignedcounts
;;				
;;				ENDIF
	
				ENDFOR
				totassignedcounts = totassignedcounts + assignedcounts
				totcounts = totcounts + FLOAT(tmpcounts)
;				plot_mat[512,i] = plot_mat[521,i] + (tmpcounts-assignedcounts)

			ENDFOR		
			
;		PRINT,'Corrected columns ' ,2*m, ' and ', (2*m)-1

		ENDFOR

;		PRINT,'total counts to assign = ',totcounts
;		PRINT,'total counts assigned  = ',totassignedcounts 

		FOR l = 0,(XDIM-1) DO BEGIN

			xachs[l] = l
			yachs[l] = 1
			tmp = 0.
			FOR m = 1,(YDIM-1) DO BEGIN
				tmp = tmp + FLOAT(plot_mat[l,m])
			ENDFOR

			IF (tmp GE 1) THEN BEGIN
				plot_sum[l] = tmp
			ENDIF ELSE BEGIN
				plot_sum[l] = 1.
			ENDELSE

		ENDFOR

		SET_PLOT,'ps',/copy,/interpolate

;------ Plot des T-Spektrums wird erzeugt
	
	call_procedure,'int2str',step,tmp2

	namew ='corrected_sum_'+ tmp2 + '.ps' 
	DEVICE,FILE=namew, YSIZE=21.,XSIZE=29.,YOFFSET=29.,XOFFSET=0.,/LANDSCAPE
	PLOT,plot_sum2,XRANGE=[400,600],$
;YRANGE=[1,100000],$
	TITLE=namew,LINESTYLE = 3,THICK = 3,POS=[0.1,.1,0.9,0.9]
;,/YLOG


	OPLOT,plot_sum,THICK=3
	whole_sum3[*] = SQRT(plot_sum2[*])*3.
	OPLOTERR,plot_sum,whole_sum3

	DEVICE,/CLOSE	

ENDFOR


;****************************
;***** Output : ps-file *****
;****************************

	nameplot='corrected_data.ps'
	X_RANGE [0] = 0
	X_RANGE [1] = 1024
	Y_RANGE [0] = 0
	Y_RANGE [1] = 256
	OUTPUTMAT = intarr(XDIM_DATA,YDIM_DATA)
	OUTPUTMAT[*,*] = et_mat[0,*,*]

	call_procedure,'plot_et_mat',X_RANGE,Y_RANGE,OUTPUTMAT,nameplot

ENDFOR

ende:

END
