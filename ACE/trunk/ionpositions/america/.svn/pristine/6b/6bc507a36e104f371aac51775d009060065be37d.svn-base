; color_20.pro
; received from Nathan Schwandron, 25Jan00
;==============================
PRO COLOR_20, dummy
;==============================
;     making a color table
;         0    1  2  3  4  5
;
common rgb, red, green, blue
ncol=!d.n_colors
    Red = FLTARR(ncol)
    Green = FLTARR(ncol)
    BLUE = FLTARR(ncol)

    FOR I=0UL,ncol-1 DO BEGIN
      RED(I) = 0.15*(ncol-1.)
      GREEN(I) = 0.0*(ncol-1.)
      BLUE(I) = .25*(ncol-1.)
    IF( I GT .05*ncol) THEN BEGIN
      RED(I) = 0.3*(ncol-1.)
      GREEN(I) = 0.0*(ncol-1.)
      BLUE(I) = .5*(ncol-1.)
    ENDIF
    IF( I GT .1*ncol) THEN BEGIN
       RED(I) = 0.15
       GREEN(I) = 0.1*(ncol-1)   ; 0.0*255
       BLUE(I) = .75*(ncol-1)
    ENDIF
    IF( I GT .15*ncol) THEN BEGIN
       RED(I) = 0.0
       GREEN(I) = 0.2*(ncol-1)   ; 0.0*255
       BLUE(I) = 1*(ncol-1)
    ENDIF
    IF( I GT .2*ncol) THEN BEGIN
       RED(I) = 0.0*(ncol-1)
       GREEN(I) = 0.45*(ncol-1)  ; 0.9*255
       BLUE(I) = 1.0*(ncol-1)   ; 0.8*255
    ENDIF
    IF( I GT .25*ncol) THEN BEGIN
       RED(I) = 0.0*(ncol-1)
       GREEN(I) = 0.7*(ncol-1)  ; 0.9*255
       BLUE(I) = 1.0*(ncol-1)   ; 0.8*255
    ENDIF
    IF( I GT .3*ncol) THEN BEGIN
       RED(I) = 0.0*(ncol-1)   ; 0.0*255
       GREEN(I) = .85*(ncol-1)
       BLUE(I) = 0.85*(ncol-1)
    ENDIF
    IF( I GT .35*ncol) THEN BEGIN
       RED(I) = 0.0*(ncol-1)   ; 0.0*255
       GREEN(I) = 1.0*(ncol-1)
       BLUE(I) = 0.7*(ncol-1)
    ENDIF
    IF( I GT .4*ncol) THEN BEGIN
       RED(I) = 0.3*(ncol-1)
       GREEN(I) = 1.0*(ncol-1)
       BLUE(I) = 0.45*(ncol-1)
    ENDIF
    IF( I GT .45*ncol) THEN BEGIN
       RED(I) = 0.6*(ncol-1)
       GREEN(I) = 1.0*(ncol-1)
       BLUE(I) = 0.0*(ncol-1)
    ENDIF
    IF( I GT .5*ncol) THEN BEGIN
       RED(I) = .8*(ncol-1)
       GREEN(I) = 1.0*(ncol-1)
       BLUE(I) = 0.0*(ncol-1)
    ENDIF
    IF( I GT .55*ncol) THEN BEGIN
       RED(I) = 1.0*(ncol-1)
       GREEN(I) = 1.0*(ncol-1)
       BLUE(I) = 0.0*(ncol-1)
    ENDIF
    IF( I GT .6*ncol) THEN BEGIN
       RED(I) = 1.0*(ncol-1)
       GREEN(I) = 0.85*(ncol-1)   ; 1.0*255
       BLUE(I) = 0.0*(ncol-1)
    ENDIF
    IF( I GT .65*ncol) THEN BEGIN
       RED(I) = 1.0*(ncol-1)
       GREEN(I) = 0.7*(ncol-1)   ; 1.0*255
       BLUE(I) = 0.0*(ncol-1)
    ENDIF
    IF( I GT .7*ncol) THEN BEGIN
       RED(I) = .9*(ncol-1)
       GREEN(I) = 0.5*(ncol-1)   ; 1.0*255
       BLUE(I) = 0.15*(ncol-1)
    ENDIF
    IF( I GT .75*ncol) THEN BEGIN
       RED(I) = .8*(ncol-1)
       GREEN(I) = 0.3*(ncol-1)   ; 1.0*255
       BLUE(I) = 0.3*(ncol-1)
    ENDIF
    IF( I GT .8*ncol) THEN BEGIN
       RED(I) = .9*(ncol-1)
       GREEN(I) = 0.15*(ncol-1)
       BLUE(I) = 0.4*(ncol-1)
    ENDIF
    IF( I GT .85*ncol) THEN BEGIN
       RED(I) = 1.0*(ncol-1)
       GREEN(I) = 0.0*(ncol-1)
       BLUE(I) = 0.4*(ncol-1)
    ENDIF
    IF( I GT .9*ncol) THEN BEGIN
       RED(I) = 1.0*(ncol-1)
       GREEN(I) = 0.2*(ncol-1)
       BLUE(I) = .7*(ncol-1)
    ENDIF
    IF( I GT .95*ncol) THEN BEGIN
       RED(I) = 1.0*(ncol-1)
       GREEN(I) = 0.4*(ncol-1)
       BLUE(I) = 1.0*(ncol-1)
    ENDIF
    ENDFOR
;
   RED(0) = 0.
   GREEN(0) = 0.
   BLUE(0) = 0.
   RED(ncol-1) = (ncol-1)
   GREEN(ncol-1) = (ncol-1)
   BLUE(ncol-1) = (ncol-1)
;	PRINT,RED
   TVLCT, RED, GREEN, BLUE
;
RETURN
END
