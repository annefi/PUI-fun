PRO databinning;

tmp2 = ''
tmp4 = ''
XDIM_DATA = 1024
YDIM_DATA = 256
XBIN = 2
YBIN = 2
XDIM = XDIM_DATA/XBIN
YDIM = YDIM_DATA/YBIN
read_et_mat_tmp = fltarr(YDIM_DATA,XDIM_DATA)
et_mat_bin = fltarr(58,YDIM_DATA,XDIM)
et_mat_bin_xy = fltarr(58,YDIM,XDIM)
plot_mat = fltarr(YDIM,XDIM)

;*********************
;***** set paths *****
;*********************

;	pathr = '/data/ivar/work/subversion/amerika/runs/2000138-2005198_accum_aspang/'
	pathr = '/home/asterix/berger/projects/databinning/data/'

;	pathw = '/home/ivar/berger/projects/SWICS/trunk/databinning/'
	pathw = '/home/asterix/berger/projects/databinning/'


;*****************************************************************
;***** start loop -> load_data - bin_data - save_binned_data *****
;*****************************************************************
	
	FOR aspint = 1,15 DO BEGIN

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

	;***** namew is created later, see Output : ps-file

		dataloadedtmp = 'axlv2_sumwhol_asp_'	
	
	;***** ending is created and added.
		PRINT,'aspint = ',aspint
	
		call_procedure,'int2str',aspint-1,tmp2
		call_procedure,'int2str',aspint,tmp4

		dataloadedtmp = dataloadedtmp + tmp2 + '.0-' + tmp4 
		namer = pathr + dataloadedtmp + '.0.dat'
		namew = pathw + dataloadedtmp + '.0_bin.dat'


;************************************************
;***** Daten werden geladen                 *****
;************************************************ 

	;***** idl reads x = colums, y = rows 
	;***** therefor plot_mat is used to switch x and y around
	;***** if necessary for plotting; Plotting for ACE/SWICS should
	;***** have format x = XDIM ToFch and y = YDIM Ech

		OPENR,1,namer

		FOR i = 0,57 DO BEGIN

			read_et_mat_tmp[*,*] = 0.

			IF (EOF(1)) THEN BEGIN
				CLOSE,1
				PRINT,'End of file encountered. Exit without binning!' 
				GOTO,ende
			ENDIF
			READF,1,tmp10,tmp11
			IF (EOF(1)) THEN BEGIN
				CLOSE,1
				PRINT,'End of file encountered. Exit without binning!'
				GOTO,ende
			ENDIF
			READF,1,read_et_mat_tmp	

;			FOR bla1 = 0,YDIM_DATA-1 DO BEGIN
;				FOR bla = 0,XDIM_DATA-1 DO BEGIN
;					IF (read_et_mat_tmp[bla1,bla] NE 0.) THEN PRINT,read_et_mat_tmp[bla1,bla]
;				
;				ENDFOR
;			ENDFOR
		

	

;************************
;***** binning data *****
;************************
	
	;***** first and last ToF-channel (read_et_mat_tmp[0,l]..[i,XDIM_DATA-1,l]) are not binned / channels not relevant for data analalysis
	;***** the rest is binned third[*,2,*] and second[*,1,*] ...

	;***** XBINNING

			FOR l = 0,YDIM_DATA-1 DO BEGIN
				et_mat_bin[i,l,0] = read_et_mat_tmp[l,0]
				FOR m = 1,XDIM-1 DO BEGIN
					FOR k = 0,XBIN-1 DO BEGIN 
						et_mat_bin[i,l,m] = et_mat_bin[i,l,m]+read_et_mat_tmp[l,(m*XBIN)-k]
					ENDFOR
				ENDFOR
			ENDFOR	

	;***** YBINNING

			FOR l = 0,XDIM-1 DO BEGIN
				et_mat_bin_xy[i,0,l] = et_mat_bin[i,0,l]
				FOR m = 1,YDIM-1 DO BEGIN
					FOR k = 0,YBIN-1 DO BEGIN 
						et_mat_bin_xy[i,m,l] = et_mat_bin_xy[i,m,l]+et_mat_bin[i,(m*YBIN)-k,l]
					ENDFOR
				ENDFOR
			ENDFOR	
	

		ENDFOR

;****************************
;***** Save binned data *****
;****************************

		OPENW,2,namew
	
		FOR i = 0,57 DO BEGIN
			PRINTF,2,XDIM,YDIM
			plot_mat[*,*] = et_mat_bin_xy[i,*,*]
;			FOR k = 0,YDIM-1 DO BEGIN
;				FOR l = 0,XDIM-1 DO BEGIN
;					plot_mat[k,l] = et_mat_bin_xy[i,k,l]
;				ENDFOR
;			ENDFOR
	
			PRINTF,2,plot_mat
		ENDFOR

		CLOSE,2

	close,1

	ENDFOR

ende:

end