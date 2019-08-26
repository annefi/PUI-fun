;  ************************************************
;  *                                              *
;  * file:      ion_pos.pro                       *
;  *                                              *
;  * author:                                      *
;  *            Lars Berger                       *
;  *            <berger@physik.uni-kiel.de>       *
;  *                                              *
;  * version:   1.00                              *
;  *                                              *
;  * rev. date: 13.05.2005                        *
;  *                                              *
;  * Program to determine Ion-Species and         *
;  * positions for ACE/SWICS data.                *
;  *                                              *
;  *                                              *
;  *                                              *
;  *                                              *
;  ************************************************



PRO ion_pos;

;**************************
;***** Initialisation *****
;**************************



XDIM = 512
YDIM = 128

X_RANGE = intarr(2)
Y_RANGE = intarr(2)

tmpstat = 0
b = ''
bar = '**********************************'
;pathr = '/data/ivar/work/subversion/amerika/runs/2000138-2005198_accum_aspang/'
pathr = '/home/ivar/berger/projects/SWICS/trunk/databinning/'
pathw = '/home/ivar/berger/projects/SWICS/trunk/ionpositions/'
eingabe = ''
dataloaded = 'NA'
selectedeqstep = -1
i = 0

ionsdat_loaded = 0 
ionpos_loaded = 0

et_mat = fltarr(YDIM,XDIM)
et_mat_tmp = fltarr(YDIM,XDIM)
plot_mat = fltarr(XDIM,YDIM)

readdummystr = strarr(100)
readdummymass = fltarr(100)
readdummycharge = fltarr(100)
readdummytch = fltarr(100)
readdummyech = fltarr(100)
readdummypeak = fltarr(100)
readdummyvel = fltarr(100)

numberions = 0
temp1 = ''
temp2 = 0. 
temp3 = 0.
temp4 = 0.
temp5 = 0.
temp6 = 0.
temp7 = 0.
temp8 = ''
mproton = 1.661e-27
echarge = 1.602e-19
;;;;this is the real E/Q vector, since the first step is not used the array needs to be modified!
;;;;epq_arr = [100.012,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532]
epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532,0.55]

format_ion_pos_1 = '(A10,1x,F10.2,1x,F10.2,1x,F10.2,1x,F10.2,1x,F10.2,1x,F10.2)'
format_ion_pos_2 = '(A10,1x,A10,1x,A10,1x,A10,1x,A10,1x,A10,1x,A10)
format_ion_pos_3 = '(A11,I2,4x,A14,I2)'
format_ions_dat = '(A8,2x,F8.2,F8.2)'
format_show_pos1 = '(A10,1x,A10,1x,A10,1x,A10,1x,A10,1x,A10,1x,A10,1x,A10,1x,A10)'
format_show_pos2 = '(A10,1x,F10.2,1x,F10.2,1x,F10.2,1x,F10.2,1x,F10.2,1x,F10.2,1x,F10.2,1x,F10.2)'

;*********************************
;***** Mainmenu              *****
;*********************************

main:
	PRINT,bar
	PRINT,'Actually loaded data : ',dataloaded
	IF (selectedeqstep NE -1) THEN BEGIN
		PRINT,'Selected E/q-step    : ',selectedeqstep
	ENDIF ELSE BEGIN
		PRINT,'Selected E/q-step    : NA'
	ENDELSE
	PRINT,'Path for reading data        : ',pathr
	PRINT,'Path for writing ion_pos.dat : ',pathw

	IF (ionsdat_loaded) THEN BEGIN
		PRINT,'ions.dat loaded'
	ENDIF ELSE BEGIN
		PRINT,'ions.dat not loaded'
	ENDELSE

	IF (ionpos_loaded) THEN BEGIN
		PRINT,'ion_pos.dat loaded'
	ENDIF ELSE BEGIN
		PRINT,'ion_pos.dat not loaded'
	ENDELSE

	PRINT,bar
	PRINT,'Choose :'
	PRINT,'1 : load ions.dat'
	PRINT,'2 : load data'
	PRINT,'3 : load ion_pos.dat'
	PRINT,'4 : show ion_pos'
	PRINT,'5 : determine ion postions'
	PRINT,'6 : save positions'
	PRINT,'q : quit'
	READ,eingabe

	IF (eingabe EQ '1') THEN GOTO,load_ions
	IF (eingabe EQ '2') THEN GOTO,load_data
	IF (eingabe EQ '3') THEN GOTO,load_ion_pos
	IF (eingabe EQ '4') THEN GOTO,show_pos
	IF (eingabe EQ '5') THEN GOTO,determine_pos
	IF (eingabe EQ '6') THEN GOTO,save_pos
	IF (eingabe EQ 'q') THEN GOTO,quit

	eingabe= ''
	GOTO,main			 

;*********************************
;***** load ions.dat 	     *****
;*********************************

load_ions:

	PRINT,''
	PRINT,bar
	PRINT, 'loading ions.dat'
	OPENR,1,'./ions.dat'

	READF,1,temp1
	READF,1,numberions
	PRINT,'numberions = ', numberions
	READF,1,temp1
	READF,1,temp1

	ions_name = STRARR(numberions)
	ions_mass = FLTARR(numberions)
	ions_charge = FLTARR(numberions)
	ions_xpos = FLTARR(numberions)
	ions_ypos = FLTARR(numberions)
	ions_peak = FLTARR(numberions)
	ions_thxpos = FLTARR(numberions)
	ions_thypos = FLTARR(numberions)
	ions_velocity = FLTARR(numberions)
	ions_sigxp = FLTARR(numberions)
	ions_sigxm = FLTARR(numberions)
	ions_sigyp = FLTARR(numberions)
	ions_sigym = FLTARR(numberions)

	FOR k = 0,(numberions-1) DO BEGIN
		READF,1,temp1,temp4,temp5,FORMAT = format_ions_dat
		ions_name[k] = temp1
		ions_mass[k] = temp4
		ions_charge[k]= temp5
	ENDFOR

	CLOSE,1

	ionsdat_loaded = 1
	ionpos_loaded = 0

	PRINT,bar
	PRINT,''
	
	IF (tmpstat) THEN GOTO,load_data

	GOTO,main



;******************************************
;***** Data is loaded		      *****
;******************************************

load_data:

	tmpstat = 0

	IF (NOT ionsdat_loaded) THEN BEGIN
		PRINT,bar
		PRINT,'ions.dat not loaded -> loading ions.dat'
		tmpstat = 1
		GOTO,load_ions
	ENDIF
	
	aspint = 0
	READ,'Aspect Angle Intervall : ',aspint
	READ,'E/q step : ',i
	selectedeqsteptmp = i

;***** Because E/q-steps are shifted by -1 from axlv2 software i is decreased by 1
	i = i-1

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

	dataloadedtmp = 'axlv2_sumwhol_asp_'	
	
	;***** ending is created and added.
	PRINT,'aspint = ',aspint
	
	tmp = STRING(aspint-1)
	tmp3 = STRING(aspint)

	IF (aspint-1 LT 10) THEN BEGIN 
		tmp2 = STRMID(tmp,STRLEN(tmp)-1,1)
		tmp2 = '0' + tmp2
	ENDIF ELSE BEGIN
		tmp2 = strmid(tmp,STRLEN(tmp)-2,2)
	ENDELSE
	IF (aspint-1 LT 9) THEN BEGIN
		tmp4 = STRMID(tmp3,STRLEN(tmp3)-1,1)
		tmp4 = '0' + tmp4
	ENDIF ELSE BEGIN
		tmp4 = strmid(tmp3,STRLEN(tmp3)-2,2)
	ENDELSE

	dataloadedtmp = dataloadedtmp + tmp2 + '.0-' + tmp4 + '.0_bin.dat'
;	namer = namer + tmp2 + '.0-' + tmp4 + '.0_bin.dat'
	namer = pathr + dataloadedtmp
	namew = pathw + 'ion_pos_bin.dat'
;	namew = pathw + 'ion_pos_' + tmp2 + '.0-' + tmp4 + '.0_bin.dat'

;************************
;***** Data is read *****
;************************

	;***** idl reads x = colums, y = rows 
	;***** therefor plot_mat is used to switch x and y around
	;***** if necessary for plotting; Plotting for ACE/SWICS should
	;***** have format x = XDIM ToFch and y = YDIM Ech

	PRINT, 'loading', namer
	OPENR,1,namer,ERROR = err
	IF (err NE 0) THEN BEGIN
		PRINT,!ERROR_STATE.MSG
		CLOSE,1
		GOTO,main
	ENDIF


;************************************************
;***** E-T-Matrix wird geladen              *****
;************************************************ 

	FOR k = 0,i DO BEGIN
		IF (EOF(1)) THEN BEGIN
			CLOSE,1
			PRINT,'End of file encountered. No data is loaded!' 
			GOTO,main
		ENDIF
		READF,1,tmp10,tmp11
		IF (EOF(1)) THEN BEGIN
			CLOSE,1
			PRINT,'End of file encountered. No data is loaded!'
			GOTO,main
		ENDIF
		READF,1,et_mat_tmp	
	ENDFOR

	et_mat = et_mat_tmp
	tmp = STRING(i)

	IF (i LT 10) THEN BEGIN 
		tmp2 = STRMID(tmp,STRLEN(tmp)-1,1)
		tmp2 = '0' + tmp2
	ENDIF ELSE BEGIN
		tmp2 = strmid(tmp,STRLEN(tmp)-2,2)
	ENDELSE

	step = 'E/q-Step '+ tmp2
;	PRINT,'step : ',step

	FOR l = 0,YDIM-1 DO BEGIN
		FOR m = 0,XDIM-1 DO BEGIN
			plot_mat[m,l] = et_mat[l,m]
		ENDFOR
	ENDFOR

	plot_mat[*,0] = 0

	dataloaded = dataloadedtmp
	selectedeqstep = selectedeqsteptmp

;;	READ,'Delete ion positions ?',b

;;	IF (b EQ 'y') THEN BEGIN 
;;		ions_xpos[*] = 0.
;;		ions_ypos[*] = 0.
;;		ions_peak[*] = 0. 	
;;		ions_velocity[*] = 0.
;;		ionpos_loaded = 0
;;	ENDIF 
;;	b = ''

	CLOSE,1
	
;****************************************************************
;***** Theoretische Positionen aller Ionen werden berechnet *****
;****************************************************************

	PRINT,'Theor. positions are calculated'
	PRINT,bar

	FOR k = 0,(numberions-1) DO BEGIN
		
		va = SQRT((((epq_arr[selectedeqstep] + 23.5) * 1000. * ions_charge[k] * echarge) * 2.) / (ions_mass[k] * mproton) )
		ions_thypos[k] = (float(YDIM)/610.78) * ((epq_arr[selectedeqstep] + 23.5) * ions_charge[k])
		ions_thxpos[k] = (float(XDIM)/200.) * ((0.1 / va)/1e-09) 
		v0 = SQRT(((epq_arr[selectedeqstep] * echarge * ions_charge[k] * 1000.) * 2.) / (ions_mass[k] * mproton)) 
		ions_velocity[k] = (v0/1000.)
;		PRINT, ions_name[k], ions_thxpos[k], ions_thypos[k], (va/1000), ions_velocity[k]
	
	ENDFOR

	GOTO,main

;******************************
;***** load ion_pos_x.dat *****
;******************************

load_ion_pos:

	OPENR,1,namew,ERROR = err
	IF (err NE 0) THEN BEGIN
		PRINT,!ERROR_STATE.MSG
		CLOSE,1
		GOTO,main
	ENDIF

	FOR l= 0,(selectedeqstep-1) DO BEGIN

		eqtmp = 0
		numberionstmp = 0
		READF,1,temp1, eqtmp, temp1, numberionstmp, FORMAT = format_ion_pos_3
		READF,1,temp1

		FOR k = 0,(numberionstmp-1) DO BEGIN
			READF,1,temp1,temp4,temp5,temp2,temp3,temp6,temp7, FORMAT = format_ion_pos_1
			readdummystr[k] = temp1
			readdummymass[k] = temp4
			readdummycharge[k] = temp5
			readdummytch[k] = temp2
			readdummyech[k] = temp3
			readdummypeak[k] = temp6
			readdummyvel[k] = temp7
;			PRINT,readdummystr[k],readdummymass[k],readdummycharge[k],readdummytch[k],readdummyech[k],readdummypeak[k], readdummyvel[k], FORMAT = format_ion_pos_1
		ENDFOR

		READF,1,temp1

	ENDFOR

	CLOSE,1

	FOR  i = 0,(numberionstmp-1) DO BEGIN
		
		FOR k = 0,(numberions-1) DO BEGIN
;			PRINT,readdummystr[i],ions_name[k]	
			IF (readdummystr[i] EQ ions_name[k]) THEN BEGIN
				ions_mass[k] = readdummymass[i]
				ions_charge[k] = readdummycharge[i]
				ions_xpos[k] = readdummytch[i]
				ions_ypos[k] = readdummyech[i]
				ions_peak[k] = readdummypeak[i]
				ions_velocity[k] = readdummyvel[i]
				PRINT,k,ions_name[k],ions_mass[k],ions_charge[k],ions_xpos[k],ions_ypos[k],ions_peak[k],ions_velocity[k]
			ENDIF

		ENDFOR
	ENDFOR
 
	ionpos_loaded = 1	

	GOTO,main	

;******************************
;***** Show ion positions *****
;******************************
	
show_pos:
	
	PRINT,bar
	PRINT,'NAME','MASS','CHARGE','THXPOS','THYPOS','XPOS','YPOS','PEAK','VELO.',FORMAT = format_show_pos1

	FOR i = 0,(numberions-1) DO BEGIN
		PRINT,ions_name[i],ions_mass[i],ions_charge[i],ions_thxpos[i],ions_thypos[i],ions_xpos[i],ions_ypos[i],ions_peak[i],ions_velocity[i], FORMAT = format_show_pos2
	ENDFOR

	PRINT,bar
	PRINT,''

	GOTO,main

;************************************************************
;***** Output : Screen ; Determination of Ion Positions *****
;************************************************************
	
determine_pos:

	SET_PLOT,'X',/copy,/interpolate
		

;	DEVICE,FILE="test",/LANDSCAPE,$ 
;	;,YSIZE=19.,XSIZE=29.
;	YOFFSET=29.,XOFFSET=0.
        ;,/ENCAPSUL
;        !P.MULTI=[0,1,3]
	
;------ Skalierung des Contour-Plots wird berechnet

	step2 = MAX(plot_mat(*,*))
	step3 = step2 / 2097151. 
	clevels = fltarr(21)
	clevels[0] = 0
	PRINT,'Maximaler Wert : ',MAX(plot_mat(*,*))
	PRINT,step3
	FOR k = 1,20 DO BEGIN
		clevels[k] = step3 * (2.^k)
	ENDFOR 

;------ Contour-Plot der gesammten E-T-Matrix wird erzeugt

;	DEVICE,DECOMPOSED=0
;	LOADCT,0	


	CONTOUR,plot_mat,XRANGE=[0,XDIM-1],YRANGE=[0,YDIM-1],XSTYLE=1,YSTYLE=1,$
		LEVELS = clevels,$
;		/CELL_FILL,$
;		C_COLORS = [!P.COLOR,237,224,212,199,187,174,162,149,137,124,112,99,87,74,62,49,37,24,12,0],$
;		YMARGIN=[0,2],$
		XTITLE='ToF channel',$
		YTITLE='Energy channel',$
		CHARSIZE=1.5,$
		TITLE = step,$
		BACKGROUND=!P.Color,$
		COLOR=!P.Background
;	DEVICE,/close


;----- Theoretische Ionen Positionen werden geplottet
;	DEVICE,DECOMPOSED=1
;	LOADCT,4
	
	FOR k = 0, (numberions-1) DO BEGIN

		PRINT,ions_name[k],ions_thxpos[k],ions_thypos[k]
		PLOTS,ions_thxpos[k]-2,ions_thypos[k]+2,COLOR=50000,THICK=1
;		PLOTS,ions_thxpos[k]+2,ions_thypos[k]-2,/CONTINUE,COLOR=50000,THICK=1
		PLOTS,ions_thxpos[k]+2,ions_thypos[k]-2,COLOR=50000,THICK=1

		PLOTS,ions_thxpos[k]-2,ions_thypos[k]-2,COLOR=50000,THICK=1
;		PLOTS,ions_thxpos[k]+2,ions_thypos[k]+2,/CONTINUE,COLOR=50000,THICK=1
		PLOTS,ions_thxpos[k]+2,ions_thypos[k]+2,COLOR=50000,THICK=1
		XYOUTS,ions_thxpos[k]-20,ions_thypos[k]+3,ions_name[k],COLOR=50000

		IF (ions_xpos[k] GT 0.) THEN BEGIN
			PRINT,ions_name[k],ions_xpos[k],ions_ypos[k]
			PLOTS,ions_xpos[k]-2,ions_ypos[k]+2,COLOR=100000,THICK=1
;			PLOTS,ions_xpos[k]+2,ions_ypos[k]-2,/CONTINUE,COLOR=100000,THICK=1
			PLOTS,ions_xpos[k]+2,ions_ypos[k]-2,COLOR=100000,THICK=1
			PLOTS,ions_xpos[k]-2,ions_ypos[k]-2,COLOR=100000,THICK=1
;			PLOTS,ions_xpos[k]+2,ions_ypos[k]+2,/CONTINUE,COLOR=100000,THICK=1
			PLOTS,ions_xpos[k]+2,ions_ypos[k]+2,COLOR=100000,THICK=1
			XYOUTS,ions_xpos[k]-20,ions_ypos[k]+3,ions_name[k],COLOR=100000
		ENDIF
	ENDFOR

	
;----- Abfrage ob Positionen bestimmt werden sollen
	
;;	b = ''
;;	READ, 'Postionen bestimmen ? ',b

;;	IF ((b EQ 'y') OR (b EQ 'Y')) THEN BEGIN
	IF (1) THEN BEGIN

;----- Anfang Schleife über alle Ionen zur Bestimmung der Ionenpositionen durch Mausklick

		FOR l = 0,(numberions-1) DO BEGIN

			WDELETE,0
			DEVICE,DECOMPOSED=0
;			LOADCT,0
;----- Vergrösserter Ausschnitt um aktuelles (l.) Ion wird geplottet

			
			plot_mat_tmp = fltarr(21,101)
			plot_mat_tmp[*,*] = 0
			FOR x_tmp = 0,20 DO BEGIN
				FOR y_tmp = 0,100 DO BEGIN
					x_tmp2 = ions_thxpos[l]-10+x_tmp
					IF (x_tmp2 LT 1) THEN x_tmp2 = 1
					IF (x_tmp2 GT XDIM-1) THEN x_tmp2 = XDIM-1
					y_tmp2 = ions_thypos[l]-80+y_tmp
					IF (y_tmp2 LT 1) THEN y_tmp2 = 1
					IF (y_tmp2 GT YDIM-1) THEN y_tmp2 = YDIM-1
					plot_mat_tmp[x_tmp,y_tmp] = plot_mat[x_tmp2,y_tmp2]	
				ENDFOR
			ENDFOR

			step2 = MAX(plot_mat_tmp(*,*))
			step3 = step2 / 2097151. 
			clevels = fltarr(21)
			clevels[0] = 0
			PRINT,'Maximaler Wert : ',MAX(plot_mat_tmp(*,*))
			PRINT,step3
			FOR k = 1,20 DO BEGIN
				clevels[k] = step3 * (2.^k) 
			ENDFOR 


	
			CONTOUR,plot_mat,XRANGE=[ions_thxpos[l]-10,ions_thxpos[l]+10],YRANGE=[ions_thypos[l]-80,ions_thypos[l]+20],XSTYLE=1,YSTYLE=1,$
				LEVELS = clevels,$
;				/CELL_FILL,$
;				C_COLORS = [255,237,224,212,199,187,174,162,149,137,124,112,99,87,74,62,49,37,24,12,0],$
;				YMARGIN=[0,2],$
				XTITLE='ToF channel',$
				YTITLE='Energy channel',$
				CHARSIZE=1.5,$
				TITLE = step,$
				BACKGROUND=!P.Color,$
				COLOR=!P.Background
	
			DEVICE,DECOMPOSED=1
;			LOADCT,4
			
;----- Theoretische Positionen aller Ionen im Ausschnitt werden geplottet

			FOR k = 0,(numberions-1) DO BEGIN

				IF ((ions_thxpos[k] GE ions_thxpos[l]-40) AND (ions_thxpos[k] LE ions_thxpos[l]+40) AND (ions_thypos[k] GE ions_thypos[l]-40) AND (ions_thypos[k] LE ions_thypos[l]+40)) THEN BEGIN 
					PLOTS,ions_thxpos[k]-2,ions_thypos[k]+2,COLOR=50000,THICK=1
;					PLOTS,ions_thxpos[k]+2,ions_thypos[k]-2,/CONTINUE,COLOR=50000,THICK=1
					PLOTS,ions_thxpos[k]+2,ions_thypos[k]-2,COLOR=50000,THICK=1
					PLOTS,ions_thxpos[k]-2,ions_thypos[k]-2,COLOR=50000,THICK=1
;					PLOTS,ions_thxpos[k]+2,ions_thypos[k]+2,/CONTINUE,COLOR=50000,THICK=1
					PLOTS,ions_thxpos[k]+2,ions_thypos[k]+2,COLOR=50000,THICK=1
					XYOUTS,ions_thxpos[k]-2,ions_thypos[k]+3,ions_name[k],COLOR=50000
				ENDIF
				IF ((ions_xpos[k] GT 0.) AND((ions_xpos[k] GE ions_thxpos[l]-40) AND (ions_xpos[k] LE ions_thxpos[l]+40) AND (ions_ypos[k] GE ions_ypos[l]-40) AND (ions_ypos[k] LE ions_thypos[l]+40))) THEN BEGIN
					PRINT,ions_name[k],ions_xpos[k],ions_ypos[k]
					PLOTS,ions_xpos[k]-2,ions_ypos[k]+2,COLOR=100000,THICK=1
;					PLOTS,ions_xpos[k]+2,ions_ypos[k]-2,/CONTINUE,COLOR=100000,THICK=1
					PLOTS,ions_xpos[k]+2,ions_ypos[k]-2,COLOR=100000,THICK=1
					PLOTS,ions_xpos[k]-2,ions_ypos[k]-2,COLOR=100000,THICK=1
;					PLOTS,ions_xpos[k]+2,ions_ypos[k]+2,/CONTINUE,COLOR=100000,THICK=1
					PLOTS,ions_xpos[k]+2,ions_ypos[k]+2,COLOR=100000,THICK=1
					XYOUTS,ions_xpos[k]-2,ions_ypos[k]+3,ions_name[k],COLOR=100000
				ENDIF
			ENDFOR

;----- Mausabfrage

			PRINT, 'Position ', ions_name[l]
;			CURSOR, temp4, temp5, /DOWN


;----- Linke Maustaste -> Element ist vorhanden und Position wird gespeichert

			IF (!MOUSE.BUTTON EQ 1) THEN BEGIN
				ions_xpos[l] = temp4
				ions_ypos[l] = temp5
				IF (plot_mat[temp4,temp5] GT 0) THEN BEGIN
					ions_peak[l] = plot_mat[temp4,temp5]
				ENDIF ELSE BEGIN
					ions_peak[l] = 1
				ENDELSE

				PRINT, ions_xpos[l], ions_ypos[l], ions_peak[l]
			ENDIF

;----- Mittlere Maustaste -> Element ist nicht vorhanden Position und Peakhöhe wird -1 gesetzt

			IF (!MOUSE.BUTTON EQ 2) THEN BEGIN
				ions_xpos[l] = -1
				ions_ypos[l] = -1
				ions_peak[l] = -1
				PRINT, 'Ion nicht vorhanden'
			ENDIF

;----- Rechte Maustaste -> Abbruch

			IF (!MOUSE.BUTTON EQ 4) THEN BEGIN
				l = numberions
				PRINT,'Positionsbestimmung abgebrochen!'
			ENDIF	
				
		ENDFOR

;----- Ende Schleife über alle Ionen zur Bestimmung der Ionenpositionen durch Mausklick

	ENDIF
	WDELETE,0

	GOTO,main

;************************
;***** Save ion_pos *****
;************************

save_pos:
	
	tmpstat = 0

	OPENR,1,'ion_pos.dat',ERROR = err
	IF (err NE 0) THEN BEGIN
		PRINT,!ERROR_STATE.MSG
		tmpstat = 1
	ENDIF
	CLOSE,1

	IF (tmpstat EQ 1) THEN BEGIN
		
		OPENW,2,'ion_pos.dat'

		FOR i= 0,59 DO BEGIN

			sum = 0

			IF (i+1 EQ selectedeqstep) THEN BEGIN
				FOR k = 0,(numberions-1) DO BEGIN
				
					IF (ions_xpos[k] GT 0) THEN BEGIN
						sum = sum + 1
					ENDIF

				ENDFOR		
			ENDIF

			PRINTF,2,'E/Q-Step : ', i+1, 'Number Ions : ', sum, FORMAT = format_ion_pos_3
			PRINTF,2,'Name','Mass','Charge','TCH','ECH','Peak','Veloc.',FORMAT = format_ion_pos_2

			IF ((i+1) EQ selectedeqstep) THEN BEGIN

				FOR k = 0,(numberions-1) DO BEGIN
	
					IF (ions_xpos[k] GT 0) THEN BEGIN
						PRINTF,2,ions_name[k],ions_mass[k],ions_charge[k],ions_xpos[k],ions_ypos[k],ions_peak[k], ions_velocity[k], FORMAT = format_ion_pos_1
					ENDIF

				ENDFOR
			ENDIF
			
			PRINTF,2,'**************************************************************'

		ENDFOR
	
		CLOSE,2

	ENDIF ELSE BEGIN

		OPENR,1,'ion_pos.dat'
		OPENW,2,'tmp.dat'

		FOR l= 0,59 DO BEGIN

			IF (l NE (selectedeqstep-1)) THEN BEGIN
				eqtmp = 0
				numberionstmp = 0
				READF,1,temp1,eqtmp,temp8, numberionstmp, FORMAT = format_ion_pos_3
				PRINTF,2,temp1,eqtmp,temp8, numberionstmp, FORMAT = format_ion_pos_3
				READF,1,temp1
				PRINTF,2,temp1

				FOR k = 0,(numberionstmp-1) DO BEGIN
					READF,1,temp1,temp4,temp5,temp2,temp3,temp6,temp7, FORMAT = format_ion_pos_1
					PRINTF,2,temp1,temp4,temp5,temp2,temp3,temp6,temp7, FORMAT = format_ion_pos_1
				ENDFOR

				READF,1,temp1
				PRINTF,2,temp1
			ENDIF ELSE BEGIN
				OPENW,3,'step_tmp.dat'
					
				eqtmp = 0
				numberionstmp = 0
				READF,1,temp1,eqtmp,temp8, numberionstmp, FORMAT = format_ion_pos_3
				READF,1,temp1

				FOR k = 0,(numberionstmp-1) DO BEGIN
					READF,1,temp1,temp4,temp5,temp2,temp3,temp6,temp7, FORMAT = format_ion_pos_1
					PRINTF,3,temp1,temp4,temp5,temp2,temp3,temp6,temp7, FORMAT = format_ion_pos_1
					temp1 = STRCOMPRESS(temp1,/REMOVE_ALL)
					FOR m = 0,(numberions-1) DO BEGIN
						temp10 = STRCOMPRESS(ions_name[m],/REMOVE_ALL)
						if (temp1 EQ temp10) THEN BEGIN
							ions_xpos[m] = -1.
						ENDIF
					ENDFOR

				ENDFOR
		
				CLOSE,3
				OPENR,3,'step_tmp.dat',/DELETE
				READF,1,temp1

				sum = numberionstmp
			
				FOR k = 0,(numberions-1) DO BEGIN
				
					IF (ions_xpos[k] GT 0.) THEN BEGIN
						sum = sum + 1
					ENDIF

				ENDFOR		

				PRINTF,2,'E/Q-Step : ', l+1, 'Number Ions : ', sum, FORMAT = format_ion_pos_3
				PRINTF,2,'Name','Mass','Charge','TCH','ECH','Peak','Veloc.',FORMAT = format_ion_pos_2

				FOR k = 0,(numberionstmp-1) DO BEGIN
					READF,3,temp1,temp4,temp5,temp2,temp3,temp6,temp7, FORMAT = format_ion_pos_1
					PRINTF,2,temp1,temp4,temp5,temp2,temp3,temp6,temp7, FORMAT = format_ion_pos_1
				ENDFOR
				CLOSE,3

				FOR k = 0,(numberions-1) DO BEGIN
	
					IF (ions_xpos[k] GT 0.) THEN BEGIN
						PRINTF,2,ions_name[k],ions_mass[k],ions_charge[k],ions_xpos[k],ions_ypos[k],ions_peak[k], ions_velocity[k], FORMAT = format_ion_pos_1
					ENDIF

				ENDFOR
		
				PRINTF,2,'**************************************************************'

			ENDELSE

		ENDFOR

		CLOSE,1
		CLOSE,2
		


		OPENR,1,'tmp.dat',/DELETE
		OPENW,2,'ion_pos.dat'

		WHILE (NOT EOF(1)) DO BEGIN
			READF,1,temp1
			PRINTF,2,temp1
		ENDWHILE
		
		CLOSE,1
		CLOSE,2

	ENDELSE

	GOTO,main


;*********************************
;***** quit                  *****
;*********************************

quit:

END
