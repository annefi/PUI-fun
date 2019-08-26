      SUBROUTINE ARNAUD_SHARE(XZ,XTE,X,XRECO,XRTOT)
C-----------------------------------------------------------------------
C     DESCRIPTION OF PARAMETERS                                         
C                                                                       
C     Z     Number of protons in element                                 
C     TE    Electron temperature [K]
C     RTOT  Total ionisation rate                                        
C     RDIR  Direct ionisation rate                                       
C     RAUTO Autoionisation rate                                         
C     RAD   Radiative recombination rate                                 
C     DIEL  Dielectronic recombination rate                              
C     RECO  Total recombination rate                                      
C
C     This routine is based on the original package of Arnaud and
C     Rothenflug (1985)
C
C     MODIFICATIONS: 
C         June 20, 1994     initial version
C         August 24, 1994   make ARNMAIN into a subroutine (P.W.)
C         August 19, 1996   removed COMMON block (P.W.)
C         January 20, 1998  adapted for SUN/UNIX (P.W.)     
C-----------------------------------------------------------------------
      IMPLICIT REAL*8 (A-H,O-Z)                                         

      INTEGER*4 IZ(15)		! Table of available ions
      INTEGER*4  S,Z
      INTEGER*4 NION(30)                                          

      REAL*8 TE			! Temperature of electrons in degrees Kelvin
      REAL*8 RTOT(29),RDIR(29),RAUTO(29)
      REAL*8 ALRTOT
      REAL*8 PROD(30)
      REAL*8 RAD(29)
      REAL*8 DIEL(29)
      REAL*8 RECO(29)

	DATA IZ/1,2,6,7,8,10,11,12,13,14,16,18,20,26,28/

C-----------------------------------------------------------------------
C	IDL Interface
C.......................................................................
	REAL*8 X(30)
	REAL*8 XRECO(30)
	REAL*8 XRTOT(30)
	integer*4 XZ
	real*8 XTE

	TE = XTE		
	Z  = XZ
C	WRITE(*,*) xz, xte
C-----------------------------------------------------------------------
C	Do initial check
C.......................................................................
 	DO 33, I=1,15
		IF (Z .EQ. IZ(I)) GOTO 10
33		CONTINUE
	WRITE(6,8010) Z
8010	FORMAT(1X,'ARNAUD> Cannot handle this ion:',I5)
        RETURN
C	CALL EXIT(-1)
C-----------------------------------------------------------------------
C	Start processing
C.......................................................................
10	CONTINUE
	WRITE(6, *) XZ, XTE, Z, TE
8011	FORMAT(1X,'ARNAUD_SHARE> ', 2G15.5,/,1X,T15,I5,G15.5)

      DO 19, I=1,30
        RTOT(I)=0.D0
19    CONTINUE
      ILEC=0                                                            
      AKTEV=TE/11606.0
      CALL IONSUB(Z,AKTEV,RAUTO,RDIR,RTOT)                                   
C-----------------------------------------------------------------------
C                                                                 
C.......................................................................
      PRODSU = 1.D0                                                     
      PROD(1) = 1.D0                                                    
      PRODL = 0.D0                                                      
      INDEX = 0
      DO 18, I=1,30
           X(I)=0.D0
18         RECO(I)=0.D0
   50 DO 20, I=1,Z                                                       
           S=I+1                                                             
           IF (Z.NE.26) CALL RECOMB(Z,S,TE,RR,RDIEL)                      
           IF (Z.EQ.26) CALL RECOFE(Z,S,TE,RR,RDIEL)
           RAD(I)=RR                                                         
           DIEL(I)=RDIEL                                                     
           RECO(I)=RR+RDIEL                                                  
           ALRTOT = DLOG(MAX(RTOT(I),1.0D-30))
           PRODL = PRODL + ALRTOT - DLOG(RECO(I))                            
           IF (PRODL.LT.-70.D0) PROD(I+1) = 0.D0                               
           IF (PRODL.GE.-70.D0) PROD(I+1) = DEXP(PRODL)                        
           IF (PRODL.GE.70.D0 .AND. INDEX.LE.2) THEN
               IF (PRODL.GE.70.D0 .AND. INDEX.GT.2) STOP
               INDEX = INDEX + 1 
               PRODL = -70.D0*DFLOAT(INDEX)
               PRODSU = DEXP(PRODL)
               PROD(1) = DEXP(PRODL)
               GO TO 50
               END IF
           PRODSU = PRODSU + PROD(I+1)                                       
 20        CONTINUE                                                          
C                                                                       
      MZ = Z + 1                                                        
      DO 100, I=1,MZ                                                     
         NION(I) = I-1                                                     
         IF (PROD(I).EQ.0.D0) THEN
		X(I)=0.D0 
		GO TO 100    
		ENDIF
         IF (DLOG(PROD(I))-DLOG(PRODSU).LT.-70.0D0) X(I) = 0.D0              
         IF (DLOG(PROD(I))-DLOG(PRODSU).GE.-70.0D0) X(I)=PROD(I)/PRODSU    
100      CONTINUE                                                          
C-----------------------------------------------------------------------
C	IDL Interface
C.......................................................................
	DO 110, I=1,29
		XRECO(I+1)=RECO(I)
		XRTOT(I)  =RTOT(I)
110		CONTINUE
	write(*,*)reco
	write(*,*)rtot

      END                                                               

      SUBROUTINE RECOMB(Z,S,TE,RR,RDIEL)                                
C=======================================================================
C Ce sous-programme calcule le taux de recombinaison                    
C en utilisant Aldrovandi et Pequignot, Shull et al.                    
C SEATOJ, PRADHAJ, QIUJEER, QTIREY (BEDQ DUBAU,JACIBS                       
C                                                                       
C S est le numero de l'ion qui va se recombiner                         
C=====================================================                  
C                                                                       
C     Original version of Arnaud and Rothenflug  should not be used
C     for iron
C
C     Implemented into ARNMAIN by Peter Bochsler June 20, 1994
C     Adapted for SUN/UNIX by Peter Wurz January 22, 1998
C-----------------------------------------------------------------------
      IMPLICIT REAL*8 (A-H,O-Z)                                         

      REAL*8 KT,KTEV                                                    
      REAL*8 REAL_LOW
      INTEGER Z,S,Z1
      DIMENSION AR(166),ETA(166),POTLI(28)                              
      DIMENSION ASTOR(18),BSTOR(18),CSTOR(18),DSTOR(18),FSTOR(18)       
      DIMENSION ID(28),KSTOR(28),ISTOR(28)                              
      DIMENSION ADI(166),T05(166),BDI(166),T15(166)                     

      PARAMETER (REAL_LOW=1.0D-70)

      DATA POTLI/0.,0.,5.39,18.2,37.9,64.5,97.9,138.,185.,239.,300.,
     1           367.,442.,523.,612.,700.,809.,918.,1034.,1157.,1288.,
     2           1425.,1569.,1721.,1880.,2045.,2218.,2399./
      DATA ID/0,1,3*0,2,8,15,0,23,0,33,0,45,0,59,0,
     1        75,0,93,5*0,113,0,139/                          
      DATA KSTOR/5*0,4,5,6,3*0,2,3,4,14*0/                              
      DATA ISTOR/5*0,1,4,8,3*0,13,14,16,14*0/                           
      DATA ASTOR/.0108,1.8267,2.3196,0.,.032,-.8806,.4134,0.,           
     1           -.0036,0.,.0061,-2.8425,1.2044,0.0710,0.7086,-0.0219,     
     2           3.2163,0.1203/                                  
      DATA BSTOR/-.1075,4.1012,10.7328,.6310,-.6624,11.2406,            
     1           -4.6319,.0238,.7519,21.879,.2269,.2283,-4.6836,-0.4079,
     2           -3.1083,0.4364,-12.0571,-2.6900/                          
      DATA CSTOR/.2810,4.8443,6.883,.199,4.3191,30.7066,25.9172,.0659,
     1           1.5252,16.273,32.1419,40.4072,7.6620,2.3487,7.0422,         
     2           0.0684,16.2118,19.1943/ 
      DATA DSTOR/-.0193,.2261,-.1824,-.0197,.0003,-1.1721,-2.229,       
     1           .0349,-.0838,-.7020,1.9939,-3.4956,-0.5930,-0.1309,
     2           0.5998,-0.0032,-0.5886,-0.1479/                              
      DATA FSTOR/-.1127,.596,.4101,.4398,.5946,.6127,.2360,.5334,       
     1           .2769,1.1899,-.0646,1.7558,1.6260,0.6126,0.4194,0.1342,
     2           0.5613,0.1118/                                              
      DATA ADI/1.27,2.54,6.15,1.62,47.8,32.2,0.,2.98,7.41,11.3,2.62,75.,
     &46.1,                                                             
     $0.,1.11,5.07,14.8,18.4,4.13,106.,47.2,0.,.977,2.65,3.69,11.8,2    
     $4.4,30.2,6.10,252.,71.4,0.,.449,1.95,5.12,7.74,11.7,36.9,36.3,41.5
     $,8.86,252.,92.8,0.,1.1,5.87,5.03,5.43,8.86,16.8,24.9,31.3,42.5,61.
     $8,13.8,327.,113.,0.,1.62,10.9,33.5,31.4,12.7,14.7,13.4,23.8,31.9, 
     $71.3,80.,79.6,13.4,402.,145.,0.,1.,11.,34.,48.0,75.,63.5,26.,24.,2
     $1.,35.,43.,71.3,96.,85.,17.,476.,178.,0.,.328,58.4,112.,132.,133.,
     $126.,139.,95.5,40.2,41.9,25.7,44.5,54.8,71.3,109.,110.,20.5,54    
     $9.,268.,0.,1.58,8.38,15.4,37.5,117.,254.,291.,150.,140.,100.,200.,
     $240.,260.,190.,120.,350.,66.,100.,130.,230.,140.,110.,41.,747.,   
     $369.,0.,1.41,5.2,13.8,23.,41.9,68.3,122.,300.,150.,697.,709.,644.,
     $525.,446.,363.,302.,102.,270.,46.7,83.5,99.6,199.,240.,115.,31.6, 
     $803.,345.,0./                                                     
      DATA BDI/300.,44.2,58.8,343.,362.,315.,0.,0.,76.4,164.,243.,350., 
     &309                                                               
     $.,0.,92.5,181.,305.,100.,162.,340.,0.,0.,73.,242.,1010.,391.,252  
     $0.,445.,254.,304.,296.,0.,21.,74.,323.,636.,807.,351.,548.,233.,31
     $8.,315.,0.,0.,0.,753.,188.,450.,0.,1800.,1880.,2010.,1220.,303.,  
     $1420.,306.,286.,0.,0.,12.,65.9,68.9,187.,129.,1040.,1120.,1400.,  
     $1000.,555.,1630.,304.,298.,281.,0.,5.,45.,57.,87.,76.9,140.,120., 
     $100.,1920.,1660.,1670.,1400.,1310.,1020.,245.,294.,277.,0.,90.7,1 
     $10.,17.4,132.,114.,162.,87.8,263.,62.7,61.6,2770.,2230.,2000.,1820
     $.,1740.,243.,185.,292.,0.,0.,456.,323.,310.,411.,359.,97.5,229.,  
     $4200.,3300.,5300.,1500.,700.,600.,500.,1000.,0.,7800.,6300.,5500.,
     $3600.,4900.,1600.,4200.,284.,0.,0.,469.,357.,281.,128.,41.7,55.8  
     $,34.6,0.,1900.,277.,135.,134.,192.,332.,337.,121.,51.4,183.,7560.,
     $4550.,4870.,2190.,1150.,1230.,132.,289.,286.,0./                  
      DATA T05/4.7,1.57,1.41,.819,34.,40.6,0.,2.2,2.01,1.72,1.02,47.5,54
     $.4,0.,1.75,1.98,2.41,2.12,1.25,62.5,60.,0.,3.11,2.84,2.24,2.70,3. 
     $09,2.83,1.68,140.,110.,0.,.501,6.06,4.69,3.74,3.28,4.80,3.88,3.39,
     $2.11,140.,145.,0.,.77,.963,.875,10.5,11.4,4.85,4.15,3.66,3.63,3.88
     $,2.51,188.,199.,0.,1.25,1.92,1.89,1.68,1.38,18.,6.90,5.84,5.17,   
     $6.66,6.,5.09,2.91,241.,254.,0.,3.2,2.9,2.39,2.56,2.50,2.1,1.8,27  
     $.,8.3,6.95,6.05,6.68,6.5,5.3,3.55,301.,313.,0.,.346,3.85,4.08,    
     $3.82,3.53,3.19,3.22,2.47,2.29,37.3,9.26,7.96,6.9,6.7,7.00,5.67,4.2
     $1,365.,374.,0.,.6,1.94,3.31,4.32,6.28,7.5,7.73,2.62,2.5,2.57,2.84,
     $8.69,4.21,4.57,2.85,81.8,15.1,13.0,11.9,10.9,9.62,7.23,4.23,584., 
     $600.,0.,.982,2.01,3.05,4.2,5.56,6.72,7.93,9.,10.,7.81,7.64,7.44,  
     $6.65,5.97,5.24,4.96,4.46,84.9,13.6,12.3,10.6,12.5,12.3,3.32,6.45, 
     $665.,681.,0./                                                     
      DATA T15/.94,3.74,1.41,1.59,5.87,8.31,0.,0.,.737,2.25,1.25,8.35   
     $,11.4,0.,1.45,3.35,2.83,2.83,2.27,11.2,14.7,0.,2.06,3.07,2.94,    
     $5.5,9.91,17.3,6.13,18.,22.4,0.,.281,14.4,7.55,7.88,10.2,9.73,     
     $7.38,3.82,15.4,26.4,30.9,0.,0.,0.646,0.471,7.98,0.,10.3,19.1,21.1,
     $21.4,11.2,39.3,36.,41.4,0.,0.,0.180,1.59,.804,1.71,17.5,21.5,25.9,
     $29.1,23.2,24.1,63.7,10.4,46.7,53.,0.,3.1,5.5,6.,3.81,3.3,2.15,2.15
     $,33.,35.,36.,38.,29.,36.,28.,11.,60.5,65.4,0.,.164,2.45,4.27,6.92,
     $8.78,7.43,6.99,4.43,2.81,58.4,48.9,46.2,45.2,33.2,49.3,44.1,22.7, 
     $72.5,76.8,0.,.897,1.71,2.73,3.49,5.29,4.69,6.54,13.2,13.3,14.1,   
     $15.2,15.1,18.2,18.4,23.1,0.,99.8,99.8,100.,110.,83.4,101.,107.,   
     $117.,99.7,0.,1.01,1.91,2.32,3.18,4.55,5.51,5.28,0.,5.5,8.87,18.,  
     $12.5,18.9,8.84,12.9,6.24,15.9,80.1,93.2,94.5,94.5,80.1,75.7,26.4, 
     $19.3,119.,90.8,0./                                                
      DATA AR/4.3,4.7,23.,49.,91.6,170.,330.,4.1,22.,50.,94.,157.,290., 
     #480.,3.1,20.,51.,96.,159.,244.,720.,671.,2.2,15.,44.,91.,150.,    
     #230.,346.,570.,860.,1160.,1.4,8.8,35.,77.,140.,230.,320.,460.,    
     #683.,1130.,2160.,1810.,5.9,10.,37.,55.,120.,210.,300.,430.,580.,  
     #770.,1430.,2150.,3200.,2640.,4.1,18.,27.,57.,120.,170.,270.,400., 
     #550.,740.,920.,1400.,2000.,2910.,4300.,3680.,3.77,19.5,32.3,60.3, 
     !91.2,158.,269.,355.,490.,692.,955.,1230.,1580.,2140.,3070.,       
     !4360.,5800.,4910.,1.12,6.78,39.6,70.8,107.,180.,240.,376.,504.,   
     $646.,851.,1180.,1580.,2040.,2600.,3240.,4610.,5620.,8440.,        
     !6350.,1.42,10.2,33.2,78.,151.,262.,412.,605.,813.,1090.,          
     !1330.,1640.,2000.,2410.,2890.,3420.,3870.,4520.,5250.,6070.,      
     !6980.,7720.,11500.,15800.,14000.,12000.,3.6,10.,14.,16.,38.5,     
     !90.5,175.,304.,891.,1190.,1500.,1910.,2290.,2630.,3160.,          
     !3630.,4030.,4730.,5250.,5750.,6380.,7080.,7940.,8710.,13600.,     
     !18700.,10600.,14500./                                             
      DATA ETA/.672,.624,.645,.803,.791,.721,.726,.608,.639,.676,.765,  
     $.780,.750,.726,.678,.646,.666,.670,.759,.774,.834,.726,.759,.693, 
     $.675,.668,.684,.704,                                              
     $.742,.803,.769,.726,.855,.838,.734,.718,.716,.695,.691,.711,.765, 
     $.829,.821,.726,.601,.786,.693,.821,.735,.716,.702,.688,.703,.714, 
     $.823,.858,.818,.726,.630,.686,.745,.755,.701,.849,.733,.696,.711, 
     $.716,.714,.755,.806,.840,.807,.726,.651,.752,.869,.812,.811,.793, 
     $.744,.910,.801,.811,.793,.702,.790,.774,.819,.854,.803,.726,.900, 
     $.800,.700,.780,.840,.820,.820,.810,.780,.900,.820,.810,.800,.730, 
     $.800,.780,.833,.839,.819,.726,.891,.843,.746,.682,.699,.728,.759, 
     $.790,.810,.829,.828,.834,.836,.840,.846,.850,.836,.824,.816,.811, 
     $.808,.800,.852,.875,.787,.726,.700,.700,.700,.700,.746,.682,.699, 
     $.728,.759,.790,.810,.829,.828,.834,.836,.840,.846,.850,.836,.824, 
     $.816,.811,.808,.800,.842,.868,.732,.726/       

C-----------------------------------------------------------------------      
C     CHECK IF Z.NE.26
C.......................................................................
      IF (Z.EQ.26) THEN
         WRITE(6,1099)
 1099    FORMAT(1X,' THERE WAS AN ATTEMPT TO USE SUBROUTINE "RECOMB"'/
     c      'FOR COMPUTING RECOMBINATION RATES FOR IRON. RECOMB IS NO'/
     C      'LONGER THE BEST SOURCE. USE "RECOFE" INSTEAD!'/
     C      'THE PROGRAMME IS STOPPED!')
         RETURN
C         CALL EXIT(-1)
         END IF
C
      KTEV=TE/11605.                                                    
      KT=KTEV/1000.                                                     
      TL=DLOG10(TE)                                                     
      RDIEL=0.                                                          
      RR=0.                                                             
      RSTOR=0.                                                          
C                                                                       
      IZ=ID(Z)+(S-2)                                                    
C AIGUILLAGE POUR LES DIFFERENTS CAS                                    
      IF(S.GT.Z.OR.Z.EQ.1) GOTO 10                                      
      Z1=Z-1                                                            
      GOTO 11                                                           
C                                                                       
C=======================================================================
C RECOMBINAISON RADIATIVE                                               
C========================================================               
C                                                                       
C                                                                       
C IONS HYDROGENOIDES ( SEATON)                                          
C-----------------------------------------------------------------------
C                                                                       
  10  ALAM=157890.*Z*Z/TE                                               
      RR=5.197D-14*Z*DSQRT(ALAM)*(.4288+.5*DLOG(ALAM)+.469*
     1    (ALAM**(-1./3.)))                                                 
      GOTO 12                                                           
C                                                                       
C AUTRES IONS                                                           
C---------------------------------------------                          
C                                                                       
  11  IF (Z.EQ.11) GO TO 51                                              
      IF (Z.EQ.13) GO TO 52                                              
      RR=1.E-13*AR(IZ)/((TE/1.D4)**ETA(IZ)) 
      GO TO 20                                                          
C                                                                       
C CALCUL DE NA, AL PAR INTERPOLATION                                    
C                                                                       
  51  IZ1=23+(S-3)                                                      
      IZ2=33+(S-1)                                                      
      IF (S.EQ.2) IZ1=34                                                 
      IF (S.EQ.2) IZ2=48                                                 
      GO TO 53                                                          
  52  IZ1=33+(S-3)                                                      
      IZ2=45+(S-1)                                                      
      IF (S.EQ.2) IZ1=46                                                 
      IF (S.EQ.2) IZ2=62                                                 
  53  RR1=1.E-13*AR(IZ1)/((TE/1.D4)**ETA(IZ1))  
      IF (RR1 .LT. REAL_LOW) RR1= REAL_LOW
      RR2=1.E-13*AR(IZ2)/((TE/1.D4)**ETA(IZ2)) 
      IF (RR2 .LT. REAL_LOW) RR2= REAL_LOW
      IF (S.EQ.2) RR=RR1*RR1/RR2                                         
      IF (S.EQ.2) GO TO 54                                               
      AA=DFLOAT(S-1)/DFLOAT(S-2)                                        
      AB=DFLOAT(S)/DFLOAT(S-2)                                          
      U=DLOG10(AA)/DLOG10(AB)                                           
      RR=RR1*((RR2/RR1)**U)                                             
      IF (S.EQ.Z1) GO TO 21                                             
      GO TO 54                                                          
C                                                                       
C                                                                       
C=======================================================                
C RECOMBINAISON DIELECTRONIQUE                                          
C========================================================               
C                                                                       
 20   IF (S.EQ.Z1) GO TO 21                                              
      ARG = 1.D+5 * T15(IZ) / TE                                        
      IF (ARG .GT. 150.) ARG = 150.                                     
      FF=1.E-3*BDI(IZ)*DEXP(-ARG)                                       
      ARG = 1.D+5 * T05(IZ) / TE                                        
      IF (ARG .GT. 150.) ARG = 150.                                     
      FACT=DEXP(-ARG)*(1+FF)                                            
      RDIEL=1.0E-3*ADI(IZ)*(TE**(-1.5))*FACT                             
      GOTO 22                                                           
C                                                                       
C CALCUL DE NA AL PAR INTERPOLATION                                     
C                                                                       
 54   Y1=1.E+5*T15(IZ1)/TE                                              
      IF (Y1.GT.150.) Y1=150.                                            
      FF1=1.E-3*BDI(IZ1)*DEXP(-Y1)                                      
      Y1=1.E+5*T05(IZ1)/TE                                              
      IF (Y1.GT.150.) Y1=150.                                            
      FF1=DEXP(-Y1)*(1+FF1)                                             
      RDIEL1=1.0E-3*ADI(IZ1)*(TE**(-1.5))*FF1                            
      IF (RDIEL1 .LT. REAL_LOW) RDIEL1 = REAL_LOW
      Y2=1.0E+5*T15(IZ2)/TE                                              
      IF (Y2 .GT. 150.) Y2=150.                                            
      FF2=1.0E-3*BDI(IZ2)*DEXP(-Y2)                                      
      Y2=1.0E+5*T05(IZ2)/TE                                              
      IF (Y2.GT.150.) Y2=150.                                            
      FF2=DEXP(-Y2)*(1+FF2)                                             
      RDIEL2=1.0E-3*ADI(IZ2)*(TE**(-1.5))*FF2                            
      IF (RDIEL2 .LT. REAL_LOW) RDIEL2= REAL_LOW
      IF (S.EQ.2) RDIEL=RDIEL1*RDIEL1/RDIEL2                             
      IF (S.EQ.2) GO TO 22                                               
      RDIEL=RDIEL1*((RDIEL2/RDIEL1)**U)                                 
      GO TO 22                                                          
C                                                                       
C RECOMBINAISON DES HELIUMOIDES DE YOUNGER                              
C-----------------------------------------                              
C                                                                       
  21  ZA=DFLOAT(Z-1)                                                    
      ZB=DFLOAT(Z-2)                                                    
      X=3.*ZA/4.                                                        
      AX=DSQRT(X)/(2.*(1.+0.21*X+.03*X*X))                              
      D=3.*ZA*ZA/(ZB*ZB*(1.+.015*(ZB**3.)/(ZA*ZA)))                     
      XY=ZB*ZB+13.4                                                     
      XX=ZA**2.5                                                        
      B=ZB*(XX)/(2.*DSQRT(XY))                                          
      CHI=KTEV/POTLI(Z)                                                 
      Y3=D/CHI                                                          
      IF (Y3.GT.150.) Y3=150.                                            
      RDIEL=3.2D-10*B*AX*DEXP(-Y3)/((CHI**1.5)*(ZB**3.))                
      GO TO 12                                                          
C-----------------------------------------------------------------------
C RECOMBINAISON DE CII,CIII,CIV;NII,NIII,NIV,NV;OII,OIII,OIV,OV,OVI     
C MGII,ALII,ALIII,SIII,SIIII,SIIV                                       
C A BASSE TEMPERATURE NUSSBAUMER ET STOREY                              
C-----------------------------------------------------------------------
C                                                                       
 22   IF (TE.GT.6.D+4) GOTO 23                                           
      IF (S.GT.KSTOR(Z)) GO TO 23                                        
      IST=ISTOR(Z)+S-2                                                  
      T4=TE/1.D4
      AS=DEXP(-FSTOR(IST)/T4)                                           
      AS=AS/(T4**1.5)                                                   
      AS=AS*(BSTOR(IST)+T4*CSTOR(IST)+T4*T4*DSTOR(IST)+ASTOR(IST)/T4)   
      RSTOR=1.0D-12*AS                                                   
      IF (Z.NE.14.OR.TL.GT.4.7) GO TO 12                                 
C                                                                       
C                                                                       
C CORRECTION DES FITS DE SHULL A BASSE TEMPERATURE                      
C POUR SI II,SI III                                                     
C--------------------------------------------------                     
C                                                                       
       IF (S.EQ.2.AND.TL.LE.4.3) RDIEL=4.35D-23*(TE**2.64)               
       IF (S.EQ.3) RDIEL=8.16D-3*DEXP(-1.07D+5/TE)/(TE**1.5)             
C                                                                       
C                                                                       
C CORRECTION DES FITS DE SHULL A HAUTE TEMPERATURE                      
C POUR NEVII,NEVIII,SVI,SXIII,SXIV,CAXVIII                              
C--------------------------------------------------                     
C                                                                       
  23   IF (Z.EQ.10) GO TO 100                                            
       IF (Z.EQ.16) GO TO 101                                            
       IF (Z.EQ.20) GO TO 102                                            
       GO TO 12                                                         
 100   IF (S.EQ.7.AND.TL.GE.6.35) RDIEL=1.22D-6/(TE**.81)                
       IF (S.EQ.8.AND.TL.GE.6.35) RDIEL=1.52D-7/(TE**.77)                
       GO TO 12                                                         
 101   IF (S.EQ.6.AND.TL.GE.6.5) RDIEL=1.08D-2/(TE**1.46)                
       IF (S.EQ.13.AND.TL.GE.6.6) RDIEL=5.20D-6/(TE**.86)                
       IF (S.EQ.14.AND.TL.GE.6.7) RDIEL=8.00D-10/(TE**.41)               
       GO TO 12                                                         
 102   IF (S.EQ.18.AND.TL.GE.6.8) RDIEL=6.29D-3/(TE**1.41)               
       GO TO 12                                                         
C      IF (Z.EQ.26.AND.S.EQ.17.) RDIEL=.86*DEXP(-560./KTEV)/(TE**1.5)    
 12   RDIEL=RSTOR+RDIEL                                                 
       RETURN                                                           
       END                                                              
C
C 
      SUBROUTINE RECOFE(Z,S,TE,RR,RDIEL)
C=======================================================================
C This subroutine computes the recombination rates
C (radiative and dielectronique) for iron only. 
C 
C S     is the ionicity of the recombining ion EX: s=1 for FeI
C Z     is the nuclear charge here Z=26
C TE    is the temperature in Kelvin
C RR    is the radiative recombination rate in cm+3/s
C RDIEL IS the dielectronic recombination rate in cm+3/s
C
C Modifications:
C---------------
C 
C     IMPLEMENTED ON JUNE 20, 1994 INTO ARNMAIN.FOR
C      BY PETER BOCHSLER
C  
C     Adated for SUN/UNIX  by Peter Wurz, Jannuary 22, 1998
C=======================================================================
      IMPLICIT REAL*8(A-H,O-Z) 
      INTEGER Z,S
      DIMENSION AR(26),ETA(26),BETA(26)
      DATA AR/1.42,10.2,33.2,78.,151.,262.,412.,605.,813.,1090.,
     1        1330.,1640.,2000.,1460.,1680.,1910.,2240.,2590.,2960.,
     2        3160.,3490.,3910.,4330.,4770.,5840.,0./ 
      DATA ETA/.891,.843,.746,.682,.699,.728,.759,.790,.810,.829,
     1         .828,.834,.836,.597,.602,.601,.579,.567,.557,.534,
     2         .521,.523,.531,.537,.546,.0/ 
      DATA BETA/13*0.,5.22,5.07,5.10,5.49,5.65,5.79,6.02,6.22,6.15,
     1          5.77,5.49,4.02,0./
C-----------------------------------------------------------------------
      RR=0. 
      IZ=S-1
C------------------------------
C IONS HYDROGENOIDES ( SEATON)
C------------------------------ 
      IF(S.GT.Z.OR.Z.EQ.1) THEN     
      ALAM=157890.*Z*Z/TE
      RR=5.197D-14*Z*SQRT(ALAM)*(.4288+.5*DLOG(ALAM)+.469*
     &(ALAM**(-1./3.))) 
      RETURN 
      ENDIF
C 
C AUTRES IONS 
C---------------
C 
      TE4=TE/1.D4
      RR=1.E-13*AR(IZ)/(TE4**(ETA(IZ)+BETA(IZ)*1.D-2*DLOG10(TE4))) 

C RECOMBINAISON DIELECTRONIQUE
C-----------------------------
      RDIEL=alphadi(Z,S,TE)
C
      RETURN
      END


      FUNCTION ALPHADI(N,J,T)
C=======================================================================
c  returns value of dielectronic recombination rate coefficient.
c  for now, does only iron (n=26)
c  J is the ionicity : J=1 for Fe I, 2 for Fe II ...
c  T is in Kelvin
c  result is cm**3 s**-1
c  data arrays contain coefficients for a sum of terms
c        T**-1.5 * A * EXP(-E1*11590./T)
c  Fe XXV - Karim&Bhalla : XXV - Chen : XXIV -  McLH & Romanik
c  XXIII-XXII - Badnell : XXI-XIX - Roszman
c  XVIII - Dasgupta&Whitney : XVII Smith etal scaled to Chen
c  XVI - II : Sarazin, Shull&Woods ?
C   
C Modifications:
C---------------
C  IMPLEMENTED INTO ARNMAIN.FOR BY PETER BOCHSLER ON JUNE 20, 1994
C
C  Adapted for SUN/UNIX by Peter Wurz, January 22, 1998
C.......................................................................
      IMPLICIT REAL*8 (A-H,O-Z) 
      DIMENSION A(4,25),E1(4,25)
C-----------------------------------------------------------------------
c  data for Shull and van Steenberg for Fe XVI-II
c     data a/0.43,3*0., .256,.452,2*0., .011,.0488,.0801,.529,
C    1  .131,0.,.613,.0849,  .129,.00092,.912,.192,
c    2  .0185,.0953,.079,1.23, .016,.0717,.0906,.739,
c    3  .00567,.0782,.0318,1.263, 
c    4  .0336,.00253,1.92,.181, 1.23,3*0., 
c    5  .12,.12,2*0., .19,.09,2*0., .26,.16,2*0., .24,.17,2*0.,
c    6  .20,.30,2*0., .10,.53,2*0., .14,.46,2*0., .15,.63,2*0.,
c    7  .29,.067,2*0., .25,.025,2*0., .12,.043,2*0., .038,.016,2*0.,
c    8  .015,.0047,2*0., .0084,.0027,2*0., .0016,.000736,2*0./
c  e1 for Fe XIII looks odd
c     data e1/5300.,3*0., 4625.,6000.,2*0., 0.1,36.2,306.,928.,
c    1  73.2,0.,877.,316.,  80.3,39.1,919.,392.,
c    2  13.2,66.6,297.,714., 23.7,85.1,329.,787.,
c    3  16.2,96.0,330.,729.,
c    4  117.,22.5,683.,341., 560.,3*0., 
c    5  24.6,248.,2*0.,39.4,198.,2*0.,36.3,193.,2*0.,75.0,205.,2*0.,
c    6  24.5,155.,2*0.,22.2,144.,2*0.,21.6,136.,2*0.,22.6,136.,2*0.,
c    7  66.7,123.,2*0.,64.7,105.,2*0.,54.2,100.,2*0.,37.3,67.4,2*0.,
c    8  28.6,52.1,2*0.,16.7,31.4,2*0.,5.12,12.9,2*0./

c  SvS scaled for Fe XIII- XVI, with Zhdanov inner shell added :
c  Hahn for Fe XII and Fe VII
c  SvS high T scaled to Hahn for Fe X,XI 
c  Burgess formula for Fe IX
c  SvS scaled to Hahn for Fe VIII, Fe II-VI
C-----------------------------------------------------------------------
      DATA A/0.43,3*0., .256,.452,2*0., .011,.0488,.0801,.529,
     1       .131,0.,.613,.0849,  .129,.00092,.912,.192,
     2       .0185,.0953,.079,1.23, .016,.0717,.0906,.739,
     3       .00567,.0782,.0318,1.263,
     4       .0336,.00253,1.92,.181, 1.23,3*0.,
     5       .12,.12,.6,0., .19,.09,2*0., .26,.16,2*0., .24,.17,2*0.,
     6       .225,.231,2*0., .10,.28,2*0., .14,.26,2*0., .62,.24,2*0.,
     7       .16,.036,2*0.,.092,.041,2*0.,.08,.024,2*0., .038,.016,2*0.,
     8       .015,.0047,2*0., .0023,.0027,2*0., .00022,.0001,2*0./
      DATA E1/5300.,3*0., 4625.,6000.,2*0., 0.1,36.2,306.,928.,
     1        73.2,0.,877.,316.,  80.3,39.1,919.,392.,
     2        13.2,66.6,297.,714., 23.7,85.1,329.,787.,16.2,96.0,330.,
     3        729.,117.,22.5,683.,341., 560.,3*0.,24.6,248.,560.,0.,
     4        39.4,198.,2*0.,36.3,193.,2*0.,75.0,205.,2*0.,59.6,362.,
     5        2*0.,22.2,144.,2*0.,21.6,136.,2*0.,66.1,129.,2*0.,66.7,
     6        123.,2*0.,45.5,360.,2*0.,54.2,100.,2*0.,37.3,67.4,2*0.,
     7        28.6,52.1,2*0.,16.7,31.4,2*0.,5.12,12.9,2*0./
C-----------------------------------------------------------------------
      AD = 0.
      DO 10 I = 1,4
   10 AD = AD + A(I,N-J+1) * DEXP(-E1(I,N-J+1)*11590./T)
      ALPHADI = AD * T ** (-1.5)
      RETURN
      END


	SUBROUTINE IONSUB(Z,AKTEV,AUTO,DIR,RION)
c***********************************************************************
C     THIS PROGRAM IS A COMPLETE REWRITING FOLLOWING INSTRUCTIONS FROM
C     M. ARNAUD ON JUNE 20, 1994
C
C     MODIFICATIONS:
C     --------------
C     Peter Wurz, 19/08/1996: Changed to D_FLOAT format
C     Peter Wurz,  4/09/1996: enabled shared use of input data 
C     Peter Wurz,  9/11/1997: removed reading of data files
C     Peter Wurz  20/01/1998: Adapted for SUN/UNIX
C-----------------------------------------------------------------------
	IMPLICIT REAL*8(A-H,O-Z)

 	INTEGER*4 Z,ZR,LINE(15),ILINES(15),IZ(15),ELNO,ELMIN
	INTEGER*4 ION_LINE
	REAL*8 REAL_LOW
	REAL*8 REL(5),RELEA(6),RION(28),AUTO(28),DIR(28)

        PARAMETER (REAL_LOW=1.0D-38)

	DATA LINE/1,2,4,14,26,40,58,78,102,127,156,188,224,266,326/
	DATA IZ/1,2,6,7,8,10,11,12,13,14,16,18,20,26,28/
C----------------------------------------------------------------------
      DO 100, IEL=1,15
           IF (IEL.EQ.1) ILINES(IEL)=1
           IF (IEL.GT.1 .AND. IEL.LE.7) ILINES(IEL)=2*(IZ(IEL)-1)
           IF (IEL.GT.7 .AND. IEL.LE.12) ILINES(IEL)=2*IZ(IEL)
           IF (IEL.EQ.13) ILINES(IEL)=42
           IF (IEL.EQ.14) ILINES(IEL)=60
           IF (IEL.EQ.15) ILINES(IEL)=66
           IF (IZ(IEL).EQ.Z) THEN
                ELNO=  IEL
                ELMIN= IEL-1
                GO TO 101
                END IF
  100      CONTINUE
  101   LINEND=0
        DO 110 IEL=1,ELNO
           LINEND=ILINES(IEL)+LINEND    
  110      CONTINUE
        LINESTAR = LINEND-ILINES(ELNO)
        NLINES = ILINES(ELNO)
	IF (LINESTAR.GT.0) CALL DIR_DATA(LINESTAR,ZR,IR,KR,REL)
	ION_LINE = 0
	DO 210 IEL=1,ELMIN
		ION_LINE = ION_LINE + IZ(IEL)
210		CONTINUE
	IF (ION_LINE.GT.0) CALL EA(ION_LINE,ZR,IR,RELEA)
C----------------------------------------
C     reset array of rates
C----------------------------------------
      DO 400 ION=1,Z
      dir(ion)=0.d0
      auto(ion)=0.d0
      rion(ion)=0.d0
c
      nel = z-ion+1
      sd = 0.0d0
      nj = 1
      if (nel.gt.2  .and. nel.le.10) nj = 2
      if (nel.gt.10 .and. nel.le.12) nj = 3
      if (nel.gt.12 .and. nel.le.18) nj = 2
      if (nel.gt.18)                 nj = 3
      if (z.eq.11 .and. ion.eq.1)    nj = 2   
      DO 300 IELE=1,NJ
	   CALL DIR_DATA(LINESTAR+IELE,ZR,IR,KR,REL)
c          ................................................................
c          exclude mismatches in dir.dat
c          ................................................................
           IF (ZR.NE.Z .OR. IR.NE.ION .OR. KR.NE.IELE) THEN
	      	WRITE(6,1001) ZR,Z,IR,ION,KR,IELE
 1001 		FORMAT(1X, 'ARNAUD> mismatch in input DIR.DAT:'/, 
     1	               3(i2,' ?=? ',i5,5x),/,
     2		       ' ARNAUD> The program is stopped in subroutine',
     3                 ' IONSUB ')
		WRITE(6,1002) LINESTAR+IELE
 1002		FORMAT(1X,T9,'at line',I6)
                RETURN
C		CALL EXIT(-1)
		end if
c          write(6,1002) zr,z,ir,ion,kr,iele,rel
c 1002     format(1h ,6(i2,1x),5(0pf11.5))
           a = rel(2)
           b = rel(3)
           c = rel(4)
           d = rel(5)
           pion = rel(1)
           x = pion/aktev
           sa = a*fa(x) + b*fb(x) + c*fu(x) + d*x*f2(x)
C          if (x.gt.150.d0) x=150.d0
  	   x = min(150.0d0,x)
           sd = sd + sa*dexp(-x)/x
  300      CONTINUE
         LINESTAR = LINESTAR+NJ
C        if (sd .lt. REAL_LOW) sd=REAL_LOW
	 sd = max(sd, REAL_LOW)
         dirlog = dlog10(sd) + dlog10(6.692d-7) - 1.5d0*dlog10(aktev)
C 	 if (dirlog.lt.-150.d0) dir(ion) = 0.0d0
C        if (dirlog.ge.-150.d0) dir(ion) = 10.0d0**dirlog
 	 if (dirlog.lt.-70.d0) dir(ion) = 0.0d0
         if (dirlog.ge.-70.d0) dir(ion) = DEXP(dirlog*DLOG(10.0D0))
C-----------------------------------------------------------------------
c     excitation autoionisation
C-----------------------------------------------------------------------
	CALL EA(ION_LINE+ION,ZR,IR,RELEA)
C	WRITE(6,*) ION_LINE+ION,ZR,IR,RELEA
c     ...............................
c     exclude mismatch in ea.dat
c     ...............................
      if (zr.ne.z .or .ir.ne.ion) then
	      write(6,1003) zr,z,ir,ion,ION_LINE+ION
 1003 	     format(1X,'ARNAUD> Mismatch in input EA.DAT: ',
     c              2(i2,' ?=? ',i2,5x)/,
     2              1X,T10,'at line ',I6,/, 
     c              1X,'ARNAUD> The program is stopped!')
             RETURN
C             CALL EXIT(-1)
             end if
c     
      auto(ion) = 0.d0
      a = relea(2)
      b = relea(3)
      c = relea(4)
      d = relea(5)
      e = relea(6)
      pion = relea(1)
      if (pion.ge.1.d-6) then
      x = pion/aktev
      sea = a + b*fa(x)+c*fc(x)+d*fd(x)+e*fu(x)
      if (x.gt.150.d0) x = 150.d0
      sealog = dlog(sea)-x
      autlog = dlog(1.d-16)+dlog(6.692d7)+sealog-0.5d0*dlog(aktev)
      auto(ion)=dexp(autlog)
      end if
c     .........................................
c     processus dit 'reda' (La Gattuta et Hahn)
c     .........................................
      if (z.eq.26 .and. ion.eq.16) then
             call redan(aktev,redac)
             auto(ion)=auto(ion)+redac
      else
             redac = 0.d0
             endif
      rion(ion) = dir(ion) + auto(ion)
c     write(6,1011)ion,rion(ion),dir(ion),auto(ion)
 1011 format(1h ,' ionisation rates for ion: ',i3/
     c3(1pd12.5,2x))
  400 continue    
C      close(unit=5,status='keep')
C      close(unit=4,status='keep')
      return
      end


C==================================== 
      FUNCTION FU(X)
C==================================== 
      IMPLICIT REAL*8 (A-H,O-Z)
C------------------------------------ 
      IF(X.GE.10.) GO TO 1
      IF(X.LE.0.02) GO TO 2 
C APPROXIMATION FROM M-S-(1978) 
      IF(X.LT.1.5) EPS=-0.5 
      IF(X.GE.1.5) EPS=0.5
      R=(1.+X)/X
      Q2=1./((1.+X)*(1.+X)) 
      FU=DLOG(R)-(0.36+0.03*((X+0.01)**EPS))*Q2 
      RETURN
  1   FU=(1.-1./X+2./(X*X)-6./(X*X*X))/X
      RETURN
  2   FU = DEXP(X)*(-DLOG(X)-0.5772 + X)
      RETURN
      END 

C==================================== 
      FUNCTION FA(X)
C==================================== 
      IMPLICIT REAL*8 (A-H,O-Z) 
C------------------------------------
      IF (X.LT.10) THEN    
            FA=1.0-X*FU(X) 
      ELSE      
            FA=(1.0-2.0/X+6.0/(X*X)-24.0/(X*X*X)+120./(X*X*X*X))/X
            ENDIF
      RETURN
      END 

C==================================== 
      FUNCTION FC(X)
C==================================== 
      IMPLICIT REAL*8 (A-H,O-Z) 
C------------------------------------
      IF (X.LT.10) THEN    
	FC=1.-X*FA(X) 
	RETURN    
      ELSE      
	FC=2./X-6./(X*X)+24./(X*X*X)-120./(X*X*X*X)
	RETURN    
      ENDIF
      END 

C==================================== 
      FUNCTION FD(X)
C==================================== 
      IMPLICIT REAL*8 (A-H,O-Z) 
C------------------------------------
      IF(X.LE.10) THEN    
	FD = 1. -0.5* X * (1. - X + X*X*FU(X))
	RETURN    
      ELSE    
	FD =3./X-12./(X*X) +60./(X*X*X)-360./(X*X*X*X) 
	RETURN    
      ENDIF
      END

C==================================== 
      FUNCTION FB(X)
C==================================== 
      IMPLICIT REAL*8 (A-H,O-Z) 
C------------------------------------
      IF(X.LT.1.) THEN    
      FB=1.+X-X*FU(X)*(2.+X)
      RETURN              
      ELSE
      FB=2.*X*X*X*X + 60.*X*X*X + 540.*X*X + 1512.*X + 720. 
      FB=FB/(X*X*X*X*X+35.*X*X*X*X+416.*X*X*X+2016.*X*X+3708.*X+1764.)
      FB=FB*FU(X) 
      RETURN    
      ENDIF
      END 

C============================================================ 
      FUNCTION F2(X)
C
C Adapted for use at SUN/UNIX by Peter Wurz, January 23, 1998
C============================================================
      IMPLICIT REAL*8 (A-H,O-Z) 
      DIMENSION AP(14),AQ(14) 
      DATA AP/      2.165775917955525D+2, 2.033587105342909D+4
     ]             ,1.091065065646484D+6, 3.711399580079484D+7
     ]             ,8.396327345237503D+8, 1.288918149583380D+10 
     ]             ,1.344856883951851D+11,9.400171941902539D+11 
     ]             ,4.257075535864156D+12,1.174304576501000D+13 
     ]             ,1.754867504059569D+13,1.080630148187369D+13 
     ]             ,4.977620100319121D+11,0.D+1/
      DATA AQ/      2.195775917955525D+2, 2.098360382881574D+4
     ]             ,1.151650523623183D+6, 4.034883260913706D+7
     ]             ,9.490018565225945D+8, 1.534455719230511D+10 
     ]             ,1.718164841585205D+11,1.324851363645336D+12 
     ]             ,6.907059906460437D+12,2.353091122612837D+13 
     ]             ,4.943221846942425D+13,5.776015744186425D+13 
     ]             ,3.022538587683950D+13,3.364065905726312D+12/
C------------------------------------
      U=1.0/X
      IF (X.LT.10.) THEN    
	      U2=U*U
	      U3=U2*U 
	      U4=U3*U 
	      F2=(-0.0005725 + 0.01345*U + 0.8691*U2 + 0.03404*U3) / 
     1           (1.0 + 2.197*U + 0.2454*U2 + 0.002053*U3) 
      ELSE
	      AN=1.0D+0
	      AD=1.0D+0
              UE=1.0D+0
	      DO 200 II=1,14
                   UE=UE*U
C	           AN=AN + AP(II)*(U**II ) 
C  	           AD=AD + AQ(II)*(U**II ) 
	           AN=AN + AP(II)*UE 
  	           AD=AD + AQ(II)*UE
 200               CONTINUE
	      F2=AN*U*U/AD
	      ENDIF
      RETURN
      END 

c******************************************************************************
c     subroutine redan
C
C MODIFICATIONS:
C---------------
c     implemented on June 20, 1994 by P. Bochsler
C     Adapted for SUN/UNIX , January 22, 1998 by Peter Wurz
C.......................................................................
      SUBROUTINE REDAN(AKTEV,REDAC)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION REDAS(12)

      DATA REDAS/0.55D0,0.60D0,2.70D0,1.50D0,0.40D0,0.10D0,0.80D0,
     C           0.70D0,1.15D0,0.65D0,0.65D0,0.20D0/
C-----------------------------------------------------------------------
      SK=0.D0
      DO 2 K=1,12
	      ED = 720.D0+20.D0*DFLOAT(K-1)
	      EF = ED+20.D0
	      YD = ED/AKTEV
	      YF = EF/AKTEV
	      FD = DEXP(-YD)*(YD+1.D0)
	      FF = DEXP(-YF)*(YF+1.D0)
	      SK = SK +1.D-19*REDAS(K)*(FD-FF)
    2 	      CONTINUE
      REDAC=6.692D7*SK*DSQRT(AKTEV)
      RETURN
      END

	SUBROUTINE DIR_DATA(INDEX,ZR,IR,KR,REL)
C=======================================================================
C This subroutine replaces the open and read statements in the 
C subroutine IONSUB of the Arnaud program.
C
C Author:
C Peter Wurz,   6. Nov. 1997 Initial version
C Peter Wurz,  20. Jan. 1998 Adaptations for SUN/UNIX
C-----------------------------------------------------------------------
	INTEGER*4 INDEX		! Index of data set

	INTEGER*4 ZR 		! Atomic number
	INTEGER*4 IR 		! Ionization state
	INTEGER*4 KR 		! 
	INTEGER*4 COARSE	! Coarse array selector
	INTEGER*4 REMAIN 	! Pointer in array
	INTEGER*4 SIZE 		! Array size

	PARAMETER (SIZE=100)

	REAL*8 REL(5)
	REAL*8 DIR_DATA_1(8,SIZE-1)
	REAL*8 DIR_DATA_2(8,0:SIZE-1)
	REAL*8 DIR_DATA_3(8,0:SIZE-1)
	REAL*8 DIR_DATA_4(8,0:91)
C-----------------------------------------------------------------------
	DATA DIR_DATA_1/1.,1.,1., 13.6,   22.8,  -12.0,    1.9,  -22.6,
     C       2.,  1.,  1.,     24.6,   17.8,  -11.0,    7.0,  -23.2,
     C       2.,  2.,  1.,     54.4,   14.4,   -5.6,    1.9,  -13.3,
     C       6.,  1.,  1.,     11.3,    6.0,  -16.0,   12.0,  -15.1,
     C       6.,  1.,  2.,     16.6,   24.3,   -7.8,    2.5,  -24.0,
     C       6.,  2.,  1.,     24.4,   17.3,   -9.0,    2.5,  -13.6,
     C       6.,  2.,  2.,     30.9,   23.7,   -7.6,    2.5,  -21.7,
     C       6.,  3.,  1.,     47.9,   23.2,   -7.4,    2.5,  -19.4,
     C       6.,  3.,  2.,    325.0,   20.0,   -5.6,    4.1,  -18.0,
     C       6.,  4.,  1.,     64.5,    8.2,   -2.7,    1.4,   -6.6,
     C       6.,  4.,  2.,    343.0,   20.0,   -5.6,    4.1,  -18.0,
     C       6.,  5.,  1.,    392.0,   20.4,   -6.1,    4.5,  -18.0,
     C       6.,  6.,  1.,    490.0,   12.2,   -3.9,    1.9,  -10.3,
     C       7.,  1.,  1.,     14.5,   19.5,  -30.5,   15.0,  -29.0,
     C       7.,  1.,  2.,     20.3,   19.0,   -4.5,    2.8,  -20.2,
     C       7.,  2.,  1.,     29.6,   25.0,   -6.3,    5.3,  -25.7,
     C       7.,  2.,  2.,     36.7,   18.5,   -4.3,    2.8,  -18.0,
     C       7.,  3.,  1.,     47.4,   16.0,   -7.5,    2.3,  -10.0,
     C       7.,  3.,  2.,     55.8,   18.1,   -4.0,    2.8,  -15.8,
     C       7.,  4.,  1.,     77.5,   17.6,   -3.8,    2.8,  -13.6,
     C       7.,  4.,  2.,    471.0,   20.5,   -5.8,    4.1,  -18.0,
     C       7.,  5.,  1.,     97.9,   10.5,   -3.3,    1.4,   -7.7,
     C       7.,  5.,  2.,    493.0,   20.5,   -5.8,    4.1,  -18.0,
     C       7.,  6.,  1.,    552.0,   20.8,   -6.3,    4.4,  -18.2,
     C       7.,  7.,  1.,    667.0,   12.3,   -4.0,    1.9,  -10.3,
     C       8.,  1.,  1.,     13.6,    3.5,  -18.5,   15.6,  -16.6,
     C       8.,  1.,  2.,     28.5,   18.2,   -4.0,    2.8,  -20.2,
     C       8.,  2.,  1.,     35.1,   26.0,   -8.0,    8.4,  -28.2,
     C       8.,  2.,  2.,     42.6,   17.8,   -3.9,    2.8,  -18.1,
     C       8.,  3.,  1.,     54.9,   25.0,   -7.0,    5.0,  -18.0,
     C       8.,  3.,  2.,     63.8,   17.3,   -3.5,    2.9,  -16.1,
     C       8.,  4.,  1.,     77.4,   15.0,   -5.0,    2.2,  -10.5,
     C       8.,  4.,  2.,     87.6,   16.8,   -3.3,    2.8,  -14.1,
     C       8.,  5.,  1.,    114.0,   16.4,   -3.0,    2.9,  -12.0,
     C       8.,  5.,  2.,    644.0,   20.8,   -6.0,    4.1,  -18.0,
     C       8.,  6.,  1.,    138.0,   10.9,   -3.19,   1.4,  -9.21,
     C       8.,  6.,  2.,    670.0,   20.8,   -6.0,    4.1,  -18.0,
     C       8.,  7.,  1.,    739.0,   21.2,   -6.5,    4.3,  -18.4,
     C       8.,  8.,  1.,    871.0,   12.3,   -4.0,    1.9,  -10.3,
     C       10.,  1.,  1.,     21.6,   40.0,  -42.0,   18.0,  -56.0,
     C       10.,  1.,  2.,     48.5,   19.1,   -4.9,    2.8,  -21.8,
     C       10.,  2.,  1.,     41.1,   33.8,  -20.4,   15.5,  -46.0,
     C       10.,  2.,  2.,     66.4,   18.6,   -4.7,    2.8,  -20.2,
     C       10.,  3.,  1.,     63.5,    7.5,  -17.5,   25.0,  -19.7,
     C       10.,  3.,  2.,     86.2,   18.2,   -4.4,    2.8,  -18.4,
     C       10.,  4.,  1.,     97.1,   34.0,  -10.0,    7.5,  -25.0,
     C       10.,  4.,  2.,    108.0,   17.8,   -4.1,    2.8,  -16.7,
     C       10.,  5.,  1.,    126.0,   25.5,   -8.5,    4.5,  -16.8,
     C       10.,  5.,  2.,    139.0,   17.4,   -3.8,    2.8,  -14.9,
     C       10.,  6.,  1.,    158.0,   14.5,   -4.6,    1.9,   -8.5,
     C       10.,  6.,  2.,    172.0,   16.9,   -3.4,    2.8,  -13.2,
     C       10.,  7.,  1.,    207.0,   16.5,   -3.1,    2.8,  -11.4,
     C       10.,  7.,  2.,   1073.0,   21.5,   -6.4,    4.1,  -18.0,
     C       10.,  8.,  1.,    239.0,   10.1,   -3.1,    1.4,   -7.1,
     C       10.,  8.,  2.,   1107.0,   21.5,   -6.4,    4.1,  -18.0,
     C       10.,  9.,  1.,   1196.0,   21.9,   -6.8,    4.2,  -18.7,
     C       10., 10.,  1.,   1362.0,   12.5,   -4.1,    1.9,  -10.4,
     C       11.,  1.,  1.,      5.1,   16.0,   -1.0,    0.2,  -13.5,
     C       11.,  1.,  2.,     34.0,   63.9,  -27.0,   33.0,  -80.0,
     C       11.,  2.,  1.,     47.3,   48.5,  -33.5,   19.4,  -65.9,
     C       11.,  2.,  2.,     80.1,   19.2,   -5.3,    2.8,  -21.2,
     C       11.,  3.,  1.,     71.7,   50.1,  -20.2,   14.8,  -41.7,
     C       11.,  3.,  2.,    102.0,   18.8,   -5.0,    2.8,  -19.6,
     C       11.,  4.,  1.,     99.0,   43.3,  -16.3,   10.7,  -33.4,
     C       11.,  4.,  2.,    126.0,   18.4,   -4.7,    2.8,  -18.0,
     C       11.,  5.,  1.,    138.0,   35.1,  -12.4,    7.2,  -25.1,
     C       11.,  5.,  2.,    151.0,   18.3,   -4.3,    2.8,  -16.3,
     C       11.,  6.,  1.,    172.0,   25.5,   -8.5,    4.2,  -16.8,
     C       11.,  6.,  2.,    186.0,   17.6,   -4.0,    2.8,  -14.7,
     C       11.,  7.,  1.,    208.0,   14.5,   -4.6,    1.8,   -8.5,
     C       11.,  7.,  2.,    224.0,   17.2,   -3.7,    2.8,  -13.1,
     C       11.,  8.,  1.,    264.0,   16.8,   -3.4,    2.8,  -11.4,
     C       11.,  8.,  2.,   1328.0,   21.7,   -6.5,    4.1,  -18.0,
     C       11.,  9.,  1.,    300.0,   10.0,   -3.0,    1.4,   -6.9,
     C       11.,  9.,  2.,   1366.0,   21.7,   -6.5,    4.1,  -18.0,
     C       11., 10.,  1.,   1465.0,   22.2,   -7.0,    4.2,  -18.8, 
     C       11., 11.,  1.,   1649.0,   12.5,   -4.1,    1.9,  -10.4,
     C       12.,  1.,  1.,      7.6,   18.0,   -1.0,    0.6,   -4.0,
     C       12.,  1.,  2.,     54.0,   37.7,  -30.0,   24.8,  -62.0,
     C       12.,  1.,  3.,     92.2,   17.6,   -5.2,    3.3,  -19.0,
     C       12.,  2.,  1.,     15.0,    9.0,   -3.6,    0.3,   -5.4,
     C       12.,  2.,  2.,     65.0,   37.7,  -30.0,   24.8,  -62.0,
     C       12.,  2.,  3.,    104.5,   17.6,   -5.2,    3.3,  -19.0,
     C       12.,  3.,  1.,     80.1,   55.5,  -24.1,   18.7,  -65.0,
     C       12.,  3.,  2.,    119.0,   19.3,   -5.6,    2.8,  -20.5,
     C       12.,  4.,  1.,    109.0,   50.1,  -20.2,   14.2,  -41.7,
     C       12.,  4.,  2.,    144.0,   19.1,   -5.3,    2.8,  -19.0,
     C       12.,  5.,  1.,    141.0,   43.3,  -16.3,   10.3,  -33.4,
     C       12.,  5.,  2.,    172.0,   18.6,   -4.9,    2.8,  -17.5,
     C       12.,  6.,  1.,    187.0,   35.1,  -12.4,    6.9,  -25.1,
     C       12.,  6.,  2.,    201.0,   18.4,   -4.6,    2.8,  -16.0,
     C       12.,  7.,  1.,    225.0,   25.5,   -8.5,    4.1,  -16.8,
     C       12.,  7.,  2.,    241.0,   18.0,   -4.3,    2.8,  -14.5,
     C       12.,  8.,  1.,    266.0,   14.5,   -4.6,    1.8,   -8.5,
     C       12.,  8.,  2.,    283.0,   17.5,   -4.0,    2.8,  -13.0,
     C       12.,  9.,  1.,    328.0,   17.1,   -3.6,    2.7,  -11.5,
     C       12.,  9.,  2.,   1611.0,   22.0,   -6.7,    4.1,  -18.0,
     C       12., 10.,  1.,    367.0,   10.0,   -3.0,    1.4,   -6.8,
     C       12., 10.,  2.,   1653.0,   22.0,   -6.7,    4.1,  -18.0/
C-----------------------------------------------------------------------
	DATA DIR_DATA_2/12., 11., 1., 1762.0,  22.4,  -7.1,  4.1, -18.9,
     C       12., 12.,  1.,   1963.0,   12.6,   -4.2,    1.9,  -10.4,
     C       13.,  1.,  1.,      6.0,   47.0,  -26.0,    0.6,  -39.0,
     C       13.,  1.,  2.,     10.6,   55.1,  -37.2,    1.4,  -41.0,
     C       13.,  2.,  1.,     18.8,   17.0,   -6.0,    1.0,   -8.0,
     C       13.,  2.,  2.,     90.0,   31.3,  -22.7,   21.0,  -44.1,
     C       13.,  2.,  3.,    131.0,   12.1,   -3.5,    3.3,  -13.1,
     C       13.,  3.,  1.,     28.4,    6.3,   -2.4,    0.5,   -4.1,
     C       13.,  3.,  2.,    103.0,   31.3,  -22.7,   21.0,  -44.1,
     C       13.,  3.,  3.,    145.6,   12.1,   -3.5,    3.3,  -13.1,
     C       13.,  4.,  1.,    120.0,   69.8,  -23.7,   18.0,  -69.8,
     C       13.,  4.,  2.,    164.0,   19.5,   -5.9,    2.8,  -19.8,
     C       13.,  5.,  1.,    154.0,   60.8,  -20.2,   13.7,  -41.7,
     C       13.,  5.,  2.,    194.0,   19.2,   -5.5,    2.8,  -18.4,
     C       13.,  6.,  1.,    190.0,   49.5,  -16.3,    9.9,  -33.4,
     C       13.,  6.,  2.,    225.0,   18.9,   -5.2,    2.8,  -17.1,
     C       13.,  7.,  1.,    241.0,   38.3,  -12.4,    6.7,  -25.1,
     C       13.,  7.,  2.,    258.0,   18.5,   -4.8,    2.8,  -15.7,
     C       13.,  8.,  1.,    285.0,   27.0,   -8.5,    3.9,  -16.8,
     C       13.,  8.,  2.,    302.0,   18.2,   -4.5,    2.8,  -14.3,
     C       13.,  9.,  1.,    330.0,   14.0,   -4.6,    1.7,   -8.5,
     C       13.,  9.,  2.,    350.0,   17.9,   -4.1,    2.8,  -13.0,
     C       13., 10.,  1.,    399.0,   17.4,   -3.8,    2.7,  -11.6,
     C       13., 10.,  2.,   1921.0,   22.2,   -6.8,    4.1,  -18.0,
     C       13., 11.,  1.,    442.0,    9.9,   -3.0,    1.4,   -6.7,
     C       13., 11.,  2.,   1967.0,   22.2,   -6.8,    4.1,  -18.0,
     C       13., 12.,  1.,   2086.0,   22.7,   -7.2,    4.1,  -19.0,
     C       13., 13.,  1.,   2304.0,   12.6,   -4.2,    1.9,  -10.4,
     C       14.,  1.,  1.,      8.1,   74.5,  -49.4,    1.3,  -54.6,
     C       14.,  1.,  2.,     13.5,   53.8,  -35.8,    1.4,  -40.7,
     C       14.,  2.,  1.,     16.3,   50.4,  -33.4,    0.6,  -36.9,
     C       14.,  2.,  2.,     22.9,   55.1,  -37.2,    1.4,  -41.0,
     C       14.,  3.,  1.,     33.5,   19.8,   -5.7,    1.3,  -11.9,
     C       14.,  3.,  2.,    133.0,   66.7,  -24.8,   18.7,  -65.0,
     C       14.,  3.,  3.,    176.6,   22.0,   -7.2,    3.3,  -20.9,
     C       14.,  4.,  1.,     45.1,    9.0,   -3.0,    0.6,   -5.8,
     C       14.,  4.,  2.,    148.0,   66.7,  -24.8,   18.7,  -65.0,
     C       14.,  4.,  3.,    193.5,   22.0,   -7.2,    3.3,  -20.9,
     C       14.,  5.,  1.,    167.0,   70.8,  -23.4,   17.4,  -64.2,
     C       14.,  5.,  2.,    217.0,   19.6,   -6.2,    2.8,  -19.0,
     C       14.,  6.,  1.,    205.0,   60.8,  -20.2,   13.2,  -41.7,
     C       14.,  6.,  2.,    250.0,   19.3,   -5.8,    2.8,  -17.8,
     C       14.,  7.,  1.,    246.0,   49.5,  -16.3,    9.6,  -33.4,
     C       14.,  7.,  2.,    285.0,   19.0,   -5.4,    2.8,  -16.6,
     C       14.,  8.,  1.,    303.0,   38.3,  -12.4,    6.4,  -25.1,
     C       14.,  8.,  2.,    321.0,   18.6,   -5.1,    2.8,  -15.4,
     C       14.,  9.,  1.,    351.0,   27.0,   -8.5,    3.8,  -16.8,
     C       14.,  9.,  2.,    371.0,   18.3,   -4.7,    2.8,  -14.1,
     C       14., 10.,  1.,    401.0,   14.0,   -4.6,    1.6,   -8.5,
     C       14., 10.,  2.,    423.0,   18.0,   -4.3,    2.8,  -12.9,
     C       14., 11.,  1.,    476.0,   17.7,   -4.0,    2.7,  -11.7,
     C       14., 11.,  2.,   2259.0,   22.4,   -6.9,    4.1,  -18.0,
     C       14., 12.,  1.,    523.0,    9.8,   -2.9,    1.4,   -6.6,
     C       14., 12.,  2.,   2309.0,   22.4,   -6.9,    4.1,  -18.0,
     C       14., 13.,  1.,   2438.0,   22.9,   -7.3,    4.0,  -19.1,
     C       14., 14.,  1.,   2673.0,   12.7,   -4.3,    1.9,  -10.4,
     C       16.,  1.,  1.,     10.4,    6.0,  -22.0,   20.0,  -20.0,
     C       16.,  1.,  2.,     20.2,   51.3,  -33.2,    1.4,  -40.2,
     C       16.,  2.,  1.,     23.4,   98.7,  -65.4,    1.9,  -72.3,
     C       16.,  2.,  2.,     30.7,   52.5,  -34.5,    1.4,  -40.5,
     C       16.,  3.,  1.,     35.0,   74.5,  -49.4,    1.3,  -54.6,
     C       16.,  3.,  2.,     43.8,   53.8,  -35.8,    1.4,  -40.7,
     C       16.,  4.,  1.,     47.3,   50.4,  -33.4,    0.6,  -36.9,
     C       16.,  4.,  2.,     57.6,   55.1,  -37.2,    1.4,  -41.0,
     C       16.,  5.,  1.,     72.7,   19.8,   -5.7,    1.6,  -11.9,
     C       16.,  5.,  2.,    239.0,   73.2,  -27.0,   15.8,  -61.1,
     C       16.,  5.,  3.,    288.2,   23.1,   -8.0,    3.3,  -19.5,
     C       16.,  6.,  1.,     88.1,    9.0,   -2.8,    0.7,   -5.4,
     C       16.,  6.,  2.,    257.0,   73.2,  -27.0,   15.8,  -61.1,
     C       16.,  6.,  3.,    309.7,   23.1,   -8.0,    3.3,  -19.5,
     C       16.,  7.,  1.,    281.0,   72.0,  -21.7,   14.2,  -55.9,
     C       16.,  7.,  2.,    343.0,   19.6,   -6.8,    2.8,  -17.5,
     C       16.,  8.,  1.,    328.0,   60.8,  -20.2,   10.9,  -41.7,
     C       16.,  8.,  2.,    384.0,   19.3,   -6.3,    2.8,  -16.6,
     C       16.,  9.,  1.,    379.0,   49.5,  -16.3,    8.0,  -33.4,
     C       16.,  9.,  2.,    426.0,   19.1,   -5.9,    2.8,  -15.6,
     C       16., 10.,  1.,    447.0,   38.3,  -12.4,    5.5,  -25.1,
     C       16., 10.,  2.,    469.0,   18.8,   -5.5,    2.8,  -14.7,
     C       16., 11.,  1.,    505.0,   27.0,   -8.5,    3.3,  -16.8,
     C       16., 11.,  2.,    528.0,   18.6,   -5.1,    2.8,  -13.7,
     C       16., 12.,  1.,    564.0,   14.0,   -4.6,    1.5,   -8.5,
     C       16., 12.,  2.,    589.0,   18.3,   -4.7,    2.8,  -12.8,
     C       16., 13.,  1.,    652.0,   18.1,   -4.4,    2.7,  -11.8,
     C       16., 13.,  2.,   3017.0,   22.8,   -7.1,    4.1,  -18.0,
     C       16., 14.,  1.,    707.0,    9.7,   -2.8,    1.4,   -6.4,
     C       16., 14.,  2.,   3075.0,   22.8,   -7.1,    4.1,  -18.0,
     C       16., 15.,  1.,   3224.0,   23.3,   -7.6,    4.0,  -19.3,
     C       16., 16.,  1.,   3493.0,   12.8,   -4.3,    1.9,  -10.5,
     C       18.,  1.,  1.,     15.8,  171.1,  -78.0,    3.8, -169.0,
     C       18.,  1.,  2.,     29.2,   48.7,  -30.5,    1.4,  -39.7,
     C       18.,  2.,  1.,     27.6,  147.0,  -97.4,    3.2, -107.7,
     C       18.,  2.,  2.,     41.7,   50.0,  -31.8,    1.4,  -40.0,
     C       18.,  3.,  1.,     40.9,  122.8,  -81.4,    2.6,  -90.0,
     C       18.,  3.,  2.,     55.5,   51.3,  -33.2,    1.4,  -40.2,
     C       18.,  4.,  1.,     59.7,   98.7,  -65.4,    1.9,  -72.3,
     C       18.,  4.,  2.,     70.4,   52.5,  -34.5,    1.4,  -40.5,
     C       18.,  5.,  1.,     75.2,   74.5,  -49.4,    1.3,  -54.6,
     C       18.,  5.,  2.,     87.6,   53.8,  -35.8,    1.4,  -40.7,
     C       18.,  6.,  1.,     91.2,   50.4,  -33.4,    0.6,  -36.9,
     C       18.,  6.,  2.,    105.0,   55.1,  -37.2,    1.4,  -41.0/ 
C-----------------------------------------------------------------------
	DATA DIR_DATA_3/18., 7., 1., 125.0,  19.8,  -5.7,   1.9,  -11.9,
     C       18.,  7.,  2.,    373.0,   74.8,  -27.0,   14.1,  -58.6,  
     C       18.,  7.,  3.,    427.0,   23.4,   -8.3,    3.3,  -18.5,  
     C       18.,  8.,  1.,    143.0,    9.0,   -2.7,    0.8,   -5.4,  
     C       18.,  8.,  2.,    394.0,   74.8,  -27.0,   14.1,  -58.6,  
     C       18.,  8.,  3.,    453.1,   23.4,   -8.3,    3.3,  -18.5,  
     C       18.,  9.,  1.,    423.0,   72.6,  -19.9,   11.9,  -51.0, 
     C       18.,  9.,  2.,    498.0,   19.6,   -7.3,    2.8,  -16.0,  
     C       18., 10.,  1.,    479.0,   60.8,  -20.2,    9.3,  -41.7,  
     C       18., 10.,  2.,    545.0,   19.4,   -6.8,    2.8,  -15.3,  
     C       18., 11.,  1.,    539.0,   49.5,  -16.3,    6.9,  -33.4,  
     C       18., 11.,  2.,    594.0,   19.2,   -6.4,    2.8,  -14.6,  
     C       18., 12.,  1.,    618.0,   38.3,  -12.4,    4.8,  -25.1,  
     C       18., 12.,  2.,    644.0,   18.9,   -5.9,    2.8,  -14.0,  
     C       18., 13.,  1.,    686.0,   27.0,   -8.5,    3.0,  -16.8,  
     C       18., 13.,  2.,    713.0,   18.7,   -5.4,    2.8,  -13.3,  
     C       18., 14.,  1.,    755.0,   14.0,   -4.6,    1.4,   -8.5,  
     C       18., 14.,  2.,    784.0,   18.5,   -5.0,    2.8,  -12.6,  
     C       18., 15.,  1.,    855.0,   18.4,   -4.6,    2.7,  -12.0,  
     C       18., 15.,  2.,   3885.0,   23.1,   -7.3,    4.1,  -18.0,  
     C       18., 16.,  1.,    918.0,    9.6,   -2.8,    1.4,   -6.2,  
     C       18., 16.,  2.,   3951.0,   23.1,   -7.3,    4.1,  -18.0,  
     C       18., 17.,  1.,   4121.0,   23.7,   -7.8,    3.9,  -19.5,  
     C       18., 18.,  1.,   4426.0,   12.8,   -4.4,    1.9,  -10.5,  
     C       20.,  1.,  1.,      6.1,    2.5,   -2.5,    8.0,   -5.5,  
     C       20.,  1.,  2.,     28.0,   74.3,  -24.2,    7.0,  -63.0,  
     C       20.,  1.,  3.,     40.3,   17.6,   -3.8,    1.9,  -13.8,  
     C       20.,  2.,  1.,     11.9,    7.9,   -2.0,    0.2,   -6.0,  
     C       20.,  2.,  2.,     37.0,   74.3,  -24.2,    7.0,  -63.0,  
     C       20.,  2.,  3.,     45.2,   17.6,   -3.8,    1.9,  -13.8,  
     C       20.,  3.,  1.,     51.2,   74.3,  -24.2,    7.0,  -63.0,  
     C       20.,  3.,  2.,     70.1,   17.6,   -3.8,    1.95, -13.8,  
     C       20.,  4.,  1.,     67.3,   55.8,  -15.8,    6.4,  -44.5,  
     C       20.,  4.,  2.,     86.4,   16.2,   -3.2,    1.77, -11.6,  
     C       20.,  5.,  1.,     84.5,   47.1,  -14.5,    4.75, -35.5,  
     C       20.,  5.,  2.,    104.0,   18.9,   -5.13,   1.62, -13.2,  
     C       20.,  6.,  1.,    109.0,   40.9,  -13.6,    3.44, -30.1,  
     C       20.,  6.,  2.,    123.0,   20.4,   -6.33,   2.13, -13.8,  
     C       20.,  7.,  1.,    128.0,   22.9,   -7.4,    2.84, -15.9,  
     C       20.,  7.,  2.,    144.0,   21.9,   -7.7,    1.9,  -14.9,  
     C       20.,  8.,  1.,    148.0,   11.1,   -3.35,   1.26,  -7.3,  
     C       20.,  8.,  2.,    165.0,   22.7,   -8.65,   1.89, -15.5,  
     C       20.,  9.,  1.,    189.0,   19.8,   -5.7,    1.75, -11.9,  
     C       20.,  9.,  2.,    534.0,   76.1,  -27.0,   12.8,  -56.6,  
     C       20.,  9.,  3.,    593.1,   23.5,   -8.4,    3.3,  -17.8,  
     C       20., 10.,  1.,    211.0,    9.0,   -2.6,    0.9,   -5.4,  
     C       20., 10.,  2.,    559.0,   76.1,  -27.0,   12.8,  -56.6,  
     C       20., 10.,  3.,    623.7,   23.5,   -8.4,    3.3,  -17.8,  
     C       20., 11.,  1.,    592.0,   76.5,  -24.5,   10.3,  -50.5,  
     C       20., 11.,  2.,    680.0,   19.5,   -7.8,    2.8,  -14.5,  
     C       20., 12.,  1.,    657.0,   60.8,  -20.2,    8.1,  -41.7,  
     C       20., 12.,  2.,    734.0,   19.4,   -7.3,    2.8,  -14.1,  
     C       20., 13.,  1.,    727.0,   49.5,  -16.3,    6.1,  -33.4,  
     C       20., 13.,  2.,    790.0,   19.2,   -6.8,    2.8,  -13.7,  
     C       20., 14.,  1.,    818.0,   38.3,  -12.4,    4.3,  -25.1,  
     C       20., 14.,  2.,    847.0,   19.0,   -6.3,    2.8,  -13.2,  
     C       20., 15.,  1.,    894.0,   27.0,   -8.5,    2.7,  -16.8,  
     C       20., 15.,  2.,    925.0,   18.9,   -5.8,    2.8,  -12.8,  
     C       20., 16.,  1.,    974.0,   14.0,   -4.6,    1.3,   -8.5,  
     C       20., 16.,  2.,   1006.0,   18.7,   -5.3,    2.8,  -12.4,  
     C       20., 17.,  1.,   1087.0,   18.6,   -4.6,    2.7,  -12.1,  
     C       20., 17.,  2.,   4865.0,   23.4,   -7.4,    4.1,  -18.0,  
     C       20., 18.,  1.,   1157.0,    9.5,   -2.7,    1.4,   -6.1,  
     C       20., 18.,  2.,   4939.0,   23.4,   -7.4,    4.1,  -18.0,  
     C       20., 19.,  1.,   5129.0,   24.0,   -7.9,    3.9,  -19.6,  
     C       20., 20.,  1.,   5470.0,   12.9,   -4.4,    1.9,  -10.5,  
     C       26.,  1.,  1.,      7.9,   31.9,  -15.0,   0.32,  -28.1,  
     C       26.,  1.,  2.,      9.0,   15.0,  -16.7,    7.0,  -12.7,  
     C       26.,  1.,  3.,     59.0,   115.0,  -72.40,  9.57, -107.0, 
     C       26.,  2.,  1.,     16.18,  17.40,  -3.27,   0.16,  -10.16,
     C       26.,  2.,  2.,     24.83,  30.12,  -38.82,  18.60, -45.72,
     C       26.,  2.,  3.,     83.37,  115.0,  -72.40,  9.57, -107.0, 
     C       26.,  3.,  1.,     34.75,  84.77, -67.60,  21.00, -84.08, 
     C       26.,  3.,  2.,     93.28,  87.7,  -49.6,    11.4,  -84.8, 
     C       26.,  3.,  3.,    131.9,   25.9,   -11.70,  2.32, -23.90, 
     C       26.,  4.,  1.,     53.74,  77.40, -43.90,  19.60, -81.9,  
     C       26.,  4.,  2.,    111.9,   79.10, -30.0,    8.38, -74.60, 
     C       26.,  4.,  3.,    151.0,   16.70, -3.44,    2.32,  -15.10,
     C       26.,  5.,  1.,     75.15,  48.10, -20.4,   16.2,  -48.4,  
     C       26.,  5.,  2.,    132.7,   66.80, -18.9,    9.29, -60.5, 
     C       26.,  5.,  3.,    172.4,   13.4,  -0.410,   2.33, -10.9, 
     C       26.,  6.,  1.,     98.69,  36.9,  -11.8,   10.3,  -31.5, 
     C       26.,  6.,  2.,    155.5,   67.0,  -18.6,    9.43, -56.5, 
     C       26.,  6.,  3.,    195.8,   12.7,   -0.086,  2.42,  -8.97,
     C       26.,  7.,  1.,    124.2,   14.6,   -4.36,   5.98, -10.5, 
     C       26.,  7.,  2.,    180.0,   67.9,  -20.6,    9.82, -53.7, 
     C       26.,  7.,  3.,    220.9,   15.6,   -2.29,   2.3,  -10.6, 
     C       26.,  8.,  1.,    151.7,   14.3,   -4.44,   2.45,  -9.53,
     C       26.,  8.,  2.,    213.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       26.,  8.,  3.,    249.,    19.2,   -5.7,    2.3,  -12.7, 
     C       26.,  9.,  1.,    235.0,   69.9,  -23.7,    9.5,  -51.7,
     C       26.,  9.,  2.,    271.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       26., 10.,  1.,    262.0,   57.7,  -18.6,    7.8,  -40.3,    
     C       26., 10.,  2.,    297.0,   21.0,   -7.1,    2.3,  -14.1,
     C       26., 11.,  1.,    290.0,   45.6,  -13.9,    6.2,  -30.0, 
     C       26., 11.,  2.,    324.0,   22.8,   -8.4,    2.3,  -15.4, 
     C       26., 12.,  1.,    331.0,   39.2,   -9.7,    4.4,  -20.8, 
     C       26., 12.,  2.,    356.0,   24.6,   -9.8,    2.3,  -16.8, 
     C       26., 13.,  1.,    361.0,   21.3,   -5.9,    3.0,  -12.6, 
     C       26., 13.,  2.,    388.0,   26.4,  -11.2,    2.3,  -18.1/
C-----------------------------------------------------------------------
	DATA DIR_DATA_4/26., 14., 1.,  392.0,  9.1,  -2.6,  1.4,   -5.6,
     C       26., 14.,  2.,    421.0,   28.2,  -12.5,    2.3,  -19.4, 
     C       26., 15.,  1.,    457.0,   19.8,   -5.7,    2.1,  -11.9, 
     C       26., 15.,  2.,   1185.0,   78.9,  -27.0,   10.6,  -52.8, 
     C       26., 15.,  3.,   1254.3,   23.5,   -7.8,    3.3,  -16.5, 
     C       26., 16.,  1.,    490.0,    9.0,   -2.6,    1.0,   -5.4, 
     C       26., 16.,  2.,   1223.0,   78.9,  -27.0,   10.6,  -52.8, 
     C       26., 16.,  3.,   1298.6,   23.5,   -7.8,    3.3,  -16.5, 
     C       26., 17.,  1.,   1265.0,   82.2,  -26.4,    6.1,  -49.8, 
     C       26., 17.,  2.,   1397.0,   19.2,   -5.5,    2.8,  -12.3, 
     C       26., 18.,  1.,   1358.0,   68.5,  -22.0,    5.1,  -41.5, 
     C       26., 18.,  2.,   1471.0,   19.2,   -5.5,    2.8,  -12.3, 
     C       26., 19.,  1.,   1456.0,   54.8,  -17.6,    4.1,  -33.2, 
     C       26., 19.,  2.,   1548.0,   19.2,   -5.5,    2.8,  -12.3, 
     C       26., 20.,  1.,   1582.0,   41.1,  -13.2,    3.1,  -24.9, 
     C       26., 20.,  2.,   1622.0,   19.2,   -5.5,    2.8,  -12.3, 
     C       26., 21.,  1.,   1689.0,   27.4,   -8.8,    2.0,  -16.6, 
     C       26., 21.,  2.,   1731.0,   19.2,   -5.5,    2.8,  -12.3, 
     C       26., 22.,  1.,   1799.0,   13.7,   -4.4,    1.0,   -8.3, 
     C       26., 22.,  2.,   1842.0,   19.2,   -5.5,    2.8,  -12.3, 
     C       26., 23.,  1.,   1950.0,   19.2,   -5.3,    2.7,  -12.3, 
     C       26., 23.,  2.,   8482.0,   24.1,   -7.9,    4.1,  -18.0, 
     C       26., 24.,  1.,   2045.0,    9.3,   -2.6,    1.4,   -5.8, 
     C       26., 24.,  2.,   8580.0,   24.1,   -7.9,    4.1,  -18.0, 
     C       26., 25.,  1.,   8828.0,   24.8,   -8.4,    3.8,  -20.0, 
     C       26., 26.,  1.,   9278.0,   13.0,   -4.5,    1.9,  -10.6, 
     C       28.,  1.,  1.,      8.7,    2.5,   -0.8,    0.2,   -1.2, 
     C       28.,  1.,  2.,     10.0,   12.6,   -4.0,    0.4,   -6.1, 
     C       28.,  1.,  3.,     73.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  2.,  1.,     18.2,   32.2,  -10.0,    1.0,  -15.4, 
     C       28.,  2.,  2.,     97.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  2.,  3.,    142.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28.,  3.,  1.,     35.2,   44.4,  -14.1,    1.4,  -21.5, 
     C       28.,  3.,  2.,    122.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  3.,  3.,    166.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28.,  4.,  1.,     54.9,   50.3,  -16.0,    1.6,  -24.3, 
     C       28.,  4.,  2.,    146.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  4.,  3.,    190.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28.,  5.,  1.,     75.5,   49.9,  -15.9,    1.6,  -24.1, 
     C       28.,  5.,  2.,    171.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  5.,  3.,    215.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28.,  6.,  1.,    108.0,   50.8,  -16.1,    1.6,  -24.6, 
     C       28.,  6.,  2.,    196.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  6.,  3.,    239.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28.,  7.,  1.,    133.0,   43.2,  -13.7,    1.3,  -20.9, 
     C       28.,  7.,  2.,    221.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  7.,  3.,    264.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28.,  8.,  1.,    162.0,   34.5,  -10.9,    1.1,  -16.7, 
     C       28.,  8.,  2.,    246.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  8.,  3.,    288.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28.,  9.,  1.,    193.0,   24.1,   -7.7,    0.7,  -11.7, 
     C       28.,  9.,  2.,    271.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28.,  9.,  3.,    313.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28., 10.,  1.,    225.0,   12.5,   -4.0,    0.4,   -6.0, 
     C       28., 10.,  2.,    296.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28., 10.,  3.,    338.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28., 11.,  1.,    321.0,   69.9,  -23.7,    9.5,  -51.7, 
     C       28., 11.,  2.,    363.0,   19.2,   -5.7,    2.3,  -12.7, 
     C       28., 12.,  1.,    352.0,   57.7,  -18.6,    7.8,  -40.3, 
     C       28., 12.,  2.,    393.0,   21.0,   -7.1,    2.3,  -14.1, 
     C       28., 13.,  1.,    384.0,   45.6,  -13.9,    6.2,  -30.0, 
     C       28., 13.,  2.,    423.0,   22.8,   -8.4,    2.3,  -15.4, 
     C       28., 14.,  1.,    430.0,   33.4,   -9.7,    4.6,  -20.8, 
     C       28., 14.,  2.,    458.0,   24.6,   -9.8,    2.3,  -16.8, 
     C       28., 15.,  1.,    464.0,   21.3,   -5.9,    3.0,  -12.6, 
     C       28., 15.,  2.,    494.0,   26.4,  -11.2,    2.3,  -18.1, 
     C       28., 16.,  1.,    499.0,    9.1,   -2.6,    1.4,   -5.6, 
     C       28., 16.,  2.,    531.0,   28.2,  -12.5,    2.3,  -19.4, 
     C       28., 17.,  1.,    571.0,   19.8,   -5.7,    2.2,  -11.9, 
     C       28., 17.,  2.,   1458.0,   79.6,  -27.0,   10.1,  -51.9, 
     C       28., 17.,  3.,   1529.1,   23.5,   -7.8,    3.3,  -16.2, 
     C       28., 18.,  1.,    608.0,    9.0,   -2.6,    1.0,   -5.4, 
     C       28., 18.,  2.,   1500.0,   79.6,  -27.0,   10.1,  -51.9, 
     C       28., 18.,  3.,   1578.0,   23.5,   -7.8,    3.3,  -16.2, 
     C       28., 19.,  1.,   1546.4,   71.69, -23.19,  10.71, -45.63,
     C       28., 19.,  2.,   1692.1,   16.33,  -5.04,   3.52, -11.47,
     C       28., 20.,  1.,   1655.5,   61.24, -19.16,   7.78, -38.09,
     C       28., 20.,  2.,   1786.4,   16.49,  -5.11,   3.44, -11.41,
     C       28., 21.,  1.,   1756.0,   49.29, -15.28,   5.77, -30.11,
     C       28., 21.,  2.,   1882.9,   16.36,  -4.97,   3.35, -11.09,
     C       28., 22.,  1.,   1882.5,   37.12, -11.41,   4.02, -22.30,
     C       28., 22.,  2.,   2179.8,   16.08,  -4.78,   3.26, -10.62,
     C       28., 23.,  1.,   2000.3,   24.76,  -7.54,   2.50, -14.64,
     C       28., 23.,  2.,   2082.6,   15.74,  -4.47,   3.18, -10.13,
     C       28., 24.,  1.,   2131.0,   13.41,  -3.76,   1.16,  -7.24,
     C       28., 24.,  2.,   2185.6,   15.52,  -4.27,   3.09,  -9.74,
     C       28., 25.,  1.,   2290.9,   15.46,  -4.18,   3.01, -9.52, 
     C       28., 25.,  2.,   9914.0,   24.3,   -8.0,    4.1,  -18.0, 
     C       28., 26.,  1.,   2401.2,    7.82,  -2.13,   1.48,  -4.77,
     C       28., 26.,  2.,  10150.0,   23.37,  -9.12,   4.02, -19.82,
     C       28., 27.,  1.,  10299.0,   23.27,  -8.97,   3.92, -19.55,
     C       28., 28.,  1.,  10790.0,   13.0,   -4.5,    1.9,  -10.67/
C-----------------------------------------------------------------------
	COARSE = INDEX/SIZE
	REMAIN = MOD(INDEX, SIZE)
C	WRITE(6,*) INDEX,COARSE,REMAIN

	IF (COARSE.EQ.0) ZR = INT(DIR_DATA_1(1,REMAIN))
	IF (COARSE.EQ.0) IR = INT(DIR_DATA_1(2,REMAIN))
	IF (COARSE.EQ.0) KR = INT(DIR_DATA_1(3,REMAIN))
	IF (COARSE.EQ.1) ZR = INT(DIR_DATA_2(1,REMAIN))
	IF (COARSE.EQ.1) IR = INT(DIR_DATA_2(2,REMAIN))
	IF (COARSE.EQ.1) KR = INT(DIR_DATA_2(3,REMAIN))
	IF (COARSE.EQ.2) ZR = INT(DIR_DATA_3(1,REMAIN))
	IF (COARSE.EQ.2) IR = INT(DIR_DATA_3(2,REMAIN))
	IF (COARSE.EQ.2) KR = INT(DIR_DATA_3(3,REMAIN))
	IF (COARSE.EQ.3) ZR = INT(DIR_DATA_4(1,REMAIN))
	IF (COARSE.EQ.3) IR = INT(DIR_DATA_4(2,REMAIN))
	IF (COARSE.EQ.3) KR = INT(DIR_DATA_4(3,REMAIN))

	DO 100, I=1, 5
		IF (COARSE.EQ.0) REL(I) = DIR_DATA_1(3+I,REMAIN)
		IF (COARSE.EQ.1) REL(I) = DIR_DATA_2(3+I,REMAIN)
		IF (COARSE.EQ.2) REL(I) = DIR_DATA_3(3+I,REMAIN)
		IF (COARSE.EQ.3) REL(I) = DIR_DATA_4(3+I,REMAIN)
100		CONTINUE  
C----------------------------------------------------------------------- 
	RETURN
	END

	SUBROUTINE EA(INDEX,ZR,IR,RELEA)
C=======================================================================
C This subroutine replaces the open and read statements in the 
C subroutine IONSUB of the Arnaud program.
C
C Author:
C Peter Wurz,  6. Nov. 1997 Initial version
C Peter Wurz, 20. Jan. 1998 Adaptations for SUN/UNIX
C Peter Wurz, 23. Jan. 1998 Remove subtle error in adea access
C-----------------------------------------------------------------------
	INTEGER*4 ZR 		! Atomic number
	INTEGER*4 IR 		! Ionization state
	INTEGER*4 COARSE 	! Array selector
	INTEGER*4 REMAIN 	! Array position
	INTEGER*4 SIZE		! Size of arrays

	PARAMETER (SIZE=100)

	REAL*8 RELEA(6)
	REAL*8 EA_DATA_1(8,SIZE)
	REAL*8 EA_DATA_2(8,0:91)
C-----------------------------------------------------------------------
	DATA EA_DATA_1/1.,  1.,   0.0,   0.0,   0.0,  0.0,  0.0,   0.0,
     C  2.,  1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  2.,  2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  6.,  1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  6.,  2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  6.,  3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  6.,  4.,   297.6, 0.898, 0.0963,-0.638,   0.0,   1.18,
     C  6.,  5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  6.,  6.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  7.,  1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  7.,  2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  7.,  3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  7.,  4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  7.,  5.,   418.5, 0.840, 0.0901,-0.597,   0.0,   1.10,
     C  7.,  6.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  7.,  7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  8.,  1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  8.,  2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  8.,  3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  8.,  4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  8.,  5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  8.,  6.,   559.8, 0.584, 0.0658,-0.411,   0.0,   0.756,
     C  8.,  7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  8.,  8.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10., 1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10., 2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10., 3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10., 4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10., 5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10., 6.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10., 7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10., 8.,   903.6, 0.361, 0.0396,-0.256,   0.0,   0.472,
     C  10., 9.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  10.,10.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 6.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 8.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11., 9.,  1106.1, 0.289, 0.0313,-0.205,   0.0,   0.379,
     C  11.,10.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  11.,11.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12., 1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12., 2.,    52.0,   0.0,   14.6,   0.0,   0.0,   0.0,
     C  12., 3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12., 4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12., 5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12., 6.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12., 7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12., 8.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12., 9.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12.,10.,  1329.0, 0.232, 0.0249,-0.165,   0.0,   0.305,
     C  12.,11.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  12.,12.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13., 1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13., 2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13., 3.,    78.0,   0.0,   13.4,   0.0,   0.0,   0.0,
     C  13., 4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13., 5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13., 6.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13., 7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13., 8.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13., 9.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13.,10.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13.,11.,  1572.3, 0.188, 0.0200,-0.134,   0.0,   0.247,
     C  13.,12.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  13.,13.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14., 1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14., 2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14., 3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14., 4.,   104.0,   0.0,   13.5,   0.0,   0.0,   0.0,
     C  14., 5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14., 6.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14., 7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14., 8.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14., 9.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14.,10.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14.,11.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14.,12.,  1836.0, 0.151, 0.0161,-0.107,   0.0,   0.199,
     C  14.,13.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  14.,14.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16., 1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16., 2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16., 3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16., 4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16., 5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16., 6.,   156.0,   0.0,   14.2,   0.0,   0.0,   0.0,
     C  16., 7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16., 8.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16., 9.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16.,10.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16.,11.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16.,12.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16.,13.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16.,14.,  2424.6, 0.0988, 0.0105,-0.0704,   0.0,   0.130,
     C  16.,15.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  16.,16.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0/
C-----------------------------------------------------------------------
	DATA EA_DATA_2/18., 1.,   0.0,   0.0,   0.0,  0.0,  0.0,  0.0,
     C  18., 2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18., 3.,   184.3,   0.0,    0.0,   0.0,   12.3,   0.0,
     C  18., 4.,   189.0,   0.0,    0.0,   0.0,   12.3,   0.0,
     C  18., 5.,   210.4,   0.0,    0.0,   0.0,   12.3,   0.0,
     C  18., 6.,   243.5,   0.0,    0.0,   0.0,   12.3,   0.0,
     C  18., 7.,   243.0,   0.0,    0.0,   0.0,   12.3,   0.0,
     C  18., 8.,   248.9,   0.0,    0.0,   0.0,   13.8,   0.0,
     C  18., 9.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18.,10.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18.,11.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18.,12.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18.,13.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18.,14.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18.,15.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18.,16.,  3094.8,0.0658,0.00699,-0.0469,   0.0, 8.69E-02,
     C  18.,17.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  18.,18.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20., 1.,    25.0,  15.0,    0.0,   0.0,   0.0,   16.8,
     C  20., 2.,    29.0,  28.4,    0.0,   0.0,   0.0,   31.8,
     C  20., 3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20., 4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20., 5.,   287.8,   0.0,    0.0,   0.0,   10.0,   0.0,
     C  20., 6.,   291.7,   0.0,    0.0,   0.0,   10.0,   0.0,
     C  20., 7.,   311.2,   0.0,    0.0,   0.0,   10.0,   0.0,
     C  20., 8.,   340.1,   0.0,    0.0,   0.0,   10.0,   0.0,
     C  20., 9.,   341.1,   0.0,    0.0,   0.0,   10.0,   0.0,
     C  20.,10.,   347.9,   0.0,    0.0,   0.0,   8.42,   0.0,
     C  20.,11.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20.,12.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20.,13.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20.,14.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20.,15.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20.,16.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20.,17.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20.,18.,  3846.6,0.0446,0.00473,-0.0318,   0.0,   5.88E-02,
     C  20.,19.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  20.,20.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26., 1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26., 2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26., 3.,   57.28, 0.878,    0.0,-0.0115,  71.2,   47.9,
     C  26., 4.,    60.0,  3.02,   67.5,  -59.8,   46.0,   0.0,
     C  26., 5.,    81.0,   0.0,  0.280,  -16.2,   35.5,   0.0,
     C  26., 6.,    95.0,   0.0,    0.0,  -5.83,   12.3,   8.85,
     C  26., 7.,   125.0,   0.0,    0.0,  -48.1,   42.5,   16.3,
     C  26., 8.,   160.0,  5.00,   43.0,  -72.6,   42.9,   0.0,
     C  26., 9.,   650.0,   0.0,    0.0,   0.0,   1.87,   0.0,
     C  26.,10.,   650.0,   0.0,    0.0,   0.0,   1.96,   0.0,
     C  26.,11.,   650.0,   0.0,    0.0,   0.0,   3.21,   0.0,
     C  26.,12.,   650.0,   0.0,    0.0,   0.0,   3.89,   0.0,
     C  26.,13.,   670.0,   0.0,    0.0,   0.0,   4.10,   0.0,
     C  26.,14.,   670.9,   0.0,    0.0,   0.0,   5.92,   0.0,
     C  26.,15.,   700.0,   0.0,    0.0,   0.0,   4.81,   0.0,
     C  26.,16.,   704.0,   0.0,    0.0,   0.0,   2.95,   0.0,
     C  26.,17.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26.,18.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26.,19.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26.,20.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26.,21.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26.,22.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26.,23.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26.,24.,  6591.7,0.0153,0.00162,-0.0109,   0.0,   2.02E-02,
     C  26.,25.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  26.,26.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 1.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 2.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 3.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 4.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 5.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 6.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 7.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 8.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28., 9.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,10.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,11.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,12.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,13.,   730.9,   0.0,    0.0,   0.0,   5.10,   0.0,
     C  28.,14.,   779.7,   0.0,    0.0,   0.0,   5.10,   0.0,
     C  28.,15.,   798.8,   0.0,    0.0,   0.0,   5.10,   0.0,
     C  28.,16.,   792.4,   0.0,    0.0,   0.0,   5.10,   0.0,
     C  28.,17.,   833.4,   0.0,    0.0,   0.0,   5.10,   0.0,
     C  28.,18.,   840.0,   0.0,    0.0,   0.0,   2.27,   0.0,
     C  28.,19.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,20.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,21.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,22.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,23.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,24.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,25.,     0.0,   0.0,     0.0,   0.0,   0.0,   0.0,
     C  28.,26.,  7669.9,0.0111,0.00118,-0.00789,   0.0,   1.46E-02,
     C  28.,27.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0,
     C  28.,28.,     0.0,   0.0,    0.0,   0.0,   0.0,   0.0/
C-----------------------------------------------------------------------
	COARSE = INDEX/(SIZE+1)
	REMAIN = MOD(INDEX, SIZE+1)
C	WRITE(6,*) INDEX,COARSE,REMAIN

	IF (COARSE.EQ.0) ZR = INT(EA_DATA_1(1,REMAIN))
	IF (COARSE.EQ.0) IR = INT(EA_DATA_1(2,REMAIN))
	IF (COARSE.EQ.1) ZR = INT(EA_DATA_2(1,REMAIN))
	IF (COARSE.EQ.1) IR = INT(EA_DATA_2(2,REMAIN))
	DO 100, I=1, 6
		IF (COARSE.EQ.0) RELEA(I) = EA_DATA_1(2+I,REMAIN)
		IF (COARSE.EQ.1) RELEA(I) = EA_DATA_2(2+I,REMAIN)
100		CONTINUE  
C----------------------------------------------------------------------- 
	RETURN
	END
 
