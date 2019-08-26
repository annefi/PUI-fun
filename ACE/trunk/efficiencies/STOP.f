       SUBROUTINE STOP(Z1,M1,Z2,EE,SE,SN,UNITS)
c
       IMPLICIT REAL*4(A-Z)
       INTEGER Z1,Z2,UNITS
       DIMENSION PCOEF(8),X(8)
c
       IF (Z1.GT.92) GOTO 210
       IF (EE.LT.1E-10) GOTO 220
       CALL SCOEF(Z1,A,B,Y,Y,Y,Y,LFCTR,X)
       IF (M1.EQ.0.) THEN
          MM1=A
          M1=B
       END IF
       E=EE/M1
       IF (E.GT.1E5) GOTO 210
       CALL SCOEF(Z2,Y,Y,M2,RHO,ATRHO,VFERMI,Y,PCOEF)
       IF (Z1.EQ.1) THEN
          CALL PSTOP(Z1,M1,Z2,M2,E,PCOEF,SE)
       ELSE IF (Z1.EQ.2) THEN 
          CALL HESTOP(Z1,M1,Z2,M2,E,PCOEF,SE)
       ELSE 
          CALL HISTOP(Z1,M1,Z2,M2,E,EE,VFERMI,LFCTR,PCOEF,SE)
       END IF
c
       EPSIL=32.53*M2*EE/(Z1*Z2*(M1+M2)*(Z1**.23+Z2**.23))
       IF (EPSIL.LT.30.) THEN
          A=(.01321*EPSIL**.21226)+(.19593*SQRT(EPSIL))
          SN=.5*ALOG(1+1.1383*EPSIL)/(EPSIL+A)
       ELSE
          SN=ALOG(EPSIL)/(2*EPSIL)
       END IF
c
       SN=SN*Z1*Z2*M1*8.462/((M1+M2)*(Z1**.23+Z2**.23))
       IF (UNITS.EQ.2) THEN
          SE=SE*.60222/M2
          SN=SN*.60222/M2
       ELSE IF (UNITS.EQ.3) THEN
          SE=SE*ATRHO*1E-23
          SN=SN*ATRHO*1E-23
       ELSE IF (UNITS.EQ.4) THEN
          A=(M1+M2)*SQRT(Z1**.6667+Z2**.6667)/(Z1*Z2*M1*8.462)
          SE=SE*A
          SN=SN*A
       END IF
       RETURN
  210  WRITE(*,*)
       WRITE(*,*) ' INPUT PARAMETERS OUTSIDE LIMIT OF PROGRAM'
  220  SE=0
       SN=0
       RETURN
       END       
