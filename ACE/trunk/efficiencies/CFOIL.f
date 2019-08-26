      FUNCTION CFOIL(EPN,ZAMU)
C REVISED   2-05-80    KAH
C REVISED   2-18-80    ABG
C REVISED   3-09-82    FMI   : ALL POINTS CHANGED 
C REVISED   3-28-82    FMI   : ALL LOGIC CHANGED
C REVISED   4-30-82    FMI   : He slightly changed
C REVISED   1-12-85    FMI   : Masses changed to H = 1.000 system 
C REVISED   4-21-89    WNH   : Moved to microvax
C 
C           use Anderson & Ziegler for H
C           use            Ziegler for He 
C           other elements based on data from 
C           UMD(SWICS E/M at Lindau, 11-81 and 12-81) 
C           STUDEMANN & WILKEN (Rev. Sci. Instr.) 
C           ACHIM (Diplom-arbeit,1982)
C            supplemented by  ZIEGLER(1980) 
C                        and NORTHCLIFF & SCHILLING(1970) 
C       CFOIL uses Log-Log interpolation for EPN between 1 & 1.E4 keV/nuc 
C             and Log-Log extrapolation outside this range
C       CFOIL uses Lin-Lin interpolation for AMU between 1 & 84 
C             and Lin-Lin extrapolation for AMU .GT. 84 
C       CFOIL uses Lin-Lin interpolation for Z between 1 & 36 
C             and Lin-Lin extrapolation for Z .GT. 36 
C 
C****** 
C 
C INPUT : EPN , incident energy per nuc. in keV per nucleon 
C         ZAMU , if > 0, represents  mass in amu
C              , if < 0, then ABS(ZAMU) represents nuclear charge 
C OUTPUT : CFOIL = dE/dx  in  keV per microgram/cm**2 
C 
C***************************************************************
C 
      DIMENSION   ENERGY(20) , DEDX(20,10)
      DIMENSION   RMASS(10) , Z(10) , ZMASS(10) 
      INTEGER  ZMFLAG , EFLAG 
C 
      DATA RMASS/ 1.0 , 3.97 , 11.92 , 13.90 , 15.87 , 20.02 ,  
     $   31.81 , 39.63 , 55.41 , 83.14 /
C 
      DATA  Z/ 1., 2., 6., 7., 8., 10., 16., 18., 26., 36. /
C 
      DATA ENERGY/1., 1.5, 2.5, 4., 6., 8., 10., 15., 25., 40., 60.,
     $  80., 100., 150., 250., 400., 600., 800., 1000., 10000. /
C** 
C 
C PROTONS 
      DATA DEDX/.16, .18, .23, .28, .34, .38, .42, .50, .60, .70, .75,
     $  .75, .725, .64, .51, .40, .32, .27, .23, .04, 
C HELIUM
     $ .43, .48, .57, .66, .75, .84, .91, 1.05, 1.25, 1.47, 1.65, 
     $  1.82, 1.86, 1.93, 1.81, 1.53, 1.24, 1.04, .89, .16, 
C CARBON
     $ 1.28, 1.38, 1.52, 1.72, 1.91, 2.10, 2.28, 2.60, 3.25, 4.10, 4.95,
     $  5.58, 6.05, 6.75, 7.20, 7.10, 6.80, 6.25, 5.80, 1.45, 
C NITROGEN
     $ 1.41, 1.51, 1.71, 1.91, 2.18, 2.39, 2.58, 2.97, 3.67, 4.55, 5.50,
     $  6.25, 6.80, 7.95, 8.70, 8.80, 8.30, 7.75, 7.20, 1.95, 
C OXYGEN
     $ 1.42, 1.52, 1.72, 1.99, 2.29, 2.51, 2.73, 3.22, 4.05, 5.00, 6.02,
     $  7.00, 7.62, 8.90, 10.1, 10.2, 9.80, 9.35, 8.85, 2.50, 
C NEON
     $ 1.30, 1.37, 1.54, 1.80, 2.10, 2.35, 2.60, 3.13, 4.15, 5.27, 6.50,
     $  7.58, 8.56, 10.7, 13.6, 15.2, 15.2, 14.4, 13.4, 3.90, 
C SULFUR
     $ 2.00, 2.00, 2.18, 2.53, 3.04, 3.50, 3.91, 4.80, 6.20, 7.70, 9.50,
     $  11.0, 12.2, 15.0, 19.0, 22.2, 23.8, 23.8, 23.2, 8.60, 
C ARGON 
     $ 3.08, 3.08, 3.18, 3.45, 3.80, 4.15, 4.45, 5.20, 6.30, 7.77, 9.60,
     $  11.3, 12.8, 16.3, 21.0, 24.5, 26.6, 26.8, 26.3, 10.4, 
C IRON
     $ 3.25, 3.25, 3.25, 3.40, 3.72, 4.13, 4.60, 5.65, 7.40, 9.48, 11.8,
     $  13.9, 15.9, 20.9, 27.3, 33.1, 36.9, 38.0, 37.9, 18.3, 
C KRYPTON 
     $ 4.10, 4.10, 4.10, 4.20, 4.43, 4.78, 5.19, 6.30, 8.38, 10.8, 13.6,
     $  16.1, 18.5, 24.8, 33.7, 42.4, 48.6, 51.0, 51.5, 29.3 /
C 
C***   initialize here
C 
      ERG = EPN 
      ZM = ZAMU 
      ZMFLAG = 0
      EFLAG = 0 
C 
      DO 90 I=1,10
      ZMASS(I) = RMASS(I) 
      IF(ZM .LT. 0.)   ZMASS(I) = Z(I)
 90   CONTINUE
C 
      ZM = ABS(ZM)
      IF(ZM .LT. 1.)   ZM = 1.
      IF(ERG .LT. 1.E-5)   ERG = 1.E-5
C 
C******************** 
C 
      DO 140 I=1,10 
      IF(ZM .EQ. ZMASS(I))   GO TO 145
      IF( I .EQ. 1 )         GO TO 140
      IF(ZM .LT. ZMASS(I))   GO TO 150
 140  CONTINUE
      I = 10
      GO TO 150 
C 
 145  ZMFLAG = 1
C 
 150  DO 190 J=1,20 
      IF(ERG .EQ. ENERGY(J))   GO TO 195
      IF( J .EQ. 1 )           GO TO 190
      IF(ERG .LT. ENERGY(J))   GO TO 200
 190  CONTINUE
      J = 20
      GO TO 200 
C 
 195  EFLAG = 1 
C 
C**  check flags here 
C 
 200  IF( ZMFLAG*EFLAG .EQ. 1 )  GO TO 600
      IF(ZMFLAG .EQ. 1)  GO TO 300
      IF(EFLAG .EQ. 1)   J = J + 1
C 
C  interpolate linearly on mass at E1 
C 
      ZM1 = ZMASS(I-1)
      ZM2 = ZMASS(I)
      XNUM = DEDX(J-1,I) - DEDX(J-1,I-1)
      XDEN = ZM2 - ZM1
      SLOPE = XNUM / XDEN 
      DEDX1 = DEDX(J-1,I-1) + SLOPE * (ZM-ZM1)
         IF(EFLAG .EQ. 1)   GO TO 500 
C 
C   now interpolate on mass at E2 
C 
      XNUM = DEDX(J,I) - DEDX(J,I-1)
      SLOPE = XNUM / XDEN 
      DEDX2 = DEDX(J,I-1) + SLOPE * (ZM-ZM1)
      GO TO 350 
C 
 300  DEDX1 = DEDX(J-1,I) 
      DEDX2 = DEDX(J,I) 
C 
C  here interpolate logarithmically on energy 
C 
 350  E2 = ENERGY(J)
      E1 = ENERGY(J-1)
      XNUM = ALOG( DEDX2/DEDX1 )
      XDEN = ALOG( E2/E1) 
      SLOPE = XNUM / XDEN 
      RHS = SLOPE * ALOG( ERG/E1 )
C 
      CFOIL = DEDX1 * EXP( RHS )
      RETURN
C 
 500  CFOIL = DEDX1 
      RETURN
C 
 600  CFOIL = DEDX(J,I) 
      RETURN
C 
      END 
