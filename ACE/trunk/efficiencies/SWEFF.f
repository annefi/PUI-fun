C******************** 12-12-84 *******************
      FUNCTION SWEFF(ENERGY,RNUCL)
C 
C    old version 10-12-77 
C    02-28-80    new values for ENERGY .LT. 1.5 keV/nucleon 
C                incorporate iron and xeon results from LINDAU, 
C                (iron results extended using PETRILAK) 
C 
C     08-03-80   SOME REVISIONS TO FE AND KR. 
C 
C     08-08-80   REVISIONS TO HIGH ENERGY FE BASED ON &GOLD RESULTS.
C 
C     09-17-80   MINOR REVISIONS TO C,N,AR,FE.
C       -18-     AND NE.
C 
C     10-02-80   revisions to lower energies based on &GOLD for 
C                all elements. Revisions to O16 based on data.
C                Elimination of E = .1 keV/nuc  in arrays.
C 
C     10-08-80   All elements (except Xe) now based on &GOLD output.
C       -09-     Changes also made to Xe to conform better to data. 
C 
C     10-24-80   CHANGES TO HE. 
C 
C     12-12-84   Copied SWEFF from DFECT
C                Redefined mass to units wherein H = 1.0000 
C                Modified efficiencies based on SWICS calibration of
C                flight unit at Lindau. 
C 
C     12-17-84   Changed Oxygen to a variable offset relative to ISEE 
C 
      DIMENSION RNUC(10),ENERG(22),EFF(22,10),DELTA(10) 
      DATA IFLAG/1/ 
      DATA DELTA/2.6, 4.1, 1.9, 2.2, 2.2, 2.2, 1.2, 1.4, 1.2, 1.2/
      DATA RNUC/ 1., 3.97, 11.92, 13.9, 15.87, 20.02, 39.63,
     $   55.41, 83.14, 129./
      DATA ENERG/.4,.7,1.,1.5,2.5,4.,6.,8.,10.,15.,25.,40., 
     $60.,80.,100.,150.,250.,400.,600.,800.,1000.,10000./ 
C PROTONS 
      DATA EFF/35.5,45.5,51.9,58.4,65.7,71.8,77.0,80.5,82.9,86.4,90.2,
     $92.8,94.6,95.6,96.4,97.5,98.5,99.2,99.5,99.6,99.7,100., 
C HELIUM
     $32.8,43.4,50.0,57.2,65.5,72.3,77.5,80.7,83.1,87.0,90.9,93.4,95.2, 
     $96.0,96.6,97.5,98.4,99.0,99.4,99.5,99.6,100., 
C CARBON
     $18.2,26.2,31.6,38.3,47.3,56.2,64.1,69.1,72.5,78.2,84.2, 
     $88.3,91.3,93.1,94.,95.7,97.2,98.2,98.7,99.0,99.2,99.8,
C NITROGEN
     $17.3,24.8,29.9,36.4,45.7,54.6,62.2,67.2,70.7,76.6,82.8,87.4,
     $90.7,92.6,93.7,95.3,97.0,98.0,98.6,98.9,99.1,99.8,
C OXYGEN
     $17.2,23.2,27.1,32.9,41.5,50.4,59.1,64.6,68.4,74.5,80.8, 
     $85.8,88.7,90.4,91.5,93.6,95.7,97.1,97.9,98.4,98.7,99.7, 
C NEON
     $17.1,22.5,25.8,30.2,37.1,45.1,52.7,58.1,62.2,69.5,77.6, 
     $82.7,86.4,88.6,90.,92.,94.3,95.8,96.8,97.4,97.7,99.5, 
C ARGON 
     $15.2,20.5,23.9,28.2,35.0,42.1,48.8,53.4,57.0,63.3,71.2,77.2,81.9, 
     $84.6,86.6,89.9,93.1,94.9,96.1,96.6,97.0,99.3, 
C IRON
     $14.5,18.8,22.4,26.2,31.0,35.6,40.3,43.7,46.6,52.8,62.0,70.9,
     $77.5,81.2,83.3,86.6,90.3,92.9,94.6,95.4,95.9,99.0,
C KRYPTON 
     $14.0,17.4,21.2,25.2,29.8,34.2,38.6,42.2,45.1,50.4,58.2,66.0,
     $72.4,76.5,78.9,82.9,87.8,91.3,93.3,94.4,95.1,98.8,
C XEON
     $13.9,17.4,20.3,23.4,27.1,30.9,34.4,36.9,39.,43.6,50.0,57.7, 
     $64.1,68.2,70.6,74.5,78.3,80.8,82.7,83.8,84.1,87.5 / 
C 
      IF(IFLAG .NE. 1)   GO TO 8
C 
C**      Modified defect for SWICS here 
C 
      DO 400 J=1,10 
      DO 400 I=1,22 
400   EFF(I,J) = EFF(I,J) - DELTA(J)
      IFLAG = -1
C 
C**  Variable Oxygen offset here
C 
      EFF(4,5) = EFF(4,5) - 0.25
      EFF(5,5) = EFF(5,5) - 1.6 
      EFF(6,5) = EFF(6,5) - 2.4 
      EFF(7,5) = EFF(7,5) - 2.4 
      EFF(8,5) = EFF(8,5) - 1.8 
      EFF(9,5) = EFF(9,5) - 1.4 
      EFF(10,5) = EFF(10,5) - 0.6 
 
8     RMASS = RNUCL 
      ERG = ENERGY
      IF (ERG.LT.10000.) GO TO 10 
      SWEFF=1.00
      RETURN
10    IF (RMASS .LT. 1.) GO TO 200
      IF(ERG .LT. .4)   ERG=.4001 
      IF(RMASS .GT. 129.) RMASS = 129.
      IE=-1 
20    DO 100 J=1,22 
      IF (ERG-ENERG(J)) 120,110,100 
100   CONTINUE
110   IE=0
120   DO 140 I=1,10 
      IF (RMASS-RNUC(I)) 160,150,140
140   CONTINUE
150   IF (IE.EQ.0) GO TO 180
      EFF1=EFF(J-1,I) 
      EFF2=EFF(J,I) 
      GO TO 170 
160   EFF1=(EFF(J-1,I)-EFF(J-1,I-1))/(RNUC(I)-RNUC(I-1))
      EFF1=EFF1*(RMASS-RNUC(I-1))+EFF(J-1,I-1)
      EFF2=(EFF(J,I)-EFF(J,I-1))/(RNUC(I)-RNUC(I-1))
      EFF2=EFF2*(RMASS-RNUC(I-1))+EFF(J,I-1)
      IF (IE.EQ.0) GO TO 190
170   EFFIC=(EFF2-EFF1)*(ALOG10(ERG)-ALOG10(ENERG(J-1)))
      EFFIC=EFFIC/(ALOG10(ENERG(J))-ALOG10(ENERG(J-1)))+EFF1
      SWEFF=EFFIC/100.
      RETURN
180   SWEFF=EFF(J,I)/100. 
      RETURN
190   SWEFF=EFF2/100. 
      RETURN
200   SWEFF=-1.00 
      RETURN
      END 
